#include <Planner/impl/LatticePlanner.h>
#include <Planner/type/STGraph.h>
#include <Planner/tool/PredictionQuerier.h>
#include <Planner/tool/lattice/LatticeGenerator.h>
#include <Planner/tool/lattice/LatticeEvaluator.h>
#include <Planner/tool/CollisionChecker.h>
#include <nox>

USING_NAMESPACE_NOX;
using namespace nox::app;
using namespace nox::type;
using std::endl;

Result<bool> LatticePlanner::Plan(const PlannerBase::Frame & frame, type::Trajectory &result)
{
    struct PlanningResult
    {
        type::Trajectory trajectory;
        double cost = 0;
    };

    struct PtrPlanningResultComparator
    {
        bool operator()(const Ptr<PlanningResult> & a, const Ptr<PlanningResult> & b)
        {
            return a->cost > b->cost;
        }
    };

    struct PtrReferenceLineComparator
    {
        bool operator()(const Ptr<ReferenceLine> & a, const Ptr<ReferenceLine> & b)
        {
            return not a->IsPriorThan(*b);
        }
    };
    Heap<Ptr<ReferenceLine>, PtrReferenceLineComparator> references_heap;
    Heap<Ptr<PlanningResult>, PtrPlanningResultComparator> results_heap;

    for(auto & i : frame.references)
    {
        if(not i->Dead())
            references_heap.push(i);
    }

    string error_msg;
    bool is_optimal_reference_line = true;
    auto init_point = frame.stitch->Back();
    frame.stitch->PopBack();

    Logger::I("LatticePlanner")
        << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl
        << "Start to plan ...";

    while (references_heap.HasNext())
    {
        auto i = references_heap.Next();
        type::Trajectory candidate;

        double cost;
        auto planning_result = PlanOnReferenceLine(frame, init_point, i, candidate, cost);
        if(planning_result.OK())
        {
            auto result_candidate = New<PlanningResult>();
            result_candidate->cost = cost;
            result_candidate->trajectory = *frame.stitch + candidate;

            LaunchTrajectory(result_candidate->trajectory, frame.vehicle);

            if(not is_optimal_reference_line)
                result_candidate->cost *= param.cost_not_optimal_reference_line;
            else
                is_optimal_reference_line = false;

            results_heap.push(result_candidate);
        }
        else
        {
            error_msg += FormatOut("Guide Line [id: %lu]: %s\n", i->id, planning_result.Message().c_str());
        }
    }

    if(results_heap.empty())
        return Result(false, "all guide lines are suck.\n" + error_msg);

    result = results_heap.top()->trajectory;
    return Result(true);
}

Result<bool> LatticePlanner::PlanOnReferenceLine(
    const PlannerBase::Frame    & frame,
    const type::TrajectoryPoint & init_point,
    Ptr<ReferenceLine>            reference,
    type::Trajectory            & result,
    double                      & cost)
{
    analyze_init(LatticePlanner);
    analyze_enable(false);

    analyze(1. 匹配起点在轨迹上的最近点);
    auto matched_point = reference->path.PointAtPosition(init_point.pose.t);
    Logger::D("LatticePlanner")
        << "Plan Init at (x, y, theta, kappa): "
        << init_point.pose.t.x << ", "
        << init_point.pose.t.y << ", "
        << init_point.pose.theta.get() << ", "
        << init_point.kappa;

    analyze(2. 计算起点与最近点的Frenet坐标);
    math::Derivative<2> s, l;
    ComputeFrentState(init_point, matched_point, s, l);

    analyze(3. 计算障碍物时空分布图);
    auto st_graph = New<STGraph>
    (
        frame.scene,                          // 所有障碍物
        reference,                            // 沿着当前参考线建立图
        s[0], s[0] + param.planning_distance, // 图的距离范围
        0,    param.planning_temporal_length, // 图的时间范围
        param.lane_default_width,             // 图的宽度范围
        param.time_resolution                 // 时间分辨率
    );

    analyze(4. 分别生成纵向和横向的候选轨迹);
    auto prediction_querier = New<PredictionQuerier>
    (
        frame.scene,
        reference
    );

    LatticeGenerator generator
    (
        s, l,
        st_graph,
        prediction_querier
    );

    lattice::Bundle lon_bundle;
    lattice::Bundle lat_bundle;
    generator.GenerateBundles
    (
        reference,
        lon_bundle,
        lat_bundle
    );

    analyze(5. 评估轨迹);
    LatticeEvaluator evaluator
    (
        s,                        // 规划起始状态
        lon_bundle,               // 纵向分量
        lat_bundle,               // 横向分量
        frame.vehicle,            // 车体参数与状态
        st_graph,                 // 障碍物时空图
        reference                 // 引导参考线
    );

    analyze(6. 遍历所有候选轨迹，进行碰撞检测与约束检测);
    ConstraintChecker constraint_checker(frame.vehicle);
    CollisionChecker collision_checker(frame.scene, s[0], l[0], reference);

    if(not evaluator.HasNext())
        return Result(false, "Evaluator is empty");

    while (evaluator.HasNext())
    {
        auto candidate = evaluator.Next();

        Trajectory & trajectory = result;
        generator.Combine(reference, *candidate.lon, *candidate.lat, trajectory);

        if(!constraint_checker.CheckTrajectory(trajectory))
            continue;

        if(collision_checker.InCollision(trajectory))
            continue;

        auto lon = std::dynamic_pointer_cast<lattice::Curve>(candidate.lon);
        auto lat = std::dynamic_pointer_cast<lattice::Curve>(candidate.lat);
        Logger::D("LatticePlanner")
            << endl
            << "Pick lon(p, v, t) = " << lon->state[0] << ", " << lon->state[1] << ", " << lon->state.t << endl
            << "Pick lat(p, v, t) = " << lat->state[0] << ", " << lat->state[1] << ", " << lat->state.t << endl
            << "Cost Factor(lon, lat): " << lon->state.cost_factor.all << ", " << lat->state.cost_factor.all << endl
            << "1. lon s travelled: " << lon->state.cost_factor.s_travelled << endl
            << "2. lon v reached:   " << lon->state.cost_factor.v_reached << endl
            << "3. lat offset:      " << lat->state.cost_factor.lateral_offset << endl
            << "Cost: " << candidate.cost_sum << endl
            << "1. lon objective: " << candidate.costs[0] << endl
            << "2. lon jerk:      " << candidate.costs[1] << endl
            << "3. lon collision: " << candidate.costs[2] << endl
            << "4. centripetal a: " << candidate.costs[3] << endl
            << "5. lat offset:    " << candidate.costs[4] << endl
            << "6. lat comfort:   " << candidate.costs[5] << endl;

        cost = candidate.cost_sum;
        return Result(true);
    }

    return Result(false, "All candidate trajectories cannot pass the test.");
}

void LatticePlanner::ComputeFrentState(
    const TrajectoryPoint &init_point,
    const PathPoint &matched_point,
    nox::math::Derivative<2> &s,
    nox::math::Derivative<2> &l)
{
    math::Cartesian2Frenet(
        math::Cartesian(init_point.pose.x, init_point.pose.y, init_point.pose.theta),
        math::Cartesian(matched_point.pose.x, matched_point.pose.y, matched_point.pose.theta),
        init_point.v, init_point.a, init_point.kappa,
        matched_point.s, math::Derivative<1>{matched_point.kappa, matched_point.dkappa},
        OUT s, OUT l
    );

    Logger::D("Planner").Print("Init Frenet: s(%lf, %lf, %lf), l(%lf, %lf, %lf)", s[0], s[1], s[2], l[0], l[1], l[2]);
}

Result<bool> LatticePlanner::Check(const type::Trajectory &trajectory, const PlannerBase::Frame &frame)
{
    //region 检查碰撞
    auto reference = New<ReferenceLine>();
    reference->path = trajectory.ToPath();

    auto frenet = reference->CalculateFrenet(frame.vehicle);
    CollisionChecker collisionChecker(frame.scene, frenet.s, frenet.l, reference, trajectory.Back().t);

    if(collisionChecker.InCollision(trajectory))
        return Result(false, "Checking: Trajectory is in collision.");
    //endregion

    //region 检查停止线
    // 简单实现，直接取最后一个点来判断
    const auto & last_point = trajectory.Back();

    for(auto & i : frame.references)
    {
        if(i->IsBeyondStopLine(last_point.pose))
            return Result(false, "Checking: Trajectory is beyond stop line.");
    }
    //endregion

    return Result(true);
}

void LatticePlanner::LaunchTrajectory(type::Trajectory &trajectory, Ptr<Vehicle> vehicle)
{
    type::Trajectory result;
    double segment = 0;

    if(not trajectory.Empty())
        result.Add(trajectory.Front());

    for(size_t i = 1, size = trajectory.Size(); i < size; ++i)
    {
        segment += trajectory[i].s - trajectory[i-1].s;
        if(segment > 0.2)
        {
            segment = 0;
            result.Add(trajectory[i]);
        }
    }

    if(segment != 0)
        result.Add(trajectory.Back());

    if(result.Size() >= 2)
        result[0].v = result[1].v;

    size_t nearest_index = result.QueryNearestByPosition(vehicle->pose.t);
    if(nearest_index + 1 < result.Size())
        result[nearest_index].v = result[nearest_index + 1].v;

    trajectory = result;
}


#include <Planner/tool/CollisionChecker.h>
#include <nox>
#include <Planner/PlannerConfig.h>
USING_NAMESPACE_NOX;
using namespace nox;
using namespace nox::app;


CollisionChecker::CollisionChecker(
    Ptr<nox::type::Scene> scene,
    double s,
    double l,
    const ReferenceLine &reference)
{
    BuildPredictedEnvironment(scene, s, l, reference);
}

void CollisionChecker::BuildPredictedEnvironment(
    Ptr<nox::type::Scene> scene,
    double s,
    double l,
    const ReferenceLine &reference)
{
    std::vector<Ptr<Obstacle>> obstacles_considered;

    for(auto & i : scene->obstacles)
    {
        if(ShouldIgnore(i.second, s, l, reference))
        {
            continue;
        }

        obstacles_considered.push_back(i.second);
    }

    for(double t : range(0, _param._time_resolution, _param._planning_temporal_length))
    {
        std::vector<Box> predicted_env;

        for(auto & i : obstacles_considered)
        {
            auto box = i->BoxAtTime(t);
            box.Expand(2.0 * _param._buffer._lon, 2.0 * _param._buffer._lat);
            predicted_env.push_back(std::move(box));
        }

        _predicted_bouding_boxes.push_back(std::move(predicted_env));
    }
}

bool CollisionChecker::ShouldIgnore(Ptr<type::Obstacle> obstacle, double s, double l, const ReferenceLine &reference) const
{
    auto point = obstacle->PointAtTime(0);
    auto frenet = GetFrenetCoordinate(point.pose, reference);
    double half_line_width = 0.5 * reference.width;

    return
        std::abs(l) < half_line_width and       // 车在当前参考线上
        frenet.s < s and                        // 障碍物在车的后面
        abs(frenet.l) < 0.5 * reference.width;  // 障碍物也在这条车道线上
}

math::Frenet CollisionChecker::GetFrenetCoordinate(const Pose & pose, const ReferenceLine &referenceLine) const
{
    return referenceLine.CalculateFrenet(pose.x, pose.y, pose.theta);
}

bool CollisionChecker::InCollision(const type::Trajectory &trajectory) const
{
    auto vehicle = cache::ReadEgoVehicle();

    for(size_t i = 0, end = trajectory.Size(); i != end; ++i)
    {
        auto & point = trajectory[i];
        Box box(point.pose, vehicle.param.length.x, vehicle.param.length.y);

        for(auto & obstacle_box : _predicted_bouding_boxes[i])
        {
            if(box.HasOverlap(obstacle_box))
                return true;
        }
    }

    return false;
}



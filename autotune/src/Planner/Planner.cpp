#include <Planner/Planner.h>
#include <Planner/rule/Junction.h>
#include <Planner/rule/Overtake.h>
#include <Planner/rule/SignalLight.h>
#include <Planner/impl/LatticePlanner.h>
#include <Planner/PlannerConfig.h>

using namespace nox::app;
USING_NAMESPACE_NOX;

void Planner::Initialize()
{
    _trajectoryStitcher = New<TrajectoryStitcher>(); // TODO: 参数初始化
    _algorithm = New<LatticePlanner>();
    _scene.SetVehicle(AddressOf(_vehicle));

    InitializeDeciders();

    _scene_server.SetReceiver({"scene"});

    cache::WriteEgoVehicle(AddressOf(_vehicle));
}

void Planner::InitializeDeciders()
{
    auto traffic_decider = std::make_shared<TrafficDecider>(AddressOf(_scene), AddressOf(_vehicle));
    traffic_decider->AddRule<rule::Junction>()
                   ->AddRule<rule::SignalLight>()
                   ->AddRule<rule::Overtake>();

    _deciders.push_back(traffic_decider);
}

void Planner::Process(nav_msgs::Odometry vehicle_state, optional<nox_msgs::Trajectory> &trajectory)
{
    _vehicle.From(vehicle_state);

    nox_msgs::GetSceneRequest request_for_scene;
    _vehicle.pose.To(request_for_scene.location.pose);
    request_for_scene.location.header = vehicle_state.header;

    _scene_server.SendRequest(request_for_scene); // TODO: 超时处理
    _scene.From(_scene_server.GetResponse().scene);

    Trajectory planning_trajectory;
    Process(AddressOf(_vehicle), AddressOf(_scene), planning_trajectory);
    planning_trajectory.To(trajectory.value());
}


Planner::Result Planner::Process(Ptr<type::Vehicle> vehicle, Ptr<type::Scene> scene, type::Trajectory &trajectory)
{
    /// 1. 计算缝合轨迹
    bool is_replan = false;
    trajectory = _trajectoryStitcher->FromLastTrajectory(*vehicle, GetPeriod(), trajectory, &is_replan);

    /// 2. 封装车道线为reference_line
    vector<ReferenceLine> references;
    for(auto & i : scene->lanes)
    {
        references.emplace_back(*i.second);
    }

    /// 3. 运用决策器，决策信息放在ReferenceLine中
    for(auto & decider : _deciders)
    {
        decider->Execute(references);
    }

    /// 4. 构造Frame
    PlannerBase::Frame frame{AddressOf(references), scene, vehicle};

    /// 5. 运用规划器
    auto planning_result = _algorithm->Plan(trajectory, frame, trajectory);

    /// 6. 返回处理结果
    if(planning_result.OK())
    {
        return Result(ErrorCode::Success);
    }
    else
    {
        return Result(ErrorCode::PlanningFail, "Unable to plan");
    }
}




#include <LoMap/LoMap.h>
using namespace nox::app;
USING_NAMESPACE_NOX;

void LoMap::Initialize()
{
    _scene_maintainer = New<SceneMaintainer>(New<Scene>());
    _scene_server.Subscribe({"scene"});
    _scene_server.AddRequestCallback(&LoMap::ProcessOnPlannerRequest, this);

    Logger::GlobalLogLevel(Logger::Debug);
}

bool LoMap::ProcessOnvehicle_state(nav_msgs::Odometry vehicle_state)
{
    type::Odometry state;
    state.From(vehicle_state);
    _scene_maintainer->UpdateState(state);
    return true;
}

bool LoMap::ProcessOnobstacles(nox_msgs::ObstacleArray obstacles)
{
    _scene_maintainer->UpdateObstacles(obstacles);
    return true;
}

bool LoMap::ProcessOnold_map(nox_msgs::Road old_map)
{
    Logger::I("LoMap") << "Receive new map !";
    _scene_maintainer->UpdateMap(old_map);
    return true;
}

bool LoMap::ProcessOnPlannerRequest(
    const nox_msgs::GetScene::Request &request,
    const mailbox::Address &address,
    nox_msgs::GetScene::Response &response)
{
    response.scene = _scene_maintainer->ToMsg();
    return true;
}

bool LoMap::ProcessOnhdmap(std_msgs::String hdmap)
{
    _scene_maintainer->UpdateMap(hdmap);
    return true;
}


#include <LoMap/.LoMapModule.h>
#include <LoMap/LoMap.h>
using namespace nox::app;
USING_NAMESPACE_NOX;

LaunchModule(LoMap);

void LoMapModule::OnStart()
{
    /// 配置节点
    SetFrequency( 20.000000 );
    Viewer::Instance()->SetRender(std::make_shared< None >());

    // TODO： 看门狗

    /// 框架初始化
    InitParameter();
    InitPlugin();
    InitMailbox();
    InitCallback();

    /// 用户模块初始化
    Initialize();
}

void LoMapModule::OnRun()
{
    bool status = true;
    
    if(!mailboxes.vehicle_state.IsFresh())
    {
        status = false;

        ProcessOutput(  );
    }

    if(!mailboxes.obstacles.IsFresh())
    {
        status = false;

        ProcessOutput(  );
    }

    if(!mailboxes.old_map.IsFresh())
    {
        status = false;

        ProcessOutput(  );
    }

    if(status)
    {
        
        Process( mailboxes.vehicle_state.Get(), mailboxes.obstacles.Get(), mailboxes.old_map.Get()  );
        ProcessOutput(  );
    }
}

void LoMapModule::OnFinish()
{
    Terminate();
    TerminateMailbox();
    TerminatePlugin();
}

void LoMapModule::InitMailbox()
{
    
    mailboxes.vehicle_state.Subscribe({"vehicle_state"});
    mailboxes.vehicle_state.SetValidity(1000);
    mailboxes.obstacles.Subscribe({"obstacles"});
    mailboxes.obstacles.SetValidity(1000);
    mailboxes.old_map.Subscribe({"old_map"});
    mailboxes.old_map.SetValidity(1000);
    
}

void LoMapModule::InitParameter()
{
    
}

void LoMapModule::InitCallback()
{
    mailboxes.vehicle_state.AddCallback([&]( const nav_msgs::Odometry & msg, const Address & address ) {
        
        bool result = ProcessOnvehicle_state( msg  );
        ProcessOutput(  );
        return result;
    });

    mailboxes.obstacles.AddCallback([&]( const nox_msgs::ObstacleArray & msg, const Address & address ) {
        
        bool result = ProcessOnobstacles( msg  );
        ProcessOutput(  );
        return result;
    });

    mailboxes.old_map.AddCallback([&]( const nox_msgs::Road & msg, const Address & address ) {
        
        bool result = ProcessOnold_map( msg  );
        ProcessOutput(  );
        return result;
    });

}

void LoMapModule::InitPlugin()
{
    
}

void LoMapModule::TerminateMailbox()
{
    
    mailboxes.vehicle_state.UnSubscribe();
    mailboxes.obstacles.UnSubscribe();
    mailboxes.old_map.UnSubscribe();
}

void LoMapModule::TerminatePlugin()
{
    
}

void LoMapModule::ProcessOutput(  )
{
    
}

void LoMapModule::Initialize()
{
    // Do Nothing ...
}

void LoMapModule::Terminate()
{
    // Do Nothing ...
}

void LoMapModule::Process( optional<nav_msgs::Odometry> vehicle_state, optional<nox_msgs::ObstacleArray> obstacles, optional<nox_msgs::Road> old_map  )
{
    
}




bool LoMapModule::ProcessOnvehicle_state( nav_msgs::Odometry vehicle_state   )
{
    
    return false; /// 
}
bool LoMapModule::ProcessOnobstacles( nox_msgs::ObstacleArray obstacles   )
{
    
    return false; /// 
}
bool LoMapModule::ProcessOnold_map( nox_msgs::Road old_map   )
{
    
    return false; /// 
}
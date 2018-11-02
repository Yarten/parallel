/**
 * @brief 用户模块框架代码，由noxcreate生成
 * @details
 * 1. 维护通信，参数读取，算法加载；
 * 2. 提供空实现的通信处理函数，可由子类重载；
 */
#pragma once

#include <nox>
#include "../../../.param/template/Parameter.h"
#include "../../../.plugin/Plugin.h"
#include "TrackingConfig.h"
#include <memory>
#include <optional>

using std::optional;

namespace nox::app
{
    class TrackingModule
        : public manage::Module
    {
    protected: /// 用户处理代码，默认空实现
        virtual void Initialize();

        virtual void Terminate();

        virtual void Process( nox_msgs::Trajectory trajectory, nav_msgs::Odometry vehicle_state  );

        

        
        void OntrajectoryFail(  );
        void Onvehicle_stateFail(  );

    protected: /// 参数成员、插件成员、信道成员
        struct
        {
            
        } params;

        struct
        {
            
        } plugins;

        struct
        {
            
            mailbox::Topic<nox_msgs::Trajectory> trajectory;
            mailbox::Topic<nav_msgs::Odometry> vehicle_state;
        } mailboxes;

    protected: /// 框架生命周期管理代码
        void OnStart() final;

        void OnRun() final;

        void OnFinish() final;

    private: /// 框架的配置接口
        void InitMailbox();

        void InitParameter();

        void InitCallback();

        void InitPlugin();

        void TerminateMailbox();

        void TerminatePlugin();

        void ProcessOutput(  );

    private: /// 框架成员
        struct
        {
            
        } loaders;

        struct
        {
            
        } postoffices;
    };
}

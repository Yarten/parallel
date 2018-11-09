/**
 * @brief 用户模块代码，由noxcreate生成
 * @details
 * 可以通过override处理函数来实现：
 * 1. 初始化
 * 2. 结束收尾
 * 3. 主处理函数
 * 4. 信道回调处理函数
 * 5. 信道不到位的回调处理函数
 *
 * 另外，其父类框架代码里边，有一些成员变量可以访问：
 * 1. 参数对象
 * 2. 插件对象
 * 3. 通信对象
 */
#pragma once

#include ".SimulatorModule.h"

namespace nox::app
{
    class Simulator
        : public SimulatorModule
    {
        /// Override your process functions ...
    protected:
        void Initialize() override;

        void Process(optional<nav_msgs::Odometry> &vehicle_state, optional<nox_msgs::Location> &Localization,
                     optional<nox_lcm::GPSData> &GPSDataLCM, optional<nox_msgs::Chassis> &chassis,
                     optional<nox_msgs::Location> &localization) override;

    private:
        type::Odometry _odometry;
    };
}

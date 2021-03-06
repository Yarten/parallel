/**
 * @brief 评估生成的Lattice
 */
#pragma once

#include "LatticeCommon.h"
#include <Planner/type/STGraph.h>
#include <Planner/type/ReferenceLine.h>
#include <Planner/tool/ConstraintChecker.h>

namespace nox::app
{
    class LatticeEvaluator
    {
        using Target = ReferenceLine::Target;
    public:
        LatticeEvaluator(
            const math::Derivative<3> & init_state,
            const Target & target,
            const lattice::Bundle & lon_bundles,
            const lattice::Bundle & lat_bundles,
            Ptr<type::Vehicle> vehicle,
            Ptr<STGraph> st_graph,
            ReferenceLine & referenceLine
        );

    public:
        bool HasNext() const;

        lattice::Combination Next();

    private:
        void InitParameter();

        /**
         * @brief 根据当前状态以及规划目标，预计算参考的速度。
         */
        void ComputeLonGuideVelocity(const Target & target);

        /**
         * 评估该轨迹对的分数
         * @param target 规划目标
         * @param lon_traj 纵向的轨迹
         * @param lat_traj 横向的轨迹
         * @param costs 各个角度评估的罚值
         * @return 返回加权和的罚值
         */
        double Evaluate(
            const Target & target,
            const Ptr<math::Parametric<1>> & lon_traj,
            const Ptr<math::Parametric<1>> & lat_traj,
            std::vector<double> & costs
        ) const;

        void Evaluate(const Target & target, lattice::Combination & candidate) const;

    private:
        double LonObjectiveCost(const Ptr <math::Parametric<1>> &lon_traj, const Target &target) const;

        double LonComfortCost(const Ptr<math::Parametric<1>> & lon_traj) const;

        double LonCollisionCost(const Ptr<math::Parametric<1>> & lon_traj) const;

        double CentripetalAccelerationCost(const Ptr<math::Parametric<1>> & lon_traj) const;

        double LatOffsetCost(const Ptr<math::Parametric<1>> & lat_traj, double evaluation_horizon) const;

        double LatComfortCost(const Ptr<math::Parametric<1>> & lon_traj, const Ptr<math::Parametric<1>> & lat_traj) const;

    private:
        struct
        {
            double _time_resolution = 1.0;                // 规划时间分辨率
            double _space_resolution = 1.0;               // 规划距离分辨率
            double _planning_distance = 20.0;             // 规划距离跨度
            double _planning_temporal_length = 10.0;      // 规划时间跨度
            double _stop_in_range_threshold = 1.0;        // 判断是否位于停止点的距离阈值
            double _lon_collision_yield_buffer = 3.0;     // 跟在障碍物后的避让距离（应该跟速度相关）
            double _lon_collision_overtake_buffer = 3.0;  // 超过障碍物的超前距离
            double _lat_offset_bound = 3.0;               // 侧向偏移上界

            struct
            {
                double _min_lon_a;
                double _comfort_a_factor;
            } _vehicle;

            struct
            {
                /// 位置与速度的权衡
                double _s_travelled = 0.5;
                double _v_reached = 0.5;

                /// 侧向偏移在不同方向的惩罚系数
                double _opposite_side_offset = 0.5;
                double _same_side_offset = 0.5;

                /// 各代价系数
                struct
                {
                    double _lon_objective;
                    double _lon_jerk;
                    double _lon_collision;
                    double _centripetal_acc;
                    double _lat_offset;
                    double _lat_comfort;
                } _cost;
            } _weight;

            double _lon_collision_cost_std = 1.0;
        } _param;

        lattice::State                        _init_state;
        Ptr<type::Vehicle>                       _vehicle;
        Ptr<STGraph>                            _st_graph;
        ReferenceLine &                   _reference_line;
        std::vector<double>                  _reference_v;
        ConstraintChecker              _constaint_checker;
        container::Heap<lattice::Combination> _candidates;
    };
}
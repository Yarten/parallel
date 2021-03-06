/**
 * @brief Lattice状态采样器
 */
#pragma once

#include "LatticeCommon.h"
#include <Planner/type/STGraph.h>
#include <Planner/type/FeasibleRegion.h>
#include <Planner/tool/PredictionQuerier.h>

namespace nox::app
{
    class LatticeSampler
    {
    public:
        LatticeSampler(
           const math::Derivative<3> & s,
           const math::Derivative<3> & l,
           Ptr<STGraph> path_time_graph,
           Ptr<PredictionQuerier> prediction_querier
        );

        using States = std::vector<lattice::State>;

        Ptr<States> SampleLatStates() const;

        Ptr<States> SampleLonStatesForCruising(double target_speed) const;

        Ptr<States> SampleLonStatesForStopping(double target_position) const;

        Ptr<States> SampleLonStatesForObstacles() const;

    private:
        struct SamplePoint
        {
            double t = 0;
            double s = 0;
            double v = 0;
        };
        using ID = scene::ID;

        std::vector<SamplePoint> QuerySTPoints() const;

        void QuerySTPointsToFollow(const ID & obstacle_id, std::vector<SamplePoint> & result) const;

        void QuerySTPointsToOvertake(const ID & obstacle_id, std::vector<SamplePoint> & result) const;

    private:
        lattice::State _init_s;
        lattice::State _init_l;
        FeasibleRegion _feasible_region;
        Ptr<STGraph> _st_graph;
        Ptr<PredictionQuerier> _prediction_querier;

        struct
        {
            double _min_response_time = 1.0;
            double _mps_resolution = 0.1;
            double _sample_longitudinal_length = 5.0;
            size_t _number_of_samples = 5;

            struct
            {
                double from_edge_to_center;
            } _vehicle;
        } _param;
    };
}
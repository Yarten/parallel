#include <utility>
#include <nox>
#include <Planner/tool/lattice/LatticeSampler.h>
#include <Planner/type/STGraph.h>
#include <Planner/PlannerConfig.h>
USING_NAMESPACE_NOX;
using namespace nox::app;


LatticeSampler::LatticeSampler(
    const nox::math::Derivative<2> &s,
    const nox::math::Derivative<2> &l,
    nox::Ptr<nox::app::STGraph> path_time_graph,
    Ptr<PredictionQuerier> prediction_querier
)
    : _init_s(s, 0), _init_l(l, 0),
      _feasible_region(s[0], s[1], s[2]),
      _st_graph(std::move(path_time_graph)),
      _prediction_querier(prediction_querier)
{
    // TODO: 读取参数
    auto & vehicle = cache::ReadEgoVehicle();
    _param._follow_reserve += vehicle.param.length.x;

    double dt = _param._min_response_time;
    auto graph_t_range = _st_graph->TRange();

    _time_samples.push_back(real::Epsilon);
    for(auto t : range(graph_t_range.Start + dt, dt, graph_t_range.End))
        _time_samples.push_back(t);
    if(_time_samples.back() != graph_t_range.End)
        _time_samples.push_back(graph_t_range.End);
}

Ptr<LatticeSampler::States> LatticeSampler::SampleLatStates() const
{
    auto end_states = New<States>();

    for(auto s : {10.0, 20.0, 40.0, 80.0})
    {
        for(auto l : {0.0, -0.5, 0.5})
        {
            lattice::State state(l, 0, 0, s);

            if(l != 0)
                state.cost_factor.lateral_offset = 5;

            end_states->emplace_back(state);
        }
    }

    return end_states;
}

Ptr<LatticeSampler::States> LatticeSampler::SampleLonStatesForCruising(double target_speed) const
{
    auto end_states = New<States>();

    static auto CreateState = [](double v, double t, double factor)
    {
        lattice::State state(0, v, 0, t);
        state.cost_factor.v_reached = factor;
        return state;
    };

    auto Sampler = [&](double t, double v_min, double v_max, double factor)
    {
        end_states->push_back(CreateState(v_min, t, factor));
        end_states->push_back(CreateState(v_max, t, factor));

        double dv = std::max
        (
            _param._mps_resolution,
            (v_max - v_min) / (_param._num_velocity_samples - 2)
        );

        for(auto v : range(v_min + dv, dv, v_max - dv))
        {
            end_states->push_back(CreateState(v, t, factor));
        }
    };

    /// 在ST图的时间维度上，按系统的反应时间进行采样
    for(auto t : _time_samples)
    {
        double v_upper = std::min(_feasible_region.VUpper(t), target_speed);
        double v_lower = _feasible_region.VLower(t);
        double v_comfort_upper = std::min(_feasible_region.ComfortVUpper(t), target_speed);
        double v_comfort_lower = _feasible_region.ComfortVLower(t);

        Sampler(t, v_comfort_lower, v_comfort_upper, 0.5);
        Sampler(t, v_lower, v_comfort_lower - _param._mps_resolution, 1.0);
        Sampler(t, v_comfort_upper + _param._mps_resolution, v_upper, 1.5);
    }

    return end_states;
}

Ptr<LatticeSampler::States> LatticeSampler::SampleLonStatesForStopping(double target_position) const
{
    auto end_states = New<States>();

    /// 在ST图的时间维度上，按系统的反应时间进行采样
    for(auto t : _time_samples)
    {
        lattice::State state(std::max(_init_s[0], target_position), 0, 0, t);
        state.cost_factor.s_travelled = 0.5;

        end_states->emplace_back(state);
    }

    return end_states;
}

Ptr<LatticeSampler::States> LatticeSampler::SampleLonStatesForObstacles() const
{
    auto sample_points = QuerySTPoints();
    auto end_states = New<States>();

    for(auto & i : sample_points)
    {
        if(i.t < _param._min_response_time)
            continue;

        if(i.s > _feasible_region.SUpper(i.t) or i.s < _feasible_region.SLower(i.t))
            continue;

        end_states->emplace_back(i.s, i.v, 0, i.t);
    }

    return end_states;
}

vector<LatticeSampler::SamplePoint> LatticeSampler::QuerySTPoints() const
{
    vector<SamplePoint> result;

    for (auto i : _st_graph->Obstacles())
    {
        const ID & id = i.first;
        QuerySTPointsToFollow(id, result);
        QuerySTPointsToOvertake(id, result);
    }

    return result;
}

void LatticeSampler::QuerySTPointsToFollow(
    const LatticeSampler::ID &obstacle_id,
    vector<LatticeSampler::SamplePoint> &result) const
{
    auto obstacle = _st_graph->GetObstacle(obstacle_id);

    for(auto & i : obstacle->trajectory)
    {
        double target_s = i.s.Start; /// 跟随模式，总跟在障碍物前边
        double v = _prediction_querier->ProjectVelocityAlongReferenceLine(
            obstacle_id, target_s, i.t
        );

        double s_upper = target_s - _param._follow_reserve;
        double s_lower = s_upper - _param._sample_longitudinal_length;
        assert(_param._number_of_samples > 2);
        double ds = _param._sample_longitudinal_length / _param._number_of_samples;

        for(auto s : range(s_lower, ds, s_upper))
        {
            result.push_back({i.t, s, v});
        }
    }
}

void LatticeSampler::QuerySTPointsToOvertake(
    const LatticeSampler::ID &obstacle_id,
    vector<LatticeSampler::SamplePoint> &result) const
{
    auto obstacle = _st_graph->GetObstacle(obstacle_id);

    for(auto & i : obstacle->trajectory)
    {
        double target_s = i.s.End + _param._overtake_reserve; /// 超车模式，总在障碍物前边
        double v = _prediction_querier->ProjectVelocityAlongReferenceLine(
            obstacle_id, target_s, i.t
        );

        result.push_back({i.t, target_s + _param._sample_longitudinal_length, v});
    }
}



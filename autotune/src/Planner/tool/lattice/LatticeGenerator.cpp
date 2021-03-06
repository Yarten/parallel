#include <Planner/tool/lattice/LatticeGenerator.h>
USING_NAMESPACE_NOX;
using namespace nox::app;


LatticeGenerator::LatticeGenerator(
    const nox::math::Derivative<3> &s,
    const nox::math::Derivative<3> &l,
    nox::Ptr<nox::app::STGraph> path_time_graph,
    Ptr<PredictionQuerier> prediction_querier
)
    : _init_lon_state(s, 0), _init_lat_state(l, 0),
      _sampler(s, l, path_time_graph, prediction_querier)
{

}

void LatticeGenerator::GenerateBundles(const ReferenceLine::Target &target, lattice::Bundle &lon, lattice::Bundle &lat) const
{
    GenerateLongitudinalBundle(target, lon);
    GenerateLateralBundle(lat);
}

void LatticeGenerator::GenerateLongitudinalBundle(const ReferenceLine::Target &target, lattice::Bundle &result) const
{
    GenerateSpeedProfilesForCruising(target.v, result);
    GenerateSpeedProfilesForObstacles(result);
    if(target.IsStop())
    {
        GenerateSpeedProfilesForStopping(target.s, result);
    }
}

void LatticeGenerator::GenerateLateralBundle(lattice::Bundle &result) const
{
    auto end_states = _sampler.SampleLatStates();
    GenerateQuinticBundle(_init_lat_state, end_states, result);
}

void LatticeGenerator::GenerateSpeedProfilesForCruising(double target_speed, lattice::Bundle &lon) const
{
    auto end_states = _sampler.SampleLonStatesForCruising(target_speed);
    if(end_states->empty())
    {
        return;
    }

    GenerateQuarticBundle(_init_lon_state, end_states, lon);
}

void LatticeGenerator::GenerateSpeedProfilesForStopping(double distance, lattice::Bundle &lon) const
{
    auto end_states = _sampler.SampleLonStatesForStopping(distance);
    if(end_states->empty())
    {
        return;
    }

    GenerateQuinticBundle(_init_lon_state, end_states, lon);
}

void LatticeGenerator::GenerateSpeedProfilesForObstacles(lattice::Bundle &lon) const
{
    auto end_states = _sampler.SampleLonStatesForObstacles();
    if(end_states->empty())
    {
        return;
    }

    GenerateQuinticBundle(_init_lon_state, end_states, lon);
}

void LatticeGenerator::GenerateQuarticBundle(
    const lattice::State &init_state,
    Ptr<LatticeGenerator::States> end_states,
    lattice::Bundle &result) const
{
    result.reserve(end_states->size());
    for(auto & end_state : *end_states)
    {
        auto lattice_curve = std::make_shared<lattice::Curve>(
            Ptr<math::Parametric<1>>(new math::QuarticCurve(
                init_state[0], init_state[1], init_state[2],
                end_state[1], end_state[2],
                end_state.t
            ))
        );

        lattice_curve->target_speed = end_state[1];
        lattice_curve->target_time = end_state.t;
        result.push_back(lattice_curve);
    }
}

void LatticeGenerator::GenerateQuinticBundle(
    const lattice::State &init_state,
    Ptr<LatticeGenerator::States> end_states,
    lattice::Bundle &result) const
{
    result.reserve(end_states->size());
    for(auto & end_state : *end_states)
    {
        auto lattice_curve = std::make_shared<lattice::Curve>(
            Ptr<math::Parametric<1>>(new math::QuinticCurve(
                init_state[0], init_state[1], init_state[2],
                end_state[0], end_state[1], end_state[2],
                end_state.t
            ))
        );

        lattice_curve->target_position = end_state[0];
        lattice_curve->target_speed = end_state[1];
        lattice_curve->target_time = end_state.t;
        result.push_back(lattice_curve);
    }
}

void LatticeGenerator::Combine(
    const ReferenceLine &reference,
    const nox::math::Parametric<1> &lon,
    const nox::math::Parametric<1> &lat,
    nox::type::Trajectory &result) const
{
    double s0 = lon.Calculate(0, 0);
    double s_max = reference.path->Back().s;
    double s_sum = 0;
    double last_s = -Real::Epsilon;

    result.Clear();

    for(double t : range(0, _param._time_resolution, _param._planning_temporal_length))
    {
        math::Derivative<3> s, l;
        s[0] = lon.Calculate(0, t);

        if(last_s > 0)
            s[0] = std::max(last_s, s[0]);
        last_s = s[0];

        if(s[0] > s_sum) break;

        s[1] = std::max(Real::Epsilon, lon.Calculate(1, t));
        s[2] = lon.Calculate(2, t);

        double ds = s[0] - s0;
        l[0] = lat.Calculate(0, ds);
        l[1] = lat.Calculate(1, ds);
        l[2] = lat.Calculate(2, ds);

        auto nearest_index = reference.path->QueryNearestByDistance(s[0]);
        auto nearest_point = reference.path->at(nearest_index);

        TrajectoryPoint point;
        math::Cartesian original_point;

        math::Frenet2Cartesian(
            math::Cartesian(nearest_point.pose.x, nearest_point.pose.y, nearest_point.pose.theta),
            nearest_point.s, nearest_point.kappa, nearest_point.dkappa,
            s, l,
            original_point,
            point.kappa,
            point.v,
            point.a
        );

        point.pose.x = original_point.x;
        point.pose.y = original_point.y;
        point.pose.theta = original_point.theta;

        result.Add(point);
    }
}



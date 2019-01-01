#include <Tracking/component/PCPID.h>
#include "../../../../.param/template/Parameter.h"

USING_NAMESPACE_NOX;

namespace nox::app
{

    void PCPID::Initialize()
    {
        _param._pcpid = cache::ReadPCPIDParameter();
        _param._vehicle = cache::ReadVehicleParameter();
    }

    double PCPID::Calculate(const type::Trajectory &path, const type::Vehicle &vehicle)
    {
        const auto matched_point = path.PointAtPosition(vehicle.pose.t);
        const double vx = vehicle.v.x;
        const double vy = vehicle.v.y;
        const double w  = vehicle.w.z;
        const double kappa = matched_point.kappa;
        const double aError = Radian(vehicle.pose.theta - matched_point.pose.theta).Warp(Angle::Radian);

        double rear_dError = vehicle.pose.t.DistanceTo(matched_point.pose.t) *
            math::PointOnLine(vehicle.pose.x, vehicle.pose.y, matched_point.pose.x, matched_point.pose.y, matched_point.pose.theta);
        double center_dError = rear_dError + _param._vehicle.Physical.Lb * std::sin(aError);
        double dError;
        if(abs(rear_dError) < abs(center_dError))
            dError = rear_dError;
        else
            dError = center_dError;

        const double ff = FeedForward(vx, kappa);
        const double fb = FeedBack(aError, dError);
        const double in = Integral(dError * vx * 0.05 * std::cos(aError));
        const double dp = Damping(vx, vy, w, kappa, aError);

        double Kff, Kfb, Kin, Kdp;
        PickPID(vx, Kff, Kfb, Kin, Kdp);

        const double sff = Kff * ff;
        const double sfb = Kfb * fb;
        const double sin = Kin * in;
        const double sdp = Kdp * dp;
        const double result = sff + sfb + sin + sdp;

        Logger::I("PCPID").Print(R"(
--------------------------------------------------------------------
[Input ]| %10s | %10s | %10s | %10s | %10s | %10s |
        | %10.6lf | %10.6lf | %10.6lf | %10.6lf | %10.6lf | %10.6lf |
--------------------------------------------------------------------
[ Item ]| %10s | %10s | %10s | %10s |
 weight | %10.6lf | %10.6lf | %10.6lf | %10.6lf |
original| %10.6lf | %10.6lf | %10.6lf | %10.6lf |
 in deg | %10.6lf | %10.6lf | %10.6lf | %10.6lf |
   sum  | %10.6lf |
--------------------------------------------------------------------
)",
"vx", "vy", "w", "aError/deg", "dError", "kappa",
vx, vy, w, aError * 180.0 / M_PI, dError, kappa,
"FF", "FB", "IN", "DP",
Kff, Kfb, Kin, Kdp,
ff, fb, in, dp,
ff * 180.0 / M_PI, fb * 180.0 / M_PI, in * 180.0 / M_PI, dp * 180.0 / M_PI,
result
);

        return result;
    }

    double PCPID::FeedForward(double v, double curvature)
    {
        double L  = _param._vehicle.Physical.WheelBase;
        double g  = 9.8;
        double Cf = _param._vehicle.Physical.Cornering.Front;
        double Cr = _param._vehicle.Physical.Cornering.Rear;
        double la = _param._vehicle.Physical.La;
        double lb = _param._vehicle.Physical.Lb;
        double m  = _param._vehicle.Physical.Weight;

        double Wf = lb / L * m * g;
        double Wr = la / L * m * g;
        double Kug = Wf / Cf - Wr / Cr;
        double heading = (L + Kug * v * v / g) * curvature;

        return heading;
    }

    double PCPID::FeedBack(double aError, double dError)
    {
        double ela = dError + (_param._pcpid.xla + _param._vehicle.Physical.La)* std::sin(aError);
        double heading = -2 * _param._pcpid.Kp / _param._vehicle.Physical.Cornering.Front * ela;

        return heading;
    }

    double PCPID::Integral(double e)
    {
        _integral = _integral + e;
        return -_integral;
    }

    void PCPID::PickPID(double v, double & Kff, double & Kfb, double & Kin, double & Kdp)
    {
        v *= 3.6;
        auto & vv = _param._pcpid.Kv;
        size_t index = math::Extremum(vv.begin(), vv.end(), [&](const double & lhs, const double & rhs)
        {
            return std::abs(lhs - v) < std::abs(rhs - v);
        });

        auto & vff = _param._pcpid.Kff;
        auto & vfb = _param._pcpid.Kfb;
        auto & vin = _param._pcpid.Kin;
        auto & vdp = _param._pcpid.Kdp;

        Kff = vff.empty() ? 0 : vff[std::min(index, vff.size() - 1)];
        Kfb = vfb.empty() ? 0 : vfb[std::min(index, vfb.size() - 1)];
        Kin = vin.empty() ? 0 : vin[std::min(index, vin.size() - 1)];
        Kdp = vdp.empty() ? 0 : vdp[std::min(index, vdp.size() - 1)];
    }

    double PCPID::Damping(double vx, double vy, double w, double curvature, double aError)
    {
        double heading = w - vx * curvature  * (
            std::cos(aError) - std::tan(vy / (vx + real::Epsilon)) * std::sin(aError)
        );
        heading *= _param._pcpid.Ky;
        return heading;
    }


}

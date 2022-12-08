#pragma once
#include <math/Spatial.h>
namespace common::math{

class DeadReckoning
{
public:
    enum class Type
    {
        //f = fixed rate, P = position, R = rotation
        FPW, ///< linear interpolation of position based on velocity
        FVW, ///< linear interpolation of position based on acceleration and velocity
        RPW, ///< linear interpolation of position like FPW + rotation based on angular speed
        RVW, ///< linear interpolation of position like FVW + rotation based on angular speed

    };

    static Spatial extrapolate(const Spatial& s, std::chrono::milliseconds delta_t, Type type = Type::FPW);

protected:
    static Spatial extrapolateFPW(const Dynamic& s, std::chrono::milliseconds delta_t);

    static Spatial extrapolateFVW(const Kinematic& s, std::chrono::milliseconds delta_t);

    static Spatial extrapolateRVW(const Kinematic& s, std::chrono::milliseconds delta_t);

    static Spatial extrapolateRPW(const Kinematic& s, std::chrono::milliseconds delta_t);
};

}
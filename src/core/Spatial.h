#pragma once

#include <chrono>

#include <glog/logging.h>
#include <gmtl/gmtl.h>

namespace msge{
	
/**
 * representation of spatial information on an entity
 */
class Spatial 
{
public:
	gmtl::Vec3d position;
    gmtl::Quatd orientation;
};

/**
 * First order derivate of a {@code Spatial}.
 */
class Dynamic : public Spatial
{
    void        derive(Spatial prev, Spatial current, std::chrono::seconds);
    gmtl::Vec3d velocity;
    gmtl::Vec3d rot_velocity;
};

/**
 * Second order derivate of a {@code Spatial}.
 */
class Kinematic : public Dynamic
{
    void        derive(Dynamic prev, Dynamic current, std::chrono::seconds);
    gmtl::Vec3d acceleration;
    gmtl::Vec3d rot_acceleration;
};


} //namespace msge

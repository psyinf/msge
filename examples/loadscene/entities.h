#pragma once
#include <math/Spatial.h>
#include <math/DeadReckoning.h>

#include <FrameStamp.h>
#include <entities/DynamicEntity.h>
#include <entities/DynamicCompoundEntity.h>

class SceneObject
{
public:
    virtual ~SceneObject() = default;

protected:
    virtual void frame(const msge::FrameStamp& fs) = 0;

    void reflectAtBounds(common::math::Dynamic& spatial) const
    {
        const auto   dim = 10.0f;
        gmtl::AABoxd box(gmtl::Vec3d{-dim, -dim, -dim}, {dim, dim, dim});

        auto& velocity = spatial.velocity;
        auto& trans    = spatial.position;
        for (auto i : {0, 1, 2})
        {
            if (trans[i] > box.mMax[i])
            {
                trans[i]    = box.mMax[i];
                velocity[i] = -velocity[i];
            }
            else if (trans[i] < box.mMin[i])
            {
                trans[i]    = box.mMin[i];
                velocity[i] = -velocity[i];
            }
        }
    }
};
/*Very simple dynamic entity*/
class Mover : public msge::DynamicEntity
    , public SceneObject
{
    Mover(Mover&) = delete;


public:
    using DynamicEntity::DynamicEntity;
    // move along some simple path
    void frame(const msge::FrameStamp& fs) override
    {
        spatial.position += spatial.velocity * common::math::DeadReckoning::toSeconds(fs.frameTime);
        reflectAtBounds(spatial);
    }
};

class CompoundMover : public msge::DynamicCompoundEntity
    , public SceneObject
{
public:
    using DynamicCompoundEntity::DynamicCompoundEntity;
    // move along some simple path
    void frame(const msge::FrameStamp& fs) override
    {
        spatial.position += spatial.velocity * common::math::DeadReckoning::toSeconds(fs.frameTime);
        reflectAtBounds(spatial);
    }
};


#pragma once
#include <BaseEntityVisitor.h>
#include <CoreDefinitions.h>
#include <FrameStamp.h>
#include <Spatial.h>
#include <array>


namespace msge
{

/**
 * Base for entities. No spatial properties
 */
class BaseEntity
{
public:
    explicit BaseEntity(const EntityId& id)
        : id{id}
    {
    }

    virtual void accept(BaseEntityVisitor& bev)
    {
        bev.visit(*this);
    }
    virtual void traverse(BaseEntityVisitor& bev)
    {
        //implement for grouping entities
    }

    virtual ~BaseEntity() = default;

    BaseEntity() = default;

    const EntityId id;
};
} // namespace msge
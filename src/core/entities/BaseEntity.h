#pragma once
#include <visitors/BaseEntityVisitor.h>
#include <CoreDefinitions.h>
#include <FrameStamp.h>
#include <math/Spatial.h>
#include <array>


namespace msge
{

/**
 * Base for entities. No spatial properties. 
 * #TODO maybe make virtual base class.
 */
class BaseEntity
{
public:
    explicit BaseEntity(const EntityId& id, const TypeId& type)
        : id{id}
        , type{type}
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
    const TypeId   type;
};
} // namespace msge
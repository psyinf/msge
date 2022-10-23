#pragma once
#include <Spatial.h>
#include <BaseEntityVisitor.h>
#include <CoreDefinitions.h>
#include <FrameStamp.h>
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
	{}

	virtual void accept(BaseEntityVisitor& bev)
    {
        bev.visit(*this);
    }

    virtual ~BaseEntity() = default;

	BaseEntity() = default;

    const EntityId id;
};
}
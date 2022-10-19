#pragma once
#include <Spatial.h>
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

	BaseEntity() = default;

    const EntityId id;
};
}
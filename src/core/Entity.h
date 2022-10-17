#pragma once
#include <Spatial.h>

#include <array>
#include "FrameStamp.h"

namespace msge
{
using EntityId = std::array<char, 64>;



class Entity
{
public:
	explicit Entity(const EntityId& id)
        : id{id}
	{}

	virtual ~Entity() = default;

    virtual void   frame(const FrameStamp& );
	const EntityId id;

	Spatial spatial;
};


}
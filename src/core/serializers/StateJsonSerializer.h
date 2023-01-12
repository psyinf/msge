#pragma once
#include <entities/BaseEntity.h>
#include <nlohmann/json.hpp>

namespace msge
{

inline void to_json(nlohmann::json& j, const EntityState& s)
{
}

inline void from_json(const nlohmann::json& j, EntityState& s)
{
}

} // namespace msge
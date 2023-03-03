#pragma once
#include <entities/EntityState.h>
#include <nlohmann/json.hpp>
#include <entities/BaseEntity.h>
namespace msge
{

inline void to_json(nlohmann::json& j, const BaseEntity& s)
{
}

inline void from_json(const nlohmann::json& j, BaseEntity& s)
{
}

} // namespace msge
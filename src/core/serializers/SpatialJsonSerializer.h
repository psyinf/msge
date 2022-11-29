#pragma once
#include <serializers/GmtlJsonSerializer.h>
#include <Spatial.h>
namespace msge
{

inline void to_json(nlohmann::json& j, const Spatial& s)
{
    j = nlohmann::json{{"pos", s.position}, {"rot", s.orientation}};
}

inline void from_json(const nlohmann::json& j, Spatial& s)
{
    j.at("pos").get_to(s.position);
    j.at("rot").get_to(s.orientation);
}

} // namespace msge
#include "JsonSerializer.h"

#include <Core.h>
#include <nlohmann/json.hpp>
#include <serializers/SpatialJsonSerializer.h>
#include <serializers/GmtlJsonSerializer.h>
#include <stack>
#include <vector>


using namespace msge;
using namespace nlohmann;

EntitySerializationBuffer convert(const nlohmann::json& json, const std::string& id)
{
    auto c_s = json.dump();

    uint8_t* u = std::bit_cast<uint8_t*>(c_s.data());
    auto     v = std::vector<uint8_t>(u, u + c_s.size());

    return {id, v};
}
std::string buildPath(const plugin::JsonSerializer::IdStack& ids, const EntityId& currentId)
{
    std::string res;
    for (const auto& id : ids)
    {
        res = res.append(std::string(id.data())).append(".");
    }
    return res.append(std::string(currentId.data()));
}

void plugin::JsonSerializer::traverse(BaseEntity& e)
{
    idStack.push_back(e.id);
    e.traverse(*this);
    idStack.pop_back();
}

void plugin::JsonSerializer::visit(CompoundEntity& entity)
{
    nlohmann::json c;
    c["id"]      = entity.id;
    c["spatial"] = entity.spatial;

    getSink()(convert(c, buildPath(idStack, entity.id)));
    traverse(entity);
}

void plugin::JsonSerializer::visit(StaticEntity& entity)
{
    nlohmann::json c;
    c["id"]      = entity.id;
    c["spatial"] = entity.spatial;

    getSink()(convert(c, buildPath(idStack, entity.id)));
}

void plugin::JsonSerializer::visit(BaseEntity& entity)
{
    nlohmann::json c;
    c["id"] = entity.id;

    getSink()(convert(c, buildPath(idStack, entity.id)));
}

plugin::JsonSerializer::JsonSerializer(Core& core)
    : CoreEntityVisitor(core)
{
}

void plugin::JsonSerializer::finish()
{
}

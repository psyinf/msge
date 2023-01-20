#include "JsonStateSerializer.h"

#include <Core.h>
#include <CoreDefinitions.h>
#include <nlohmann/json.hpp>
#include <serializers/SpatialJsonSerializer.h>
#include <serializers/GmtlJsonSerializer.h>
#include <serializers/StateJsonSerializer.h>

#include <entities/BaseEntity.h>
#include <entities/DynamicCompoundEntity.h>
#include <entities/StaticEntity.h>
#include <entities/DynamicEntity.h>

#include <stack>
#include <vector>


using namespace msge;
using namespace nlohmann;
void serializeBase(nlohmann::json& c, const BaseEntity& entity)
{
    c["id"]   = entity.id;
    c["type"] = entity.type;
    c["state"] = *entity.entityState;
}

EntitySerializationBuffer convert(const nlohmann::json& json, const std::string& id)
{
    auto c_s = json.dump();

    uint8_t* u = std::bit_cast<uint8_t*>(c_s.data());
    auto     v = std::vector<uint8_t>(u, u + c_s.size());

    return {id, v};
}
std::string buildPath(const plugin::JsonStateSerializer::IdStack& ids, const EntityId& currentId)
{
    std::string res;
    for (const auto& id : ids)
    {
        res = res.append(std::string(id.data())).append(".");
    }
    return res.append(std::string(currentId.data()));
}

void plugin::JsonStateSerializer::traverse(BaseEntity& e)
{
    idStack.push_back(e.id);
    e.traverse(*this);
    idStack.pop_back();
}

void plugin::JsonStateSerializer::visit(DynamicCompoundEntity& entity)
{
    nlohmann::json c;
    serializeBase(c, entity);
    
    c["spatial"] = entity.spatial;

    getSink()(convert(c, buildPath(idStack, entity.id)));
    traverse(entity);
}

void plugin::JsonStateSerializer::visit(StaticEntity& entity)
{
    nlohmann::json c;
    serializeBase(c, entity);
    c["spatial"] = entity.spatial;

    getSink()(convert(c, buildPath(idStack, entity.id)));
}

void plugin::JsonStateSerializer::visit(DynamicEntity& entity)
{
    nlohmann::json c;
    serializeBase(c, entity);
    c["spatial"] = entity.spatial;

    getSink()(convert(c, buildPath(idStack, entity.id)));
}

void plugin::JsonStateSerializer::visit(BaseEntity& entity)
{
    nlohmann::json c;
    serializeBase(c, entity);

    getSink()(convert(c, buildPath(idStack, entity.id)));
}

plugin::JsonStateSerializer::JsonStateSerializer(Core& core)
    : CoreEntityVisitor(core)
{
}

void plugin::JsonStateSerializer::finish()
{
}



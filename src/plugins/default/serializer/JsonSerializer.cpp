#include "JsonSerializer.h"
#include <Core.h>
#include <serializers/gmtlJsonSerializer.h>
#include <serializers/SpatialJsonSerializer.h>

#include <nlohmann/json.hpp>
#include <stack>
#include <vector>


using namespace msge;
using namespace nlohmann;

EntitySerializationBuffer convert(nlohmann::json&& json, const EntityId& id)
{
    auto c_s = json.dump();

    uint8_t* u = std::bit_cast<uint8_t*>(c_s.data());
    auto     v = std::vector<uint8_t>(u, u + c_s.size());
    return {id, v};
}

void plugin::JsonSerializer::traverse(BaseEntity& e)
{
    idStack.push(e.id);
    e.traverse(*this);
    idStack.pop();
}

void plugin::JsonSerializer::visit(CompoundEntity& entity)
{
    nlohmann::json c;
    c["id"] = entity.id;
    c["spatial"] = entity.spatial;
    
    sink(convert(std::move(c),entity.id));
    traverse(entity);

}

void plugin::JsonSerializer::visit(StaticEntity& entity)
{
    nlohmann::json c;
    c["id"]        = entity.id;
    c["spatial"] = entity.spatial;

    sink(convert(std::move(c), entity.id));
}

void plugin::JsonSerializer::visit(BaseEntity& entity)
{
    nlohmann::json c;
    c["id"]        = entity.id;
   

    sink(convert(std::move(c), entity.id));
}

plugin::JsonSerializer::JsonSerializer(Core& core)
    : CoreEntityVisitor(core)
{
    
}

void plugin::JsonSerializer::finish()
{
   
}

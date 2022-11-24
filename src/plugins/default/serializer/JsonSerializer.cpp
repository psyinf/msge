#include "JsonSerializer.h"
#include <Core.h>

#include <nlohmann/json.hpp>
#include <stack>

using namespace msge;
using namespace nlohmann;

auto child_field = "sub";

class JsonSink
{
public:
    JsonSink() {
        json scene_root;
        scene_root["id"] = "scene_root";
        scene_root[child_field] = json::array();
        objects.push(scene_root);
    }
    void add(const nlohmann::json& t)
    {
        objects.top().at(child_field).push_back(t);
    }
    void push() {
        //we borrow the last element in the children 
        auto borrowed = std::move(objects.top().at(child_field).back());
        objects.push(std::move(borrowed));
    }
    void pop()
    {
        auto borrowed = std::move(objects.top());
        objects.pop();
        objects.top().at(child_field).back() = std::move(borrowed);
    }
    std::stack<nlohmann::json> objects;
    

    void write() {
        std::ofstream f{"out.bin"};
        f << objects.top();
    }
};
JsonSink js;

void plugin::JsonSerializer::traverse(BaseEntity& e)
{
    js.push();
    e.traverse(*this);
    js.pop();
}

void plugin::JsonSerializer::visit(CompoundEntity& entity)
{
    nlohmann::json ejson;

   
    ejson["id"] = std::string_view(entity.id);
    ejson[child_field] = json::array();
    js.add(ejson);
    traverse(entity);

}

void plugin::JsonSerializer::visit(StaticEntity& entity)
{
    nlohmann::json ejson;
    ejson["id"] = std::string_view(entity.id);
    js.add(ejson);
}

void plugin::JsonSerializer::visit(BaseEntity& entity)
{
    nlohmann::json ejson;
    ejson["id"] = std::string_view(entity.id);
    js.add(ejson);
}

plugin::JsonSerializer::JsonSerializer(Core& core)
    : CoreEntityVisitor(core)
{
    
}

void plugin::JsonSerializer::finish()
{
    js.write();
}

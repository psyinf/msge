#include "JsonEntitySerializer.h"
#include <entities/BaseEntity.h>
#include <entities/DynamicEntity.h>
#include <entities/DynamicCompoundEntity.h>
#include <entities/StaticEntity.h>

using namespace msge;

void JsonEntityVisitor::traverse(BaseEntity& e)
{
}

void JsonEntityVisitor::visit(DynamicEntity& entity)
{
    json["spatial"] = entity.spatial;
    visit(static_cast<BaseEntity&>(entity));
}

void JsonEntityVisitor::visit(DynamicCompoundEntity& entity)
{
    json["spatial"] = entity.spatial;
    visit(static_cast<BaseEntity&>(entity));
}

void JsonEntityVisitor::visit(StaticEntity& entity)
{
    json["spatial"] = entity.spatial;
    visit(static_cast<BaseEntity&>(entity));
}

void JsonEntityVisitor::visit(BaseEntity& entity)
{
    json["state"] = *entity.entityState;
}

JsonEntityVisitor::JsonEntityVisitor(JsonType& jt)
    : json(jt)
{
}

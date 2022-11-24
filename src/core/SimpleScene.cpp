#include "SimpleScene.h"
#include "BaseEntityVisitor.h"
#include <BaseEntity.h>


#include <algorithm>
#include <ranges>
using namespace msge;

void SimpleScene::addEntity(std::shared_ptr<BaseEntity> entity)
{
    if (hasEntity(entity->id))
    {
        throw std::invalid_argument(fmt::format("Entity '{}' already in scene", entity->id));
    }
    entities.push_back(entity);
}

bool SimpleScene::hasEntity(const EntityId& entityId)
{
    return entities.end() !=  std::ranges::find_if(entities, [&entityId](const auto e) {return  e->id == entityId; });
}

void SimpleScene::runVisitor(BaseEntityVisitor& visitor)
{
   std::ranges::for_each(entities, [&visitor](const auto& e) { e->accept(visitor); });
    visitor.finish();
}

#include "SimpleScene.h"
#include <BaseEntity.h>
#include <algorithm>
#include <ranges>
using namespace msge;

void SimpleScene::addEntity(std::shared_ptr<BaseEntity> entity)
{
    if (hasEntity(entity->id))
    {
        throw std::invalid_argument(std::format("Entity '{}' already in scene", entity->id));
    }
    entities.push_back(entity);
}

bool SimpleScene::hasEntity(const EntityId& entityId)
{
    return entities.end() !=  std::ranges::find_if(entities, [&entityId](const auto e) {return  e->id == entityId; });
}

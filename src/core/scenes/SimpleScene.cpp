#include <algorithm>
#include <entities/BaseEntity.h>
#include <ranges>
#include <scenes/SimpleScene.h>
#include <visitors/BaseEntityVisitor.h>
#include <visitors/FindEntityVisitor.h>
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
    return entities.end() != std::ranges::find_if(entities, [&entityId](const auto e) { return e->id == entityId; });
}

void SimpleScene::runVisitor(
    BaseEntityVisitor& visitor, const std::function<bool(BaseEntityVisitor&)>& callback)
{
    std::ranges::for_each(entities, [&visitor, &callback](auto& e) { e->accept(visitor); if(callback) {callback(visitor);} });
}

std::optional<std::reference_wrapper<msge::BaseEntity>> SimpleScene::findEntity(std::string_view path)
{
    std::optional<std::reference_wrapper<msge::BaseEntity>> b = {};

    FindEntityVisitor f(path);
    runVisitor(f, [&b](const auto& v) {
        
        if (auto res = dynamic_cast<const FindEntityVisitor&>(v).getResult(); res.has_value())
        {
            b = std::move(res);
            return true;
        }
        return false;
    });
    return b;
}

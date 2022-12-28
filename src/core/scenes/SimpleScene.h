#pragma once
#include <scenes/BaseScene.h>
#include <vector>

namespace msge
{
class SimpleScene : public BaseScene
{

public:
    using BaseScene::BaseScene;


    void addEntity(std::shared_ptr<BaseEntity>) override;

    bool hasEntity(const EntityId& entityId) override;


    void runVisitor(
        BaseEntityVisitor& visitor, const std::function<bool(BaseEntityVisitor&)>& callback = []([[maybe_unused]] const auto& v) { return true; }) override;


    std::optional<std::reference_wrapper<BaseEntity>> findEntity(std::string_view) override;

private:
    std::vector<std::shared_ptr<BaseEntity>> entities;
};
} // namespace msge
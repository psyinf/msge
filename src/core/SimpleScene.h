#pragma once
#include <BaseScene.h>
#include <vector>

namespace msge
{
class SimpleScene : public BaseScene
{

public:
    explicit SimpleScene(const SceneId& sceneId)
        : BaseScene(sceneId)
    {
    }


    void addEntity(std::shared_ptr<BaseEntity>) override;

    bool hasEntity(const EntityId& entityId) override;


    void runVisitor(BaseEntityVisitor& visitor) override;

private:
    std::vector<std::shared_ptr<BaseEntity>> entities;
};
} // namespace msge
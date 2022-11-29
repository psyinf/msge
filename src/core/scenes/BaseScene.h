#pragma once
#include <CoreDefinitions.h>

#include <memory>
#include <string>


namespace msge
{
class BaseEntity;
class BaseEntityVisitor;

//collection of Entities 
class BaseScene
{
public:
    explicit BaseScene(const SceneId& id) 
        : sceneId(id)
    {}
    virtual ~BaseScene() = default;
    
    virtual void addEntity(std::shared_ptr<BaseEntity>) = 0;
    
    virtual bool hasEntity(const EntityId& entityId) = 0;

    virtual void runVisitor(BaseEntityVisitor& visitor) = 0;

    const SceneId& getSceneId() const
    {
        return sceneId;
    }

private:
    const SceneId sceneId;
};

} // namespace msge
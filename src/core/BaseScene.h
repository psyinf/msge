#pragma once
#include <CoreDefinitions.h>

#include <memory>
#include <string>


namespace msge
{
class BaseEntity;

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

    const SceneId& getSceneId() const
    {
        return sceneId;
    }

private:
    const SceneId sceneId;
};

} // namespace msge
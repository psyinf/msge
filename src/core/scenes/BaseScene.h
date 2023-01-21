#pragma once
#include <CoreDefinitions.h>

#include <memory>
#include <functional>
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

    virtual void runVisitor(
        BaseEntityVisitor& visitor, const std::function<bool(BaseEntityVisitor&)>& callback = []([[maybe_unused]] const auto& v) { return true; }) = 0;
    
    virtual std::optional<std::reference_wrapper<BaseEntity>> findEntity(std::string_view) = 0;
    
    template <typename T>
    std::optional<std::reference_wrapper<T>> findEntity(std::string_view path)
    {
        auto found = findEntity(path);
        return  std::reference_wrapper<T>(dynamic_cast<T&>(found->get()));
    };
    

    const SceneId& getSceneId() const
    {
        return sceneId;
    }

private:
    const SceneId sceneId;
};

} // namespace msge
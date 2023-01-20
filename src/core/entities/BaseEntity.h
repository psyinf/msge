#pragma once
#include <CoreDefinitions.h>
#include <FrameStamp.h>
#include <array>
#include <math/Spatial.h>
#include <serializers/StateJsonSerializer.h>
#include <visitors/BaseEntityVisitor.h>


namespace msge
{
template <class T>
class VisitorInterface
{
public:
    ~VisitorInterface() = default;

    virtual void accept(T& bev) = 0;

    virtual void traverse(T& bev) = 0;
};



class BaseEntity : public VisitorInterface<BaseEntityVisitor>
{
public:
    explicit BaseEntity(const EntityId& id, const TypeId& type)
        : id{id}
        , type{type}
    {
    }

    void accept(BaseEntityVisitor& bev) override
    {
        bev.visit(*this);
    }

    void traverse(BaseEntityVisitor& bev) override
    {
    }

    virtual void load(const JsonType& json)
    {
        *entityState = json["state"];
    }

    virtual void save(JsonType& json) const
    {
        json["state"] = *entityState;
    }

    virtual ~BaseEntity() = default;

    BaseEntity() = default;

    std::shared_ptr<EntityState> entityState;
    const EntityId               id;
    const TypeId                 type;
};
} // namespace msge
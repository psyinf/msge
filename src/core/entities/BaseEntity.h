#pragma once
#include <CoreDefinitions.h>
#include <FrameStamp.h>
#include <array>
#include <math/Spatial.h>
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

class EntityState
{

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

    virtual ~BaseEntity() = default;

    BaseEntity() = default;

    std::shared_ptr<EntityState>    entityState;
    const EntityId id;
    const TypeId   type;
};
} // namespace msge
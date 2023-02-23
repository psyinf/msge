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
    /*
    Implement to accept the Visitor
    */
    virtual void accept(T& bev) = 0;
    /*
    Implement to traverse potential children
    */
    virtual void traverse(T& bev) = 0;
};
/**
 * Interface to have a tagged Type
 */
class TaggedType
{
    virtual TypeId getTaggedType() const = 0;
};


class BaseEntity : public VisitorInterface<BaseEntityVisitor>, public TaggedType
{
public:
    explicit BaseEntity(const EntityId& id)
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
        //to be implemented for structured entities
    }

    virtual void load(const JsonType& json)
    {
        *entityState = json["state"];
    }

    virtual void save(JsonType& json) const
    {
        json["state"] = *entityState;
        json["type"]  = type;
        json["tag"]   = getTaggedType();
    }
    

    TypeId getTaggedType() const override { return "Base"; }

    virtual ~BaseEntity() = default;

    BaseEntity() = default;

    std::shared_ptr<EntityState> entityState;
    const EntityId               id;
    const TypeId                 type;
    
};
} // namespace msge
#pragma once
#include <entities/BaseEntity.h>
#include <serializers/SpatialJsonSerializer.h>
namespace msge
{
/**
 * Entity that is supposed not to move (e.g. a house or a tree)
 */
class StaticEntity : public BaseEntity
{
public:
    using BaseEntity::BaseEntity;
   
    void accept(BaseEntityVisitor& bev) final {
        bev.visit(*this);
    }

    common::math::Spatial spatial;

    void load(const JsonType& json) override
    {
        BaseEntity::load(json);
        spatial = json["spatial"];
    }

    void save(JsonType& json) const override
    {
        BaseEntity::save(json);
        json["spatial"] = spatial;
    }

   
};
} // namespace msge

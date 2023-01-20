#pragma once
#include <entities/BaseEntity.h>
#include <serializers/SpatialJsonSerializer.h>
namespace msge
{
/**
 * Entity that can move
 */
class DynamicEntity : public BaseEntity
{
public:
    using BaseEntity::BaseEntity;

    void accept(BaseEntityVisitor& bev) final
    {
        bev.visit(*this);
    }

    common::math::Dynamic spatial;

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

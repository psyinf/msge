#pragma once
#include <entities/BaseEntity.h>

namespace msge
{
/**
 * Entity that can move
 */
class DynamicEntity : public BaseEntity
{
public:
    using BaseEntity::BaseEntity;
   
    void accept(BaseEntityVisitor& bev) final {
        bev.visit(*this);
    }

    common::math::Dynamic spatial;
};
} // namespace msge

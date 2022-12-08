#pragma once
#include <entities/BaseEntity.h>

namespace msge
{
/**
 * Entity that is supposed not to move (e.g. a house or a tree)
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

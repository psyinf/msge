#pragma once
#include <BaseEntity.h>

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

    Spatial spatial;
};
} // namespace msge

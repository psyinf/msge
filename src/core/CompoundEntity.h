#pragma once
#include <BaseEntity.h>
#include <BaseEntityVisitor.h>

namespace msge
{
class BaseEntity;

/**
 * Compound of entities. The spatial is the base for all children. I.e. their spatial is considered relative to the base
 */
class CompoundEntity : public BaseEntity
{

public:
    using BaseEntity::BaseEntity;

    void accept(BaseEntityVisitor& bev) override
    {
        bev.visit(*this);
    }
    void traverse(BaseEntityVisitor& bev) override
    {
        std::ranges::for_each(children, [&bev](auto& c) { c->accept(bev); });
    }

    void addChildren(const std::shared_ptr<BaseEntity>& c)
    {
        children.emplace_back(c);
    }


private:
    std::vector<std::shared_ptr<BaseEntity>> children;
};

} // namespace msge
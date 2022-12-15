#pragma once
#include <entities/BaseEntity.h>
#include <math/Spatial.h>
#include <ranges>
#include <visitors/BaseEntityVisitor.h>
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
    /*
    FIXME: emplace_back should accept ellipse
    */
    void addChildren(std::convertible_to<std::shared_ptr<BaseEntity>> auto&&... s)
    {
        for (const auto& v : std::initializer_list<std::shared_ptr<BaseEntity>>{s...})
        {
            children.emplace_back(v);
        }
    }

    common::math::Spatial spatial;


private:
    std::vector<std::shared_ptr<BaseEntity>> children;
};

} // namespace msge
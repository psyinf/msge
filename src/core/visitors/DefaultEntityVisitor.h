#pragma once
#include <entities/DynamicCompoundEntity.h>
#include <entities/BaseEntity.h>
#include <entities/DynamicEntity.h>
#include <entities/StaticEntity.h>
#include <visitors/BaseEntityVisitor.h>

namespace msge
{

class DefaultEntityVisitor : public BaseEntityVisitor
{
public:

    void visit(BaseEntity&) override {

    }
    void visit(StaticEntity& entity) override
    {
        visit(static_cast<BaseEntity&>(entity));
    }
    void visit(DynamicCompoundEntity& entity) override
    {
        visit(static_cast<BaseEntity&>(entity));
    }
    void visit(DynamicEntity& entity) override
    {
        visit(static_cast<BaseEntity&>(entity));
    }
};


} // namespace msge
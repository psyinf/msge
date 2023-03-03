#pragma once
#include <entities/BaseEntity.h>
#include <entities/DynamicCompoundEntity.h>
#include <entities/DynamicEntity.h>
#include <entities/StaticEntity.h>
#include <visitors/BaseEntityVisitor.h>

namespace msge
{
/*
   Visitor that delegates to the BaseEntity visit function per default. Traversal of CompoundEntites is performed too.
*/

class DefaultEntityVisitor : public BaseEntityVisitor
{
public:
    using BaseEntityVisitor::visit;
    
    void visit(StaticEntity& entity) override
    {
        visit(static_cast<BaseEntity&>(entity));
    }
    void visit(DynamicCompoundEntity& entity) override
    {
        visit(static_cast<BaseEntity&>(entity));
        traverse(entity);
    }
    void visit(DynamicEntity& entity) override
    {
        visit(static_cast<BaseEntity&>(entity));
    }
};


} // namespace msge
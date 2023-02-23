#pragma once
#include <visitors/DefaultEntityVisitor.h>
#include <visitors/QualifiedNameStack.h>

namespace msge
{
// TBD, WIP
class DelegateEntitiesVisitor : public DefaultEntityVisitor
{
    std::shared_ptr<BaseEntityVisitor> delegate;
    QualifiedNameStack                 nameStack;

public:
    void visit(BaseEntity& entity) override
    {
        nameStack.push(entity);
        delegate->visit(entity);
        nameStack.pop();
    }

    void visit(msge::DynamicCompoundEntity& entity) override
    {
        nameStack.push(entity);
        delegate->visit(entity);
        traverse(entity);
        nameStack.pop();
    }

    void setDelegate(std::shared_ptr<BaseEntityVisitor> visitor_delegate)
    {
        delegate = visitor_delegate;
    }
};

} // namespace msge
#pragma once
#include <visitors/DefaultEntityVisitor.h>
#include <visitors/QualifiedNameStack.h>

namespace msge
{

class CollectSceneEntitiesVisitor : public DefaultEntityVisitor
{
    std::map<std::string, std::reference_wrapper<BaseEntity>, std::less<>> collected;
    QualifiedNameStack                                        nameStack;

public:
    void visit(msge::BaseEntity& entity) override
    {
        nameStack.push(entity);
        collected.insert_or_assign(nameStack.getQualifiedName(), entity);
        nameStack.pop();
    }

    void visit(msge::DynamicCompoundEntity& entity) override
    {
        nameStack.push(entity);
        collected.insert_or_assign(nameStack.getQualifiedName(), entity);
        traverse(entity);
        nameStack.pop();
    }

    const auto& getCollected() const
    {
        return collected;
    }
};

} // namespace msge
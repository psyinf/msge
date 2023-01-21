#pragma once
#include <entities/DynamicCompoundEntity.h>
#include <entities/StaticEntity.h>
#include <entities/DynamicEntity.h>
#include <fmt/core.h>
#include <visitors/BaseEntityVisitor.h>
#include <deque>
#include "QualifiedEntityVisitor.h"
namespace msge
{

class LogEntityVisitor : public BaseEntityVisitor
{
    QualifiedNameStack nameStack;

public:
    void visit(BaseEntity& e) override
    {
        nameStack.push(e);
        print(fmt::format("Base: {}", nameStack.getQualifiedName()));
        nameStack.pop();
    }

    void visit(StaticEntity& e) override
    {
        nameStack.push(e);
        print(fmt::format("Static: {}", nameStack.getQualifiedName()));
        nameStack.pop();
    }

    void visit(DynamicCompoundEntity& e) override
    {
        nameStack.push(e);
        print(fmt::format("Compound: {}", nameStack.getQualifiedName()));
        traverse(e);
        nameStack.pop();
    }


    void visit(DynamicEntity& e) override
    {
        nameStack.push(e);
        print(fmt::format("Dynamic: {}", nameStack.getQualifiedName()));
        nameStack.pop();
    }

protected:
    virtual std::string indent() const
    {
        return std::string(nameStack.size()-1, '\t');
    }
    virtual void print(std::string_view s)
    {
        std::cout << indent() << s << "\n";
    }

    void traverse(BaseEntity& e) override
    {
        e.traverse(*this);  
    }
};

} // namespace msge
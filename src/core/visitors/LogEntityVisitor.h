#pragma once
#include <entities/CompoundEntity.h>
#include <entities/StaticEntity.h>
#include <entities/DynamicEntity.h>
#include <fmt/core.h>
#include <visitors/BaseEntityVisitor.h>
namespace msge
{

class LogEntityVisitor : public BaseEntityVisitor
{
    size_t level = 0;

public:
    void visit(BaseEntity& entity) override
    {
        print(fmt::format("Base: {}", entity.id));
    }

    void visit(StaticEntity& entity) override
    {
        print(fmt::format("Static: {}", entity.id));
    }

    void visit(CompoundEntity& entity) override
    {
        print(fmt::format("Compound: {}", entity.id));
        traverse(entity);
    }


    void visit(DynamicEntity& entity) override
    {
        print(fmt::format("Dynamic: {}", entity.id));
    }

    void finish() override{};


protected:
    virtual std::string indent() const
    {
        // #TODO: replace with a clever approach
        std::string indent;
        for (auto i = 0u; i < level; ++i)
        {
            indent += "\t";
        }
        return indent;
    }
    virtual void print(std::string_view s)
    {
        std::cout << indent() << s << "\n";
    }

    void traverse(BaseEntity& e) override
    {
        ++level;
        e.traverse(*this);
        --level;
    }
};

} // namespace msge
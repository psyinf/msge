#pragma once
#include <SerializationBuffer.h>
#include <visitors/BaseEntityVisitor.h>

#include <functional>
#include <memory>
#include <stack>
#include <strings/StringTools.h>

namespace msge
{

class FindEntityVisitor : public BaseEntityVisitor
{
public:
    explicit FindEntityVisitor(std::string_view name)
        : BaseEntityVisitor()
    {
        initializeNameStack(name);
    }

    ~FindEntityVisitor() override = default;


protected:
    void traverse(BaseEntity&) override;

    void visit(BaseEntity& entity) override;

    void visit(StaticEntity& entity) override;

    void visit(CompoundEntity& entity) override;

    void visit(DynamicEntity& entity) override;

    void finish() override;

private:
    void initializeNameStack(std::string_view name);

    std::stack<std::string> names;
};
} // namespace msge
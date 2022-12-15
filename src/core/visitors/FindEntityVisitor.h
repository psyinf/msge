#pragma once
#include <SerializationBuffer.h>
#include <strings/StringTools.h>
#include <visitors/BaseEntityVisitor.h>

#include <deque>
#include <functional>
#include <memory>
#include <optional>
namespace msge
{

class FindEntityVisitor : public BaseEntityVisitor
{
public:
    FindEntityVisitor() = default;


    std::optional<std::reference_wrapper<BaseEntity>> find( CompoundEntity& root, std::string_view name);

protected:
    void traverse(BaseEntity&) override;

    void visit(BaseEntity& entity) override;

    void visit(StaticEntity& entity) override;

    void visit(CompoundEntity& entity) override;

    void visit(DynamicEntity& entity) override;

    void finish() override;

private:
    void                                              initializeNameStack(std::string_view name);
    bool                                              traversalStopped = false;
    std::optional<std::reference_wrapper<BaseEntity>> result;

    std::deque<std::string> stack;
};
} // namespace msge
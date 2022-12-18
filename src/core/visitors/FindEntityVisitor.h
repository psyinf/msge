#pragma once
#include <SerializationBuffer.h>
#include <deque>
#include <functional>
#include <memory>
#include <optional>
#include <strings/StringTools.h>
#include <visitors/BaseEntityVisitor.h>
namespace msge
{

class FindEntityVisitor : public BaseEntityVisitor
{
public:
    FindEntityVisitor() = default;
    FindEntityVisitor(std::string_view name);

    void                                              reset(std::string_view name);
    std::optional<std::reference_wrapper<BaseEntity>> getResult() const { return result; }

    template <class T>
    std::optional<std::reference_wrapper<T>> getResult() const
    {
        static_assert(std::is_base_of<BaseEntity, T>::value, "type parameter of this class must derive from BaseEntity");
        return result;
    }

protected:
    void traverse(BaseEntity&) override;

    void visit(BaseEntity& entity) override;

    void visit(StaticEntity& entity) override;

    void visit(CompoundEntity& entity) override;

    void visit(DynamicEntity& entity) override;

    void finish() override;

private:
    void                                              initializeNameStack(std::string_view name);
    bool                                              traversalStopped = true;
    std::optional<std::reference_wrapper<BaseEntity>> result;

    std::deque<std::string> stack;
};
} // namespace msge
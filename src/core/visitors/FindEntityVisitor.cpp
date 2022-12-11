#include "FindEntityVisitor.h"
#include <entities/BaseEntity.h>
#include <typeinfo>
void msge::FindEntityVisitor::traverse(BaseEntity& e)
{
    e.traverse(*this);
}

void msge::FindEntityVisitor::visit(BaseEntity& entity)
{
    //if (names.top())
}

void msge::FindEntityVisitor::visit(DynamicEntity& entity)
{
    visit((BaseEntity&)entity);
}

void msge::FindEntityVisitor::visit(CompoundEntity& entity)
{
    visit((BaseEntity&)entity);
}

void msge::FindEntityVisitor::visit(StaticEntity& entity)
{
    visit((BaseEntity&)entity);
}

void msge::FindEntityVisitor::finish()
{
}

void msge::FindEntityVisitor::initializeNameStack(std::string_view name)
{
    auto view = name
         
              | std::views::split('.')
              | std::views::transform([](const auto& rng) {
                    auto c = rng | std::views::common;
                    return std::string_view(c);
              });
    //TODO: auto x = view | std::views::reverse;
    std::ranges::for_each(view, [this](auto s) { std::cout << s << std::endl; });
}

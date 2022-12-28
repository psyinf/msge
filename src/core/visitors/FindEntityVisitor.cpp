#include "FindEntityVisitor.h"

#include <entities/BaseEntity.h>
#include <entities/CompoundEntity.h>
#include <algorithm>
#include <ranges>
#include <string_view>

msge::FindEntityVisitor::FindEntityVisitor(std::string_view name)
{
    reset(name);
}

void msge::FindEntityVisitor::reset(std::string_view name)
{
    result           = {};
    stack            = {};
    traversalStopped = false;
    initializeNameStack(name);
    traversalStopped = stack.empty();
}

void msge::FindEntityVisitor::traverse(BaseEntity& e)
{
    e.traverse(*this);
}

void msge::FindEntityVisitor::visit(BaseEntity& entity)
{
    if (traversalStopped)
    {
        return;
    }
    if (!stack.empty() && entity.id == stack.front())
    {
        stack.pop_front();
    }
    if (stack.empty())
    {
        result           = entity;
        traversalStopped = true;
        return;
    }
}

void msge::FindEntityVisitor::visit(DynamicEntity& entity)
{
    visit((BaseEntity&)entity);
}

void msge::FindEntityVisitor::visit(CompoundEntity& entity)
{
    visit((BaseEntity&)entity);
    if (!traversalStopped)
    {
        traverse(entity);
    }
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
    /**
     * split the name by the separation character and put the result on a stack for later inspection
     */
    auto view = name
              | std::views::split('.')
              | std::views::transform([](const auto& rng) {
                    auto c = rng | std::views::common;
                    return std::string_view(c.begin(), c.end());
                });
    std::ranges::for_each(view, [this](const auto& s) { stack.emplace_back(s); });
}

#include "FindEntityVisitor.h"

#include <entities/BaseEntity.h>
#include <entities/CompoundEntity.h>
#include <typeinfo>

std::optional<std::reference_wrapper<msge::BaseEntity>> 
msge::FindEntityVisitor::find(CompoundEntity& root, std::string_view name){
    result = {};
    traversalStopped = false;
    initializeNameStack(name);
    root.accept(*this);
    return result;
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
    if (entity.id == stack.front())
    {
        std::cout << "considered "
                  << entity.id
                  << std::endl;
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
    auto view = name
              | std::views::split('.')
              | std::views::transform([](const auto& rng) {
                    auto c = rng | std::views::common;
                    return std::string_view(c);
                });
    std::ranges::for_each(view, [this](const auto& s) { stack.emplace_back(s); });
}

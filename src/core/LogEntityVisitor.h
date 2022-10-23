#pragma once
#include <BaseEntityVisitor.h>

namespace msge{

class LogEntityVisitor : public BaseEntityVisitor
{

public:

    void visit(msge::BaseEntity& entity) override
    {
        std::cout << "Base: " << entity.id << "\n";
    }

    void visit(msge::StaticEntity& entity) override
    {
        std::cout << "Static: " << entity.id << "\n";
    }
};

} //namespace msge
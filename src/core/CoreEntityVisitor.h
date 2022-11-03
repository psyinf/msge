#pragma once
#include <memory>

#include <BaseEntityVisitor.h>


namespace msge {


class Core;
/**
 * Abstract base class of BaseEntityVisitor classes that are associated with a Core instance
 */

class CoreEntityVisitor : public BaseEntityVisitor
{   
    
public:
    Core& core;

    CoreEntityVisitor(Core& core)
        : BaseEntityVisitor()
        , core(core)
    {}
};
}
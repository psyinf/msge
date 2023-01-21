#include "BaseEntityVisitor.h"
#include "entities/BaseEntity.h"


void msge::BaseEntityVisitor::traverse(msge::BaseEntity& e)
{
    e.traverse(*this);
}

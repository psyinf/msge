#pragma once

namespace msge{

class BaseEntity;
class StaticEntity;
class DynamicCompoundEntity;
class DynamicEntity;
class BaseEntityVisitor
{
public:
    BaseEntityVisitor()          = default;
    virtual ~BaseEntityVisitor() = default;

    virtual void visit(BaseEntity& entity) = 0;
	virtual void visit(StaticEntity& entity) = 0;
    virtual void visit(DynamicCompoundEntity& entity) = 0;
    virtual void visit(DynamicEntity& entity) = 0;
    virtual void finish()                      = 0;

protected:
    virtual void traverse(BaseEntity&)         = 0;
};


} //namespace msge
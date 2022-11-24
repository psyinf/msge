#pragma once

namespace msge{

class BaseEntity;
class StaticEntity;
class CompoundEntity;

class BaseEntityVisitor
{
public:
    BaseEntityVisitor()          = default;
    virtual ~BaseEntityVisitor() = default;

    virtual void visit(BaseEntity& entity) = 0;
	virtual void visit(StaticEntity& entity) = 0;
    virtual void visit(CompoundEntity& entity) = 0;
    virtual void finish()                      = 0;

protected:
    virtual void traverse(BaseEntity&)         = 0;
};


} //namespace msge
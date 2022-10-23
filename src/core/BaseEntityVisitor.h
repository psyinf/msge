#pragma once

namespace msge{

class BaseEntity;
class StaticEntity;

class BaseEntityVisitor
{
public:
    BaseEntityVisitor()          = default;
    virtual ~BaseEntityVisitor() = default;

    virtual void visit(BaseEntity& entity) = 0;
	virtual void visit(StaticEntity& entity) = 0;

};


} //namespace msge
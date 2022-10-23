#pragma once

namespace msge{

class BaseEntity;
class StaticEntity;

class BaseEntityVisitor
{
public:
    BaseEntityVisitor()          = default;
    virtual ~BaseEntityVisitor() = default;

    virtual void visit(msge::BaseEntity& entity) = 0;
	virtual void visit(msge::StaticEntity& entity) = 0;

};


} //namespace msge
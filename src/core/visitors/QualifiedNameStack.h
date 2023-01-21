#pragma once
#include <deque>
#include <CoreDefinitions.h>
namespace msge {

class QualifiedNameStack
{
public:
    std::deque<EntityId> idStack;

    void push(BaseEntity& e)
    {
        idStack.push_back(e.id);
    }

    void pop()
    {
        idStack.pop_back();
    }

    size_t size() const
    {
        return idStack.size();
    }

    std::string getQualifiedName() const
    {
        return makeQualifiedName(idStack);
    }
};	
	
}
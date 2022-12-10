#pragma once
#include <SerializationBuffer.h>
#include <functional>
#include <memory>
#include <visitors/BaseEntityVisitor.h>


namespace msge
{

class FindEntityVisitor : public BaseEntityVisitor
{

public:
    using BaseEntityVisitor::BaseEntityVisitor;


};
} // namespace msge
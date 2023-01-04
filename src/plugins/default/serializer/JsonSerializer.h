#include <deque>
#include <fstream>
#include <nlohmann/json.hpp>
#include <visitors/CoreEntityVisitor.h>
#include <CoreDefinitions.h>

namespace msge
{
class Core;
class BaseEntity;
class StaticEntity;
class DynamicEntity;
class CompoundEntity;
}

namespace msge::plugin
{

/**
 * Serializer that converts a list of entities individually.
 */

class JsonSerializer : public CoreEntityVisitor
{
public:
    using IdStack = std::deque<msge::EntityId>;

    JsonSerializer(Core& core);


    void visit(BaseEntity& entity) override;

    void visit(StaticEntity& entity) override;

    void visit(CompoundEntity& entity) override;

    void visit(DynamicEntity& entity) override;

    void finish() override;

protected:
    void traverse(BaseEntity& e) override;

private:
    IdStack idStack;
};
} // namespace msge::plugin
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
 * Serializer that produces State snapshots (e.g. to serve as updates to a rendering back-end)
 */

class JsonStateSerializer : public CoreEntityVisitor
{
public:
    using IdStack = std::deque<msge::EntityId>;

    explicit JsonStateSerializer(Core& core);


    void visit(BaseEntity& entity) override;

    void visit(StaticEntity& entity) override;

    void visit(DynamicCompoundEntity& entity) override;

    void visit(DynamicEntity& entity) override;

protected:
    void traverse(BaseEntity& e) override;

private:
    IdStack idStack;
};
} // namespace msge::plugin
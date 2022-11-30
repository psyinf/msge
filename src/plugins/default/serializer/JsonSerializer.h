#include <entities/BaseEntity.h>
#include <entities/CompoundEntity.h>
#include <entities/StaticEntity.h>
#include <visitors/CoreEntityVisitor.h>

#include <fstream>
#include <nlohmann/json.hpp>
#include <deque>


namespace msge
{
class Core;
}

namespace msge::plugin
{

/**
 * Serializer that converts a list of entities individually. 
 */

class JsonSerializer : public CoreEntityVisitor
{
public:
    using IdStack  = std::deque<EntityId>;

    JsonSerializer(Core& core);


    void visit(BaseEntity& entity) override;

    void visit(StaticEntity& entity) override;

    void visit(CompoundEntity& entity) override;

    void finish() override;

protected:
    void traverse(BaseEntity& e) override;

private:
    IdStack idStack;
};
} // namespace msge::plugin
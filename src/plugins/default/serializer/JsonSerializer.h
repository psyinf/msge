#include <entities/BaseEntity.h>
#include <entities/CompoundEntity.h>
#include <entities/StaticEntity.h>
#include <visitors/CoreEntityVisitor.h>

#include <fstream>
#include <nlohmann/json.hpp>
#include <stack>


namespace msge
{
class Core;
}

namespace msge::plugin
{


class JsonSerializer : public CoreEntityVisitor
{


public:
    JsonSerializer(Core& core);


    void visit(BaseEntity& entity) override;

    void visit(StaticEntity& entity) override;

    void visit(CompoundEntity& entity) override;

    void finish() override;

protected:
    void traverse(BaseEntity& e) override;

private:
    std::stack<EntityId> idStack;
};
} // namespace msge::plugin
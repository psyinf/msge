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

namespace msge
{

/**
 * Serializer that produces entity snapshots (e.g. to Save the scene to json)
 */

class JsonEntityVisitor : public BaseEntityVisitor
{

public:
    JsonEntityVisitor(JsonType& jt);

    void visit(BaseEntity & entity) override;

    void visit(StaticEntity& entity) override;

    void visit(DynamicCompoundEntity& entity) override;

    void visit(DynamicEntity& entity) override;

protected:
    void traverse(BaseEntity& e) override;

    JsonType& json;
};
} // namespace plugin
#include <BaseEntity.h>
#include <CoreEntityVisitor.h>
#include <CompoundEntity.h>
#include <StaticEntity.h>

#include <nlohmann/json.hpp>

#include <fstream>

namespace msge
{
class Core;
}

namespace msge::plugin
{


class JsonSerializer : public CoreEntityVisitor
{
    

public:
    JsonSerializer(Core& core );



    void visit(BaseEntity& entity) override;

    void visit(StaticEntity& entity) override;

    void visit(CompoundEntity& entity) override;

   void finish() override;

protected:
    void traverse(BaseEntity& e) override;
};
} // namespace msge::plugin
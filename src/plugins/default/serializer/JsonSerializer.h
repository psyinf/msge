#include <BaseEntity.h>
#include <BaseEntityVisitor.h>
#include <CompoundEntity.h>
#include <StaticEntity.h>

namespace msge::plugin
{


class JsonSerializer : public CoreEntityVisitor
{
    //std::ostream& os =  std::cout;

public:
    JsonSerializer(Core& core )
        : CoreEntityVisitor(core)
    {
        //TODO: retrieve the prototype to serialize to
    }

    void visit(BaseEntity& entity) override
    {
       
    }

    void visit(StaticEntity& entity) override
    {
      
    }

    void visit(CompoundEntity& entity) override
    {
       
    }

protected:
    void traverse(BaseEntity& e) override
    {
        e.traverse(*this);
    }
};
} // namespace msge::plugin
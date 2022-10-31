#include <BaseEntity.h>
#include <BaseEntityVisitor.h>
#include <CompoundEntity.h>
#include <StaticEntity.h>

namespace msge::plugin
{
class StreamSerializer : public BaseEntityVisitor
{
    std::ostream& os =  std::cout;

public:
    //TODO: add constructor with sink descriptor. This could be a reference to a registry holding a sink


    void visit(BaseEntity& entity) override
    {
        os << entity.id;
        entity.accept(*this);
    }

    void visit(StaticEntity& entity) override
    {
        os << entity.id;
        entity.accept(*this);
    }

    void visit(CompoundEntity& entity) override
    {
        os << entity.id;
        entity.accept(*this);
    }

protected:
    void traverse(BaseEntity& e) override
    {
        e.traverse(*this);
    }
};
} // namespace msge::plugin
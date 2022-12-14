#include <Core.h>
#include <LogEntityVisitor.h>
#include <SimpleScene.h>
#include <StaticEntity.h>
#include <exception>
#include <iostream>
#include <memory>


using namespace msge;





int main(int argc, char** argv)
try
{
    std::vector<std::string_view> arguments(argv, argv + argc);
    Core::initializeLogging(arguments);

    auto bs = std::make_unique<SimpleScene>("scene1");

    auto ses = {StaticEntity{"se1"}, StaticEntity{"se2"}, StaticEntity{"se3"}};
    for (auto& es : ses)
    {
        bs->addEntity(std::make_shared<StaticEntity>(es));
    }
    

    CompoundEntity group1 = CompoundEntity("g1");
    group1.addChildren(std::make_shared<BaseEntity>("sub1"));
    group1.addChildren(std::make_shared<BaseEntity>("sub2"));
    bs->addEntity(std::make_shared<CompoundEntity>(std::move(group1)));
    bs->addEntity(std::make_shared<BaseEntity>("be1"));
    msge::LogEntityVisitor lev;

    

    bs->runVisitor(lev);
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}
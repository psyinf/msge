#include <Core.h>
#include <visitors/LogEntityVisitor.h>
#include <scenes/SimpleScene.h>
#include <entities/StaticEntity.h>
#include <exception>
#include <iostream>
#include <memory>
#include <visitors/CollectSceneEntitiesVisitor.h>


using namespace msge;





int main(int argc, char** argv)
try
{
    std::vector<std::string_view> arguments(argv, argv + argc);
    Core::initializeLogging(arguments);

    auto bs = std::make_unique<SimpleScene>("scene1");

    auto ses = {StaticEntity{"se1", "t1"}, StaticEntity{"se2", "t1"}, StaticEntity{"se3", "t1"}};
    for (auto& es : ses)
    {
        bs->addEntity(std::make_shared<StaticEntity>(es));
    }
    

    auto group1 = DynamicCompoundEntity("g1", "gt1");
    group1.addChildren(std::make_shared<BaseEntity>("sub1", "st1"));
    group1.addChildren(std::make_shared<BaseEntity>("sub2", "st1"));
    bs->addEntity(std::make_shared<DynamicCompoundEntity>(std::move(group1)));
    bs->addEntity(std::make_shared<BaseEntity>("be1", "t1"));
    msge::LogEntityVisitor lev;
    CollectSceneEntitiesVisitor cse;
    bs->runVisitor(cse);
    std::ranges::for_each(cse.getCollected(), [](const auto& p) {auto [k,v] = p; std::cout << k << "("<< v.get().id << ")" << std::endl; });
  
    

    bs->runVisitor(lev);
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}
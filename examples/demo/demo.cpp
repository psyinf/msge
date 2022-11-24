#include "Core.h"
#include "CoreConfig.h"

#include <StaticEntity.h>
#include <CompoundEntity.h>

#include <plugins/PluginRegistry.h>
#include <exception>
#include <iostream>

using namespace msge;


auto makeStaticEntity(std::string_view name, const Spatial& s)
{
    auto e     = std::make_shared<StaticEntity>(name);
    e->spatial = s;
    return e;
}

auto makeGroup(std::string_view name)
{
   return std::make_shared<CompoundEntity>(name);
}

int main(int argc, char** argv)
try
{
    /* Setup the core instance. Pass a configuration item and some command line arguments.*/
    CoreConfig c;
    c.default_scene = "root";

    Core core(c, Core::makeCommandLineArgs(argc, argv));

    // add simple scene
    auto& scene = core.getScene("root");
    // static entity
    scene.addEntity(makeStaticEntity("se1", Spatial{gmtl::Point3d{0, 0, 0}}));
    scene.addEntity(makeStaticEntity("se2", Spatial{gmtl::Point3d{1, 0, 0}}));
    auto g = makeGroup("g1");
    auto g2 = makeGroup("g2");
    scene.addEntity(g);
    g->addChildren(g2);
    g->addChildren(makeStaticEntity("sge1", Spatial{}));
    g2->addChildren(makeStaticEntity("sge2", Spatial{}));
   
    auto jsonSerializer =  core.getPluginRegistry().getCoreVisitorPrototype("JsonSerializer", core);
    scene.runVisitor(*jsonSerializer);


   
    //
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}
#include "Core.h"
#include "CoreConfig.h"

#include <ArrayTaskQueue.h>
#include <BasicScheduler.h>
#include <SerializationBuffer.h>
#include <entities/CompoundEntity.h>
#include <entities/StaticEntity.h>
#include <exception>
#include <iostream>
#include <plugins/PluginRegistry.h>

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

void getMsg(msge::EntitySerializationBuffer&& buf)
{
    std::cout << buf.key << "\n";
    std::cout << std::string(buf.buffer.begin(), buf.buffer.end()) << "\n";
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
    auto g  = makeGroup("g1");
    auto g2 = makeGroup("g2");
    scene.addEntity(g);
    g->addChildren(g2);
    g->addChildren(makeStaticEntity("sge1", Spatial{}));
    g2->addChildren(makeStaticEntity("sge2", Spatial{}));

    auto jsonSerializer = core.getPluginRegistry().getCoreVisitorPrototype("JsonSerializer", core);
    jsonSerializer->setSink(getMsg);
    scene.runVisitor(*jsonSerializer);


    core.addTask("frameStart", [](auto& frame_stamp) { std::cout << " starting frame  " << frame_stamp.frameNumber << std::endl; });

    core.addTask("frameEnd", [](auto& frame_stamp) { std::cout << " ending frame  " << frame_stamp.frameNumber << std::endl; });
    auto future = core.start();
    // TODO: put serializer into a task and some task to modify an entity (group with children) every frame


    //

    future.get();
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}
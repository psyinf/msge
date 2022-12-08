#include "Core.h"
#include "CoreConfig.h"

#include <ArrayTaskQueue.h>
#include <BasicScheduler.h>
#include <SerializationBuffer.h>
#include <entities/CompoundEntity.h>
#include <entities/StaticEntity.h>
#include <entities/DynamicEntity.h>
#include <math/Spatial.h>
#include <exception>
#include <iostream>
#include <thread>
#include <plugins/PluginRegistry.h>

using namespace msge;


auto makeStaticEntity(std::string_view name, const common::math::Spatial& s)
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


void setupScene(msge::BaseScene& scene)
{
    // static entity
    scene.addEntity(makeStaticEntity("se1", common::math::Spatial{gmtl::Point3d{0, 0, 0}}));
    scene.addEntity(makeStaticEntity("se2", common::math::Spatial{gmtl::Point3d{1, 0, 0}}));
    auto g  = makeGroup("g1");
    auto g2 = makeGroup("g2");
    scene.addEntity(g);
    g->addChildren(g2);
    g->addChildren(makeStaticEntity("sge1", common::math::Spatial{}));
    g2->addChildren(makeStaticEntity("sge2", common::math::Spatial{}));
}

void setupTasks(Core& core)
{
    //some informative task
    core.addTask("frameStart", [](const auto& frame_stamp) {
        if (frame_stamp.frameNumber % 1000 == 0)
        {
            std::cout << " starting frame  " << frame_stamp.frameNumber << std::endl;
        }
    });

    core.addTask("playing the waiting game", []([[maybe_unused]] const auto& frame_stamp) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    });
    //some informative end-task
    core.addTask("frameEnd", [](auto& frame_stamp) {
        if (frame_stamp.frameNumber % 1000 == 0)
        {
            std::cout << " starting frame  " << frame_stamp.frameNumber << std::endl;
        }
    });


}

class Mover : public DynamicEntity
{

};

int main(int argc, char** argv)
try
{
    /* Setup the core instance. Pass a configuration item and some command line arguments.*/
    CoreConfig c;
    c.default_scene = "root";

    Core core(c, Core::makeCommandLineArgs(argc, argv));

    // add simple scene
    auto& scene = core.getScene("root");
    setupScene(scene);
    

    setupTasks(core);


    //run the core
    auto future = core.start();
    // TODO: put serializer into a task and some task to modify an entity (group with children) every frame
    future.get();
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}
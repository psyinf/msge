#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#undef WIN32_LEAN_AND_MEAN
#include "Core.h"
#include "CoreConfig.h"

#include <ArrayTaskQueue.h>
#include <BasicScheduler.h>
#include <SerializationBuffer.h>
#include <entities/CompoundEntity.h>
#include <entities/DynamicEntity.h>
#include <entities/StaticEntity.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <math/DeadReckoning.h>
#include <math/Spatial.h>
#include <plugins/PluginRegistry.h>
#include <thread>
#include <visitors/FindEntityVisitor.h>
#include "KafkaStreamAdapter.h"

using namespace msge;

/*Very simple dynamic entity*/
class Mover : public DynamicEntity
{
    Mover(Mover&) = delete;


public:
    using DynamicEntity::DynamicEntity;
    // move along some simple path
    void frame(const FrameStamp& fs)
    {
        const auto   dim = 10.0f;
        gmtl::AABoxd box(gmtl::Vec3d{-dim, -dim, -dim}, {dim, dim, dim});
        auto&        velocity = spatial.velocity;
        auto&        trans    = spatial.position;
        trans += velocity * common::math::DeadReckoning::toSeconds(fs.frameTime);
        for (auto i : {0, 1, 2})
        {
            if (trans[i] > box.mMax[i])
            {
                trans[i]    = box.mMax[i];
                velocity[i] = -velocity[i];
            }
            else if (trans[i] < box.mMin[i])
            {
                trans[i]    = box.mMin[i];
                velocity[i] = -velocity[i];
            }
        }
        if (fs.frameNumber % 1000)
        {
            std::cout << spatial.position << std::endl;
        }
    }
};

/**
 * Simple stream sink
 */

class SerializationBufferStreamAdaptor
{
public:
    SerializationBufferStreamAdaptor(std::ostream& ostream)
        : stream(ostream.rdbuf())
    {
    }


    void operator()(const EntitySerializationBuffer& b)
    {
        stream << b;
    }


private:
    std::ostream stream;
};




std::ofstream                    outstream("outstream.txt");
SerializationBufferStreamAdaptor sa(outstream);
KafkaStreamAdaptor               ka;

auto makeMover(std::string_view name, common::math::Dynamic&& s)
{
    auto e     = std::make_shared<Mover>(name);
    e->spatial = std::move(s);
    return e;
}


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


void setupScene(msge::BaseScene& scene)
{

    // static entity
    scene.addEntity(makeStaticEntity("se1", common::math::Spatial{gmtl::Point3d{0, 0, 0}}));
    scene.addEntity(makeStaticEntity("se2", common::math::Spatial{gmtl::Point3d{1, 0, 0}}));
    auto g               = makeGroup("g1");
    auto g2              = makeGroup("g2");
    g2->spatial.position = {0, 1, 0};
    scene.addEntity(g);
    g->addChildren(g2);
    g->addChildren(makeStaticEntity("sge1", common::math::Spatial{}));
    g2->addChildren(makeStaticEntity("sge2", common::math::Spatial{}));
    g2->addChildren(makeMover("m1", common::math::Dynamic{.velocity{0, 0, 1}}));
}


void setupTasks(Core& core)
{
    auto jsonSerializer = std::shared_ptr<msge::CoreEntityVisitor>(core.getPluginRegistry().getCoreVisitorPrototype("JsonSerializer", core));
    //jsonSerializer->setSink(std::bind_front(&SerializationBufferStreamAdaptor::operator(), &sa));
    jsonSerializer->setSink(std::bind_front(&KafkaStreamAdaptor::operator(), &ka));


    std::reference_wrapper<Mover> m = core.getScene("root").findEntity<Mover>("g1.g2.m1").value();

    // some informative task
    core.addTask("frameStart", [](const auto& frame_stamp) {
        if (frame_stamp.frameNumber % 1000 == 0)
        {
            std::cout << " starting frame  " << frame_stamp.frameNumber << std::endl;
        }
    });

    core.addTask("Serialize", [&core, jsonSerializer]([[maybe_unused]] const auto& frame_stamp) {
        if (0 == frame_stamp.frameNumber % 100)
        {
            core.getScene("root").runVisitor(*jsonSerializer, nullptr);
        }
    });

    core.addTask("playing the waiting game", []([[maybe_unused]] const auto& frame_stamp) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    });

    core.addTask("move", [m](const auto& fs) { m.get().frame(fs); });

    // some informative end-task
    core.addTask("frameEnd", [](auto& frame_stamp) {
        if (frame_stamp.frameNumber % 1000 == 0)
        {
            std::cout << " starting frame  " << frame_stamp.frameNumber << std::endl;
        }
    });
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
    setupScene(scene);


    setupTasks(core);


    // run the core
    auto future = core.start();
    future.get();
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#undef WIN32_LEAN_AND_MEAN
#endif
#include "Core.h"
#include "CoreConfig.h"
#include "KafkaStreamAdapter.h"

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

using namespace msge;
class SceneObject
{
public:
    virtual ~SceneObject() = default;

protected:
    virtual void frame(const FrameStamp& fs) = 0;

    void reflectAtBounds(common::math::Dynamic& spatial)
    {
        const auto   dim = 10.0f;
        gmtl::AABoxd box(gmtl::Vec3d{-dim, -dim, -dim}, {dim, dim, dim});

        auto& velocity = spatial.velocity;
        auto& trans    = spatial.position;
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
    }
};
/*Very simple dynamic entity*/
class Mover : public DynamicEntity
    , public SceneObject
{
    Mover(Mover&) = delete;


public:
    using DynamicEntity::DynamicEntity;
    // move along some simple path
    void frame(const FrameStamp& fs) override
    {
        spatial.position += spatial.velocity * common::math::DeadReckoning::toSeconds(fs.frameTime);
        reflectAtBounds(spatial);
    }
};

class CompoundMover : public CompoundEntity
    , public SceneObject
{
public:
    using CompoundEntity::CompoundEntity;
    // move along some simple path
    void frame(const FrameStamp& fs) override
    {
        spatial.position += spatial.velocity * common::math::DeadReckoning::toSeconds(fs.frameTime);
        reflectAtBounds(spatial);
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
    auto e     = std::make_shared<Mover>(name, "cone");
    e->spatial = std::move(s);
    return e;
}
auto makeCompoundMover(std::string_view name, common::math::Dynamic&& s)
{
    auto e     = std::make_shared<CompoundMover>(name, "cone");
    e->spatial = std::move(s);
    return e;
}

auto makeStaticEntity(std::string_view name, std::string_view type, const common::math::Spatial& s)
{
    auto e     = std::make_shared<StaticEntity>(name, type);
    e->spatial = s;
    return e;
}

auto makeGroup(std::string_view name, std::string_view type)
{
    return std::make_shared<CompoundEntity>(name, type);
}


void setupScene(msge::BaseScene& scene)
{
    const auto cube = "cube";
    // static entities as scene markers
    scene.addEntity(makeStaticEntity("a111", cube, common::math::Spatial{gmtl::Point3d{-10, -10, -10}}));
    scene.addEntity(makeStaticEntity("a110", cube, common::math::Spatial{gmtl::Point3d{-10, -10, 10}}));
    scene.addEntity(makeStaticEntity("a101", cube, common::math::Spatial{gmtl::Point3d{-10, 10, -10}}));
    scene.addEntity(makeStaticEntity("a100", cube, common::math::Spatial{gmtl::Point3d{-10, 10, 10}}));
    scene.addEntity(makeStaticEntity("a011", cube, common::math::Spatial{gmtl::Point3d{10, -10, -10}}));
    scene.addEntity(makeStaticEntity("a010", cube, common::math::Spatial{gmtl::Point3d{10, -10, 10}}));
    scene.addEntity(makeStaticEntity("a001", cube, common::math::Spatial{gmtl::Point3d{10, 10, -10}}));
    scene.addEntity(makeStaticEntity("a000", cube, common::math::Spatial{gmtl::Point3d{10, 10, 10}}));

    auto g               = makeGroup("g1", "");
    auto g2              = makeGroup("g2", "");
    g->spatial.position  = {0, -1, 0};
    g2->spatial.position = {0, 3, 0};
    scene.addEntity(g);
    g->addChildren(g2);
    g->addChildren(makeStaticEntity("sge1", "sphere", common::math::Spatial{}));
    g2->addChildren(makeStaticEntity("sge2", "sphere", common::math::Spatial{}));
    g2->addChildren(makeMover("m1", common::math::Dynamic{.velocity{0, 0, 1}}));
    auto m2 = makeCompoundMover("m2", common::math::Dynamic{.velocity{0, 0, -1}});
    m2->addChildren(makeStaticEntity("p1", cube, common::math::Spatial{gmtl::Point3d{-0.75, -0.75, -1}}));
    m2->addChildren(makeStaticEntity("p2", cube, common::math::Spatial{gmtl::Point3d{0.75, -0.75, -1}}));
    m2->addChildren(makeStaticEntity("p3", cube, common::math::Spatial{gmtl::Point3d{-0.75, 0.75, -1}}));
    m2->addChildren(makeStaticEntity("p4", cube, common::math::Spatial{gmtl::Point3d{0.75, 0.75, -1}}));

    g2->addChildren(m2);
}


void setupTasks(Core& core)
{
    auto jsonSerializer = std::shared_ptr<msge::CoreEntityVisitor>(core.getPluginRegistry().getCoreVisitorPrototype("JsonSerializer", core));
    // jsonSerializer->setSink(std::bind_front(&SerializationBufferStreamAdaptor::operator(), &sa));
    jsonSerializer->setSink(std::bind_front(&KafkaStreamAdaptor::operator(), &ka));


    std::reference_wrapper<Mover>         m  = core.getScene("root").findEntity<Mover>("g1.g2.m1").value();
    std::reference_wrapper<CompoundMover> m2 = core.getScene("root").findEntity<CompoundMover>("g1.g2.m2").value();

    // some informative task
    core.addTask("frameStart", [](const auto& frame_stamp) {
        if (frame_stamp.frameNumber % 1000 == 0)
        {
            std::cout << " starting frame  " << frame_stamp.frameNumber << std::endl;
        }
    });

    core.addTask("Serialize", [&core, jsonSerializer]([[maybe_unused]] const auto& frame_stamp) {
        //if (0 == frame_stamp.frameNumber % 5)
        {
            core.getScene("root").runVisitor(*jsonSerializer, nullptr);
        }
    });

    core.addTask("playing the waiting game", []([[maybe_unused]] const auto& frame_stamp) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    });

    core.addTask("move", [m](const auto& fs) { m.get().frame(fs); });
    core.addTask("move2", [m2](const auto& fs) { m2.get().frame(fs); });

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
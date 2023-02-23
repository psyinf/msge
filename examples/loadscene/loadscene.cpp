#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#undef WIN32_LEAN_AND_MEAN
#endif
#include <Core.h>
#include <CoreConfig.h>
#include "KafkaStreamAdapter.h"
#include "scene.h"
#include "entities.h"

#include <ArrayTaskQueue.h>
#include <BasicScheduler.h>
#include <SerializationBuffer.h>
#include <entities/DynamicCompoundEntity.h>
#include <entities/DynamicEntity.h>
#include <entities/StaticEntity.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <math/DeadReckoning.h>
#include <math/Spatial.h>
#include <nlohmann/json.hpp>
#include <plugins/PluginRegistry.h>
#include <thread>
#include <visitors/CollectSceneEntitiesVisitor.h>
#include <visitors/DefaultEntityVisitor.h>
#include <visitors/QualifiedNameStack.h>
#include <serializers/StateJsonSerializer.h>

using namespace msge;

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



class SaveEntityVisitor : public BaseEntityVisitor
{

public:
    SaveEntityVisitor(JsonType& jt)
        : json(jt)
    {
    }

    void visit(BaseEntity& entity) override
    {
        json["state"] = *entity.entityState;
    }

    void visit(StaticEntity& entity) override
    {
        json["spatial"] = entity.spatial;
        visit(static_cast<BaseEntity&>(entity));
    }

    void visit(DynamicCompoundEntity& entity) override
    {
        json["spatial"] = entity.spatial;
        visit(static_cast<BaseEntity&>(entity));
    }

    void visit(DynamicEntity& entity) override
    {
        json["spatial"] = entity.spatial;
        visit(static_cast<BaseEntity&>(entity));
    }

protected:
    void traverse(BaseEntity& e) override
    {
    }

    JsonType& json;
};

/**
 * Simple method to serialize a scene to json
 */
void saveScene(msge::BaseScene& scene)
{
    std::ofstream               os("data/test_out.json");
    auto          scene_json   = nlohmann::json::object();
    auto                        entites = nlohmann::json::array();

    CollectSceneEntitiesVisitor csev;
    scene.runVisitor(csev);
    std::ranges::for_each(csev.getCollected(), [&](const auto& pair) {
        const auto& [name, item] = pair;
        fmt::print("{}\n", name);
        nlohmann::json    entity;
        SaveEntityVisitor sev(entity);

        item.get().accept(sev);
        auto data = nlohmann::json::object();
        entity["id"] = name;
        data["entity"] = entity;
        entites.push_back(data);
        
    });
    scene_json["entities"] = entites;
    os << scene_json;
}

void loadScene(msge::BaseScene& scene)
{
    std::ifstream is("data/test_scene.json");
    auto          loaded = nlohmann::json::parse(is);
    for (const auto& s : loaded)
    {
        
    }
    //...scene
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
        // if (0 == frame_stamp.frameNumber % 5)
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
    //todo: from cmd-line
    auto load = false;

    /* Setup the core instance. Pass a configuration item and some command line arguments.*/
    CoreConfig c;
    c.default_scene = "root";

    Core core(c, Core::makeCommandLineArgs(argc, argv));
    
  
    auto& scene = core.getScene("root");
    if (load)
    {
        loadScene(scene);
    }
    else
    {
        setupScene(scene);
        saveScene(scene);

    }
   

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
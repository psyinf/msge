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
#include <visitors/JsonEntitySerializer.h>
#include <serializers/StateJsonSerializer.h>

using namespace msge;

/**
 * Simple method to serialize a scene to json
 */
void saveScene(msge::BaseScene& scene)
{

    auto                        filename = "data/test_out2.json";
    std::ofstream               os(filename);
    auto          scene_json   = nlohmann::json::object();
    auto                        entites = nlohmann::json::array();

    CollectSceneEntitiesVisitor csev;
    scene.runVisitor(csev);
    std::ranges::for_each(csev.getCollected(), [&](const auto& pair) {
        const auto& [name, item] = pair;
        fmt::print("{}\n", name);
        nlohmann::json    entity;
       
        item.get().save(entity);
        auto data = nlohmann::json::object();
        entity["id"] = name;
        data["entity"] = entity;
        entites.push_back(data);
        
    });
    scene_json["entities"] = entites;
    os << scene_json;
    fmt::print("Successfully saved to {} ", filename);
}


int main(int argc, char** argv)
try
{
    /* Setup the core instance. Pass a configuration item and some command line arguments.*/
    CoreConfig c;
    c.default_scene = "root";
    c.plugins.loadTypes   = CoreConfig::Plugins::PluginTypes::DEFAULT;
    
    Core core(c, Core::makeCommandLineArgs(argc, argv));
    
  
    auto& scene = core.getScene("root");
    setupScene(scene);
    saveScene(scene);
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Caught unhandled exception: " << e.what() << "\n";
}  
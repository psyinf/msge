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
#include <serializers/FixedStringSerializer.h>
using namespace msge;

enum class EntityTypeTags
{
    Static,
    Dynamic,

};

class TagEntityFactory
{
public:
    TagEntityFactory() = default;

    std::shared_ptr<BaseEntity> build(const JsonType& json) {
        //extract type:
        auto tag = json["tag"];
        fmt::print("tag: {}", tag);
        if (tag == "Static")
        {
        
            auto se = std::make_shared<StaticEntity>();
            se->load(json);
        }
        else if (tag == "Dynamic")
        {
        
        }
        else if (tag == "DynamicCompound")
        {
        }
        else if (tag == "Base")
        {

        }
        auto result = std::make_shared<BaseEntity>();
        return result;
    }


};

void loadScene(msge::BaseScene& scene)
{
    std::ifstream is("data/saved_scene.json");
   
    auto          loaded = nlohmann::json::parse(is);
    TagEntityFactory tef;
    
    for (const auto& s : loaded["entities"])
    {
        tef.build(s["entity"]);    
    }
    //...scene
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
    loadScene(scene);
    

    

    // run the core
    auto future = core.start();
    future.get();
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}
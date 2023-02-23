#pragma once

#include <set>
#include <string>
#include <nlohmann/json.hpp>
namespace msge
{


struct CoreConfig
{
    struct Plugins
    {
        enum class PluginTypes
        {
            ALL,
            DEFAULT,
            NONE,
        };
        std::string path = "plugins";
        std::string filter = "*.dll"; //TODO: default plugin extension per platform
        PluginTypes loadTypes = PluginTypes::ALL;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Plugins, path, filter, loadTypes)
    };
    
    Plugins     plugins;
    std::string default_scene = "root"; //
    std::string scheduler_name = "BasicScheduler";
    std::string task_queue_name = "ArrayTaskQueue";
    

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CoreConfig, plugins, default_scene)
};

}
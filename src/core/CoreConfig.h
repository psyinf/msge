#pragma once

#include <set>
#include <string>
#include <nlohmann/json.hpp>
namespace msge
{

struct CoreConfig
{
    std::string plugins_path = "plugins";
    std::string default_scene = "root"; //
    std::string scheduler_name = "BasicScheduler";
    std::string task_queue_name = "ArrayTaskQueue";
    

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CoreConfig, plugins_path, default_scene)
};

}
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
    

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CoreConfig, plugins_path, default_scene)
};

}
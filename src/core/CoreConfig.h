#pragma once
#include <string>
#include <nlohmann/json.hpp>
namespace msge
{

struct CoreConfig
{
    std::string plugins_path = "plugins";

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CoreConfig, plugins_path)
};

}
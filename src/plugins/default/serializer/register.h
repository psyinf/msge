#pragma once


#include <Core.h>
#include <plugins/PluginBase.h>
#include <plugins/PluginRegistry.h>
#include <serializer/JsonSerializer.h>

#include <fmt/core.h>

#include <vector>

auto registerPlugins(msge::Core& core)
{
    std::vector<std::string> names;
    auto&                    registry = core.getPluginRegistry();
    try
    {
        auto [name, proto] = std::make_pair("JsonSerializer", common::GenericFactory<msge::plugin::JsonSerializer, msge::Core&>::proto());
        registry.registerPlugin(name, proto);
        names.emplace_back(name);
    }
    catch (const std::runtime_error& e)
    {
        LOG(ERROR) << "Error registering prototype: " << e.what();
    }
    return names;
}

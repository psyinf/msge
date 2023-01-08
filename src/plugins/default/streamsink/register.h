#pragma once


#include <Core.h>
#include <plugins/PluginBase.h>
#include <plugins/PluginRegistry.h>
#include <streamsink/SerializationStreamAdapter.h>

#include <fmt/core.h>

#include <vector>

auto registerStreamSinks(msge::Core& core)
{
    std::vector<std::string> names;
    auto&                    registry = core.getPluginRegistry();
    try
    {
        auto [name, proto] = std::make_pair("SerializationStreamAdaptor", common::GenericFactory<msge::plugin::SerializationStreamAdaptor, msge::Core&, const msge::StreamSinkConfig&>::proto());
        registry.registerPlugin(name, proto);
        names.emplace_back(name);
    }
    catch (const std::runtime_error& e)
    {
        LOG(ERROR) << "Error registering prototype: " << e.what();
    }
    return names;
}

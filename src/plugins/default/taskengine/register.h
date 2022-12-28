#pragma once


#include <Core.h>
#include <plugins/PluginBase.h>
#include <plugins/PluginRegistry.h>

#include <ArrayTaskQueue.h>
#include <BasicScheduler.h>

#include <fmt/core.h>

#include <vector>

auto registerSchedulers(msge::Core& core)
{
    std::vector<std::string> names;
   
    try
    {
        core.getSchedulerPrototypes().registerPrototype("BasicScheduler", common::GenericFactory<msge::BasicScheduler>::proto());   
        core.getTaskQueuePrototypes().registerPrototype("ArrayTaskQueue", common::GenericFactory<msge::ArrayTaskQueue>::proto());   
    }
    catch (const std::runtime_error& e)
    {
        LOG(ERROR) << "Error registering prototype: " << e.what();
    }
    return names;
}

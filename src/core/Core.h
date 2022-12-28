#pragma once

#include <array>
#include <filesystem>
#include <functional>
#include <glog/logging.h>
#include <iostream>
#include <map>

#include <scenes/BaseScene.h>
#include <FactoryRegistry.h>

#include <future>
#include <string>
#include <vector>


namespace common
{
template <class PluginBaseClass, class PluginInfoType>
class PluginManager;
}

namespace msge
{

class BaseEntityVisitor;
class CoreConfig;
class AbstractScheduler;
class AbstractTaskQueue;
class Core;
class FrameStamp;

namespace plugins
{
class PluginRegistry;
class CorePluginInterface;
class CorePluginInfo;
} // namespace plugins

using CorePluginManager = common::PluginManager<msge::plugins::CorePluginInterface, msge::plugins::CorePluginInfo>;
using SchedulerPrototypes = common::GenericFactory<msge::AbstractScheduler>;
using TaskQueuePrototypes = common::GenericFactory<msge::AbstractTaskQueue>;
class Core
{
public:
    using CommandLineArgs = std::vector<std::string_view>;

    explicit Core(const CoreConfig& config, const CommandLineArgs&);
    ~Core();
    /**
     * Initialize logging framework. Will be called by the Core constructor, but can also be called in contexts without a core reference.
     */
    static void initializeLogging(const CommandLineArgs& cmdLineArgs);
    /**
     * Convert command-line arguments into a internal representation.
     */
    static CommandLineArgs makeCommandLineArgs(int argc, char** argv);
    /**
     * Setup facilities using the configuration
     */
    auto& getPluginRegistry() const { return *pluginRegistry; }

    auto& getScene(std::string_view name) const { return *rootScenes.at(name); }

    /**
     * Get the registry that holds all scheduler prototypes
     */
    auto& getSchedulerPrototypes() { return schedulerPrototypes; }
    /**
     * Get the registry that holds all scheduler taskQueue prototypes
     */
    auto& getTaskQueuePrototypes() { return taskQueuePrototypes; }
   

    //#TODO: move the task related functions into an interface
    // for now, adds a scheduled function
    void addTask(std::string_view name, std::function<void(const FrameStamp&)>&& f);

    std::future<void> start();

    void stop();


private:
    void setup(const CoreConfig& config, const CommandLineArgs& args);

    std::unique_ptr<CorePluginManager>            pluginManager;
    std::unique_ptr<plugins::PluginRegistry>      pluginRegistry;
    std::map<SceneId, std::unique_ptr<BaseScene>> rootScenes;
    //#TODO: coerce scheduler prototypes into a separate registry
    SchedulerPrototypes                           schedulerPrototypes;
    TaskQueuePrototypes                           taskQueuePrototypes;
    
    std::unique_ptr<AbstractScheduler>            scheduler;
    std::shared_ptr<AbstractTaskQueue>            taskQueue;
};


} // namespace msge
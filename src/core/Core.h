#pragma once

#include <array>
#include <filesystem>
#include <glog/logging.h>
#include <iostream>
#include <map>
#include <scenes/BaseScene.h>
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

namespace plugins
{
class PluginRegistry;
class CorePluginInterface;
class CorePluginInfo;
} // namespace plugins
using CorePluginManager = common::PluginManager<msge::plugins::CorePluginInterface, msge::plugins::CorePluginInfo>;

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

private:
    void setup(const CoreConfig& config, const CommandLineArgs& args);

    std::unique_ptr<CorePluginManager>            pluginManager;
    std::unique_ptr<plugins::PluginRegistry>      pluginRegistry;
    std::map<SceneId, std::unique_ptr<BaseScene>> rootScenes;
};


} // namespace msge
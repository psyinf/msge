#pragma once

#include <glog/logging.h>

#include <array>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace common
{
template <class PluginBaseClass, class PluginInfoType>
class PluginManager;
}
namespace msge{

class BaseEntityVisitor;

namespace plugins
{
class PluginRegistry;
class CorePluginInterface;
class CorePluginInfo;
}
using CorePluginManager = common::PluginManager<msge::plugins::CorePluginInterface, msge::plugins::CorePluginInfo>;

class Core
{
public:
    struct Config
    {
        std::string plugins_path = "plugins";
    };

    using CommandLineArgs = std::vector<std::string_view>; 

    explicit Core(const Config& config, const CommandLineArgs&);
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

private:
    void                                     setup(const Config& config, const CommandLineArgs& args);

      std::unique_ptr<CorePluginManager>       pluginManager;
    std::unique_ptr<plugins::PluginRegistry> pluginRegistry;
  
     
};



}
#pragma once

#include <glog/logging.h>

#include <array>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>


namespace msge{

class BaseEntityVisitor;

namespace plugins
{
class PluginRegistry;
}

class Core
{
    struct Config
    {
        std::string plugins_path;

    };

public:
    Core();
    ~Core();
    /**
     * Initialize logging framework. Should be done as early as possible. 
     */
    static void initializeLogging(const std::vector<std::string_view>& cmdLineArgs);
    /**
     * Setup facilities using the configuration
     */
    void setup(const Config& config);

	auto& getPluginRegistry() const { return *pluginRegistry; }

private:
    std::unique_ptr<plugins::PluginRegistry> pluginRegistry;
     
};



}
#pragma once

#include <glog/logging.h>

#include <array>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace msge{



class Core
{
    struct Config
    {
        std::string plugins_path;

    };
    static constexpr std::array<std::uint16_t, 3> inlineStaticVar = {0u,1u,0};
    
public:
    /**
     * Initialize logging framework. Should be done as early as possible. 
     */
    static void initializeLogging(const std::vector<std::string_view>& cmdLineArgs);
    /**
     * Setup facilities using the configuration
     */
    void setup(const Config& config);
     
};



}
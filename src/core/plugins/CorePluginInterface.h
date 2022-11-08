#pragma once

#include <plugins/PluginBase.h>



namespace msge::plugins
{
class PluginRegistry;

class CorePluginInfo : public common::PluginInfo
{
};

class CorePluginInterface : public common::PluginBase
{
public:
    explicit CorePluginInterface(const std::string& plugin_file_path);

    bool registerPlugin(PluginRegistry& core) const;

private:
    std::function<void(PluginRegistry&)> registerPluginFn;


    
};
} // namespace msge::plugin
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

    __declspec(dllexport) bool registerPlugin(PluginRegistry& core);

private:
    std::function<int(PluginRegistry&)> registerPluginFn;


    
};
} // namespace msge::plugin
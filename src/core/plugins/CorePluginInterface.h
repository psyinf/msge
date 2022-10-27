#pragma once

#include <plugins/PluginBase.h>



namespace msge::plugin
{
class PluginRegistry;

class CorePluginInterface : public common::PluginBase
{
public:
    explicit CorePluginInterface(const std::string& plugin_file_path);

    __declspec(dllexport) bool registerPlugin(PluginRegistry& core);

private:
    std::function<int(PluginRegistry&)> registerPluginFn;


    
};
} // namespace msge::plugin
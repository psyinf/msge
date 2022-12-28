#pragma once

#include <plugins/PluginBase.h>


namespace msge
{
    class Core;
}

namespace msge::plugins
{


class CorePluginInfo : public common::PluginInfo
{
};

class CorePluginInterface : public common::PluginBase
{
public:
    explicit CorePluginInterface(const std::string& plugin_file_path);

    bool registerPlugin(Core& core) const;

private:
    std::function<void(Core&)> registerPluginFn;
};
} // namespace msge::plugins
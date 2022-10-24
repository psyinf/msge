#pragma once

#include "buildInfo.h"
#include "strings/StringTools.h"

#include <filesystem>
#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

namespace common
{


template <class PluginBaseClass, class PluginInfoType>
class PluginManager
{
    using PluginBasePtr = std::shared_ptr<PluginBaseClass>;
    using PluginMap     = std::map<PluginInfoType, PluginBasePtr>;

public:
    PluginManager()          = default;
    virtual ~PluginManager() = default;

    PluginBasePtr makeInstance(const std::filesystem::directory_entry& entry) const
    {
        return std::make_shared<PluginBaseClass>(entry.path().string());
    }

    void scanForPlugins(const std::string& path, const std::vector<std::string>& filters)
    {
        std::ranges::for_each(
            filters, [](const auto& filter) { scanForPlugins(path, filter); });
    }

    size_t scanForPlugins(const std::string& path, const std::string& filter = "*.dll")
    {
        size_t num_loaded = 0;
        LOG(INFO) << "Scanning for plug-ins in :" << std::quoted(path);

        for (auto& p : std::filesystem::directory_iterator(path)) /*get directory */
        {
            auto file_path       = p.path().filename().string();
            auto file_path_noext = p.path().filename().replace_extension("").string();
            file_path_noext | std::ranges::views::transform([](auto c) { return std::toupper(c); });

            if (!Strings::matchesWildCard(file_path, filter))
            {
                VLOG(1) << "skipping non matching plugin: " << quote(file_path);
                continue;
            }
            else if (!file_path_noext.ends_with("_d") && isDebug())
            {
                VLOG(1) << "skipping non-debug plugin: " << quote(file_path_noext);
                continue;
            }
            else if (file_path_noext.ends_with("_d") && !isDebug())
            {
                VLOG(1) << "skipping debug plugin: " << quote(file_path_noext);
                continue;
            }
            else
            {
                try
                {
                    auto           plugin = makeInstance(p);
                    PluginInfoType plugin_info;
                    plugin->getInfo(plugin_info);
                    if (!mPlugins.count(plugin_info))
                    {
                        LOG(INFO) << std::format("Found plugin {} [{}]", file_path, plugin_info.name);
                        mPlugins[plugin_info] = plugin;
                        ++num_loaded;
                    }
                    else
                    {
                        LOG(WARNING) << std::format("Skipping plugin {} [{}], already registered.", file_path, plugin_info.name);
                    }
                }
                catch (const std::exception& e)
                {
                    LOG(ERROR) << std::format("Error loading plugin {}: {}", p.path().string(), e.what());
                }
            }
        }
        return num_loaded;
    }


    PluginBasePtr getPlugin(const std::string& plugin_name)
    {
        PluginInfoType plugin_info;
        // plugin info type at least needs a key type string
        plugin_info.name = plugin_name;
        if (mPlugins.count(plugin_info))
        {
            return (mPlugins[plugin_info]);
        }
    }

    auto getPluginList() -> PluginMap
    {
        return mPlugins;
    }

private:
    PluginMap mPlugins;
};


} // namespace common
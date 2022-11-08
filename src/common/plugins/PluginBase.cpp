#include "PluginBase.h"

#include "glog/logging.h"

#include <array>
#include <fmt/core.h>
#include <functional>
#include <stdexcept>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

using namespace common;
std::string FormatErrorMessage(const DWORD errorCode)
{
    std::array<char, 512> message;

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        message.data(),
        message.size(),
        nullptr);

    return std::string(message.begin(), message.end());
}

//#TODO: explore modes and try to match flags to unify interface here
using Handle = void*;
Handle LoadSharedLibrary(std::string_view libraryPath, [[maybe_unused]] int iMode = 2)
{
#if defined(_MSC_VER) // Microsoft compiler
    return (void*)LoadLibraryEx(libraryPath.data(), nullptr, 0x0);
#elif defined(__linux__)
    return dlopen(sDllName.c_str(), iMode);
#endif
}


std::string getLastError()
{
#if defined(_MSC_VER) // Microsoft compiler
    DWORD error        = ::GetLastError();
    auto  last_err_str = FormatErrorMessage(error);
    last_err_str.append(" ( ");
    last_err_str.append(std::to_string(error));
    last_err_str.append(" )");
    return last_err_str;
#elif __linux__
    char* error = dlerror();
    return std::string(error);
#endif
}



PLUGIN_API
PluginBase::PluginBase(const std::string& path)
    : path(path)
{
    auto handle = LoadSharedLibrary(path);

    if (!handle)
    {
        auto last_err_str = getLastError();
        throw std::invalid_argument(fmt::format("Could not load '{}'.\nError reported: {}", path, last_err_str));
    }
    // TODO:move to generic list or use introspection
    getInfoFunction = bindFunction<void, PluginInfo&>(handle, std::string("getInfo"));
    if (!getInfoFunction)
    {
        reportMissingInterface(path, "getInfo");
    }

    dllHandle = handle;
}

void PluginBase::reportMissingInterface(const std::string& path, const std::string& name) const
{
    throw std::invalid_argument(fmt::format("Plugin at '{}' is not a valid plugin (Missing '{}' interface)", path, name));
}

PLUGIN_API void PluginBase::getInfo(PluginInfo& info) const
{
    getInfoFunction(info);
}

PLUGIN_API PluginBase::~PluginBase()
{

    if (dllHandle.has_value())
    {
        PluginInfo info;
        getInfo(info);
        ::FreeLibrary(std::any_cast<HMODULE>(dllHandle));
    }
}

void* PluginBase::_getFunction(const DLLHandle& handle, std::string_view name)
{
#if defined(_MSC_VER) // Microsoft compiler
    return ::GetProcAddress(std::any_cast<HINSTANCE>(getHandle()), name.data());
#elif __linux__
    return dlsym(handle, name.data());
#endif
}

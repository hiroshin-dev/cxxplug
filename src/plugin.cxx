///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include "cxxplug/plugin.hxx"

#include "cxxlog/cxxlog.hxx"
#include "version/version.hxx"

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif  // _WIN32

namespace {

#ifdef _WIN32

void* load_library(const char *path) {
  void *handle = reinterpret_cast<void*>(LoadLibraryA(path));
  if (handle == nullptr) {
    CXXLOG_E << "LoadLibraryA: `" << path << "`, error " << GetLastError();
  }
  return handle;
}

void* get_symbol_address(void *handle, const char *symbol) {
  void *address = reinterpret_cast<void*>(
      GetProcAddress(reinterpret_cast<HMODULE>(handle), symbol));
  if (address == nullptr) {
    CXXLOG_E << "GetProcAddress: `" << symbol << "`, error " << GetLastError();
  }
  return address;
}

void unload_library(void *handle) {
  FreeLibrary(reinterpret_cast<HMODULE>(handle));
}

#else

void* load_library(const char *path) {
  dlerror();
  void *handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
  if (handle == nullptr) {
    CXXLOG_E << "dlopen: " << dlerror();
  }
  return handle;
}

void* get_symbol_address(void *handle, const char *symbol) {
  dlerror();
  void *address = dlsym(handle, symbol);
  if (address == nullptr) {
    CXXLOG_E << "dlsym: " << dlerror();
  }
  return address;
}

void unload_library(void *handle) {
  dlclose(handle);
}

#endif  // _WIN32

using EntryPoint = void (*)(void *);

const char entrypoint_symbol[] = "cxxplug_entry";

struct library_deleter {
  void operator()(void *handle) {
    if (handle != nullptr) {
      CXXLOG_V << "unload_library: " << handle;
      unload_library(handle);
    }
  }
};

}  // namespace

namespace cxxplug {

struct Plugin::impl {
  impl(void *handle, const std::string &path)
      : library(handle), library_path(path) {}

  const std::unique_ptr<void, library_deleter> library;
  const std::string library_path;
  std::map<std::string, std::unique_ptr<detail::I_FactoryBase>> factories;
};

std::unique_ptr<Plugin> Plugin::load(const std::string &library_path) {
  auto handle = load_library(library_path.c_str());
  if (handle != nullptr) {
    CXXLOG_V << "load_library: " << handle;
    auto pimpl = std::make_unique<impl>(handle, library_path);
    auto entrypoint = reinterpret_cast<EntryPoint>(
        get_symbol_address(handle, entrypoint_symbol));
    if (entrypoint != nullptr) {
      struct make_unique_enabler : public Plugin {
        make_unique_enabler(std::unique_ptr<impl> pimpl)
            : Plugin(std::move(pimpl)) {}
      };
      auto plugin = std::make_unique<make_unique_enabler>(std::move(pimpl));
      entrypoint(plugin.get());
      return plugin;
    }
  }
  return nullptr;
}

Plugin::Plugin(std::unique_ptr<impl> pimpl)
    : pimpl_(std::move(pimpl)) {
  CXXLOG_V << "Plugin.ctor: " << this;
}

Plugin::~Plugin() {
  CXXLOG_V << "Plugin.dtor: " << this;
}

std::string Plugin::library_path() const {
  return pimpl_->library_path;
}

std::vector<std::string> Plugin::get_registered_classes() const {
  std::vector<std::string> class_names;
  for (const auto &element : pimpl_->factories) {
    class_names.push_back(element.first);
  }
  return class_names;
}

const std::map<std::string, std::unique_ptr<detail::I_FactoryBase>>&
Plugin::get_factories() const {
  return pimpl_->factories;
}

const detail::I_FactoryBase* Plugin::get_factory(
    const std::string &class_name) const {
  detail::I_FactoryBase *factory = nullptr;
  const auto itr = pimpl_->factories.find(class_name);
  if (itr != pimpl_->factories.end()) {
    factory = itr->second.get();
  }
  CXXLOG_V << "get_factory: `" << class_name << "`, " << factory;
  return factory;
}

void Plugin::register_factory(
    const std::string &class_name,
    std::unique_ptr<detail::I_FactoryBase> factory) {
  CXXLOG_V << "register_factory: `" << class_name << "`, " << factory.get();
  pimpl_->factories[class_name] = std::move(factory);
}

std::unique_ptr<I_Version> get_version() {
  return std::make_unique<Version>();
}

}  // namespace cxxplug

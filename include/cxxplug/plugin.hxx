///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
/// @file
///
#ifndef CXXPLUG_PLUGIN_HXX_
#define CXXPLUG_PLUGIN_HXX_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "cxxplug/factory.hxx"
#include "cxxplug/version.hxx"

/// @brief Namespace of cxxplug
namespace cxxplug {

/// @brief A class that represents a plugin library
class Plugin {
 public:
  /// @brief Loads a plugin library
  /// @param[in] library_path - the path of the library to load
  /// @return an instance of plugin library
  static std::unique_ptr<Plugin> load(const std::string &library_path);

  /// @brief Destructor
  ~Plugin();

  /// @brief Returns the path of the library
  std::string library_path() const;

  /// @brief Returns a list of available class names
  ///
  /// This function requires RTTI.
  template<typename Base>
  std::vector<std::string> get_available_classes() const {
    std::vector<std::string> class_names;
    for (const auto &element : factories_) {
      const auto factory =
          dynamic_cast<detail::I_Factory<Base>*>(element.second.get());
      if (factory != nullptr) {
        class_names.push_back(element.first);
      }
    }
    return class_names;
  }

  /// @brief Generates an instance of the class
  /// @param[in] class_name - the name of the class to create
  /// @return an instance of the created class
  template<typename Base>
  std::unique_ptr<Base> create_instance(const std::string &class_name) const {
    return std::unique_ptr<Base>(create_raw_instance<Base>(class_name));
  }

  /// @brief Registers the class of the plugin library
  /// @param[in] class_name - the name of the class to register
  template<typename Base, typename Derived>
  void register_class(const std::string &class_name) {
    register_factory(
        class_name, std::make_unique<detail::Factory<Base, Derived>>());
  }

 private:
  struct library_deleter {
    void operator()(void *handle);
  };

  explicit Plugin(
      std::unique_ptr<void, library_deleter> library,
      const std::string &library_path);

  template<typename Base>
  Base* create_raw_instance(const std::string &class_name) const {
    const auto factory = get_factory(class_name);
    return (factory != nullptr) ?
        static_cast<const detail::I_Factory<Base>*>(factory)->create() :
        nullptr;
  }

  const detail::I_FactoryBase* get_factory(
      const std::string &class_name) const;

  void register_factory(
      const std::string &class_name,
      std::unique_ptr<detail::I_FactoryBase> factory);

 private:
  const std::unique_ptr<void, library_deleter> library_;
  const std::string library_path_;
  std::map<std::string, std::unique_ptr<detail::I_FactoryBase>> factories_;
};

/// @brief Returns the version of cxxplug
std::unique_ptr<I_Version> get_version();

/// @brief Converts a pointer to a plugin instance
Plugin& plugin_cast(void *plugin_ptr);

}  // namespace cxxplug

#endif  // CXXPLUG_PLUGIN_HXX_

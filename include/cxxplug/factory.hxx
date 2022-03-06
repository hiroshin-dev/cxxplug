///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
/// @file
///
#ifndef CXXPLUG_FACTORY_HXX_
#define CXXPLUG_FACTORY_HXX_

namespace cxxplug {
namespace detail {

class I_FactoryBase {
 public:
  virtual ~I_FactoryBase() = default;
};

template<typename Base>
class I_Factory : public I_FactoryBase {
 public:
  virtual Base* create() const = 0;
};

template<typename Base, typename Derived>
class Factory : public I_Factory<Base> {
 public:
  Base* create() const final {
    return new Derived;
  }
};

}  // namespace detail
}  // namespace cxxplug

#endif  // CXXPLUG_FACTORY_HXX_

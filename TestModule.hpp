#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: Test module that covers currently supported XRobot config syntax
constructor_args:
  - test_uint: 250
  - test_float: 1.5
  - test_bool: true
  - test_numeric_string: '123'
  - test_text: abc
  - test_enum: std::errc::permission_denied
  - test_led: '@BlinkLED_0'
  - test_struct:
      x: 1
      y: true
      z: 2.5
  - test_array:
      - 1
      - 2
      - 3
template_args:
  - enum_type: std::errc
  - value_type: int
  - count: 3
  - flag: true
required_hardware: []
depends:
  - xrobot-org/BlinkLED
=== END MANIFEST === */
// clang-format on

#include "app_framework.hpp"
#include <cstdint>
#include <system_error>
#include <type_traits>
#include "BlinkLED.hpp"
#include "libxr.hpp"

struct TestStructArg {
  int x;
  bool y;
  float z;
};

struct TestArrayArg {
  int values[3];
};

template <typename EnumType, typename ValueType, int Count, bool Flag>
class TestModule : public LibXR::Application {
 public:
  TestModule(LibXR::HardwareContainer& hw, LibXR::ApplicationManager& app,
             uint32_t test_uint, float test_float, bool test_bool,
             uint32_t test_numeric_string, const char* test_text,
             EnumType test_enum, BlinkLED& test_led, TestStructArg test_struct,
             TestArrayArg test_array) {
    UNUSED(hw);

    static_assert(std::is_same_v<EnumType, std::errc>);
    static_assert(std::is_same_v<ValueType, int>);
    static_assert(Count == 3);
    static_assert(Flag);

    LibXR::STDIO::Printf(
        "TestModule: uint=%u, float=%f, bool=%d, numstr=%u, text=%s, enum=%d, led=%p, struct={%d,%d,%f}, array={%d,%d,%d}\n",
        test_uint, test_float, test_bool, test_numeric_string, test_text,
        static_cast<int>(test_enum), &test_led, test_struct.x, test_struct.y,
        test_struct.z, test_array.values[0], test_array.values[1],
        test_array.values[2]);

    app.Register(*this);
  }

  void OnMonitor() override {
    LibXR::STDIO::Printf("TestModule: OnMonitor\n");
  }
};

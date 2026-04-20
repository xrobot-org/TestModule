#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: 测试模块 / A simple test module
constructor_args:
  - test_arg1: 250
  - test_arg2: abc
  - test_arg3: '123'
  - test_arg4: std::errc::permission_denied
  - test_arg5: '@BlinkLED_0'
  - test_arg6: 1.5
  - test_arg7: true
  - test_arg8:
      x: 1
      y: true
      z: 2.5
  - test_arg9:
      - 1
      - 2
      - 3
template_args:
  - test_temp1: std::errc
  - test_temp2: int
  - test_temp3: 3
  - test_temp4: true
required_hardware: []
depends:
  - xrobot-org/BlinkLED@master
  - xrobot-org/BlinkLED
=== END MANIFEST === */
// clang-format on

#include "app_framework.hpp"
#include <system_error>
#include "BlinkLED.hpp"
#include "libxr.hpp"

struct TestStructArg
{
  int x;
  bool y;
  float z;
};

struct TestArrayArg
{
  int values[3];
};

template <typename Type1, typename Type2, int Type3, bool Type4>
class TestModule : public LibXR::Application
{
public:
  TestModule(LibXR::HardwareContainer &hw, LibXR::ApplicationManager &app,
             uint32_t test_arg1, const char *test_arg2, uint32_t test_arg3,
             Type1 test_arg4, BlinkLED &test_arg5, float test_arg6,
             bool test_arg7, TestStructArg test_arg8, TestArrayArg test_arg9)
  {
    static_assert(std::is_same_v<Type1, std::errc>);
    static_assert(std::is_same_v<Type2, int>);
    static_assert(Type3 == 3);
    static_assert(Type4);

    LibXR::STDIO::Printf("TestModule: test_arg1=%d, test_arg2=%s, test_arg3=%d, test_arg4=%d, test_arg5=%p, test_arg6=%f, test_arg7=%d, test_arg8={%d,%d,%f}, test_arg9={%d,%d,%d}\n",
                         test_arg1, test_arg2, test_arg3, test_arg4, &test_arg5, test_arg6, test_arg7,
                         test_arg8.x, test_arg8.y, test_arg8.z,
                         test_arg9.values[0], test_arg9.values[1], test_arg9.values[2]);
    
    app.Register(*this);
  }

  void OnMonitor() override
  {
    LibXR::STDIO::Printf("TestModule: OnMonitor\n");
  }

private:
};

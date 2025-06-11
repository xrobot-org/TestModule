#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: 测试模块 / A simple test module
constructor_args:
  - test_arg1: 250
  - test_arg2: abc
  - test_arg3: ABCD
  - test_arg4: std::errc::permission_denied
  - test_arg5: '@BlinkLED_0'
template_args:
  - test_temp1: std::errc
  - test_temp2: int
  - test_temp3: 3
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

template <typename Type1, typename Type2, int Type3>
class TestModule : public LibXR::Application
{
public:
  TestModule(LibXR::HardwareContainer &hw, LibXR::ApplicationManager &app,
             uint32_t test_arg1, const char *test_arg2, const char *test_arg3,
             Type1 test_arg4, BlinkLED &test_arg5)
  {
    static_assert(std::is_same_v<Type1, std::errc>);
    static_assert(std::is_same_v<Type2, int>);
    static_assert(Type3 == 3);

    LibXR::STDIO::Printf("TestModule: test_arg1=%d, test_arg2=%s, test_arg3=%s, test_arg4=%d, test_arg5=%p\n",
                         test_arg1, test_arg2, test_arg3, test_arg4, &test_arg5);
    
    app.Register(*this);
  }

  void OnMonitor() override
  {
    LibXR::STDIO::Printf("TestModule: OnMonitor\n");
  }

private:
};

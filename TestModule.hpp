#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: XRobot 工具链的测试夹具模块 / Test fixture Module for the XRobot tool chain
depends:
- id: xrobot-org/BlinkLED
  ref: same-or-dev
=== END MANIFEST === */
// clang-format on

#include <cstdint>
#include <system_error>

#include "BlinkLED.hpp"
#include "libxr.hpp"

/**
 * @brief 聚合结构体构造参数的测试类型。
 *        Test type for an aggregate struct constructor argument.
 */
struct TestStructArg
{
  int x;    ///< 整数字段 Integer field
  bool y;   ///< 布尔字段 Bool field
  float z;  ///< 浮点字段 Float field
};

/**
 * @brief 数组结构体构造参数的测试类型。
 *        Test type for an array struct constructor argument.
 */
struct TestArrayArg
{
  int values[3];  ///< 三个整数 Three integers
};

/**
 * @brief XRobot 工具链的测试夹具，模板参数须为 std::errc、int、3、true。
 *        Test fixture for the XRobot tool chain; the template arguments must be
 *        std::errc, int, 3 and true.
 *
 * @tparam Type1 须为 std::errc。
 *               Must be std::errc.
 * @tparam Type2 须为 int。
 *               Must be int.
 * @tparam Type3 须为 3。
 *               Must be 3.
 * @tparam Type4 须为 true。
 *               Must be true.
 */
template <typename Type1, typename Type2, int Type3, bool Type4>
class TestModule
{
 public:
  /**
   * @brief 构造 TestModule，检查模板参数并打印全部构造参数。
   *        Construct TestModule, check the template arguments and print every
   *        constructor argument.
   *
   * @param test_arg5 BlinkLED 实例，打印其地址。
   *                  BlinkLED instance whose address is printed.
   * @param test_arg1 整数参数。
   *                  Integer argument.
   * @param test_arg2 字符串参数。
   *                  String argument.
   * @param test_arg3 整数参数。
   *                  Integer argument.
   * @param test_arg4 枚举参数，类型为 Type1。
   *                  Enum argument of type Type1.
   * @param test_arg6 浮点参数。
   *                  Float argument.
   * @param test_arg7 布尔参数。
   *                  Bool argument.
   * @param test_arg8 聚合结构体参数。
   *                  Aggregate struct argument.
   * @param test_arg9 数组结构体参数。
   *                  Array struct argument.
   */
  TestModule(
      BlinkLED& test_arg5,
      uint32_t test_arg1 = 250,
      const char* test_arg2 = "abc",
      uint32_t test_arg3 = 123,
      Type1 test_arg4 = std::errc::permission_denied,
      float test_arg6 = 1.5f,
      bool test_arg7 = true,
      TestStructArg test_arg8 = {.x = 1, .y = true, .z = 2.5},
      TestArrayArg test_arg9 = {.values = {1, 2, 3}})
  {
    static_assert(std::is_same_v<Type1, std::errc>);
    static_assert(std::is_same_v<Type2, int>);
    static_assert(Type3 == 3);
    static_assert(Type4);

    LibXR::STDIO::Printf<
        "TestModule: test_arg1=%u, test_arg2=%s, test_arg3=%u, test_arg4=%d, "
        "test_arg5=%x, test_arg6=%f, test_arg7=%u, test_arg8={%d,%u,%f}, "
        "test_arg9={%d,%d,%d}\n">(
        test_arg1, test_arg2, test_arg3, test_arg4,
        static_cast<unsigned>(reinterpret_cast<std::uintptr_t>(&test_arg5)), test_arg6,
        static_cast<unsigned>(test_arg7), test_arg8.x, static_cast<unsigned>(test_arg8.y),
        test_arg8.z, test_arg9.values[0], test_arg9.values[1], test_arg9.values[2]);
  }

  /**
   * @brief 监控回调：打印 `TestModule: OnMonitor`。
   *        Monitor callback: print `TestModule: OnMonitor`.
   */
  void OnMonitor() { LibXR::STDIO::Printf<"TestModule: OnMonitor\n">(); }

 private:
};

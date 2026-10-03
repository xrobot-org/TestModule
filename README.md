# TestModule

XRobot 工具链的测试夹具模块，覆盖模板参数和各类构造参数 / Test fixture Module for the XRobot tool chain, covering template parameters and the constructor argument kinds

## 1. 模块作用 / Purpose

TestModule 提供一个带模板参数的 Module，构造参数涵盖整数、字符串、枚举、浮点、布尔、聚合结构体、数组结构体以及对另一个 Module 实例的引用。

构造时，TestModule 用 `static_assert` 要求模板参数为 `std::errc, int, 3, true`，然后通过 `LibXR::STDIO::Printf` 打印全部构造参数，其中 `test_arg5` 打印为 `BlinkLED` 实例的地址。`OnMonitor()` 在每次 monitor 循环中打印 `TestModule: OnMonitor`。

TestModule is a Module with template parameters whose constructor arguments cover integer, string, enum, float, bool, aggregate struct, array struct and a reference to another Module instance.

Upon construction, TestModule uses `static_assert` to require the template arguments `std::errc, int, 3, true`, then prints every constructor argument through `LibXR::STDIO::Printf`, with `test_arg5` printed as the address of the `BlinkLED` instance. `OnMonitor()` prints `TestModule: OnMonitor` on every monitor cycle.

## 2. 构造接口 / Constructor

```cpp
template <typename Type1, typename Type2, int Type3, bool Type4>
class TestModule;

TestModule(BlinkLED& test_arg5,
           uint32_t test_arg1 = 250,
           const char* test_arg2 = "abc",
           uint32_t test_arg3 = 123,
           Type1 test_arg4 = std::errc::permission_denied,
           float test_arg6 = 1.5f,
           bool test_arg7 = true,
           TestStructArg test_arg8 = {.x = 1, .y = true, .z = 2.5},
           TestArrayArg test_arg9 = {.values = {1, 2, 3}});
```

模板参数：`Type1`、`Type2` 为类型，`Type3` 为 `int`，`Type4` 为 `bool`，取值为 `std::errc`、`int`、`3`、`true`。

依赖：

- `test_arg5`：`BlinkLED` 实例，填写该实例的 id。

配置参数：

- `test_arg1`：`uint32_t`，默认 250。
- `test_arg2`：`const char*`，默认 `"abc"`。
- `test_arg3`：`uint32_t`，默认 123。
- `test_arg4`：`Type1`，默认 `std::errc::permission_denied`。
- `test_arg6`：`float`，默认 1.5。
- `test_arg7`：`bool`，默认 `true`。
- `test_arg8`：`TestStructArg { int x; bool y; float z; }`，默认 `{.x = 1, .y = true, .z = 2.5}`。
- `test_arg9`：`TestArrayArg { int values[3]; }`，默认 `{.values = {1, 2, 3}}`。

Template parameters: `Type1` and `Type2` are types, `Type3` is an `int` and `Type4` is a `bool`, with the values `std::errc`, `int`, `3`, `true`.

Dependencies:

- `test_arg5`: a `BlinkLED` instance, set to the id of that instance.

Configuration parameters:

- `test_arg1`: `uint32_t`, default 250.
- `test_arg2`: `const char*`, default `"abc"`.
- `test_arg3`: `uint32_t`, default 123.
- `test_arg4`: `Type1`, default `std::errc::permission_denied`.
- `test_arg6`: `float`, default 1.5.
- `test_arg7`: `bool`, default `true`.
- `test_arg8`: `TestStructArg { int x; bool y; float z; }`, default `{.x = 1, .y = true, .z = 2.5}`.
- `test_arg9`: `TestArrayArg { int values[3]; }`, default `{.values = {1, 2, 3}}`.

## 3. Topic

无 / None

## 4. 配置示例 / Configuration Example

`xrobot instance add` 写入 `xrobot-org/BlinkLED` 与 `xrobot-org/TestModule` 的实例（`template_args` 填写为上述取值），`test_arg5` 填写为 `BlinkLED` 实例的 id，`led` 填写为 BSP 通过 `XR_REGISTER`（硬件注册）注册的 GPIO 名称：

`xrobot instance add` writes the instances of `xrobot-org/BlinkLED` and `xrobot-org/TestModule` (with `template_args` set to the values above), with `test_arg5` set to the id of the `BlinkLED` instance and `led` set to a GPIO name registered by the BSP's `XR_REGISTER` (Registration):

```yaml
modules:
  - module: xrobot-org/BlinkLED
    id: blink_led
    args:
      - led: LED_B
      - blink_cycle: 250
  - module: xrobot-org/TestModule
    id: testmodule_0
    template_args:
      - std::errc
      - int
      - 3
      - true
    args:
      - test_arg5: blink_led
      - test_arg1: 250
      - test_arg2: "abc"
      - test_arg3: 123
      - test_arg4: std::errc::permission_denied
      - test_arg6: 1.5f
      - test_arg7: true
      - test_arg8:
          x: 1
          y: true
          z: 2.5
      - test_arg9:
          values: '{1, 2, 3}'
```

`examples/xrobot_constexpr.yaml` 是同样两个实例的完整配置，参数取自项目级 `constexprs`，生成为命名空间 `TestModuleConstexpr` 中的 `inline constexpr` 值。

`examples/xrobot_constexpr.yaml` is a complete configuration of the same two instances whose arguments come from project-level `constexprs`, generated as `inline constexpr` values in the namespace `TestModuleConstexpr`.

## 5. 依赖与硬件 / Dependencies and Hardware

依赖：

- `xrobot-org/BlinkLED`：`test_arg5` 的类型。
- LibXR。

硬件：`BlinkLED` 使用的一个 LED GPIO。

Dependencies:

- `xrobot-org/BlinkLED`: the type of `test_arg5`.
- LibXR.

Hardware: the LED GPIO used by `BlinkLED`.

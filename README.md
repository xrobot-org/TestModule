# TestModule

测试模块：XRobot 工具链的测试夹具，覆盖模板参数和各类构造参数（整数、字符串、枚举、
浮点、布尔、聚合结构体、数组结构体以及对另一个模块实例的引用）。

A simple test module: a fixture for the XRobot tool chain that exercises template
parameters and the constructor argument kinds (integer, string, enum, float, bool,
aggregate struct, array struct, and a reference to another Module instance).

## 行为 / Behaviour

- 构造时用 `static_assert` 要求模板参数恰好为 `std::errc, int, 3, true`，然后通过
  `LibXR::STDIO::Printf` 打印全部构造参数（`test_arg5` 打印为 `BlinkLED` 实例的地址）。
- `OnMonitor()` 在每次 monitor 循环中打印 `TestModule: OnMonitor`。

- The constructor `static_assert`s that the template arguments are exactly
  `std::errc, int, 3, true`, then prints every constructor argument through
  `LibXR::STDIO::Printf` (`test_arg5` is printed as the address of the `BlinkLED`
  instance).
- `OnMonitor()` prints `TestModule: OnMonitor` on every monitor cycle.

## 依赖 / Dependencies

- `xrobot-org/BlinkLED`：`test_arg5` 引用的模块类型。/ The Module type referenced by
  `test_arg5`.

## 构造接口 / Constructor

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

模板参数 / Template parameters: `Type1`、`Type2`（类型 / types）、`Type3`（`int`）、
`Type4`（`bool`），必须为 `std::errc`、`int`、`3`、`true`。/ must be `std::errc`,
`int`, `3`, `true`.

依赖 / Dependencies:

- `test_arg5`：一个 `BlinkLED` 实例（填写其实例 id）。/ A `BlinkLED` instance (its
  instance id).

配置 / Configuration:

- `test_arg1`：`uint32_t`，默认 250。/ default 250.
- `test_arg2`：`const char*`，默认 `"abc"`。/ default `"abc"`.
- `test_arg3`：`uint32_t`，默认 123。/ default 123.
- `test_arg4`：`Type1`，默认 `std::errc::permission_denied`。/ default
  `std::errc::permission_denied`.
- `test_arg6`：`float`，默认 1.5。/ default 1.5.
- `test_arg7`：`bool`，默认 `true`。/ default `true`.
- `test_arg8`：`TestStructArg { int x; bool y; float z; }`，默认
  `{.x = 1, .y = true, .z = 2.5}`。/ default `{.x = 1, .y = true, .z = 2.5}`.
- `test_arg9`：`TestArrayArg { int values[3]; }`，默认 `{.values = {1, 2, 3}}`。/
  default `{.values = {1, 2, 3}}`.

## 使用 / Use

```sh
xrobot module add xrobot-org/TestModule
xrobot setup
xrobot instance add xrobot-org/BlinkLED
xrobot instance add xrobot-org/TestModule
```

`xrobot instance add` 在 `User/xrobot.yaml` 中写入一个实例，依赖项留空，默认值按源码写出；
把 `test_arg5` 填为前面列出的 `BlinkLED` 实例的 id（`xrobot-org/BlinkLED` 通过
`depends` 自动拉取）：
`xrobot instance add` writes an instance to `User/xrobot.yaml` with empty
dependencies and the source defaults; set `test_arg5` to the id of a `BlinkLED`
instance listed earlier (`xrobot-org/BlinkLED` is pulled in through `depends`):

```yaml
modules:
  - module: xrobot-org/BlinkLED
    id: blinkled_0
    args:
      - led: led_b
      - blink_cycle: '250'
  - module: xrobot-org/TestModule
    id: testmodule_0
    template_args:
      - std::errc
      - int
      - '3'
      - 'true'
    args:
      - test_arg5: blinkled_0
      - test_arg1: '250'
      - test_arg2: '"abc"'
      - test_arg3: '123'
      - test_arg4: std::errc::permission_denied
      - test_arg6: 1.5f
      - test_arg7: 'true'
      - test_arg8:
          x: '1'
          y: 'true'
          z: '2.5'
      - test_arg9:
          values:
            - '1'
            - '2'
            - '3'
```

BSP 侧（`BlinkLED` 使用的 GPIO）/ BSP side (the GPIO used by `BlinkLED`):

```cpp
XR_REGISTER(led_b, LibXR::GPIO);
```

填好后再次运行 `xrobot setup`，生成 `User/xrobot_main.hpp`。
Run `xrobot setup` again to generate `User/xrobot_main.hpp`.

`xrobot module show .`（在本仓库中）或 `xrobot module show Modules/xrobot-org/TestModule`
（在 BSP 中）打印 manifest 和当前的构造函数。
`xrobot module show .` in this repository, or
`xrobot module show Modules/xrobot-org/TestModule` in a BSP, prints the manifest
and the current constructor.

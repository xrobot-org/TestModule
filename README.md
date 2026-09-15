# TestModule

## Static assembly source line

This source line uses explicit C++ constructor dependencies and ordered instance
arguments. Inspect the current primary header with `xrobot_mod_parser --path .`;
its declarations, not old manifest/config examples, define the interface.
Historical HardwareContainer/ApplicationManager examples below apply only to the
older dynamic source tags. Device/protocol descriptions remain relevant.
See the XRobot [migration guide](https://github.com/xrobot-org/XRobot/blob/dev/MIGRATION.md).
Compilation is not hardware validation; retain version-specific board evidence.


测试模块 / A simple test module

## Required Hardware
None

## Constructor Arguments
- `test_arg1`: 250
- `test_arg2`: abc
- `test_arg3`: '123'
- `test_arg4`: std::errc::permission_denied
- `test_arg5`: @BlinkLED_0
- `test_arg6`: 1.5
- `test_arg7`: true
- `test_arg8`: { x: 1, y: true, z: 2.5 }
- `test_arg9`: [1, 2, 3]

## Template Arguments
- `test_temp1`: std::errc
- `test_temp2`: int
- `test_temp3`: 3
- `test_temp4`: true

## Examples / 示例
- `examples/xrobot_constexpr.yaml`: `xrobot 0.2.10` 的项目级 `constexpr` 配置示例 / Example project-level `constexpr` config for `xrobot 0.2.10`

## Depends
- xrobot-org/BlinkLED@master
- xrobot-org/BlinkLED

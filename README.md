# TestModule

Test module for exercising the currently supported XRobot config syntax.

## Required Hardware
None

## Constructor / Template Syntax
- Integer, float, boolean, plain string, numeric-string token, scoped enum name, and `@instance` reference are encoded in `TestModule.hpp`.
- Mapping and list aggregate arguments are encoded in `TestModule.hpp`.
- Raw string type names plus non-type integer / boolean template arguments are encoded in `TestModule.hpp`.

## Examples
- `xrobot_add_mod TestModule` uses the manifest defaults declared in `TestModule.hpp`.
- `examples/xrobot_constexpr.yaml` shows project-level `constexpr_includes`, `constexprs`, and `{constexpr: Name}` usage with this module.

## Depends
- xrobot-org/BlinkLED

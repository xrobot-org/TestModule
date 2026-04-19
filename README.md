# TestModule

Test module that covers the currently supported XRobot config syntax.

## Covered Syntax
- Integer literal constructor argument
- Float literal constructor argument
- Boolean literal constructor argument
- Numeric string constructor argument (`'123'` -> raw numeric token)
- Plain string constructor argument
- Scoped-name constructor argument (`std::errc::permission_denied`)
- Instance reference constructor argument (`@BlinkLED_0`)
- Mapping aggregate constructor argument
- List aggregate constructor argument
- Raw string template arguments (`std::errc`, `int`)
- Non-type integer template argument (`3`)
- Non-type boolean template argument (`true`)

## Required Hardware
None

## Depends
- xrobot-org/BlinkLED

## Example
- Manifest-driven defaults are encoded in `TestModule.hpp` and are meant to be exercised through `xrobot_add_mod TestModule`.
- A project-level `constexpr` sample config is provided at `examples/xrobot_constexpr.yaml`.
- CI covers both paths so the checked-in syntax stays aligned with the currently released `xrobot` generator.

#pragma once

class CompareWithZero
{
public:
  static float constexpr kEps = 1e-5;
  static float FloatIsEps(float v) noexcept { return (fabs(v) <= kEps) ? 0.0 : v; }
  static bool EqualWithEps(float v) noexcept { return fabs(v) < kEps; }
  static bool EqualWithEps(float v1, float v2) noexcept { return fabs(v1 - v2) < kEps; }
};
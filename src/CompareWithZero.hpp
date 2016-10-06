#pragma once


class CompareWithZero 
{
public:
  static float constexpr kEps = 1e-5;
  static float EqualWithEps(float v)
  {
    return (v <= kEps) ? 0.0 : v;
  }
  static bool EqualWithEps(float v1, float v2) 
  {
    return fabs(v1 - v2) < kEps;
  }
};
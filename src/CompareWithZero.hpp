#pragma once


class CompareWithZero 
{

protected:
  float const kEps = 1e-5;
  virtual float EqualWithEps(float v) const 
  {
    return (v <= kEps) ? 0.0 : v;
  }
  virtual bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }
};
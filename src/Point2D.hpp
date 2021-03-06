#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include <exception>

#include "CompareWithZero.hpp"

class Point2D
{
public:
  Point2D() = default;
  Point2D(Point2D const & obj) noexcept : m_x(obj.m_x), m_y(obj.m_y) {};
  Point2D(float x, float y = 0.0) noexcept : m_x(x), m_y(y) {};

  Point2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = {&m_x, &m_y};
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  Point2D(Point2D && obj) noexcept
  {
    std::swap(m_x, obj.m_x);
    std::swap(m_y, obj.m_y);
  }

  Point2D & operator =(Point2D && obj) noexcept
  {
    std::swap(m_x, obj.m_x);
    std::swap(m_y, obj.m_y);
    return *this;
  }

  Point2D & operator =(Point2D const & obj)
  {
    if (this == &obj) return *this;
    m_x = obj.m_x;
    m_y = obj.m_y;
    return *this;
  }

  bool operator ==(Point2D const & obj) const noexcept
  {
    return CompareWithZero::EqualWithEps(m_x, obj.m_x) && CompareWithZero::EqualWithEps(m_y, obj.m_y);
  }

  bool operator !=(Point2D const & obj) const noexcept { return !operator ==(obj); }

  bool operator <(Point2D const & obj) const noexcept
  {
    if (m_x < obj.m_x) return true;
    return m_y < obj.m_y;
  }

  friend float atan2(Point2D const & obj) { return atan2(obj.y(), obj.x()); }

  Point2D operator +(Point2D const & obj) const noexcept { return {m_x + obj.m_x, m_y + obj.m_y}; }

  Point2D operator -(Point2D const & obj) const noexcept { return {m_x - obj.m_x, m_y - obj.m_y}; }

  Point2D operator -() const noexcept { return {-m_x, -m_y}; }

  Point2D operator *(float scale) const noexcept { return {m_x * scale, m_y * scale}; }

  Point2D operator /(float scale) const
  {
    if (scale == 0) throw std::invalid_argument("division by zero");
    return {m_x / scale, m_y / scale};
  }

  Point2D & operator +=(Point2D const & obj) noexcept
  {
    m_x += obj.m_x;
    m_y += obj.m_y;
    return *this;
  }

  Point2D & operator -=(Point2D const & obj) noexcept
  {
    m_x -= obj.m_x;
    m_y -= obj.m_y;
    return *this;
  }

  Point2D & operator *=(float scale) noexcept
  {
    m_x *= scale;
    m_y *= scale;
    return *this;
  }

  Point2D & operator /=(float scale)
  {
    if (CompareWithZero::EqualWithEps(scale)) throw std::invalid_argument("division by zero");
    m_x /= scale;
    m_y /= scale;
    return *this;
  }

  float operator [](unsigned int index) const noexcept
  {
    if (index >= 2) return 0.0f;
    return index == 0 ? m_x : m_y;
  }

  Point2D & Move(Point2D const & obj) noexcept
  {
    if (this == &obj) return *this;
    m_x = obj.x();
    m_y = obj.y();
    return *this;
  }
  Point2D & Move(float x, float y) noexcept
  {
    if (CompareWithZero::EqualWithEps(m_x, x) && CompareWithZero::EqualWithEps(m_y, y)) return *this;
    m_x = x;
    m_y = y;
    return *this;
  }

  float & x() noexcept { return m_x; }
  float & y() noexcept { return m_y; }

  float const & x() const noexcept { return m_x; }
  float const & y() const noexcept { return m_y; }

  float const Length() const noexcept { return std::sqrt(m_x * m_x + m_y * m_y); }

  void Normalization()
  {
    float length = Length();
    if (CompareWithZero::EqualWithEps(length)) throw std::invalid_argument("division by zero");
    m_x /= length;
    m_y /= length;
  }

  friend Point2D GetNormal(Point2D const & obj)
  {
    Point2D point(obj);
    point.Normalization();
    return point;
  }

  struct Hash
  {
    size_t operator ()(Point2D const & p) const
    {
      auto hasher = std::hash<float>();
      return (hasher(p.x()) ^ (hasher(p.y()) << 1));
    }
  };

  friend std::ostream & operator <<(std::ostream & os, Point2D const & obj)
  {
    os << "Point 2D {" << obj.x() << ", " << obj.y() << "}";
    return os;
  }

private:
  float m_x = 0.0f, m_y = 0.0f;
};
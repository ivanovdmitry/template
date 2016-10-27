#pragma once

#include "Box2D.hpp"
#include <initializer_list>
#include <ostream>

#include "CompareWithZero.hpp"

class Ray2D
{
public:
  Ray2D() = default;
  Ray2D(Point2D const & obj1, Point2D const & obj2) noexcept : m_origin(obj1), m_direction(obj2) {}
  Ray2D(float x1, float y1, float x2, float y2) noexcept : m_origin(x1, y1), m_direction(x2, y2) {}
  Ray2D(Ray2D const & obj) noexcept : m_origin(obj.m_origin), m_direction(obj.m_direction) {}

  Ray2D(std::initializer_list<float> const & lst)
  {
    std::vector<float> v(lst.begin(), lst.end());
    while (v.size() <= 3) v.push_back(0);

    Point2D * vals[] = {&m_origin, &m_direction};
    int const count = sizeof(vals) / sizeof(vals[0]);

    auto it = v.begin();
    for (int i = 0; i < count && it != v.end(); i++, it += 2)
      *vals[i] = {CompareWithZero::FloatIsEps(*it), CompareWithZero::FloatIsEps(*(it + 1))};
  }

  Ray2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = {&m_origin, &m_direction};
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *(it);
  }

  Ray2D(Ray2D && obj) noexcept
  {
    std::swap(m_origin, obj.m_origin);
    std::swap(m_direction, obj.m_direction);
  }

  Ray2D & operator =(Ray2D && obj) noexcept
  {
    std::swap(m_origin, obj.m_origin);
    std::swap(m_direction, obj.m_direction);
    return *this;
  }

  Ray2D & operator =(Ray2D const & obj) noexcept
  {
    if (this == &obj) return *this;
    m_origin = obj.m_origin;
    m_direction = obj.m_direction;
    return *this;
  }

  Ray2D operator *(float scale) const noexcept { return {m_origin, m_direction * scale}; }

  bool operator ==(Ray2D const & obj) const noexcept { return (m_origin == obj.m_origin) && (m_direction == obj.m_direction); }

  bool operator !=(Ray2D const & obj) noexcept { return !operator ==(obj); }

  Point2D GetDirectionNormal() { return GetNormal(m_direction - m_origin); }

  Ray2D & Move(Point2D const & obj) noexcept
  {
    if (m_origin == obj) return *this;
    m_origin = obj;
    return *this;
  }

  Ray2D & Move(float x, float y) noexcept
  {
    if (CompareWithZero::EqualWithEps(m_origin.x(), x) && CompareWithZero::EqualWithEps(m_origin.y(), y))
      return *this;
    m_origin.Move(x, y);
    return *this;
  }

  friend bool Intsec(Box2D const & obj1, Ray2D const & obj2)
  {
    float arr[] = {
      atan2(obj1.LeftBottom() - obj2.Point()),
      atan2(obj1.LeftTop() - obj2.Point()),
      atan2(obj1.RightTop() - obj2.Point()),
      atan2(obj1.RightBottom() - obj2.Point())
    };

    float v = atan2(obj2.Vector());
    for (auto & i: arr)
    {
      if (v >= i)
      {
        for (auto & k : arr)
        {
          if (v <= k) return true;
        }
        return false;
      }
    }
    return false;
  }

  friend bool Intsec(Ray2D const & obj1, Box2D const & obj2) { return Intsec(obj2, obj1); }

  Point2D & Point() noexcept { return m_origin; }
  Point2D & Vector() noexcept { return m_direction; }
  Point2D const & Point() const noexcept { return m_origin; }
  Point2D const & Vector() const noexcept { return m_direction; }

  float const Length() const
  {
    Point2D temp = m_direction - m_origin;
    return temp.Length();
  }

  void Normalization()
  {
    if (CompareWithZero::EqualWithEps(Length())) throw std::invalid_argument("division by zero");
    m_direction = (m_direction - m_origin) / Length() + m_origin;
  }

  friend std::ostream & operator <<(std::ostream & os, Ray2D const & obj)
  {
    os << "Ray 2D { Origin " << obj.Point() << ", Direction " << obj.Vector() << "}";
    return os;
  }

private:
  Point2D m_origin = {0.0f, 0.0f}, m_direction = {0.0f, 0.0f};
};
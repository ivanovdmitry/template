#pragma once

#include "Point2D.hpp"
#include <cmath>
#include <initializer_list>
#include <ostream>
#include <exception>
#include <vector>

#include "CompareWithZero.hpp"

class Box2D 
{
public:
  Box2D() = default;

  Box2D(Point2D const & obj1, Point2D const & obj2 = Point2D(0.0, 0.0)) : m_min(obj1), m_max(obj2) { CheckBox(); }

  Box2D(float x1, float y1 = 0.0, float x2 = 0.0, float y2 = 0.0) noexcept : m_min(x1, y1), m_max(x2, y2) { CheckBox(); }

  Box2D(Box2D const & obj) : m_min(obj.m_min), m_max(obj.m_max) {}

  Box2D(std::initializer_list<float> const & lst)
  {
    std::vector<float> v (lst.begin(), lst.end());
    while (v.size() <= 3) v.push_back(0);

    Point2D * vals[] = { &m_min, &m_max };
    int const count = sizeof(vals) / sizeof(vals[0]);

    auto it = v.begin();
    for (int i = 0; i < count && it != v.end(); i++, it += 2)
      *vals[i] = { CompareWithZero::EqualWithEps(*it), CompareWithZero::EqualWithEps(*(it + 1)) };
    CheckBox();
  }

  Box2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_min, &m_max };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, it ++)
      *vals[i] =  *(it);
    CheckBox();
  }

  Box2D(Box2D && obj) noexcept
  {
    std::swap(m_min, obj.m_min);
    std::swap(m_max, obj.m_max);
  }

  Box2D & operator = (Box2D && obj) noexcept
  {
    std::swap(m_min, obj.m_min);
    std::swap(m_max, obj.m_max);
    return *this;
  }
  
  Box2D & operator = (Box2D const & obj) noexcept
  {
    if (this == &obj) return *this;
    m_min = obj.m_min;
    m_max = obj.m_max;
    return *this;
  }

  bool operator == (Box2D const & obj) const noexcept { return (m_min == obj.m_min) && (m_max == obj.m_max); }

  bool operator != (Box2D const & obj) const noexcept { return !operator==(obj); }

  Point2D operator [] (unsigned int index) const 
  {
    if (index >= 2)  throw std::invalid_argument( "Reference to non-existing object" );
    return index == 0 ? m_min : m_max;
  }

  Point2D Centre () const noexcept { return (m_min + m_max) / 2.0; }

  friend bool Intsec (Box2D const & obj1, Box2D const & obj2)
  {
    return (obj1.m_max.y() >= obj2.m_min.y()) && (obj1.m_min.y() <= obj2.m_max.y()) && 
      (obj1.m_max.x() >= obj2.m_min.x()) && (obj1.m_min.x() <= obj2.m_max.x());    
  }

  Box2D & Move(Point2D const & obj)
  {
    if (Centre() == obj) return *this;

    Point2D point(obj - Centre());
    m_min += point;
    m_max += point;
    return *this;
  }
  
  Box2D & Move(float x, float y) noexcept
  {
    if ( CompareWithZero::EqualWithEps(Centre().x(),x) && CompareWithZero::EqualWithEps(Centre().y(), y)) return *this;
    Point2D point(x - Centre().x(), y - Centre().y());
    m_min += point;
    m_max += point;
    return *this;
  }

  Point2D const & LeftBottom() const noexcept { return m_min; }

  Point2D const & RightTop() const noexcept { return m_max; }

  Point2D const LeftTop() const noexcept
  {
    Point2D point = { m_min.x(), m_max.y() };
    return point;
  }

  Point2D const RightBottom() const noexcept
  {
    Point2D point = { m_max.x(), m_min.y() };
    return point;
  }

  friend std::ostream & operator << (std::ostream & os, Box2D const & obj)
  {
    os << "Box 2D {Left Bottom " << obj.LeftBottom() << ", Right Top " << obj.RightTop() << "}";
    return os;
  }

private:
  void CheckBox() noexcept
  { 
    if (m_max.x() < m_min.x()) std::swap(m_min.x(), m_max.x()); 
    if (m_max.y() < m_min.y()) std::swap(m_min.y(), m_max.y()); 
  }
  Point2D m_min = { 0.0f, 0.0f }, m_max = { 0.0f, 0.0f };
};
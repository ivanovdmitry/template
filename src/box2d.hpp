#pragma once

#include <memory>

#include "point2d.hpp"


class Box2D
{
public:
  Box2D() = default;
  Box2D(std::shared_ptr<Point2D> & in_min, std::shared_ptr<Point2D> & in_max) : m_min(in_min), m_max(in_max) {}

  Box2D(Box2D const & obj) : m_min(obj.m_min), m_max(obj.m_max) {}


  Point2D GetCenter() const;

  void Move(Point2D const & point);

  bool Crossing(Box2D const & box) const;

  std::shared_ptr<Point2D> & GetMin() { return m_min; }
  std::shared_ptr<Point2D> & GetMax() { return m_max; }


  bool operator == (Box2D const & obj) const
  {
    return (m_min == obj.m_min) && (m_max == obj.m_max);
  }

  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_min = obj.m_min;
    m_max = obj.m_max;
    return *this;
  }

  friend std::ostream & operator << (std::ostream & os, Box2D const & obj)
  {
    os << "Box2D {(" << obj.m_min->x() << ", " << obj.m_min->y() << "), (" << obj.m_max->x() << ", " << obj.m_max->y() << ")}";
    return os;
  }

private:
  std::shared_ptr<Point2D> m_min = std::make_shared<Point2D>();
  std::shared_ptr<Point2D> m_max = std::make_shared<Point2D>();

};

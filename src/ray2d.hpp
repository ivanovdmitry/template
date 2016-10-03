#pragma once

#include <memory>

#include "point2d.hpp"


class Ray2D
{
public:
  Ray2D() = default;
  Ray2D(std::shared_ptr<Point2D> const & origin, std::shared_ptr<Point2D> const & direction) : m_origin(origin),  m_direction(direction) {}
  Ray2D(Ray2D const & obj) : m_origin(obj.m_origin), m_direction(obj.m_direction) {}

  inline std::shared_ptr<Point2D> & GetOrigin() { return m_origin; }
  inline std::shared_ptr<Point2D> & GetDirection() { return m_direction; }

  bool operator == (Ray2D const & obj) const
  {
    return (m_origin == obj.m_origin) && (m_direction == obj.m_direction);
  }
  
  Ray2D & operator = (Ray2D const & obj)
  {
    if (this == &obj) return *this;
    m_origin = obj.m_origin;
    m_direction = obj.m_direction;
    return *this;
  }



private:
  std::shared_ptr<Point2D> m_origin = std::make_shared<Point2D>();
  std::shared_ptr<Point2D> m_direction = std::make_shared<Point2D>();
};
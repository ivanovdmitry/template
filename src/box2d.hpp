#pragma once

#include <memory>

#include "point2d.hpp"


class Box2D
{
public:
  Box2D() = default;
  Box2D(std::shared_ptr<Point2D> & in_min, std::shared_ptr<Point2D> & in_max) : m_min(in_min), m_max(in_max) {}

  Box2D(Box2D const & obj) noexcept : m_min(obj.m_min), m_max(obj.m_max) {}
  Box2D(Box2D && obj) noexcept : m_min(std::move(obj.m_min)), m_max(std::move(obj.m_max)) {}


  std::shared_ptr<Point2D>  GetCenter() const 
  {
    return std::make_shared<Point2D>((m_max->x() - m_min->x())/2.0f + m_min->x(), (m_max->y() - m_min->y())/2.0f + m_min->y());
  }

  void SetCenter(std::shared_ptr<Point2D> const & point) 
  {
    float w = m_max->x() - m_min->x();
    float h = m_max->y() - m_min->y();

    m_min = std::make_shared<Point2D>(point->x() - w/2.0f, point->y() - h/2.0f);
    m_max = std::make_shared<Point2D>(point->x() + w/2.0f, point->y() + h/2.0f);
  }

  friend bool Crossing(Box2D const & box1, Box2D const & box2)  
  {
    return !(box1.m_min->x() > box2.m_max->x() || box1.m_max->x() < box2.m_min->x() || box1.m_max->y() < box2.m_min->y() || box1.m_min->y() > box2.m_max->y());
 }

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

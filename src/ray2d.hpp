#pragma once

#include <memory>
#include <cmath>
#include <vector>
#include <exception>

#include "box2d.hpp"
#include "point2d.hpp"

#include <iostream>
class Ray2D
{
public:
  Ray2D() = default;
  Ray2D(std::shared_ptr<Point2D> const & origin, std::shared_ptr<Point2D> const & direction) : m_origin(origin),  m_direction(direction) {}
  Ray2D(Ray2D const & obj) : m_origin(obj.m_origin), m_direction(obj.m_direction) {}
  Ray2D(Ray2D  && obj) : m_origin(std::move(obj.m_origin)), m_direction(std::move(obj.m_direction)) {}

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

  Ray2D  operator + (Ray2D const & obj) const
  {
    if (*m_direction != *obj.m_origin) { throw std::invalid_argument( "Uncorrected positions of the rays" ); }
    auto origin = std::make_shared<Point2D>(*m_origin);
    auto direction = std::make_shared<Point2D>(*m_direction + *obj.m_direction);
    return Ray2D(origin, direction);
  }

  Ray2D  operator - (Ray2D const & obj) const
  {
    if (*m_origin != *obj.m_origin) { throw std::invalid_argument( "Uncorrected positions of the rays" ); }
    auto origin = std::make_shared<Point2D>(*obj.m_direction);
    auto direction = std::make_shared<Point2D>(-(*obj.m_direction - *m_direction));
    return  Ray2D(origin, direction);
  }

  float  operator * (Ray2D const & obj) const
  {
    if ((*m_origin != *obj.m_origin) && (*m_direction != *obj.m_origin)) { throw std::invalid_argument( "Uncorrected positions of the rays" ); }
    Point2D a = *obj.m_origin - *obj.m_direction;
    Point2D b = *m_origin - *m_direction;
    return  a.x()*b.x() + a.y()*b.y();
  }

  Ray2D  operator * (float const & value) const
  {
    auto origin = std::make_shared<Point2D>(*m_origin);
    auto direction = std::make_shared<Point2D>(*m_direction*value);
    return  Ray2D(origin, direction);
  }

  inline float Abs() const
  {
    return std::sqrt(std::pow(m_direction->x(), 2) + std::pow(m_direction->y(), 2));
  }


  void Normalisation() 
  {
    m_direction = std::make_shared<Point2D>(m_direction->x()/Abs(), m_direction->y()/Abs());
  }


  // условие коллинеарности векторов
  friend bool Crossing (Ray2D const & ray1, Ray2D const & ray2)  
  {
     return ray1.m_direction->x()/ray2.m_direction->x() != ray1.m_direction->y()/ray2.m_direction->y();
  }

  friend bool Crossing (Ray2D  & ray, Box2D & box)  
  {

   return false;
  }

 friend std::ostream & operator << (std::ostream & os, Ray2D const & obj)
  {
    os << "Ray2D { from (" << obj.m_origin->x() << ", " << obj.m_origin->y() << "), to (" << obj.m_direction->x() << ", " << obj.m_direction->y() << ")}";
    return os;
  }

private:

  friend float GetAngle (std::shared_ptr<Ray2D> const &a, std::shared_ptr<Ray2D> const &b) 
  {
    return *a * *b / a->Abs() / b->Abs();
  }

  std::shared_ptr<Point2D> m_origin = std::make_shared<Point2D>();
  std::shared_ptr<Point2D> m_direction = std::make_shared<Point2D>();
};

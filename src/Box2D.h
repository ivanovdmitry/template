#pragma once

#include "Point2D.h"
#include <cmath>
#include <initializer_list>
#include <ostream>
#include <exception>

class Box2D
{
public:
	Box2D() = default;
	Box2D(Point2D const & obj1, Point2D const & obj2) : m_min(obj1), m_max(obj2) {};
	Box2D(float x1, float y1, float x2, float y2)
	{
		m_min = { std::min(x1,x2), std::min(y1, y2) };
		m_max = { std::max(x1,x2), std::max(y1, y2) };
	}
	Box2D(std::initializer_list<float> const & lst)
	{
		Point2D * vals[] = { &m_min, &m_max };
		int const count = sizeof(vals) / sizeof(vals[0]);
		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, it += 2)
			*vals[i] = { EqualWithEps(*(it)), EqualWithEps(*(it+1)) };
	}

	Box2D(std::initializer_list<Point2D> const & lst)
	{
		Point2D * vals[] = { &m_min, &m_max };
		int const count = sizeof(vals) / sizeof(vals[0]);
		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, it ++)
			*vals[i] =  *(it) ;
	}

	Box2D & operator = (Box2D const & obj)
	{
		if (this == &obj) return *this;
		m_min = obj.m_min;
		m_max = obj.m_max;
		return *this;
	}

	bool operator == (Box2D const & obj) const {  return (m_min == obj.m_min) && (m_max == obj.m_max);  }

	bool operator != (Box2D const & obj)  {  return !operator==(obj);  }

	Point2D operator [] (unsigned int index) const
	{
		if (index >= 2)  throw std::invalid_argument( "Reference to non-existing object" );
		return index == 0 ? m_min : m_max;
	}

	Point2D Centre () const  {  return (m_min + m_max) / 2.0;  }

	friend bool Intsec (Box2D const & obj1, Box2D const & obj2)
	{
		if ( (obj1.m_max.y() >= obj2.m_min.y()) && (obj1.m_min.y() <= obj2.m_max.y()) )
		return (obj1.m_max.x() >= obj2.m_min.x()) && (obj1.m_min.x() <= obj2.m_max.x());
		return false;
	}

	Box2D & Move(Point2D const & obj)
	{
		if ((*this).Centre() == obj) return *this;
		Point2D point(obj - (*this).Centre());
		m_min += point;
		m_max += point;
		return *this;
	}
	Box2D & Move(float x, float y)
	{
		if ( EqualWithEps((*this).Centre().x(),x) && EqualWithEps((*this).Centre().y(), y)) return *this;
		Point2D point(x - (*this).Centre().x(), y - (*this).Centre().y());
		m_min += point;
		m_max += point;
		return *this;
	}

	Point2D & LeftBot()  {  return m_min;  }
	Point2D & RightTop()  {  return m_max;  }
	Point2D LeftTop() 
	{
		Point2D point = { m_min.x(), m_max.y() };
		return point;
	}
	Point2D RightBot() 
	{
		Point2D point = { m_max.x(), m_min.y() };
		return point;
	}

	Point2D const & LeftBot() const  {  return m_min;  }
	Point2D const & RightTop() const  {  return m_max;  }
	Point2D const LeftTop() const
	{
		Point2D point = { m_min.x(), m_max.y() };
		return point;
	}
	Point2D const RightBot() const
	{
		Point2D point = { m_max.x(), m_min.y() };
		return point;
	}

	friend std::ostream & operator << (std::ostream & os, Box2D const & obj)
	{
		os << "Box 2D {Left Bot " << obj.LeftBot() << ", Right Top " << obj.RightTop() << "}";
		return os;
	}

private:
	float const kEps = 1e-5;
	float EqualWithEps(float v) const 
	{
		return (v <= kEps) ? 0.0 : v;
	}
	bool EqualWithEps(float v1, float v2) const
	{
		return fabs(v1 - v2) < kEps;
	}
	Point2D m_min = { 0.0f, 0.0f }, m_max = { 1.0f, 1.0f };
};
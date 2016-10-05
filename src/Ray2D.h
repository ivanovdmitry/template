#pragma once

#include "Box2D.h"
#include <initializer_list>
#include <ostream>

class Ray2D
{
public:
	Ray2D() = default;
	Ray2D(Point2D const & obj1, Point2D const & obj2) : m_origin(obj1), m_direction(obj2) {}
	Ray2D(float x1, float y1, float x2, float y2) : m_origin(x1, y1), m_direction(x2, y2) {}
	Ray2D(std::initializer_list<float> const & lst)
	{
		Point2D * vals[] = { &m_origin, &m_direction };
		int const count = sizeof(vals) / sizeof(vals[0]);
		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, it += 2)
			*vals[i] = { EqualWithEps(*it), EqualWithEps(*(it + 1)) };
	}
	Ray2D(std::initializer_list<Point2D> const & lst)
	{
		Point2D * vals[] = { &m_origin, &m_direction };
		int const count = sizeof(vals) / sizeof(vals[0]);
		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, it ++)
			*vals[i] =  *(it) ;
	}

	Ray2D & operator = (Ray2D const & obj)
	{
		if (this == &obj) return *this;
		m_origin = obj.m_origin;
		m_direction = obj.m_direction;
		return *this;
	}

	bool operator == (Ray2D const & obj) const {  return (m_origin == obj.m_origin) && (m_direction == obj.m_direction);  }

	bool operator != (Ray2D const & obj)  {  return !operator==(obj);  }


	Ray2D & Move(Point2D const & obj)
	{
		if ((*this).m_origin == obj) return *this;
		m_origin = obj;
		return *this;
	}

	Ray2D & Move(float x, float y)
	{
		if ( EqualWithEps((*this).m_origin.x(), x) && EqualWithEps((*this).m_origin.y(), y) ) return *this;
		m_origin.Move(x, y);
		return *this;
	}

	
	
	friend bool Intsec(Box2D const & obj1, Ray2D const & obj2)
	{
		float arr[5] = { 
			atan2(obj1.LeftBot() - obj2.Point()), 
			atan2(obj1.LeftTop() - obj2.Point()),
			atan2(obj1.RightTop() - obj2.Point()), 
			atan2(obj1.RightBot() - obj2.Point()), 
			atan2(obj2.Vector()) 
		};

		for (int i = 0; i < 4; i++)
		{
			if (arr[4] >= arr[i])
			{
				for (int i = 0; i < 4; i++)
					if (arr[4] <= arr[i])
						return true;
				return false;
			}
		}
		return false;
	}

	friend bool Intsec(Ray2D const & obj1, Box2D const & obj2)  {  return Intsec(obj2, obj1);  }

	
	
	Point2D & Point()  {  return m_origin;  }
	Point2D & Vector()  {  return m_direction;  }

	Point2D const & Point() const  {  return m_origin;  }
	Point2D const & Vector() const  {  return m_direction;  }

	friend std::ostream & operator << (std::ostream & os, Ray2D const & obj)
	{
		os << "Ray 2D { Origin " << obj.Point() << ", Direction " << obj.Vector() << "}";
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
	Point2D m_origin = { 0.0f, 0.0f };
	Point2D m_direction = { 0.0f, 0.0f };
};
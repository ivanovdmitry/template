#pragma once

#include "point2d.h"
#include <cmath>
#include <initializer_list>
#include <ostream>

class Box2D
{
public:
	Box2D() = default;
	Box2D(Point2D const & obj1, Point2D const & obj2) : m_pLeftBot(obj1), m_pRightTop(obj2) {};
	Box2D(float x1, float y1, float x2, float y2)
	{
		if (x1 < x2)
		{
			m_pLeftBot = { x1, y1 };
			m_pRightTop = { x2, y2 };
		}
		else
		{
			m_pLeftBot = { x2, y2 };
			m_pRightTop = { x1, y1 };
		}
	}
	Box2D(std::initializer_list<float> const & lst)
	{
		Point2D * vals[] = { &m_pLeftBot, &m_pRightTop };
		int const count = sizeof(vals) / sizeof(vals[0]);
		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, it += 2)
			*vals[i] = { *(it), *(it + 1) };
	}

	Box2D & operator = (Box2D const & obj)
	{
		if (this == &obj) return *this;
		m_pLeftBot = obj.m_pLeftBot;
		m_pRightTop = obj.m_pRightTop;
		return *this;
	}

	bool operator == (Box2D const & obj)  {  return (m_pLeftBot == obj.m_pLeftBot) && (m_pRightTop == obj.m_pRightTop);  }

	bool operator != (Box2D const & obj)  {  return !operator==(obj);  }

	Point2D Centre () const  {  return{ (m_pLeftBot + m_pRightTop) / 2 };  }

	friend bool Intsec (Box2D const & obj1, Box2D const & obj2)
	{
		if ( (obj1.m_pRightTop.y() >= obj2.m_pLeftBot.y()) && (obj1.m_pLeftBot.y() <= obj2.m_pRightTop.y()) )
		return (obj1.m_pRightTop.x() >= obj2.m_pLeftBot.x()) && (obj1.m_pLeftBot.x() <= obj2.m_pRightTop.x());
		return false;
	}

	Box2D & Move(Point2D const & obj)
	{
		if ((*this).Centre() == obj) return *this;
		Point2D point(obj - (*this).Centre());
		m_pLeftBot += point;
		m_pRightTop += point;
		return *this;
	}
	Box2D & Move(float x, float y)
	{
		if ( EqualWithEps((*this).Centre().x(),x) && EqualWithEps((*this).Centre().y(), y)) return *this;
		Point2D point(x - (*this).Centre().x(), y - (*this).Centre().y());
		m_pLeftBot += point;
		m_pRightTop += point;
		return *this;
	}

	Point2D & LeftBot()  {  return m_pLeftBot;  }
	Point2D & RightTop()  {  return m_pRightTop;  }
	Point2D LeftTop() 
	{
		Point2D point = { m_pLeftBot.x(), m_pRightTop.y() };
		return point;
	}
	Point2D RightBot() 
	{
		Point2D point = { m_pRightTop.x(), m_pLeftBot.y() };
		return point;
	}

	Point2D const & LeftBot() const  {  return m_pLeftBot;  }
	Point2D const & RightTop() const  {  return m_pRightTop;  }
	Point2D const LeftTop() const
	{
		Point2D point = { m_pLeftBot.x(), m_pRightTop.y() };
		return point;
	}
	Point2D const RightBot() const
	{
		Point2D point = { m_pRightTop.x(), m_pLeftBot.y() };
		return point;
	}

	friend std::ostream & operator << (std::ostream & os, Box2D const & obj)
	{
		os << "Box 2D {Left Bot" << obj.LeftBot() << ", Right Top" << obj.RightTop() << "}";
		return os;
	}

private:
	float const kEps = 1e-5;
	bool EqualWithEps(float v1, float v2) const
	{
		return fabs(v1 - v2) < kEps;
	}
	Point2D m_pLeftBot = { 0.0f, 0.0f }, m_pRightTop = { 1.0f, 1.0f };
};
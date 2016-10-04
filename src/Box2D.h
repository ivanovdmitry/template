#pragma once

#include "Point2D.h"

class Box2D
{
public:
	Box2D() = default;
	Box2D(Point2D const & obj1, Point2D const & obj2) : m_pMin(obj1), m_pMax(obj2) {};
	Box2D(float x1, float y1, float x2, float y2)
	{
		if (x1 < x2)
		{
			m_pMin = { x1, y1 };
			m_pMax = { x2, y2 };
		}
		else
		{
			m_pMin = { x2, y2 };
			m_pMax = { x1, y1 };
		}
	};
	Box2D(std::initializer_list<float> const & lst)
	{
		Point2D * vals[] = { &m_pMin, &m_pMax };
		int const count = sizeof(vals) / sizeof(vals[0]);

		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, it+=2)
			*vals[i] = { *(it), *(it + 1) };
	}

	Box2D & operator = (Box2D const & obj)
	{
		if (this == &obj) return *this;
		m_pMin = obj.m_pMin;
		m_pMax = obj.m_pMax;
		return *this;
	}

	bool operator == (Box2D const & obj)
	{
		return (m_pMin == obj.m_pMin) && (m_pMax == obj.m_pMax);
	}

	bool operator != (Box2D const & obj)
	{
		return !operator==(obj);
	}

	Point2D centre () const
	{
		return{ (m_pMin + m_pMax) / 2 };
	}

	friend bool intsec (Box2D const & obj1, Box2D const & obj2)
	{
		if ( (obj1.m_pMax.y() >= obj2.m_pMin.y()) && (obj1.m_pMin.y() <= obj2.m_pMax.y()) )
		return (obj1.m_pMax.x() >= obj2.m_pMin.x()) && (obj1.m_pMin.x() <= obj2.m_pMax.x());
		return false;
	}

	Box2D & move(Point2D const & obj)
	{
		if ((*this).centre() == obj) return *this;
		Point2D x(obj - (*this).centre());
		m_pMin += x;
		m_pMax += x;
		return *this;
	}
	Box2D & move(float x, float y)
	{
		if ( EqualWithEps((*this).centre().x(),x) && EqualWithEps((*this).centre().y(), y)) return *this;
		Point2D point(x - (*this).centre().x(), y - (*this).centre().y());
		m_pMin += point;
		m_pMax += point;
		return *this;
	}

	Point2D & leftBot() { return m_pMin; }
	Point2D & rightTop() { return m_pMax; }
	Point2D leftTop() 
	{
		Point2D point = { m_pMin.x(), m_pMax.y() };
		return point;
	}
	Point2D rightBot() 
	{
		Point2D point = { m_pMax.x(), m_pMin.y() };
		return point;
	}

	Point2D const & leftBot() const { return m_pMin; }
	Point2D const & rightTop() const { return m_pMax; }
	Point2D const leftTop() const
	{
		Point2D point = { m_pMin.x(), m_pMax.y() };
		return point;
	}
	Point2D const rightBot() const
	{
		Point2D point = { m_pMax.x(), m_pMin.y() };
		return point;
	}

	friend std::ostream & operator << (std::ostream & os, Box2D const & obj)
	{
		os << "Box 2D {" << obj.leftBot() << "," << obj.rightTop() << "}";
		return os;
	}

private:
	float const kEps = 1e-5;
	bool EqualWithEps(float v1, float v2) const
	{
		return fabs(v1 - v2) < kEps;
	}
	Point2D m_pMin = { 0.0f, 0.0f }, m_pMax = { 1.0f, 1.0f };
};
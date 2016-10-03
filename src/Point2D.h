#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

float const kEps = 1e-5;

class Point2D
{
public:
	Point2D() = default;
	Point2D(Point2D const & obj) : m_x(obj.m_x), m_y(obj.m_y) {};
	Point2D(float x, float y) : m_x(x), m_y(y) {};
	Point2D(std::initializer_list<float> const & lst)
	{
		float * vals[] = { &m_x, &m_y };
		int const count = sizeof(vals) / sizeof(vals[0]);

		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, ++it)
			*vals[i] = *it;
	}

	Point2D & operator = (Point2D const & obj)
	{
		if (this == &obj) return *this;
		m_x = obj.m_x;
		m_y = obj.m_y;
		return *this;
	}

	bool operator == (Point2D const & obj) const
	{
		return EqualWithEps(m_x, obj.m_x) && EqualWithEps(m_y, obj.m_y);
	}

	bool operator != (Point2D const & obj) const
	{
		return !operator==(obj);
	}

	bool operator < (Point2D const & obj) const
	{
		if (m_x < obj.m_x) return true;
		return m_y < obj.m_y;
	}

	Point2D operator + (Point2D const & obj) const
	{
		return{ m_x + obj.m_x,m_y + obj.m_y };
	}

	Point2D operator - (Point2D const & obj) const
	{
		return{ m_x - obj.m_x,m_y - obj.m_y };
	}

	Point2D operator - () const
	{
		return{ -m_x,-m_y };
	}

	Point2D operator * (float scale) const
	{
		return{ m_x*scale,m_y*scale };
	}

	Point2D operator / (float scale) const
	{
		if (scale == 0) return{ INFINITY , INFINITY };
		return{ m_x / scale,m_y / scale };
	}

	Point2D & operator += (Point2D const & obj)
	{
		m_x += obj.m_x;
		m_y += obj.m_y;
		return *this;
	}

	Point2D & operator -= (Point2D const & obj)
	{
		m_x -= obj.m_x;
		m_y -= obj.m_y;
		return *this;
	}

	Point2D & operator *= (float scale)
	{
		m_x *= scale;
		m_y *= scale;
		return *this;
	}

	Point2D & operator /= (float scale)
	{
		if (scale == 0)
		{
			m_x = INFINITY;
			m_y = INFINITY;
			return *this;
		}
		m_x /= scale;
		m_y /= scale;
		return *this;
	}

	float operator [] (unsigned int index) const
	{
		if (index >= 2) return 0.0f;
		return index == 0 ? m_x : m_y;
	}

	float & x() { return m_x; }
	float & y() { return m_y; }

	float const & x() const { return m_x; }
	float const & y() const { return m_y; }

	struct Hash
	{
		size_t operator () (Point2D const & p) const
		{
			auto hasher = std::hash<float>();
			return (hasher(p.x()) ^ (hasher(p.y()) << 1));
		}
	};

	friend std::ostream & operator << (std::ostream & os, Point2D const & obj)
	{
		os << "Point2D {" << obj.x() << ", " << obj.y() << "}";
		return os;
	}

private:
	bool EqualWithEps(float v1, float v2) const
	{
		return fabs(v1 - v2) < kEps;
	}
	float m_x = 0.0f, m_y = 0.0f;

};
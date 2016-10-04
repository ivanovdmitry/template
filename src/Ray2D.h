#pragma once

#include "Point2D.h";
#include "Box2D.h";

class Ray2D
{
public:
	Ray2D() = default;
	Ray2D(Point2D const & obj1, Point2D const & obj2) : m_p(obj1), m_vec(obj2) {}
	Ray2D(float x1, float y1, float x2, float y2) : m_p(x1, y1), m_vec(x2, y2) {}
	Ray2D(std::initializer_list<float> const & lst)
	{
		Point2D * vals[] = { &m_p,&m_vec };
		int const count = sizeof(vals) / sizeof(vals[0]);
		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, it += 2)
			*vals[i] = { *it, *(it + 1) };
	}

	Ray2D & move(Point2D const & obj)
	{
		if ((*this).m_p == obj) return *this;
		m_p = obj;
		return *this;
	}

	Ray2D & move(float x, float y)
	{
		if ( EqualWithEps((*this).m_p.x(), x) && EqualWithEps((*this).m_p.y(), y) ) return *this;
		m_p.move(x, y);
		return *this;
	}

	friend bool intsec(Box2D const & obj1, Ray2D const & obj2)
	{
		float arr[5] = { atan2f(obj1.leftBot() - obj2.point()), atan2f(obj1.leftTop() - obj2.point()),
			atan2f(obj1.rightTop() - obj2.point()), atan2f(obj1.rightBot() - obj2.point()), atan2f(obj2.vec()) };
		/*int flag = 0;
		for (int i = 0; i < 4; i++)
			(arr[i] > 0) ? flag++ : flag--;*/
		/*if (flag != 0)*/
		for (int i = 0; i < 4; i++)
		{
			if (arr[4] > arr[i])
			{
				for (int i = 0; i < 4; i++)
					if (arr[4] < arr[i])
						return true;
				return false;
			}
		}
		return false;
	}

	friend bool intsec(Ray2D const & obj1, Box2D const & obj2) 
	{
		return intsec(obj2, obj1);
	}

	friend float atan2f(Point2D const & obj) {return atan2f(obj.y(), obj.x());}
	
	Point2D & point() { return m_p; }
	Point2D & vec() { return m_vec; }

	Point2D const & point() const { return m_p; }
	Point2D const & vec() const { return m_vec; }

	friend std::ostream & operator << (std::ostream & os, Ray2D const & obj)
	{
		os << "Ray 2D {" << obj.point() << "," << obj.vec() << "}";
		return os;
	}

private:
	float const kEps = 1e-5;
	bool EqualWithEps(float v1, float v2) const
	{
		return fabs(v1 - v2) < kEps;
	}
	Point2D m_p = { 0.0f, 0.0f };
	Point2D m_vec = { 0.0f, 0.0f };
};
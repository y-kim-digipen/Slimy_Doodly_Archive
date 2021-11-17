/*--------------------------------------------------------------
File Name: BasicDataTypes.inl
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "BasicDataTypes.h"

inline Vector2D operator+(Vector2D v1, Vector2D v2)
{
	Vector2D add = { v1.x + v2.x, v1.y + v2.y };
	return add;
}


inline Vector2D operator-(Vector2D v1, Vector2D v2)
{
	Vector2D sub = { v1.x - v2.x, v1.y - v2.y };
	return sub;
}


inline Vector2D operator*(Vector2D v, double val)
{
	Vector2D mult = { v.x * val, v.y * val };
	return mult;
}


inline Vector2D operator/(Vector2D v, double val)
{
	Vector2D div = { v.x / val, v.y / val };
	return div;
}


inline Vector2D& operator+=(Vector2D& v1, Vector2D v2)
{
	Vector2D v3 = v1 + v2;
	v1 = v3;
	return v1;
}


inline Vector2D& operator-=(Vector2D& v1, Vector2D v2)
{
	Vector2D v3 = v1 - v2;
	v1 = v3;
	return v1;
}


inline Vector2D operator-(Vector2D& v)
{
	const Vector2D negative = { -v.x, -v.y };
	return negative;
}

inline bool operator<(Vector2D& v1, Vector2D& v2)
{
	return ((v1.x < v2.x) && (v1.y < v2.y));
}

inline bool operator>(Vector2D& v1, Vector2D& v2)
{
	return ((v1.x > v2.x) && (v1.y > v2.y));
}

inline bool operator==(Vector2D& v1, Vector2D& v2)
{
	return ((v1.x == v2.x) && (v1.y == v2.y));
}

inline bool operator>=(Vector2D& v1, Vector2D& v2)
{
	return ((v1.x >= v2.x) && (v1.y >= v2.y));
}

inline bool operator<=(Vector2D& v1, Vector2D& v2)
{
	return ((v1.x <= v2.x) && (v1.y <= v2.y));
}

inline Vector2DInt operator+(Vector2DInt v1, Vector2DInt v2)
{
	Vector2DInt add = { v1.x + v2.x, v1.y + v2.y };
	return add;
}


inline Vector2DInt operator-(Vector2DInt v1, Vector2DInt v2)
{
	Vector2DInt sub = { v1.x - v2.x, v1.y - v2.y };
	return sub;
}


inline Vector2DInt operator*(Vector2DInt v, double val)
{
	Vector2DInt mult = { static_cast<int>(v.x * val), static_cast<int>(v.y * val) };
	return mult;
}


inline Vector2DInt operator/(Vector2DInt v, double val)
{
	Vector2DInt div = { static_cast<int>(v.x / val), static_cast<int>(v.y / val) };
	return div;
}


inline Vector2DInt& operator+=(Vector2DInt& v1, Vector2DInt v2)
{
	Vector2DInt v3 = v1 + v2;
	v1 = v3;
	return v1;
}


inline Vector2DInt& operator-=(Vector2DInt& v1, Vector2DInt v2)
{
	Vector2DInt v3 = v1 - v2;
	v1 = v3;
	return v1;
}


inline Vector2DInt operator-(Vector2DInt& v)
{
	const Vector2DInt negative = { -v.x, -v.y };
	return negative;
}

inline bool operator<(Vector2DInt& v1, Vector2DInt& v2)
{
	return ((v1.x < v2.x) && (v1.y < v2.y));
}

inline bool operator>(Vector2DInt& v1, Vector2DInt& v2)
{
	return ((v1.x > v2.x)&& (v1.y > v2.y));
}

inline bool operator==(Vector2DInt& v1, Vector2DInt& v2)
{
	return ((v1.x == v2.x) && (v1.y == v2.y));
}

inline bool isLinesIntersection(const Vector2D& AP1, const Vector2D& AP2, const Vector2D& BP1, const Vector2D& BP2)
{
    double t;
    double s;
    double under = (BP2.y - BP1.y) * (AP2.x - AP1.x) - (BP2.x - BP1.x) * (AP2.y - AP1.y);
    if (under == 0) return false;

    double _t = (BP2.x - BP1.x) * (AP1.y - BP1.y) - (BP2.y - BP1.y) * (AP1.x - BP1.x);
    double _s = (AP2.x - AP1.x) * (AP1.y - BP1.y) - (AP2.y - AP1.y) * (AP1.x - BP1.x);

    t = _t / under;
    s = _s / under;

    if (t < 0.0 || t > 1.0 || s < 0.0 || s > 1.0) return false;
    if (_t == 0 && _s == 0) return false;

    return true;
}

inline Vector2D GetIntersectPoint(const Vector2D& AP1, const Vector2D& AP2, const Vector2D& BP1, const Vector2D& BP2, double* collisiontime)
{
    double t;
    double s;
    double under = (BP2.y - BP1.y) * (AP2.x - AP1.x) - (BP2.x - BP1.x) * (AP2.y - AP1.y);

    double _t = (BP2.x - BP1.x) * (AP1.y - BP1.y) - (BP2.y - BP1.y) * (AP1.x - BP1.x);
    double _s = (AP2.x - AP1.x) * (AP1.y - BP1.y) - (AP2.y - AP1.y) * (AP1.x - BP1.x);

    t = _t / under;
    s = _s / under;

    Vector2D IP;

    IP.x = AP1.x + t * static_cast<double>(AP2.x - AP1.x);
    IP.y = AP1.y + t * static_cast<double>(AP2.y - AP1.y);

	*collisiontime = t;

    return IP;
}


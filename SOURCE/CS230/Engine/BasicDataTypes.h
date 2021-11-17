/*--------------------------------------------------------------
File Name: BasicDataTypes.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include <utility>

#include "cmath"
typedef unsigned Color;

struct [[nodiscard]] Vector2D
{
	double x { 0.0 };
	double y { 0.0 };

	Vector2D(double x, double y) noexcept : x{ x }, y{ y }{};
	Vector2D() = default;
    [[nodiscard]] double Length() const
    {
		return std::sqrt(x * x + y * y);
	}

    [[nodiscard]] Vector2D UnitVec() const
    {
        const double length = Length();
		return Vector2D{ x / length , y / length };
    }
};

struct [[nodiscard]] Vector2DInt
{
	int x { 0 };
	int y { 0 };

	Vector2DInt(int x, int y) noexcept : x{ x }, y{ y }{};
	Vector2DInt() = default;

	Vector2D operator()() const
	{
		return Vector2D{ static_cast<double>(x), static_cast<double>(y) };
	};
};

struct Rect
{
	Vector2D bottomLeft;
	Vector2D topRight;

	Rect() = default;
	Rect(Vector2D _bottomLeft, Vector2D _topRight) : bottomLeft(_bottomLeft), topRight(_topRight) {}
};

Vector2D operator+(Vector2D, Vector2D);
Vector2D operator-(Vector2D, Vector2D);
Vector2D operator*(Vector2D, double);

inline Vector2D operator*(Vector2D A, Vector2D B)
{
	return { A.x * B.x , A.y * B . y };
}

Vector2D operator/(Vector2D, double);
Vector2D& operator+=(Vector2D&, Vector2D);
Vector2D& operator-=(Vector2D&, Vector2D);
Vector2D operator-(Vector2D&);
bool operator<(Vector2D&, Vector2D&);
bool operator>(Vector2D&, Vector2D&);
bool operator==(Vector2D&, Vector2D&);
bool operator>=(Vector2D&, Vector2D&);
bool operator<=(Vector2D&, Vector2D&);

Vector2DInt operator+(Vector2DInt, Vector2DInt);
Vector2DInt operator-(Vector2DInt, Vector2DInt);
Vector2DInt operator*(Vector2DInt, double);
Vector2DInt operator/(Vector2DInt, double);
Vector2DInt& operator+=(Vector2DInt&, Vector2DInt);
Vector2DInt& operator-=(Vector2DInt&, Vector2DInt);
Vector2DInt operator-(Vector2DInt&);
inline Vector2DInt operator-(Vector2DInt&& v)
{
	return { -v.x, -v.y };
}
bool operator<(Vector2DInt&, Vector2DInt&);
bool operator>(Vector2DInt&, Vector2DInt&);
bool operator==(Vector2DInt&, Vector2DInt&);

inline bool isLinesIntersection(const Vector2D& AP1, const Vector2D& AP2,
                                const Vector2D& BP1, const Vector2D& BP2);

inline Vector2D GetIntersectPoint(const Vector2D& AP1, const Vector2D& AP2,
                                  const Vector2D& BP1, const Vector2D& BP2, double* collisiontime);

inline double GetTwoTimesLength(const Vector2D& A, const Vector2D& B)
{
    const Vector2D sub = B - A;
	return sub.x * sub.x + sub.y * sub.y;
}

inline bool IsCollision(Rect a, Rect b)
{

	if (!(a.topRight.x < b.bottomLeft.x || a.bottomLeft.x > b.topRight.x)
		&& !(a.topRight.y < b.bottomLeft.y || a.bottomLeft.y > b.topRight.y))
		return true;
	return false;
}

inline double calcDistance(Vector2D a, Vector2D b)
{
	Vector2D newVec = b - a ;
	return std::sqrt(newVec.x * newVec.x + newVec.y * newVec.y);
}

inline double calcDistance(std::pair<Vector2D, Vector2D> line, Vector2D point)
{
	double a = (line.first.y - line.second.y) / (line.first.x - line.second.x);

	return abs(a * (point.x - line.first.x) - point.y + line.first.y) / sqrt(a * a + 1);
}

#include "BasicDataTypes.inl"

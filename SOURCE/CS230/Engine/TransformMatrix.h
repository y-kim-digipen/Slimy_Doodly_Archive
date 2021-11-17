/*--------------------------------------------------------------
File Name: TransformMatrix.h
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#pragma once
#include "BasicDataTypes.h"		//Vector2D
#include "doodle/doodle.hpp"

class TransformMatrix {
public:
	TransformMatrix();

	double* operator[](int index) { return matrix[index]; }
	const double* operator[](int index) const { return matrix[index]; }
	TransformMatrix operator * (TransformMatrix rhs) const;
	Vector2D operator * (Vector2D rhs) const;
	TransformMatrix& operator *= (TransformMatrix rhs);
	void Reset();
protected:
	double matrix[3][3];
};

class TranslateMatrix : public TransformMatrix {
public:
	TranslateMatrix(Vector2DInt translate);
	TranslateMatrix(Vector2D translate);
};

class RotateMatrix : public TransformMatrix {
public:
	RotateMatrix(double radians);
};

class ScaleMatrix : public TransformMatrix {
public:
	ScaleMatrix(Vector2D scale);
};
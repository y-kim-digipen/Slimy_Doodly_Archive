/*--------------------------------------------------------------
File Name: TransformMatrix.cpp
Project: Slimy Doodly
Author: Kevin Wright
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
-----------------------------------------------------------------*/

#include "TransformMatrix.h"

TransformMatrix::TransformMatrix() {
	Reset();
}

void TransformMatrix::Reset() {
	// Set the matrix to the identity 
	// You can use this format where you are setting 3 variables on the same line its a lot more readable like that.
	// Also you can set values to a hard coded 0.0 or 1.0, that's fine since that how these are defined
	// just replace the a,b,c... with the actual values like 0.0 or 1.0 or whatever
	// Remember that the first index is the row index, so [0][0],[0][1],[0][2] is the top row and [2][0],[2][1],[2][2] is the bottom row
	// Remove this function block before submitting (this would be considered an old comment, and should not be checked in)
	matrix[0][0] = 1.0; matrix[0][1] = .0; 	matrix[0][2] = .0;
	matrix[1][0] = .0; 	matrix[1][1] = 1.0; matrix[1][2] = .0;
	matrix[2][0] = .0; 	matrix[2][1] = 1.0; matrix[2][2] = 1.0;
}

TranslateMatrix::TranslateMatrix(Vector2DInt translate) {
	const Vector2D translateDouble = translate();
	matrix[0][0] = 1.0; matrix[0][1] = 0.; 	matrix[0][2] = translateDouble.x;
	matrix[1][0] = .0; 	matrix[1][1] = 1.0; matrix[1][2] = translateDouble.y;
	matrix[2][0] = .0; 	matrix[2][1] = .0; 	matrix[2][2] = 1.0;
}

TranslateMatrix::TranslateMatrix(Vector2D translate) {
	matrix[0][0] = 1.0; matrix[0][1] = 0.; 	matrix[0][2] = translate.x;
	matrix[1][0] = .0; 	matrix[1][1] = 1.0; matrix[1][2] = translate.y;
	matrix[2][0] = .0; 	matrix[2][1] = .0; 	matrix[2][2] = 1.0;
}

RotateMatrix::RotateMatrix(double radians) {
	const double cos = std::cos(radians);
	const double sin = std::sin(radians);
	matrix[0][0] = cos; 	matrix[0][1] = -sin; 	matrix[0][2] = .0;
	matrix[1][0] = sin; 	matrix[1][1] = cos; 	matrix[1][2] = .0;
	matrix[2][0] = .0; 		matrix[2][1] = .0;		matrix[2][2] = 1.0;
}

ScaleMatrix::ScaleMatrix(Vector2D scale) {
	matrix[0][0] = scale.x; matrix[0][1] = 0.; 		matrix[0][2] = .0;
	matrix[1][0] = .0; 		matrix[1][1] = scale.y; matrix[1][2] = .0;
	matrix[2][0] = .0; 		matrix[2][1] = .0;		matrix[2][2] = 1.0;
}

TransformMatrix TransformMatrix::operator * (TransformMatrix rhs) const {
	TransformMatrix result;

	result[0][0] = matrix[0][0] * rhs[0][0] + matrix[0][1] * rhs[1][0] + matrix[0][2] * rhs[2][0];
	result[0][1] = matrix[0][0] * rhs[0][1] + matrix[0][1] * rhs[1][1] + matrix[0][2] * rhs[2][1];
	result[0][2] = matrix[0][0] * rhs[0][2] + matrix[0][1] * rhs[1][2] + matrix[0][2] * rhs[2][2];
	result[1][0] = matrix[1][0] * rhs[0][0] + matrix[1][1] * rhs[1][0] + matrix[1][2] * rhs[2][0];
	result[1][1] = matrix[1][0] * rhs[0][1] + matrix[1][1] * rhs[1][1] + matrix[1][2] * rhs[2][1];
	result[1][2] = matrix[1][0] * rhs[0][2] + matrix[1][1] * rhs[1][2] + matrix[1][2] * rhs[2][2];
	result[2][0] = matrix[2][0] * rhs[0][0] + matrix[2][1] * rhs[1][0] + matrix[2][2] * rhs[2][0];
	result[2][1] = matrix[2][0] * rhs[0][1] + matrix[2][1] * rhs[1][1] + matrix[2][2] * rhs[2][1];
	result[2][2] = matrix[2][0] * rhs[0][2] + matrix[2][1] * rhs[1][2] + matrix[2][2] * rhs[2][2];

	return result;
}

Vector2D TransformMatrix::operator * (Vector2D rhs) const {
	Vector2D result;
	result.x = matrix[0][0] * rhs.x + matrix[0][1] * rhs.y;
	result.y = matrix[1][0] * rhs.x + matrix[1][1] * rhs.y;
	return result;
}

TransformMatrix& TransformMatrix::operator *= (TransformMatrix rhs) {
	(*this) = (*this) * rhs;
	return (*this);
}
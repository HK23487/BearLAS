#pragma once

#ifndef BEARLAS_IMPLEM_H__
#define BEARLAS_IMPLEM_H__

#include "Vector.h"
#include "Matrix.h"
#include <string>
#include <iomanip>
#include <iostream>

namespace BearLas {

	std::string ToString(const Vector& v);
	void PrintOut(const Vector& v);
	void PrintOut(const Matrix& m, int width = 4);

	void PrintOut(Vector_Complex v);
	void PrintOut(Matrix_Complex m, int width = 4);

	Vector Zeros(int _L);
	Vector Ones(int _L);
	Matrix Zeros(int _R, int _C);
	Matrix Ones(int _R, int _C);
	Vector Range(double start, double step, double stop);

	Vector _Cramer_Solution(const Matrix& A, const Vector& b);


	Vector_Complex _Cramer_Solution(Matrix_Complex A, Vector_Complex b);


	int _Leading(const Vector& V);
	bool _Row_Echelon_Form(const Matrix& A, double lead = 1.0);



	// EXPERIMENTAL; DO NOT USE

	Vector _EXP_Gaussian_Row_Echelon_Solution(Matrix A, Vector b);

	Matrix _Inverse(const Matrix& A);

	Matrix _Adjugate(const Matrix& A);
	Matrix _Adjoint(const Matrix& A);

	Matrix _Transpose(const Matrix& A);

	Matrix _Cofactor(const Matrix& A);
	bool _Symmetric(const Matrix& A);


}

#endif
#pragma once

#ifndef BEARLAS_IMPLEM_H__
#define BEARLAS_IMPLEM_H__

#include "Vector.h"
#include "Matrix.h"
#include <string>
#include <iomanip>
#include <iostream>

namespace BearLas {

	std::string ToString(Vector v);
	void PrintOut(Vector v);
	void PrintOut(Matrix m, int width = 4);

	void PrintOut(Vector_Complex v);
	void PrintOut(Matrix_Complex m, int width = 4);

	Vector Zeros(int _L);
	Vector Ones(int _L);
	Matrix Zeros(int _R, int _C);
	Matrix Ones(int _R, int _C);
	Vector Range(double start, double step, double stop);

	Vector _Cramer_Solution(Matrix A, Vector b);


	Vector_Complex _Cramer_Solution(Matrix_Complex A, Vector_Complex b);


	int _Leading(Vector V);
	bool _Row_Echelon_Form(Matrix A, double lead = 1.0);



	// EXPERIMENTAL; DO NOT USE

	Vector _EXP_Gaussian_Row_Echelon_Solution(Matrix A, Vector b);

	Matrix _Inverse(Matrix A);

	Matrix _Adjugate(Matrix A);
	Matrix _Adjoint(Matrix A);

	Matrix _Transpose(Matrix A);

	Matrix _Cofactor(Matrix A);
	bool _Symmetric(Matrix A);


}

#endif
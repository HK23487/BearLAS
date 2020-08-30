#pragma once

#ifndef BEARLAS_MATRIX_H__
#define BEARLAS_MATRIX_H__

#include "Vector.h"

namespace BearLas
{

	class Matrix
	{
	public:
		Matrix();
		Matrix(std::vector<Vector> _Rows);
		~Matrix();

		void Fill(int _R, int _C, double _Init = 0.0);

		std::vector<Vector>& VectorType();
		void operator=(std::vector<Vector> _Rows);

		std::vector<int> Dimensions();


		Vector& operator[](int _Id);
		void operator=(Matrix _Set);

		Matrix operator+(Matrix _A);
		Vector operator*(Vector _V);
		Matrix operator*(double _S);
		Matrix operator*(Matrix _M);

		double Det();

		bool Square();

	private:

		std::vector<Vector> rows;
		std::vector<int> size;
		

	};



	class Matrix_Complex
	{
	public:
		Matrix_Complex();
		Matrix_Complex(std::vector<Vector_Complex> _Rows);
		~Matrix_Complex();

		void Fill(int _R, int _C, Complex _Init = Complex(0.0, 0.0));

		std::vector<Vector_Complex> VectorType();
		void operator=(std::vector<Vector_Complex> _Rows);

		std::vector<int> Dimensions();


		Vector_Complex& operator[](int _Id);
		void operator=(Matrix_Complex _Set);

		Matrix_Complex operator+(Matrix_Complex _A);
		Vector_Complex operator*(Vector_Complex _V);
		Matrix_Complex operator*(Complex _S);
		Matrix_Complex operator*(Matrix_Complex _M);

		Complex Det();

		bool Square();

	private:

		std::vector<Vector_Complex> rows;
		std::vector<int> size;


	};

}

#endif
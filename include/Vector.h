#pragma once

#ifndef BEARLAS_VECTOR_H__
#define BEARLAS_VECTOR_H__


#include <vector>
#include <math.h>
#include <complex>

namespace BearLas
{
	
	typedef std::complex<double> Complex;

	class Vector
	{
	public:
		Vector();
		Vector(std::vector<double> _V);
		~Vector();

		void Fill(int _Length, double _Init = 0.0);

		std::vector<double> VectorType();
		void operator= (std::vector<double> _Set);

		int Length();


		double& operator[] (int _Id);
		void operator= (Vector _Set);

		Vector operator+ (Vector _A);
		Vector operator* (double _S);

		double Dot(Vector _V);
		Vector Cross(Vector _V);

	private:
		std::vector<double> values;
		int length;

	};


	class Vector_Complex 
	{
	public:
		Vector_Complex();
		Vector_Complex(std::vector<Complex> _V);
		~Vector_Complex();

		void Fill(int _Length, Complex _Init = Complex(0.0, 0.0));

		std::vector<Complex> VectorType();
		void operator=(std::vector<Complex> _Set);

		int Length();

		Complex& operator[] (int _Id);
		void operator= (Vector_Complex _Set);

		Vector_Complex operator+ (Vector_Complex _A);
		Vector_Complex operator* (Complex _S);

		Complex Dot(Vector_Complex _V);
		Vector_Complex Cross(Vector_Complex _V);

	private:
		std::vector<Complex> values;
		int length;

	};


}

#endif
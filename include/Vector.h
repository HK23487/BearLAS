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

		std::vector<double>& VectorType();
		const std::vector<double> VectorType() const;
		void operator= (std::vector<double> _Set);

		int Length();
		const int Length() const;


		double& operator[] (int _Id);
		const double operator[] (int _Id) const;

		void operator= (Vector _Set);

		Vector operator+ (Vector _A);
		Vector operator- (Vector _S);
		Vector operator* (double _S);
		Vector operator/ (double _S);

		Vector operator+ (Vector _A) const;
		Vector operator- (Vector _S) const;
		Vector operator* (double _S) const;
		Vector operator/ (double _S) const;

		double Dot(Vector _V);
		double Dot(Vector _V) const;

		Vector Cross(Vector _V);
		Vector Cross(Vector _V) const;


	private:
		std::vector<double> values;
		int length;

	};


	/*
		+------------------------------------+
		| WARNING: const not yet implemented |
		|         for Vector_Complex.        |
		+------------------------------------+
	*/


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
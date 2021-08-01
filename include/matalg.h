#pragma once
#include <complex>
#include "matrix.h"
#include "sparse.h"

namespace bla
{
	template <class _Ty>
	double p_norm(const basic_vector<_Ty>& vec, double p)
	{
		double sum = 0.0;
		for (size_t i = 0; i < vec.size(); i++)
			sum += std::pow(std::abs(vec.at(i)), p);
		return std::pow(sum, 1 / p);
	}


	double solve_linear(double a, double b)
	{
		if (a != 0) return -b / a;
		else return 0.0;
	}

	std::pair<double, double> solve_quadratic_r(double a, double b, double c)
	{
		if (a != 0) return { (-b + std::sqrt(b * b - 4 * a * c)) / (2 * a),
							 (-b - std::sqrt(b * b - 4 * a * c)) / (2 * a) };
		else return { solve_linear(b, c), solve_linear(b, c) };
	}

	std::pair<std::complex<double>, std::complex<double>> 
			 solve_quadratic_c(std::complex<double> a,
							   std::complex<double> b,
							   std::complex<double> c)
	{
		using namespace std::complex_literals;
		if (a != 0i) return 
		{ (-b + std::sqrt(b * b - std::complex<double>(4.0, 0.0) * a * c)) / (std::complex<double>(2.0, 0.0) * a),
		(-b - std::sqrt(b * b - std::complex<double>(4.0, 0.0) * a * c)) / (std::complex<double>(2.0, 0.0) * a) };
	}

	template <class _Ty>
	bool is_square(basic_matrix<_Ty> mat)
	{
		return mat.height() == mat.width();
	}

	template <class _Ty>
	basic_matrix<_Ty> submatrix_e(const basic_matrix<_Ty>& mat, size_t r, size_t c)
	{
		return basic_matrix<_Ty>();
	}

	template <class _Ty>
	_Ty determinant(basic_matrix<_Ty> mat)
	{
		if (!is_square(mat)) return 0;
		if (mat.height() == 2) return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
		else
		{
			_Ty sum = 0;
			for (size_t i = 0; i < mat.width(); i++)
				sum += ((i % 2) * -1) * mat.at(0, i) * 
				determinant(submatrix_e(mat, 0, i));
			return sum;
		}
	}

	template <class _Ty>
	basic_vector<_Ty> eigen_values_2x2(const basic_matrix<_Ty>& mat)
	{
		if (!(is_square(mat) && mat.height() == 2)) return basic_vector<_Ty>();
		auto [l1, l2] = solve_quadratic_r(1.0, -mat[1][1] - mat[0][0], determinant(mat));
		return basic_vector<_Ty>({ l1, l2 }, COL_VECTOR);
	}

	template <class _Ty>
	basic_vector<_Ty> solve_system(const basic_matrix<_Ty>& _A,
		const basic_vector<_Ty>& _b)
	{

	}



}
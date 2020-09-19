#pragma once

#ifndef BEARLAS_LITERAL_H__
#define BEARLAS_LITERAL_H__

#include "Matrix.h"
#include "Vector.h"
#include "Implementations.h"

namespace blas {

	namespace Literals {

		namespace Complex_Literals {

			std::complex<double> operator"" _i(long double _I);

		}

		namespace Matrix_Literals {

			Vector operator|(Matrix A, Vector b);

			Vector_Complex operator|(Matrix_Complex A, Vector_Complex b);

		}

		Vector operator*(const Vector& b, const Matrix& A);

		Vector operator*(const double& a, const Vector& b);

		Matrix operator*(const double& a, const Matrix& b);

		Vector operator/=(Vector& lhs, const double& rhs);

		Matrix operator/=(Matrix& lhs, const double& rhs);

		Vector operator*=(Vector& lhs, const double& rhs);

		Matrix operator*=(Matrix& lhs, const double& rhs);

	}

}

#endif
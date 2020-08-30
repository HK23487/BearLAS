#pragma once

#ifndef BEARLAS_LITERAL_H__
#define BEARLAS_LITERAL_H__

#include "Matrix.h"
#include "Vector.h"
#include "Implementations.h"

namespace BearLas {

	namespace Literals {

		namespace Complex_Literals {

			std::complex<double> operator"" _i(long double _I);

		}

		namespace Matrix_Literals {

			Vector operator|(Matrix A, Vector b);

			Vector_Complex operator|(Matrix_Complex A, Vector_Complex b);

		}

		Vector operator*(Vector b, Matrix A);

		Vector operator*(double a, Vector b);

		Matrix operator*(double a, Matrix b);

	}

}

#endif
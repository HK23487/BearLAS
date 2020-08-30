#include "Literals.h"



namespace BearLas
{


	namespace Literals {

		namespace Complex_Literals {

			std::complex<double> operator"" _i(long double _I) {
				return std::complex<double>(0.0, _I);
			}

		}

		namespace Matrix_Literals {

			Vector operator|(Matrix A, Vector b) {
				return _Cramer_Solution(A, b);
			}

			Vector_Complex operator|(Matrix_Complex A, Vector_Complex b) {
				return _Cramer_Solution(A, b);
			}

		}

		Vector operator*(Vector b, Matrix A) {
			return A * b;
		}

		Vector operator*(double a, Vector b) {
			return b * a;
		}

		Matrix operator*(double a, Matrix b) {
			return b * a;
		}

	}



}
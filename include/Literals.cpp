#include "Literals.h"



namespace blas
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

		Vector operator*(const Vector& b, const Matrix& A) {
			return A * b;		
		}				 		
						 		
		Vector operator*(const double& a, const Vector& b) {
			return b * a; 		
		}				  		
						  		
		Matrix operator*(const double& a, const Matrix& b) {
			return b * a;
		}

		Vector operator/=(Vector& lhs, const double& rhs) {
			lhs = lhs / rhs;
			return lhs;
		}

		Matrix operator/=(Matrix& lhs, const double& rhs) {
			lhs = lhs / rhs;
			return lhs;
		}

		Vector operator*=(Vector& lhs, const double& rhs) {
			lhs = lhs * rhs;
			return lhs;
		}

		Matrix operator*=(Matrix& lhs, const double& rhs) {
			lhs = lhs * rhs;
			return lhs;
		}

	}



}
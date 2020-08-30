
#include "BearLAS.h"





namespace BearLas
{


#ifdef LAS_UNIT_VECTORS
	Vector I({ 1, 0, 0 });
	Vector J({ 0, 1, 0 });
	Vector K({ 0, 0, 1 });
#elif defined LAS_ALL
	Vector I({ 1, 0, 0 });
	Vector J({ 0, 1, 0 });
	Vector K({ 0, 0, 1 });
#endif

#ifdef LAS_ID_MATRIX
	Matrix IDMatrix_2D({ \
	   Vector({1, 0}),
	   Vector({0, 1})
		});
	Matrix IDMatrix_3D({ \
	   Vector({1, 0, 0}),
	   Vector({0, 1, 0}),
	   Vector({0, 0, 1})
		});
	Matrix IDMatrix_4D({ \
	   Vector({1, 0, 0, 0}),
	   Vector({0, 1, 0, 0}),
	   Vector({0, 0, 1, 0}),
	   Vector({0, 0, 0, 1})
		});
#elif defined LAS_ALL
	Matrix IDMatrix_2D({ \
	   Vector({1, 0}),
	   Vector({0, 1})
		});
	Matrix IDMatrix_3D({ \
	   Vector({1, 0, 0}),
	   Vector({0, 1, 0}),
	   Vector({0, 0, 1})
		});
	Matrix IDMatrix_4D({ \
	   Vector({1, 0, 0, 0}),
	   Vector({0, 1, 0, 0}),
	   Vector({0, 0, 1, 0}),
	   Vector({0, 0, 0, 1})
		});
#endif

#ifdef LAS_PLANE_CALC
	Matrix _Plane_Rotate(double _Theta)
	{
		return Matrix({ \
		Vector({ std::cos(_Theta), std::sin(_Theta) * -1 }),
		Vector({ std::sin(_Theta), std::cos(_Theta)      })
			});
	}

	Matrix _Plane_Rotate(double _Theta, double _S)
	{
		return Matrix({ \
		Vector({ std::cos(_Theta) * _S, std::sin(_Theta) * _S * -1 }),
		Vector({ std::sin(_Theta) * _S, std::cos(_Theta) * _S      })
			});
	}

	Matrix _Plane_Shear(short _Dir = 1)
	{
		return Matrix({ \
		Vector({ 1.0 * _Dir, 1.0 * _Dir }),
		Vector({ 0,          1.0 * _Dir })
			});
	}
#elif defined LAS_ALL
	Matrix _Plane_Rotate(double _Theta)
	{
		return Matrix({ \
	Vector({ std::cos(_Theta), std::sin(_Theta) * -1 }),
	Vector({ std::sin(_Theta), std::cos(_Theta)      })
			});
	}

	Matrix _Plane_Rotate(double _Theta, double _S)
	{
		return Matrix({ \
	Vector({ std::cos(_Theta) * _S, std::sin(_Theta) * _S * -1 }),
	Vector({ std::sin(_Theta) * _S, std::cos(_Theta) * _S      })
			});
	}

	Matrix _Plane_Shear(short _Dir = 1)
	{
		return Matrix({ \
	Vector({ 1.0 * _Dir, 1.0 * _Dir }),
	Vector({ 0,          1.0 * _Dir })
			});
	}
#endif

#ifdef LAS_CONSTANTS
	double _PI = 3.1415926535897932384626;
	double _E = 2.7182818284590452353602;
	double _PHI = 1.6180339887498948482045;
	std::complex<double> _I = std::complex<double>(0.0, 1.0);
	double _SQRT2 = std::sqrt(2.0);
#elif defined LAS_ALL
	double _PI = 3.1415926535897932384626;
	double _E = 2.7182818284590452353602;
	double _PHI = 1.6180339887498948482045;
	std::complex<double> _I = std::complex<double>(0.0, 1.0);
	double _SQRT2 = std::sqrt(2.0);
#endif



}
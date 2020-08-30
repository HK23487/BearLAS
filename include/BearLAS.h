#pragma once

#ifndef BEARLAS_H
#define BEARLAS_H



/*

	BearLAS - A portable linear algebra library that can be used for various applications.

	Current Version: BearLAS Alpha 6.0 (8/12/2020)

	Past Versions:

	Alpha 5.0 (8/11/2020)
	Alpha 4.0 (8/9/2020)
	Alpha 3.0 (8/7/2020)
	Alpha 2.0 (8/6/2020)
	Alpha 1.0 (8/4/2020)

	~~~~~~~~~~~~

	Please read the following agreements and license before using this software. If the user 
	does not agree to the following terms, he/she MAY NOT USE THIS SOFTWARE.

	~~~~~~~~~~~~

	Copyright (c) 2020 by Hyun-Jin Kim.

	~~~~~~License~~~~~~

	1. Reproduction of this software (File copying, text copying, or by any means) is strictly
	prohibited without written or verbal permission from the programmer.

	2. Usage of this software in any other program (published, are to be published, or private) 
	requires explicit commenting that the program is currently using this software.

	3. Even with permission from the programmer, the user may NOT copy the text and only this
	library's contents onto another file. The user of this software is limited to
	#include "BearLAS.h" ONLY.

	4. The user is allowed to either use the FILES or only the .LIB FILE, IMPLYING THAT HE/SHE
	HAS PERMISSION FROM THE PROGRAMMER.

	5. If the user attempts to sell this software, the user will be severely punished. If the
	user does want to sell this software, contact the programmer for more information.

	6. Even if the name of this library has the word 'bear' in it, no 'bears' may use this
	software.

	7. THIS SOFTWARE DOES NOT COME WITH ANY WARRANTY. IF THE USER MODIFIES THIS LIBRARY FOR
	HIS/HER OWN USE, HE/SHE IS RESPONSIBLE FOR MALFUNCTIONS OR BUGS OF ANY KIND. 

	~~~~~~~~~~~~

	~~~~~~Features~~~~~~

	All assets are contained inside the BearLas namespace.

	BearLas::Vector - A class for a Vector object.
	BearLas::Matrix - A class for a Matrix object.

	A Vector can be printed, multiplied or added by a Matrix or a scalar (double),
	and can get its std::string value.
	A Matrix can be printed, multiplied or added by a Matrix, Vector, or a scalar (double),
	but cannot get its std:string value.

	The Range() function can help when creating large Vectors. Its parameters are start, step, and stop.
	Use like this:

	~~~~~~~~~~~~

	Vector v = Range(0, 0.1, 0.7);
	PrintOut(v);

	------------------------------
	Output:

	0
	0.1
	0.2
	0.3
	0.4
	0.5
	0.6
	0.7

	~~~~~~~~~~~~

	Settings: The user may #define certain macros for certain provisions.

	LAS_ALL:				Provides all settings

	LAS_UNIT_VECTORS:		Provides I, J, K unit vectors
	LAS_ID_MATRIX:			Provides 2x2, 3x3, and 4x4 indentity matrices
	LAS_PLANE_CALC:			Provides 2D plane calculation packages
	LAS_LITERALS:			Provides literals (complex, matrix operations)
	LAS_CONSTANTS:			Provides mathematical constants such as pi or e

	Example Program:

	-------------------------------------

	#include <iostream>
	#define LAS_ALL
	#include "BearLAS.h"

	using namespace std;
	using namespace BearLas;

	int main() {
		Vector v({ 4, 15, 22 });
		Matrix test({ \
			Vector({ 0, 2, 1 }),
			Vector({ 3, 1, 4 }),
			Vector({ 8, 6, 0 })
			});
		PrintOut( _Cramer_Solution(test, v) );

		std::cin.get();
		return 0;
	}

	-------------------------------------
	Output:

	2
	1
	2


*/

#ifdef __cplusplus

#pragma warning ( disable: 4018 4244 )

#include "Vector.h"
#include "Matrix.h"
#include "Implementations.h"

namespace BearLas {

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
	{	return Matrix({ \
			Vector({ std::cos(_Theta), std::sin(_Theta) * -1 }),
			Vector({ std::sin(_Theta), std::cos(_Theta)      })
			});	}

	Matrix _Plane_Rotate(double _Theta, double _S)
	{	return Matrix({ \
			Vector({ std::cos(_Theta) * _S, std::sin(_Theta) * _S * -1 }),
			Vector({ std::sin(_Theta) * _S, std::cos(_Theta) * _S      })
			}); }
	
	Matrix _Plane_Shear(short _Dir = 1)
	{	return Matrix({ \
			Vector({ 1.0 * _Dir, 1.0 * _Dir }),
			Vector({ 0,          1.0 * _Dir })
			}); }
#elif defined LAS_ALL
	Matrix _Plane_Rotate(double _Theta)
	{	return Matrix({ \
		Vector({ std::cos(_Theta), std::sin(_Theta) * -1 }),
		Vector({ std::sin(_Theta), std::cos(_Theta)      })
			}); }

	Matrix _Plane_Rotate(double _Theta, double _S)
	{	return Matrix({ \
		Vector({ std::cos(_Theta) * _S, std::sin(_Theta) * _S * -1 }),
		Vector({ std::sin(_Theta) * _S, std::cos(_Theta) * _S      })
			}); }

	Matrix _Plane_Shear(short _Dir = 1)
	{	return Matrix({ \
		Vector({ 1.0 * _Dir, 1.0 * _Dir }),
		Vector({ 0,          1.0 * _Dir })
			}); }
#endif

#ifdef LAS_CONSTANTS
	constexpr double _PI			  = 3.1415926535897932384626;
	constexpr double _E				  = 2.7182818284590452353602;
	constexpr double _PHI			  = 1.6180339887498948482045;
	constexpr std::complex<double> _I = std::complex<double>(0.0, 1.0);
	const	  double _SQRT2			  = std::sqrt(2.0);
#elif defined LAS_ALL
	constexpr double _PI			  = 3.1415926535897932384626;
	constexpr double _E				  = 2.7182818284590452353602;
	constexpr double _PHI			  = 1.6180339887498948482045;
	constexpr std::complex<double> _I = std::complex<double>(0.0, 1.0);
	const	  double _SQRT2			  = std::sqrt(2.0);
#endif

}

#ifdef LAS_LITERALS
#include "Literals.h"
#elif defined LAS_ALL
#include "Literals.h"
#endif


#else // C language

#include "C_handler.h"

#endif // __cplusplus

#endif
# BearLAS 
A portable linear algebra library that can be used for various applications.

Current Version: BearLAS Alpha 8.0 (9/19/2020)

Past Versions:

Alpha 7.1 (9/13/2020)
Alpha 7.0 (8/30/2020)
Alpha 6.0 (8/12/2020)
Alpha 5.0 (8/11/2020)
Alpha 4.0 (8/9/2020)
Alpha 3.0 (8/7/2020)
Alpha 2.0 (8/6/2020)
Alpha 1.0 (8/4/2020)

\~~~~~~~~~~~~

Please read the following agreements and license before using this software. If the user 
does not agree to the following terms, he/she MAY NOT USE THIS SOFTWARE.

\~~~~~~~~~~~~

Copyright (c) 2020 by HK23487.

\~~~~~~ License \~~~~~~

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

\~~~~~~~~~~~~

\~~~~~~ Features \~~~~~~

All assets are contained inside the `blas` ( `BearLas` if 7.1 or under) namespace.

BearLas::Vector - A class for a Vector object.
BearLas::Matrix - A class for a Matrix object.

A Vector can be printed, multiplied or added by a Matrix or a scalar (double),
and can get its std::string value.
A Matrix can be printed, multiplied or added by a Matrix, Vector, or a scalar (double),
but cannot get its std:string value.

The `Range()` function can help when creating large Vectors. Its parameters are start, step, and stop.
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

LAS_FORCE_NO_OPERATORS:		Forces no Matrix/Vector operators

LAS_CONSTANTS:			Provides mathematical constants such as pi or e


Example Program:

-------------------------------------

~~~~~

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

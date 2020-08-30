# BearLAS
A C++ library for linear algebra functions and types.

<br>
Current Version: BearLAS Alpha 7.0 (8/30/2020)
<br>
Past Versions:<br>
<br>
Alpha 6.0 (8/12/2020)<br>
Alpha 5.0 (8/11/2020)<br>
Alpha 4.0 (8/9/2020)<br>
Alpha 3.0 (8/7/2020)<br>
Alpha 2.0 (8/6/2020)<br>
Alpha 1.0 (8/4/2020)<br>
<br>

\~~~~~~~~~~~~

Please read the following agreements and license before using this software. If the user 
does not agree to the following terms, he/she MAY NOT USE THIS SOFTWARE.

\~~~~~~~~~~~~

Copyright (c) 2020 by Hyun-Jin Kim.

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

All assets are contained inside the BearLas namespace.

BearLas::Vector - A class for a Vector object.
BearLas::Matrix - A class for a Matrix object.

A Vector can be printed, multiplied or added by a Matrix or a scalar (double),
and can get its std::string value.
A Matrix can be printed, multiplied or added by a Matrix, Vector, or a scalar (double),
but cannot get its std:string value.

The Range() function can help when creating large Vectors. Its parameters are start, step, and stop.
Use like this:

\~~~~~~~~~~~~

Vector v = Range(0, 0.1, 0.7);
PrintOut(v);

------------------------------
Output:
<br>
0<br>
0.1<br>
0.2<br>
0.3<br>
0.4<br>
0.5<br>
0.6<br>
0.7<br>

\~~~~~~~~~~~~

Settings: The user may #define certain macros for certain provisions.

LAS_ALL:				Provides all settings

LAS_UNIT_VECTORS:		Provides I, J, K unit vectors<br>
LAS_ID_MATRIX:			Provides 2x2, 3x3, and 4x4 indentity matrices<br>
LAS_PLANE_CALC:			Provides 2D plane calculation packages<br>
LAS_LITERALS:			Provides literals (complex, matrix operations)<br>
LAS_CONSTANTS:			Provides mathematical constants such as pi or e<br>

Example Program:

-------------------------------------
~~~~~~~
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
~~~~~~~
-------------------------------------
Output:
<br>
2<br>
1<br>
2<br>

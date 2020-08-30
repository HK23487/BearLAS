#pragma once

#ifndef BEARLAS_C_HANDLER_H__
#define BEARLAS_C_HANDLER_H__


#ifndef BEARLAS_C
#error BearLAS is built for C++, not C. Please #define BEARLAS_C to access functions for C.
#else

#error C_handler.h: Line 11 <Configuration Error> using C Experimental features

const float* blas_sqmv(float** A, float* b, const int& size) {
	float* return_value = new float[size];
	for (int i = 0; i < size; i++) {
		float iter_val = 0.0f;
		for (int j = 0; j < size; j++) {
			iter_val += A[i][j] * b[j];
		}
		return_value[i] = iter_val;
	}
	return return_value;
}

const float* blas_sqmv(float** A, float* b, const unsigned int& size) {
	return blas_sqmv(A, b, (signed)size);
}

const float* blas_sqmv(float** A, float* b, int&& size) {
	return blas_sqmv(A, b, size);
}

const float* blas_sqmv(float** A, float* b, unsigned int&& size) {
	return blas_sqmv(A, b, (signed)size);
}

const float* blas_gemv(float** A, float* b, const int& rows, const int& cols) {
	float* return_value = new float[rows];
	for (int i = 0; i < rows; i++) {
		float iter_val = 0.0f;
		for (int j = 0; j < cols; j++) {
			iter_val += A[i][j] * b[j];
		}
		return_value[i] = iter_val;
	}
	return return_value;
}

const float* blas_gemv(float** A, float* b, const unsigned int& rows, const unsigned int& cols) {
	return blas_gemv(A, b, (signed)rows, (signed)cols);
}

const float* blas_gemv(float** A, float* b, int&& rows, int&& cols) {
	return blas_gemv(A, b, rows, cols);
}

const float* blas_gemv(float** A, float* b, unsigned int&& rows, unsigned int&& cols) {
	return blas_gemv(A, b, (signed)rows, (signed)cols);
}


#endif

#endif
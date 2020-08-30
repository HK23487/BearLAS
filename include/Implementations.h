#pragma once

#ifndef BEARLAS_IMPLEM_H__
#define BEARLAS_IMPLEM_H__

#include "Vector.h"
#include "Matrix.h"
#include <string>
#include <iomanip>
#include <iostream>

namespace BearLas {

	std::string ToString(Vector v) {
		std::string ret;
		for (double d : v.VectorType()) {
			ret += (d + '\n');
		}
		return ret;
	}
	void PrintOut(Vector v) {
		for (double d : v.VectorType()) {
			std::cout << d << std::endl;
		}
	}
	void PrintOut(Matrix m, int width = 4) {
		for (Vector v : m.VectorType()) {
			for (double d : v.VectorType()) {
				std::cout << std::setw(width) << std::left << d;
			}
			std::cout << '\n';
		}
	}

	void PrintOut(Vector_Complex v) {
		for (std::complex<double> d : v.VectorType()) {
			std::cout << d << '\n';
		}
	}
	void PrintOut(Matrix_Complex m, int width = 4) {
		for (Vector_Complex v : m.VectorType()) {
			for (std::complex<double> d : v.VectorType()) {
				std::cout << std::setw(width) << std::left << d;
			}
			std::cout << '\n';
		}
	}

	Vector Zeros(int _L) {
		Vector ret; ret.Fill(_L, 0.0);
		return ret;
	}
	Vector Ones(int _L) {
		Vector ret; ret.Fill(_L, 1.0);
		return ret;
	}
	Matrix Zeros(int _R, int _C) {
		Matrix ret; ret.Fill(_R, _C, 0.0);
		return ret;
	}
	Matrix Ones(int _R, int _C) {
		Matrix ret; ret.Fill(_R, _C, 1.0);
		return ret;
	}
	Vector Range(double start, double step, double stop) {
		std::vector<double> ret;
		for (double s = start; s <= stop; s += step) {
			ret.push_back(s);
		}
		return Vector(ret);
	}

	Vector _Cramer_Solution(Matrix A, Vector b) {
		if (A.Square()) {
			double det = A.Det();
			if (det != 0) {
				if (b.Length() == A.Dimensions()[0]) {
					std::vector<Matrix> coords;
					Matrix emp; emp.Fill(A.Dimensions()[0], A.Dimensions()[0]);
					coords.resize(A.Dimensions()[1]);
					for (int i = 0; i < coords.size(); i++) {
						coords[i] = A;
						for (int j = 0; j < A.Dimensions()[0]; j++) {
							coords[i][j][i] = b[j];
						}
					}
					std::vector<double> vals;
					vals.resize(A.Dimensions()[1]);
					for (int i = 0; i < vals.size(); i++) {
						vals[i] = coords[i].Det() / det;
					}
					return Vector(vals);
				}
			}
		}
		return Vector();
	}


	Vector_Complex _Cramer_Solution(Matrix_Complex A, Vector_Complex b) {
		if (A.Square()) {
			Complex det = A.Det();
			if (det != Complex(0, 0)) {
				if (b.Length() == A.Dimensions()[0]) {
					std::vector<Matrix_Complex> coords;
					Matrix_Complex emp; emp.Fill(A.Dimensions()[0], A.Dimensions()[0]);
					coords.resize(A.Dimensions()[1]);
					for (int i = 0; i < coords.size(); i++) {
						coords[i] = A;
						for (int j = 0; j < A.Dimensions()[0]; j++) {
							coords[i][j][i] = b[j];
						}
					}
					std::vector<Complex> vals;
					vals.resize(A.Dimensions()[1]);
					for (int i = 0; i < vals.size(); i++) {
						vals[i] = coords[i].Det() / det;
					}
					return Vector_Complex(vals);
				}
			}
		}
		return Vector_Complex();
	}


	int _Leading(Vector V) {
		for (int i = 0; i < V.Length(); i++) {
			if (V[i] != 0) return i;
			else continue;
		}
		return -1;
	}
	bool _Row_Echelon_Form(Matrix A, double lead = 1.0) {
		if (A.Square()) {
			for (int i = 0; i < A.Dimensions()[0]; i++) {
				if (_Leading(A[i]) != i) return false;
				else if (A[i][_Leading(A[i])] != lead) return false;
			}
			return true;
		}
		else { return false; }
	}



	// EXPERIMENTAL; DO NOT USE

	Vector _EXP_Gaussian_Row_Echelon_Solution(Matrix A, Vector b) {
		if (A.Square()) {
			if (A.Dimensions()[0] == b.Length()) {
				if (_Row_Echelon_Form(A)) {
					// Back substitution
					std::vector<double> cords;
					int length = b.Length();
					cords.resize(length, 0.0);
					for (int i = length - 1; i > -1; i--) {
						double val = b[i];
						for (int j = length - 1; j > -1; j--) {
							val -= A[i][j] * cords[j];
						}
						cords[i] = val;
					}
					return Vector(cords);
				}
				else {
					if (A.Det() != 0) {
						// Row operations
						return _EXP_Gaussian_Row_Echelon_Solution(A, b);
					}
					else {
						return Vector();
					}
				}
			}
			else {
				return Vector();
			}
		}
		else {
			return Vector();
		}
	}

	Matrix _Inverse(Matrix A) {
		if (A.Square()) {
			Matrix ret; ret.Fill(A.Dimensions()[0], A.Dimensions()[1]);
			Matrix I; I.Fill(A.Dimensions()[0], A.Dimensions()[1]);
			for (int i = 0; i < I.Dimensions()[0]; i++) {
				I[i][i] = 1;
			}
			std::vector<Vector> cols; cols.resize(A.Dimensions()[1]);
			std::vector<Vector> retv; retv.resize(I.Dimensions()[1]);
			for (int i = 0; i < A.Dimensions()[1]; i++) {
				std::vector<double> items; items.resize(A.Dimensions()[0]);
				for (int j = 0; j < A.Dimensions()[0]; j++) {
					items[j] = A[j][i];
				}
				cols[i] = Vector(items);
			}
			for (int i = 0; i < I.Dimensions()[1]; i++) {
				retv[i] = _Cramer_Solution(A, I[i]);
			}
			for (int i = 0; i < A.Dimensions()[0]; i++) {
				for (int j = 0; j < A.Dimensions()[0]; j++) {
					ret[i][j] = retv[j][i];
				}
			}
			return ret;
		}
		else {
			return Matrix();
		}
	}

	Matrix _Adjugate(Matrix A) {
		return _Inverse(A) * A.Det();
	}
	Matrix _Adjoint(Matrix A) {
		return _Adjugate(A);
	}

	Matrix _Transpose(Matrix A) {
		std::vector<Vector> rows = A.VectorType();
		std::vector<Vector> retv; retv.resize(A.Dimensions()[1], Zeros(A.Dimensions()[0]));
		for (int i = 0; i < rows.size(); i++) {
			for (int j = 0; j < rows[0].Length(); j++) {
				retv[j][i] = rows[i][j];
			}
		}
		return retv;
	}

	Matrix _Cofactor(Matrix A) {
		return _Transpose(_Inverse(A));
	}

	bool _Symmetric(Matrix A) {
		Matrix T = _Transpose(A);
		for (int i = 0; i < A.Dimensions()[0]; i++) {
			for (int j = 0; j < A.Dimensions()[1];  j++) {
				if (T[i][j] != A[i][j]) {
					return false;
				}
			}
		}
		return true;
	}


}

#endif
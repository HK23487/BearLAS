#include "Matrix.h"


namespace BearLas
{

	Matrix::Matrix() {
		size.resize(2);
	}
	Matrix::Matrix(std::vector<Vector> _Rows) {
		size.resize(2);
		rows = _Rows;
		size[0] = rows.size();
		size[1] = rows[0].Length();
	}
	Matrix::~Matrix() {
	}

	void Matrix::Fill(int _R, int _C, double _Init) {
		size[0] = _R;
		size[1] = _C;
		Vector v; v.Fill(_C, _Init);
		rows.resize(_R, v);
	}

	std::vector<Vector> Matrix::VectorType() {
		return rows;
	}
	void Matrix::operator=(std::vector<Vector> _Rows) {
		rows = _Rows;
		size[0] = rows.size();
		size[1] = rows[0].Length();
	}

	std::vector<int> Matrix::Dimensions() {
		return size;
	}


	Vector& Matrix::operator[](int _Id) {
		return rows[_Id];
	}
	void Matrix::operator=(Matrix _Set) {
		rows = _Set.rows;
		size = _Set.size;
	}

	Matrix Matrix::operator+(Matrix _A) {
		if (size == _A.size) {
			Matrix ret; ret.Fill(size[0], size[1]);
			for (int i = 0; i < size[0]; i++) {
				for (int j = 0; j < size[1]; j++) {
					ret[i][j] = rows[i][j] + _A[i][j];
				}
			}
			return ret;
		}
		else {
			return Matrix();
		}
	}
	Vector Matrix::operator*(Vector _V) {
		if (size[1] == _V.Length()) {
			Vector ret; ret.Fill(size[0]);
			for (int i = 0; i < size[0]; i++) {
				for (int j = 0; j < size[1]; j++) {
					ret[i] += rows[i][j] * _V[j];
				}
			}
			return ret;
		}
		else {
			return Vector();
		}
	}
	Matrix Matrix::operator*(double _S) {
		Matrix ret;
		ret.Fill(size[0], size[1]);

		for (int i = 0; i < size[0]; i++) {
			ret[i] = rows[i] * _S;
		}

		return ret;
	}
	Matrix Matrix::operator*(Matrix _M) {
		if (size[1] == _M.size[0]) {
			Matrix ret; ret.Fill(size[0], _M.size[1]);
			std::vector<Vector> retv; retv.resize(_M.size[1]);
			std::vector<Vector> cols; cols.resize(_M.size[1]);
			for (int i = 0; i < _M.size[1]; i++) {
				std::vector<double> items; items.resize(_M.size[0]);
				for (int j = 0; j < _M.size[0]; j++) {
					items[j] = _M[j][i];
				}
				cols[i] = Vector(items);
			}
			for (int i = 0; i < _M.size[1]; i++) {
				retv[i] = *this * cols[i];
			}
			for (int i = 0; i < size[0]; i++) {
				for (int j = 0; j < _M.size[1]; j++) {
					ret[i][j] = retv[j][i];
				}
			}
			return ret;
		}
		else {
			return Matrix();
		}
	}


	double Matrix::Det() {
		if (size[0] == size[1]) {
			if (size[0] == 1) {
				return 0.0;
			}
			else if (size[0] == 2) {
				return (rows[0][0] * rows[1][1] - rows[0][1] * rows[1][0]);
			}
			else if (size[0] == 3) {
				double A = rows[0][0];
				double B = rows[0][1];
				double C = rows[0][2];
				double D = rows[1][0];
				double E = rows[1][1];
				double F = rows[1][2];
				double G = rows[2][0];
				double H = rows[2][1];
				double I = rows[2][2];

				return A * E * I + B * F * G + C * D * H - C * E * G - B * D * I - A * F * H;
			}
			else {
				Vector top = rows[0];
				double ret = 0;
				for (int i = 0; i < top.VectorType().size(); i++) {
					Matrix submatrix; submatrix.Fill(size[0] - 1, size[0] - 1);
					short past = 0;
					for (int j = 0; j < top.VectorType().size(); j++) {
						if (j == i) { past = 1; continue; }
						for (int k = 0; k < size[0] - 1; k++) {
							submatrix[k][j - past] = rows[k + 1][j];
						}
					}
					if ((i + 1) % 2 == 0) {
						ret -= top[i] * submatrix.Det();
					}
					else {
						ret += top[i] * submatrix.Det();
					}
				}
				return ret;
			}
		}
	}

	bool Matrix::Square() {
		return size[0] == size[1];
	}









	Matrix_Complex::Matrix_Complex() {
		size.resize(2);
	}
	Matrix_Complex::Matrix_Complex(std::vector<Vector_Complex> _Rows) {
		size.resize(2);
		rows = _Rows;
		size[0] = rows.size();
		size[1] = rows[0].Length();
	}
	Matrix_Complex::~Matrix_Complex() {
	}

	void Matrix_Complex::Fill(int _R, int _C, Complex _Init) {
		size[0] = _R;
		size[1] = _C;
		Vector_Complex v; v.Fill(_C, _Init);
		rows.resize(_R, v);
	}

	std::vector<Vector_Complex> Matrix_Complex::VectorType() {
		return rows;
	}
	void Matrix_Complex::operator=(std::vector<Vector_Complex> _Rows) {
		rows = _Rows;
		size[0] = rows.size();
		size[1] = rows[0].Length();
	}

	std::vector<int> Matrix_Complex::Dimensions() {
		return size;
	}


	Vector_Complex& Matrix_Complex::operator[](int _Id) {
		return rows[_Id];
	}
	void Matrix_Complex::operator=(Matrix_Complex _Set) {
		rows = _Set.rows;
		size = _Set.size;
	}

	Matrix_Complex Matrix_Complex::operator+(Matrix_Complex _A) {
		if (size == _A.size) {
			Matrix_Complex ret; ret.Fill(size[0], size[1]);
			for (int i = 0; i < size[0]; i++) {
				for (int j = 0; j < size[1]; j++) {
					ret[i][j] = rows[i][j] + _A[i][j];
				}
			}
			return ret;
		}
		else {
			return Matrix_Complex();
		}
	}
	Vector_Complex Matrix_Complex::operator*(Vector_Complex _V) {
		if (size[1] == _V.Length()) {
			Vector_Complex ret; ret.Fill(size[0]);
			for (int i = 0; i < size[0]; i++) {
				for (int j = 0; j < size[1]; j++) {
					ret[i] += rows[i][j] * _V[j];
				}
			}
			return ret;
		}
		else {
			return Vector_Complex();
		}
	}
	Matrix_Complex Matrix_Complex::operator*(Complex _S) {
		Matrix_Complex ret;
		ret.Fill(size[0], size[1]);

		for (int i = 0; i < size[0]; i++) {
			ret[i] = rows[i] * _S;
		}

		return ret;
	}
	Matrix_Complex Matrix_Complex::operator*(Matrix_Complex _M) {
		if (size[1] == _M.size[0]) {
			Matrix_Complex ret; ret.Fill(size[0], _M.size[1]);
			std::vector<Vector_Complex> retv; retv.resize(_M.size[1]);
			std::vector<Vector_Complex> cols; cols.resize(_M.size[1]);
			for (int i = 0; i < _M.size[1]; i++) {
				std::vector<Complex> items; items.resize(_M.size[0]);
				for (int j = 0; j < _M.size[0]; j++) {
					items[j] = _M[j][i];
				}
				cols[i] = Vector_Complex(items);
			}
			for (int i = 0; i < _M.size[1]; i++) {
				retv[i] = *this * cols[i];
			}
			for (int i = 0; i < size[0]; i++) {
				for (int j = 0; j < _M.size[1]; j++) {
					ret[i][j] = cols[j][i];
				}
			}
			return ret;
		}
		else {
			return Matrix_Complex();
		}
	}


	Complex Matrix_Complex::Det() {
		if (size[0] == size[1]) {
			if (size[0] == 1) {
				return 0.0;
			}
			else if (size[0] == 2) {
				return (rows[0][0] * rows[1][1] - rows[0][1] * rows[1][0]);
			}
			else if (size[0] == 3) {
				Complex A = rows[0][0];
				Complex B = rows[0][1];
				Complex C = rows[0][2];
				Complex D = rows[1][0];
				Complex E = rows[1][1];
				Complex F = rows[1][2];
				Complex G = rows[2][0];
				Complex H = rows[2][1];
				Complex I = rows[2][2];

				return A * E * I + B * F * G + C * D * H - C * E * G - B * D * I - A * F * H;
			}
			else {
				Vector_Complex top = rows[0];
				Complex ret = 0;
				for (int i = 0; i < top.VectorType().size(); i++) {
					Matrix_Complex submatrix; submatrix.Fill(size[0] - 1, size[0] - 1);
					short past = 0;
					for (int j = 0; j < top.VectorType().size(); j++) {
						if (j == i) { past = 1; continue; }
						for (int k = 0; k < size[0] - 1; k++) {
							submatrix[k][j - past] = rows[k + 1][j];
						}
					}
					if ((i + 1) % 2 == 0) {
						ret -= top[i] * submatrix.Det();
					}
					else {
						ret += top[i] * submatrix.Det();
					}
				}
				return ret;
			}
		}
	}

	bool Matrix_Complex::Square() {
		return size[0] == size[1];
	}



}
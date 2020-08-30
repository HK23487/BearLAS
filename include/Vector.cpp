#include "Vector.h"

namespace BearLas
{
	
	Vector::Vector() {
		length = 0;
	}
	Vector::Vector(std::vector<double> _V) {
		values = _V;
		length = values.size();
	}
	Vector::~Vector() {
	}

	void Vector::Fill(int _Length, double _Init) {
		values.resize(_Length, _Init);
		length = _Length;
	}

	std::vector<double> Vector::VectorType() {
		return values;
	}
	void Vector::operator=(std::vector<double> _Set) {
		values = _Set;
		length = values.size();
	}

	int Vector::Length() {
		return length;
	}


	double& Vector::operator[](int _Id) {
		return values[_Id];
	}
	void Vector::operator=(Vector _Set) {
		values = _Set.values;
		length = _Set.length;
	}

	Vector Vector::operator+(Vector _A) {
		if (length == _A.length) {
			Vector ret; ret.Fill(length);
			for (int i = 0; i < length; i++) {
				ret[i] = values[i] + _A[i];
			}
			return ret;
		}
		else {
			return Vector();
		}
	}
	Vector Vector::operator*(double _S) {
		Vector ret;
		ret.Fill(length);
		for (int i = 0; i < length; i++) {
			ret[i] = values[i] * _S;
		}
		return ret;
	}

	double Vector::Dot(Vector _V) {
		double ret = 0;
		if (length == _V.length) {
			for (int i = 0; i < length; i++) {
				ret += values[i] * _V[i];
			}
			return ret;
		}
		else {
			return 0.0001e-10;
		}
	}
	Vector Vector::Cross(Vector _V) {
		if (length == _V.length) {
			
			if (length == 2) {
				Vector ret; ret.Fill(1);
				ret[0] = values[0] * _V[1] - _V[0] * values[1];
				return ret;
			}
			else if (length == 3) {
				Vector ret; ret.Fill(3);
				std::vector<double> V = values;
				std::vector<double> W = _V.values;

				ret[0] = V[1] * W[2] - W[1] * V[2];
				ret[1] = V[2] * W[0] - W[2] * V[0];
				ret[2] = V[0] * W[1] - W[0] * V[1];

				return ret;

			}
			else {
				return Vector();
			}
		}
		else {
			return Vector();
		}
	}






	Vector_Complex::Vector_Complex() {
		length = 0;
	}
	Vector_Complex::Vector_Complex(std::vector<Complex> _V) {
		values = _V;
		length = values.size();
	}
	Vector_Complex::~Vector_Complex() {
	}

	void Vector_Complex::Fill(int _Length, Complex _Init) {
		values.resize(_Length, _Init);
		length = _Length;
	}

	std::vector<Complex> Vector_Complex::VectorType() {
		return values;
	}
	void Vector_Complex::operator=(std::vector<Complex> _Set) {
		values = _Set;
		length = values.size();
	}

	int Vector_Complex::Length() {
		return length;
	}


	Complex& Vector_Complex::operator[](int _Id) {
		return values[_Id];
	}
	void Vector_Complex::operator=(Vector_Complex _Set) {
		values = _Set.values;
		length = _Set.length;
	}

	Vector_Complex Vector_Complex::operator+(Vector_Complex _A) {
		if (length == _A.length) {
			Vector_Complex ret; ret.Fill(length);
			for (int i = 0; i < length; i++) {
				ret[i] = values[i] + _A[i];
			}
			return ret;
		}
		else {
			return Vector_Complex();
		}
	}
	Vector_Complex Vector_Complex::operator*(Complex _S) {
		Vector_Complex ret;
		ret.Fill(length);
		for (int i = 0; i < length; i++) {
			ret[i] = values[i] * _S;
		}
		return ret;
	}

	Complex Vector_Complex::Dot(Vector_Complex _V) {
		Complex ret = 0;
		if (length == _V.length) {
			for (int i = 0; i < length; i++) {
				ret += values[i] * _V[i];
			}
			return ret;
		}
		else {
			return 0.0001e-10;
		}
	}
	Vector_Complex Vector_Complex::Cross(Vector_Complex _V) {
		if (length == _V.length) {

			if (length == 2) {
				Vector_Complex ret; ret.Fill(1);
				ret[0] = values[0] * _V[1] - _V[0] * values[1];
				return ret;
			}
			else if (length == 3) {
				Vector_Complex ret; ret.Fill(3);
				std::vector<Complex> V = values;
				std::vector<Complex> W = _V.values;

				ret[0] = V[1] * W[2] - W[1] * V[2];
				ret[1] = V[2] * W[0] - W[2] * V[0];
				ret[2] = V[0] * W[1] - W[0] * V[1];

				return ret;

			}
			else {
				return Vector_Complex();
			}
		}
		else {
			return Vector_Complex();
		}
	}

}
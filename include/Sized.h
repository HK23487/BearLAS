#pragma once



#ifndef BEARLAS_SIZED_VECTORS_MATRICES_HEADER_H__
#define BEARLAS_SIZED_VECTORS_MATRICES_HEADER_H__


#include "Vector.h"
#include "Matrix.h"

#include <array>

namespace blas
{

	template <size_t S>
	class SizedVector
	{
	public:
		SizedVector() {}
		SizedVector(const std::vector<double>& _Elems) {
			std::copy(_Elems.begin(), _Elems.begin() + S, elems.begin());
		}
		~SizedVector(){}

		void Fill(double _Init) {
			elems.fill(_Init);
		}

		std::array<double, S>& ArrayType() {
			return elems;
		}

		const std::array<double, S> ArrayType() const {
			return elems;
		}

		std::vector<double> VectorType() {
			return std::vector<double>(elems.begin(), elems.end());
		}

		const std::vector<double> VectorType() const {
			const std::vector<double> ret(elems.begin(), elems.end());
			return ret;
		}

		Vector BlasVector() {
			return Vector(VectorType());
		}

		const Vector BlasVector() const {
			return Vector(VectorType());
		}

		size_t Length() { return S; }

		const size_t Length() const { return S; }

		double& operator[] (int _Id) {
			return elems[_Id];
		}
		const double operator[] (int _Id) const {
			return elems[_Id];
		}

		void operator= (const Vector& _Set) {
			auto _Elems = _Set.VectorType();
			std::copy(_Elems.begin(), _Elems.begin() + S, elems.begin());
		}

		void operator= (const std::array<double, S>& _Set) {
			elems = _Set;
		}

		SizedVector<S> operator+(const SizedVector<S>& _V) {
			return SizedVector<S>((BlasVector() + _V.BlasVector()).VectorType());
		}
		SizedVector<S> operator-(const SizedVector<S>& _V) {
			return SizedVector<S>((BlasVector() - _V.BlasVector()).VectorType());
		}
		SizedVector<S> operator*(const double& _V) {
			return SizedVector<S>((BlasVector() * _V).VectorType());
		}
		SizedVector<S> operator/(const double& _V) {
			return SizedVector<S>((BlasVector() / _V).VectorType());
		}

		SizedVector<S> operator+(const SizedVector<S>& _V) const {
			return SizedVector<S>((BlasVector() + _V.BlasVector()).VectorType());
		}										  
		SizedVector<S> operator-(const SizedVector<S>& _V) const {
			return SizedVector<S>((BlasVector() - _V.BlasVector()).VectorType());
		}										  
		SizedVector<S> operator*(const double& _V) const {
			return SizedVector<S>((BlasVector() * _V).VectorType());
		}										  
		SizedVector<S> operator/(const double& _V) const {
			return SizedVector<S>((BlasVector() / _V).VectorType());
		}

		double Dot(const SizedVector<S>& _V) {
			return (BlasVector().Dot(_V.BlasVector()));
		}											
		double Dot(const SizedVector<S>& _V) const {
			return (BlasVector().Dot(_V.BlasVector()));
		}

		SizedVector<S> Cross(const SizedVector<S>& _V) {
			return SizedVector<S>((BlasVector().Cross(_V.BlasVector())).VectorType());
		}
		SizedVector<S> Cross(const SizedVector<S>& _V) const {
			return SizedVector<S>((BlasVector().Cross(_V.BlasVector())).VectorType());
		}


		operator Vector() const { return BlasVector(); }


	private:
		std::array<double, S> elems;

	};

	typedef SizedVector<2> vec2d;
	typedef SizedVector<3> vec3d;
	typedef SizedVector<4> vec4d;

	template <size_t S>
	std::vector<Vector> Convert(std::vector<SizedVector<S>> _V) {
		std::vector<Vector> ret;
		for (auto& v : _V) {
			ret.push_back(v);
		}
		return ret;
	}




	template <size_t R, size_t C>
	class SizedMatrix 
	{
	public:
		SizedMatrix() {}
		SizedMatrix(const std::array<SizedVector<C>, R>& _Elems) {
			//std::copy(_Elems.begin(), _Elems.begin() + R, elems.begin());
			elems = _Elems;
		}
		~SizedMatrix() {}


		void Fill(double _Init) {
			std::vector<double> row; row.resize(C, _Init);
			elems.fill(SizedVector<C>(row));
		}

		std::array<SizedVector<C>, R>& ArrayType() {
			return elems;
		}

		const std::array<SizedVector<C>, R> ArrayType() const {
			return elems;
		}

		std::vector<SizedVector<C>> VectorType() {
			return std::vector<SizedVector<C>>(elems.begin(), elems.end());
		}

		const std::vector<SizedVector<C>> VectorType() const {
			const std::vector<SizedVector<C>> ret(elems.begin(), elems.end());
			return ret;
		}
		
		Matrix BlasMatrix() {
			return Matrix(Convert<C>(VectorType()));
		}

		const Matrix BlasMatrix() const {
			return Matrix(Convert<C>(VectorType()));
		}

		void operator=(std::vector<const SizedVector<C>&> _Rows) {
			std::copy(_Rows.begin(), _Rows.begin() + R, elems.begin());
		}

		void operator=(const Matrix& _Set) {
			auto __Elems = _Set.VectorType();
			std::vector<SizedVector<C>, R> _Elems;
			for (auto& v : __Elems) {
				_Elems.push_back(SizedVector<C>(v.VectorType()));
			}
			std::copy(_Elems.begin(), _Elems.begin() + R, elems.begin());
		}


		const std::pair<size_t, size_t> Dimensions() {
			return std::pair<size_t, size_t>(R, C);
		}

		const std::pair<size_t, size_t> Dimensions() const {
			return std::pair<size_t, size_t>(R, C);
		}

		SizedVector<C>& operator[](int _Id) {
			return elems[_Id];
		}

		const SizedVector<C> operator[](int _Id) const {
			return elems[_Id];
		}

		SizedMatrix<R, C> operator+(const SizedMatrix<R, C>& _A) {
			return SizedMatrix<R, C>(Convert<C>((BlasMatrix() + _A.BlasMatrix()).VectorType()));
		}
		SizedVector<R>    operator*(const SizedVector<C>& _V) {
			return SizedVector<R>((BlasMatrix() * _V.BlasVector()).VectorType());
		}
		SizedMatrix<R, C> operator*(double _S) {
			return SizedMatrix<R, C>(Convert<C>((BlasMatrix() * _S).VectorType()));
		}
		SizedMatrix<R, C> operator/(double _S) {
			return SizedMatrix<R, C>(Convert<C>((BlasMatrix() / _S).VectorType()));
		}
		SizedMatrix<R, C> operator*(const SizedMatrix<R, C>& _M) {
			return SizedMatrix<R, C>(Convert<C>((BlasMatrix() * _M.BlasMatrix()).VectorType()));
		}

		SizedMatrix<R, C> operator+(const SizedMatrix<R, C>& _A) const {
			return SizedMatrix<R, C>(Convert<C>((BlasMatrix() + _A.BlasMatrix()).VectorType()));
		}
		SizedVector<R>    operator*(const SizedVector<C>& _V) const {
			return SizedVector<R>((BlasMatrix() * _V.BlasVector()).VectorType());
		}
		SizedMatrix<R, C> operator*(double _S) const {
			return SizedMatrix<R, C>(Convert<C>((BlasMatrix() * _S).VectorType()));
		}
		SizedMatrix<R, C> operator/(double _S) const {
			return SizedMatrix<R, C>(Convert<C>((BlasMatrix() / _S).VectorType()));
		}
		SizedMatrix<R, C> operator*(const SizedMatrix<R, C>& _M) const {
			return SizedMatrix<R, C>(Convert<C>((BlasMatrix() * _M.BlasMatrix()).VectorType()));
		}


		double Det() {
			return BlasMatrix().Det();
		}
		double Det() const {
			return BlasMatrix().Det();
		}

		bool Square() {
			return R == C;
		}
		bool Square() const {
			return R == C;
		}



	private:
		std::array<SizedVector<C>, R> elems;

	};

	typedef SizedMatrix<2, 2> mat2x2;
	typedef SizedMatrix<3, 3> mat3x3;
	typedef SizedMatrix<4, 4> mat4x4;

	typedef SizedMatrix<2, 3> mat2x3;
	typedef SizedMatrix<3, 2> mat3x2;
	typedef SizedMatrix<3, 4> mat3x4;
	typedef SizedMatrix<4, 3> mat4x3;


}


#endif



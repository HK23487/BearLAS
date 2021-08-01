#pragma once

#include <iterator>
#include <vector>
#include <cassert>
#include <iostream>


#ifndef NDEBUG
#define blas_assert(condition, message) \
    do { if (!(condition)) { std::cerr << "Debug assertion failed!\nFile " << __FILE__ \
                      << " line " << __LINE__ << '\n' << message << '\n'; \
            std::terminate(); } } while (false)
#else
#define blas_assert(condition, message) do { } while (false)
#endif



#ifndef _BEARLAS_MATRIX_H
#define _BEARLAS_MATRIX_H


static_assert(sizeof(size_t) == sizeof(uint32_t), "Error: static_assert, line 10, matrix.h:\n\
sizeof(size_t) is not equal to sizeof(uint32_t). This may cause problems when using BearLAS,\n\
so please explicitly declare that BearLAS needs to change its size type.");


namespace bla
{	

	template <class _Ty>
	class grid
	{
	public:
		using _Valty = _Ty;

		using iterator = _Grid_iterator<grid<_Ty>>;
		using const_iterator = const _Grid_iterator<grid<_Ty>>;
	public:
		grid();
		grid(size_t _RowC, size_t _ColC);
		~grid();

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

		_Ty& at(size_t _Where);
		_Ty& at(size_t _RowIndex, size_t _ColIndex);

		size_t height();
		size_t width();

		void realloc(size_t _RowC, size_t _ColC);
		void dealloc();

		std::vector<_Ty> get_row(size_t _RowIndex);
		std::vector<_Ty> get_col(size_t _ColIndex);


		_Ty at(size_t _Where) const;
		_Ty at(size_t _RowIndex, size_t _ColIndex) const;

		size_t height() const;
		size_t width() const;

		std::vector<_Ty> get_row(size_t _RowIndex) const;
		std::vector<_Ty> get_col(size_t _ColIndex) const;

	private:
		std::vector<_Ty> _elems;
		size_t _col;
		size_t _row;

	};

	struct size2d
	{
		size2d();
		size2d(uint64_t _Single);
		size2d(uint32_t _height, uint32_t _width);

		union
		{
			uint64_t _Single_size_value;

			struct
			{
				uint32_t _Height, _Width;
			};
		};

	};

	
	// Constants

	typedef unsigned char defined_constant_t;


	constexpr defined_constant_t NULL_TYPE = 0;

	constexpr defined_constant_t COL_VECTOR = 1;
	constexpr defined_constant_t ROW_VECTOR = 2;
	
	constexpr defined_constant_t COORDINATE = 4;
	constexpr defined_constant_t COMPRESSED_ROW = 5;
	constexpr defined_constant_t COMPRESSED_COL = 6;
	constexpr defined_constant_t BAND_STORAGE = 7;
	
	constexpr defined_constant_t UNKNOWN_TYPE = 255;
	

	
	template <class _Ty>
	class basic_matrix
	{
	public:

		using size_type = size_t;
		using value_type = _Ty;

	private:

		using _immediate_init_val = std::initializer_list<std::initializer_list<value_type>>;

	public: // immediate initializers + constructors/destructors
		basic_matrix();
		basic_matrix(const grid<value_type>& _Data);
		basic_matrix(_immediate_init_val _Immediate);

		~basic_matrix();

	public: // initializers
		void value_initialize(const value_type& _Val);
		void value_initialize(_immediate_init_val _Immediate);

	public:	// size and memory
		void resize(size_type _NewRowCnt, size_type _NewColCnt);
		void resize(size2d _NewSize);

		size_type height() const;
		size_type width() const;
		size_type total_elem_count() const;
		size2d size() const;

	public: // element access
		value_type& at(size_type _Row, size_type _Col);
		std::vector<value_type> row(size_type _RowInd);
		std::vector<value_type> col(size_type _ColInd);

		value_type at(size_type _Row, size_type _Col) const;
		std::vector<value_type> row(size_type _RowInd) const;
		std::vector<value_type> col(size_type _ColInd) const;

		void set_row(size_type _RowInd, const std::vector<value_type>& _Val);
		void set_col(size_type _ColInd, const std::vector<value_type>& _Val);
		
	public: // basic matrix operations (member functions)
		basic_matrix<value_type> transpose() const;
		basic_matrix<value_type> inverse() const; // TODO: implement after implementing non-member inverse alg

	public: // operators
		std::vector<value_type> operator[](size_type _RowInd);
		std::vector<value_type> operator()(size_type _ColInd);

		std::vector<value_type> operator[](size_type _RowInd) const;
		std::vector<value_type> operator()(size_type _ColInd) const;

		value_type& operator()(size_type _Row, size_type _Col);
		value_type operator()(size_type _Row, size_type _Col) const;
		
	private:
		grid<value_type> _elems;

	};

	using matrix = basic_matrix<double>;
	using matrix_f = basic_matrix<float>;
	using matrix_int16 = basic_matrix<int16_t>;
	using matrix_int32 = basic_matrix<int32_t>;
	using matrix_int64 = basic_matrix<int64_t>;
	using matrix_uint16 = basic_matrix<uint16_t>;
	using matrix_uint32 = basic_matrix<uint32_t>;
	using matrix_uint64 = basic_matrix<uint64_t>;



	template <class _Ty>
	class basic_vector
	{
	public:

		using size_type = size_t;
		using value_type = _Ty;

	public:
		basic_vector();
		basic_vector(const std::vector<_Ty>& _Val, defined_constant_t _How = COL_VECTOR);

		~basic_vector();

	public: // initializers
		void value_initialize(const std::vector<_Ty>& _Val, 
			defined_constant_t _How = COL_VECTOR);
		void value_initialize(const std::initializer_list<_Ty>& _Val,
			defined_constant_t _How = COL_VECTOR);

	public:
		void resize(size_type _NewSize, defined_constant_t _How = COL_VECTOR);

		size_type size();
		size_type size() const;

		defined_constant_t vector_type();
		defined_constant_t vector_type() const;


	public:
		value_type& at(size_type _Where);
		value_type at(size_type _Where) const;

		value_type& operator[](size_type _Where);
		value_type operator[](size_type _Where) const;

		value_type& operator()(size_type _Where);
		value_type operator()(size_type _Where) const;

	public:
		basic_matrix<_Ty> bmatrix();
		basic_matrix<_Ty> bmatrix() const;

		operator basic_matrix<_Ty>();
		operator basic_matrix<_Ty>() const;

	public:
		basic_vector<_Ty> transpose();
		basic_vector<_Ty> transpose() const;

		double mag();
		_Ty mag2();
		
		double mag() const;
		_Ty mag2() const;

	private:
		basic_matrix<_Ty> _mat;
		defined_constant_t _Type;

	};

	using bvector = basic_vector<double>;
	using vector_f = basic_vector<float>;
	using vector_int16 = basic_vector<int16_t>;
	using vector_int32 = basic_vector<int32_t>;
	using vector_int64 = basic_vector<int64_t>;
	using vector_uint16 = basic_vector<uint16_t>;
	using vector_uint32 = basic_vector<uint32_t>;
	using vector_uint64 = basic_vector<uint64_t>;



	template <class _Ty>
	basic_matrix<_Ty> basic_add(const basic_matrix<_Ty>& _A, const basic_matrix<_Ty>& _B)
	{
		basic_matrix<_Ty> _return;
		blas_assert(_A.size() == _B.size(), "size of A and B are not equal");
		if (_A.size() == _B.size())
		{
			_return.resize(_A.size());
			for (size_t i = 0; i < _A.height(); i++)
				for (size_t j = 0; j < _A.width(); j++)
					_return.at(i, j) = _A.at(i, j) + _B.at(i, j);
		}
		return _return;
	}

	template <class _Ty>
	basic_matrix<_Ty> basic_sub(const basic_matrix<_Ty>& _A, const basic_matrix<_Ty>& _B)
	{
		basic_matrix<_Ty> _return;
		blas_assert(_A.size() == _B.size(), "size of A and B are not equal");
		if (_A.size() == _B.size())
		{
			_return.resize(_A.size());
			for (size_t i = 0; i < _A.height(); i++)
				for (size_t j = 0; j < _A.width(); j++)
					_return.at(i, j) = _A.at(i, j) - _B.at(i, j);
		}
		return _return;
	}

	template <class _Ty>
	basic_matrix<_Ty> basic_mul(const basic_matrix<_Ty>& _A, const basic_matrix<_Ty>& _B)
	{
		basic_matrix<_Ty> _return;
		blas_assert(_A.width() == _B.height(), "width of A is not equal to height of B");
		if (_A.width() == _B.height())
		{
			_return.resize(_A.height(), _B.width());
			for (size_t h = 0; h < _B.width(); h++)
				for (size_t i = 0; i < _A.height(); i++)
				{
					_Ty _sum = static_cast<_Ty>(0);
					for (size_t j = 0; j < _A.width(); j++)
						_sum += _A.at(i, j) * _B.at(j, h);
					_return.at(i, h) = _sum;
				}
		}
		return _return;
	}

	template <class _Ty>
	_Ty basic_dot(const basic_vector<_Ty>& _a, const basic_vector<_Ty>& _b)
	{
		_Ty sum = static_cast<_Ty>(0);
		blas_assert(_a.size() == _b.size(), "size of a and b are not equal");
		if (_a.size() == _b.size())
			for (size_t i = 0; i < _a.size(); i++)
				sum += _a.at(i) * _b.at(i);
		return sum;
	}

	template <class _Ty>
	_Ty basic_dot_prod(const basic_vector<_Ty>& _a, const basic_vector<_Ty>& _b)
	{
		basic_matrix<_Ty> _dot = basic_mul(_a.transpose().bmatrix(), _b.bmatrix());
		return _dot.at(0, 0);
	}

	template <class _Ty>
	basic_vector<_Ty> basic_saxpy(const _Ty& _a,
		const basic_vector<_Ty>& _x, const basic_vector<_Ty>& _y)
	{
		basic_vector<_Ty> _return;
		for (size_t i = 0; i < _x.size(); i++)
			_return.at(i) = _x.at(i) * _a;
		for (size_t i = 0; i < _y.size(); i++)
			_return.at(i) += _y.at(i);
		return _return;
	}

}


bool operator==(const bla::size2d& _Left, const bla::size2d& _Right);
bool operator!=(const bla::size2d& _Left, const bla::size2d& _Right);



#endif

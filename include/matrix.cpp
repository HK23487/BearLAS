#include "matrix.h"


namespace bla
{

	template <class _Ty>
	grid<_Ty>::grid() { _col = 0; _row = 0; }

	template <class _Ty>
	grid<_Ty>::grid(size_t _RowC, size_t _ColC) 
	{
		realloc(_RowC, _ColC);
	}

	template <class _Ty>
	grid<_Ty>::~grid()
	{ 
		dealloc();
	}

	template <class _Ty>
	_Grid_iterator<grid<_Ty>> grid<_Ty>::begin()
	{
		_Grid_iterator<grid<_Ty>> b(_elems.data());
		return b;
	}
	template <class _Ty>
	_Grid_iterator<grid<_Ty>> grid<_Ty>::end()
	{
		_Grid_iterator<grid<_Ty>> e(_elems.data() + _elems.size());
		return e;
	}

	template <class _Ty>
	const _Grid_iterator<grid<_Ty>> grid<_Ty>::begin() const
	{
		const _Grid_iterator<grid<_Ty>> b(_elems.data());   
		return b;
	}
	template <class _Ty>
	const _Grid_iterator<grid<_Ty>> grid<_Ty>::end() const
	{
		const _Grid_iterator<grid<_Ty>> e(_elems.data() + _elems.size());
		return e;
	}


	template <class _Ty>
	_Ty& grid<_Ty>::at(size_t _Where)
	{
		return _elems[_Where];
	}

	template <class _Ty>
	_Ty& grid<_Ty>::at(size_t _RowIndex, size_t _ColIndex)
	{
		return _elems[_RowIndex * _col + _ColIndex];
	}

	template <class _Ty>
	size_t grid<_Ty>::height() { return _row; }
	template <class _Ty>
	size_t grid<_Ty>::width() { return _col; }

	template <class _Ty>
	void grid<_Ty>::realloc(size_t _RowC, size_t _ColC)
	{
		dealloc();
		_col = _ColC; _row = _RowC;
		_elems.resize(_RowC * _ColC);
	}
	template <class _Ty>
	void grid<_Ty>::dealloc()
	{
		_elems.clear();
	}

	template <class _Ty>
	std::vector<_Ty> grid<_Ty>::get_row(size_t _RowIndex)
	{
		std::vector<_Ty> row; row.reserve(_col);
		for (size_t i = _RowIndex * _col; i < _RowIndex * _col + _col; i++)
			row.push_back(_elems[i]);
		return row;
	}
	template <class _Ty>
	std::vector<_Ty> grid<_Ty>::get_col(size_t _ColIndex)
	{
		std::vector<_Ty> col; col.reserve(_row);
		for (size_t i = _ColIndex; i < _row * _col; i += _col)
			col.push_back(_elems[i]);
		return col;
	}

	template <class _Ty>
	_Ty grid<_Ty>::at(size_t _Where) const
	{
		return _elems[_Where];
	}
	template <class _Ty>
	_Ty grid<_Ty>::at(size_t _RowIndex, size_t _ColIndex) const
	{
		return _elems[_RowIndex * _col + _ColIndex];
	}
	template <class _Ty>
	size_t grid<_Ty>::height() const
	{
		return _row;
	}
	template <class _Ty>
	size_t grid<_Ty>::width() const
	{
		return _col;
	}
	template <class _Ty>
	std::vector<_Ty> grid<_Ty>::get_row(size_t _RowIndex) const
	{
		std::vector<_Ty> row; row.reserve(_col);
		for (size_t i = _RowIndex * _col; i < _RowIndex * _col + _col; i++)
			row.push_back(_elems[i]);
		return row;
	}
	template <class _Ty>
	std::vector<_Ty> grid<_Ty>::get_col(size_t _ColIndex) const
	{
		std::vector<_Ty> col; col.reserve(_row);
		for (size_t i = _ColIndex; i < _row * _col; i += _col)
			col.push_back(_elems[i]);
		return col;
	}







	template <class _Ty>
	basic_matrix<_Ty>::basic_matrix() {}
	template <class _Ty>
	basic_matrix<_Ty>::basic_matrix(const grid<value_type>& _Data) 
	{
		_elems = _Data;
	}
	template <class _Ty>
	basic_matrix<_Ty>::~basic_matrix() 
	{
		_elems.dealloc();
	}
	template <class _Ty>
	basic_matrix<_Ty>::basic_matrix(_immediate_init_val _Immediate)
	{
		value_initialize(_Immediate);
	}



	template <class _Ty>
	void basic_matrix<_Ty>::value_initialize(const value_type& _Val)
	{
		size_type _ElemCpty = _elems.height() * _elems.width();
		for (size_type i = 0; i < _ElemCpty; i++)
			_elems.at(i) = _Val;
	}
	template <class _Ty>
	void basic_matrix<_Ty>::value_initialize(_immediate_init_val _Immediate)
	{
		size_type i, j; i = j = 0; _elems.realloc(_Immediate.size(), _Immediate.begin()->size());
		for (auto si : _Immediate)
		{
			j = 0;
			for (auto tv : si)
			{
				_elems.at(i, j) = tv;
				j++;
			}
			i++;
		}
	}


	template <class _Ty>
	void basic_matrix<_Ty>::resize(size_type _NewRowCnt, size_type _NewColCnt)
	{
		_elems.realloc(_NewRowCnt, _NewColCnt);
	}
	template <class _Ty>
	void basic_matrix<_Ty>::resize(size2d _NewSize)
	{
		resize(_NewSize._Height, _NewSize._Width);
	}
	template <class _Ty>
	size_t basic_matrix<_Ty>::height() const
	{
		return _elems.height();
	}
	template <class _Ty>
	size_t basic_matrix<_Ty>::width() const
	{
		return _elems.width();
	}
	template <class _Ty>
	size_t basic_matrix<_Ty>::total_elem_count() const
	{
		return height() * width();
	}
	template <class _Ty>
	size2d basic_matrix<_Ty>::size() const
	{
		return size2d(height(), width());
	}

	template <class _Ty>
	_Ty& basic_matrix<_Ty>::at(size_type _Row, size_type _Col)
	{
		blas_assert(_Row < this->_elems.height(), "matrix (row) subscript out of range");
		blas_assert(_Col < this->_elems.width(), "matrix (column) subscript out of range");
		return _elems.at(_Row, _Col);
	}
	template <class _Ty>
	std::vector<_Ty> basic_matrix<_Ty>::row(size_type _RowInd)
	{
		blas_assert(_RowInd < _elems.height(), "row subscript out of range");
		return _elems.get_row(_RowInd);
	}
	template <class _Ty>
	std::vector<_Ty> basic_matrix<_Ty>::col(size_type _ColInd) 
	{
		blas_assert(_ColInd < _elems.width(), "column subscript out of range");
		return _elems.get_col(_ColInd);
	}
	template <class _Ty>
	void basic_matrix<_Ty>::set_row(size_type _RowInd, const std::vector<value_type>& _Val)
	{
		blas_assert(_RowInd < _elems.height(), "row subscript out of range");
		for (size_type i = 0; i < _elems.width(); i++)
			_elems.at(_RowInd, i) = _Val[i];
	}
	template <class _Ty>
	void basic_matrix<_Ty>::set_col(size_type _ColInd, const std::vector<value_type>& _Val)
	{
		blas_assert(_ColInd < _elems.width(), "column subscript out of range");
		for (size_type i = 0; i < _elems.height(); i++)
			_elems.at(i, _ColInd) = _Val[i];
	}
	template <class _Ty>
	_Ty basic_matrix<_Ty>::at(size_type _Row, size_type _Col) const
	{
		blas_assert(_Row < this->_elems.height(), "matrix (row) subscript out of range");
		blas_assert(_Col < this->_elems.width(), "matrix (column) subscript out of range");
		return _elems.at(_Row, _Col);
	}
	template <class _Ty>
	std::vector<_Ty> basic_matrix<_Ty>::row(size_type _RowInd) const
	{
		blas_assert(_RowInd < _elems.height(), "row subscript out of range");
		return _elems.get_row(_RowInd);
	}
	template <class _Ty>
	std::vector<_Ty> basic_matrix<_Ty>::col(size_type _ColInd) const
	{
		blas_assert(_ColInd < _elems.width(), "column subscript out of range");
		return _elems.get_col(_ColInd);
	}

	template <class _Ty>
	std::vector<_Ty> basic_matrix<_Ty>::operator[](size_type _RowInd)
	{
		return row(_RowInd);
	}
	template <class _Ty>
	std::vector<_Ty> basic_matrix<_Ty>::operator()(size_type _ColInd)
	{
		return col(_ColInd);
	}
	template <class _Ty>
	std::vector<_Ty> basic_matrix<_Ty>::operator[](size_type _RowInd) const
	{
		return row(_RowInd);
	}
	template <class _Ty>
	std::vector<_Ty> basic_matrix<_Ty>::operator()(size_type _ColInd) const
	{
		return col(_ColInd);
	}

	template <class _Ty>
	basic_matrix<_Ty> basic_matrix<_Ty>::transpose() const
	{
		basic_matrix<_Ty> _trans; _trans.resize(this->width(), this->height());
		for (size_type i = 0; i < height(); i++)
			for (size_type j = 0; j < width(); j++)
				_trans.at(j, i) = _elems.at(i, j);
		return _trans;
	}
	template <class _Ty>
	basic_matrix<_Ty> basic_matrix<_Ty>::inverse() const
	{
		return basic_matrix<_Ty>();
	}
	template <class _Ty>
	_Ty& basic_matrix<_Ty>::operator()(size_type _Row, size_type _Col)
	{
		return at(_Row, _Col);
	}
	template <class _Ty>
	_Ty basic_matrix<_Ty>::operator()(size_type _Row, size_type _Col) const
	{
		return at(_Row, _Col);
	}


	



	size2d::size2d()
	{
		_Single_size_value = 0;
	}
	size2d::size2d(uint64_t _Single)
	{
		_Single_size_value = _Single;
	}
	size2d::size2d(uint32_t _height, uint32_t _width)
	{
		_Height = _height;
		_Width = _width;
	}




	template <class _Ty>
	basic_vector<_Ty>::basic_vector()
	{
		_Type = NULL_TYPE;
	}
	template <class _Ty>
	basic_vector<_Ty>::basic_vector(const std::vector<_Ty>& _Val, defined_constant_t _How)
	{
		value_initialize(_Val, _How);
	}
	template <class _Ty>
	basic_vector<_Ty>::~basic_vector()
	{
	}
	template <class _Ty>
	void basic_vector<_Ty>::value_initialize(const std::vector<_Ty>& _Val,
		defined_constant_t _How)
	{
		if (_How == COL_VECTOR)
		{
			_mat.resize(_Val.size(), 1);
			_mat.set_col(0, _Val);
		}
		else if (_How == ROW_VECTOR)
		{
			_mat.resize(1, _Val.size());
			_mat.set_row(0, _Val);
		}
		else
			blas_assert(!(_How == UNKNOWN_TYPE || _How == NULL_TYPE), 
				"vector type not defined");
		_Type = _How;
	}
	template <class _Ty>
	void basic_vector<_Ty>::value_initialize(const std::initializer_list<_Ty>& _Val,
		defined_constant_t _How)
	{
		value_initialize(std::vector<_Ty>(_Val), _How);
	}
	template <class _Ty>
	void basic_vector<_Ty>::resize(size_type _NewSize, defined_constant_t _How)
	{
		if (_How == COL_VECTOR)
			_mat.resize(_NewSize, 1);
		else if (_How == ROW_VECTOR)
			_mat.resize(1, _NewSize);
		else
			blas_assert(!(_How == UNKNOWN_TYPE || _How == NULL_TYPE),
				"vector type not defined");
		_Type = _How;
	}
	template <class _Ty>
	size_t basic_vector<_Ty>::size()
	{
		if (_Type == ROW_VECTOR)
			return _mat.width();
		if (_Type == COL_VECTOR)
			return _mat.height();
		else
			blas_assert(!(_Type == UNKNOWN_TYPE || _Type == NULL_TYPE),
				"vector type not defined"); return 0;
	}
	template <class _Ty>
	size_t basic_vector<_Ty>::size() const
	{
		if (_Type == ROW_VECTOR)
			return _mat.width();
		if (_Type == COL_VECTOR)
			return _mat.height();
		else
			blas_assert(!(_Type == UNKNOWN_TYPE || _Type == NULL_TYPE),
				"vector type not defined"); return 0;
	}
	template <class _Ty>
	defined_constant_t basic_vector<_Ty>::vector_type()
	{
		return _Type;
	}
	template <class _Ty>
	defined_constant_t basic_vector<_Ty>::vector_type() const
	{
		return _Type;
	}
	template <class _Ty>
	_Ty& basic_vector<_Ty>::at(size_type _Where)
	{
		if (_Type == ROW_VECTOR)
			return _mat.at(0, _Where);
		if (_Type == COL_VECTOR)
			return _mat.at(_Where, 0);
		else
			blas_assert(!(_Type == UNKNOWN_TYPE || _Type == NULL_TYPE),
				"vector type not defined"); return _mat.at(0, 0);
	}
	template <class _Ty>
	_Ty basic_vector<_Ty>::at(size_type _Where) const
	{
		if (_Type == ROW_VECTOR)
			return _mat.at(0, _Where);
		if (_Type == COL_VECTOR)
			return _mat.at(_Where, 0);
		else
			blas_assert(!(_Type == UNKNOWN_TYPE || _Type == NULL_TYPE),
				"vector type not defined"); return _mat.at(0, 0);
	}
	template <class _Ty>
	_Ty& basic_vector<_Ty>::operator[](size_type _Where)
	{
		return at(_Where);
	}
	template <class _Ty>
	_Ty basic_vector<_Ty>::operator[](size_type _Where) const
	{
		return at(_Where);
	}
	template <class _Ty>
	_Ty& basic_vector<_Ty>::operator()(size_type _Where)
	{
		return at(_Where);
	}
	template <class _Ty>
	_Ty basic_vector<_Ty>::operator()(size_type _Where) const
	{
		return at(_Where);
	}
	template <class _Ty>
	basic_vector<_Ty> basic_vector<_Ty>::transpose()
	{
		if (_Type == ROW_VECTOR)
			return basic_vector<_Ty>(_mat.transpose().col(0));
		if (_Type == COL_VECTOR)
			return basic_vector<_Ty>(_mat.transpose().row(0));
		else
			blas_assert(!(_Type == UNKNOWN_TYPE || _Type == NULL_TYPE),
				"vector type not defined"); return basic_vector<_Ty>();
	}
	template <class _Ty>
	basic_vector<_Ty> basic_vector<_Ty>::transpose() const
	{
		if (_Type == ROW_VECTOR)
			return basic_vector<_Ty>(_mat.transpose().col(0));
		if (_Type == COL_VECTOR)
			return basic_vector<_Ty>(_mat.transpose().row(0));
		else
			blas_assert(!(_Type == UNKNOWN_TYPE || _Type == NULL_TYPE),
				"vector type not defined"); return basic_vector<_Ty>();
	}
	template <class _Ty>
	basic_matrix<_Ty> basic_vector<_Ty>::bmatrix()
	{
		return _mat;
	}
	template <class _Ty>
	basic_matrix<_Ty> basic_vector<_Ty>::bmatrix() const
	{
		return _mat;
	}
	template <class _Ty>
	basic_vector<_Ty>::operator basic_matrix<_Ty>()
	{
		return bmatrix();
	}
	template <class _Ty>
	basic_vector<_Ty>::operator basic_matrix<_Ty>() const
	{
		return bmatrix();
	}
	template <class _Ty>
	double basic_vector<_Ty>::mag()
	{
		_Ty sum = 0;
		for (size_t i = 0; i < size(); i++)
			sum += at(i) * at(i);
		return std::sqrt(sum);
	}
	template <class _Ty>
	_Ty basic_vector<_Ty>::mag2()
	{
		_Ty sum = 0;
		for (size_t i = 0; i < size(); i++)
			sum += at(i) * at(i);
		return sum;
	}
	template <class _Ty>
	double basic_vector<_Ty>::mag() const
	{
		_Ty sum = 0;
		for (size_t i = 0; i < size(); i++)
			sum += at(i) * at(i);
		return std::sqrt(sum);
	}
	template <class _Ty>
	_Ty basic_vector<_Ty>::mag2() const
	{
		_Ty sum = 0;
		for (size_t i = 0; i < size(); i++)
			sum += at(i) * at(i);
		return sum;
	}



	template class grid<float>;
	template class grid<double>;

	template class grid<int16_t>;
	template class grid<int32_t>;
	template class grid<int64_t>;

	template class grid<uint16_t>;
	template class grid<uint32_t>;
	template class grid<uint64_t>;



	template class basic_matrix<float>;
	template class basic_matrix<double>;

	template class basic_matrix<int16_t>;
	template class basic_matrix<int32_t>;
	template class basic_matrix<int64_t>;

	template class basic_matrix<uint16_t>;
	template class basic_matrix<uint32_t>;
	template class basic_matrix<uint64_t>;


	template class basic_vector<float>;
	template class basic_vector<double>;

	template class basic_vector<int16_t>;
	template class basic_vector<int32_t>;
	template class basic_vector<int64_t>;

	template class basic_vector<uint16_t>;
	template class basic_vector<uint32_t>;
	template class basic_vector<uint64_t>;

	
}



bool operator==(const bla::size2d& _Left, const bla::size2d& _Right)
{
	return _Left._Single_size_value == _Right._Single_size_value;
}

bool operator!=(const bla::size2d& _Left, const bla::size2d& _Right)
{
	return _Left._Single_size_value != _Right._Single_size_value;
}


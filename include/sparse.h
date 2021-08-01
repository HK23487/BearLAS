#pragma once


#include "matrix.h"


namespace bla
{

	template <class _Ty, defined_constant_t _Storage_method>
	class sparse_matrix
	{
	};

	template <class _Ty>
	class sparse_matrix<_Ty, COORDINATE>
	{
	public:

		using value_type = _Ty;
		using size_type = uint32_t;

	public:
		sparse_matrix()
		{
			_Height = _Width = 0;
		}
		sparse_matrix(size_type _Height, size_type _Width)
		{
			this->_Height = _Height;
			this->_Width = _Width;
		}
		
		~sparse_matrix()
		{

		}

	private:
		size_type find_elem(size_type _Row, size_type _Col)
		{
			//size_type _row_it = 0;
			//

			//// Iterate through all row indices and see if _Row is in the list
			//while (_RowInds[_row_it] != _Row && _row_it < _RowInds.size())
			//	_row_it++;
			//if (_row_it >= _Row_Inds.size()) return (size_type)-1; // If there is no _Row, return -1
			//size_type _col_it = _row_it;

			//// Iterate through all col indices with row indices of _Row 
			//// and see if _Col is in the list
			//while (_ColInds[_col_it] != _Col && _col_it < _ColInds.size()
			//	&& _RowInds[_col_it] == _Row)
			//	_col_it++;
			//// If there is no _Col, return -1
			//if (_col_it >= _ColInds.size() || _RowInds[_col_it] != _Row) return (size_type)-1;

			//// If both exists, then return the 1d _col_it index
			//return _col_it;

			blas_assert(_RowInds.size() == _ColInds.size(), 
				"Coordinate Storage matrix corrupted");

			for (size_type i = 0; i < _RowInds.size(); i++)
			{
				if (_RowInds[i] == _Row && _ColInds[i] == _Col) return i;
			}

			return (size_type)-1;

		}

		size_type find_elem(size_type _Row, size_type _Col) const
		{
			blas_assert(_RowInds.size() == _ColInds.size(),
				"Coordinate Storage matrix corrupted");
			for (size_type i = 0; i < _RowInds.size(); i++)
			{
				if (_RowInds[i] == _Row && _ColInds[i] == _Col) return i;
			}
			return (size_type)-1;
		}

	public:
		void resize(uint32_t _Height, uint32_t _Width)
		{
			// Reset width and height
			this->_Height = _Height;
			this->_Width = _Width;

			// Erase data
			_Nz.clear();
			_RowInds.clear();
			_ColInds.clear();
		}
		
		size_type height()
		{
			return _Height;
		}
		size_type width()
		{
			return _Width;
		}
		size_type total_elem_count()
		{
			return _Height * _Width;
		}
		size_type n_nonzeros()
		{
			return _Nz.size();
		}

		size_type height() const
		{
			return _Height;
		}
		size_type width() const
		{
			return _Width;
		}
		size_type total_elem_count() const
		{
			return _Height * _Width;
		}
		size_type n_nonzeros() const
		{
			return _Nz.size();
		}

	public:
		_Ty at(size_type _Row, size_type _Col)
		{
			blas_assert(_RowInds.size() == _ColInds.size(),
				"Coordinate Storage matrix corrupted");
			blas_assert(_Nz.size() == _RowInds.size(), "Coordinate Storage matrix corrupted");

			size_type elem_ind = find_elem(_Row, _Col);
			if (elem_ind == (size_type)-1) return static_cast<_Ty>(0);
			else
			{
				blas_assert(elem_ind < _Nz.size(), "Coordinate Storage matrix corrupted");
				return _Nz[elem_ind];
			}
		}
		std::vector<_Ty> row_v(size_type _Row) // time-consuming; use as little as possible
		{
			std::vector<_Ty> _row;
			for (size_type i = 0; i < _Width; i++)
			{
				_row.push_back(at(_Row, i));
			}
			return _row;
		}
		std::vector<_Ty> col_v(size_type _Col) // time-consuming; use as little as possible
		{
			std::vector<_Ty> _col;
			for (size_type i = 0; i < _Height; i++)
			{
				_col.push_back(at(i, _Col));
			}
			return _col;
		}

		basic_vector<_Ty> row(size_type _Row) // time-consuming; use as little as possible
		{
			std::vector<_Ty> _row;
			for (size_type i = 0; i < _Width; i++)
			{
				_row.push_back(at(_Row, i));
			}
			return basic_vector<_Ty>(_row, ROW_VECTOR);
		}
		basic_vector<_Ty> col(size_type _Col) // time-consuming; use as little as possible
		{
			std::vector<_Ty> _col;
			for (size_type i = 0; i < _Height; i++)
			{
				_col.push_back(at(i, _Col));
			}
			return basic_vector<_Ty>(_col, COL_VECTOR);
		}

		void set(size_type _Row, size_type _Col, _Ty _Val)
		{
			blas_assert(_RowInds.size() == _ColInds.size(),
				"Coordinate Storage matrix corrupted");
			blas_assert(_Nz.size() == _RowInds.size(), "Coordinate Storage matrix corrupted");

			size_type elem_ind = find_elem(_Row, _Col);
			if (elem_ind == (size_type)-1) 
			{
				_Nz.push_back(_Val);
				_RowInds.push_back(_Row);
				_ColInds.push_back(_Col);
			}
			else
			{
				blas_assert(elem_ind < _Nz.size(), "Coordinate Storage matrix corrupted");
				if (_Val == 0) 
				{
					_Nz.erase(_Nz.begin() + elem_ind);
					_RowInds.erase(_RowInds.begin() + elem_ind);
					_ColInds.erase(_ColInds.begin() + elem_ind);
					return;
				}
				_Nz[elem_ind] = _Val;
			}
		}

		_Ty at(size_type _Row, size_type _Col) const
		{
			blas_assert(_RowInds.size() == _ColInds.size(),
				"Coordinate Storage matrix corrupted");
			blas_assert(_Nz.size() == _RowInds.size(), "Coordinate Storage matrix corrupted");

			size_type elem_ind = find_elem(_Row, _Col);
			if (elem_ind == (size_type)-1) return static_cast<_Ty>(0);
			else
			{
				blas_assert(elem_ind < _Nz.size(), "Coordinate Storage matrix corrupted");
				return _Nz[elem_ind];
			}
		}
		std::vector<_Ty> row_v(size_type _Row) const // time-consuming; use as little as possible
		{
			std::vector<_Ty> _row;
			for (size_type i = 0; i < _Width; i++)
			{
				_row.push_back(at(_Row, i));
			}
			return _row;
		}
		std::vector<_Ty> col_v(size_type _Col) const // time-consuming; use as little as possible
		{
			std::vector<_Ty> _col;
			for (size_type i = 0; i < _Height; i++)
			{
				_col.push_back(at(i, _Col));
			}
			return _col;
		}

		basic_vector<_Ty> row(size_type _Row) const // time-consuming; use as little as possible
		{
			std::vector<_Ty> _row;
			for (size_type i = 0; i < _Width; i++)
			{
				_row.push_back(at(_Row, i));
			}
			return basic_vector<_Ty>(_row, ROW_VECTOR);
		}
		basic_vector<_Ty> col(size_type _Col) const // time-consuming; use as little as possible
		{
			std::vector<_Ty> _col;
			for (size_type i = 0; i < _Height; i++)
			{
				_col.push_back(at(i, _Col));
			}
			return basic_vector<_Ty>(_col, COL_VECTOR);
		}



		void set_row_v(size_type _RowInd, const std::vector<_Ty>& _Val) // time-consuming; use as little as possible
		{
			blas_assert(_Val.size() == _Width, "Unreasonable size for _Val");
			for (size_type i = 0; i < _Width; i++)
			{
				set(_RowInd, i, _Val[i]);
			}
			
		}
		void set_col_v(size_type _ColInd, const std::vector<_Ty>& _Val) // time-consuming; use as little as possible
		{
			blas_assert(_Val.size() == _Height, "Unreasonable size for _Val");
			for (size_type i = 0; i < _Height; i++)
			{
				set(i, _ColInd, _Val[i]);
			}
		}

		void set_row(size_type _RowInd, const basic_vector<_Ty>& _Val) // time-consuming; use as little as possible
		{
			blas_assert(_Val.size() == _Width, "Unreasonable size for _Val");
			for (size_type i = 0; i < _Width; i++)
			{
				set(_RowInd, i, _Val[i]);
			}

		}
		void set_col(size_type _ColInd, const basic_vector<_Ty>& _Val) // time-consuming; use as little as possible
		{
			blas_assert(_Val.size() == _Height, "Unreasonable size for _Val");
			for (size_type i = 0; i < _Height; i++)
			{
				set(i, _ColInd, _Val[i]);
			}
		}

		std::vector<_Ty>& nonzeros()
		{
			return _Nz;
		}
		std::vector<_Ty> nonzeros() const
		{
			return _Nz;
		}

		std::vector<size_type>& row_indices()
		{
			return _RowInds;
		}
		std::vector<size_type> row_indices() const
		{
			return _RowInds;
		}

		std::vector<size_type>& col_indices()
		{
			return _ColInds;
		}
		std::vector<size_type> col_indices() const
		{
			return _ColInds;
		}

	private:
		std::vector<_Ty> _Nz;
		std::vector<size_type> _RowInds;
		std::vector<size_type> _ColInds;

		size_type _Height;
		size_type _Width;

	};

	template <class _Ty>
	class sparse_matrix<_Ty, COMPRESSED_ROW>
	{
	public:

		using value_type = _Ty;
		using size_type = uint32_t;

	public:
		sparse_matrix()
		{
			_Height = _Width = 0;
		}
		sparse_matrix(size_type _Height, size_type _Width)
		{
			this->_Height = _Height;
			this->_Width = _Width;

			_RowPtrs.resize(_Height, (size_type)0);
		}

		~sparse_matrix()
		{

		}

	private:
		size_type find_elem(size_type _Row, size_type _Col)
		{
			size_type _first = _RowPtrs[_Row];
			size_type _last;
			if (_Row + 1 == _RowPtrs.size()) { _last = _ColInds.size(); }
			else { _last = _RowPtrs[_Row + 1]; }
			for (size_type i = _first; i < _last; i++)
				if (_ColInds[i] == _Col) return i;
			return (size_type)-1;
		}

	public:
		void resize(uint32_t _Height, uint32_t _Width)
		{
			// Reset width and height
			this->_Height = _Height;
			this->_Width = _Width;

			// Erase data
			_Nz.clear();
			_RowPtrs.clear();
			_RowPtrs.resize(_Height, (size_type)0);
			_ColInds.clear();
		}

		size_type height()
		{
			return _Height;
		}
		size_type width()
		{
			return _Width;
		}
		size_type total_elem_count()
		{
			return _Height * _Width;
		}
		size_type n_nonzeros()
		{
			return _Nz.size();
		}

		size_type height() const
		{
			return _Height;
		}
		size_type width() const
		{
			return _Width;
		}
		size_type total_elem_count() const
		{
			return _Height * _Width;
		}
		size_type n_nonzeros() const
		{
			return _Nz.size();
		}

	private:
		void update_row_ptr(size_type _Ind, bool _Dir, int32_t _By, bool _Inclusive = false)
		{
			if (_Dir)
				for (size_type i = _Ind; i < _RowPtrs.size(); i++)
				{
					if (i == _Ind && _Inclusive) _RowPtrs[i] += _By;
					else if (i == _Ind && !_Inclusive) continue;
					else _RowPtrs[i] += _By;
				}
			else
				for (size_type i = _Ind; i >= 0; i--)
				{
					if (i == _Ind && _Inclusive) _RowPtrs[i] += _By;
					else if (i == _Ind && !_Inclusive) continue;
					else _RowPtrs[i] += _By;
					if (i == 0) break;
				}
		}

		void update_row_ptr_a(size_type _Ind, bool _Dir, uint32_t _Set, bool _Inclusive = false)
		{
			if (_Dir)
				for (size_type i = _Ind; i < _RowPtrs.size(); i++)
				{
					if (i == _Ind && _Inclusive) _RowPtrs[i] = _Set;
					else if (i == _Ind && !_Inclusive) continue;
					else _RowPtrs[i] = _Set;
				}
			else
				for (size_type i = _Ind; i >= 0; --i)
				{
					if (i == _Ind && _Inclusive) _RowPtrs[i] = _Set;
					else if (i == _Ind && !_Inclusive) continue;
					else _RowPtrs[i] = _Set;
					if (i == 0) break;
				}
		}

		

	public:
		_Ty at(size_type _Row, size_type _Col)
		{
			size_type elem_ind = find_elem(_Row, _Col);
			if (elem_ind == (size_type)-1) return static_cast<_Ty>(0);
			else
			{
				blas_assert(elem_ind < _Nz.size(), "Compressed Row Storage matrix corrupted");
				return _Nz[elem_ind];
			}
		}

		void set(size_type _Row, size_type _Col, _Ty _Val)
		{
			size_type elem_ind = find_elem(_Row, _Col);
			if (elem_ind == (size_type)-1)
			{
				if (_ColInds.size() == 0)
				{
					_ColInds.push_back(_Col);
					_Nz.push_back(_Val);
					update_row_ptr_a(_Row, (bool)0, 0, true);
					update_row_ptr(_Row, (bool)1, 1, false);
					return;
				}

				size_type insert_ind = _RowPtrs[_Row];
				size_type _last;
				if (_Row + 1 == _RowPtrs.size()) _last = _ColInds.size();
				else _last = _RowPtrs[_Row + 1];

				if (insert_ind == _last) // Row is empty
				{
					_ColInds.insert(_ColInds.begin() + insert_ind, _Col);
					_Nz.insert(_Nz.begin() + insert_ind, _Val);
					update_row_ptr(_Row, (bool)1, 1, false);
					return;
				}

				for (; insert_ind <= _last; insert_ind++)
				{
					if (insert_ind >= _ColInds.size()) break;
					blas_assert(_ColInds[insert_ind] != _Col, 
						"Compressed Row Storage matrix corrupted");
					if (_ColInds[insert_ind] < _Col) continue;
					if (_ColInds[insert_ind] > _Col) break;
				}

				_ColInds.insert(_ColInds.begin() + insert_ind, _Col);
				_Nz.insert(_Nz.begin() + insert_ind, _Val);
				update_row_ptr(_Row, (bool)1, 1, false);


				/*if (_ColInds.size() == 0)
				{
					_ColInds.push_back(_Col);
					_Nz.push_back(_Val);
					return;
				}
				size_type insert_ind = _RowPtrs[_Row];
				size_type _last;
				if (_Row + 1 == _RowPtrs.size()) _last = _ColInds.size();
				else _last = _RowPtrs[_Row + 1];
				bool is_row_empty = false;
				if (_Row > 0)
				{
					is_row_empty = is_row_empty || (insert_ind == _RowPtrs[_Row - 1]);
				}
				while (true)
				{
					if (is_row_empty) break;
					if (insert_ind + 1 == _last) break;
					if (_ColInds[insert_ind] < _Col) { insert_ind++; continue; }
					if (_ColInds[insert_ind] > _Col) { insert_ind--; break; }
					blas_assert(_ColInds[insert_ind] == _Col,
						"Compressed Row Storage matrix corrupted");
				}
				_ColInds.insert(_ColInds.begin() + insert_ind + 1, _Col);
				_Nz.insert(_Nz.begin() + insert_ind + 1, _Val);
				update_row_ptr(_Row, (bool)1, 1, is_row_empty);*/
			}
			else
			{
				blas_assert(elem_ind < _Nz.size(), "Compressed Row Storage matrix corrupted");
				if (_Val == 0)
				{
					_Nz.erase(_Nz.begin() + elem_ind);
					_ColInds.erase(_ColInds.begin() + elem_ind);
					update_row_ptr(_Row, (bool)1, -1, false);
					return;
				}
				_Nz[elem_ind] = _Val;
			}
		}

	public:
		std::vector<_Ty> row_v(size_type _Row) // time-consuming; use as little as possible
		{
			std::vector<_Ty> _row;
			for (size_type i = 0; i < _Width; i++)
			{
				_row.push_back(at(_Row, i));
			}
			return _row;
		}
		std::vector<_Ty> col_v(size_type _Col) // time-consuming; use as little as possible
		{
			std::vector<_Ty> _col;
			for (size_type i = 0; i < _Height; i++)
			{
				_col.push_back(at(i, _Col));
			}
			return _col;
		}

		basic_vector<_Ty> row(size_type _Row) // time-consuming; use as little as possible
		{
			std::vector<_Ty> _row;
			for (size_type i = 0; i < _Width; i++)
			{
				_row.push_back(at(_Row, i));
			}
			return basic_vector<_Ty>(_row, ROW_VECTOR);
		}
		basic_vector<_Ty> col(size_type _Col) // time-consuming; use as little as possible
		{
			std::vector<_Ty> _col;
			for (size_type i = 0; i < _Height; i++)
			{
				_col.push_back(at(i, _Col));
			}
			return basic_vector<_Ty>(_col, COL_VECTOR);
		}

		std::vector<_Ty> row_v(size_type _Row) const // time-consuming; use as little as possible
		{
			std::vector<_Ty> _row;
			for (size_type i = 0; i < _Width; i++)
			{
				_row.push_back(at(_Row, i));
			}
			return _row;
		}
		std::vector<_Ty> col_v(size_type _Col) const // time-consuming; use as little as possible
		{
			std::vector<_Ty> _col;
			for (size_type i = 0; i < _Height; i++)
			{
				_col.push_back(at(i, _Col));
			}
			return _col;
		}

		basic_vector<_Ty> row(size_type _Row) const // time-consuming; use as little as possible
		{
			std::vector<_Ty> _row;
			for (size_type i = 0; i < _Width; i++)
			{
				_row.push_back(at(_Row, i));
			}
			return basic_vector<_Ty>(_row, ROW_VECTOR);
		}
		basic_vector<_Ty> col(size_type _Col) const // time-consuming; use as little as possible
		{
			std::vector<_Ty> _col;
			for (size_type i = 0; i < _Height; i++)
			{
				_col.push_back(at(i, _Col));
			}
			return basic_vector<_Ty>(_col, COL_VECTOR);
		}

		void set_row_v(size_type _RowInd, const std::vector<_Ty>& _Val) // time-consuming; use as little as possible
		{
			blas_assert(_Val.size() == _Width, "Unreasonable size for _Val");
			for (size_type i = 0; i < _Width; i++)
			{
				set(_RowInd, i, _Val[i]);
			}

		}
		void set_col_v(size_type _ColInd, const std::vector<_Ty>& _Val) // time-consuming; use as little as possible
		{
			blas_assert(_Val.size() == _Height, "Unreasonable size for _Val");
			for (size_type i = 0; i < _Height; i++)
			{
				set(i, _ColInd, _Val[i]);
			}
		}

		void set_row(size_type _RowInd, const basic_vector<_Ty>& _Val) // time-consuming; use as little as possible
		{
			blas_assert(_Val.size() == _Width, "Unreasonable size for _Val");
			for (size_type i = 0; i < _Width; i++)
			{
				set(_RowInd, i, _Val[i]);
			}

		}
		void set_col(size_type _ColInd, const basic_vector<_Ty>& _Val) // time-consuming; use as little as possible
		{
			blas_assert(_Val.size() == _Height, "Unreasonable size for _Val");
			for (size_type i = 0; i < _Height; i++)
			{
				set(i, _ColInd, _Val[i]);
			}
		}

		std::vector<_Ty>& nonzeros()
		{
			return _Nz;
		}
		std::vector<size_type>& row_pointers()
		{
			return _RowPtrs;
		}
		std::vector<size_type>& col_indices()
		{
			return _ColInds;
		}

		std::vector<_Ty> nonzeros() const
		{
			return _Nz;
		}
		std::vector<size_type> row_pointers() const
		{
			return _RowPtrs;
		}
		std::vector<size_type> col_indices() const
		{
			return _ColInds;
		}

	private:
		std::vector<_Ty> _Nz;
		std::vector<size_type> _RowPtrs;
		std::vector<size_type> _ColInds;

		size_type _Height;
		size_type _Width;

	};


}



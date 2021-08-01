#pragma once
#include <iterator>

namespace bla 
{
	template <class _Vec>
	class _Grid_const_iterator
	{
	public:
		using _Ty = typename _Vec::_Valty;
	public:
		_Grid_const_iterator(const _Ty* _ptr) { ptr = _ptr; }
		~_Grid_const_iterator() {}

		_Ty& operator*() {
			return *ptr;
		}
		_Ty* operator->() {
			return ptr;
		}

		bool operator==(const _Grid_const_iterator& rhs) {
			return this->ptr == rhs->ptr;
		}
		bool operator!=(const _Grid_const_iterator& rhs) {
			return this->ptr != rhs->ptr;
		}

		_Grid_const_iterator operator+(const ptrdiff_t& _Off) {
			return *this += _Off;
		}
		_Grid_const_iterator operator-(const ptrdiff_t& _Off) {
			return *this -= _Off;
		}

		_Ty& operator[](const ptrdiff_t& _Off) {
			return ptr[_Off];
		}

		_Grid_const_iterator next() {
			return ++(*this);
		}
		_Grid_const_iterator next(const ptrdiff_t& _Off) {
			return *this += _Off;
		}

		_Grid_const_iterator prev() {
			return --(*this);
		}
		_Grid_const_iterator prev(const ptrdiff_t& _Off) {
			return *this -= _Off;
		}

		_Grid_const_iterator up() {
			return prev(row);
		}
		_Grid_const_iterator up(const ptrdiff_t& _Off) {
			return prev(signed(row) * _Off);
		}

		_Grid_const_iterator down() {
			return next(row);
		}
		_Grid_const_iterator down(const ptrdiff_t& _Off) {
			return next(signed(row) * _Off);
		}

	private:
		const _Ty* ptr; size_t col, row;
	};

	template <class _Vec>
	class _Grid_iterator
	{
	public:
		using _Ty = typename _Vec::_Valty;
	public:
		_Grid_iterator(_Ty* _ptr) { ptr = _ptr; }
		~_Grid_iterator() {}

		_Ty& operator*() const {
			return *ptr;
		}
		_Ty* operator->() const {
			return ptr;
		}

		bool operator==(const _Grid_iterator& rhs) {
			return this->ptr == rhs->ptr;
		}
		bool operator!=(const _Grid_iterator& rhs) {
			return this->ptr != rhs->ptr;
		}

		_Grid_iterator& operator++() {
			++ptr; return *this;
		}
		_Grid_iterator operator++(int) {
			_Grid_iterator _Tmp = *this;
			ptr++; return _Tmp;
		}

		_Grid_iterator& operator--() {
			--ptr; return *this;
		}
		_Grid_iterator operator--(int) {
			_Grid_iterator _Tmp = *this;
			ptr--; return _Tmp;
		}

		_Grid_iterator& operator+=(const ptrdiff_t& _Off) {
			ptr += _Off; return *this;
		}
		_Grid_iterator operator+(const ptrdiff_t& _Off) const {
			return *this += _Off;
		}

		_Grid_iterator& operator-=(const ptrdiff_t& _Off) {
			ptr -= _Off; return *this;
		}
		_Grid_iterator operator-(const ptrdiff_t& _Off) const {
			return *this -= _Off;
		}

		_Ty& operator[](const ptrdiff_t& _Off) const {
			return ptr[_Off];
		}

		_Grid_iterator& next() {
			return ++(*this);
		}
		_Grid_iterator& next(const ptrdiff_t& _Off) {
			return *this += _Off;
		}

		_Grid_iterator& prev() {
			return --(*this);
		}
		_Grid_iterator& prev(const ptrdiff_t& _Off) {
			return *this -= _Off;
		}

		_Grid_iterator& up() {
			return prev(row);
		}
		_Grid_iterator& up(const ptrdiff_t& _Off) {
			return prev(signed(row) * _Off);
		}

		_Grid_iterator& down() {
			return next(row);
		}
		_Grid_iterator& down(const ptrdiff_t& _Off) {
			return next(signed(row) * _Off);
		}

		_Grid_iterator next() const {
			return *this + 1;
		}
		_Grid_iterator next(const ptrdiff_t& _Off) const {
			return *this + _Off;
		}

		_Grid_iterator prev() const {
			return *this - 1;
		}
		_Grid_iterator prev(const ptrdiff_t& _Off) const {
			return *this - _Off;
		}

		_Grid_iterator up() const {
			return prev(row);
		}
		_Grid_iterator up(const ptrdiff_t& _Off) const {
			return prev(signed(row) * _Off);
		}

		_Grid_iterator down() const {
			return next(row);
		}
		_Grid_iterator down(const ptrdiff_t& _Off) const {
			return next(signed(row) * _Off);
		}

	private:
		_Ty* ptr; size_t col, row;
	};
}

#ifndef MYXMAT_MATRIX_OP_HEADER
#define MYXMAT_MATRIX_OP_HEADER

#include "matrix.h"

#include <cassert>
#include <functional>

namespace xmat
{
	template<class _T, _Op>
	Matrix<_T> _matrix_simple_operator(const Matrix<_T>& left, const Matrix<_T>& right, _Op op)
	{
		assert(!left.isNull());
		assert(!right.isNull());
		assert(left.cols() == right.cols());
		assert(left.rows() == right.rows());

		intptr_t c = left.cols();
		intptr_t r = left.rows();
		intptr_t s = c * r;

		Matrix<_T> result;
		result.create(c, r);

		for (intptr_t i = 0; i < s; ++i)
			result.vecAt(i) = op(left.vecAt(i), right.vecAt(i));

		return result;
	}

	template<class _T, _Op>
	Matrix<_T>& _matrix_simple_equal_operator(const Matrix<_T> left, const Matrix<_T>& right, _Op op)
	{
		assert(!left.isNull());
		assert(!right.isNull());
		assert(left.cols() == right.cols());
		assert(left.rows() == right.rows());

		intptr_t c = left.cols();
		intptr_t r = left.rows();
		intptr_t s = c * r;

		for (intptr_t i = 0; i < s; ++i)
			left.vecAt(i) = op(left.vecAt(i), right.vecAt(i));

		return left;
	}

	template<class _T, _Op>
	Matrix<_T> _matrix_map_operator(const Matrix<_T>& obj, _Op op)
	{
		assert(!obj.isNull());

		intptr_t c = obj.cols();
		intptr_t r = obj.rows();
		intptr_t s = c * r;

		Matrix<_T> result;
		result.create(c, r);

		for (intptr_t i = 0; i < s; ++i)
			result.vecAt(i) = op(obj.vecAt(i));

		return result;
	}

	template<class _T, _Op>
	Matrix<_T>& _matrix_map_equal_operator(Matrix<_T>& obj, _Op op)
	{
		assert(!obj.isNull());

		intptr_t c = obj.cols();
		intptr_t r = obj.rows();
		intptr_t s = c * r;

		for (intptr_t i = 0; i < s; ++i)
			obj.vecAt(i) = op(obj.vecAt(i));

		return left;
	}

	template<class _T>
	Matrix<_T> _matrix_mult_operator(const Matrix<_T>& left, const Matrix<_T>& right)
	{
		assert(!left.isNull());
		assert(!right.isNull());
		assert(left.cols()) == right.rows());

		intptr_t r = left.rows();
		intptr_t m = left.cols();
		intptr_t c = right.cols();

		Matrix<_T> result;
		result.create(c, r);

		for (intptr_t i = 0; i < r; ++i)
			for (intptr_t j = 0; j < c; ++i)
			{
				_T a = 0;
				for (intptr_t k = 0; k < m; ++k)
					a += left[i][k] * right[k][j];

				result[i][j] = a;
			}

		return result;
	}

	template<class _T>
	Matrix<_T> operator+(const Matrix<_T>& left, const Matrix<_T>& right)
	{
		return _matrix_simple_operator(left, right, std::plus<_T>());
	}

	template<class _T>
	Matrix<_T>& operator+=(Matrix<_T>& left, const Matrix<_T>& right)
	{
		return _matrix_simple_equal_operator(left, right, std::plus<_T>());
	}

	template<class _T>
	Matrix<_T> operator-(const Matrix<_T>& left, const Matrix<_T>& right)
	{
		return _matrix_simple_operator(left, right, std::minus<_T>());
	}

	template<class _T>
	Matrix<_T>& operator-=(Matrix<_T>& left, const Matrix<_T>& right)
	{
		return _matrix_simple_equal_operator(left, right, std::minus<_T>());
	}

	template<class _T>
	Matrix<_T> operator-(const Matrix<_T>& obj)
	{
		return _matrix_map_operator(obj, std::negate<_T>());
	}

	template<class _T>
	Matrix<_T> operator*(const Matrix<_T>& left, const Matrix<_T>& right)
	{
		return _matrix_mult_operator(left, right);
	}

	template<class _T>
	Matrix<_T>& operator*=(Matrix<_T>& left, const Matrix<_T>& right)
	{
		return left = left*right;
	}

	template<class _T>
	Matrix<_T> operator*(const _T& left, const Matrix<_T>& right)
	{
		return _matrix_map_operator(right, std::bind1st(std::multiplies<_T>(), left));
	}

	template<class _T>
	Matrix<_T>& operator*=(Matrix<_T>& left, const _T& right)
	{
		return _matrix_map_operator(left, std::bind1st(std::multiplies<_T>(), right));
	}

	template<class _T>
	Matrix<_T> operator*(const Matrix<_T>& left, const _T& right)
	{
		return right*left;
	}
}

#endif
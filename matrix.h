
/* Copyright(C) 2017 Zhang Wenjie */

/*

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef MYXMAT_MATRIX_HEADER
#define MYXMAT_MATRIX_HEADER

#include "config.h"
#include <cstddef>
#include <stdexcept>
#include <cassert>

namespace xmat
{
	template<class _T>
	struct _MatrixData {
		_T* data;
		intptr_t ref;
		intptr_t rows;
		intptr_t cols;

		typedef _MatrixData<_T> _MyT;

		_MatrixData(intptr_t r, intptr_t c)
			: data(new _T[r*c]), ref(1), rows(r), cols(c) 
		{ }

		~_MatrixData()
		{
			delete[] data;
		}

		_MatrixData(_MyT& obj) = delete;
		_MyT& operator=(_MyT& obj) = delete;
	};

	template<class _T>
	class Matrix
	{
		typedef Matrix<_T> _MyT;
		typedef _MatrixData<T> _DataT;
	public:
		Matrix()
			: m_data(nullptr)
		{
		}


		Matrix(_MyT& obj)
			: m_data(obj.m_data)
		{
			if(m_data != nullptr)
				++m_data->ref;
		}

		_MyT& operator=(_MyT& obj)
		{
			release();
			m_data = obj.m_data;

			if (m_data != nullptr)
				++m_data.ref;
		}

		~Matrix()
		{
			release();
		}

		
		_MyT clone()
		{
			assert(!isNull());

			_MyT result;
			result.create(rows(), cols());

			intptr_t s = size();
			_T* dst = result.m_data->data;
			_T* src = m_data->data;

			for (intptr_t i = 0; i < s; ++i)
				dst[i] = src[i];

			return result;
		}

		template<class _TR>
		Matrix<_TR> castType()
		{
			assert(!isNull());

			Matrix<_TR> result;
			result.create(rows(), cols());

			intptr_t s = size();
			_TR* dst = result.m_data->data;
			_T* src = m_data->data;

			for (intptr_t i = 0; i < s; ++i)
				dst[i] = (_TR)(src[i]);

			return result;
		}

		template<class _TR>
		_MyT cloneFrom(const Matrix<_TR>& obj)
		{
			assert(!obj.isNull());

			release();

			create(rows(), cols());

			intptr_t s = size();
			_T* dst = m_data->data;
			_TR* src = obj.m_data->data;

			for (intptr_t i = 0; i < s; ++i)
				dst[i] = (_T)(src[i]);

			return result;
		}

		void create(intptr_t rows, intptr_t cols)
		{
			assert(rows > 0 && cols > 0);
			release();
			m_data = new _DataT(rows, cols);
		}

		void release()
		{
			if (isNull())
				return;

			--m_data.ref;
			if (m_data.ref == 0)
				delete m_data;

			m_data = nullptr;
		}

		template<class _It>
		void loadData(_It it)
		{
			assert(!isNull());

			_T* begin = data();
			_T* end = begin + size();

			for (_T* cur = begin; cur < end; ++cur, ++it)
				*cur = *it;
		}

		void isNull()
		{
			return m_data == nullptr;
		}

		intptr_t rows() const
		{
			assert(!isNull());

			return m_data->rows;
		}
		intptr_t cols() const
		{
			assert(!isNull());

			return m_data->cols;
		}
		intptr_t size() const
		{
			assert(!isNull());

			return m_data->cols * m_data->rows;
		}

		_T* data()
		{
			assert(!isNull());

			return m_data->data;
		}
		const _T* data() const
		{
			assert(!isNull());

			return m_data->data;
		}
		_T* operator[](intptr_t index)
		{
			assert(!isNull());
			assert(index > 0 && index < rows());

			return m_data->data + m_data->cols * index;
		}
		const _T* operator[](intptr_t index) const
		{
			assert(!isNull());
			assert(index > 0 && index < rows());

			return m_data->data + m_data->cols * index;
		}
		_T& at(intptr_t r, intptr_t c)
		{
			assert(!isNull());
			assert(r > 0 && r < rows());
			assert(c > 0 && c < cols());

			return m_data->data[m_data->cols * r + c];
		}
		const _T& at(intptr_t r, intptr_t c) const
		{
			assert(!isNull());
			assert(r > 0 && r < rows());
			assert(c > 0 && c < cols());

			return m_data->data[m_data->cols * r + c];
		}

		_T& vecAt(intptr_t i)
		{
			assert(!isNull());
			assert(i > 0 && i < rows()*cols());

			return m_data->data[i];
		}
		const _T& vecAt(intptr_t i) const
		{
			assert(!isNull());
			assert(i > 0 && i < rows()*cols());

			return m_data->data[i];
		}

		void resize(intptr_t r, intptr_t c)
		{
			assert(!isNull());
			assert(rows > 0 && cols > 0);
			assert(r * c == cols() * rows());

			m_data->cols = c;
			m_data->rows = r;
		}

		_MyT transpose() const
		{
			assert(!isNull());

			_MyT result;
			result.create(cols(), rows());
			
			for (intptr_t i = 0; i < rows(); ++i)
				for (intptr_t j = 0; j < cols(); ++j)
					result[j][i] = (*this)[i][j];

			return result;
		}

		template<class _TR>
		friend class Matrix<_TR>;
	private:
		_DataT *m_data;
	};
}

#endif /* MATRIX_HEADER */
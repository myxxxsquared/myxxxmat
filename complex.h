
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


#ifndef MYXMAT_COMPLEX_HEADER
#define MYXMAT_COMPLEX_HEADER

#include "config.h"

namespace xmat
{
	template<class _T>
	struct Complex
	{
		_T real;
		_T imaginary;

		Complex()
			: real(0), imaginary(0)
		{}

		Complex(_T r, _T i)
			: real(r), imaginary(i)
		{}


	};


}

#endif /* MYXMAT_COMPLEX_HEADER */
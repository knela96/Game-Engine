/* 
Generic Memory Manager (memory-mgr)
http://memory-mgr.sourceforge.net/
Copyright (c) 2007-2008 Anton (shikin) Matosov

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3, 29 June 2007 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA <http://fsf.org/>


Please feel free to contact me via e-mail: shikin@users.sourceforge.net
*/

#ifndef MGR_POINTER_TRATS_HEADER
#define MGR_POINTER_TRATS_HEADER

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

namespace memory_mgr
{
	namespace detail
	{
		class null_type
		{};
	}
	//Base pointer traits class
 	template<class PtrT>
 	struct pointer_traits
 	{
 		typedef PtrT					poiner_type;
 		typedef typename poiner_type::mgr_type		mgr_type;
 
 		static const poiner_type null_ptr;
 	};
 
 	template< class PtrT >
 	const typename pointer_traits< PtrT >::poiner_type pointer_traits< PtrT >::null_ptr = typename pointer_traits< PtrT >::poiner_type( detail::null_type() );

		
}


#endif// MGR_POINTER_TRATS_HEADER

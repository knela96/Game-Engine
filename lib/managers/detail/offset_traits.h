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

#ifndef MGR_OFFSET_TRAITS_HEADER
#define MGR_OFFSET_TRAITS_HEADER

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

namespace memory_mgr
{	
	/**
	   @brief Memory offset traits
	   @details Stores associated types and values, e.g. invalid_offset
	   @tparam OffsetType offset type
	*/
	template<class OffsetType>
	struct offset_traits
	{
		/**
		   @brief type passed as template parameter
		*/
		typedef OffsetType			offset_type;

		/**
		   @brief Value that represents invalid offset, like NULL for pointers
		*/
		static const offset_type	invalid_offset;
	};

	/**
	   @brief Memory offset traits for size_t type
	*/
	template<>
	struct offset_traits<size_t>
	{
		/**
		   @brief type passed as template parameter
		*/
		typedef size_t			offset_type;

		/**
		   @brief Value that represents invalid offset, like NULL for pointers
		*/
		static const offset_type	invalid_offset = static_cast< offset_type >(-1);
	};

	
}


#endif// MGR_OFFSET_TRAITS_HEADER

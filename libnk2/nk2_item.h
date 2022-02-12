/*
 * The item definition of a Nickfile
 *
 * Copyright (C) 2009-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _NK2_ITEM_H )
#define _NK2_ITEM_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct nk2_item_value_entry nk2_item_value_entry_t;

struct nk2_item_value_entry
{
	/* The value type
	 * Consists of 2 bytes
	 */
	uint8_t value_type[ 2 ];

	/* The entry type
	 * Consists of 2 bytes
	 */
	uint8_t entry_type[ 2 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The value data array
	 * Consists of 8 bytes
	 */
	uint8_t value_data_array[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _NK2_ITEM_H ) */


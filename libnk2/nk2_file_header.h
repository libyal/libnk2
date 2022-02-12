/*
 * The file header definition of a Nickfile
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

#if !defined( _NK2_FILE_HEADER_H )
#define _NK2_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct nk2_file_header nk2_file_header_t;

struct nk2_file_header
{
	/* Signature
	 * Consists of 4 bytes
	 * 0x0d 0xf0 0xad 0xba
	 */
	uint8_t signature[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Number of items
	 * Consists of 4 bytes
	 */
	uint8_t number_of_items[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _NK2_FILE_HEADER_H ) */


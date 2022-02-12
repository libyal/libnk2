/*
 * The file footer definition of a Nickfile
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

#if !defined( _NK2_FILE_FOOTER_H )
#define _NK2_FILE_FOOTER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct nk2_file_footer nk2_file_footer_t;

struct nk2_file_footer
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Last written/modification date and time
	 * Consists of 8 bytes
	 * Contains a filetime
	 */
	uint8_t modification_time[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _NK2_FILE_FOOTER_H ) */


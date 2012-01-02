/*
 * Value identifier functions
 *
 * Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBNK2_VALUE_IDENTIFIER_H )
#define _LIBNK2_VALUE_IDENTIFIER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_value_identifier libnk2_value_identifier_t;

struct libnk2_value_identifier
{
	/* The item entry type
	 */
	uint16_t entry_type;

	/* The item entry value type
	 */
	uint16_t value_type;
};

int libnk2_value_identifier_initialize(
     libnk2_value_identifier_t **value_identifier,
     liberror_error_t **error );

int libnk2_value_identifier_free(
     libnk2_value_identifier_t **value_identifier,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif


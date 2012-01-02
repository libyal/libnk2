/*
 * Legacy functions
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

#if !defined( _LIBNK2_LEGACY_H )
#define _LIBNK2_LEGACY_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_extern.h"
#include "libnk2_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBNK2 )

LIBNK2_EXTERN \
int libnk2_file_get_amount_of_items(
     libnk2_file_t *file,
     int *amount_of_items,
     liberror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_amount_of_entries(
     libnk2_item_t *item,
     uint32_t *amount_of_entries,
     liberror_error_t **error );

#endif /* !defined( HAVE_LOCAL_LIBNK2 ) */

#if defined( __cplusplus )
}
#endif

#endif


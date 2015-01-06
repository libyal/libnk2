/*
 * Legacy functions
 *
 * Copyright (C) 2009-2015, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libnk2_file.h"
#include "libnk2_item.h"
#include "libnk2_legacy.h"
#include "libnk2_libcerror.h"
#include "libnk2_types.h"

#if !defined( HAVE_LOCAL_LIBNK2 )

/* Retrieves the amount of items
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_amount_of_items(
     libnk2_file_t *file,
     int *amount_of_items,
     libcerror_error_t **error )
{
	return( libnk2_file_get_number_of_items(
	         file,
	         amount_of_items,
	         error ) );
}

/* Retrieves the amount of entries of the referenced item
 * All sets in an item contain the same amount of entries
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_amount_of_entries(
     libnk2_item_t *item,
     uint32_t *amount_of_entries,
     libcerror_error_t **error )
{
	return( libnk2_item_get_number_of_entries(
	         item,
	         amount_of_entries,
	         error ) );
}

#endif /* !defined( HAVE_LOCAL_LIBNK2 ) */


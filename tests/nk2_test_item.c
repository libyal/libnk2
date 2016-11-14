/*
 * Library item type testing program
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "nk2_test_libcerror.h"
#include "nk2_test_libnk2.h"
#include "nk2_test_macros.h"
#include "nk2_test_memory.h"
#include "nk2_test_unused.h"

#include "../libnk2/libnk2_item.h"

/* Tests the libnk2_item_free function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_item_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libnk2_item_free(
	          NULL,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        NK2_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc NK2_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] NK2_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc NK2_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] NK2_TEST_ATTRIBUTE_UNUSED )
#endif
{
	NK2_TEST_UNREFERENCED_PARAMETER( argc )
	NK2_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ )

	/* TODO: add tests for libnk2_item_initialize */

#endif /* defined( __GNUC__ ) */

	NK2_TEST_RUN(
	 "libnk2_item_free",
	 nk2_test_item_free );

	/* TODO: add tests for libnk2_item_get_number_of_entries */

	/* TODO: add tests for libnk2_item_get_entry_type */

	/* TODO: add tests for libnk2_item_get_value_type */

	/* TODO: add tests for libnk2_item_get_entry_value */

	/* TODO: add tests for libnk2_item_get_entry_value_boolean */

	/* TODO: add tests for libnk2_item_get_entry_value_32bit */

	/* TODO: add tests for libnk2_item_get_entry_value_64bit */

	/* TODO: add tests for libnk2_item_get_entry_value_filetime */

	/* TODO: add tests for libnk2_item_get_entry_value_size */

	/* TODO: add tests for libnk2_item_get_entry_value_floating_point */

	/* TODO: add tests for libnk2_item_get_entry_value_utf8_string_size */

	/* TODO: add tests for libnk2_item_get_entry_value_utf8_string */

	/* TODO: add tests for libnk2_item_get_entry_value_utf16_string_size */

	/* TODO: add tests for libnk2_item_get_entry_value_utf16_string */

	/* TODO: add tests for libnk2_item_get_entry_value_binary_data_size */

	/* TODO: add tests for libnk2_item_get_entry_value_binary_data */

	/* TODO: add tests for libnk2_item_get_entry_value_guid */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


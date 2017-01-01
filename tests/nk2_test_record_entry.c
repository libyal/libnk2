/*
 * Library record_entry type test program
 *
 * Copyright (C) 2009-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libnk2/libnk2_record_entry.h"

/* Tests the libnk2_record_entry_free function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libnk2_record_entry_free(
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

#if defined( __GNUC__ )

#endif /* defined( __GNUC__ ) */

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

	/* TODO: add tests for libnk2_record_entry_initialize */

#endif /* defined( __GNUC__ ) */

	NK2_TEST_RUN(
	 "libnk2_record_entry_free",
	 nk2_test_record_entry_free );

#if defined( __GNUC__ )

	/* TODO: add tests for libnk2_record_entry_read_data */

	/* TODO: add tests for libnk2_record_entry_read_value */

	/* TODO: add tests for libnk2_record_entry_get_entry_type */

	/* TODO: add tests for libnk2_record_entry_get_value_type */

	/* TODO: add tests for libnk2_record_entry_get_data_size */

	/* TODO: add tests for libnk2_record_entry_get_data */

	/* TODO: add tests for libnk2_record_entry_get_data_as_boolean */

	/* TODO: add tests for libnk2_record_entry_get_data_as_16bit_integer */

	/* TODO: add tests for libnk2_record_entry_get_data_as_32bit_integer */

	/* TODO: add tests for libnk2_record_entry_get_data_as_64bit_integer */

	/* TODO: add tests for libnk2_record_entry_get_data_as_filetime */

	/* TODO: add tests for libnk2_record_entry_get_data_as_floatingtime */

	/* TODO: add tests for libnk2_record_entry_get_data_as_size */

	/* TODO: add tests for libnk2_record_entry_get_data_as_floating_point */

	/* TODO: add tests for libnk2_record_entry_get_data_as_utf8_string_size */

	/* TODO: add tests for libnk2_record_entry_get_data_as_utf8_string */

	/* TODO: add tests for libnk2_record_entry_get_data_as_utf16_string_size */

	/* TODO: add tests for libnk2_record_entry_get_data_as_utf16_string */

	/* TODO: add tests for libnk2_record_entry_get_data_as_guid */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


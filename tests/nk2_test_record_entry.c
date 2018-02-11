/*
 * Library record_entry type test program
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
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

uint8_t nk2_test_record_entry_data1[ 16 ] = {
	0x03, 0x00, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

/* Tests the libnk2_record_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                        = 0;

#if defined( HAVE_NK2_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libnk2_record_entry_initialize(
	          &record_entry,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "record_entry",
	 record_entry );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_record_entry_free(
	          &record_entry,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "record_entry",
	 record_entry );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libnk2_record_entry_initialize(
	          NULL,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	record_entry = (libnk2_record_entry_t *) 0x12345678UL;

	result = libnk2_record_entry_initialize(
	          &record_entry,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	record_entry = NULL;

#if defined( HAVE_NK2_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libnk2_record_entry_initialize with malloc failing
		 */
		nk2_test_malloc_attempts_before_fail = test_number;

		result = libnk2_record_entry_initialize(
		          &record_entry,
		          LIBNK2_CODEPAGE_WINDOWS_1252,
		          &error );

		if( nk2_test_malloc_attempts_before_fail != -1 )
		{
			nk2_test_malloc_attempts_before_fail = -1;

			if( record_entry != NULL )
			{
				libnk2_record_entry_free(
				 &record_entry,
				 NULL );
			}
		}
		else
		{
			NK2_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			NK2_TEST_ASSERT_IS_NULL(
			 "record_entry",
			 record_entry );

			NK2_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libnk2_record_entry_initialize with memset failing
		 */
		nk2_test_memset_attempts_before_fail = test_number;

		result = libnk2_record_entry_initialize(
		          &record_entry,
		          LIBNK2_CODEPAGE_WINDOWS_1252,
		          &error );

		if( nk2_test_memset_attempts_before_fail != -1 )
		{
			nk2_test_memset_attempts_before_fail = -1;

			if( record_entry != NULL )
			{
				libnk2_record_entry_free(
				 &record_entry,
				 NULL );
			}
		}
		else
		{
			NK2_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			NK2_TEST_ASSERT_IS_NULL(
			 "record_entry",
			 record_entry );

			NK2_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_NK2_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record_entry != NULL )
	{
		libnk2_record_entry_free(
		 &record_entry,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

/* Tests the libnk2_record_entry_read_data function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_read_data(
     void )
{
	libcerror_error_t *error          = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libnk2_record_entry_initialize(
	          &record_entry,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "record_entry",
	 record_entry );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libnk2_record_entry_read_data(
	          NULL,
	          nk2_test_record_entry_data1,
	          16,
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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          NULL,
	          16,
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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_data1,
	          0,
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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_data1,
	          (size_t) SSIZE_MAX + 1,
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

	/* Clean up
	 */
	result = libnk2_record_entry_free(
	          &record_entry,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "record_entry",
	 record_entry );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record_entry != NULL )
	{
		libnk2_record_entry_free(
		 &record_entry,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

	NK2_TEST_RUN(
	 "libnk2_record_entry_initialize",
	 nk2_test_record_entry_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

	NK2_TEST_RUN(
	 "libnk2_record_entry_free",
	 nk2_test_record_entry_free );

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

	NK2_TEST_RUN(
	 "libnk2_record_entry_read_data",
	 nk2_test_record_entry_read_data );

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

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


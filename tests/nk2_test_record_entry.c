/*
 * Library record_entry type test program
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

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "nk2_test_functions.h"
#include "nk2_test_libbfio.h"
#include "nk2_test_libcerror.h"
#include "nk2_test_libnk2.h"
#include "nk2_test_macros.h"
#include "nk2_test_memory.h"
#include "nk2_test_unused.h"

#include "../libnk2/libnk2_record_entry.h"

uint8_t nk2_test_record_entry_16bit_integer_data1[ 16 ] = {
	0x02, 0x00, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t nk2_test_record_entry_32bit_integer_data1[ 16 ] = {
	0x03, 0x00, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t nk2_test_record_entry_float_32bit_data1[ 16 ] = {
	0x04, 0x00, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t nk2_test_record_entry_floatingtime_data1[ 16 ] = {
	0x07, 0x00, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t nk2_test_record_entry_boolean_data1[ 16 ] = {
	0x0b, 0x00, 0x02, 0x60, 0x94, 0xfd, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00 };

uint8_t nk2_test_record_entry_64bit_integer_data1[ 16 ] = {
	0x14, 0x00, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t nk2_test_record_entry_string_unicode_data1[ 46 ] = {
	0x1f, 0x00, 0xf6, 0x5f, 0x00, 0x00, 0x4c, 0x29, 0xd6, 0x11, 0x26, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x1a, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x6f, 0x00, 0x61, 0x00, 0x63, 0x00, 0x68, 0x00, 0x69, 0x00,
	0x6d, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x7a, 0x00, 0x00, 0x00 };

uint8_t nk2_test_record_entry_filetime_data1[ 16 ] = {
	0x40, 0x00, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

/* Tests the libnk2_record_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_initialize(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

#if defined( HAVE_NK2_TEST_MEMORY )
	int number_of_malloc_fail_tests     = 1;
	int number_of_memset_fail_tests     = 1;
	int test_number                     = 0;
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

	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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

	record_entry = NULL;

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

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
				libnk2_internal_record_entry_free(
				 (libnk2_internal_record_entry_t **) &record_entry,
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
				libnk2_internal_record_entry_free(
				 (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
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
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

	/* Test regular cases
	 */
	record_entry = (libnk2_record_entry_t *) 0x12345678UL;

	result = libnk2_record_entry_free(
	          &record_entry,
	          &error );

	record_entry = NULL;

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

/* Tests the libnk2_internal_record_entry_free function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_internal_record_entry_free(
     void )
{
	uint8_t *value_data                 = NULL;
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

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

	value_data = (uint8_t *) memory_allocate(
	                          sizeof( uint8_t ) * 8 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "value_data",
	 value_data );

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = value_data;

	/* Test regular cases
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
	result = libnk2_internal_record_entry_free(
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
	if( record_entry != NULL )
	{
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_read_data function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_read_data(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

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
	          nk2_test_record_entry_32bit_integer_data1,
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
	          nk2_test_record_entry_32bit_integer_data1,
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
	          nk2_test_record_entry_32bit_integer_data1,
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
	          nk2_test_record_entry_32bit_integer_data1,
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

#if defined( HAVE_NK2_TEST_MEMORY )

	/* Test libnk2_record_entry_read_data with memcpy failing
	 */
	nk2_test_memcpy_attempts_before_fail = 0;

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_32bit_integer_data1,
	          16,
	          &error );

	if( nk2_test_memcpy_attempts_before_fail != -1 )
	{
		nk2_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		NK2_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		NK2_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_NK2_TEST_MEMORY ) */

/* TODO test libnk2_mapi_value_get_data_size failing */

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle    = NULL;
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

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

	/* Initialize file IO handle
	 */
	result = nk2_test_open_file_io_handle(
	          &file_io_handle,
	          nk2_test_record_entry_string_unicode_data1,
	          46,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_read_file_io_handle(
	          record_entry,
	          file_io_handle,
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
	result = libnk2_record_entry_read_file_io_handle(
	          NULL,
	          file_io_handle,
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

	result = libnk2_record_entry_read_file_io_handle(
	          record_entry,
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

#if defined( TODO )
/* TODO fix failing test */

#if defined( HAVE_NK2_TEST_MEMORY )

	/* Test libnk2_record_entry_read_file_io_handle with malloc failing
	 */
	nk2_test_malloc_attempts_before_fail = 0;

	result = libnk2_record_entry_read_file_io_handle(
	          record_entry,
	          file_io_handle,
	          &error );

	if( nk2_test_malloc_attempts_before_fail != -1 )
	{
		nk2_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		NK2_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		NK2_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_NK2_TEST_MEMORY ) */
#endif

	/* Clean up file IO handle
	 */
	result = nk2_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small for record entry
	 */
	result = nk2_test_open_file_io_handle(
	          &file_io_handle,
	          nk2_test_record_entry_string_unicode_data1,
	          8,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_record_entry_read_file_io_handle(
	          record_entry,
	          file_io_handle,
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

	result = nk2_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small for value size
	 */
	result = nk2_test_open_file_io_handle(
	          &file_io_handle,
	          nk2_test_record_entry_string_unicode_data1,
	          18,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_record_entry_read_file_io_handle(
	          record_entry,
	          file_io_handle,
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

	result = nk2_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small for value data
	 */
	result = nk2_test_open_file_io_handle(
	          &file_io_handle,
	          nk2_test_record_entry_string_unicode_data1,
	          22,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_record_entry_read_file_io_handle(
	          record_entry,
	          file_io_handle,
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

	result = nk2_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO test libnk2_record_entry_read_data failing */

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( record_entry != NULL )
	{
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_entry_type function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_entry_type(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	uint32_t entry_type                 = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_32bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_entry_type(
	          record_entry,
	          &entry_type,
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
	result = libnk2_record_entry_get_entry_type(
	          NULL,
	          &entry_type,
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

	result = libnk2_record_entry_get_entry_type(
	          record_entry,
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

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_value_type function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_value_type(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	uint32_t value_type                 = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_32bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_value_type(
	          record_entry,
	          &value_type,
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
	result = libnk2_record_entry_get_value_type(
	          NULL,
	          &value_type,
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

	result = libnk2_record_entry_get_value_type(
	          record_entry,
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

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_size function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_size(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	size_t data_size                    = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_32bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_size(
	          record_entry,
	          &data_size,
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
	result = libnk2_record_entry_get_data_size(
	          NULL,
	          &data_size,
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

	result = libnk2_record_entry_get_data_size(
	          record_entry,
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

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data(
     void )
{
	uint8_t data[ 32 ];

	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_32bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data(
	          record_entry,
	          data,
	          32,
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
	result = libnk2_record_entry_get_data(
	          NULL,
	          data,
	          32,
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

	result = libnk2_record_entry_get_data(
	          record_entry,
	          NULL,
	          32,
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

	result = libnk2_record_entry_get_data(
	          record_entry,
	          data,
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

	result = libnk2_record_entry_get_data(
	          record_entry,
	          data,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data(
	          record_entry,
	          data,
	          32,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

#if defined( TODO )
/* TODO fix failing test */

#if defined( HAVE_NK2_TEST_MEMORY )

	/* Test libnk2_record_entry_get_data with memcpy failing
	 */
	nk2_test_memcpy_attempts_before_fail = 0;

	result = libnk2_record_entry_get_data(
	          record_entry,
	          data,
	          32,
	          &error );

	if( nk2_test_memcpy_attempts_before_fail != -1 )
	{
		nk2_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		NK2_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		NK2_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_NK2_TEST_MEMORY ) */
#endif

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_boolean function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_boolean(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	uint8_t value_boolean               = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_boolean_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_boolean(
	          record_entry,
	          &value_boolean,
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
	result = libnk2_record_entry_get_data_as_boolean(
	          NULL,
	          &value_boolean,
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

	result = libnk2_record_entry_get_data_as_boolean(
	          record_entry,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = 0;

	result = libnk2_record_entry_get_data_as_boolean(
	          record_entry,
	          &value_boolean,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = LIBNK2_VALUE_TYPE_BOOLEAN;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_boolean(
	          record_entry,
	          &value_boolean,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_boolean(
	          record_entry,
	          &value_boolean,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 2;

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_16bit_integer function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_16bit_integer(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	uint16_t value_16bit                = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_16bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_16bit_integer(
	          record_entry,
	          &value_16bit,
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
	result = libnk2_record_entry_get_data_as_16bit_integer(
	          NULL,
	          &value_16bit,
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

	result = libnk2_record_entry_get_data_as_16bit_integer(
	          record_entry,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = 0;

	result = libnk2_record_entry_get_data_as_16bit_integer(
	          record_entry,
	          &value_16bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = LIBNK2_VALUE_TYPE_INTEGER_16BIT_SIGNED;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_16bit_integer(
	          record_entry,
	          &value_16bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_16bit_integer(
	          record_entry,
	          &value_16bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 2;

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_32bit_integer function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_32bit_integer(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	uint32_t value_32bit                = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_32bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_32bit_integer(
	          record_entry,
	          &value_32bit,
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
	result = libnk2_record_entry_get_data_as_32bit_integer(
	          NULL,
	          &value_32bit,
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

	result = libnk2_record_entry_get_data_as_32bit_integer(
	          record_entry,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = 0;

	result = libnk2_record_entry_get_data_as_32bit_integer(
	          record_entry,
	          &value_32bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_32bit_integer(
	          record_entry,
	          &value_32bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_32bit_integer(
	          record_entry,
	          &value_32bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 4;

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_64bit_integer function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_64bit_integer(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	uint64_t value_64bit                = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_64bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_64bit_integer(
	          record_entry,
	          &value_64bit,
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
	result = libnk2_record_entry_get_data_as_64bit_integer(
	          NULL,
	          &value_64bit,
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

	result = libnk2_record_entry_get_data_as_64bit_integer(
	          record_entry,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = 0;

	result = libnk2_record_entry_get_data_as_64bit_integer(
	          record_entry,
	          &value_64bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_64bit_integer(
	          record_entry,
	          &value_64bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_64bit_integer(
	          record_entry,
	          &value_64bit,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 8;

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_filetime function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_filetime(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	uint64_t filetime                   = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_filetime_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_filetime(
	          record_entry,
	          &filetime,
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
	result = libnk2_record_entry_get_data_as_filetime(
	          NULL,
	          &filetime,
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

	result = libnk2_record_entry_get_data_as_filetime(
	          record_entry,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = 0;

	result = libnk2_record_entry_get_data_as_filetime(
	          record_entry,
	          &filetime,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = LIBNK2_VALUE_TYPE_FILETIME;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_filetime(
	          record_entry,
	          &filetime,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_filetime(
	          record_entry,
	          &filetime,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 8;

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_floatingtime function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_floatingtime(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	uint64_t floatingtime               = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_floatingtime_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_floatingtime(
	          record_entry,
	          &floatingtime,
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
	result = libnk2_record_entry_get_data_as_floatingtime(
	          NULL,
	          &floatingtime,
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

	result = libnk2_record_entry_get_data_as_floatingtime(
	          record_entry,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = 0;

	result = libnk2_record_entry_get_data_as_floatingtime(
	          record_entry,
	          &floatingtime,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = LIBNK2_VALUE_TYPE_FLOATINGTIME;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_floatingtime(
	          record_entry,
	          &floatingtime,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_floatingtime(
	          record_entry,
	          &floatingtime,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 8;

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_size function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_size(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	size64_t value_size                 = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_32bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_size(
	          record_entry,
	          &value_size,
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
	result = libnk2_record_entry_get_data_as_size(
	          NULL,
	          &value_size,
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

	result = libnk2_record_entry_get_data_as_size(
	          record_entry,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = 0;

	result = libnk2_record_entry_get_data_as_size(
	          record_entry,
	          &value_size,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_size(
	          record_entry,
	          &value_size,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_size(
	          record_entry,
	          &value_size,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 4;

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_floating_point function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_floating_point(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	double value_floating_point         = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_float_32bit_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_floating_point(
	          record_entry,
	          &value_floating_point,
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
	result = libnk2_record_entry_get_data_as_floating_point(
	          NULL,
	          &value_floating_point,
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

	result = libnk2_record_entry_get_data_as_floating_point(
	          record_entry,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = 0;

	result = libnk2_record_entry_get_data_as_floating_point(
	          record_entry,
	          &value_floating_point,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_type = LIBNK2_VALUE_TYPE_FLOAT_32BIT;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_floating_point(
	          record_entry,
	          &value_floating_point,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_floating_point(
	          record_entry,
	          &value_floating_point,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 4;

	/* Clean up
	 */
	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_utf8_string_size(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	size_t utf8_string_size             = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_string_unicode_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libnk2_internal_record_entry_t *) record_entry )->value_data      = &( nk2_test_record_entry_string_unicode_data1[ 20 ] );
	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 26;

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_utf8_string_size(
	          record_entry,
	          &utf8_string_size,
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
	result = libnk2_record_entry_get_data_as_utf8_string_size(
	          NULL,
	          &utf8_string_size,
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

	result = libnk2_record_entry_get_data_as_utf8_string_size(
	          record_entry,
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

	/* Clean up
	 */
	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_utf8_string(
     void )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_string_unicode_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libnk2_internal_record_entry_t *) record_entry )->value_data      = &( nk2_test_record_entry_string_unicode_data1[ 20 ] );
	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 26;

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_utf8_string(
	          record_entry,
	          utf8_string,
	          32,
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
	result = libnk2_record_entry_get_data_as_utf8_string(
	          NULL,
	          utf8_string,
	          32,
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

	result = libnk2_record_entry_get_data_as_utf8_string(
	          record_entry,
	          NULL,
	          32,
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

	result = libnk2_record_entry_get_data_as_utf8_string(
	          record_entry,
	          utf8_string,
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

	result = libnk2_record_entry_get_data_as_utf8_string(
	          record_entry,
	          utf8_string,
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
	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_utf16_string_size(
     void )
{
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	size_t utf16_string_size            = 0;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_string_unicode_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libnk2_internal_record_entry_t *) record_entry )->value_data      = &( nk2_test_record_entry_string_unicode_data1[ 20 ] );
	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 26;

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_utf16_string_size(
	          record_entry,
	          &utf16_string_size,
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
	result = libnk2_record_entry_get_data_as_utf16_string_size(
	          NULL,
	          &utf16_string_size,
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

	result = libnk2_record_entry_get_data_as_utf16_string_size(
	          record_entry,
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

	/* Clean up
	 */
	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_utf16_string(
     void )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_string_unicode_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	( (libnk2_internal_record_entry_t *) record_entry )->value_data      = &( nk2_test_record_entry_string_unicode_data1[ 20 ] );
	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 26;

	/* Test regular cases
	 */
	result = libnk2_record_entry_get_data_as_utf16_string(
	          record_entry,
	          utf16_string,
	          32,
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
	result = libnk2_record_entry_get_data_as_utf16_string(
	          NULL,
	          utf16_string,
	          32,
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

	result = libnk2_record_entry_get_data_as_utf16_string(
	          record_entry,
	          NULL,
	          32,
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

	result = libnk2_record_entry_get_data_as_utf16_string(
	          record_entry,
	          utf16_string,
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

	result = libnk2_record_entry_get_data_as_utf16_string(
	          record_entry,
	          utf16_string,
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
	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_record_entry_get_data_as_guid function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_record_entry_get_data_as_guid(
     void )
{
	uint8_t guid_data[ 16 ];
	
	libcerror_error_t *error            = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	int result                          = 0;

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

	result = libnk2_record_entry_read_data(
	          record_entry,
	          nk2_test_record_entry_32bit_integer_data1,
	          16,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
/* TODO implement */

	/* Test error cases
	 */
	result = libnk2_record_entry_get_data_as_guid(
	          NULL,
	          guid_data,
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

	result = libnk2_record_entry_get_data_as_guid(
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

	result = libnk2_record_entry_get_data_as_guid(
	          record_entry,
	          guid_data,
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

	result = libnk2_record_entry_get_data_as_guid(
	          record_entry,
	          guid_data,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_record_entry_get_data_as_guid(
	          record_entry,
	          guid_data,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data = ( (libnk2_internal_record_entry_t *) record_entry )->value_data_array;

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 0;

	result = libnk2_record_entry_get_data_as_guid(
	          record_entry,
	          guid_data,
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

	( (libnk2_internal_record_entry_t *) record_entry )->value_data_size = 16;

	/* Clean up
	 */
	( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

	result = libnk2_internal_record_entry_free(
	          (libnk2_internal_record_entry_t **) &record_entry,
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
		( (libnk2_internal_record_entry_t *) record_entry )->value_data = NULL;

		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
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
	 "nk2_test_internal_record_entry_free",
	 nk2_test_internal_record_entry_free );

	NK2_TEST_RUN(
	 "libnk2_record_entry_read_data",
	 nk2_test_record_entry_read_data );

	NK2_TEST_RUN(
	 "libnk2_record_entry_read_file_io_handle",
	 nk2_test_record_entry_read_file_io_handle );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_entry_type",
	 nk2_test_record_entry_get_entry_type );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_value_type",
	 nk2_test_record_entry_get_value_type );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_size",
	 nk2_test_record_entry_get_data_size );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data",
	 nk2_test_record_entry_get_data );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_boolean",
	 nk2_test_record_entry_get_data_as_boolean );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_16bit_integer",
	 nk2_test_record_entry_get_data_as_16bit_integer );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_32bit_integer",
	 nk2_test_record_entry_get_data_as_32bit_integer );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_64bit_integer",
	 nk2_test_record_entry_get_data_as_64bit_integer );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_filetime",
	 nk2_test_record_entry_get_data_as_filetime );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_floatingtime",
	 nk2_test_record_entry_get_data_as_floatingtime );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_size",
	 nk2_test_record_entry_get_data_as_size );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_floating_point",
	 nk2_test_record_entry_get_data_as_floating_point );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_utf8_string_size",
	 nk2_test_record_entry_get_data_as_utf8_string_size );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_utf8_string",
	 nk2_test_record_entry_get_data_as_utf8_string );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_utf16_string_size",
	 nk2_test_record_entry_get_data_as_utf16_string_size );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_utf16_string",
	 nk2_test_record_entry_get_data_as_utf16_string );

	NK2_TEST_RUN(
	 "libnk2_record_entry_get_data_as_guid",
	 nk2_test_record_entry_get_data_as_guid );

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


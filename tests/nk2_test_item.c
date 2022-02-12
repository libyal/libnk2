/*
 * Library item type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "nk2_test_libbfio.h"
#include "nk2_test_libcerror.h"
#include "nk2_test_libnk2.h"
#include "nk2_test_macros.h"
#include "nk2_test_memory.h"
#include "nk2_test_unused.h"

#include "../libnk2/libnk2_io_handle.h"
#include "../libnk2/libnk2_item.h"

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

/* Tests the libnk2_item_initialize function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_item_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libnk2_item_t *item             = NULL;
	int result                      = 0;

#if defined( HAVE_NK2_TEST_MEMORY )
	int number_of_malloc_fail_tests = 2;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libnk2_item_initialize(
	          &item,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "item",
	 item );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_internal_item_free(
	          (libnk2_internal_item_t **) &item,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "item",
	 item );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libnk2_item_initialize(
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

	item = (libnk2_item_t *) 0x12345678UL;

	result = libnk2_item_initialize(
	          &item,
	          &error );

	item = NULL;

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
		/* Test libnk2_item_initialize with malloc failing
		 */
		nk2_test_malloc_attempts_before_fail = test_number;

		result = libnk2_item_initialize(
		          &item,
		          &error );

		if( nk2_test_malloc_attempts_before_fail != -1 )
		{
			nk2_test_malloc_attempts_before_fail = -1;

			if( item != NULL )
			{
				libnk2_internal_item_free(
				 (libnk2_internal_item_t **) &item,
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
			 "item",
			 item );

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
		/* Test libnk2_item_initialize with memset failing
		 */
		nk2_test_memset_attempts_before_fail = test_number;

		result = libnk2_item_initialize(
		          &item,
		          &error );

		if( nk2_test_memset_attempts_before_fail != -1 )
		{
			nk2_test_memset_attempts_before_fail = -1;

			if( item != NULL )
			{
				libnk2_internal_item_free(
				 (libnk2_internal_item_t **) &item,
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
			 "item",
			 item );

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
	if( item != NULL )
	{
		libnk2_internal_item_free(
		 (libnk2_internal_item_t **) &item,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

/* Tests the libnk2_item_free function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_item_free(
     void )
{
	libcerror_error_t *error = NULL;
	libnk2_item_t *item      = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	item = (libnk2_item_t *) 0x12345678UL;

	result = libnk2_item_free(
	          &item,
	          &error );

	item = NULL;

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "item",
	 item );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

/* Tests the libnk2_internal_item_free function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_internal_item_free(
     void )
{
	libcerror_error_t *error = NULL;
	libnk2_item_t *item      = NULL;
	int result               = 0;

	/* Test regular cases
	 */
/* TODO implement */

	/* Test error cases
	 */
	result = libnk2_internal_item_free(
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
	if( item != NULL )
	{
		libnk2_internal_item_free(
		 (libnk2_internal_item_t **) &item,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_item_read_record_entries function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_item_read_record_entries(
     void )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libnk2_io_handle_t *io_handle    = NULL;
	libnk2_item_t *item              = NULL;
	int result                       = 0;

	/* Initialize test
	 */
	result = libnk2_item_initialize(
	          &item,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "item",
	 item );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
/* TODO implement */

	/* Test error cases
	 */
	result = libnk2_item_read_record_entries(
	          NULL,
	          io_handle,
	          file_io_handle,
	          0,
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

	result = libnk2_item_read_record_entries(
	          (libnk2_internal_item_t *) item,
	          NULL,
	          file_io_handle,
	          0,
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

	/* Clean up
	 */
	result = libnk2_internal_item_free(
	          (libnk2_internal_item_t **) &item,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "item",
	 item );

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
	if( item != NULL )
	{
		libnk2_internal_item_free(
		 (libnk2_internal_item_t **) &item,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_item_get_number_of_entries function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_item_get_number_of_entries(
     void )
{
	libcerror_error_t *error = NULL;
	libnk2_item_t *item      = NULL;
	int number_of_entries    = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libnk2_item_initialize(
	          &item,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "item",
	 item );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libnk2_item_get_number_of_entries(
	          item,
	          &number_of_entries,
	          &error );

	NK2_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libnk2_item_get_number_of_entries(
	          NULL,
	          &number_of_entries,
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

	result = libnk2_item_get_number_of_entries(
	          item,
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
	result = libnk2_internal_item_free(
	          (libnk2_internal_item_t **) &item,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "item",
	 item );

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
	if( item != NULL )
	{
		libnk2_internal_item_free(
		 (libnk2_internal_item_t **) &item,
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
	 "libnk2_item_initialize",
	 nk2_test_item_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

	NK2_TEST_RUN(
	 "libnk2_item_free",
	 nk2_test_item_free );

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

	NK2_TEST_RUN(
	 "libnk2_internal_item_free",
	 nk2_test_internal_item_free );

	NK2_TEST_RUN(
	 "libnk2_item_read_record_entries",
	 nk2_test_item_read_record_entries );

	NK2_TEST_RUN(
	 "libnk2_item_get_number_of_entries",
	 nk2_test_item_get_number_of_entries );

	/* TODO: add tests for libnk2_item_get_entry_by_index */

	/* TODO: add tests for libnk2_item_get_entry_by_type */

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


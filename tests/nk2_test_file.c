/*
 * Library file type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "nk2_test_functions.h"
#include "nk2_test_getopt.h"
#include "nk2_test_libbfio.h"
#include "nk2_test_libcerror.h"
#include "nk2_test_libnk2.h"
#include "nk2_test_macros.h"
#include "nk2_test_memory.h"
#include "nk2_test_unused.h"

#include "../libnk2/libnk2_file.h"

#if !defined( LIBNK2_HAVE_BFIO )

LIBNK2_EXTERN \
int libnk2_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_open_file_io_handle(
     libnk2_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libnk2_error_t **error );

#endif /* !defined( LIBNK2_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make nk2_test_file generate verbose output
#define NK2_TEST_FILE_VERBOSE
 */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int nk2_test_file_open_source(
     libnk2_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "nk2_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libnk2_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = libnk2_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBNK2_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libnk2_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int nk2_test_file_close_source(
     libnk2_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "nk2_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libnk2_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libnk2_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libnk2_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libnk2_file_t *file             = NULL;
	int result                      = 0;

#if defined( HAVE_NK2_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libnk2_file_initialize(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_file_free(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libnk2_file_initialize(
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

	file = (libnk2_file_t *) 0x12345678UL;

	result = libnk2_file_initialize(
	          &file,
	          &error );

	file = NULL;

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
		/* Test libnk2_file_initialize with malloc failing
		 */
		nk2_test_malloc_attempts_before_fail = test_number;

		result = libnk2_file_initialize(
		          &file,
		          &error );

		if( nk2_test_malloc_attempts_before_fail != -1 )
		{
			nk2_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libnk2_file_free(
				 &file,
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
			 "file",
			 file );

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
		/* Test libnk2_file_initialize with memset failing
		 */
		nk2_test_memset_attempts_before_fail = test_number;

		result = libnk2_file_initialize(
		          &file,
		          &error );

		if( nk2_test_memset_attempts_before_fail != -1 )
		{
			nk2_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libnk2_file_free(
				 &file,
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
			 "file",
			 file );

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
	if( file != NULL )
	{
		libnk2_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_file_free function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libnk2_file_free(
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

/* Tests the libnk2_file_open function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libnk2_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = nk2_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_file_initialize(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libnk2_file_open(
	          file,
	          narrow_source,
	          LIBNK2_OPEN_READ,
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
	result = libnk2_file_open(
	          NULL,
	          narrow_source,
	          LIBNK2_OPEN_READ,
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

	result = libnk2_file_open(
	          file,
	          NULL,
	          LIBNK2_OPEN_READ,
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

	result = libnk2_file_open(
	          file,
	          narrow_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libnk2_file_open(
	          file,
	          narrow_source,
	          LIBNK2_OPEN_READ,
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
	result = libnk2_file_free(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libnk2_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libnk2_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libnk2_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = nk2_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_file_initialize(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libnk2_file_open_wide(
	          file,
	          wide_source,
	          LIBNK2_OPEN_READ,
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
	result = libnk2_file_open_wide(
	          NULL,
	          wide_source,
	          LIBNK2_OPEN_READ,
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

	result = libnk2_file_open_wide(
	          file,
	          NULL,
	          LIBNK2_OPEN_READ,
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

	result = libnk2_file_open_wide(
	          file,
	          wide_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libnk2_file_open_wide(
	          file,
	          wide_source,
	          LIBNK2_OPEN_READ,
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
	result = libnk2_file_free(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libnk2_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libnk2_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libnk2_file_t *file              = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
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

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        NK2_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libnk2_file_initialize(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libnk2_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBNK2_OPEN_READ,
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
	result = libnk2_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBNK2_OPEN_READ,
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

	result = libnk2_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBNK2_OPEN_READ,
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

	result = libnk2_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          -1,
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

	/* Test open when already opened
	 */
	result = libnk2_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBNK2_OPEN_READ,
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
	result = libnk2_file_free(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
         "file_io_handle",
         file_io_handle );

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
	if( file != NULL )
	{
		libnk2_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_file_close function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libnk2_file_close(
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

/* Tests the libnk2_file_open and libnk2_file_close functions
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libnk2_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libnk2_file_initialize(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libnk2_file_open_wide(
	          file,
	          source,
	          LIBNK2_OPEN_READ,
	          &error );
#else
	result = libnk2_file_open(
	          file,
	          source,
	          LIBNK2_OPEN_READ,
	          &error );
#endif

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_file_close(
	          file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libnk2_file_open_wide(
	          file,
	          source,
	          LIBNK2_OPEN_READ,
	          &error );
#else
	result = libnk2_file_open(
	          file,
	          source,
	          LIBNK2_OPEN_READ,
	          &error );
#endif

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_file_close(
	          file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libnk2_file_free(
	          &file,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libnk2_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libnk2_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_signal_abort(
     libnk2_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libnk2_file_signal_abort(
	          file,
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
	result = libnk2_file_signal_abort(
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

/* Tests the libnk2_file_get_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_get_ascii_codepage(
     libnk2_file_t *file )
{
	libcerror_error_t *error  = NULL;
	int ascii_codepage        = 0;
	int ascii_codepage_is_set = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libnk2_file_get_ascii_codepage(
	          file,
	          &ascii_codepage,
	          &error );

	NK2_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	ascii_codepage_is_set = result;

	/* Test error cases
	 */
	result = libnk2_file_get_ascii_codepage(
	          NULL,
	          &ascii_codepage,
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

	if( ascii_codepage_is_set != 0 )
	{
		result = libnk2_file_get_ascii_codepage(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libnk2_file_set_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_set_ascii_codepage(
     libnk2_file_t *file )
{
	int supported_codepages[ 15 ] = {
		LIBNK2_CODEPAGE_ASCII,
		LIBNK2_CODEPAGE_WINDOWS_874,
		LIBNK2_CODEPAGE_WINDOWS_932,
		LIBNK2_CODEPAGE_WINDOWS_936,
		LIBNK2_CODEPAGE_WINDOWS_949,
		LIBNK2_CODEPAGE_WINDOWS_950,
		LIBNK2_CODEPAGE_WINDOWS_1250,
		LIBNK2_CODEPAGE_WINDOWS_1251,
		LIBNK2_CODEPAGE_WINDOWS_1252,
		LIBNK2_CODEPAGE_WINDOWS_1253,
		LIBNK2_CODEPAGE_WINDOWS_1254,
		LIBNK2_CODEPAGE_WINDOWS_1255,
		LIBNK2_CODEPAGE_WINDOWS_1256,
		LIBNK2_CODEPAGE_WINDOWS_1257,
		LIBNK2_CODEPAGE_WINDOWS_1258 };

	int unsupported_codepages[ 17 ] = {
		LIBNK2_CODEPAGE_ISO_8859_1,
		LIBNK2_CODEPAGE_ISO_8859_2,
		LIBNK2_CODEPAGE_ISO_8859_3,
		LIBNK2_CODEPAGE_ISO_8859_4,
		LIBNK2_CODEPAGE_ISO_8859_5,
		LIBNK2_CODEPAGE_ISO_8859_6,
		LIBNK2_CODEPAGE_ISO_8859_7,
		LIBNK2_CODEPAGE_ISO_8859_8,
		LIBNK2_CODEPAGE_ISO_8859_9,
		LIBNK2_CODEPAGE_ISO_8859_10,
		LIBNK2_CODEPAGE_ISO_8859_11,
		LIBNK2_CODEPAGE_ISO_8859_13,
		LIBNK2_CODEPAGE_ISO_8859_14,
		LIBNK2_CODEPAGE_ISO_8859_15,
		LIBNK2_CODEPAGE_ISO_8859_16,
		LIBNK2_CODEPAGE_KOI8_R,
		LIBNK2_CODEPAGE_KOI8_U };

	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

	/* Test set ASCII codepage
	 */
	for( index = 0;
	     index < 15;
	     index++ )
	{
		codepage = supported_codepages[ index ];

		result = libnk2_file_set_ascii_codepage(
		          file,
		          codepage,
		          &error );

		NK2_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		NK2_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libnk2_file_set_ascii_codepage(
	          NULL,
	          LIBNK2_CODEPAGE_ASCII,
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

	for( index = 0;
	     index < 17;
	     index++ )
	{
		codepage = unsupported_codepages[ index ];

		result = libnk2_file_set_ascii_codepage(
		          file,
		          codepage,
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
	}
	/* Clean up
	 */
	result = libnk2_file_set_ascii_codepage(
	          file,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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
	return( 0 );
}

/* Tests the libnk2_file_get_modification_time function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_get_modification_time(
     libnk2_file_t *file )
{
	libcerror_error_t *error     = NULL;
	uint64_t modification_time   = 0;
	int modification_time_is_set = 0;
	int result                   = 0;

	/* Test regular cases
	 */
	result = libnk2_file_get_modification_time(
	          file,
	          &modification_time,
	          &error );

	NK2_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	modification_time_is_set = result;

	/* Test error cases
	 */
	result = libnk2_file_get_modification_time(
	          NULL,
	          &modification_time,
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

	if( modification_time_is_set != 0 )
	{
		result = libnk2_file_get_modification_time(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libnk2_file_get_number_of_items function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_get_number_of_items(
     libnk2_file_t *file )
{
	libcerror_error_t *error   = NULL;
	int number_of_items        = 0;
	int number_of_items_is_set = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	result = libnk2_file_get_number_of_items(
	          file,
	          &number_of_items,
	          &error );

	NK2_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_items_is_set = result;

	/* Test error cases
	 */
	result = libnk2_file_get_number_of_items(
	          NULL,
	          &number_of_items,
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

	if( number_of_items_is_set != 0 )
	{
		result = libnk2_file_get_number_of_items(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libnk2_file_get_item function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_file_get_item(
     libnk2_file_t *file )
{
	libcerror_error_t *error = NULL;
	libnk2_item_t *item      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libnk2_file_get_item(
	          file,
	          0,
	          &item,
	          &error );

	NK2_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	NK2_TEST_ASSERT_IS_NOT_NULL(
	 "item",
	 item );

	result = libnk2_item_free(
	          &item,
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
	result = libnk2_file_get_item(
	          NULL,
	          0,
	          &item,
	          &error );

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

	result = libnk2_file_get_item(
	          file,
	          -1,
	          &item,
	          &error );

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

	result = libnk2_file_get_item(
	          file,
	          0,
	          NULL,
	          &error );

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
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libnk2_file_t *file              = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = nk2_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( NK2_TEST_FILE_VERBOSE )
	libnk2_notify_set_verbose(
	 1 );
	libnk2_notify_set_stream(
	 stderr,
	 NULL );
#endif

	NK2_TEST_RUN(
	 "libnk2_file_initialize",
	 nk2_test_file_initialize );

	NK2_TEST_RUN(
	 "libnk2_file_free",
	 nk2_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
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

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		NK2_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        NK2_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libnk2_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		NK2_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		NK2_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_open",
		 nk2_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_open_wide",
		 nk2_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_open_file_io_handle",
		 nk2_test_file_open_file_io_handle,
		 source );

		NK2_TEST_RUN(
		 "libnk2_file_close",
		 nk2_test_file_close );

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_open_close",
		 nk2_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = nk2_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		NK2_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		NK2_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		NK2_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_signal_abort",
		 nk2_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

		/* TODO: add tests for libnk2_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_get_ascii_codepage",
		 nk2_test_file_get_ascii_codepage,
		 file );

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_set_ascii_codepage",
		 nk2_test_file_set_ascii_codepage,
		 file );

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_get_modification_time",
		 nk2_test_file_get_modification_time,
		 file );

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_get_number_of_items",
		 nk2_test_file_get_number_of_items,
		 file );

		NK2_TEST_RUN_WITH_ARGS(
		 "libnk2_file_get_item",
		 nk2_test_file_get_item,
		 file );

		/* Clean up
		 */
		result = nk2_test_file_close_source(
		          &file,
		          &error );

		NK2_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		NK2_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		NK2_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		NK2_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		NK2_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        NK2_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libnk2_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}


/*
 * Library mapi_value functions test program
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

#include "nk2_test_libcerror.h"
#include "nk2_test_libnk2.h"
#include "nk2_test_macros.h"
#include "nk2_test_unused.h"

#include "../libnk2/libnk2_mapi_value.h"

uint8_t nk2_test_mapi_value_string_ascii_data[ 13 ] = {
	0x4a, 0x6f, 0x61, 0x63, 0x68, 0x69, 0x6d, 0x20, 0x4d, 0x65, 0x74, 0x7a, 0x00 };

uint8_t nk2_test_mapi_value_string_unicode_data[ 26 ] = {
	0x4a, 0x00, 0x6f, 0x00, 0x61, 0x00, 0x63, 0x00, 0x68, 0x00, 0x69, 0x00, 0x6d, 0x00, 0x20, 0x00,
	0x4d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x7a, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT )

/* Tests the libnk2_mapi_value_get_data_size function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_mapi_value_get_data_size(
     void )
{
	libcerror_error_t *error = NULL;
	size_t value_data_size   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libnk2_mapi_value_get_data_size(
	          LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED,
	          &value_data_size,
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
	result = libnk2_mapi_value_get_data_size(
	          0xffffffff,
	          &value_data_size,
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

	result = libnk2_mapi_value_get_data_size(
	          LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED,
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

/* Tests the libnk2_mapi_value_data_contains_zero_bytes function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_mapi_value_data_contains_zero_bytes(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libnk2_mapi_value_data_contains_zero_bytes(
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_data_contains_zero_bytes(
	          nk2_test_mapi_value_string_unicode_data,
	          26,
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
	result = libnk2_mapi_value_data_contains_zero_bytes(
	          NULL,
	          13,
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

	result = libnk2_mapi_value_data_contains_zero_bytes(
	          nk2_test_mapi_value_string_ascii_data,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libnk2_mapi_value_get_data_as_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_mapi_value_get_data_as_utf8_string_size(
     void )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libnk2_mapi_value_get_data_as_utf8_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &utf8_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 13 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_get_data_as_utf8_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          NULL,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &utf8_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_get_data_as_utf8_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          0,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &utf8_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_get_data_as_utf8_string_size(
	          LIBNK2_VALUE_TYPE_STRING_UNICODE,
	          nk2_test_mapi_value_string_unicode_data,
	          26,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &utf8_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 13 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_get_data_as_utf8_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_unicode_data,
	          26,
	          1200,
	          &utf8_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 13 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO test codepage 65000 UTF-7 */

	result = libnk2_mapi_value_get_data_as_utf8_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          65001,
	          &utf8_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 13 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libnk2_mapi_value_get_data_as_utf8_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          -1,
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

	result = libnk2_mapi_value_get_data_as_utf8_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

/* Tests the libnk2_mapi_value_get_data_as_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_mapi_value_get_data_as_utf8_string(
     void )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          NULL,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          0,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_UNICODE,
	          nk2_test_mapi_value_string_unicode_data,
	          26,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_unicode_data,
	          26,
	          1200,
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

/* TODO test codepage 65000 UTF-7 */

	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          65001,
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
	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          -1,
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

	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf8_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libnk2_mapi_value_get_data_as_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_mapi_value_get_data_as_utf16_string_size(
     void )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libnk2_mapi_value_get_data_as_utf16_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 13 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_get_data_as_utf16_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          NULL,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_get_data_as_utf16_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          0,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_get_data_as_utf16_string_size(
	          LIBNK2_VALUE_TYPE_STRING_UNICODE,
	          nk2_test_mapi_value_string_unicode_data,
	          26,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 13 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libnk2_mapi_value_get_data_as_utf16_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_unicode_data,
	          26,
	          1200,
	          &utf16_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 13 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO test codepage 65000 UTF-7 */

	result = libnk2_mapi_value_get_data_as_utf16_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          65001,
	          &utf16_string_size,
	          &error );

	NK2_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	NK2_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 13 );

	NK2_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libnk2_mapi_value_get_data_as_utf16_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          -1,
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

	result = libnk2_mapi_value_get_data_as_utf16_string_size(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

/* Tests the libnk2_mapi_value_get_data_as_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int nk2_test_mapi_value_get_data_as_utf16_string(
     void )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          NULL,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          0,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_UNICODE,
	          nk2_test_mapi_value_string_unicode_data,
	          26,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_unicode_data,
	          26,
	          1200,
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

/* TODO test codepage 65000 UTF-7 */

	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          65001,
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
	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          -1,
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

	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	result = libnk2_mapi_value_get_data_as_utf16_string(
	          LIBNK2_VALUE_TYPE_STRING_ASCII,
	          nk2_test_mapi_value_string_ascii_data,
	          13,
	          LIBNK2_CODEPAGE_WINDOWS_1252,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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
	 "libnk2_mapi_value_get_data_size",
	 nk2_test_mapi_value_get_data_size )

	NK2_TEST_RUN(
	 "libnk2_mapi_value_data_contains_zero_bytes",
	 nk2_test_mapi_value_data_contains_zero_bytes )

	NK2_TEST_RUN(
	 "libnk2_mapi_value_get_data_as_utf8_string_size",
	 nk2_test_mapi_value_get_data_as_utf8_string_size )

	NK2_TEST_RUN(
	 "libnk2_mapi_value_get_data_as_utf8_string",
	 nk2_test_mapi_value_get_data_as_utf8_string )

	NK2_TEST_RUN(
	 "libnk2_mapi_value_get_data_as_utf16_string_size",
	 nk2_test_mapi_value_get_data_as_utf16_string_size )

	NK2_TEST_RUN(
	 "libnk2_mapi_value_get_data_as_utf16_string",
	 nk2_test_mapi_value_get_data_as_utf16_string )

#endif /* defined( __GNUC__ ) && !defined( LIBNK2_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}


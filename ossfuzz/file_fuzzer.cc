/*
 * OSS-Fuzz target for libnk2 file type
 *
 * Copyright (C) 2009-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libnk2.h"

#if !defined( LIBNK2_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_open_file_io_handle(
      libnk2_file_t *file,
      libbfio_handle_t *file_io_handle,
      int access_flags,
      libnk2_error_t **error );

/* Determines if a file contains a NK2 file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_check_file_signature_file_io_handle(
      libbfio_handle_t *file_io_handle,
      libnk2_error_t **error );

#endif /* !defined( LIBNK2_HAVE_BFIO ) */

/* The deprecated declarations are ignored
 */
#if defined( __clang__ )
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

/* Used to limit the amount of memory the fuzzer will allocate
 */
#define MAXIMUM_ALLOCATION_SIZE	( 8 * 1024 * 1024 )

/* Used to limit the number of items and entries that are tested
 */
#define NUMBER_OF_ITEMS_TO_EXERCISE	32
#define NUMBER_OF_ENTRIES_TO_EXERCISE	32

#define NUMBER_OF_CODEPAGES	16

/* The codepages supported by libnk2_file_set_ascii_codepage
 * The value 0 represents an unsupported codepage
 */
const int codepages[ NUMBER_OF_CODEPAGES ] = {
	0,
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
	LIBNK2_CODEPAGE_WINDOWS_1258,
	LIBNK2_CODEPAGE_ASCII
};

/* Retrieves the UTF-8 encoded string from a record entry
 * using a pair of getter functions
 */
void fuzzer_record_entry_fetch_utf8_string(
      libnk2_record_entry_t *record_entry )
{
	uint8_t *utf8_string    = NULL;
	size_t utf8_string_size = 0;

	if( record_entry == NULL )
	{
		return;
	}
	if( libnk2_record_entry_get_data_as_utf8_string_size(
	      record_entry,
	      &utf8_string_size,
	      NULL ) != 1 )
	{
		return;
	}
	if( ( utf8_string_size == 0 )
	 || ( utf8_string_size > MAXIMUM_ALLOCATION_SIZE ) )
	{
		return;
	}
	utf8_string = (uint8_t *) malloc( utf8_string_size );

	if( utf8_string == NULL )
	{
		return;
	}
	libnk2_record_entry_get_data_as_utf8_string(
	 record_entry,
	 utf8_string,
	 utf8_string_size,
	 NULL );

	/* Tests the string size value out of bounds error branch
	 */
	libnk2_record_entry_get_data_as_utf8_string(
	 record_entry,
	 utf8_string,
	 0,
	 NULL );
	free( utf8_string );
}

/* Retrieves the UTF-16 encoded string from a record entry
 * using a pair of getter functions
 */
void fuzzer_record_entry_fetch_utf16_string(
      libnk2_record_entry_t *record_entry )
{
	uint16_t *utf16_string   = NULL;
	size_t utf16_string_size = 0;

	if( record_entry == NULL )
	{
		return;
	}
	if( libnk2_record_entry_get_data_as_utf16_string_size(
	      record_entry,
	      &utf16_string_size,
	      NULL ) != 1 )
	{
		return;
	}
	if( ( utf16_string_size == 0 )
	 || ( utf16_string_size > ( MAXIMUM_ALLOCATION_SIZE / sizeof( uint16_t ) ) ) )
	{
		return;
	}
	utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

	if( utf16_string == NULL )
	{
		return;
	}
	libnk2_record_entry_get_data_as_utf16_string(
	 record_entry,
	 utf16_string,
	 utf16_string_size,
	 NULL );

	/* Tests the string size value out of bounds error branch
	 */
	libnk2_record_entry_get_data_as_utf16_string(
	 record_entry,
	 utf16_string,
	 0,
	 NULL );
	free( utf16_string );
}

/* Tests the getter functions of a record entry
 */
void fuzzer_record_entry_test_getters(
      libnk2_record_entry_t *record_entry )
{
	uint8_t value_boolean   = 0;
	uint8_t guid_data[ 16 ] = { 0 };
	uint16_t value_16bit    = 0;
	uint32_t value_32bit    = 0;
	uint64_t value_64bit    = 0;
	uint8_t *data           = NULL;
	size64_t value_size     = 0;
	size_t data_size        = 0;
	double value_floating_point = 0.0;
	int result              = 0;

	if( record_entry == NULL )
	{
		return;
	}
	libnk2_record_entry_get_entry_type(
	 record_entry,
	 &( value_32bit ),
	 NULL );

	libnk2_record_entry_get_value_type(
	 record_entry,
	 &( value_32bit ),
	 NULL );

	result = libnk2_record_entry_get_data_size(
	          record_entry,
	          &data_size,
	          NULL );

	if( ( result == 1 )
	 && ( data_size <= MAXIMUM_ALLOCATION_SIZE ) )
	{
		data = (uint8_t *) malloc(
		              data_size < 1 ? 1 : data_size );

		if( data != NULL )
		{
			libnk2_record_entry_get_data(
			 record_entry,
			 data,
			 data_size,
			 NULL );
			free( data );
		}
	}
	/* Tests the data size value out of bounds error branch
	 */
	if( ( result == 1 )
	 && ( data_size <= MAXIMUM_ALLOCATION_SIZE ) )
	{
		data = (uint8_t *) malloc( 1 );

		if( data != NULL )
		{
			libnk2_record_entry_get_data(
			 record_entry,
			 data,
			 0,
			 NULL );
			free( data );
		}
	}
	libnk2_record_entry_get_data_as_boolean(
	 record_entry,
	 &value_boolean,
	 NULL );

	libnk2_record_entry_get_data_as_16bit_integer(
	 record_entry,
	 &value_16bit,
	 NULL );

	libnk2_record_entry_get_data_as_32bit_integer(
	 record_entry,
	 &value_32bit,
	 NULL );

	libnk2_record_entry_get_data_as_64bit_integer(
	 record_entry,
	 &value_64bit,
	 NULL );

	libnk2_record_entry_get_data_as_filetime(
	 record_entry,
	 &value_64bit,
	 NULL );

	libnk2_record_entry_get_data_as_floatingtime(
	 record_entry,
	 &value_64bit,
	 NULL );

	libnk2_record_entry_get_data_as_size(
	 record_entry,
	 &value_size,
	 NULL );

	libnk2_record_entry_get_data_as_floating_point(
	 record_entry,
	 &value_floating_point,
	 NULL );

	fuzzer_record_entry_fetch_utf8_string(
	 record_entry );

	fuzzer_record_entry_fetch_utf16_string(
	 record_entry );

	libnk2_record_entry_get_data_as_guid(
	 record_entry,
	 guid_data,
	 sizeof( guid_data ),
	 NULL );

	/* Tests the GUID data size value too small error branch
	 */
	libnk2_record_entry_get_data_as_guid(
	 record_entry,
	 guid_data,
	 8,
	 NULL );
}

/* Tests the invalid output getter functions of a record entry
 */
void fuzzer_record_entry_test_invalid_output(
      libnk2_record_entry_t *record_entry )
{
	if( record_entry == NULL )
	{
		return;
	}
	libnk2_record_entry_get_entry_type(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_value_type(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_size(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data(
	 record_entry,
	 NULL,
	 8,
	 NULL );

	libnk2_record_entry_get_data_as_boolean(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_16bit_integer(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_32bit_integer(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_64bit_integer(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_filetime(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_floatingtime(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_size(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_floating_point(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_utf8_string_size(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_utf16_string_size(
	 record_entry,
	 NULL,
	 NULL );

	libnk2_record_entry_get_data_as_guid(
	 record_entry,
	 NULL,
	 sizeof( uint8_t ) * 16,
	 NULL );
}

/* Tests the getter functions of an item
 */
void fuzzer_item_test(
      libnk2_item_t *item )
{
	libnk2_record_entry_t *record_entry = NULL;
	int number_of_entries               = 0;
	int entry_index                     = 0;
	int result                          = 0;

	if( item == NULL )
	{
		return;
	}
	result = libnk2_item_get_number_of_entries(
	          item,
	          &number_of_entries,
	          NULL );

	/* Tests the invalid output getter functions of an item
	 */
	if( result != 1 )
	{
		number_of_entries = 0;
	}
	libnk2_item_get_number_of_entries(
	 item,
	 NULL,
	 NULL );

	/* Tests the invalid output getter functions of an item
	 */
	libnk2_item_get_entry_by_index(
	 item,
	 0,
	 NULL,
	 NULL );

	record_entry = (libnk2_record_entry_t *) 0x12345678UL;

	libnk2_item_get_entry_by_index(
	 item,
	 0,
	 &record_entry,
	 NULL );

	record_entry = NULL;

	if( number_of_entries > 0 )
	{
		entry_index = number_of_entries;

		libnk2_item_get_entry_by_index(
		 item,
		 entry_index,
		 &record_entry,
		 NULL );

		entry_index = -1;

		libnk2_item_get_entry_by_index(
		 item,
		 entry_index,
		 &record_entry,
		 NULL );
	}
	if( number_of_entries > NUMBER_OF_ENTRIES_TO_EXERCISE )
	{
		number_of_entries = NUMBER_OF_ENTRIES_TO_EXERCISE;
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		record_entry = NULL;

		result = libnk2_item_get_entry_by_index(
		          item,
		          entry_index,
		          &record_entry,
		          NULL );

		if( ( result == 1 )
		 && ( record_entry != NULL ) )
		{
			fuzzer_record_entry_test_getters(
			 record_entry );

			fuzzer_record_entry_test_invalid_output(
			 record_entry );

			libnk2_record_entry_free(
			 &record_entry,
			 NULL );
		}
	}
	/* Tests the invalid output and unsupported flags of an item
	 */
	libnk2_item_get_entry_by_type(
	 item,
	 LIBNK2_ENTRY_TYPE_DISPLAY_NAME,
	 LIBNK2_VALUE_TYPE_STRING_UNICODE,
	 NULL,
	 0,
	 NULL );

	record_entry = (libnk2_record_entry_t *) 0x12345678UL;

	libnk2_item_get_entry_by_type(
	 item,
	 LIBNK2_ENTRY_TYPE_DISPLAY_NAME,
	 LIBNK2_VALUE_TYPE_STRING_UNICODE,
	 &record_entry,
	 0,
	 NULL );

	record_entry = NULL;

	libnk2_item_get_entry_by_type(
	 item,
	 LIBNK2_ENTRY_TYPE_DISPLAY_NAME,
	 LIBNK2_VALUE_TYPE_STRING_UNICODE,
	 &record_entry,
	 0x80,
	 NULL );

	record_entry = NULL;

	result = libnk2_item_get_entry_by_type(
	          item,
	          LIBNK2_ENTRY_TYPE_DISPLAY_NAME,
	          LIBNK2_VALUE_TYPE_STRING_UNICODE,
	          &record_entry,
	          0,
	          NULL );

	if( ( result == 1 )
	 && ( record_entry != NULL ) )
	{
		fuzzer_record_entry_test_getters(
		 record_entry );

		fuzzer_record_entry_test_invalid_output(
		 record_entry );

		libnk2_record_entry_free(
		 &record_entry,
		 NULL );
	}
	record_entry = NULL;

	result = libnk2_item_get_entry_by_type(
	          item,
	          LIBNK2_ENTRY_TYPE_RECIPIENT_TYPE,
	          LIBNK2_VALUE_TYPE_UNSPECIFIED,
	          &record_entry,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          NULL );

	if( ( result == 1 )
	 && ( record_entry != NULL ) )
	{
		fuzzer_record_entry_test_getters(
		 record_entry );

		fuzzer_record_entry_test_invalid_output(
		 record_entry );

		libnk2_record_entry_free(
		 &record_entry,
		 NULL );
	}
}

/* Tests the getter functions of a file
 */
void fuzzer_file_test_getters(
      libnk2_file_t *file )
{
	libnk2_item_t *item               = NULL;
	uint64_t filetime                 = 0;
	int ascii_codepage                = 0;
	int number_of_items               = 0;
	int item_index                    = 0;
	int result                        = 0;

	if( file == NULL )
	{
		return;
	}
	libnk2_file_get_ascii_codepage(
	 file,
	 &ascii_codepage,
	 NULL );

	libnk2_file_get_ascii_codepage(
	 file,
	 NULL,
	 NULL );

	libnk2_file_get_modification_time(
	 file,
	 &filetime,
	 NULL );

	libnk2_file_get_modification_time(
	 file,
	 NULL,
	 NULL );

	result = libnk2_file_get_number_of_items(
	          file,
	          &number_of_items,
	          NULL );

	if( result != 1 )
	{
		number_of_items = 0;
	}
	libnk2_file_get_number_of_items(
	 file,
	 NULL,
	 NULL );

	/* Tests the invalid output getter functions of a file
	 */
	libnk2_file_get_item(
	 file,
	 0,
	 NULL,
	 NULL );

	item = (libnk2_item_t *) 0x12345678UL;

	libnk2_file_get_item(
	 file,
	 0,
	 &item,
	 NULL );

	item = NULL;

	libnk2_file_get_item(
	 file,
	 -1,
	 &item,
	 NULL );

	if( number_of_items > 0 )
	{
		item_index = number_of_items;

		libnk2_file_get_item(
		 file,
		 item_index,
		 &item,
		 NULL );
	}
	if( number_of_items > NUMBER_OF_ITEMS_TO_EXERCISE )
	{
		number_of_items = NUMBER_OF_ITEMS_TO_EXERCISE;
	}
	for( item_index = 0;
	     item_index < number_of_items;
	     item_index++ )
	{
		item = NULL;

		result = libnk2_file_get_item(
		          file,
		          item_index,
		          &item,
		          NULL );

		if( ( result == 1 )
		 && ( item != NULL ) )
		{
			fuzzer_item_test(
			 item );

			libnk2_item_free(
			 &item,
			 NULL );
		}
	}
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	libbfio_handle_t *file_io_handle = NULL;
	libnk2_file_t *file              = NULL;
	uint64_t filetime                = 0;
	int codepage                     = 0;
	int global_codepage              = 0;
	int result                       = 0;

	/* Tests the library support functions
	 */
	libnk2_get_version();
	libnk2_get_access_flags_read();

	libnk2_get_codepage(
	 &global_codepage,
	 NULL );

	libnk2_set_codepage(
	 1252,
	 NULL );

	/* Tests the unsupported codepage error branch
	 */
	libnk2_set_codepage(
	 1234,
	 NULL );

	libnk2_set_codepage(
	 0,
	 NULL );

	libnk2_notify_set_verbose(
	 0 );

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libnk2_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	/* Tests the error branches of the file functions
	 * before the file is opened
	 */
	libnk2_file_close(
	 file,
	 NULL );

	libnk2_file_signal_abort(
	 file,
	 NULL );

	libnk2_file_open(
	 file,
	 NULL,
	 LIBNK2_ACCESS_FLAG_READ,
	 NULL );

#if defined( LIBNK2_HAVE_WIDE_CHARACTER_TYPE )
	/* Tests the invalid filename error branch
	 */
	libnk2_file_open_wide(
	 file,
	 NULL,
	 LIBNK2_ACCESS_FLAG_READ,
	 NULL );

#endif /* defined( LIBNK2_HAVE_WIDE_CHARACTER_TYPE ) */

	libnk2_file_open_file_io_handle(
	 file,
	 NULL,
	 LIBNK2_ACCESS_FLAG_READ,
	 NULL );

	libnk2_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 0,
	 NULL );

	libnk2_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 LIBNK2_ACCESS_FLAG_READ | LIBNK2_ACCESS_FLAG_WRITE,
	 NULL );

	libnk2_check_file_signature_file_io_handle(
	 NULL,
	 NULL );

	libnk2_check_file_signature_file_io_handle(
	 file_io_handle,
	 NULL );

	libnk2_file_get_ascii_codepage(
	 file,
	 NULL,
	 NULL );

	libnk2_file_set_ascii_codepage(
	 file,
	 1234,
	 NULL );

	libnk2_file_get_modification_time(
	 file,
	 &filetime,
	 NULL );

	libnk2_file_get_number_of_items(
	 file,
	 NULL,
	 NULL );

	libnk2_file_get_item(
	 file,
	 0,
	 NULL,
	 NULL );

	if( size > 0 )
	{
		codepage = codepages[ (int) ( data[ 0 ] % NUMBER_OF_CODEPAGES ) ];
	}
	else
	{
		codepage = codepages[ 1 ];
	}
	if( libnk2_file_set_ascii_codepage(
	     file,
	     codepage,
	     NULL ) != 1 )
	{
		codepage = LIBNK2_CODEPAGE_WINDOWS_1252;
	}
	result = libnk2_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBNK2_ACCESS_FLAG_READ,
	          NULL );

	if( result == 1 )
	{
		/* Tests the file IO handle value already set error branch
		 */
		libnk2_file_open_file_io_handle(
		 file,
		 file_io_handle,
		 LIBNK2_ACCESS_FLAG_READ,
		 NULL );

		fuzzer_file_test_getters(
		 file );

		libnk2_file_close(
		 file,
		 NULL );

		/* Tests the missing file IO handle error branch
		 */
		libnk2_file_close(
		 file,
		 NULL );
	}
	if( size > 1 )
	{
		codepage = codepages[ (int) ( data[ 1 ] % NUMBER_OF_CODEPAGES ) ];

		if( libnk2_file_set_ascii_codepage(
		     file,
		     codepage,
		     NULL ) != 1 )
		{
			codepage = LIBNK2_CODEPAGE_WINDOWS_1252;
		}
	}
	result = libnk2_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBNK2_ACCESS_FLAG_READ,
	          NULL );

	if( result == 1 )
	{
		fuzzer_file_test_getters(
		 file );

		libnk2_file_signal_abort(
		 file,
		 NULL );

		libnk2_file_close(
		 file,
		 NULL );
	}
	libnk2_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

#if defined( __clang__ )
#pragma clang diagnostic pop
#elif defined( __GNUC__ )
#pragma GCC diagnostic pop
#endif

} /* extern "C" */

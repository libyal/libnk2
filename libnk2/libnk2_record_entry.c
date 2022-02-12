/*
 * Record entry functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libnk2_libbfio.h"
#include "libnk2_libcerror.h"
#include "libnk2_libcnotify.h"
#include "libnk2_libfmapi.h"
#include "libnk2_libuna.h"
#include "libnk2_mapi.h"
#include "libnk2_mapi_value.h"
#include "libnk2_record_entry.h"

#include "nk2_item.h"

/* Creates a record entry
 * Make sure the value record_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_initialize(
     libnk2_record_entry_t **record_entry,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_initialize";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	if( *record_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid record entry value already set.",
		 function );

		return( -1 );
	}
	internal_record_entry = memory_allocate_structure(
	                         libnk2_internal_record_entry_t );

	if( internal_record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create record entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_record_entry,
	     0,
	     sizeof( libnk2_internal_record_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear record entry.",
		 function );

		goto on_error;
	}
	internal_record_entry->ascii_codepage = ascii_codepage;

	*record_entry = (libnk2_record_entry_t *) internal_record_entry;

	return( 1 );

on_error:
	if( internal_record_entry != NULL )
	{
		memory_free(
		 internal_record_entry );
	}
	return( -1 );
}

/* Frees a record entry
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_free(
     libnk2_record_entry_t **record_entry,
     libcerror_error_t **error )
{
	static char *function = "libnk2_record_entry_free";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	if( *record_entry != NULL )
	{
		*record_entry = NULL;
	}
	return( 1 );
}

/* Frees a record entry
 * Returns 1 if successful or -1 on error
 */
int libnk2_internal_record_entry_free(
     libnk2_internal_record_entry_t **internal_record_entry,
     libcerror_error_t **error )
{
	static char *function = "libnk2_internal_record_entry_free";

	if( internal_record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	if( *internal_record_entry != NULL )
	{
		if( ( ( *internal_record_entry )->value_data != NULL )
		 && ( ( *internal_record_entry )->value_data != ( *internal_record_entry )->value_data_array ) )
		{
			memory_free(
			 ( *internal_record_entry )->value_data );
		}
		memory_free(
		 *internal_record_entry );

		*internal_record_entry = NULL;
	}
	return( 1 );
}

/* Reads the record entry
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_read_data(
     libnk2_record_entry_t *record_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	const char *description                               = 0;
	const char *identifier                                = 0;
	uint32_t value_32bit                                  = 0;
#endif

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < sizeof( nk2_item_value_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: record entry data\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) data,
		 sizeof( nk2_item_value_entry_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 ( (nk2_item_value_entry_t *) data )->value_type,
	 internal_record_entry->value_type );

	byte_stream_copy_to_uint16_little_endian(
	 ( (nk2_item_value_entry_t *) data )->entry_type,
	 internal_record_entry->entry_type );

	if( memory_copy(
	     internal_record_entry->value_data_array,
	     ( (nk2_item_value_entry_t *) data )->value_data_array,
	     8 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy value data array.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		identifier = libfmapi_value_type_get_identifier(
		              internal_record_entry->value_type );

		description = libfmapi_value_type_get_description(
		               internal_record_entry->value_type );

		libcnotify_printf(
		 "%s: value type\t\t\t\t: 0x%04" PRIx32 " (%s : %s)\n",
		 function,
		 internal_record_entry->value_type,
		 identifier,
		 description );

		identifier = libfmapi_property_type_get_identifier(
		              NULL,
		              internal_record_entry->entry_type,
		              internal_record_entry->value_type );

		description = libfmapi_property_type_get_description(
		               NULL,
		               internal_record_entry->entry_type,
		               internal_record_entry->value_type );

		libcnotify_printf(
		 "%s: entry type\t\t\t\t: 0x%04" PRIx32 " (%s : %s)\n",
		 function,
		 internal_record_entry->entry_type,
		 identifier,
		 description );

		byte_stream_copy_to_uint32_little_endian(
		 ( (nk2_item_value_entry_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: value data array:\n",
		 function );
		libcnotify_print_data(
		 internal_record_entry->value_data_array,
		 8,
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( libnk2_mapi_value_get_data_size(
	     internal_record_entry->value_type,
	     &( internal_record_entry->value_data_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value data size.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size != 0 )
	{
		internal_record_entry->value_data = internal_record_entry->value_data_array;
	}
	return( 1 );
}

/* Reads the record entry
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_read_file_io_handle(
     libnk2_record_entry_t *record_entry,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t record_entry_data[ sizeof( nk2_item_value_entry_t ) ];

	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_read_file_io_handle";
	uint32_t stored_value_data_size                       = 0;
	ssize_t read_count                                    = 0;

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_data != NULL )
	 && ( internal_record_entry->value_data != internal_record_entry->value_data_array ) )
	{
		memory_free(
		 internal_record_entry->value_data );
	}
	internal_record_entry->value_data      = NULL;
	internal_record_entry->value_data_size = 0;

	read_count = libbfio_handle_read_buffer(
		      file_io_handle,
		      record_entry_data,
		      sizeof( nk2_item_value_entry_t ),
		      error );

	if( read_count != (ssize_t) sizeof( nk2_item_value_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read record entry data.",
		 function );

		goto on_error;
	}
	if( libnk2_record_entry_read_data(
	     record_entry,
	     record_entry_data,
	     sizeof( nk2_item_value_entry_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read record entry.",
		 function );

		goto on_error;
	}
	if( internal_record_entry->value_data_size == 0 )
	{
		/* The value data size is stored after the item value
		 */
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      internal_record_entry->value_data_array,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read value data size.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 internal_record_entry->value_data_array,
		 stored_value_data_size );

#if SIZEOF_SIZE_T <= 4
		if( stored_value_data_size > (uint32_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid stored value data size value exceeds maximum.",
			 function );

			goto on_error;
		}
#endif
		internal_record_entry->value_data_size = (size_t) stored_value_data_size;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: value data size\t\t\t\t: %" PRIzd "\n",
		 function,
		 internal_record_entry->value_data_size );
	}
#endif
	if( internal_record_entry->value_data == NULL )
	{
		if( ( stored_value_data_size == 0 )
		 || ( stored_value_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid stored value data size value out of bounds.",
			 function );

			goto on_error;
		}
		internal_record_entry->value_data = (uint8_t *) memory_allocate(
		                                                 (size_t) internal_record_entry->value_data_size );

		if( internal_record_entry->value_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value data.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
		              internal_record_entry->value_data,
		              internal_record_entry->value_data_size,
		              error );

		if( read_count != (ssize_t) internal_record_entry->value_data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read value data.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( ( internal_record_entry->value_data != NULL )
	 && ( internal_record_entry->value_data != internal_record_entry->value_data_array ) )
	{
		memory_free(
		 internal_record_entry->value_data );
	}
	internal_record_entry->value_data      = NULL;
	internal_record_entry->value_data_size = 0;

	return( -1 );
}

/* Retrieves the entry type
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
int libnk2_record_entry_get_entry_type(
     libnk2_record_entry_t *record_entry,
     uint32_t *entry_type,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_entry_type";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( entry_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry type.",
		 function );

		return( -1 );
	}
	*entry_type = internal_record_entry->entry_type;

	return( 1 );
}

/* Retrieves the value type
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
int libnk2_record_entry_get_value_type(
     libnk2_record_entry_t *record_entry,
     uint32_t *value_type,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_value_type";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( value_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	*value_type = internal_record_entry->value_type;

	return( 1 );
}

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_size(
     libnk2_record_entry_t *record_entry,
     size_t *data_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_size";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	*data_size = internal_record_entry->value_data_size;

	return( 1 );
}

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data(
     libnk2_record_entry_t *record_entry,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_size < internal_record_entry->value_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     data,
	     internal_record_entry->value_data,
	     internal_record_entry->value_data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as a boolean value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_boolean(
     libnk2_record_entry_t *record_entry,
     uint8_t *value_boolean,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_boolean";
	uint16_t value_16bit                                  = 0;

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_BOOLEAN )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size != 2 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_boolean == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value boolean.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 internal_record_entry->value_data,
	 value_16bit );

	*value_boolean = (uint8_t) value_16bit;

	return( 1 );
}

/* Retrieves the data as a 16-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_16bit_integer(
     libnk2_record_entry_t *record_entry,
     uint16_t *value_16bit,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_16bit_integer";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_INTEGER_16BIT_SIGNED )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size != 2 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_16bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 16-bit.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 internal_record_entry->value_data,
	 *value_16bit );

	return( 1 );
}

/* Retrieves the data as a 32-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_32bit_integer(
     libnk2_record_entry_t *record_entry,
     uint32_t *value_32bit,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_32bit_integer";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED )
	 && ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_ERROR ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size != 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_32bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 32-bit.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 internal_record_entry->value_data,
	 *value_32bit );

	return( 1 );
}

/* Retrieves the data as a 64-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_64bit_integer(
     libnk2_record_entry_t *record_entry,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_64bit_integer";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED )
	 && ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_CURRENCY ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size != 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint64_little_endian(
	 internal_record_entry->value_data,
	 *value_64bit );

	return( 1 );
}

/* Retrieves the data as a 64-bit FILETIME value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_filetime(
     libnk2_record_entry_t *record_entry,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_filetime";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_FILETIME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size != 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint64_little_endian(
	 internal_record_entry->value_data,
	 *filetime );

	return( 1 );
}

/* Retrieves the data as a 64-bit floating time value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_floatingtime(
     libnk2_record_entry_t *record_entry,
     uint64_t *floatingtime,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_floatingtime";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_FLOATINGTIME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size != 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( floatingtime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floatingtime.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint64_little_endian(
	 internal_record_entry->value_data,
	 *floatingtime );

	return( 1 );
}

/* Retrieves the data as a size_t value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_size(
     libnk2_record_entry_t *record_entry,
     size64_t *value_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_size";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED )
	 && ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( value_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value size.",
		 function );

		return( -1 );
	}
	/* The value data size of a size value is 4 or 8
	 */
	if( ( internal_record_entry->value_data_size != 4 )
	 && ( internal_record_entry->value_data_size != 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size == 4 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 internal_record_entry->value_data,
		 *value_size );
	}
	else if( internal_record_entry->value_data_size == 8 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 internal_record_entry->value_data,
		 *value_size );
	}
	return( 1 );
}

/* Retrieves the floating point value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_floating_point(
     libnk2_record_entry_t *record_entry,
     double *value_floating_point,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_double;
	byte_stream_float32_t value_float;

	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_floating_point";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_FLOAT_32BIT )
	 && ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_DOUBLE_64BIT ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( value_floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value floating point.",
		 function );

		return( -1 );
	}
	/* The value data size of a floating point value is 4 or 8
	 */
	if( ( internal_record_entry->value_data_size != 4 )
	 && ( internal_record_entry->value_data_size != 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size == 4 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 internal_record_entry->value_data,
		 value_float.integer );

		*value_floating_point = (double) value_float.floating_point;
	}
	else if( internal_record_entry->value_data_size == 8 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 internal_record_entry->value_data,
		 value_double.integer );

		*value_floating_point = value_double.floating_point;
	}
	return( 1 );
}

/* Retrieves the size of the data formatted as an UTF-8 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_utf8_string_size(
     libnk2_record_entry_t *record_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_utf8_string_size";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
	 && ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( libnk2_mapi_value_get_data_as_utf8_string_size(
	     internal_record_entry->value_type,
	     internal_record_entry->value_data,
	     internal_record_entry->value_data_size,
	     internal_record_entry->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of value data as UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data formatted as an UTF-8 string
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_utf8_string(
     libnk2_record_entry_t *record_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_utf8_string";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
	 && ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( libnk2_mapi_value_get_data_as_utf8_string(
	     internal_record_entry->value_type,
	     internal_record_entry->value_data,
	     internal_record_entry->value_data_size,
	     internal_record_entry->ascii_codepage,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value data as UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the data formatted as an UTF-16 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_utf16_string_size(
     libnk2_record_entry_t *record_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_utf16_string_size";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
	 && ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( libnk2_mapi_value_get_data_as_utf16_string_size(
	     internal_record_entry->value_type,
	     internal_record_entry->value_data,
	     internal_record_entry->value_data_size,
	     internal_record_entry->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of value data as UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data formatted as an UTF-16 string
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_utf16_string(
     libnk2_record_entry_t *record_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_utf16_string";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
	 && ( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( libnk2_mapi_value_get_data_as_utf16_string(
	     internal_record_entry->value_type,
	     internal_record_entry->value_data,
	     internal_record_entry->value_data_size,
	     internal_record_entry->ascii_codepage,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value data as UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as a GUID value
 * Returns 1 if successful or -1 on error
 */
int libnk2_record_entry_get_data_as_guid(
     libnk2_record_entry_t *record_entry,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_record_entry_get_data_as_guid";

	if( record_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record_entry = (libnk2_internal_record_entry_t *) record_entry;

	if( internal_record_entry->value_type != LIBNK2_VALUE_TYPE_GUID )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record_entry->value_data_size != 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: GUID data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     internal_record_entry->value_data,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}


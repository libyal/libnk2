/*
 * libnk2 Input/Output (IO) handle
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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
#include <endian.h>
#include <memory.h>
#include <types.h>

#include "libnk2_allocation_table.h"
#include "libnk2_crc.h"
#include "libnk2_debug.h"
#include "libnk2_definitions.h"
#include "libnk2_index.h"
#include "libnk2_item_descriptor.h"
#include "libnk2_item_tree.h"
#include "libnk2_io_handle.h"
#include "libnk2_libbfio.h"
#include "libnk2_notify.h"
#include "libnk2_offset_list.h"
#include "libnk2_string.h"
#include "libnk2_tree_type.h"

#include "nk2_file_header.h"

uint8_t nk2_file_signature[ 4 ] = { 0x21, 0x42, 0x44, 0x4e };

/* Initialize an io handle
 * Make sure the value io_handle is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_initialize(
     libnk2_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "libnk2_io_handle_initialize";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( *io_handle == NULL )
	{
		*io_handle = (libnk2_io_handle_t *) memory_allocate(
		                                     sizeof( libnk2_io_handle_t ) );

		if( *io_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create io handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *io_handle,
		     0,
		     sizeof( libnk2_io_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file.",
			 function );

			memory_free(
			 *io_handle );

			*io_handle = NULL;

			return( -1 );
		}
		if( libbfio_file_initialize(
		     &( ( *io_handle )->file_io_handle ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize file io handle.",
			 function );

			memory_free(
			 *io_handle );

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees an exisisting io handle
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_free(
     libnk2_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "libnk2_io_handle_free";
	int result            = 1;

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		if( ( ( *io_handle )->descriptor_index_root_node != NULL )
		 && ( libnk2_tree_node_free(
		       ( *io_handle )->descriptor_index_root_node,
		       &libnk2_index_values_free,
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free descriptor index .",
			 function );

			result = -1;
		}
		if( ( ( *io_handle )->offset_index_root_node != NULL )
		 && ( libnk2_tree_node_free(
		       ( *io_handle )->offset_index_root_node,
		       &libnk2_index_values_free,
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free offset index .",
			 function );

			result = -1;
		}
		if( ( ( *io_handle )->recovered_descriptor_index_root_node != NULL )
		 && ( libnk2_tree_node_free(
		       ( *io_handle )->recovered_descriptor_index_root_node,
		       &libnk2_index_values_free,
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free recovered descriptor index .",
			 function );

			result = -1;
		}
		if( ( ( *io_handle )->recovered_offset_index_root_node != NULL )
		 && ( libnk2_tree_node_free(
		       ( *io_handle )->recovered_offset_index_root_node,
		       &libnk2_index_values_free,
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free recovered offset index .",
			 function );

			result = -1;
		}
		if( ( ( *io_handle )->file_io_handle != NULL )
		 && ( libbfio_handle_free(
		       &( ( *io_handle )->file_io_handle ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file io handle.",
			 function );

			result = -1;
		}
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( result );
}

/* Opens an io handle
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_open(
     libnk2_io_handle_t *io_handle,
     const char *filename,
     int flags,
     liberror_error_t **error )
{
        static char *function = "libnk2_io_handle_open";

        if( io_handle == NULL )
        {
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
                 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
                 "%s: invalid io handle.",
                 function );

                return( -1 );
        }
	if( libbfio_file_set_name(
	     io_handle->file_io_handle,
	     filename,
	     narrow_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file io handle.",
                 function );

                return( -1 );
	}
	if( libbfio_open(
	     io_handle->file_io_handle,
	     flags,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_IO,
                 LIBERROR_IO_ERROR_OPEN_FAILED,
                 "%s: unable to open file io handle.",
                 function );

                return( -1 );
	}
	return( 1 );
}

#if defined( LIBNK2_WIDE_CHARACTER_TYPE )

/* Opens an io handle
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_open_wide(
     libnk2_io_handle_t *io_handle,
     const wchar_t *filename,
     int flags,
     liberror_error_t **error )
{
        static char *function = "libnk2_io_handle_open_wide";

        if( io_handle == NULL )
        {
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
                 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
                 "%s: invalid io handle.",
                 function );

                return( -1 );
        }
	if( libbfio_set_filename_wide(
	     io_handle->file_io_handle,
	     filename,
	     wide_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file io handle.",
                 function );

                return( -1 );
	}
	if( libbfio_open(
	     io_handle->file_io_handle,
	     flags,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_IO,
                 LIBERROR_IO_ERROR_OPEN_FAILED,
                 "%s: unable to open file io handle.",
                 function );

                return( -1 );
	}
	return( 1 );
}

#endif

/* Closes an io handle
 * Returns 0 if successful or -1 on error
 */
int libnk2_io_handle_close(
     libnk2_io_handle_t *io_handle,
     liberror_error_t **error )
{
        static char *function = "libnk2_io_handle_close";

        if( io_handle == NULL )
        {
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
                 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
                 "%s: invalid io handle.",
                 function );

                return( -1 );
        }
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnk2_debug_print_read_offsets(
	     io_handle->file_io_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print the read offsets.",
		 function );
	}
#endif
	if( libbfio_close(
	     io_handle->file_io_handle,
	     error ) != 0 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_IO,
                 LIBERROR_IO_ERROR_CLOSE_FAILED,
                 "%s: unable to close file io handle.",
                 function );

                return( -1 );
	}
	return( 0 );
}

/* Reads a file header
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_file_header(
     libnk2_io_handle_t *io_handle,
     off64_t *offset_index_root_node_offset,
     uint64_t *offset_index_back_pointer,
     off64_t *descriptor_index_root_node_offset,
     uint64_t *descriptor_index_back_pointer,
     int *file_content_type,
     liberror_error_t **error )
{
	uint8_t *file_header      = NULL;
	uint8_t *file_header_data = NULL;
	static char *function     = "libnk2_io_handle_read_file_header";
	size_t data_size          = 528;
	size_t read_size          = 528;
	ssize_t read_count        = 0;
	uint64_t test             = 0;
	uint32_t calculated_crc   = 0;
	uint32_t stored_crc       = 0;
	uint16_t content_type     = 0;
	uint16_t data_version     = 0;
	uint8_t sentinal          = 0;

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( io_handle->file_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid io handle - missing file io handle.",
		 function );

		return( -1 );
	}
	if( offset_index_root_node_offset == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset index root node offset.",
		 function );

		return( -1 );
	}
	if( offset_index_back_pointer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset index back pointer.",
		 function );

		return( -1 );
	}
	if( descriptor_index_root_node_offset == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid descriptor index root node offset.",
		 function );

		return( -1 );
	}
	if( descriptor_index_back_pointer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid descriptor index back pointer.",
		 function );

		return( -1 );
	}
	if( file_content_type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file content type.",
		 function );

		return( -1 );
	}
	file_header_data = (uint8_t *) memory_allocate(
	                                read_size );

	if( file_header_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header data.",
		 function );

		return( -1 );
	}
	read_count = libbfio_read(
	              io_handle->file_io_handle,
	              file_header_data,
	              read_size,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data.",
		 function );

		memory_free(
		 file_header_data );

		return( -1 );
	}
	file_header = file_header_data;

#if defined( HAVE_DEBUG_OUTPUT )
	libnk2_notify_verbose_printf(
	 "%s: file header:\n",
	 function );
	libnk2_notify_verbose_dump_data(
	 file_header_data,
	 sizeof( nk2_file_header_t ) );
#endif

	if( memory_compare(
	     ( (nk2_file_header_t *) file_header )->signature,
	     nk2_file_signature,
	     4 ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		memory_free(
		 file_header_data );

		return( -1 );
	}
	if( libnk2_crc_weak_calculate(
	     0,
	     &( file_header_data[ 8 ] ),
	     471,
	     &calculated_crc,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unable to calculate crc.",
		 function );

		memory_free(
		 file_header_data );

		return( -1 );
	}
	endian_little_convert_32bit(
	 stored_crc,
	 ( (nk2_file_header_t *) file_header )->crc );

	if( stored_crc != calculated_crc )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_INPUT,
		 LIBERROR_INPUT_ERROR_CRC_MISMATCH,
		 "%s: mismatch in file header crc ( %" PRIu32 " != %" PRIu32 " ).",
		 function,
		 stored_crc,
		 calculated_crc );

		memory_free(
		 file_header_data );

		return( -1 );
	}
	endian_little_convert_16bit(
	 content_type,
	 ( (nk2_file_header_t *) file_header )->content_type );

	if( content_type == NK2_FILE_HEADER_CONTENT_TYPE_PAB )
	{
		*file_content_type = LIBNK2_FILE_CONTENT_TYPE_PAB;
	}
	else if( content_type == NK2_FILE_HEADER_CONTENT_TYPE_PST )
	{
		*file_content_type = LIBNK2_FILE_CONTENT_TYPE_PST;
	}
	else if( content_type == NK2_FILE_HEADER_CONTENT_TYPE_OST )
	{
		*file_content_type = LIBNK2_FILE_CONTENT_TYPE_OST;
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsuported content type: 0x%04" PRIx16 ".",
		 function,
		 content_type );

		return( -1 );
	}
	endian_little_convert_16bit(
	 data_version,
	 ( (nk2_file_header_t *) file_header )->data_version );

	if( data_version == 0x000e )
	{
		data_size            = sizeof( nk2_file_header_data_32bit_t );
		io_handle->file_type = LIBNK2_FILE_TYPE_32BIT;
	}
	else if( ( data_version == 0x0015 )
	      || ( data_version == 0x0017 ) )
	{
		data_size            = sizeof( nk2_file_header_data_64bit_t );
		io_handle->file_type = LIBNK2_FILE_TYPE_64BIT;
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsuported data version: 0x%04" PRIx16 ".",
		 function,
		 data_version );

		memory_free(
		 file_header_data );

		return( -1 );
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	endian_little_convert_32bit(
	 test,
	 ( (nk2_file_header_t *) file_header )->signature );
	libnk2_notify_verbose_printf(
	 "%s: signature\t\t: 0x08%" PRIx64 "\n",
	 function,
	 test );
	libnk2_notify_verbose_printf(
	 "%s: crc\t\t\t: 0x08%" PRIx64 "\n",
	 function,
	 stored_crc );
	libnk2_notify_verbose_printf(
	 "%s: content type\t\t: 0x%04" PRIx16 "\n",
	 function,
	 content_type );
	libnk2_notify_verbose_printf(
	 "%s: data version\t\t: %" PRIu16 "\n",
	 function,
	 data_version );
	endian_little_convert_16bit(
	 test,
	 ( (nk2_file_header_t *) file_header )->content_version );
	libnk2_notify_verbose_printf(
	 "%s: content version\t: %" PRIu64 "\n",
	 function,
	 test );
	libnk2_notify_verbose_printf(
	 "%s: creation platform\t: 0x%02" PRIx8 "\n",
	 function,
	 ( (nk2_file_header_t *) file_header )->creation_platform );
	libnk2_notify_verbose_printf(
	 "%s: access platform\t: 0x%02" PRIx8 "\n",
	 function,
	 ( (nk2_file_header_t *) file_header )->access_platform );
	endian_little_convert_32bit(
	 test,
	 ( (nk2_file_header_t *) file_header )->unknown1 );
	libnk2_notify_verbose_printf(
	 "%s: unknown1\t\t: %" PRIu64 "\n",
	 function,
	 test );
	endian_little_convert_32bit(
	 test,
	 ( (nk2_file_header_t *) file_header )->unknown2 );
	libnk2_notify_verbose_printf(
	 "%s: unknown2\t\t: %" PRIu64 "\n",
	 function,
	 test );
	libnk2_notify_verbose_printf(
	 "\n" );
#endif

	file_header = &( file_header_data[ sizeof( nk2_file_header_t ) ] );

#if defined( HAVE_DEBUG_OUTPUT )
	libnk2_notify_verbose_printf(
	 "%s: file header data:\n",
	 function );
	libnk2_notify_verbose_dump_data(
	 file_header,
	 data_size );
#endif

	if( io_handle->file_type == LIBNK2_FILE_TYPE_32BIT )
	{
		endian_little_convert_32bit(
		 io_handle->file_size,
		 ( (nk2_file_header_data_32bit_t *) file_header )->file_size );

		endian_little_convert_32bit(
		 *descriptor_index_back_pointer,
		 ( (nk2_file_header_data_32bit_t *) file_header )->descriptor_index_back_pointer );
		endian_little_convert_32bit(
		 *descriptor_index_root_node_offset,
		 ( (nk2_file_header_data_32bit_t *) file_header )->descriptor_index_root_node_offset );
		endian_little_convert_32bit(
		 *offset_index_back_pointer,
		 ( (nk2_file_header_data_32bit_t *) file_header )->offset_index_back_pointer );
		endian_little_convert_32bit(
		 *offset_index_root_node_offset,
		 ( (nk2_file_header_data_32bit_t *) file_header )->offset_index_root_node_offset );

		sentinal                   = ( (nk2_file_header_data_32bit_t *) file_header )->sentinal;
		io_handle->encryption_type = ( (nk2_file_header_data_32bit_t *) file_header )->encryption_type;
	}
	else if( io_handle->file_type == LIBNK2_FILE_TYPE_64BIT )
	{
		endian_little_convert_64bit(
		 io_handle->file_size,
		 ( (nk2_file_header_data_64bit_t *) file_header )->file_size );

		endian_little_convert_64bit(
		 *descriptor_index_back_pointer,
		 ( (nk2_file_header_data_64bit_t *) file_header )->descriptor_index_back_pointer );
		endian_little_convert_64bit(
		 *descriptor_index_root_node_offset,
		 ( (nk2_file_header_data_64bit_t *) file_header )->descriptor_index_root_node_offset );
		endian_little_convert_64bit(
		 *offset_index_back_pointer,
		 ( (nk2_file_header_data_64bit_t *) file_header )->offset_index_back_pointer );
		endian_little_convert_64bit(
		 *offset_index_root_node_offset,
		 ( (nk2_file_header_data_64bit_t *) file_header )->offset_index_root_node_offset );

		sentinal                   = ( (nk2_file_header_data_64bit_t *) file_header )->sentinal;
		io_handle->encryption_type = ( (nk2_file_header_data_64bit_t *) file_header )->encryption_type;

	}
#if defined( HAVE_VERBOSE_OUTPUT )
	if( io_handle->file_type == LIBNK2_FILE_TYPE_32BIT )
	{
		endian_little_convert_32bit(
		 test,
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown1 );
		libnk2_notify_verbose_printf(
		 "%s: unknown1\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		endian_little_convert_32bit(
		 test,
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown2 );
		libnk2_notify_verbose_printf(
		 "%s: unknown2\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		endian_little_convert_32bit(
		 test,
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown3 );
		libnk2_notify_verbose_printf(
		 "%s: unknown3\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		libnk2_notify_verbose_printf(
		 "%s: unknown4:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown4,
		 128 );

		libnk2_notify_verbose_printf(
		 "%s: padding1:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_32bit_t *) file_header )->padding1,
		 4 );
	}
	else if( io_handle->file_type == LIBNK2_FILE_TYPE_64BIT )
	{
		endian_little_convert_64bit(
		 test,
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown1 );
		libnk2_notify_verbose_printf(
		 "%s: unknown1\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		endian_little_convert_64bit(
		 test,
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown2 );
		libnk2_notify_verbose_printf(
		 "%s: unknown2\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		endian_little_convert_32bit(
		 test,
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown3 );
		libnk2_notify_verbose_printf(
		 "%s: unknown3\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		libnk2_notify_verbose_printf(
		 "%s: unknown4:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown4,
		 128 );

		libnk2_notify_verbose_printf(
		 "%s: padding1:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_64bit_t *) file_header )->padding1,
		 12 );
	}
	libnk2_notify_verbose_printf(
	 "%s: file size\t\t\t\t: %" PRIu64 "\n",
	 function,
	 io_handle->file_size );

	if( io_handle->file_type == LIBNK2_FILE_TYPE_32BIT )
	{
		endian_little_convert_32bit(
		 test,
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown5 );
		libnk2_notify_verbose_printf(
		 "%s: unknown5\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		endian_little_convert_32bit(
		 test,
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown6 );
		libnk2_notify_verbose_printf(
		 "%s: unknown6\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		endian_little_convert_32bit(
		 test,
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown7 );
		libnk2_notify_verbose_printf(
		 "%s: unknown7\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
	}
	else if( io_handle->file_type == LIBNK2_FILE_TYPE_64BIT )
	{
		endian_little_convert_64bit(
		 test,
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown5 );
		libnk2_notify_verbose_printf(
		 "%s: unknown5\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		endian_little_convert_64bit(
		 test,
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown6 );
		libnk2_notify_verbose_printf(
		 "%s: unknown6\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		endian_little_convert_64bit(
		 test,
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown7 );
		libnk2_notify_verbose_printf(
		 "%s: unknown7\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
	}
	libnk2_notify_verbose_printf(
	 "%s: descriptor index root node offset\t: %" PRIu64 "\n",
	 function,
	 *descriptor_index_root_node_offset );
	libnk2_notify_verbose_printf(
	 "%s: descriptor index back pointer\t: %" PRIu64 "\n",
	 function,
	 *descriptor_index_back_pointer );
	libnk2_notify_verbose_printf(
	 "%s: offset index root node offset\t: %" PRIu64 "\n",
	 function,
	 *offset_index_root_node_offset );
	libnk2_notify_verbose_printf(
	 "%s: offset index back pointer\t\t: %" PRIu64 "\n",
	 function,
	 *offset_index_back_pointer );

	if( io_handle->file_type == LIBNK2_FILE_TYPE_32BIT )
	{
		endian_little_convert_32bit(
		 test,
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown8 );
		libnk2_notify_verbose_printf(
		 "%s: unknown8\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		libnk2_notify_verbose_printf(
		 "%s: unknown9:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown9,
		 128 );
		libnk2_notify_verbose_printf(
		 "%s: unknown10:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown10,
		 128 );
	}
	else if( io_handle->file_type == LIBNK2_FILE_TYPE_64BIT )
	{
		endian_little_convert_64bit(
		 test,
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown8 );
		libnk2_notify_verbose_printf(
		 "%s: unknown8\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		libnk2_notify_verbose_printf(
		 "%s: unknown9:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown9,
		 128 );
		libnk2_notify_verbose_printf(
		 "%s: unknown10:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown10,
		 128 );
	}
	libnk2_notify_verbose_printf(
	 "%s: sentinal\t\t\t\t: 0x%02" PRIx8 "\n",
	 function,
	 sentinal );
	libnk2_notify_verbose_printf(
	 "%s: encryption type\t\t\t: 0x%02" PRIx8 "\n",
	 function,
	 io_handle->encryption_type );

	if( io_handle->file_type == LIBNK2_FILE_TYPE_32BIT )
	{
		endian_little_convert_16bit(
		 test,
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown11 );
		libnk2_notify_verbose_printf(
		 "%s: unknown11\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		libnk2_notify_verbose_printf(
		 "%s: unknown12:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_32bit_t *) file_header )->unknown12,
		 15 );
	}
	else if( io_handle->file_type == LIBNK2_FILE_TYPE_64BIT )
	{
		endian_little_convert_16bit(
		 test,
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown11 );
		libnk2_notify_verbose_printf(
		 "%s: unknown11\t\t\t\t: %" PRIu64 "\n",
		 function,
		 test );
		libnk2_notify_verbose_printf(
		 "%s: unknown12:\n",
		 function );
		libnk2_notify_verbose_dump_data(
		 ( (nk2_file_header_data_64bit_t *) file_header )->unknown12,
		 8 );

		if( libnk2_crc_weak_calculate(
		     0,
		     &( file_header_data[ 8 ] ),
		     516,
		     &calculated_crc,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unable to calculate crc.",
			 function );

			memory_free(
			 file_header_data );

			return( -1 );
		}
		endian_little_convert_32bit(
		 stored_crc,
		 ( (nk2_file_header_data_64bit_t *) file_header )->crc );

		if( stored_crc != calculated_crc )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_INPUT,
			 LIBERROR_INPUT_ERROR_CRC_MISMATCH,
			 "%s: mismatch in file header crc ( %" PRIu32 " != %" PRIu32 " ).",
			 function,
			 stored_crc,
			 calculated_crc );

			memory_free(
			 file_header_data );

			return( -1 );
		}
	}
	libnk2_notify_verbose_printf(
	 "\n" );
#endif
	memory_free(
	 file_header_data );

	if( ( io_handle->encryption_type != LIBNK2_ENCRYPTION_TYPE_NONE )
	 && ( io_handle->encryption_type != LIBNK2_ENCRYPTION_TYPE_COMPRESSIBLE )
	 && ( io_handle->encryption_type != LIBNK2_ENCRYPTION_TYPE_HIGH ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported encryption type: 0x%02x",
		 function,
		 io_handle->encryption_type );

		return( -1 );
	}
	return( 1 );
}

/* Reads the unallocated data blocks
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_unallocated_data_blocks(
     libnk2_io_handle_t *io_handle,
     libnk2_list_t *unallocated_data_block_list,
     liberror_error_t **error )
{
	static char *function           = "libnk2_io_handle_read_unallocated_data_blocks";
	off64_t allocation_table_offset = 0;
	size64_t allocation_block_size  = 0;

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	allocation_table_offset = 0x4400;
	allocation_block_size   = 496 * 512;

	while( allocation_table_offset < (off64_t) io_handle->file_size )
	{
		if( libnk2_allocation_table_read(
		     unallocated_data_block_list,
		     io_handle->file_io_handle,
		     allocation_table_offset,
		     (int) io_handle->file_type,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read allocation table at offset: %" PRIu64 ".",
			 function,
			 allocation_table_offset );

			return( -1 );
		}
		allocation_table_offset += allocation_block_size;
	}
	return( 1 );
}

/* Reads the unallocated index node blocks
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_unallocated_index_node_blocks(
     libnk2_io_handle_t *io_handle,
     libnk2_list_t *unallocated_index_node_block_list,
     liberror_error_t **error )
{
	static char *function           = "libnk2_io_handle_read_unallocated_index_node_blocks";
	off64_t allocation_table_offset = 0;
	size64_t allocation_block_size  = 0;

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	allocation_table_offset = 0x4600;
	allocation_block_size   = 496 * 4096;

	while( allocation_table_offset < (off64_t) io_handle->file_size )
	{
		if( libnk2_allocation_table_read(
		     unallocated_index_node_block_list,
		     io_handle->file_io_handle,
		     allocation_table_offset,
		     (int) io_handle->file_type,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read allocation table at offset: %" PRIu64 ".",
			 function,
			 allocation_table_offset );

			return( -1 );
		}
		allocation_table_offset += allocation_block_size;
	}
	return( 1 );
}

/* Reads the descriptor index
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_descriptor_index(
     libnk2_io_handle_t *io_handle,
     off64_t descriptor_index_root_node_offset,
     uint64_t descriptor_index_back_pointer,
     liberror_error_t **error )
{
	static char *function = "libnk2_io_handle_read_descriptor_index";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( io_handle->descriptor_index_root_node != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid io handle - descriptor index root node already set.",
		 function );

		return( -1 );
	}
	io_handle->descriptor_index_root_node = (libnk2_tree_node_t *) memory_allocate(
					                                sizeof( libnk2_tree_node_t ) );

	if( io_handle->descriptor_index_root_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create descriptor index root node.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle->descriptor_index_root_node,
	     0,
	     sizeof( libnk2_tree_node_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear descriptor index root node.",
		 function );

		memory_free(
		 io_handle->descriptor_index_root_node );

		io_handle->descriptor_index_root_node = NULL;

		return( -1 );
	}
	if( libnk2_index_read_tree(
	     io_handle->descriptor_index_root_node,
	     io_handle->file_io_handle,
	     descriptor_index_root_node_offset,
	     (int) io_handle->file_type,
	     LIBNK2_INDEX_TYPE_DESCRIPTOR,
	     descriptor_index_back_pointer,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read descriptor index.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the (file) offset index
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_offset_index(
     libnk2_io_handle_t *io_handle,
     off64_t offset_index_root_node_offset,
     uint64_t offset_index_back_pointer,
     liberror_error_t **error )
{
	static char *function = "libnk2_io_handle_read_offset_index";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( io_handle->offset_index_root_node != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid io handle - offset index root node already set.",
		 function );

		return( -1 );
	}
	io_handle->offset_index_root_node = (libnk2_tree_node_t *) memory_allocate(
					                            sizeof( libnk2_tree_node_t ) );

	if( io_handle->offset_index_root_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create offset index root node.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle->offset_index_root_node,
	     0,
	     sizeof( libnk2_tree_node_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear offset index root node.",
		 function );

		memory_free(
		 io_handle->offset_index_root_node );

		io_handle->offset_index_root_node = NULL;

		return( -1 );
	}
	if( libnk2_index_read_tree(
	     io_handle->offset_index_root_node,
	     io_handle->file_io_handle,
	     offset_index_root_node_offset,
	     (int) io_handle->file_type,
	     LIBNK2_INDEX_TYPE_OFFSET,
	     offset_index_back_pointer,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read offset index.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Scans for recoverable items
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_recover_items(
     libnk2_io_handle_t *io_handle,
     libnk2_list_t *unallocated_data_block_list,
     libnk2_list_t *unallocated_index_node_block_list,
     libnk2_list_t *recovered_item_list,
     liberror_error_t **error )
{
	libnk2_item_descriptor_t *item_descriptor     = NULL;
	libnk2_index_values_t *child_index_values     = NULL;
	libnk2_index_values_t *result_index_values    = NULL;
	libnk2_index_values_t *recovered_index_values = NULL;
	libnk2_list_element_t *list_element           = NULL;
	libnk2_tree_node_t *child_node                = NULL;
	libnk2_tree_node_t *index_tree_node           = NULL;
	libnk2_tree_node_t *index_root_node           = NULL;
	libnk2_tree_node_t *item_tree_node            = NULL;
	libnk2_tree_node_t *recovered_index_root_node = NULL;
	libnk2_tree_node_t *recovered_index_tree_node = NULL;
	libnk2_tree_node_t *result_node               = NULL;
	libnk2_tree_node_t *result_parent_node        = NULL;
	libnk2_character_t *index_string              = NULL;
	static char *function                         = "libnk2_io_handle_recover_items";
	off64_t block_offset                          = 0;
	size64_t block_size                           = 0;
	uint64_t back_pointer                         = 0;
	uint16_t index_type                           = 0;
	uint8_t node_level                            = 0;
	int amount_of_child_nodes                     = 0;
	int block_iterator                            = 0;
	int child_iterator                            = 0;
	int recoverable                               = 0;
	int result                                    = 0;

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( unallocated_data_block_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid unallocated data block list.",
		 function );

		return( -1 );
	}
	if( unallocated_index_node_block_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid unallocated index node block list.",
		 function );

		return( -1 );
	}
	if( recovered_item_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid recovered item list.",
		 function );

		return( -1 );
	}
	/* Create the recovered descriptor index root node
	 */
	if( io_handle->recovered_descriptor_index_root_node != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid io handle - recovered descriptor index root node already set.",
		 function );

		return( -1 );
	}
	io_handle->recovered_descriptor_index_root_node = libnk2_index_node_allocate(
	                                                   error );

	if( io_handle->recovered_descriptor_index_root_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create recovered descriptor index root node.",
		 function );

		return( -1 );
	}
	/* Create the recovered offset index root node
	 */
	if( io_handle->recovered_offset_index_root_node != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid io handle - recovered offset index root node already set.",
		 function );

		return( -1 );
	}
	io_handle->recovered_offset_index_root_node = libnk2_index_node_allocate(
	                                               error );

	if( io_handle->recovered_offset_index_root_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create recovered offset index root node.",
		 function );

		return( -1 );
	}
	/* Scan the unallocated index node block list
	 */
	list_element = unallocated_index_node_block_list->first;

	for( block_iterator = 0; block_iterator < unallocated_index_node_block_list->amount_of_elements; block_iterator++ )
	{
		if( list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: corruption detected in unallocated block list at element: %d.",
			 function,
			 block_iterator );

			return( -1 );
		}
		if( list_element->value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset values for list element: %d.",
			 function,
			 block_iterator );

			return( -1 );
		}
		block_offset = ( (libnk2_offset_list_values_t *) list_element->value )->offset;
		block_size   = ( (libnk2_offset_list_values_t *) list_element->value )->size;

		/* The index nodes are 512 bytes of size
		 */
		while( block_size >= 512 )
		{
			/* The index nodes are 512 bytes aligned
			 */
			if( ( block_offset % 512 ) == 0 )
			{
				index_tree_node = (libnk2_tree_node_t *) memory_allocate(
									  sizeof( libnk2_tree_node_t ) );

				if( index_tree_node == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_MEMORY,
					 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to index tree node.",
					 function );

					return( -1 );
				}
				if( memory_set(
				     index_tree_node,
				     0,
				     sizeof( libnk2_tree_node_t ) ) == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_MEMORY,
					 LIBERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to clear index tree node.",
					 function );

					memory_free(
					 index_tree_node );

					return( -1 );
				}
				if( libnk2_index_read_node(
				     index_tree_node,
				     io_handle->file_io_handle,
				     block_offset,
				     (int) io_handle->file_type,
				     &node_level,
				     &index_type,
				     &back_pointer,
				     NULL ) != 1 )
				{
					memory_free(
					 index_tree_node );
				}
				else
				{
					if( ( node_level == 0 )
					 && ( ( index_type == LIBNK2_INDEX_TYPE_DESCRIPTOR )
					  || ( index_type == LIBNK2_INDEX_TYPE_OFFSET ) ) )
					{
						/* Check if the index leaf nodes are recoverable
						 */
						amount_of_child_nodes = index_tree_node->amount_of_child_nodes;
						child_node            = index_tree_node->first_child;

						for( child_iterator = 0; child_iterator < amount_of_child_nodes; child_iterator++ )
						{
							if( child_node == NULL )
							{
								liberror_error_set(
								 error,
								 LIBERROR_ERROR_DOMAIN_RUNTIME,
								 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
								 "%s: corruption detected for index node: %d.",
								 function,
								 child_iterator + 1 );

								libnk2_tree_node_free(
								 index_tree_node,
								 &libnk2_index_values_free,
								 NULL );

								return( -1 );
							}
							if( child_node->value == NULL )
							{
								liberror_error_set(
								 error,
								 LIBERROR_ERROR_DOMAIN_RUNTIME,
								 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
								 "%s: invalid index node: %d - missing value.",
								 function,
								 child_iterator + 1 );

								libnk2_tree_node_free(
								 index_tree_node,
								 &libnk2_index_values_free,
								 NULL );

								return( -1 );
							}
							child_index_values = (libnk2_index_values_t *) child_node->value;

							if( index_type == LIBNK2_INDEX_TYPE_DESCRIPTOR )
							{
								index_string              = _LIBNK2_STRING( "descriptor" );
								index_root_node           = io_handle->descriptor_index_root_node;
								recovered_index_root_node = io_handle->recovered_descriptor_index_root_node;
							}
							else if( index_type == LIBNK2_INDEX_TYPE_OFFSET )
							{
								index_string              = _LIBNK2_STRING( "offset" );
								index_root_node           = io_handle->offset_index_root_node;
								recovered_index_root_node = io_handle->recovered_offset_index_root_node;
							}
							result_node = NULL;

							/* Check if the index node already exists
							 */
							result = libnk2_index_get_tree_node(
								  index_root_node,
								  child_index_values->identifier,
								  &result_node,
								  error );

							if( result == -1 )
							{
								liberror_error_set(
								 error,
								 LIBERROR_ERROR_DOMAIN_RUNTIME,
								 LIBERROR_RUNTIME_ERROR_GET_FAILED,
								 "%s: error retrieving %" PRIs_LIBNK2 " index identifier: %" PRIu64 ".",
								 function,
								 index_string,
								 child_index_values->identifier );

								libnk2_tree_node_free(
								 index_tree_node,
								 &libnk2_index_values_free,
								 NULL );

								return( -1 );
							}
							else if( result == 0 )
							{
#if defined( HAVE_VERBOSE_OUTPUT )
								libnk2_notify_verbose_printf(
								 "%s: %" PRIs_LIBNK2 " index identifier: %" PRIu64 " does not exist.\n",
								 function,
								 index_string,
								 child_index_values->identifier );
#endif
								recoverable = 1;

								/* Check if the offset index value is unallocated according to the
								 * unallocated data block list
								 */
								if( index_type == LIBNK2_INDEX_TYPE_OFFSET )
								{
									result = libnk2_offset_list_range_is_present(
										  unallocated_data_block_list,
										  child_index_values->file_offset,
										  child_index_values->data_size,
										  error );

									if( result == -1 )
									{
										liberror_error_set(
										 error,
										 LIBERROR_ERROR_DOMAIN_RUNTIME,
										 LIBERROR_RUNTIME_ERROR_GET_FAILED,
										 "%s: error determining if offset range is unallocated.",
										 function );

										libnk2_tree_node_free(
										 index_tree_node,
										 &libnk2_index_values_free,
										 NULL );

										return( -1 );
									}
									else if( result == 0 )
									{
#if defined( HAVE_VERBOSE_OUTPUT )
										libnk2_notify_verbose_printf(
										 "%s: file offset: %" PRIu64 " - %" PRIu64 " allocated.\n",
										 function,
										 child_index_values->file_offset,
										 child_index_values->file_offset + child_index_values->data_size );
#endif
										recoverable = 0;
									}
#if defined( HAVE_VERBOSE_OUTPUT )
									else
									{
										libnk2_notify_verbose_printf(
										 "%s: file offset: %" PRIu64 " - %" PRIu64 " unallocated.\n",
										 function,
										 child_index_values->file_offset,
										 child_index_values->file_offset + child_index_values->data_size );
									}
#endif
								}
								if( recoverable == 1 )
								{
									/* Check if the index node already exists in the recovered index
									 */
									result_node = NULL;

									result = libnk2_index_get_tree_node(
										  recovered_index_root_node,
										  child_index_values->identifier,
										  &result_node,
										  error );

									if( result == -1 )
									{
										liberror_error_set(
										 error,
										 LIBERROR_ERROR_DOMAIN_RUNTIME,
										 LIBERROR_RUNTIME_ERROR_GET_FAILED,
										 "%s: error retrieving recovered %" PRIs_LIBNK2 " index identifier: %" PRIu64 ".",
										 function,
										 index_string,
										 child_index_values->identifier );

										libnk2_tree_node_free(
										 index_tree_node,
										 &libnk2_index_values_free,
										 NULL );

										return( -1 );
									}
									else if( result != 0 )
									{
										if( result_node == NULL )
										{
											liberror_error_set(
											 error,
											 LIBERROR_ERROR_DOMAIN_RUNTIME,
											 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
											 "%s: invalid result node.",
											 function );

											libnk2_tree_node_free(
											 index_tree_node,
											 &libnk2_index_values_free,
											 NULL );

											return( -1 );
										}
										if( result_node->value == NULL )
										{
											liberror_error_set(
											 error,
											 LIBERROR_ERROR_DOMAIN_RUNTIME,
											 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
											 "%s: invalid result node - missing value.",
											 function );

											libnk2_tree_node_free(
											 index_tree_node,
											 &libnk2_index_values_free,
											 NULL );

											return( -1 );
										}
										result_index_values = (libnk2_index_values_t *) result_node->value;

										if( index_type == LIBNK2_INDEX_TYPE_DESCRIPTOR )
										{
											if( result_index_values->parent_identifier != child_index_values->parent_identifier )
											{
#if defined( HAVE_VERBOSE_OUTPUT )
												libnk2_notify_verbose_printf(
												 "%s: found duplicate for %" PRIs_LIBNK2 " indentifier: %" PRIu64 " with different parents.\n",
												 function,
												 index_string,
												 child_index_values->identifier );
#endif
												/* Check if parent identifier exists
												 * if the parent exists we are dealing with more recent deleted information
												 */
												result_parent_node = NULL;

												result = libnk2_index_get_tree_node(
													  index_root_node,
													  child_index_values->parent_identifier,
													  &result_parent_node,
													  error );

												if( result == -1 )
												{
													liberror_error_set(
													 error,
													 LIBERROR_ERROR_DOMAIN_RUNTIME,
													 LIBERROR_RUNTIME_ERROR_GET_FAILED,
													 "%s: error retrieving recovered %" PRIs_LIBNK2 " index identifier: %" PRIu32 ".",
													 function,
													 index_string,
													 child_index_values->parent_identifier );

													libnk2_tree_node_free(
													 index_tree_node,
													 &libnk2_index_values_free,
													 NULL );

													return( -1 );
												}
												else if( ( result != 0 )
												 && ( memory_copy(
												       result_node->value,
												       child_node->value,
												       sizeof( libnk2_index_values_t ) ) == NULL ) )
												{
													liberror_error_set(
													 error,
													 LIBERROR_ERROR_DOMAIN_MEMORY,
													 LIBERROR_MEMORY_ERROR_COPY_FAILED,
													 "%s: unable to copy index node values.",
													 function );

													libnk2_tree_node_free(
													 index_tree_node,
													 &libnk2_index_values_free,
													 NULL );

													return( -1 );
												}
											}
										}
									}
									else
									{
										recovered_index_tree_node = child_node;
									}
								}
							}
#if defined( HAVE_VERBOSE_OUTPUT )
							else
							{
								libnk2_notify_verbose_printf(
								 "%s: %" PRIs_LIBNK2 " index identifier: %" PRIu64 " does exist.\n",
								 function,
								 index_string,
								 child_index_values->identifier );
							}
#endif
							child_node = child_node->next;

							/* Move the recovered node to the index
							 */
							if( recovered_index_tree_node != NULL )
							{
								if( recovered_index_tree_node->value == NULL )
								{
									liberror_error_set(
									 error,
									 LIBERROR_ERROR_DOMAIN_RUNTIME,
									 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
									 "%s: invalid recovered index tree node - missing value.",
									 function );

									libnk2_tree_node_free(
									 index_tree_node,
									 &libnk2_index_values_free,
									 NULL );

									return( -1 );
								}
								recovered_index_values = (libnk2_index_values_t *) recovered_index_tree_node->value;
#if defined( HAVE_VERBOSE_OUTPUT )
								libnk2_notify_verbose_printf(
								 "%s: found recovered %" PRIs_LIBNK2 " index identifier: %" PRIu64 ".\n",
								 function,
								 index_string,
								 recovered_index_values->identifier );
#endif
								if( libnk2_tree_node_remove_node(
								     index_tree_node,
								     recovered_index_tree_node,
								     error ) != 1 )
								{
									liberror_error_set(
									 error,
									 LIBERROR_ERROR_DOMAIN_RUNTIME,
									 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
									 "%s: unable to remove %" PRIs_LIBNK2 " index identifier: %" PRIu64 ".",
									 function,
									 index_string,
									 recovered_index_values->identifier );

									libnk2_tree_node_free(
									 index_tree_node,
									 &libnk2_index_values_free,
									 NULL );

									return( -1 );
								}
								if( libnk2_tree_node_insert_node(
								     recovered_index_root_node,
								     recovered_index_tree_node,
								     &libnk2_index_values_compare,
								     error ) != 1 )
								{
									liberror_error_set(
									 error,
									 LIBERROR_ERROR_DOMAIN_RUNTIME,
									 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
									 "%s: unable to insert %" PRIs_LIBNK2 " index identifier: %" PRIu64 ".",
									 function,
									 index_string,
									 recovered_index_values->identifier );

									libnk2_tree_node_free(
									 recovered_index_tree_node,
									 &libnk2_index_values_free,
									 NULL );
									libnk2_tree_node_free(
									 index_tree_node,
									 &libnk2_index_values_free,
									 NULL );

									return( -1 );
								}
								recovered_index_tree_node = NULL;
							}
						}
					}
					if( libnk2_tree_node_free(
					     index_tree_node,
					     &libnk2_index_values_free,
					     error ) != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free %" PRIs_LIBNK2 " index node.",
						 function,
						 index_string );

						return( -1 );
					}
				}
				block_size   -= 512;
				block_offset += 512;
			}
			else
			{
				block_size   -= ( block_offset % 512 );
				block_offset  = ( ( block_offset / 512 ) + 1 ) * 512;
			}
		}
		list_element = list_element->next;
	}
	/* Check if the list and data offset index values exists for the recovered descriptor index nodes
	 */
	amount_of_child_nodes = io_handle->recovered_descriptor_index_root_node->amount_of_child_nodes;
	child_node            = io_handle->recovered_descriptor_index_root_node->first_child;

	for( child_iterator = 0; child_iterator < amount_of_child_nodes; child_iterator++ )
	{
		if( child_node == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: corruption detected for index node: %d.",
			 function,
			 child_iterator + 1 );

			libnk2_tree_node_free(
			 recovered_index_tree_node,
			 &libnk2_index_values_free,
			 NULL );

			return( -1 );
		}
		if( child_node->value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid index node: %d - missing value.",
			 function,
			 child_iterator + 1 );

			libnk2_tree_node_free(
			 recovered_index_tree_node,
			 &libnk2_index_values_free,
			 NULL );

			return( -1 );
		}
		child_index_values = (libnk2_index_values_t *) child_node->value;

#if defined( HAVE_VERBOSE_OUTPUT )
		libnk2_notify_verbose_printf(
		 "%s: identifier: %" PRIu64 ", data: %" PRIu64 ", list: %" PRIu64 ", parent: %" PRIu32 "\n",
		 function,
		 child_index_values->identifier,
		 child_index_values->data_identifier,
		 child_index_values->list_identifier,
		 child_index_values->parent_identifier );
#endif

		recoverable = 1;

		/* Check if the list identifier exists
		 */
		result_node = NULL;

		result = libnk2_index_get_tree_node(
			  io_handle->recovered_offset_index_root_node,
			  child_index_values->list_identifier,
			  &result_node,
		          error );

		if( result == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: error retrieving recovered list index identifier: %" PRIu64 ".",
			 function,
			 child_index_values->list_identifier );

			libnk2_tree_node_free(
			 recovered_index_tree_node,
			 &libnk2_index_values_free,
			 NULL );

			return( -1 );
		}
		else if( result == 0 )
		{
#if defined( HAVE_VERBOSE_OUTPUT )
			libnk2_notify_verbose_printf(
			 "%s: missing list index identifier: %" PRIu64 ".\n",
			 function,
			 child_index_values->list_identifier );
#endif

			recoverable = 0;
		}
		if( recoverable != 0 )
		{
			/* Check if the data identifier exists
			 */
			result_node = NULL;

			result = libnk2_index_get_tree_node(
				  io_handle->recovered_offset_index_root_node,
				  child_index_values->data_identifier,
				  &result_node,
			          error );

			if( result == -1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: error retrieving recovered data index identifier: %" PRIu64 ".",
				 function,
				 child_index_values->data_identifier );

				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
			else if( result == 0 )
			{
#if defined( HAVE_VERBOSE_OUTPUT )
				libnk2_notify_verbose_printf(
				 "%s: missing recovered data index identifier: %" PRIu64 ".\n",
				 function,
				 child_index_values->data_identifier );
#endif

				recoverable = 0;
			}
		}
		if( recoverable == 0 )
		{
			recovered_index_tree_node = child_node;
		}
		else
		{
			if( child_index_values->identifier > (uint64_t) UINT32_MAX )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid descriptor index identifier value exceeds maximum.",
				 function );

				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
			/* Create a new item descriptor
			 */
			item_descriptor = (libnk2_item_descriptor_t *) memory_allocate(
									sizeof( libnk2_item_descriptor_t ) );

			if( item_descriptor == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create item descriptor.",
				 function );

				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
			if( memory_set(
			     item_descriptor,
			     0,
			     sizeof( libnk2_item_descriptor_t ) ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_SET_FAILED,
				 "%s: unable to clear item descriptor.",
				 function );

				memory_free(
				 item_descriptor );
				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
			item_descriptor->descriptor_identifier = (uint32_t) child_index_values->identifier;
			item_descriptor->recovered             = 1;

/* TODO refactor */
			/* Create a new tree node with item tree values
			 */
			item_tree_node = (libnk2_tree_node_t *) memory_allocate(
			                                         sizeof( libnk2_tree_node_t ) );

			if( item_tree_node == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create item tree node.",
				 function );

				memory_free(
				 item_descriptor );
				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
			if( memory_set(
			     item_tree_node,
			     0,
			     sizeof( libnk2_tree_node_t ) ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_SET_FAILED,
				 "%s: unable to clear item tree node.",
				 function );

				memory_free(
				 item_tree_node );
				memory_free(
				 item_descriptor );
				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
			item_tree_node->value = (intptr_t *) item_descriptor;

			result = libnk2_list_append_value(
			          recovered_item_list,
			          (intptr_t *) item_tree_node,
			          error );

			/* Free the node if it could not be appended
			 */
			if( result != 1 )
			{
				memory_free(
				 item_tree_node );
				memory_free(
				 item_descriptor );
			}
			if( result == -1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append tree node in recovered item list.",
				 function );

				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
		}
		child_node = child_node->next;

		/* Remove incomplete descriptors
		 */
		if( recovered_index_tree_node != NULL )
		{
			if( recovered_index_tree_node->value == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid recovered index tree node - missing value.",
				 function );

				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
			recovered_index_values = (libnk2_index_values_t *) recovered_index_tree_node->value;

#if defined( HAVE_VERBOSE_OUTPUT )
			libnk2_notify_verbose_printf(
			 "%s: incomplete recovered descriptor index identifier: %" PRIu64 ".\n",
			 function,
			 recovered_index_values->identifier );
#endif

			if( libnk2_tree_node_remove_node(
			     io_handle->recovered_descriptor_index_root_node,
			     recovered_index_tree_node,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
				 "%s: unable to remove descriptor index identifier: %" PRIu64 ".",
				 function,
				 recovered_index_values->identifier );

				libnk2_tree_node_free(
				 recovered_index_tree_node,
				 &libnk2_index_values_free,
				 NULL );

				return( -1 );
			}
			if( libnk2_tree_node_free(
			     recovered_index_tree_node,
			     &libnk2_index_values_free,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free recovered index node.",
				 function );

				return( -1 );
			}
			recovered_index_tree_node = NULL;
		}
	}

	/* TODO
	 * link recovered descriptors to parent? and add to item hierarchy?
	 * what about remaining deleted offset index identifiers?
	 * what about remaining unallocated data offsets?
	 */

	return( 1 );
}


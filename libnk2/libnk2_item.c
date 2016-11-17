/*
 * Item functions
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
#include <memory.h>
#include <types.h>

#include "libnk2_definitions.h"
#include "libnk2_io_handle.h"
#include "libnk2_item.h"
#include "libnk2_libbfio.h"
#include "libnk2_libcerror.h"
#include "libnk2_libfmapi.h"
#include "libnk2_libfvalue.h"
#include "libnk2_mapi.h"
#include "libnk2_value_identifier.h"

/* Creates an item
 * Make sure the value item is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_initialize(
     libnk2_item_t **item,
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfvalue_table_t *values_table,
     uint8_t flags,
     libcerror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_initialize";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid item value already set.",
		 function );

		return( -1 );
	}
	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	if( ( flags & ~( LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	internal_item = memory_allocate_structure(
	                 libnk2_internal_item_t );

	if( internal_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_item,
	     0,
	     sizeof( libnk2_internal_item_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear item.",
		 function );

		memory_free(
		 internal_item );

		return( -1 );
	}
	if( ( flags & LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) == 0 )
	{
		internal_item->file_io_handle = file_io_handle;
	}
	else
	{
		if( libbfio_handle_clone(
		     &( internal_item->file_io_handle ),
		     file_io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy file IO handle.",
			 function );

			goto on_error;
		}
		if( libbfio_handle_set_open_on_demand(
		     internal_item->file_io_handle,
		     1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to set open on demand in file IO handle.",
			 function );

			goto on_error;
		}
	}
	internal_item->io_handle    = io_handle;
	internal_item->flags        = flags;
	internal_item->values_table = values_table;

	*item = (libnk2_item_t *) internal_item;

	return( 1 );

on_error:
	if( internal_item != NULL )
	{
		if( ( flags & LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
		{
			if( internal_item->file_io_handle != NULL )
			{
				libbfio_handle_free(
				 &( internal_item->file_io_handle ),
				 NULL );
			}
		}
		memory_free(
		 internal_item );
	}
	return( -1 );
}

/* Frees an item
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_free(
     libnk2_item_t **item,
     libcerror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_free";
	int result                            = 1;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		internal_item = (libnk2_internal_item_t *) *item;
		*item         = NULL;

		/* The io_handle and values_table references are freed elsewhere
		 */
		if( ( internal_item->flags & LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
		{
			if( internal_item->file_io_handle != NULL )
			{
				if( libbfio_handle_close(
				     internal_item->file_io_handle,
				     error ) != 0 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_CLOSE_FAILED,
					 "%s: unable to close file IO handle.",
					 function );

					result = -1;
				}
				if( libbfio_handle_free(
				     &( internal_item->file_io_handle ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free file IO handle.",
					 function );

					result = -1;
				}
			}
		}
		memory_free(
		 internal_item );
	}
	return( result );
}

/* Retrieves the number of entries
 * All sets in an item contain the same number of entries
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_number_of_entries(
     libnk2_item_t *item,
     int *number_of_entries,
     libcerror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_number_of_entries";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( libfvalue_table_get_number_of_values(
	     internal_item->values_table,
	     number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get number of values from values table.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific entry from the item
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_entry_by_index(
     libnk2_item_t *item,
     int entry_index,
     libnk2_record_entry_t **record_entry,
     libcerror_error_t **error )
{
	libfvalue_value_t *value                    = NULL;
	libnk2_internal_item_t *internal_item       = NULL;
	libnk2_value_identifier_t *value_identifier = NULL;
	static char *function                       = "libnk2_item_get_entry_by_index";
	size_t value_identifier_size                = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

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
/* TODO */
	return( 1 );
}


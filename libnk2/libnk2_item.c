/*
 * Item functions
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
#include <memory.h>
#include <types.h>

#include "libnk2_definitions.h"
#include "libnk2_item.h"
#include "libnk2_libcdata.h"
#include "libnk2_libcerror.h"
#include "libnk2_record_entry.h"

/* Creates an item
 * Make sure the value item is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_initialize(
     libnk2_item_t **item,
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
	if( libcdata_array_initialize(
	     &( internal_item->entries_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	*item = (libnk2_item_t *) internal_item;

	return( 1 );

on_error:
	if( internal_item != NULL )
	{
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
	static char *function = "libnk2_item_free";

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
		*item = NULL;
	}
	return( 1 );
}

/* Frees an item
 * Returns 1 if successful or -1 on error
 */
int libnk2_internal_item_free(
     libnk2_internal_item_t **internal_item,
     libcerror_error_t **error )
{
	static char *function = "libnk2_internal_item_free";
	int result            = 1;

	if( internal_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal item.",
		 function );

		return( -1 );
	}
	if( *internal_item != NULL )
	{
		if( libcdata_array_free(
		     &( ( *internal_item )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libnk2_internal_record_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free entries array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_item );

		*internal_item = NULL;
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

	if( libcdata_array_get_number_of_entries(
	     internal_item->entries_array,
	     number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
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
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_by_index";

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
	if( libcdata_array_get_entry_by_index(
	     internal_item->entries_array,
	     entry_index,
	     (intptr_t **) record_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: %d.",
		 function,
		 entry_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the record entry matching the entry and value type pair from the item
 *
 * When the LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE is set
 * the value type is ignored and set. The default behavior is a strict
 * matching of the value type. In this case the value type must be filled
 * with the corresponding value type
 *
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
int libnk2_item_get_entry_by_type(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t value_type,
     libnk2_record_entry_t **record_entry,
     uint8_t flags,
     libcerror_error_t **error )
{
	libnk2_internal_item_t *internal_item                 = NULL;
	libnk2_internal_record_entry_t *internal_record_entry = NULL;
	static char *function                                 = "libnk2_item_get_entry_by_type";
	int entry_index                                       = 0;
	int number_of_entries                                 = 0;
	int result                                            = 0;

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
	if( ( flags & ~( LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_item->entries_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_item->entries_array,
		     entry_index,
		     (intptr_t **) &internal_record_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve record entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( internal_record_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing data record entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		result = 0;

		if( internal_record_entry->entry_type == entry_type )
		{
			result = 1;
		}
		if( result != 0 )
		{
			if( ( ( flags & LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE ) != 0 )
			 || ( internal_record_entry->value_type == value_type ) )
			{
				*record_entry = (libnk2_record_entry_t *) internal_record_entry;

				return( 1 );
			}
		}
	}
	*record_entry = NULL;

	return( 0 );
}

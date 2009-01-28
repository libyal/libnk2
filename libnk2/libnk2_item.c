/*
 * Item functions
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

#include <liberror.h>

#include "libnk2_definitions.h"
#include "libnk2_item.h"
#include "libnk2_list_type.h"
#include "libnk2_notify.h"

/* Initializes the item and its values
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_initialize(
     libnk2_item_t **item,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_initialize";

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item == NULL )
	{
		internal_item = (libnk2_internal_item_t *) memory_allocate(
		                                            sizeof( libnk2_internal_item_t ) );

		if( internal_item == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create internal item.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     internal_item,
		     0,
		     sizeof( libnk2_internal_item_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear internal item.",
			 function );

			memory_free(
			 internal_item );

			return( -1 );
		}
		internal_item->list_element = (libnk2_list_element_t *) memory_allocate(
		                                                         sizeof( libnk2_list_element_t ) );
	
		if( internal_item->list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create list element.",
			 function );

			memory_free(
			 internal_item );

			return( -1 );
		}
		if( memory_set(
		     internal_item->list_element,
		     0,
		     sizeof( libnk2_list_element_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear list element.",
			 function );

			memory_free(
			 internal_item->list_element );
			memory_free(
			 internal_item );

			return( -1 );
		}
		*item = (libnk2_item_t *) internal_item;
	}
	return( 1 );
}

/* Frees an item
 * Detaches the reference from the file if necessary
 * Return 1 if successful or -1 on error
 */
int libnk2_item_free(
     libnk2_item_t **item,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_free";

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		internal_item = (libnk2_internal_item_t *) *item;
		*item         = NULL;

		if( libnk2_item_detach(
		     internal_item,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
			 "%s: unable to detach internal item.",
			 function );

			return( -1 );
		}
		if( internal_item->list_element != NULL )
		{
			memory_free(
			 internal_item->list_element );
		}
		memory_free(
		 internal_item );
	}
	return( 1 );
}

/* Frees an item
 * Return 1 if successful or -1 on error
 */
int libnk2_item_free_no_detach(
     intptr_t *internal_item )
{
	int result = 1;

	if( internal_item != NULL )
	{
		if( ( (libnk2_internal_item_t *) internal_item )->internal_file != NULL )
		{
			memory_free(
			 ( (libnk2_internal_item_t *) internal_item )->list_element );
		}
		/* The list element is expected to be freed elsewhere
		 */
		memory_free(
		 internal_item );
	}
	return( result );
}

/* Attaches the item to the file
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_attach(
     libnk2_internal_item_t *internal_item,
     libnk2_internal_file_t *internal_file,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_attach";

	if( internal_item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal item.",
		 function );

		return( -1 );
	}
	if( internal_item->list_element == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal item - missing list element.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid internal item - already attached to file.",
		 function );

		return( -1 );
	}
	/* Add item to file
	 */
	if( libnk2_list_append_element(
	     internal_file->item_reference_list,
	     internal_item->list_element,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append internal item to file.",
		 function );

		return( -1 );
	}
	internal_item->internal_file = internal_file;

	return( 1 );
}

/* Detaches the item from its file reference
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_detach(
     libnk2_internal_item_t *internal_item,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_detach";

	if( internal_item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal item.",
		 function );

		return( -1 );
	}
	if( internal_item->list_element == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal item - missing list element.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file != NULL )
	{
		/* Remove item from file
		 */
		if( libnk2_list_remove_element(
		     internal_item->internal_file->item_reference_list,
		     internal_item->list_element,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
			 "%s: unable to remove internal item from file.",
			 function );

			return( -1 );
		}
		internal_item->internal_file = NULL;
	}
	return( 1 );
}


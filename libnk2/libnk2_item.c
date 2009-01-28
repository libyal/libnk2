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
#include "libnk2_item_descriptor.h"
#include "libnk2_item_tree.h"
#include "libnk2_item_values.h"
#include "libnk2_list.h"
#include "libnk2_list_type.h"
#include "libnk2_notify.h"
#include "libnk2_string.h"
#include "libnk2_tree_type.h"

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
		internal_item->item_values = (libnk2_item_values_t *) memory_allocate(
		                                                       sizeof( libnk2_item_values_t ) );
	
		if( internal_item->item_values == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create item values.",
			 function );

			memory_free(
			 internal_item->list_element );
			memory_free(
			 internal_item );

			return( -1 );
		}
		if( memory_set(
		     internal_item->item_values,
		     0,
		     sizeof( libnk2_item_values_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear item values.",
			 function );

			memory_free(
			 internal_item->item_values );
			memory_free(
			 internal_item->list_element );
			memory_free(
			 internal_item );

			return( -1 );
		}
		internal_item->type = LIBNK2_ITEM_TYPE_UNDEFINED;

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
		if( ( internal_item->item_values != NULL )
		 && ( libnk2_item_values_free(
		       internal_item->item_values,
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item values.",
			 function );
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
		if( ( ( (libnk2_internal_item_t *) internal_item )->item_values != NULL )
		 && ( libnk2_item_values_free(
		       ( (libnk2_internal_item_t *) internal_item )->item_values,
		       NULL ) != 1 ) )
		{
			result = -1;
		}
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
     libnk2_tree_node_t *item_tree_node,
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
	internal_item->internal_file  = internal_file;
	internal_item->item_tree_node = item_tree_node;

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
		internal_item->internal_file  = NULL;
		internal_item->item_tree_node = NULL;
	}
	return( 1 );
}

/* Retrieves the identifier of a specific entry from the item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_identifier(
     libnk2_item_t *item,
     uint32_t *identifier,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_identifier";

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
	internal_item = (libnk2_internal_item_t *) item;

	if( libnk2_item_tree_get_identifier(
	     internal_item->item_tree_node,
	     identifier,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value(
     libnk2_item_t *item,
     int set_index,
     uint32_t entry_type,
     uint32_t *value_type,
     uint8_t **value_data, 
     size_t *value_data_size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item     = NULL;
	libnk2_item_descriptor_t *item_descriptor = NULL;
	static char *function                     = "libnk2_item_get_entry_value";
	int result                                = 0;

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid item tree node - missing value.",
		 function );

		return( -1 );
	}
	item_descriptor = (libnk2_item_descriptor_t *) internal_item->item_tree_node->value;

	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          item_descriptor->descriptor_identifier,
	          item_descriptor->recovered,
	          internal_item->internal_file->name_to_id_map_list,
	          internal_item->internal_file->io_handle,
	          set_index,
	          entry_type,
	          value_type,
	          value_data, 
	          value_data_size,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );
	}
	return( result );
}

/* Retrieves the boolean value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_boolean(
     libnk2_item_t *item,
     int set_index,
     uint32_t entry_type,
     uint8_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item     = NULL;
	libnk2_item_descriptor_t *item_descriptor = NULL;
	static char *function                     = "libnk2_item_get_entry_value_boolean";
	int result                                = 0;

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid item tree node - missing value.",
		 function );

		return( -1 );
	}
	item_descriptor = (libnk2_item_descriptor_t *) internal_item->item_tree_node->value;

	result = libnk2_item_values_get_entry_value_boolean(
	          internal_item->item_values,
	          item_descriptor->descriptor_identifier,
	          item_descriptor->recovered,
	          internal_item->internal_file->name_to_id_map_list,
	          internal_item->internal_file->io_handle,
	          set_index,
	          entry_type,
	          entry_value,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get entry value boolean.",
		 function );
	}
	return( result );
}

/* Retrieves the 32-bit value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_32bit(
     libnk2_item_t *item,
     int set_index,
     uint32_t entry_type,
     uint32_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item     = NULL;
	libnk2_item_descriptor_t *item_descriptor = NULL;
	static char *function                     = "libnk2_item_get_entry_value_32bit";
	int result                                = 0;

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid item tree node - missing value.",
		 function );

		return( -1 );
	}
	item_descriptor = (libnk2_item_descriptor_t *) internal_item->item_tree_node->value;

	result = libnk2_item_values_get_entry_value_32bit(
	          internal_item->item_values,
	          item_descriptor->descriptor_identifier,
	          item_descriptor->recovered,
	          internal_item->internal_file->name_to_id_map_list,
	          internal_item->internal_file->io_handle,
	          set_index,
	          entry_type,
	          entry_value,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get entry value 32-bit.",
		 function );
	}
	return( result );
}

/* Retrieves the 64-bit value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_64bit(
     libnk2_item_t *item,
     int set_index,
     uint32_t entry_type,
     uint64_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item     = NULL;
	libnk2_item_descriptor_t *item_descriptor = NULL;
	static char *function                     = "libnk2_item_get_entry_value_64bit";
	int result                                = 0;

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid item tree node - missing value.",
		 function );

		return( -1 );
	}
	item_descriptor = (libnk2_item_descriptor_t *) internal_item->item_tree_node->value;

	result = libnk2_item_values_get_entry_value_64bit(
	          internal_item->item_values,
	          item_descriptor->descriptor_identifier,
	          item_descriptor->recovered,
	          internal_item->internal_file->name_to_id_map_list,
	          internal_item->internal_file->io_handle,
	          set_index,
	          entry_type,
	          entry_value,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get entry value 64-bit.",
		 function );
	}
	return( result );
}

/* Retrieves the size value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_size(
     libnk2_item_t *item,
     int set_index,
     uint32_t entry_type,
     size_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item     = NULL;
	libnk2_item_descriptor_t *item_descriptor = NULL;
	static char *function                     = "libnk2_item_get_entry_value_size";
	int result                                = 0;

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid item tree node - missing value.",
		 function );

		return( -1 );
	}
	item_descriptor = (libnk2_item_descriptor_t *) internal_item->item_tree_node->value;

	result = libnk2_item_values_get_entry_value_size(
	          internal_item->item_values,
	          item_descriptor->descriptor_identifier,
	          item_descriptor->recovered,
	          internal_item->internal_file->name_to_id_map_list,
	          internal_item->internal_file->io_handle,
	          set_index,
	          entry_type,
	          entry_value,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get entry value size.",
		 function );
	}
	return( result );
}

/* Retrieves the string size of a specific entry from the referenced item
 * Length includes the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_string_size(
     libnk2_item_t *item,
     int set_index,
     uint32_t entry_type,
     size_t *size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item     = NULL;
	libnk2_item_descriptor_t *item_descriptor = NULL;
	static char *function                     = "libnk2_item_get_entry_value_string_size";
	int result                                = 0;

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid item tree node - missing value.",
		 function );

		return( -1 );
	}
	item_descriptor = (libnk2_item_descriptor_t *) internal_item->item_tree_node->value;

	result = libnk2_item_values_get_entry_value_string_size(
	          internal_item->item_values,
	          item_descriptor->descriptor_identifier,
	          item_descriptor->recovered,
	          internal_item->internal_file->name_to_id_map_list,
	          internal_item->internal_file->io_handle,
	          set_index,
	          entry_type,
	          size,
	          internal_item->internal_file->ascii_codepage,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get entry value string size.",
		 function );
	}
	return( result );
}

/* Retrieves the string value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_string(
     libnk2_item_t *item,
     int set_index,
     uint32_t entry_type,
     uint8_t *string,
     size_t size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item     = NULL;
	libnk2_item_descriptor_t *item_descriptor = NULL;
	static char *function                     = "libnk2_item_get_entry_value_string";
	int result                                = 0;

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( internal_item->item_tree_node->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - invalid item tree node - missing value.",
		 function );

		return( -1 );
	}
	item_descriptor = (libnk2_item_descriptor_t *) internal_item->item_tree_node->value;

	result = libnk2_item_values_get_entry_value_string(
	          internal_item->item_values,
	          item_descriptor->descriptor_identifier,
	          item_descriptor->recovered,
	          internal_item->internal_file->name_to_id_map_list,
	          internal_item->internal_file->io_handle,
	          set_index,
	          entry_type,
	          string,
	          size,
	          internal_item->internal_file->ascii_codepage,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get entry value string.",
		 function );
	}
	return( result );
}

/* Retrieves the type value of the referenced item
 * Determines the item type if neccessary
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_item_type(
     libnk2_item_t *item,
     uint8_t *item_type,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	libnk2_character_t *item_type_string  = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_item_type";
	size_t value_data_size                = 0;
	size_t item_type_string_length        = 0;
	uint32_t value_type                   = 0;
	int result                            = 0;

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( item_type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item type.",
		 function );

		return( -1 );
	}
	if( internal_item->type == LIBNK2_ITEM_TYPE_UNDEFINED )
	{
		result = libnk2_item_get_entry_value(
		          item,
		          0,
		          LIBNK2_ENTRY_TYPE_MESSAGE_TYPE,
		          &value_type,
		          &value_data,
		          &value_data_size,
		          error );

		if( result == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: error while retrieving message class item entry.",
			 function );

			return( -1 );
		}
		else if( result == 0 )
		{
			/* The item does not contain a message type and therefore is a folder
			 */
			internal_item->type = LIBNK2_ITEM_TYPE_FOLDER;
		}
		if( value_data != NULL )
		{
			if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
			{
				item_type_string_length = value_data_size;
			}
			else if( value_type == LIBNK2_VALUE_TYPE_STRING_UNICODE )
			{
				item_type_string_length = ( value_data_size / 2 );
			}
			else
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported string value type.",
				 function );

				return( -1 );
			}
			item_type_string = (libnk2_character_t *) memory_allocate(
			                                           sizeof( libnk2_character_t ) * ( item_type_string_length + 1 ) );

			if( item_type_string == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create item type string.",
				 function );

				return( -1 );
			}
			if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
			{
				if( libnk2_string_copy_from_byte_stream(
				     item_type_string,
				     ( item_type_string_length + 1 ),
				     value_data,
				     value_data_size,
				     internal_item->internal_file->ascii_codepage,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_CONVERSION,
					 LIBERROR_CONVERSION_ERROR_GENERIC,
					 "%s: unable to set item type string.",
					 function );

					memory_free(
					 item_type_string );

					return( -1 );
				}
			}
			else if( value_type == LIBNK2_VALUE_TYPE_STRING_UNICODE )
			{
				if( libnk2_string_copy_from_utf16_stream(
				     item_type_string,
				     ( item_type_string_length + 1 ),
				     value_data,
				     value_data_size,
				     LIBNK2_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_CONVERSION,
					 LIBERROR_CONVERSION_ERROR_GENERIC,
					 "%s: unable to set item type string.",
					 function );

					memory_free(
					 item_type_string );

					return( -1 );
				}
			}
			if( item_type_string_length == 8 )
			{
				if( libnk2_string_compare(
				     item_type_string,
				     _LIBNK2_STRING( "IPM.Note" ),
				     item_type_string_length ) == 0 )
				{
					internal_item->type = LIBNK2_ITEM_TYPE_EMAIL;
				}
				else if( libnk2_string_compare(
					  item_type_string,
					  _LIBNK2_STRING( "IPM.Task" ),
					  item_type_string_length ) == 0 )
				{
					internal_item->type = LIBNK2_ITEM_TYPE_TASK;
				}
			}
			else if( item_type_string_length == 11 )
			{
				if( libnk2_string_compare(
				     item_type_string,
				     _LIBNK2_STRING( "IPM.Contact" ),
				     item_type_string_length ) == 0 )
				{
					internal_item->type = LIBNK2_ITEM_TYPE_CONTACT;
				}
			}
			else if( item_type_string_length == 12 )
			{
				if( libnk2_string_compare(
				     item_type_string,
				     _LIBNK2_STRING( "IPM.Activity" ),
				     item_type_string_length ) == 0 )
				{
					internal_item->type = LIBNK2_ITEM_TYPE_JOURNAL;
				}
			}
			else if( item_type_string_length == 15 )
			{
				if( libnk2_string_compare(
				     item_type_string,
				     _LIBNK2_STRING( "IPM.Appointment" ),
				     item_type_string_length ) == 0 )
				{
					internal_item->type = LIBNK2_ITEM_TYPE_APPOINTMENT;
				}
				else if( libnk2_string_compare(
					  item_type_string,
					  _LIBNK2_STRING( "REPORT.IPM.Note" ),
					  item_type_string_length ) == 0 )
				{
					internal_item->type = LIBNK2_ITEM_TYPE_REPORT;
				}
			}
			else if( item_type_string_length == 19 )
			{
				if( libnk2_string_compare(
				     item_type_string,
				     _LIBNK2_STRING( "REPORT.IPM.Note.NDR" ),
				     item_type_string_length ) == 0 )
				{
					internal_item->type = LIBNK2_ITEM_TYPE_REPORT;
				}
			}
			else if( item_type_string_length == 21 )
			{
				if( libnk2_string_compare(
				     item_type_string,
				     _LIBNK2_STRING( "Report.IPM.Note.IPNRN" ),
				     item_type_string_length ) == 0 )
				{
					internal_item->type = LIBNK2_ITEM_TYPE_REPORT;
				}
			}
			/* IPM.Microsoft.ScheduleData.FreeBusy
			 * IPM.Microsoft.FolderDesign.NamedView
			 * IPM.Microsoft.WunderBar.SFInfo
			 * IPM.Microsoft.WunderBar.Link
			 * IPC.MS.Outlook.AgingProperties
			 * IPM.Schedule.Meeting.Request
			 * IPM.Note.Rules.OofTemplate.Microsoft
			 * IPC
			 * IPM => Message
			 * Report.IPM
			 */
#if defined( HAVE_VERBOSE_OUTPUT )
			if( internal_item->type == LIBNK2_ITEM_TYPE_UNDEFINED )
			{
				libnk2_notify_verbose_printf(
				 "%s: unsupported item type: %" PRIs_LIBNK2 "\n",
				 function,
				 item_type_string );
			}
#endif
			memory_free(
			 item_type_string );
		}
	}
	*item_type = internal_item->type;

	return( 1 );
}

/* Retrieves the amount of sub items from a item
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_amount_of_sub_items(
     libnk2_item_t *item,
     int *amount_of_sub_items,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_amount_of_sub_items";

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( amount_of_sub_items == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid amount of sub items.",
		 function );

		return( -1 );
	}
	*amount_of_sub_items = internal_item->item_tree_node->amount_of_child_nodes;
	
	return( 1 );
}

/* Retrieves the sub item for the specific index from a item
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_sub_item(
     libnk2_item_t *item,
     int sub_item_index,
     libnk2_item_t **sub_item,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item  = NULL;
	libnk2_tree_node_t *sub_item_tree_node = NULL;
	static char *function                  = "libnk2_item_get_sub_item";

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
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item tree node.",
		 function );

		return( -1 );
	}
	if( sub_item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub item.",
		 function );

		return( -1 );
	}
	if( *sub_item != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: sub item already set.",
		 function );

		return( -1 );
	}
	if( libnk2_item_tree_get_child_node(
	     internal_item->item_tree_node,
             sub_item_index,
             &sub_item_tree_node,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub item tree node.",
		 function );

		return( -1 );
	}
	if( sub_item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid sub item tree node.",
		 function );

		return( -1 );
	}
	if( libnk2_item_initialize(
	     sub_item,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize sub item.",
		 function );

		return( -1 );
	}
	if( ( sub_item == NULL )
	 || ( *sub_item == NULL ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid sub item.",
		 function );

		return( -1 );
	}
	if( ( (libnk2_internal_item_t *) *sub_item )->internal_file != internal_item->internal_file )
	{
		if( libnk2_item_detach(
		     (libnk2_internal_item_t *) *sub_item,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
			 "%s: unable to detach sub item.",
			 function );

			libnk2_item_free(
			 sub_item,
			 NULL );

			return( -1 );
		}
	}
	if( libnk2_item_attach(
	     (libnk2_internal_item_t *) *sub_item,
	     internal_item->internal_file,
	     sub_item_tree_node,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to attach sub item.",
		 function );

		libnk2_item_free(
		 sub_item,
		 NULL );

		return( -1 );
	}
	return( 1 );
}


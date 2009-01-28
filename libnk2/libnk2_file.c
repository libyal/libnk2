/*
 * libnk2 file
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
#include <memory.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_definitions.h"
#include "libnk2_io_handle.h"
#include "libnk2_item.h"
#include "libnk2_item_descriptor.h"
#include "libnk2_file.h"
#include "libnk2_folder.h"
#include "libnk2_index.h"
#include "libnk2_item_tree.h"
#include "libnk2_libbfio.h"
#include "libnk2_name_to_id_map.h"
#include "libnk2_notify.h"
#include "libnk2_offset_list.h"

/* Initialize a file
 * Make sure the value file is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_initialize(
     libnk2_file_t **file,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_initialize";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( *file == NULL )
	{
		internal_file = (libnk2_internal_file_t *) memory_allocate(
		                                            sizeof( libnk2_internal_file_t ) );

		if( internal_file == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create file.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     internal_file,
		     0,
		     sizeof( libnk2_internal_file_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file.",
			 function );

			memory_free(
			 internal_file );

			return( -1 );
		}
		internal_file->item_reference_list = (libnk2_list_t *) memory_allocate(
		                                                        sizeof( libnk2_list_t ) );

		if( internal_file->item_reference_list == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create item list.",
			 function );

			memory_free(
			 internal_file );

			return( -1 );
		}
		if( memory_set(
		     internal_file->item_reference_list,
		     0,
		     sizeof( libnk2_list_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear item list.",
			 function );

			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		internal_file->recovered_item_list = (libnk2_list_t *) memory_allocate(
		                                                        sizeof( libnk2_list_t ) );

		if( internal_file->recovered_item_list == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create descriptor recovered item list.",
			 function );

			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		if( memory_set(
		     internal_file->recovered_item_list,
		     0,
		     sizeof( libnk2_list_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear recovered item list.",
			 function );

			memory_free(
			 internal_file->recovered_item_list );
			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		internal_file->unallocated_data_block_list = (libnk2_list_t *) memory_allocate(
		                                                                sizeof( libnk2_list_t ) );

		if( internal_file->unallocated_data_block_list == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create unallocated data block list.",
			 function );

			memory_free(
			 internal_file->recovered_item_list );
			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		if( memory_set(
		     internal_file->unallocated_data_block_list,
		     0,
		     sizeof( libnk2_list_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear unallocated data block list.",
			 function );

			memory_free(
			 internal_file->unallocated_data_block_list );
			memory_free(
			 internal_file->recovered_item_list );
			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		internal_file->unallocated_index_node_block_list = (libnk2_list_t *) memory_allocate(
		                                                                      sizeof( libnk2_list_t ) );

		if( internal_file->unallocated_index_node_block_list == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create unallocated index node block list.",
			 function );

			memory_free(
			 internal_file->unallocated_data_block_list );
			memory_free(
			 internal_file->recovered_item_list );
			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		if( memory_set(
		     internal_file->unallocated_index_node_block_list,
		     0,
		     sizeof( libnk2_list_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear unallocated index node block list.",
			 function );

			memory_free(
			 internal_file->unallocated_index_node_block_list );
			memory_free(
			 internal_file->unallocated_data_block_list );
			memory_free(
			 internal_file->recovered_item_list );
			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		internal_file->name_to_id_map_list = (libnk2_list_t *) memory_allocate(
		                                                        sizeof( libnk2_list_t ) );

		if( internal_file->name_to_id_map_list == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create name to id map list.",
			 function );

			memory_free(
			 internal_file->unallocated_index_node_block_list );
			memory_free(
			 internal_file->unallocated_data_block_list );
			memory_free(
			 internal_file->recovered_item_list );
			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		if( memory_set(
		     internal_file->name_to_id_map_list,
		     0,
		     sizeof( libnk2_list_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear name to id map list.",
			 function );

			memory_free(
			 internal_file->name_to_id_map_list );
			memory_free(
			 internal_file->unallocated_index_node_block_list );
			memory_free(
			 internal_file->unallocated_data_block_list );
			memory_free(
			 internal_file->recovered_item_list );
			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		if( libnk2_io_handle_initialize(
		     &( internal_file->io_handle ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize io handle.",
			 function );

			memory_free(
			 internal_file->name_to_id_map_list );
			memory_free(
			 internal_file->unallocated_index_node_block_list );
			memory_free(
			 internal_file->unallocated_data_block_list );
			memory_free(
			 internal_file->recovered_item_list );
			memory_free(
			 internal_file->item_reference_list );
			memory_free(
			 internal_file );

			return( -1 );
		}
		internal_file->ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1250;

		*file = (libnk2_file_t *) internal_file;
	}
	return( 1 );
}

/* Frees an exisisting file
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_free(
     libnk2_file_t **file,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_free";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( *file != NULL )
	{
		internal_file = (libnk2_internal_file_t *) *file;

		if( libnk2_list_free(
		     internal_file->item_reference_list,
		     &libnk2_item_free_no_detach,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item list.",
			 function );
		}
		if( ( internal_file->item_tree_root_node != NULL )
		 && ( libnk2_tree_node_free(
		       internal_file->item_tree_root_node,
		       &libnk2_item_descriptor_free,
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item tree.",
			 function );
		}
		if( ( internal_file->recovered_item_list != NULL )
		 && ( libnk2_list_free(
		       internal_file->recovered_item_list,
		       &libnk2_item_tree_node_free_recovered,
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free recovered item list.",
			 function );
		}
		if( libnk2_list_free(
		     internal_file->unallocated_data_block_list,
		     &libnk2_offset_list_values_free,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free unallocated data block list.",
			 function );
		}
		if( libnk2_list_free(
		     internal_file->unallocated_index_node_block_list,
		     &libnk2_offset_list_values_free,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free unallocated index node block list.",
			 function );
		}
		if( libnk2_list_free(
		     internal_file->name_to_id_map_list,
		     &libnk2_name_to_id_map_entry_free,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free name to id map list.",
			 function );
		}
		if( ( internal_file->io_handle != NULL )
		 && ( libnk2_io_handle_free(
		       &( internal_file->io_handle ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free io handle.",
			 function );
		}
		memory_free(
		 internal_file );

		*file = NULL;
	}
	return( 1 );
}

/* Opens a Personal Folder File
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_open(
     libnk2_file_t *file,
     const char *filename,
     int flags,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_open";
	int file_io_flags                     = 0;

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBNK2_FLAG_READ ) != LIBNK2_FLAG_READ )
	 && ( ( flags & LIBNK2_FLAG_WRITE ) != LIBNK2_FLAG_WRITE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBNK2_FLAG_WRITE ) == LIBNK2_FLAG_WRITE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access to personal folder files currently not supported.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( ( flags & LIBNK2_FLAG_READ ) == LIBNK2_FLAG_READ )
	{
		file_io_flags = LIBBFIO_FLAG_READ;
	}
	if( libnk2_io_handle_open(
	     internal_file->io_handle,
	     filename,
	     file_io_flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

		return( -1 );
	}
	if( libnk2_file_open_read(
	     internal_file,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file: %s.",
		 function,
		 filename );

		return( -1 );
	}
	return( 1 );
}

#if defined( LIBNK2_WIDE_CHARACTER_TYPE )

/* Opens a Personal Folder File
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_open_wide(
     libnk2_file_t *file,
     const wchar_t *filename,
     int flags,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_open_wide";
	int file_io_flags                     = 0;

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBNK2_FLAG_READ ) != LIBNK2_FLAG_READ )
	 && ( ( flags & LIBNK2_FLAG_WRITE ) != LIBNK2_FLAG_WRITE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBNK2_FLAG_WRITE ) == LIBNK2_FLAG_WRITE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access to personal folder files currently not supported.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( ( flags & LIBNK2_FLAG_READ ) == LIBNK2_FLAG_READ )
	{
		file_io_flags = LIBNK2_FILE_IO_O_RDONLY;
	}
	if( libnk2_io_handle_open_wide(
	     internal_file->io_handle,
	     filename,
	     file_io_flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		return( -1 );
	}
	if( libnk2_file_open_read(
	     internal_file,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file: %ls.",
		 function,
		 filename );

		return( -1 );
	}
	return( 1 );
}

#endif

/* Closes a Personal Folder File
 * Returns 0 if successful or -1 on error
 */
int libnk2_file_close(
     libnk2_file_t *file,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_close";
	int result                            = 0;

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing io handle.",
		 function );

		return( -1 );
	}
	result = libnk2_io_handle_close(
	          internal_file->io_handle,
	          error );

	if( result != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file io handle.",
		 function );
	}
	return( result );
}

/* Opens a Personal Folder File for reading
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_open_read(
     libnk2_internal_file_t *internal_file,
     liberror_error_t **error )
{
	static char *function                     = "libnk2_file_open_read";
	off64_t offset_index_root_node_offset     = 0;
	off64_t descriptor_index_root_node_offset = 0;
	uint64_t offset_index_back_pointer        = 0;
	uint64_t descriptor_index_back_pointer    = 0;

	if( internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal file.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	libnk2_notify_verbose_printf(
	 "Reading file header:\n" );
#endif
	if( libnk2_io_handle_read_file_header(
	     internal_file->io_handle,
	     &offset_index_root_node_offset,
	     &offset_index_back_pointer,
	     &descriptor_index_root_node_offset,
	     &descriptor_index_back_pointer,
	     &( internal_file->content_type ),
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	libnk2_notify_verbose_printf(
	 "Reading offset index:\n" );
#endif
	if( libnk2_io_handle_read_offset_index(
	     internal_file->io_handle,
	     offset_index_root_node_offset,
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
#if defined( HAVE_VERBOSE_OUTPUT )
	libnk2_notify_verbose_printf(
	 "Reading descriptor index:\n" );
#endif
	if( libnk2_io_handle_read_descriptor_index(
	     internal_file->io_handle,
	     descriptor_index_root_node_offset,
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
#if defined( HAVE_VERBOSE_OUTPUT )
	libnk2_notify_verbose_printf(
	 "Creating item tree:\n" );
#endif
	if( libnk2_item_tree_create(
	     internal_file->io_handle,
	     &( internal_file->item_tree_root_node ),
	     &( internal_file->root_folder_item_tree_node ),
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item tree.",
		 function );

		return( -1 );
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	libnk2_notify_verbose_printf(
	 "Name to ID map:\n" );
#endif
	if( libnk2_name_to_id_map_read(
	     internal_file->io_handle,
	     internal_file->name_to_id_map_list,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read name to id map.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the allocation tables
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_read_allocation_tables(
     libnk2_internal_file_t *internal_file,
     liberror_error_t **error )
{
	static char *function = "libnk2_file_read_allocation_tables";

	if( internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal file.",
		 function );

		return( -1 );
	}
	if( internal_file->read_allocation_tables != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid internal file - allocation tables already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	libnk2_notify_verbose_printf(
	 "Reading the unallocated data blocks:\n" );
#endif
	if( libnk2_io_handle_read_unallocated_data_blocks(
	     internal_file->io_handle,
	     internal_file->unallocated_data_block_list,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read unallocated data blocks.",
		 function );

		return( -1 );
	}

#if defined( HAVE_VERBOSE_OUTPUT )
	libnk2_notify_verbose_printf(
	 "Reading the unallocated index node blocks:\n" );
#endif
	if( libnk2_io_handle_read_unallocated_index_node_blocks(
	     internal_file->io_handle,
	     internal_file->unallocated_index_node_block_list,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read unallocated index node blocks.",
		 function );

		return( -1 );
	}
	internal_file->read_allocation_tables = 1;

	return( 1 );
}

/* Recovers deleted items within a Personal Folder File
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_recover_items(
     libnk2_file_t *file,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_recover_items";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( ( internal_file->read_allocation_tables == 0 )
	 && ( libnk2_file_read_allocation_tables(
	       internal_file,
	       error ) != 1 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read allocation tables.",
		 function );

		return( -1 );
	}
	if( libnk2_io_handle_recover_items(
	     internal_file->io_handle,
	     internal_file->unallocated_data_block_list,
	     internal_file->unallocated_index_node_block_list,
	     internal_file->recovered_item_list,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to recover items.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the file size
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_size(
     libnk2_file_t *file,
     size64_t *size,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_size";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing io handle.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = internal_file->io_handle->file_size;

	return( 1 );
}

/* Retrieves the file content type
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_content_type(
     libnk2_file_t *file,
     uint8_t *content_type,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_type";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( content_type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid content type.",
		 function );

		return( -1 );
	}
	*content_type = internal_file->content_type;

	return( 1 );
}

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_type(
     libnk2_file_t *file,
     uint8_t *type,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_type";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing io handle.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = internal_file->io_handle->file_type;

	return( 1 );
}

/* Retrieves the file encryption values
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_encryption_values(
     libnk2_file_t *file,
     uint8_t *encryption_type,
     uint32_t *encryption_key,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_encryption_values";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing io handle.",
		 function );

		return( -1 );
	}
	if( encryption_type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid encryption type.",
		 function );

		return( -1 );
	}
	if( encryption_key == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid encryption key.",
		 function );

		return( -1 );
	}
	*encryption_type = internal_file->io_handle->encryption_type;
	*encryption_key  = internal_file->io_handle->encryption_key;

	return( 1 );
}

/* Retrieves the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_ascii_codepage(
     libnk2_file_t *file,
     int *ascii_codepage,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_ascii_codepage";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( ascii_codepage == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid ASCII codepage.",
		 function );

		return( -1 );
	}
	*ascii_codepage = internal_file->ascii_codepage;

	return( 1 );
}

/* Sets the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_set_ascii_codepage(
     libnk2_file_t *file,
     int ascii_codepage,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_set_ascii_codepage";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( ( ascii_codepage != LIBNK2_CODEPAGE_ASCII )
	 || ( ascii_codepage != LIBNK2_CODEPAGE_WINDOWS_1250 )
	 || ( ascii_codepage != LIBNK2_CODEPAGE_WINDOWS_1251 )
	 || ( ascii_codepage != LIBNK2_CODEPAGE_WINDOWS_1252 )
	 || ( ascii_codepage != LIBNK2_CODEPAGE_WINDOWS_1253 )
	 || ( ascii_codepage != LIBNK2_CODEPAGE_WINDOWS_1254 )
	 || ( ascii_codepage != LIBNK2_CODEPAGE_WINDOWS_1256 )
	 || ( ascii_codepage != LIBNK2_CODEPAGE_WINDOWS_1257 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported ASCII codepage.",
		 function );

		return( -1 );
	}
	internal_file->ascii_codepage = ascii_codepage;

	return( 1 );
}

/* Retrieves the amount of unallocated blocks
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_amount_of_unallocated_blocks(
     libnk2_file_t *file,
     int unallocated_block_type,
     int *amount_of_unallocated_blocks,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	libnk2_list_t *unallocated_block_list = NULL;
	static char *function                 = "libnk2_file_get_amount_of_unallocated_blocks";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( ( unallocated_block_type != LIBNK2_UNALLOCATED_BLOCK_TYPE_DATA )
	 && ( unallocated_block_type != LIBNK2_UNALLOCATED_BLOCK_TYPE_INDEX_NODE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported unallocated block type.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( unallocated_block_type == LIBNK2_UNALLOCATED_BLOCK_TYPE_DATA )
	{
		unallocated_block_list = internal_file->unallocated_data_block_list;
	}
	else if( unallocated_block_type == LIBNK2_UNALLOCATED_BLOCK_TYPE_INDEX_NODE )
	{
		unallocated_block_list = internal_file->unallocated_index_node_block_list;
	}
	if( unallocated_block_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid unallocated block list.",
		 function );

		return( -1 );
	}
	if( ( internal_file->read_allocation_tables == 0 )
	 && ( libnk2_file_read_allocation_tables(
	       internal_file,
	       error ) != 1 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read allocation tables.",
		 function );

		return( -1 );
	}
	if( amount_of_unallocated_blocks == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid amount of unallocated blocks.",
		 function );

		return( -1 );
	}
	*amount_of_unallocated_blocks = unallocated_block_list->amount_of_elements;

	return( 1 );
}

/* Retrieves a specific unallocated block
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_unallocated_block(
     libnk2_file_t *file,
     int unallocated_block_type,
     int unallocated_block_index,
     off64_t *offset,
     size64_t *size,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	libnk2_list_t *unallocated_block_list = NULL;
	static char *function                 = "libnk2_file_get_unallocated_block";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( ( unallocated_block_type != LIBNK2_UNALLOCATED_BLOCK_TYPE_DATA )
	 && ( unallocated_block_type != LIBNK2_UNALLOCATED_BLOCK_TYPE_INDEX_NODE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported unallocated block type.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( unallocated_block_type == LIBNK2_UNALLOCATED_BLOCK_TYPE_DATA )
	{
		unallocated_block_list = internal_file->unallocated_data_block_list;
	}
	else if( unallocated_block_type == LIBNK2_UNALLOCATED_BLOCK_TYPE_INDEX_NODE )
	{
		unallocated_block_list = internal_file->unallocated_index_node_block_list;
	}
	if( unallocated_block_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid unallocated block list.",
		 function );

		return( -1 );
	}
	if( ( internal_file->read_allocation_tables == 0 )
	 && ( libnk2_file_read_allocation_tables(
	       internal_file,
	       error ) != 1 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read allocation tables.",
		 function );

		return( -1 );
	}
	if( libnk2_offset_list_get_offset(
	     unallocated_block_list,
	     unallocated_block_index,
	     offset,
	     size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset list element.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the root item from the Personal Folder File
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_root_item(
     libnk2_file_t *file,
     libnk2_item_t **root_item,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_root_item";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( internal_file->item_tree_root_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing item tree root node.",
		 function );

		return( -1 );
	}
	if( root_item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid root item.",
		 function );

		return( -1 );
	}
	if( libnk2_item_initialize(
	     root_item,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create root item.",
		 function );

		return( -1 );
	}
	if( libnk2_item_attach(
	     (libnk2_internal_item_t *) *root_item,
	     internal_file,
	     internal_file->item_tree_root_node,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to attach root item.",
		 function );

		libnk2_item_free(
		 root_item,
		 NULL );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the message store from the Personal Folder File
 * Returns 1 if successful, 0 if not present or -1 on error
 */
int libnk2_file_get_message_store(
     libnk2_file_t *file,
     libnk2_item_t **message_store,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_message_store";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( message_store == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message store.",
		 function );

		return( -1 );
	}
	if( libnk2_item_initialize(
	     message_store,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create message store.",
		 function );

		return( -1 );
	}
#ifdef TODO
	if( libnk2_item_attach(
	     (libnk2_internal_item_t *) *message_store,
	     internal_file,
	     internal_file->item_tree_root_node,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to attach message store.",
		 function );

		libnk2_item_free(
		 message_store,
		 NULL );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the root folder from the Personal Folder File
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_root_folder(
     libnk2_file_t *file,
     libnk2_item_t **root_folder,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_root_folder";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( internal_file->root_folder_item_tree_node == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing root folder item tree node.",
		 function );

		return( -1 );
	}
	if( root_folder == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid root folder.",
		 function );

		return( -1 );
	}
	if( libnk2_item_initialize(
	     root_folder,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create root folder.",
		 function );

		return( -1 );
	}
	if( libnk2_item_attach(
	     (libnk2_internal_item_t *) *root_folder,
	     internal_file,
	     internal_file->root_folder_item_tree_node,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to attach root folder.",
		 function );

		libnk2_item_free(
		 root_folder,
		 NULL );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the amount of recovered items
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_amount_of_recovered_items(
     libnk2_file_t *file,
     int *amount_of_recovered_items,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	static char *function                 = "libnk2_file_get_amount_of_recovered_items";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( internal_file->recovered_item_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal file - missing recovered item list.",
		 function );

		return( -1 );
	}
	if( amount_of_recovered_items == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid amount of recovered items.",
		 function );

		return( -1 );
	}
	*amount_of_recovered_items = internal_file->recovered_item_list->amount_of_elements;

	return( 1 );
}

/* Retrieves a specific recovered item
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_get_recovered_item(
     libnk2_file_t *file,
     int recovered_item_index,
     libnk2_item_t **recovered_item,
     liberror_error_t **error )
{
	libnk2_internal_file_t *internal_file = NULL;
	libnk2_list_element_t *list_element   = NULL;
	static char *function                 = "libnk2_file_get_recovered_item";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libnk2_internal_file_t *) file;

	if( internal_file->recovered_item_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal file - missing recovered item list.",
		 function );

		return( -1 );
	}
	if( recovered_item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid recovered item.",
		 function );

		return( -1 );
	}
	if( libnk2_item_initialize(
	     recovered_item,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create recovered item.",
		 function );

		return( -1 );
	}
	if( libnk2_list_get_element(
	     internal_file->recovered_item_list,
	     recovered_item_index,
	     &list_element,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve recovered item list element.",
		 function );

		return( -1 );
	}
	if( list_element->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid recovered item list element - missing value.",
		 function );

		return( -1 );
	}
	if( libnk2_item_attach(
	     (libnk2_internal_item_t *) *recovered_item,
	     internal_file,
	     (libnk2_tree_node_t *) list_element->value,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to attach recovered item.",
		 function );

		libnk2_item_free(
		 recovered_item,
		 NULL );

		return( -1 );
	}
	return( 1 );
}


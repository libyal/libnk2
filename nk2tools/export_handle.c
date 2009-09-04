/* 
 * Export handle
 *
 * Copyright (C) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>

/* If libtool DLL support is enabled set LIBNK2_DLL_IMPORT
 * before including libnk2_extern.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBNK2_DLL_EXPORT
#endif

#include <libnk2.h>

#include <libsystem.h>

#include "export_handle.h"
#include "nk2common.h"

/* Initializes the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_initialize(
     export_handle_t **export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_initialize";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle == NULL )
	{
		*export_handle = (export_handle_t *) memory_allocate(
		                                      sizeof( export_handle_t ) );

		if( *export_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create export handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *export_handle,
		     0,
		     sizeof( export_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear export handle.",
			 function );

			memory_free(
			 *export_handle );

			*export_handle = NULL;

			return( -1 );
		}
		if( libnk2_file_initialize(
		     &( ( *export_handle )->input_handle ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize input handle.",
			 function );

			memory_free(
			 *export_handle );

			*export_handle = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees the export handle and its elements
 * Returns 1 if successful or -1 on error
 */
int export_handle_free(
     export_handle_t **export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_free";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		if( ( ( *export_handle )->input_handle != NULL )
		 && ( libnk2_file_free(
		       &( ( *export_handle )->input_handle ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input handle.",
			 function );
		}
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( 1 );
}

/* Opens the input of the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_open_input(
     export_handle_t *export_handle,
     const char *filename,
     liberror_error_t **error )
{
	static char *function = "export_handle_open_input";
	int result            = 1;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle->input_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid export handle - missing input handle.",
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
	if( libnk2_file_open(
	     export_handle->input_handle,
	     filename,
	     LIBNK2_OPEN_READ,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open files.",
		 function );

		return( 1 );
	}
	return( result );
}

/* Closes both the input of the export handle
 * Returns the 0 if succesful or -1 on error
 */
int export_handle_close(
     export_handle_t *export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_close";
	int result            = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle->input_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid export handle - missing input handle.",
		 function );

		return( -1 );
	}
	if( libnk2_file_close(
	     export_handle->input_handle,
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input handle.",
		 function );

		result = -1;
	}
	return( result );
}

/* Sanitizes the filename
 * Return 1 if successful or -1 on error
 */
int export_handle_sanitize_filename(
     uint8_t *filename,
     size_t filename_size,
     liberror_error_t **error )
{
	static char *function = "export_handle_sanitize_filename";
	size_t iterator       = 0;

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
	if( filename_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid filename size value exceeds maximum.",
		 function );

		return( -1 );
	}
	for( iterator = 0; iterator < filename_size; iterator++ )
	{
		if( ( ( filename[ iterator ] >= 0x01 )
		  && ( filename[ iterator ] <= 0x1f ) )
		 || ( filename[ iterator ] == (uint8_t) '\\' )
		 || ( filename[ iterator ] == (uint8_t) '/' ) )
		{
			filename[ iterator ] = (uint8_t) '_';
		}
	}
	return( 1 );
}

/* Creates the full path/filename
 * Returns 1 if successful or -1 on error
 */
int export_handle_create_fullname(
     libsystem_character_t *export_path,
     uint8_t *filename,
     size_t filename_size,
     libsystem_character_t **fullname,
     liberror_error_t **error )
{
	static char *function = "export_handle_create_fullname";
	size_t fullname_size  = 0;

	if( export_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
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
	if( filename_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid filename size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( fullname == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid fullname.",
		 function );

		return( -1 );
	}
	if( *fullname != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid fullname already set.",
		 function );

		return( -1 );
	}
	if( export_handle_sanitize_filename(
	     filename,
	     filename_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable sanitize filename.",
		 function );

		return( -1 );
	}
	fullname_size = libsystem_string_length(
	                   export_path );

	fullname_size += filename_size - 1;

	/* Add space for the separator and the end of string character
	 */
	fullname_size += 2;

	*fullname = (libsystem_character_t *) memory_allocate(
	                                       sizeof( libsystem_character_t ) * fullname_size );

	if( *fullname == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create fullname.",
		 function );

		return( -1 );
	}
	if( libsystem_string_snprintf(
	     *fullname,
	     fullname_size,
	     "%" PRIs_LIBSYSTEM "%c%s",
	     export_path,
	     NK2COMMON_PATH_SEPARATOR,
	     (char *) filename ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set fullname.",
		 function );

		memory_free(
		 *fullname );

		*fullname = NULL;

		return( -1 );
	}
	( *fullname )[ fullname_size - 1 ] = 0;

	return( 1 );
}

/* Exports the item
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item(
     libnk2_item_t *item,
     int item_index,
     int amount_of_items,
     const libsystem_character_t *export_path,
     FILE *log_file_stream,
     liberror_error_t **error )
{
	static char *function = "export_handle_export_item";

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
	if( export_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
	fprintf(
	 stdout,
	 "Exporting item %d out of %d.\n",
	 item_index + 1,
	 amount_of_items );

	/* TODO */

	return( 1 );
}

/* Exports the items
 * Returns the 1 if succesful, 0 if no items are available or -1 on error
 */
int export_handle_export_items(
     export_handle_t *export_handle,
     const libsystem_character_t *export_path,
     FILE *log_file_stream,
     liberror_error_t **error )
{
	libnk2_item_t *item   = NULL;
	static char *function = "export_handle_export_items";
	int amount_of_items   = 0;
	int item_iterator     = 0;
	int result            = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle->input_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid export handle - missing input handle.",
		 function );

		return( -1 );
	}
	if( export_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		return( -1 );
	}
	if( libsystem_directory_make(
	     export_path ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: unable to make directory: %" PRIs_LIBSYSTEM ".\n",
		 function,
		 export_path );

		return( -1 );
	}
	if( libnk2_file_get_amount_of_items(
	     export_handle->input_handle,
	     &amount_of_items,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve amount of items.",
		 function );

		return( -1 );
	}
	if( amount_of_items == 0 )
	{
		return( 0 );
	}
	for( item_iterator = 0;
	     item_iterator < amount_of_items;
	     item_iterator++ )
	{
		if( libnk2_file_get_item(
		     export_handle->input_handle,
		     item_iterator,
		     &item,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve item: %d.",
			 function,
			 item_iterator + 1 );

			return( -1 );
		}
		if( export_handle_export_item(
		     item,
		     item_iterator,
		     amount_of_items,
		     export_path,
		     log_file_stream,
		     error ) != 1 )
		{
			fprintf(
			 stdout,
			 "Unable to export item %d out of %d.\n",
			 item_iterator + 1,
			 amount_of_items );

			libsystem_notify_verbose_printf(
			 "%s: unable to export item: %d.\n",
			 function,
			 item_iterator + 1 );

			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libsystem_notify_print_error_backtrace(
				 *error );
			}
			liberror_error_free(
			 error );

			if( log_file_stream != NULL )
			{
				fprintf(
				 log_file_stream,
				 "Unable to export item: %d.\n",
				 item_iterator + 1 );
			}
		}
		if( libnk2_item_free(
		     &item,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item: %d.",
			 function,
			 item_iterator + 1 );

			return( -1 );
		}
	}
	return( 1 );
}


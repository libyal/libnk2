/*
 * Export handle
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "export_handle.h"
#include "log_handle.h"
#include "nk2input.h"
#include "nk2tools_libcerror.h"
#include "nk2tools_libcfile.h"
#include "nk2tools_libcnotify.h"
#include "nk2tools_libcpath.h"
#include "nk2tools_libnk2.h"

#define EXPORT_HANDLE_NOTIFY_STREAM	stdout

/* Creates an export handle
 * Make sure the value export_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int export_handle_initialize(
     export_handle_t **export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_initialize";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid export handle value already set.",
		 function );

		return( -1 );
	}
	*export_handle = memory_allocate_structure(
	                  export_handle_t );

	if( *export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create export handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *export_handle,
	     0,
	     sizeof( export_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear export handle.",
		 function );

		goto on_error;
	}
	if( libnk2_file_initialize(
	     &( ( *export_handle )->input ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input.",
		 function );

		goto on_error;
	}
	( *export_handle )->dump_item_values         = 1;
	( *export_handle )->print_status_information = 1;
	( *export_handle )->notify_stream            = EXPORT_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *export_handle != NULL )
	{
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( -1 );
}

/* Frees an export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_free(
     export_handle_t **export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_free";
	int result            = 1;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		if( ( *export_handle )->input != NULL )
		{
			if( libnk2_file_free(
			     &( ( *export_handle )->input ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input.",
				 function );

				result = -1;
			}
		}
		if( ( *export_handle )->target_path != NULL )
		{
			memory_free(
			 ( *export_handle )->target_path );
		}
		if( ( *export_handle )->items_export_path != NULL )
		{
			memory_free(
			 ( *export_handle )->items_export_path );
		}
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( result );
}

/* Signals the export handle to abort
 * Returns 1 if successful or -1 on error
 */
int export_handle_signal_abort(
     export_handle_t *export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_signal_abort";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	export_handle->abort = 1;

	if( export_handle->input != NULL )
	{
		if( libnk2_file_signal_abort(
		     export_handle->input,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the ascii codepage
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_ascii_codepage(
     export_handle_t *export_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "export_handle_set_ascii_codepage";
	int result            = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	result = nk2input_determine_ascii_codepage(
	          string,
	          &( export_handle->ascii_codepage ),
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine ASCII codepage.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Sets the target path
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_target_path(
     export_handle_t *export_handle,
     const system_character_t *target_path,
     libcerror_error_t **error )
{
	static char *function                = "export_handle_set_target_path";
	size_t target_path_length            = 0;

#if defined( WINAPI )
	system_character_t *full_target_path = NULL;
        size_t full_target_path_size         = 0;
	int result                           = 0;
#endif

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( target_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		return( -1 );
	}
	if( export_handle->target_path != NULL )
	{
		memory_free(
		 export_handle->target_path );

		export_handle->target_path      = NULL;
		export_handle->target_path_size = 0;
	}
	target_path_length = system_string_length(
	                      target_path );

#if defined( WINAPI )
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcpath_path_get_full_path_wide(
	          target_path,
                  target_path_length,
                  &full_target_path,
                  &full_target_path_size,
                  error );
#else
	result = libcpath_path_get_full_path(
	          target_path,
                  target_path_length,
                  &full_target_path,
                  &full_target_path_size,
                  error );
#endif
        if( result == -1 )
        {
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create extended-length target path.",
		 function );

		goto on_error;
        }
        else if( result != 0 )
        {
                target_path        = full_target_path;
                target_path_length = full_target_path_size - 1;
        }
#endif
	if( target_path_length > 0 )
	{
		export_handle->target_path = system_string_allocate(
		                              target_path_length + 1 );

		if( export_handle->target_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create target path.",
			 function );

			goto on_error;
		}
		if( system_string_copy(
		     export_handle->target_path,
		     target_path,
		     target_path_length ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy target path.",
			 function );

			goto on_error;
		}
		( export_handle->target_path )[ target_path_length ] = 0;

		export_handle->target_path_size = target_path_length + 1;
	}
#if defined( WINAPI )
	memory_free(
	 full_target_path );
#endif
	return( 1 );

on_error:
	if( export_handle->target_path != NULL )
	{
		memory_free(
		 export_handle->target_path );

		export_handle->target_path      = NULL;
		export_handle->target_path_size = 0;
	}
#if defined( WINAPI )
	if( full_target_path != NULL )
	{
		memory_free(
		 full_target_path );
	}
#endif
	return( -1 );
}

/* Sets an export path consisting of a base path and a suffix
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_export_path(
     export_handle_t *export_handle,
     const system_character_t *base_path,
     size_t base_path_length,
     const system_character_t *suffix,
     size_t suffix_length,
     system_character_t **export_path,
     size_t *export_path_size,
     libcerror_error_t **error )
{
	static char *function = "export_handle_set_export_path";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( base_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base path.",
		 function );

		return( -1 );
	}
	if( base_path_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( suffix == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid suffix.",
		 function );

		return( -1 );
	}
	if( suffix_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid suffix length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( export_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
	if( export_path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path size.",
		 function );

		return( -1 );
	}
	if( *export_path != NULL )
	{
		memory_free(
		 *export_path );

		*export_path      = NULL;
		*export_path_size = 0;
	}
	*export_path_size = base_path_length + suffix_length + 1;

	*export_path = system_string_allocate(
	                *export_path_size );

	if( *export_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create export path.",
		 function );

		goto on_error;
	}
	if( system_string_copy(
	     *export_path,
	     base_path,
	     base_path_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy base path to item export path.",
		 function );

		goto on_error;
	}
	if( system_string_copy(
	     &( ( *export_path )[ base_path_length ] ),
	     suffix,
	     suffix_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy suffix to item export path.",
		 function );

		goto on_error;
	}
	( *export_path )[ *export_path_size - 1 ] = 0;

	return( 1 );

on_error:
	if( *export_path != NULL )
	{
		memory_free(
		 *export_path );

		*export_path      = NULL;
		*export_path_size = 0;
	}
	return( -1 );
}

/* Creates the items export path
 * Returns 1 if successful, 0 if already exists or -1 on error
 */
int export_handle_create_items_export_path(
     export_handle_t *export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_create_items_export_path";
	int result            = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle_set_export_path(
	     export_handle,
	     export_handle->target_path,
	     export_handle->target_path_size - 1,
	     _SYSTEM_STRING( ".export" ),
	     7,
	     &( export_handle->items_export_path ),
	     &( export_handle->items_export_path_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set items export path.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_exists_wide(
		  export_handle->items_export_path,
		  error );
#else
	result = libcfile_file_exists(
		  export_handle->items_export_path,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_SYSTEM " exists.",
		 function,
		 export_handle->items_export_path );

		return( -1 );
	}
	else if( result == 1 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Opens the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_open(
     export_handle_t *export_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "export_handle_open";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libnk2_file_open_wide(
	     export_handle->input,
	     filename,
	     LIBNK2_OPEN_READ,
	     error ) != 1 )
#else
	if( libnk2_file_open(
	     export_handle->input,
	     filename,
	     LIBNK2_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the export handle
 * Returns the 0 if succesful or -1 on error
 */
int export_handle_close(
     export_handle_t *export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_close";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libnk2_file_close(
	     export_handle->input,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Creates the default item directory path
 * Returns 1 if successful or -1 on error
 */
int export_handle_create_default_item_directory(
     export_handle_t *export_handle,
     int item_index,
     const system_character_t *item_prefix,
     size_t item_prefix_length,
     const system_character_t *export_path,
     size_t export_path_length,
     system_character_t **item_directory_path,
     size_t *item_directory_path_size,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	system_character_t item_directory_name[ 64 ];

	static char *function             = "export_handle_create_default_item_directory";
	size_t item_directory_name_length = 0;
	int print_count                   = 0;
	int result                        = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( item_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid item index value less than zero.",
		 function );

		return( -1 );
	}
	if( item_prefix == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item prefix.",
		 function );

		return( -1 );
	}
	if( item_prefix_length > (size_t) 63 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid item prefix length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( item_directory_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item directory path.",
		 function );

		return( -1 );
	}
	/* Create the item directory
	 */
	print_count = system_string_sprintf(
	               item_directory_name,
	               64,
	               _SYSTEM_STRING( "%s%05d" ),
	               item_prefix,
	               item_index + 1 );

	if( ( print_count < 0 )
	 || ( (size_t) print_count > ( item_prefix_length + 5 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set item directory name.",
		 function );

		goto on_error;
	}
	item_directory_name[ item_prefix_length + 5 ] = 0;
	item_directory_name_length                    = item_prefix_length + 5;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcpath_path_join_wide(
	          item_directory_path,
	          item_directory_path_size,
	          export_path,
	          export_path_length,
	          item_directory_name,
	          item_directory_name_length,
	          error );
#else
	result = libcpath_path_join(
	          item_directory_path,
	          item_directory_path_size,
	          export_path,
	          export_path_length,
	          item_directory_name,
	          item_directory_name_length,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item directory path.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_exists_wide(
		  *item_directory_path,
		  error );
#else
	result = libcfile_file_exists(
		  *item_directory_path,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_SYSTEM " exists.",
		 function,
		 *item_directory_path );

		goto on_error;
	}
	else if( result != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: %" PRIs_SYSTEM " already exists.",
		 function,
		 *item_directory_path );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libcpath_path_make_directory_wide(
	     *item_directory_path,
	     error ) != 1 )
#else
	if( libcpath_path_make_directory(
	     *item_directory_path,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to make directory: %" PRIs_SYSTEM ".",
		 function,
		 *item_directory_path );

		goto on_error;
	}
	log_handle_printf(
	 log_handle,
	 "Created directory: %" PRIs_SYSTEM ".\n",
	 *item_directory_path );

	return( 1 );

on_error:
	if( *item_directory_path != NULL )
	{
		memory_free(
		 *item_directory_path );

		*item_directory_path      = NULL;
		*item_directory_path_size = 0;
	}
	return( -1 );
}

/* Creates an item file
 * Returns 1 if successful, 0 if the file already exists or -1 on error
 */
int export_handle_create_item_file(
     export_handle_t *export_handle,
     const system_character_t *path,
     size_t path_length,
     const system_character_t *filename,
     size_t filename_length,
     item_file_t **item_file,
     libcerror_error_t **error )
{
	system_character_t *item_file_path = NULL;
	static char *function              = "export_handle_create_item_file";
	size_t item_file_path_size         = 0;
	int result                         = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( item_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item file.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcpath_path_join_wide(
	          &item_file_path,
	          &item_file_path_size,
	          path,
	          path_length,
	          filename,
	          filename_length,
	          error );
#else
	result = libcpath_path_join(
	          &item_file_path,
	          &item_file_path_size,
	          path,
	          path_length,
	          filename,
	          filename_length,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item file path.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_exists_wide(
	          item_file_path,
	          error );
#else
	result = libcfile_file_exists(
	          item_file_path,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_SYSTEM " exists.",
		 function,
		 item_file_path );

		goto on_error;
	}
	else if( result != 0 )
	{
		memory_free(
		 item_file_path );

		return( 0 );
	}
	if( item_file_initialize(
	     item_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item file.",
		 function );

		goto on_error;
	}
	if( item_file_open(
	     *item_file,
	     item_file_path,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open: %" PRIs_SYSTEM ".",
		 function,
		 item_file_path );

		goto on_error;
	}
	memory_free(
	 item_file_path );

	item_file_path = NULL;

	return( 1 );

on_error:
	if( *item_file != NULL )
	{
		item_file_free(
		 item_file,
		 NULL );
	}
	if( item_file_path != NULL )
	{
		memory_free(
		 item_file_path );
	}
	return( -1 );
}

/* Exports the record value
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_record_entry(
     export_handle_t *export_handle,
     item_file_t *item_file,
     int entry_index,
     libnk2_record_entry_t *record_entry,
     libcerror_error_t **error )
{
	uint8_t *value_data    = NULL;
	static char *function  = "export_handle_export_record_entry";
	size_t value_data_size = 0;
	uint32_t entry_type    = 0;
	uint32_t value_type    = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( item_file_write_value_integer_32bit_as_decimal(
	     item_file,
	     _SYSTEM_STRING( "Entry:\t\t\t" ),
	     (uint32_t) entry_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write 32-bit integer value.",
		 function );

		goto on_error;
	}
	if( libnk2_record_entry_get_entry_type(
	     record_entry,
	     &entry_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry type.",
		 function );

		goto on_error;
	}
	if( item_file_write_value_integer_32bit_as_hexadecimal(
	     item_file,
	     _SYSTEM_STRING( "Entry type:\t\t" ),
	     entry_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write 32-bit integer value.",
		 function );

		goto on_error;
	}
	if( libnk2_record_entry_get_value_type(
	     record_entry,
	     &value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value type.",
		 function );

		goto on_error;
	}
	if( item_file_write_value_integer_32bit_as_hexadecimal(
	     item_file,
	     _SYSTEM_STRING( "Value type:\t\t" ),
	     value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write 32-bit integer value.",
		 function );

		goto on_error;
	}
	if( libnk2_record_entry_get_data_size(
	     record_entry,
	     &value_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data size.",
		 function );

		goto on_error;
	}
	if( value_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid value data size value exceeds maximum.",
		 function );

		goto on_error;
	}
	value_data = (uint8_t *) memory_allocate(
	                          sizeof( uint8_t ) * value_data_size );

	if( value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create value data.",
		 function );

		goto on_error;
	}
	if( libnk2_record_entry_get_data(
	     record_entry,
	     value_data,
	     value_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data.",
		 function );

		goto on_error;
	}
	if( item_file_write_value_description(
	     item_file,
	     _SYSTEM_STRING( "Value:" ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write string.",
		 function );

		goto on_error;
	}
	if( item_file_write_buffer_as_hexdump(
	     item_file,
	     value_data,
	     value_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write buffer.",
		 function );

		goto on_error;
	}
	memory_free(
	 value_data );

	value_data = NULL;

	return( 1 );

on_error:
	if( value_data != NULL )
	{
		memory_free(
		 value_data );
	}
	return( -1 );
}

/* Exports the item values
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item_values(
     export_handle_t *export_handle,
     libnk2_item_t *item,
     const system_character_t *item_values_filename,
     size_t item_values_filename_length,
     const system_character_t *export_path,
     size_t export_path_length,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	item_file_t *item_file              = NULL;
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "export_handle_export_item_values";
	int entry_index                     = 0;
	int number_of_entries               = 0;
	int result                          = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
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
	if( item_values_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item value filename.",
		 function );

		return( -1 );
	}
	result = export_handle_create_item_file(
	          export_handle,
	          export_path,
	          export_path_length,
                  item_values_filename,
                  item_values_filename_length,
	          &item_file,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item file.",
		 function );

		return( -1 );
	}
	else if( result == 0 )
	{
		log_handle_printf(
		 log_handle,
		 "Skipping item values file: %" PRIs_SYSTEM " it already exists.\n",
		 item_values_filename );

		return( 1 );
	}
	if( libnk2_item_get_number_of_entries(
	     item,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		goto on_error;
	}
	if( item_file_write_value_integer_32bit_as_decimal(
	     item_file,
	     _SYSTEM_STRING( "Number of entries:\t" ),
	     (uint32_t) number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write 32-bit integer value.",
		 function );

		goto on_error;
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libnk2_item_get_entry_by_index(
		     item,
		     entry_index,
		     &record_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d.",
			 function,
			 entry_index );

			goto on_error;
		}
		if( export_handle_export_record_entry(
		     export_handle,
		     item_file,
		     entry_index,
		     record_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to export entry: %d.",
			 function,
			 entry_index );

			goto on_error;
		}
		if( libnk2_record_entry_free(
		     &record_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free record entry.",
			 function );

			goto on_error;
		}
	}
	if( item_file_close(
	     item_file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close item file.",
		 function );

		goto on_error;
	}
	if( item_file_free(
	     &item_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free item file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( record_entry != NULL )
	{
		libnk2_record_entry_free(
		 &record_entry,
		 NULL );
	}
	if( item_file != NULL )
	{
		item_file_free(
		 &item_file,
		 NULL );
	}
	return( -1 );
}

/* Exports the alias
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_alias(
     export_handle_t *export_handle,
     libnk2_item_t *alias,
     int alias_index,
     const system_character_t *export_path,
     size_t export_path_length,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	system_character_t *alias_path = NULL;
	static char *function          = "export_handle_export_alias";
	size_t alias_path_size         = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( alias == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid alias.",
		 function );

		return( -1 );
	}
	if( export_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export path.",
		 function );

		return( -1 );
	}
	log_handle_printf(
	 log_handle,
	 "Processing alias: %05d in path: %" PRIs_SYSTEM "%c\n",
	 alias_index,
	 export_path,
	 LIBCPATH_SEPARATOR );

	if( export_handle_create_default_item_directory(
	     export_handle,
	     alias_index,
	     _SYSTEM_STRING( "Alias" ),
	     5,
	     export_path,
	     export_path_length,
	     &alias_path,
	     &alias_path_size,
	     log_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable create alias directory.",
		 function );

		goto on_error;
	}
	if( alias_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid alias directory path.",
		 function );

		goto on_error;
	}
	if( export_handle->dump_item_values != 0 )
	{
		if( export_handle_export_item_values(
		     export_handle,
		     alias,
		     _SYSTEM_STRING( "ItemValues.txt" ),
		     14,
		     alias_path,
		     alias_path_size - 1,
		     log_handle,
		     error ) != 1 )
		{
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unable to export item values.\n",
				 function );
			}
			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
			libcerror_error_free(
			 error );

			log_handle_printf(
			 log_handle,
			 "Unable to export alias item values.\n" );
		}
	}
/* TODO Create the alias file */

	memory_free(
	 alias_path );

	return( 1 );

on_error:
	if( alias_path != NULL )
	{
		memory_free(
		 alias_path );
	}
	return( 1 );
}

/* Exports the items
 * Returns the 1 if succesful, 0 if no items are available or -1 on error
 */
int export_handle_export_items(
     export_handle_t *export_handle,
     libnk2_file_t *file,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	libnk2_item_t *item   = NULL;
	static char *function = "export_handle_export_items";
	int number_of_items   = 0;
	int item_index        = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libnk2_file_get_number_of_items(
	     file,
	     &number_of_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of items.",
		 function );

		return( -1 );
	}
	if( number_of_items == 0 )
	{
		return( 0 );
	}
	fprintf(
	 export_handle->notify_stream,
	 "Exporting items.\n" );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libcpath_path_make_directory_wide(
	     export_handle->items_export_path,
	     error ) != 1 )
#else
	if( libcpath_path_make_directory(
	     export_handle->items_export_path,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to make directory: %" PRIs_SYSTEM ".",
		 function,
		 export_handle->items_export_path );

		return( -1 );
	}
	log_handle_printf(
	 log_handle,
	 "Created directory: %" PRIs_SYSTEM ".\n",
	 export_handle->items_export_path );

	for( item_index = 0;
	     item_index < number_of_items;
	     item_index++ )
	{
		if( export_handle->abort != 0 )
		{
			return( -1 );
		}
		if( libnk2_file_get_item(
		     file,
		     item_index,
		     &item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve item: %d.",
			 function,
			 item_index );

			return( -1 );
		}
		if( export_handle->print_status_information != 0 )
		{
			fprintf(
			 export_handle->notify_stream,
			 "Exporting alias item %d out of %d.\n",
			 item_index + 1,
			 number_of_items );
		}
		if( export_handle_export_alias(
		     export_handle,
		     item,
		     item_index,
		     export_handle->items_export_path,
		     export_handle->items_export_path_size - 1,
		     log_handle,
		     error ) != 1 )
		{
			fprintf(
			 export_handle->notify_stream,
			 "Unable to export item %d out of %d.\n",
			 item_index + 1,
			 number_of_items );

			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unable to export item: %d.\n",
				 function,
				 item_index + 1 );
			}
			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
			libcerror_error_free(
			 error );
		}
		if( libnk2_item_free(
		     &item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item: %d.",
			 function,
			 item_index );

			return( -1 );
		}
	}
	return( 1 );
}

/* Exports the items from the file
 * Returns the 1 if succesful, 0 if no items are available or -1 on error
 */
int export_handle_export_file(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_export_file";
	int result            = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	result = export_handle_export_items(
	          export_handle,
	          export_handle->input,
	          log_handle,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GENERIC,
		 "%s: unable to export items.",
		 function );

		return( -1 );
	}
	return( result );
}


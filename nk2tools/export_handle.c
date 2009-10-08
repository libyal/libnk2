/* 
 * Export handle
 *
 * Copyright (C) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

/* If libtool DLL support is enabled set LIBNK2_DLL_IMPORT
 * before including libnk2_extern.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBNK2_DLL_EXPORT
#endif

#include <libnk2.h>

#include <libsystem.h>

#include "export_handle.h"
#include "log_handle.h"
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
			 "%s: unable to create input handle.",
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

/* Opens the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_open(
     export_handle_t *export_handle,
     const libsystem_character_t *filename,
     liberror_error_t **error )
{
	static char *function = "export_handle_open";

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
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )
	if( libnk2_file_open_wide(
	     export_handle->input_handle,
	     filename,
	     LIBNK2_OPEN_READ,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		return( -1 );
	}
#else
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
		 "%s: unable to open file.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Closes the export handle
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

/* Create a directory
 * Return 1 if successful or -1 on error
 */
int export_handle_make_directory(
     libsystem_character_t *directory_name,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_make_directory";

	if( directory_name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory name.",
		 function );

		return( -1 );
	}
	if( libsystem_directory_make(
	     directory_name ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to make directory: %" PRIs_LIBSYSTEM ".",
		 function,
		 directory_name );

		return( -1 );
	}
	log_handle_printf(
	 log_handle,
	 "Created directory: %" PRIs_LIBSYSTEM ".\n",
	 directory_name );

	return( 1 );
}

/* Sanitizes the filename
 * Return 1 if successful or -1 on error
 */
int export_handle_sanitize_filename(
     libsystem_character_t *filename,
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
		 || ( filename[ iterator ] == (libsystem_character_t) '!' )
		 || ( filename[ iterator ] == (libsystem_character_t) '$' )
		 || ( filename[ iterator ] == (libsystem_character_t) '%' )
		 || ( filename[ iterator ] == (libsystem_character_t) '&' )
		 || ( filename[ iterator ] == (libsystem_character_t) '*' )
		 || ( filename[ iterator ] == (libsystem_character_t) '+' )
		 || ( filename[ iterator ] == (libsystem_character_t) '/' )
		 || ( filename[ iterator ] == (libsystem_character_t) ':' )
		 || ( filename[ iterator ] == (libsystem_character_t) ';' )
		 || ( filename[ iterator ] == (libsystem_character_t) '<' )
		 || ( filename[ iterator ] == (libsystem_character_t) '>' )
		 || ( filename[ iterator ] == (libsystem_character_t) '?' )
		 || ( filename[ iterator ] == (libsystem_character_t) '@' )
		 || ( filename[ iterator ] == (libsystem_character_t) '\\' )
		 || ( filename[ iterator ] == (libsystem_character_t) '~' )
		 || ( filename[ iterator ] == 0x7e ) )
		{
			filename[ iterator ] = (libsystem_character_t) '_';
		}
	}
	return( 1 );
}

/* Creates the target path
 * Returns 1 if successful or -1 on error
 */
int export_handle_create_target_path(
     libsystem_character_t *export_path,
     size_t export_path_size,
     uint8_t *utf8_filename,
     size_t utf8_filename_size,
     libsystem_character_t **target_path,
     size_t *target_path_size,
     liberror_error_t **error )
{
	static char *function = "export_handle_create_target_path";
	size_t filename_size  = 0;

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
	if( utf8_filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 filename.",
		 function );

		return( -1 );
	}
	if( utf8_filename_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 filename size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		return( -1 );
	}
	if( *target_path != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid target path already set.",
		 function );

		return( -1 );
	}
	if( target_path_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path size.",
		 function );

		return( -1 );
	}
	/* Make sure to check the UTF-8 filename length
	 * the conversion routines are very strict about the string size
	 */
	utf8_filename_size = 1 + narrow_string_length(
	                          (char *) utf8_filename );

	if( libsystem_string_size_from_utf8_string(
	     utf8_filename,
	     utf8_filename_size,
	     &filename_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine UTF-8 filename size.",
		 function );

		return( -1 );
	}
	/* Include space for the separator and the end of string character
	 */
	*target_path_size = export_path_size + filename_size;

	*target_path = (libsystem_character_t *) memory_allocate(
	                                          sizeof( libsystem_character_t ) * *target_path_size );

	if( *target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create target path.",
		 function );

		*target_path_size = 0;

		return( -1 );
	}
	if( libsystem_string_copy(
	     *target_path,
	     export_path,
	     export_path_size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set export path in target path.",
		 function );

		memory_free(
		 target_path );

		*target_path      = NULL;
		*target_path_size = 0;

		return( -1 );
	}
	( *target_path )[ export_path_size - 1 ] = (libsystem_character_t) NK2COMMON_PATH_SEPARATOR;

	if( libsystem_string_copy_from_utf8_string(
	     &( ( *target_path )[ export_path_size ] ),
	     filename_size,
	     utf8_filename,
	     utf8_filename_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set filename in target path.",
		 function );

		memory_free(
		 target_path );

		*target_path      = NULL;
		*target_path_size = 0;

		return( -1 );
	}
	if( export_handle_sanitize_filename(
	     &( ( *target_path )[ export_path_size ] ),
	     filename_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable sanitize filename in target path.",
		 function );

		memory_free(
		 target_path );

		*target_path      = NULL;
		*target_path_size = 0;

		return( -1 );
	}
	return( 1 );
}

/* Exports the alias
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_alias(
     libnk2_item_t *alias,
     int alias_index,
     int amount_of_aliases,
     libsystem_character_t *export_path,
     size_t export_path_size,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	uint8_t alias_directory[ 11 ];

	libsystem_character_t *alias_path  = NULL;
	static char *function              = "export_handle_export_alias";
	size_t alias_directory_size        = 0;
	size_t alias_path_size             = 0;
	int print_count                    = 0;
	int result                         = 0;

#ifdef TODO
	libsystem_character_t *target_path = NULL;
	FILE *alias_file_stream            = NULL;
	size_t target_path_size            = 0;
#endif

	if( alias == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid alias.",
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
	 "Processing alias %d out of %d.\n",
	 alias_index + 1,
	 amount_of_aliases );

	/* Create the alias directory
	 */
	print_count = narrow_string_snprintf(
	               (char *) alias_directory,
	               11,
	               "Alias%05d",
	               alias_index + 1 );

	if( ( print_count < 0 )
	 || ( print_count > 11 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set alias directory.",
		 function );

		return( -1 );
	}
	alias_directory[ 10 ] = 0;
	alias_directory_size = 11;

	if( export_handle_create_target_path(
	     export_path,
	     export_path_size,
	     alias_directory,
	     alias_directory_size,
	     &alias_path,
	     &alias_path_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable create alias path.",
		 function );

		return( -1 );
	}
	if( alias_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid alias path.",
		 function );

		return( -1 );
	}
fprintf( stderr, "X: %s, %s, %s\n", export_path, alias_directory, alias_path );
	result = libsystem_file_exists(
	          alias_path,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_LIBSYSTEM " exists.",
		 function,
		 alias_path );
	}
	else if( result == 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: %" PRIs_LIBSYSTEM " already exists.",
		 function,
		 alias_path );
	}
	if( result != 0 )
	{
		memory_free(
		 alias_path );

		return( -1 );
	}
	if( export_handle_make_directory(
	     alias_path,
	     log_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to create directory: %" PRIs_LIBSYSTEM "",
		 function,
		 alias_path );

		memory_free(
		 alias_path );

		return( -1 );
	}
	if( export_handle_export_item_values(
	     alias,
	     alias_path,
	     alias_path_size,
	     log_handle,
	     error ) != 1 )
	{
		libsystem_notify_verbose_printf(
		 "%s: unable to export item values.\n",
		 function );

		if( ( error != NULL )
		 && ( *error != NULL ) )
		{
			libsystem_notify_print_error_backtrace(
			 *error );
		}
		liberror_error_free(
		 error );

		log_handle_printf(
		 log_handle,
		 "Unable to export item values.\n" );
	}
#ifdef TODO
	/* Create the alias file
	 */
	if( export_handle_create_target_path(
	     alias_path,
	     alias_path_size,
	     (uint8_t *) "Alias.txt",
	     10,
	     &target_path,
	     &target_path_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create target path.",
		 function );

		memory_free(
		 alias_path );

		return( -1 );
	}
	if( target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		memory_free(
		 alias_path );

		return( -1 );
	}
	result = libsystem_file_exists(
	          target_path,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_LIBSYSTEM " exists.",
		 function,
		 target_path );

		memory_free(
		 target_path );
		memory_free(
		 alias_path );

		return( -1 );
	}
	else if( result == 1 )
	{
		log_handle_printf(
		 log_handle,
		 "Skipping alias it already exists.\n" );

		memory_free(
		 target_path );
		memory_free(
		 alias_path );

		return( 1 );
	}
	alias_file_stream = libsystem_file_stream_open(
	                     target_path,
	                     _LIBSYSTEM_CHARACTER_T_STRING( "w" ) );

	if( alias_file_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open: %" PRIs_LIBSYSTEM ".",
		 function,
		 target_path );

		memory_free(
		 target_path );
		memory_free(
		 alias_path );

		return( -1 );
	}
	memory_free(
	 target_path );

	/* TODO */

	/* Close the alias file
	 */
	if( libsystem_file_stream_close(
	     alias_file_stream ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close alias file.",
		 function );

		memory_free(
		 alias_path );

		return( -1 );
	}
#endif
	memory_free(
	 alias_path );

	return( 1 );
}

/* Exports the item values
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item_values(
     libnk2_item_t *item,
     libsystem_character_t *export_path,
     size_t export_path_size,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	libsystem_character_t *target_path = NULL;
	FILE *item_values_file_stream      = NULL;
	uint8_t *value_data                = NULL;
	static char *function              = "export_handle_export_item_values";
	size_t target_path_size            = 0;
	size_t value_data_size             = 0;
	uint32_t amount_of_entries         = 0;
	uint32_t entry_iterator            = 0;
	uint32_t entry_type                = 0;
	uint32_t value_type                = LIBNK2_VALUE_TYPE_UNSPECIFIED;
	int result                         = 0;

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
	/* Create the item value file
	 */
	if( export_handle_create_target_path(
	     export_path,
	     export_path_size,
	     (uint8_t *) "ItemValues.txt",
	     15,
	     &target_path,
	     &target_path_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create target path.",
		 function );

		return( -1 );
	}
	if( target_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid target path.",
		 function );

		return( -1 );
	}
	result = libsystem_file_exists(
	          target_path,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_GENERIC,
		 "%s: unable to determine if %" PRIs_LIBSYSTEM " exists.",
		 function,
		 target_path );

		memory_free(
		 target_path );

		return( -1 );
	}
	else if( result == 1 )
	{
		memory_free(
		 target_path );

		return( 1 );
	}
	item_values_file_stream = libsystem_file_stream_open(
	                           target_path,
	                           _LIBSYSTEM_CHARACTER_T_STRING( "w" ) );

	if( item_values_file_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open: %" PRIs_LIBSYSTEM ".",
		 function,
		 target_path );

		memory_free(
		 target_path );

		return( -1 );
	}
	memory_free(
	 target_path );

	if( libnk2_item_get_amount_of_entries(
	     item,
	     &amount_of_entries,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve amount of entries.",
		 function );

		libsystem_file_stream_close(
		 item_values_file_stream );

		return( -1 );
	}
	fprintf(
	 item_values_file_stream,
	 "Amount of entries:\t%" PRIu32 "\n",
	 amount_of_entries );
	fprintf(
	 item_values_file_stream,
	 "\n" );

	for( entry_iterator = 0;
	     entry_iterator < amount_of_entries;
	     entry_iterator++ )
	{
		fprintf(
		 item_values_file_stream,
		 "Entry:\t\t\t%" PRIu32 "\n",
		 entry_iterator );

		if( libnk2_item_get_entry_type(
		     item,
		     entry_iterator,
		     &entry_type,
		     &value_type,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry type of entry: %" PRIu32 ".",
			 function,
			 entry_iterator );

			libsystem_file_stream_close(
			 item_values_file_stream );

			return( -1 );
		}
		fprintf(
		 item_values_file_stream,
		 "Entry type:\t\t0x%04" PRIx32 "\n",
		 entry_type );
		fprintf(
		 item_values_file_stream,
		 "Value type:\t\t0x%04" PRIx32 "\n",
		 value_type );

		result = libnk2_item_get_entry_value(
			  item,
			  entry_type,
			  &value_type,
			  &value_data,
			  &value_data_size,
			  0,
			  error );

		if( result == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry value of entry: %" PRIu32 ".",
			 function,
			 entry_iterator );

			libsystem_file_stream_close(
			 item_values_file_stream );

			return( -1 );
		}
		fprintf(
		 item_values_file_stream,
		 "Value:\n" );
		libsystem_notify_fprint_data(
		 item_values_file_stream,
		 value_data,
		 value_data_size );
	}
	if( libsystem_file_stream_close(
	     item_values_file_stream ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close item values file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Exports the file
 * Returns the 1 if succesful, 0 if no items are available or -1 on error
 */
int export_handle_export_file(
     export_handle_t *export_handle,
     libsystem_character_t *export_path,
     size_t export_path_size,
     log_handle_t *log_handle,
     liberror_error_t **error )
{
	libnk2_item_t *item   = NULL;
	static char *function = "export_handle_export_file";
	int amount_of_items   = 0;
	int item_iterator     = 0;

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
		if( export_handle_export_alias(
		     item,
		     item_iterator,
		     amount_of_items,
		     export_path,
		     export_path_size,
		     log_handle,
		     error ) != 1 )
		{
			fprintf(
			 stdout,
			 "Unable to export alias %d out of %d.\n",
			 item_iterator + 1,
			 amount_of_items );

			libsystem_notify_verbose_printf(
			 "%s: unable to export alias: %d.\n",
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


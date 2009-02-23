/*
 * Extracts items from a Nickfile (NK2)
 *
 * Copyright (c) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

/* If libtool DLL support is enabled set LIBNK2_DLL_IMPORT
 * before including libnk2.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBNK2_DLL_IMPORT
#endif

#include <libnk2.h>

#include "export_handle.h"
#include "error_string.h"
#include "filetime.h"
#include "file_io.h"
#include "file_stream_io.h"
#include "notify.h"
#include "nk2common.h"
#include "nk2getopt.h"
#include "nk2input.h"
#include "nk2output.h"
#include "system_string.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use nk2export to export items stored in a Nickfile (NK2).\n\n" );

	fprintf( stream, "Usage: nk2export [ -c codepage ] [ -l logfile ] [ -t target ] [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file\n\n" );

	fprintf( stream, "\t-c:     codepage of ASCII strings, options: ascii, windows-1250 (default),\n"
	                 "\t        windows-1251, windows-1252, windows-1253, windows-1254,\n"
	                 "\t        windows-1255, windows-1256, windows-1257 or windows-1258\n" );
	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-l:     logs information about the exported items\n" );
	fprintf( stream, "\t-t:     specify the target directory to export to\n"
	                 "\t        (default is the source filename followed by .export)\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER_T )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	export_handle_t *export_handle         = NULL;
	liberror_error_t *error                = NULL;
	system_character_t *log_filename       = NULL;
	system_character_t *option_target_path = NULL;
	system_character_t *path_separator     = NULL;
	system_character_t *source             = NULL;
	system_character_t *target_path        = NULL;
	FILE *log_file_stream                  = NULL;
	char *program                          = "nk2export";
	size_t source_length                   = 0;
	size_t target_path_length              = 0;
	system_integer_t option                = 0;
	int ascii_codepage                     = LIBNK2_CODEPAGE_WINDOWS_1250;
	int result                             = 0;
	int verbose                            = 0;

	if( system_string_initialize(
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize system string.\n" );

		notify_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	nk2output_version_fprint(
	 stdout,
	 program );

	while( ( option = nk2getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_CHARACTER_T_STRING( "c:hl:t:vV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf( stderr, "Invalid argument: %s\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'c':
				if( nk2input_determine_ascii_codepage(
				     optarg,
				     &ascii_codepage ) != 1 )
				{
					fprintf( stderr, "Unsupported ASCII codepage defaulting to: windows-1250.\n" );

					ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1250;
				}
				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'l':
				log_filename = optarg;

				break;

			case (system_integer_t) 't':
				option_target_path = optarg;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				nk2output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf( stderr, "Missing source file.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	if( option_target_path != NULL )
	{
		target_path_length = system_string_length(
		                      option_target_path );

		if( target_path_length > 0 )
		{
			target_path = (system_character_t *) memory_allocate(
			                                      sizeof( system_character_t ) * ( target_path_length + 1 ) );

			if( target_path == NULL )
			{
				fprintf( stderr, "Unable to create target path.\n" );

				return( EXIT_FAILURE );
			}
			else if( system_string_copy(
			          target_path,
			          option_target_path,
			          target_path_length ) == NULL )
			{
				fprintf( stderr, "Unable to set target path.\n" );

				memory_free(
				 target_path );

				return( EXIT_FAILURE );
			}
			target_path[ target_path_length ] = 0;
		}
	}
	else
	{
		source_length = system_string_length(
		                 source );

		path_separator = system_string_search_reverse(
		                  source,
		                  (system_character_t) NK2COMMON_PATH_SEPARATOR,
		                  source_length );

		if( path_separator == NULL )
		{
			path_separator = source;
		}
		else
		{
			path_separator++;
		}
		target_path_length = 8 + system_string_length(
		                          path_separator );

		target_path = (system_character_t *) memory_allocate(
		                                      sizeof( system_character_t ) * target_path_length );

		if( target_path == NULL )
		{
			fprintf( stderr, "Unable to create target path.\n" );

			return( EXIT_FAILURE );
		}
		if( system_string_snprintf(
		     target_path,
		     target_path_length,
		     "%" PRIs_SYSTEM ".export",
		     path_separator ) == -1 )
		{
			fprintf( stderr, "Unable to set target path.\n" );

			memory_free(
			 target_path );

			return( EXIT_FAILURE );
		}
	}
	result = system_string_file_exists(
	          target_path );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to determine if %" PRIs_SYSTEM " exists.\n",
		 target_path );
	}
	else if( result == 1 )
	{
		fprintf(
		 stderr,
		 "%" PRIs_SYSTEM " already exists.\n",
		 target_path );
	}
	if( result != 0 )
	{
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	libnk2_set_notify_values(
	 stderr,
	 verbose );
	notify_set_values(
	 stderr,
	 verbose );

	if( export_handle_initialize(
	     &export_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize export handle.\n" );

		notify_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	if( log_filename != NULL )
	{
		log_file_stream = system_string_fopen(
		                   log_filename,
		                   _SYSTEM_CHARACTER_T_STRING( "a" ) );

		if( log_file_stream == NULL )
		{
			fprintf(
			 stderr,
			 "Unable to open log file: %s.\n",
			 log_filename );
		}
	}
	fprintf(
	 stdout,
	 "Opening file.\n" );

	if( export_handle_open_input(
	     export_handle,
	     source,
	     &error ) != 1 )
	{
		nk2output_error_fprint(
		 stderr,
		 "Error opening file: %" PRIs_SYSTEM "",
		 argv[ optind ] );

		notify_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		export_handle_free(
		 &export_handle,
		 NULL );
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	fprintf(
	 stdout,
	 "Exporting items.\n" );

	result = export_handle_export_items(
	          export_handle,
	          target_path,
	          log_file_stream,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to export items.\n" );

		notify_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		export_handle_free(
		 &export_handle,
		 NULL );
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	if( export_handle_close(
	     export_handle,
	     &error ) != 0 )
	{
		nk2output_error_fprint(
		 stderr,
		 "Error closing file: %" PRIs_SYSTEM "",
		 argv[ optind ] );

		notify_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		export_handle_free(
		 &export_handle,
		 NULL );
		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	if( export_handle_free(
	     &export_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free export handle.\n" );

		notify_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		memory_free(
		 target_path );

		return( EXIT_FAILURE );
	}
	memory_free(
	 target_path );

	if( log_file_stream != NULL )
	{
		if( file_stream_io_fclose(
		     log_file_stream ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable to close log file: %s.\n",
			 log_filename );
		}
	}
	if( result == 0 )
	{
		fprintf(
		 stdout,
		 "No items to export.\n" );
	}
	else
	{
		fprintf(
		 stdout,
		 "Export completed.\n" );
	}
	return( EXIT_SUCCESS );
}


/*
 * Shows information obtained from a Personal Folder File (OST or PST)
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

#include "character_string.h"
#include "error_string.h"
#include "notify.h"
#include "nk2getopt.h"
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
	fprintf( stream, "Use nk2info to determine information about a Personal Folder File (OST and PST).\n\n" );

	fprintf( stream, "Usage: nk2info [ -ahvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file\n\n" );

	fprintf( stream, "\t-a:     shows allocation information\n" );
	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Prints file information
 * Returns 1 if successful or -1 on error
 */
int nk2info_file_info_fprint(
     FILE *stream,
     libnk2_file_t *file,
     libnk2_error_t **error )
{
	static char *function     = "nk2info_file_info_fprint";
	size64_t file_size        = 0;
	uint32_t encryption_key   = 0;
	uint8_t file_content_type = 0;
	uint8_t file_type         = 0;
	uint8_t encryption_type   = 0;

	if( stream == NULL )
	{
		fprintf( stderr, "%s: invalid stream.\n",
		 function );

		return( -1 );
	}
	if( file == NULL )
	{
		fprintf( stderr, "%s: invalid file.\n",
		 function );

		return( -1 );
	}
	if( libnk2_file_get_size(
	     file,
	     &file_size,
	     error ) != 1 )
	{
		fprintf( stderr, "%s: unable to retrieve size.\n",
		 function );

		return( -1 );
	}
	if( libnk2_file_get_content_type(
	     file,
	     &file_content_type,
	     error ) != 1 )
	{
		fprintf( stderr, "%s: unable to retrieve file content type.\n",
		 function );

		return( -1 );
	}
	if( libnk2_file_get_type(
	     file,
	     &file_type,
	     error ) != 1 )
	{
		fprintf( stderr, "%s: unable to retrieve file type.\n",
		 function );

		return( -1 );
	}
	if( libnk2_file_get_encryption_values(
	     file,
	     &encryption_type,
	     &encryption_key,
	     error ) != 1 )
	{
		fprintf( stderr, "%s: unable to retrieve encryption values.\n",
		 function );

		return( -1 );
	}
	fprintf( stream, "Personal Folder File information:\n" );

	fprintf( stream, "\tFile size:\t\t%" PRIu64 " bytes\n",
	 file_size );

	fprintf( stream, "\tFile content type:\t" );

	if( file_content_type == LIBNK2_FILE_CONTENT_TYPE_PAB )
	{
		fprintf( stream, "Personal Address Book (PAB)\n" );
	}
	else if( file_content_type == LIBNK2_FILE_CONTENT_TYPE_PST )
	{
		fprintf( stream, "Personal Storage Tables (PST)\n" );
	}
	else if( file_content_type == LIBNK2_FILE_CONTENT_TYPE_OST )
	{
		fprintf( stream, "Offline Storage Tables (OST)\n" );
	}
	else
	{
		fprintf( stream, "unknown: 0x02%" PRIx8 "\n",
		 file_content_type );
	}
	fprintf( stream, "\tFile type:\t\t" );

	if( file_type == LIBNK2_FILE_TYPE_32BIT )
	{
		fprintf( stream, "32-bit\n" );
	}
	else if( file_type == LIBNK2_FILE_TYPE_64BIT )
	{
		fprintf( stream, "64-bit\n" );
	}
	else
	{
		fprintf( stream, "unknown: 0x02%" PRIx8 "\n",
		 file_type );
	}
	fprintf( stream, "\tEncryption type:\t" );

	if( encryption_type == LIBNK2_ENCRYPTION_TYPE_NONE )
	{
		fprintf( stream, "none\n" );
	}
	else if( encryption_type == LIBNK2_ENCRYPTION_TYPE_COMPRESSIBLE )
	{
		fprintf( stream, "compressible\n" );
	}
	else if( encryption_type == LIBNK2_ENCRYPTION_TYPE_HIGH )
	{
		fprintf( stream, "high\n" );
	}
	else
	{
		fprintf( stream, "unknown: 0x02%" PRIx8 "\n",
		 encryption_type );
	}
	fprintf( stream, "\n" );

	return( 1 );
}

/* Prints the file unallocated blocks
 * Returns 1 if successful or -1 on error
 */
int nk2info_file_unallocated_blocks_fprint(
     FILE *stream,
     libnk2_file_t *file,
     liberror_error_t **error )
{
	static char *function            = "nk2info_file_unallocated_blocks_fprint";
	off64_t offset                   = 0;
	size64_t size                    = 0;
	int amount_of_unallocated_blocks = 0;
	int block_iterator               = 0;

	if( stream == NULL )
	{
		fprintf( stderr, "%s: invalid stream.\n",
		 function );

		return( -1 );
	}
	if( file == NULL )
	{
		fprintf( stderr, "%s: invalid file.\n",
		 function );

		return( -1 );
	}
	if( libnk2_file_get_amount_of_unallocated_blocks(
	     file,
	     LIBNK2_UNALLOCATED_BLOCK_TYPE_INDEX_NODE,
	     &amount_of_unallocated_blocks,
	     error ) != 1 )
	{
		fprintf( stderr, "%s: unable to retrieve amount of unallocated blocks.\n",
		 function );

		return( -1 );
	}
	fprintf( stream, "Unallocated index node blocks:\n" );

	for( block_iterator = 0; block_iterator < amount_of_unallocated_blocks; block_iterator++ )
	{
		if( libnk2_file_get_unallocated_block(
		     file,
		     LIBNK2_UNALLOCATED_BLOCK_TYPE_INDEX_NODE,
		     block_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			fprintf( stderr, "%s: unable to retrieve unallocated block: %d.\n",
			 function, ( block_iterator + 1 ) );

			return( -1 );
		}
		fprintf( stream, "\t%08" PRIu64 " (0x%08" PRIx64 ") - %08" PRIu64 " (0x%08" PRIx64 ") size: %" PRIu64 "\n",
		 offset, offset, ( offset + size ), ( offset + size ), size );
	}
	fprintf( stream, "\n" );

	if( libnk2_file_get_amount_of_unallocated_blocks(
	     file,
	     LIBNK2_UNALLOCATED_BLOCK_TYPE_DATA,
	     &amount_of_unallocated_blocks,
	     error ) != 1 )
	{
		fprintf( stderr, "%s: unable to retrieve amount of unallocated blocks.\n",
		 function );

		return( -1 );
	}
	fprintf( stream, "Unallocated data blocks:\n" );

	for( block_iterator = 0; block_iterator < amount_of_unallocated_blocks; block_iterator++ )
	{
		if( libnk2_file_get_unallocated_block(
		     file,
		     LIBNK2_UNALLOCATED_BLOCK_TYPE_DATA,
		     block_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			fprintf( stderr, "%s: unable to retrieve unallocated block: %d.\n",
			 function, ( block_iterator + 1 ) );

			return( -1 );
		}
		fprintf(
		 stream,
		 "\t%08" PRIu64 " (0x%08" PRIx64 ") - %08" PRIu64 " (0x%08" PRIx64 ") size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + size,
		 offset + size,
		 size );
	}
	fprintf( stream, "\n" );

	return( 1 );
}

/* The main program
 */
#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libnk2_error_t *error               = NULL;
	libnk2_file_t *nk2_file             = NULL;
	character_t *program                = _CHARACTER_T_STRING( "nk2info" );
	system_character_t *source          = NULL;
	system_integer_t option             = 0;
	int verbose                         = 0;
	uint8_t show_allocation_information = 0;

	nk2output_version_fprint(
	 stdout,
	 program );

	while( ( option = nk2getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_CHARACTER_T_STRING( "ahvV" ) ) ) != (system_integer_t) -1 )
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

			case (system_integer_t) 'a':
				show_allocation_information = 1;

				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

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

	libnk2_set_notify_values(
	 stderr,
	 verbose );
	notify_set_values(
	 stderr,
	 verbose );

	if( libnk2_file_initialize(
	     &nk2_file,
	     &error ) != 1 )
	{
		fprintf( stderr, "Unable to initialize libnk2 file.\n" );

		return( EXIT_FAILURE );
	}
	if( libnk2_file_open(
	     nk2_file,
	     source,
	     LIBNK2_OPEN_READ,
	     &error ) != 1 )
	{
		nk2output_error_fprint(
		 stderr, "Error opening file: %" PRIs_SYSTEM "",
		 argv[ optind ] );

		notify_error_backtrace(
		 error );
		libnk2_error_free(
		 &error );

		libnk2_file_free(
		 &nk2_file,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( nk2info_file_info_fprint(
	     stdout,
	     nk2_file,
	     &error ) != 1 )
	{
		fprintf( stderr, "Unable to print file information.\n" );

		notify_error_backtrace(
		 error );
		libnk2_error_free(
		 &error );

		libnk2_file_free(
		 &nk2_file,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( ( show_allocation_information != 0 )
	 && ( nk2info_file_unallocated_blocks_fprint(
	       stdout,
	       nk2_file,
	       &error ) != 1 ) )
	{
		fprintf( stderr, "Unable to print file unallocated blocks.\n" );

		notify_error_backtrace(
		 error );
		libnk2_error_free(
		 &error );

		libnk2_file_free(
		 &nk2_file,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( libnk2_file_close(
	     nk2_file,
	     &error ) != 0 )
	{
		nk2output_error_fprint(
		 stderr, "Error closing file: %" PRIs_SYSTEM "",
		 argv[ optind ] );

		notify_error_backtrace(
		 error );
		libnk2_error_free(
		 &error );

		libnk2_file_free(
		 &nk2_file,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( libnk2_file_free(
	     &nk2_file,
	     &error ) != 1 )
	{
		fprintf( stderr, "Unable to free libnk2 file.\n" );

		notify_error_backtrace(
		 error );

		notify_error_backtrace(
		 error );
		libnk2_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}


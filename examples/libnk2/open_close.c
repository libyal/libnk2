/*
 * C application to open and close a Nickfile using libnk2
 *
 * Copyright (c) 2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <stdlib.h>
#include <stdio.h>

#include <libnk2.h>

int main( int argc, char * const argv[] )
{
	libnk2_error_t *error = NULL;
	libnk2_file_t *file   = NULL;

	if( argc != 2 )
	{
		fprintf(
		 stderr,
		 "Usage: ./open_close filename\n" );

		return( EXIT_FAILURE );
	}
	/* The function will return 1 if successful or -1 on error.
	 * On error the error 'object' is created by the library.
	 *
	 * file must refer to NULL to create a new libnk2 file 'object'.
	 *
	 * If error is NULL e.g. libnk2_file_initialize( &file, NULL )
	 * no error 'object' is created
	 *
	 * The error 'object' can be freed by libnk2_error_free()
	 */
	if( libnk2_file_initialize(
	     &file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize file.\n" );

		goto on_error;
	}
	if( libnk2_file_open(
	     file,
	     argv[ 1 ],
	     LIBNK2_OPEN_READ,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open file.\n" );

		goto on_error;
	}
	if( libnk2_file_close(
	     file,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close file.\n" );

		goto on_error;
	}
	if( libnk2_file_free(
	     &file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libnk2_error_backtrace_fprint(
		 error,
		 stderr );
		libnk2_error_free(
		 &error );
	}
	if( file != NULL )
	{
		/* The function will also force a close if necessary
		 */
		libnk2_file_free(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}


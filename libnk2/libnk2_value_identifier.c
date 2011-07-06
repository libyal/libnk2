/*
 * Value identifier functions
 *
 * Copyright (c) 2009-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <libnotify.h>

#include "libnk2_value_identifier.h"

/* Initialize an value identifier
 * Make sure the value value_identifier is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_identifier_initialize(
     libnk2_value_identifier_t **value_identifier,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_identifier_initialize";

	if( value_identifier == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value identifier.",
		 function );

		return( -1 );
	}
	if( *value_identifier == NULL )
	{
		*value_identifier = memory_allocate_structure(
		                     libnk2_value_identifier_t );

		if( *value_identifier == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value identifier.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     *value_identifier,
		     0,
		     sizeof( libnk2_value_identifier_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( *value_identifier != NULL )
	{
		memory_free(
		 *value_identifier );

		*value_identifier = NULL;
	}
	return( -1 );
}

/* Frees a value identifier
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_identifier_free(
     libnk2_value_identifier_t **value_identifier,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_identifier_free";

	if( value_identifier == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value identifier.",
		 function );

		return( -1 );
	}
	if( *value_identifier != NULL )
	{
		memory_free(
		 *value_identifier );

		*value_identifier = NULL;
	}
	return( 1 );
}


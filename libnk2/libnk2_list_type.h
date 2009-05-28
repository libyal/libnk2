/*
 * List type functions
 *
 * Copyright (C) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBNK2_LIST_TYPE_H )
#define _LIBNK2_LIST_TYPE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#if defined( __cplusplus )
extern "C" {
#endif

enum LIBNK2_LIST_COMPARE_DEFINITIONS
{
	LIBNK2_LIST_COMPARE_LESS,
	LIBNK2_LIST_COMPARE_EQUAL,
	LIBNK2_LIST_COMPARE_GREATER
};

typedef struct libnk2_list_element libnk2_list_element_t;

struct libnk2_list_element
{
	/* The previous element
	 */
	libnk2_list_element_t *previous;

	/* The next element
	 */
	libnk2_list_element_t *next;

	/* The list element value
	 */
	intptr_t *value;
};

typedef struct libnk2_list libnk2_list_t;

struct libnk2_list
{
	/* The amount of elements
	 */
	int amount_of_elements;

	/* The first list element
	 */
	libnk2_list_element_t *first;

	/* The last list element
	 */
	libnk2_list_element_t *last;
};

int libnk2_list_initialize(
     libnk2_list_t **list,
     liberror_error_t **error );

int libnk2_list_free(
     libnk2_list_t **list,
     int (*value_free_function)( intptr_t *value, liberror_error_t **error ),
     liberror_error_t **error );

int libnk2_list_empty(
     libnk2_list_t *list,
     int (*value_free_function)( intptr_t *value, liberror_error_t **error ),
     liberror_error_t **error );

int libnk2_list_clone(
     libnk2_list_t **destination,
     libnk2_list_t *source,
     int (*value_clone_function)( intptr_t **destination, intptr_t *source, liberror_error_t **error ),
     liberror_error_t **error );

int libnk2_list_prepend_element(
     libnk2_list_t *list,
     libnk2_list_element_t *element,
     liberror_error_t **error );

int libnk2_list_prepend_value(
     libnk2_list_t *list,
     intptr_t *value,
     liberror_error_t **error );

int libnk2_list_append_element(
     libnk2_list_t *list,
     libnk2_list_element_t *element,
     liberror_error_t **error );

int libnk2_list_append_value(
     libnk2_list_t *list,
     intptr_t *value,
     liberror_error_t **error );

int libnk2_list_insert_element(
     libnk2_list_t *list,
     libnk2_list_element_t *element,
     int (*value_compare_function)( intptr_t *first, intptr_t *second, liberror_error_t **error ),
     liberror_error_t **error );

int libnk2_list_insert_value(
     libnk2_list_t *list,
     intptr_t *value,
     int (*value_compare_function)( intptr_t *first, intptr_t *second, liberror_error_t **error ),
     liberror_error_t **error );

int libnk2_list_remove_element(
     libnk2_list_t *list,
     libnk2_list_element_t *element,
     liberror_error_t **error );

int libnk2_list_get_amount_of_elements(
     libnk2_list_t *list,
     liberror_error_t **error );

int libnk2_list_get_element(
     libnk2_list_t *list,
     int element_index,
     libnk2_list_element_t **element,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif


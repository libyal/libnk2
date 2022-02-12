/*
 * The internal type definitions
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

#if !defined( _LIBNK2_INTERNAL_TYPES_H )
#define _LIBNK2_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBNK2 for local use of libnk2
 * The definitions in <libnk2/types.h> are copied here
 * for local use of libnk2
 */
#if defined( HAVE_LOCAL_LIBNK2 )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libnk2_file {}		libnk2_file_t;
typedef struct libnk2_item {}		libnk2_item_t;
typedef struct libnk2_record_entry {}	libnk2_record_entry_t;

#else
typedef intptr_t libnk2_file_t;
typedef intptr_t libnk2_item_t;
typedef intptr_t libnk2_record_entry_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBNK2 ) */

#endif /* !defined( _LIBNK2_INTERNAL_TYPES_H ) */


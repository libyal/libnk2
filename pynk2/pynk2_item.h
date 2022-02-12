/*
 * Python object wrapper of libnk2_item_t
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

#if !defined( _PYNK2_ITEM_H )
#define _PYNK2_ITEM_H

#include <common.h>
#include <types.h>

#include "pynk2_libnk2.h"
#include "pynk2_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pynk2_item pynk2_item_t;

struct pynk2_item
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libnk2 item
	 */
	libnk2_item_t *item;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pynk2_item_object_methods[];
extern PyTypeObject pynk2_item_type_object;

PyObject *pynk2_item_new(
           libnk2_item_t *item,
           PyObject *parent_object );

int pynk2_item_init(
     pynk2_item_t *pynk2_item );

void pynk2_item_free(
      pynk2_item_t *pynk2_item );

PyObject *pynk2_item_get_number_of_entries(
           pynk2_item_t *pynk2_item,
           PyObject *arguments );

PyObject *pynk2_item_get_entry_by_index(
           PyObject *pynk2_item,
           int entry_index );

PyObject *pynk2_item_get_entry(
           pynk2_item_t *pynk2_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pynk2_item_get_entries(
           pynk2_item_t *pynk2_item,
           PyObject *arguments );

PyObject *pynk2_item_get_entry_by_type(
           pynk2_item_t *pynk2_item,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYNK2_ITEM_H ) */


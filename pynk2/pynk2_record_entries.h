/*
 * Python object definition of the sequence and iterator object of record entries
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

#if !defined( _PYNK2_RECORD_ENTRIES_H )
#define _PYNK2_RECORD_ENTRIES_H

#include <common.h>
#include <types.h>

#include "pynk2_libnk2.h"
#include "pynk2_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pynk2_record_entries pynk2_record_entries_t;

struct pynk2_record_entries
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pynk2_record_entries_type_object;

PyObject *pynk2_record_entries_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pynk2_record_entries_init(
     pynk2_record_entries_t *sequence_object );

void pynk2_record_entries_free(
      pynk2_record_entries_t *sequence_object );

Py_ssize_t pynk2_record_entries_len(
            pynk2_record_entries_t *sequence_object );

PyObject *pynk2_record_entries_getitem(
           pynk2_record_entries_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pynk2_record_entries_iter(
           pynk2_record_entries_t *sequence_object );

PyObject *pynk2_record_entries_iternext(
           pynk2_record_entries_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYNK2_RECORD_ENTRIES_H ) */


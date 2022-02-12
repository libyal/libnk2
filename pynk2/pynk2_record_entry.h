/*
 * Python object wrapper of libnk2_record_entry_t
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

#if !defined( _PYNK2_RECORD_ENTRY_H )
#define _PYNK2_RECORD_ENTRY_H

#include <common.h>
#include <types.h>

#include "pynk2_libnk2.h"
#include "pynk2_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pynk2_record_entry pynk2_record_entry_t;

struct pynk2_record_entry
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libnk2 record entry
	 */
	libnk2_record_entry_t *record_entry;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pynk2_record_entry_object_methods[];
extern PyTypeObject pynk2_record_entry_type_object;

PyObject *pynk2_record_entry_new(
           PyTypeObject *type_object,
           libnk2_record_entry_t *record_entry,
           PyObject *parent_object );

int pynk2_record_entry_init(
     pynk2_record_entry_t *pynk2_record_entry );

void pynk2_record_entry_free(
      pynk2_record_entry_t *pynk2_record_entry );

PyObject *pynk2_record_entry_get_entry_type(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_value_type(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_data(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_data_as_boolean(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_data_as_integer(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_data_as_datetime(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_data_as_size(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_data_as_floating_point(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_data_as_string(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

PyObject *pynk2_record_entry_get_data_as_guid(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYNK2_RECORD_ENTRY_H ) */


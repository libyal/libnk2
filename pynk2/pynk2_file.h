/*
 * Python object wrapper of libnk2_file_t
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

#if !defined( _PYNK2_FILE_H )
#define _PYNK2_FILE_H

#include <common.h>
#include <types.h>

#include "pynk2_libbfio.h"
#include "pynk2_libnk2.h"
#include "pynk2_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pynk2_file pynk2_file_t;

struct pynk2_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libnk2 file
	 */
	libnk2_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pynk2_file_object_methods[];
extern PyTypeObject pynk2_file_type_object;

int pynk2_file_init(
     pynk2_file_t *pynk2_file );

void pynk2_file_free(
      pynk2_file_t *pynk2_file );

PyObject *pynk2_file_signal_abort(
           pynk2_file_t *pynk2_file,
           PyObject *arguments );

PyObject *pynk2_file_open(
           pynk2_file_t *pynk2_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pynk2_file_open_file_object(
           pynk2_file_t *pynk2_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pynk2_file_close(
           pynk2_file_t *pynk2_file,
           PyObject *arguments );

PyObject *pynk2_file_get_ascii_codepage(
           pynk2_file_t *pynk2_file,
           PyObject *arguments );

int pynk2_file_set_ascii_codepage_from_string(
     pynk2_file_t *pynk2_file,
     const char *codepage_string );

PyObject *pynk2_file_set_ascii_codepage(
           pynk2_file_t *pynk2_file,
           PyObject *arguments,
           PyObject *keywords );

int pynk2_file_set_ascii_codepage_setter(
     pynk2_file_t *pynk2_file,
     PyObject *string_object,
     void *closure );

PyObject *pynk2_file_get_modification_time(
           pynk2_file_t *pynk2_file,
           PyObject *arguments );

PyObject *pynk2_file_get_modification_time_as_integer(
           pynk2_file_t *pynk2_file,
           PyObject *arguments );

PyObject *pynk2_file_get_number_of_items(
           pynk2_file_t *pynk2_file,
           PyObject *arguments );

PyObject *pynk2_file_get_item_by_index(
           PyObject *pynk2_file,
           int item_index );

PyObject *pynk2_file_get_item(
           pynk2_file_t *pynk2_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pynk2_file_get_items(
           pynk2_file_t *pynk2_file,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYNK2_FILE_H ) */


/*
 * Python object definition of the libnk2 file
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYNK2_FILE_H )
#define _PYNK2_FILE_H

#include <common.h>
#include <types.h>

#include "pynk2_libcerror.h"
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
};

extern PyMethodDef pynk2_file_object_methods[];
extern PyTypeObject pynk2_file_type_object;

PyObject *pynk2_file_new(
           void );

int pynk2_file_init(
     pynk2_file_t *pynk2_file );

void pynk2_file_free(
      pynk2_file_t *pynk2_file );

#if defined( __cplusplus )
}
#endif

#endif


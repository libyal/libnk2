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

#include <common.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pynk2_error.h"
#include "pynk2_file.h"
#include "pynk2_libcerror.h"
#include "pynk2_libcstring.h"
#include "pynk2_libnk2.h"
#include "pynk2_python.h"
#include "pynk2_unused.h"

PyMethodDef pynk2_file_object_methods[] = {

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pynk2_file_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pynk2_file_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pynk2.file",
	/* tp_basicsize */
	sizeof( pynk2_file_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pynk2_file_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pynk2 file object (wraps libnk2_file_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pynk2_file_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pynk2_file_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pynk2_file_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new pynk2 file object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_new(
           void )
{
	static char *function    = "pynk2_file_new";
	pynk2_file_t *pynk2_file = NULL;

	pynk2_file = PyObject_New(
	              struct pynk2_file,
	              &pynk2_file_type_object );

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	if( pynk2_file_init(
	     pynk2_file ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pynk2_file );

on_error:
	if( pynk2_file != NULL )
	{
		Py_DecRef(
		 (PyObject *) pynk2_file );
	}
	return( NULL );
}

/* Intializes a file object
 * Returns 0 if successful or -1 on error
 */
int pynk2_file_init(
     pynk2_file_t *pynk2_file )
{
	static char *function    = "pynk2_file_init";
	libcerror_error_t *error = NULL;

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	pynk2_file->file = NULL;

	if( libnk2_file_initialize(
	     &( pynk2_file->file ),
	     &error ) != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a file object
 */
void pynk2_file_free(
      pynk2_file_t *pynk2_file )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pynk2_file_free";
	int result                  = 0;

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return;
	}
	if( pynk2_file->file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file - missing libnk2 file.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pynk2_file );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_free(
	          &( pynk2_file->file ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free file.",
		 function );

		libcerror_error_free(
		 &error );
	}
	ob_type->tp_free(
	 (PyObject*) pynk2_file );
}


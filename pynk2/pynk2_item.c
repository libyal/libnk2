/*
 * Python object wrapper of libnk2_item_t
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pynk2_error.h"
#include "pynk2_integer.h"
#include "pynk2_item.h"
#include "pynk2_libcerror.h"
#include "pynk2_libnk2.h"
#include "pynk2_python.h"
#include "pynk2_unused.h"

PyMethodDef pynk2_item_object_methods[] = {

	{ "get_number_of_entries",
	  (PyCFunction) pynk2_item_get_number_of_entries,
	  METH_NOARGS,
	  "get_number_of_entries() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of entries." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pynk2_item_object_get_set_definitions[] = {

	{ "number_of_entries",
	  (getter) pynk2_item_get_number_of_entries,
	  (setter) 0,
	  "The number of entries.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pynk2_item_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pynk2.item",
	/* tp_basicsize */
	sizeof( pynk2_item_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pynk2_item_free,
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
	"pynk2 item object (wraps libnk2_item_t)",
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
	pynk2_item_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pynk2_item_object_get_set_definitions,
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
	(initproc) pynk2_item_init,
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

/* Creates a new item object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_item_new(
           PyTypeObject *type_object,
           libnk2_item_t *item,
           PyObject *parent_object )
{
	pynk2_item_t *pynk2_item = NULL;
	static char *function    = "pynk2_item_new";

	if( item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	pynk2_item = PyObject_New(
	              struct pynk2_item,
	              type_object );

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize item.",
		 function );

		goto on_error;
	}
	if( pynk2_item_init(
	     pynk2_item ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize item.",
		 function );

		goto on_error;
	}
	pynk2_item->item  = item;
	pynk2_item->parent_object = parent_object;

	Py_IncRef(
	 (PyObject *) pynk2_item->parent_object );

	return( (PyObject *) pynk2_item );

on_error:
	if( pynk2_item != NULL )
	{
		Py_DecRef(
		 (PyObject *) pynk2_item );
	}
	return( NULL );
}

/* Intializes a item object
 * Returns 0 if successful or -1 on error
 */
int pynk2_item_init(
     pynk2_item_t *pynk2_item )
{
	static char *function = "pynk2_item_init";

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	/* Make sure libnk2 item is set to NULL
	 */
	pynk2_item->item = NULL;

	return( 0 );
}

/* Frees a item object
 */
void pynk2_item_free(
      pynk2_item_t *pynk2_item )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pynk2_item_free";
	int result                  = 0;

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return;
	}
	if( pynk2_item->item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item - missing libnk2 item.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pynk2_item );

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

	result = libnk2_item_free(
	          &( pynk2_item->item ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libnk2 item.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pynk2_item->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pynk2_item->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pynk2_item );
}

/* Retrieves the number of entries
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_item_get_number_of_entries(
           pynk2_item_t *pynk2_item,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_item_get_number_of_entries";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_item_get_number_of_entries(
	          pynk2_item->item,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of entries.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}


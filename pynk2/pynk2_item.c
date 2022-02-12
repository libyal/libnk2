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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pynk2_error.h"
#include "pynk2_item.h"
#include "pynk2_libcerror.h"
#include "pynk2_libnk2.h"
#include "pynk2_python.h"
#include "pynk2_record_entries.h"
#include "pynk2_record_entry.h"
#include "pynk2_unused.h"

PyMethodDef pynk2_item_object_methods[] = {

	{ "get_number_of_entries",
	  (PyCFunction) pynk2_item_get_number_of_entries,
	  METH_NOARGS,
	  "get_number_of_entries() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of entries." },

	{ "get_entry",
	  (PyCFunction) pynk2_item_get_entry,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_entry(entry_index) -> Object or None\n"
	  "\n"
	  "Retrieves the entry specified by the index." },

	{ "get_entry_by_type",
	  (PyCFunction) pynk2_item_get_entry_by_type,
	  METH_NOARGS,
	  "get_entry_by_type() -> None\n"
	  "\n"
	  "Retrieves the entry." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pynk2_item_object_get_set_definitions[] = {

	{ "number_of_entries",
	  (getter) pynk2_item_get_number_of_entries,
	  (setter) 0,
	  "The number of entries.",
	  NULL },

	{ "entries",
	  (getter) pynk2_item_get_entries,
	  (setter) 0,
	  "The entries.",
	  NULL },

	{ "entry_by_type",
	  (getter) pynk2_item_get_entry_by_type,
	  (setter) 0,
	  "The entry.",
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
           libnk2_item_t *item,
           PyObject *parent_object )
{
	pynk2_item_t *pynk2_item = NULL;
	static char *function    = "pynk2_item_new";

	if( item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pynk2_item = PyObject_New(
	              struct pynk2_item,
	              &pynk2_item_type_object );

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize item.",
		 function );

		goto on_error;
	}
	pynk2_item->item          = item;
	pynk2_item->parent_object = parent_object;

	if( pynk2_item->parent_object != NULL )
	{
		Py_IncRef(
		 (PyObject *) pynk2_item->parent_object );
	}
	return( (PyObject *) pynk2_item );

on_error:
	if( pynk2_item != NULL )
	{
		Py_DecRef(
		 (PyObject *) pynk2_item );
	}
	return( NULL );
}

/* Initializes an item object
 * Returns 0 if successful or -1 on error
 */
int pynk2_item_init(
     pynk2_item_t *pynk2_item )
{
	static char *function = "pynk2_item_init";

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	/* Make sure libnk2 item is set to NULL
	 */
	pynk2_item->item = NULL;

	return( 0 );
}

/* Frees an item object
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
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return;
	}
	if( pynk2_item->item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
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
	int number_of_entries    = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_item_get_number_of_entries(
	          pynk2_item->item,
	          &number_of_entries,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_entries );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_entries );
#endif
	return( integer_object );
}

/* Retrieves the record entry type object
 * Returns a Python type object if successful or NULL on error
 */
PyTypeObject *pynk2_item_get_record_entry_type_object(
               libnk2_record_entry_t *record_entry PYNK2_ATTRIBUTE_UNUSED )
{
	PYNK2_UNREFERENCED_PARAMETER( record_entry )

	return( &pynk2_record_entry_type_object );
}

/* Retrieves a specific entry by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_item_get_entry_by_index(
           PyObject *pynk2_item,
           int entry_index )
{
	PyObject *entry_object       = NULL;
	PyTypeObject *type_object    = NULL;
	libcerror_error_t *error     = NULL;
	libnk2_record_entry_t *entry = NULL;
	static char *function        = "pynk2_item_get_entry_by_index";
	int result                   = 0;

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_item_get_entry_by_index(
	          ( (pynk2_item_t *) pynk2_item )->item,
	          entry_index,
	          &entry,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 entry_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	type_object = pynk2_item_get_record_entry_type_object(
	               entry );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve record entry type object.",
		 function );

		goto on_error;
	}
	entry_object = pynk2_record_entry_new(
	                type_object,
	                entry,
	                (PyObject *) pynk2_item );

	if( entry_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create record entry object.",
		 function );

		goto on_error;
	}
	return( entry_object );

on_error:
	if( entry != NULL )
	{
		libnk2_record_entry_free(
		 &entry,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific entry
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_item_get_entry(
           pynk2_item_t *pynk2_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *entry_object      = NULL;
	static char *keyword_list[] = { "entry_index", NULL };
	int entry_index             = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &entry_index ) == 0 )
	{
		return( NULL );
	}
	entry_object = pynk2_item_get_entry_by_index(
	                (PyObject *) pynk2_item,
	                entry_index );

	return( entry_object );
}

/* Retrieves a sequence and iterator object for the entries
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_item_get_entries(
           pynk2_item_t *pynk2_item,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pynk2_item_get_entries";
	int number_of_entries     = 0;
	int result                = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_item_get_number_of_entries(
	          pynk2_item->item,
	          &number_of_entries,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
	sequence_object = pynk2_record_entries_new(
	                   (PyObject *) pynk2_item,
	                   &pynk2_item_get_entry_by_index,
	                   number_of_entries );

	if( sequence_object == NULL )
	{
		pynk2_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

/* Retrieves a specific entry by type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_item_get_entry_by_type(
           pynk2_item_t *pynk2_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *entry_object       = NULL;
	PyTypeObject *type_object    = NULL;
	libcerror_error_t *error     = NULL;
	libnk2_record_entry_t *entry = NULL;
	static char *function        = "pynk2_item_get_entry_by_type";
	static char *keyword_list[]  = { "entry_type", "value_type", "flags", NULL };
	int entry_type               = 0;
	int flags                    = 0;
	int result                   = 0;
	int value_type               = 0;

	if( pynk2_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "ii|i",
	     keyword_list,
	     &entry_type,
	     &value_type,
	     &flags ) == 0 )
	{
		return( NULL );
	}
	if( ( entry_type < 0 )
	 || ( entry_type > (int) UINT32_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid entry type value out of bounds.",
		 function );

		return( NULL );
	}
	if( ( value_type < 0 )
	 || ( value_type > (int) UINT32_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid value type value out of bounds.",
		 function );

		return( NULL );
	}
	if( ( flags < 0 )
	 || ( flags > (int) UINT8_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid flags value out of bounds.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_item_get_entry_by_type(
	          ( (pynk2_item_t *) pynk2_item )->item,
	          (uint32_t) entry_type,
	          (uint32_t) value_type,
	          &entry,
	          (uint8_t) flags,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve entry with type: 0x%08x 0x%08x.",
		 function,
		 entry_type,
		 value_type );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	type_object = pynk2_item_get_record_entry_type_object(
	               entry );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve record entry type object.",
		 function );

		goto on_error;
	}
	entry_object = pynk2_record_entry_new(
	                type_object,
	                entry,
	                (PyObject *) pynk2_item );

	if( entry_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create record entry object.",
		 function );

		goto on_error;
	}
	return( entry_object );

on_error:
	if( entry != NULL )
	{
		libnk2_record_entry_free(
		 &entry,
		 NULL );
	}
	return( NULL );
}


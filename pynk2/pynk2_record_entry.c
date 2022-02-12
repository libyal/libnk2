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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pynk2_datetime.h"
#include "pynk2_error.h"
#include "pynk2_guid.h"
#include "pynk2_integer.h"
#include "pynk2_libcerror.h"
#include "pynk2_libnk2.h"
#include "pynk2_python.h"
#include "pynk2_record_entry.h"
#include "pynk2_unused.h"

PyMethodDef pynk2_record_entry_object_methods[] = {

	{ "get_entry_type",
	  (PyCFunction) pynk2_record_entry_get_entry_type,
	  METH_NOARGS,
	  "get_entry_type() -> Integer or None\n"
	  "\n"
	  "Retrieves the entry type." },

	{ "get_value_type",
	  (PyCFunction) pynk2_record_entry_get_value_type,
	  METH_NOARGS,
	  "get_value_type() -> Integer or None\n"
	  "\n"
	  "Retrieves the value type." },

	{ "get_data",
	  (PyCFunction) pynk2_record_entry_get_data,
	  METH_NOARGS,
	  "get_data() -> Binary string or None\n"
	  "\n"
	  "Retrieves the data." },

	{ "get_data_as_boolean",
	  (PyCFunction) pynk2_record_entry_get_data_as_boolean,
	  METH_NOARGS,
	  "get_data_as_boolean() -> Integer or None\n"
	  "\n"
	  "Retrieves the data as a boolean." },

	{ "get_data_as_integer",
	  (PyCFunction) pynk2_record_entry_get_data_as_integer,
	  METH_NOARGS,
	  "get_data_as_integer() -> Integer or None\n"
	  "\n"
	  "Retrieves the data as an integer." },

	{ "get_data_as_datetime",
	  (PyCFunction) pynk2_record_entry_get_data_as_datetime,
	  METH_NOARGS,
	  "get_data_as_datetime() -> Datetime or None\n"
	  "\n"
	  "Retrieves the data as a datetime object." },

	{ "get_data_as_size",
	  (PyCFunction) pynk2_record_entry_get_data_as_size,
	  METH_NOARGS,
	  "get_data_as_size() -> Integer or None\n"
	  "\n"
	  "Retrieves the data as size." },

	{ "get_data_as_floating_point",
	  (PyCFunction) pynk2_record_entry_get_data_as_floating_point,
	  METH_NOARGS,
	  "get_data_as_floating_point() -> Float or None\n"
	  "\n"
	  "Retrieves the data as a floating point." },

	{ "get_data_as_string",
	  (PyCFunction) pynk2_record_entry_get_data_as_string,
	  METH_NOARGS,
	  "get_data_as_string() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the data as a string." },

	{ "get_data_as_guid",
	  (PyCFunction) pynk2_record_entry_get_data_as_guid,
	  METH_NOARGS,
	  "get_data_as_guid() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the data as guid." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pynk2_record_entry_object_get_set_definitions[] = {

	{ "entry_type",
	  (getter) pynk2_record_entry_get_entry_type,
	  (setter) 0,
	  "The entry type.",
	  NULL },

	{ "value_type",
	  (getter) pynk2_record_entry_get_value_type,
	  (setter) 0,
	  "The value type.",
	  NULL },

	{ "data",
	  (getter) pynk2_record_entry_get_data,
	  (setter) 0,
	  "The data.",
	  NULL },

	{ "data_as_boolean",
	  (getter) pynk2_record_entry_get_data_as_boolean,
	  (setter) 0,
	  "The data as a boolean.",
	  NULL },

	{ "data_as_integer",
	  (getter) pynk2_record_entry_get_data_as_integer,
	  (setter) 0,
	  "The data as an integer.",
	  NULL },

	{ "data_as_datetime",
	  (getter) pynk2_record_entry_get_data_as_datetime,
	  (setter) 0,
	  "The data as a datetime object.",
	  NULL },

	{ "data_as_size",
	  (getter) pynk2_record_entry_get_data_as_size,
	  (setter) 0,
	  "The data as size.",
	  NULL },

	{ "data_as_floating_point",
	  (getter) pynk2_record_entry_get_data_as_floating_point,
	  (setter) 0,
	  "The data as a floating point.",
	  NULL },

	{ "data_as_string",
	  (getter) pynk2_record_entry_get_data_as_string,
	  (setter) 0,
	  "The data as a string.",
	  NULL },

	{ "data_as_guid",
	  (getter) pynk2_record_entry_get_data_as_guid,
	  (setter) 0,
	  "The data as guid.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pynk2_record_entry_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pynk2.record_entry",
	/* tp_basicsize */
	sizeof( pynk2_record_entry_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pynk2_record_entry_free,
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
	"pynk2 record entry object (wraps libnk2_record_entry_t)",
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
	pynk2_record_entry_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pynk2_record_entry_object_get_set_definitions,
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
	(initproc) pynk2_record_entry_init,
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

/* Creates a new record entry object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_new(
           PyTypeObject *type_object,
           libnk2_record_entry_t *record_entry,
           PyObject *parent_object )
{
	pynk2_record_entry_t *pynk2_record_entry = NULL;
	static char *function                    = "pynk2_record_entry_new";

	if( record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	pynk2_record_entry = PyObject_New(
	                      struct pynk2_record_entry,
	                      type_object );

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize record entry.",
		 function );

		goto on_error;
	}
	if( pynk2_record_entry_init(
	     pynk2_record_entry ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize record entry.",
		 function );

		goto on_error;
	}
	pynk2_record_entry->record_entry  = record_entry;
	pynk2_record_entry->parent_object = parent_object;

	Py_IncRef(
	 (PyObject *) pynk2_record_entry->parent_object );

	return( (PyObject *) pynk2_record_entry );

on_error:
	if( pynk2_record_entry != NULL )
	{
		Py_DecRef(
		 (PyObject *) pynk2_record_entry );
	}
	return( NULL );
}

/* Initializes a record entry object
 * Returns 0 if successful or -1 on error
 */
int pynk2_record_entry_init(
     pynk2_record_entry_t *pynk2_record_entry )
{
	static char *function = "pynk2_record_entry_init";

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	/* Make sure libnk2 record entry is set to NULL
	 */
	pynk2_record_entry->record_entry = NULL;

	return( 0 );
}

/* Frees a record entry object
 */
void pynk2_record_entry_free(
      pynk2_record_entry_t *pynk2_record_entry )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pynk2_record_entry_free";
	int result                  = 0;

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return;
	}
	if( pynk2_record_entry->record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry - missing libnk2 record entry.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pynk2_record_entry );

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

	result = libnk2_record_entry_free(
	          &( pynk2_record_entry->record_entry ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libnk2 record entry.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pynk2_record_entry->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pynk2_record_entry->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pynk2_record_entry );
}

/* Retrieves the entry type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_entry_type(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_record_entry_get_entry_type";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_entry_type(
	          pynk2_record_entry->record_entry,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve entry type.",
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

/* Retrieves the value type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_value_type(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_record_entry_get_value_type";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_value_type(
	          pynk2_record_entry->record_entry,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value type.",
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

/* Retrieves the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_data(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *bytes_object   = NULL;
	libcerror_error_t *error = NULL;
	char *data               = NULL;
	static char *function    = "pynk2_record_entry_get_data";
	size_t data_size         = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_data_size(
	          pynk2_record_entry->record_entry,
	          &data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( data_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	data = (char *) PyMem_Malloc(
	                 sizeof( char ) * data_size );

	if( data == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_data(
	          pynk2_record_entry->record_entry,
	          (uint8_t *) data,
	          data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* This is a binary string so include the full size
	 */
#if PY_MAJOR_VERSION >= 3
	bytes_object = PyBytes_FromStringAndSize(
	                data,
	                (Py_ssize_t) data_size );
#else
	bytes_object = PyString_FromStringAndSize(
	                data,
	                (Py_ssize_t) data_size );
#endif
	if( bytes_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert data into Bytes object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 data );

	return( bytes_object );

on_error:
	if( data != NULL )
	{
		PyMem_Free(
		 data );
	}
	return( NULL );
}

/* Retrieves the data as a boolean value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_data_as_boolean(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_record_entry_get_data_as_boolean";
	uint8_t value_boolean    = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_data_as_boolean(
	          pynk2_record_entry->record_entry,
	          &value_boolean,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve boolean value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( value_boolean != 0x00 )
	{
		Py_IncRef(
		 Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 Py_False );

	return( Py_False );
}

/* Retrieves the data as an integer value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_data_as_integer(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_record_entry_get_data_as_integer";
	uint64_t value_64bit     = 0;
	uint32_t value_32bit     = 0;
	uint32_t value_type      = 0;
	uint16_t value_16bit     = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_value_type(
	          pynk2_record_entry->record_entry,
	          &value_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( value_type )
	{
		case LIBNK2_VALUE_TYPE_INTEGER_16BIT_SIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libnk2_record_entry_get_data_as_16bit_integer(
			          pynk2_record_entry->record_entry,
			          &value_16bit,
			          &error );

			Py_END_ALLOW_THREADS

#if PY_MAJOR_VERSION >= 3
			integer_object = PyLong_FromLong(
			                  (long) ( (int16_t) value_16bit ) );
#else
			integer_object = PyInt_FromLong(
			                  (long) ( (int16_t) value_16bit ) );
#endif
			break;

		case LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libnk2_record_entry_get_data_as_32bit_integer(
			          pynk2_record_entry->record_entry,
			          &value_32bit,
			          &error );

			Py_END_ALLOW_THREADS

#if PY_MAJOR_VERSION >= 3
			integer_object = PyLong_FromLong(
			                  (long) ( (int32_t) value_32bit ) );
#else
			integer_object = PyInt_FromLong(
			                  (long) ( (int32_t) value_32bit ) );
#endif
			break;

		case LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libnk2_record_entry_get_data_as_64bit_integer(
			          pynk2_record_entry->record_entry,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_object = pynk2_integer_signed_new_from_64bit(
			                  (int64_t) value_64bit );

			break;

		case LIBNK2_VALUE_TYPE_FILETIME:
			Py_BEGIN_ALLOW_THREADS

			result = libnk2_record_entry_get_data_as_filetime(
			          pynk2_record_entry->record_entry,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_object = pynk2_integer_unsigned_new_from_64bit(
			                  value_64bit );
			break;

		case LIBNK2_VALUE_TYPE_FLOATINGTIME:
			Py_BEGIN_ALLOW_THREADS

			result = libnk2_record_entry_get_data_as_floatingtime(
			          pynk2_record_entry->record_entry,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_object = pynk2_integer_unsigned_new_from_64bit(
			                  value_64bit );
			break;

		default:
			PyErr_Format(
			 PyExc_IOError,
			 "%s: value is not an integer type.",
			 function );

			return( NULL );
	}
	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve integer value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( integer_object );
}

/* Retrieves the data as an datetime value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_data_as_datetime(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *datetime_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pynk2_record_entry_get_data_as_datetime";
	uint64_t value_64bit      = 0;
	uint32_t value_type       = 0;
	int result                = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_value_type(
	          pynk2_record_entry->record_entry,
	          &value_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( value_type )
	{
		case LIBNK2_VALUE_TYPE_FILETIME:
			Py_BEGIN_ALLOW_THREADS

			result = libnk2_record_entry_get_data_as_filetime(
			          pynk2_record_entry->record_entry,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			datetime_object = pynk2_datetime_new_from_filetime(
			                   value_64bit );
			break;

		case LIBNK2_VALUE_TYPE_FLOATINGTIME:
			Py_BEGIN_ALLOW_THREADS

			result = libnk2_record_entry_get_data_as_floatingtime(
			          pynk2_record_entry->record_entry,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			datetime_object = pynk2_datetime_new_from_floatingtime(
			                   value_64bit );
			break;

		default:
			PyErr_Format(
			 PyExc_IOError,
			 "%s: value is not an datetime type.",
			 function );

			return( NULL );
	}
	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve datetime value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( datetime_object );
}

/* Retrieves the data as size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_data_as_size(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_record_entry_get_data_as_size";
	size64_t data_as_size    = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_data_as_size(
	          pynk2_record_entry->record_entry,
	          &data_as_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve data as size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pynk2_integer_unsigned_new_from_64bit(
	                  (uint64_t) data_as_size );

	return( integer_object );
}

/* Retrieves the data as floating point
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_data_as_floating_point(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *float_object   = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_record_entry_get_data_as_floating_point";
	double value_double      = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_data_as_floating_point(
	          pynk2_record_entry->record_entry,
	          &value_double,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data as floating point.",
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
	float_object = PyFloat_FromDouble(
	                value_double );

	return( float_object );
}

/* Retrieves the data as a string
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_data_as_string(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pynk2_value_get_data_as_string";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_data_as_utf8_string_size(
	          pynk2_record_entry->record_entry,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of data as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_data_as_utf8_string(
	          pynk2_record_entry->record_entry,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

/* Retrieves the data as guid
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_record_entry_get_data_as_guid(
           pynk2_record_entry_t *pynk2_record_entry,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_record_entry_get_data_as_guid";
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_record_entry == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record entry.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_record_entry_get_data_as_guid(
	          pynk2_record_entry->record_entry,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data as guid.",
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
	string_object = pynk2_string_new_from_guid(
	                 guid_data,
	                 16 );

	return( string_object );
}


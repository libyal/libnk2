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

#include <common.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pynk2_codepage.h"
#include "pynk2_datetime.h"
#include "pynk2_error.h"
#include "pynk2_file.h"
#include "pynk2_file_object_io_handle.h"
#include "pynk2_integer.h"
#include "pynk2_item.h"
#include "pynk2_items.h"
#include "pynk2_libbfio.h"
#include "pynk2_libcerror.h"
#include "pynk2_libclocale.h"
#include "pynk2_libnk2.h"
#include "pynk2_python.h"
#include "pynk2_unused.h"

#if !defined( LIBNK2_HAVE_BFIO )

LIBNK2_EXTERN \
int libnk2_file_open_file_io_handle(
     libnk2_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libnk2_error_t **error );

#endif /* !defined( LIBNK2_HAVE_BFIO ) */

PyMethodDef pynk2_file_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pynk2_file_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the file to abort the current activity." },

	{ "open",
	  (PyCFunction) pynk2_file_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pynk2_file_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a file using a file-like object." },

	{ "close",
	  (PyCFunction) pynk2_file_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a file." },

	{ "get_ascii_codepage",
	  (PyCFunction) pynk2_file_get_ascii_codepage,
	  METH_NOARGS,
	  "get_ascii_codepage() -> String\n"
	  "\n"
	  "Retrieves the codepage for ASCII strings used in the file." },

	{ "set_ascii_codepage",
	  (PyCFunction) pynk2_file_set_ascii_codepage,
	  METH_VARARGS | METH_KEYWORDS,
	  "set_ascii_codepage(codepage) -> None\n"
	  "\n"
	  "Sets the codepage for ASCII strings used in the file.\n"
	  "Expects the codepage to be a string containing a Python codec definition." },

	{ "get_modification_time",
	  (PyCFunction) pynk2_file_get_modification_time,
	  METH_NOARGS,
	  "get_modification_time() -> Datetime or None\n"
	  "\n"
	  "Retrieves the modification time." },

	{ "get_modification_time_as_integer",
	  (PyCFunction) pynk2_file_get_modification_time_as_integer,
	  METH_NOARGS,
	  "get_modification_time_as_integer() -> Integer or None\n"
	  "\n"
	  "Retrieves the modification time as a 64-bit integer containing a FILETIME value." },

	{ "get_number_of_items",
	  (PyCFunction) pynk2_file_get_number_of_items,
	  METH_NOARGS,
	  "get_number_of_items() -> Integer\n"
	  "\n"
	  "Retrieves the number of items." },

	{ "get_item",
	  (PyCFunction) pynk2_file_get_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_item(item_index) -> Object\n"
	  "\n"
	  "Retrieves the item specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pynk2_file_object_get_set_definitions[] = {

	{ "ascii_codepage",
	  (getter) pynk2_file_get_ascii_codepage,
	  (setter) pynk2_file_set_ascii_codepage_setter,
	  "The codepage used for ASCII strings in the file.",
	  NULL },

	{ "modification_time",
	  (getter) pynk2_file_get_modification_time,
	  (setter) 0,
	  "The modification time.",
	  NULL },

	{ "number_of_items",
	  (getter) pynk2_file_get_number_of_items,
	  (setter) 0,
	  "The number of items.",
	  NULL },

	{ "items",
	  (getter) pynk2_file_get_items,
	  (setter) 0,
	  "The items.",
	  NULL },

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

/* Initializes a file object
 * Returns 0 if successful or -1 on error
 */
int pynk2_file_init(
     pynk2_file_t *pynk2_file )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_file_init";

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	/* Make sure libnk2 file is set to NULL
	 */
	pynk2_file->file           = NULL;
	pynk2_file->file_io_handle = NULL;

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
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pynk2_file_free";
	int result                  = 0;

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
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
	if( pynk2_file->file_io_handle != NULL )
	{
		if( pynk2_file_close(
		     pynk2_file,
		     NULL ) == NULL )
		{
			return;
		}
	}
	if( pynk2_file->file != NULL )
	{
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
			 "%s: unable to free libnk2 file.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pynk2_file );
}

/* Signals the file to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_signal_abort(
           pynk2_file_t *pynk2_file,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_file_signal_abort";
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_signal_abort(
	          pynk2_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_open(
           pynk2_file_t *pynk2_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	const char *filename_narrow  = NULL;
	static char *function        = "pynk2_file_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pynk2_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libnk2_file_open_wide(
		          pynk2_file->file,
		          filename_wide,
		          LIBNK2_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pynk2_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libnk2_file_open(
		          pynk2_file->file,
		          filename_narrow,
		          LIBNK2_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pynk2_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pynk2_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libnk2_file_open(
		          pynk2_file->file,
		          filename_narrow,
		          LIBNK2_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pynk2_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a file using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_open_file_object(
           pynk2_file_t *pynk2_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pynk2_file_open_file_object";
	static char *keyword_list[] = { "file_object", "mode", NULL };
	char *mode                  = NULL;
	int result                  = 0;

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "read" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing read attribute.",
		 function );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "seek" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing seek attribute.",
		 function );

		return( NULL );
	}
	if( pynk2_file->file_io_handle != NULL )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid file - file IO handle already set.",
		 function );

		goto on_error;
	}
	if( pynk2_file_object_initialize(
	     &( pynk2_file->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_open_file_io_handle(
	          pynk2_file->file,
	          pynk2_file->file_io_handle,
	          LIBNK2_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open file.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pynk2_file->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pynk2_file->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_close(
           pynk2_file_t *pynk2_file,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_file_close";
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_close(
	          pynk2_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close file.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pynk2_file->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pynk2_file->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pynk2_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_get_ascii_codepage(
           pynk2_file_t *pynk2_file,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	const char *codepage_string = NULL;
	static char *function       = "pynk2_file_get_ascii_codepage";
	int ascii_codepage          = 0;
	int result                  = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_get_ascii_codepage(
	          pynk2_file->file,
	          &ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	codepage_string = pynk2_codepage_to_string(
	                   ascii_codepage );

	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported ASCII codepage: %d.",
		 function,
		 ascii_codepage );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromString(
	                 codepage_string );
#else
	string_object = PyString_FromString(
	                 codepage_string );
#endif
	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert codepage string into string object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns 1 if successful or -1 on error
 */
int pynk2_file_set_ascii_codepage_from_string(
     pynk2_file_t *pynk2_file,
     const char *codepage_string )
{
	libcerror_error_t *error      = NULL;
	static char *function         = "pynk2_file_set_ascii_codepage_from_string";
	size_t codepage_string_length = 0;
	uint32_t feature_flags        = 0;
	int ascii_codepage            = 0;
	int result                    = 0;

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid codepage string.",
		 function );

		return( -1 );
	}
	codepage_string_length = narrow_string_length(
	                          codepage_string );

	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	if( libclocale_codepage_copy_from_string(
	     &ascii_codepage,
	     codepage_string,
	     codepage_string_length,
	     feature_flags,
	     &error ) != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_RuntimeError,
		 "%s: unable to determine ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_set_ascii_codepage(
	          pynk2_file->file,
	          ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to set ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 1 );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_set_ascii_codepage(
           pynk2_file_t *pynk2_file,
           PyObject *arguments,
           PyObject *keywords )
{
	char *codepage_string       = NULL;
	static char *keyword_list[] = { "codepage", NULL };
	int result                  = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &codepage_string ) == 0 )
	{
		return( NULL );
	}
	result = pynk2_file_set_ascii_codepage_from_string(
	          pynk2_file,
	          codepage_string );

	if( result != 1 )
	{
		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
int pynk2_file_set_ascii_codepage_setter(
     pynk2_file_t *pynk2_file,
     PyObject *string_object,
     void *closure PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *utf8_string_object = NULL;
	char *codepage_string        = NULL;
	static char *function        = "pynk2_file_set_ascii_codepage_setter";
	int result                   = 0;

	PYNK2_UNREFERENCED_PARAMETER( closure )

	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pynk2_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		/* The codepage string should only contain ASCII characters.
		 */
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pynk2_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( -1 );
		}
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   utf8_string_object );
#else
		codepage_string = PyString_AsString(
		                   utf8_string_object );
#endif
		if( codepage_string == NULL )
		{
			return( -1 );
		}
		result = pynk2_file_set_ascii_codepage_from_string(
		          pynk2_file,
		          codepage_string );

		if( result != 1 )
		{
			return( -1 );
		}
		return( 0 );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pynk2_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   string_object );
#else
		codepage_string = PyString_AsString(
		                   string_object );
#endif
		if( codepage_string == NULL )
		{
			return( -1 );
		}
		result = pynk2_file_set_ascii_codepage_from_string(
		          pynk2_file,
		          codepage_string );

		if( result != 1 )
		{
			return( -1 );
		}
		return( 0 );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( -1 );
}

/* Retrieves the modification time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_get_modification_time(
           pynk2_file_t *pynk2_file,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *datetime_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pynk2_file_get_modification_time";
	uint64_t filetime         = 0;
	int result                = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_get_modification_time(
	          pynk2_file->file,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve modification time.",
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
	datetime_object = pynk2_datetime_new_from_filetime(
	                   filetime );

	return( datetime_object );
}

/* Retrieves the modification time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_get_modification_time_as_integer(
           pynk2_file_t *pynk2_file,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_file_get_modification_time_as_integer";
	uint64_t filetime        = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_get_modification_time(
	          pynk2_file->file,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve modification time.",
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
	integer_object = pynk2_integer_unsigned_new_from_64bit(
	                  (uint64_t) filetime );

	return( integer_object );
}

/* Retrieves the number of items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_get_number_of_items(
           pynk2_file_t *pynk2_file,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pynk2_file_get_number_of_items";
	int number_of_items      = 0;
	int result               = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_get_number_of_items(
	          pynk2_file->file,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_items );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_items );
#endif
	return( integer_object );
}

/* Retrieves a specific item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_get_item_by_index(
           PyObject *pynk2_file,
           int item_index )
{
	PyObject *item_object    = NULL;
	libcerror_error_t *error = NULL;
	libnk2_item_t *item      = NULL;
	static char *function    = "pynk2_file_get_item_by_index";
	int result               = 0;

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_get_item(
	          ( (pynk2_file_t *) pynk2_file )->file,
	          item_index,
	          &item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve item: %d.",
		 function,
		 item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	item_object = pynk2_item_new(
	               item,
	               (PyObject *) pynk2_file );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( item != NULL )
	{
		libnk2_item_free(
		 &item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_get_item(
           pynk2_file_t *pynk2_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	static char *keyword_list[] = { "item_index", NULL };
	int item_index              = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &item_index ) == 0 )
	{
		return( NULL );
	}
	item_object = pynk2_file_get_item_by_index(
	               (PyObject *) pynk2_file,
	               item_index );

	return( item_object );
}

/* Retrieves a sequence and iterator object for the items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_file_get_items(
           pynk2_file_t *pynk2_file,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pynk2_file_get_items";
	int number_of_items       = 0;
	int result                = 0;

	PYNK2_UNREFERENCED_PARAMETER( arguments )

	if( pynk2_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libnk2_file_get_number_of_items(
	          pynk2_file->file,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pynk2_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pynk2_items_new(
	                   (PyObject *) pynk2_file,
	                   &pynk2_file_get_item_by_index,
	                   number_of_items );

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


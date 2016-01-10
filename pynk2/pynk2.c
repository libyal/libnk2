/*
 * Python bindings module for libnk2 (pynk2)
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

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pynk2.h"
#include "pynk2_error.h"
#include "pynk2_file.h"
#include "pynk2_libcerror.h"
#include "pynk2_libcstring.h"
#include "pynk2_libnk2.h"
#include "pynk2_python.h"
#include "pynk2_unused.h"

/* The pynk2 module methods
 */
PyMethodDef pynk2_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pynk2_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	/* Sentinel */
	{ NULL,
	  NULL,
	  0,
	  NULL}
};

/* Retrieves the pynk2/libnk2 version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_get_version(
           PyObject *self PYNK2_ATTRIBUTE_UNUSED,
           PyObject *arguments PYNK2_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYNK2_UNREFERENCED_PARAMETER( self )
	PYNK2_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libnk2_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = libcstring_narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

#if PY_MAJOR_VERSION >= 3

/* The pynk2 module definition
 */
PyModuleDef pynk2_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pynk2",
	/* m_doc */
	"Python libnk2 module (pynk2).",
	/* m_size */
	-1,
	/* m_methods */
	pynk2_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pynk2 module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pynk2(
                void )
#else
PyMODINIT_FUNC initpynk2(
                void )
#endif
{
	PyObject *module               = NULL;
	PyTypeObject *file_type_object = NULL;
	PyGILState_STATE gil_state     = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libnk2_notify_set_stream(
	 stderr,
	 NULL );
	libnk2_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pynk2_module_definition );
#else
	module = Py_InitModule3(
	          "pynk2",
	          pynk2_module_methods,
	          "Python libnk2 module (pynk2)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

	/* Setup the file type object
	 */
	pynk2_file_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pynk2_file_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pynk2_file_type_object );

	file_type_object = &pynk2_file_type_object;

	PyModule_AddObject(
	 module,
	 "file",
	 (PyObject *) file_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}


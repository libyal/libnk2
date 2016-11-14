/*
 * Python object definition of the sequence and iterator object of items
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

#include "pynk2_libcerror.h"
#include "pynk2_libnk2.h"
#include "pynk2_python.h"
#include "pynk2_item.h"
#include "pynk2_items.h"

PySequenceMethods pynk2_items_sequence_methods = {
	/* sq_length */
	(lenfunc) pynk2_items_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pynk2_items_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pynk2_items_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pynk2._items",
	/* tp_basicsize */
	sizeof( pynk2_items_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pynk2_items_free,
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
	&pynk2_items_sequence_methods,
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
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"pynk2 internal sequence and iterator object of items",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pynk2_items_iter,
	/* tp_iternext */
	(iternextfunc) pynk2_items_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
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
	(initproc) pynk2_items_init,
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

/* Creates a new items object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pynk2_items_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int item_index ),
           int number_of_items )
{
	pynk2_items_t *pynk2_items = NULL;
	static char *function      = "pynk2_items_new";

	if( parent_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid parent object.",
		 function );

		return( NULL );
	}
	if( get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get item by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the items values are initialized
	 */
	pynk2_items = PyObject_New(
	               struct pynk2_items,
	               &pynk2_items_type_object );

	if( pynk2_items == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize items.",
		 function );

		goto on_error;
	}
	if( pynk2_items_init(
	     pynk2_items ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize items.",
		 function );

		goto on_error;
	}
	pynk2_items->parent_object             = parent_object;
	pynk2_items->get_item_by_index = get_item_by_index;
	pynk2_items->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) pynk2_items->parent_object );

	return( (PyObject *) pynk2_items );

on_error:
	if( pynk2_items != NULL )
	{
		Py_DecRef(
		 (PyObject *) pynk2_items );
	}
	return( NULL );
}

/* Intializes a items object
 * Returns 0 if successful or -1 on error
 */
int pynk2_items_init(
     pynk2_items_t *pynk2_items )
{
	static char *function = "pynk2_items_init";

	if( pynk2_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( -1 );
	}
	/* Make sure the items values are initialized
	 */
	pynk2_items->parent_object             = NULL;
	pynk2_items->get_item_by_index = NULL;
	pynk2_items->item_index        = 0;
	pynk2_items->number_of_items   = 0;

	return( 0 );
}

/* Frees a items object
 */
void pynk2_items_free(
      pynk2_items_t *pynk2_items )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pynk2_items_free";

	if( pynk2_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pynk2_items );

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
	if( pynk2_items->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pynk2_items->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pynk2_items );
}

/* The items len() function
 */
Py_ssize_t pynk2_items_len(
            pynk2_items_t *pynk2_items )
{
	static char *function = "pynk2_items_len";

	if( pynk2_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pynk2_items->number_of_items );
}

/* The items getitem() function
 */
PyObject *pynk2_items_getitem(
           pynk2_items_t *pynk2_items,
           Py_ssize_t item_index )
{
	PyObject *item_object = NULL;
	static char *function = "pynk2_items_getitem";

	if( pynk2_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( NULL );
	}
	if( pynk2_items->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( pynk2_items->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pynk2_items->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	item_object = pynk2_items->get_item_by_index(
	               pynk2_items->parent_object,
	               (int) item_index );

	return( item_object );
}

/* The items iter() function
 */
PyObject *pynk2_items_iter(
           pynk2_items_t *pynk2_items )
{
	static char *function = "pynk2_items_iter";

	if( pynk2_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pynk2_items );

	return( (PyObject *) pynk2_items );
}

/* The items iternext() function
 */
PyObject *pynk2_items_iternext(
           pynk2_items_t *pynk2_items )
{
	PyObject *item_object = NULL;
	static char *function = "pynk2_items_iternext";

	if( pynk2_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( NULL );
	}
	if( pynk2_items->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( pynk2_items->item_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - invalid item index.",
		 function );

		return( NULL );
	}
	if( pynk2_items->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - invalid number of items.",
		 function );

		return( NULL );
	}
	if( pynk2_items->item_index >= pynk2_items->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	item_object = pynk2_items->get_item_by_index(
	               pynk2_items->parent_object,
	               pynk2_items->item_index );

	if( item_object != NULL )
	{
		pynk2_items->item_index++;
	}
	return( item_object );
}


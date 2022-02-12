/*
 * Python file object IO handle functions
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

#if !defined( _PYNK2_FILE_OBJECT_IO_HANDLE_H )
#define _PYNK2_FILE_OBJECT_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "pynk2_libbfio.h"
#include "pynk2_libcerror.h"
#include "pynk2_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pynk2_file_object_io_handle pynk2_file_object_io_handle_t;

struct pynk2_file_object_io_handle
{
	/* The python file (like) object
	 */
	PyObject *file_object;

	/* The access flags
	 */
	int access_flags;
};

int pynk2_file_object_io_handle_initialize(
     pynk2_file_object_io_handle_t **file_object_io_handle,
     PyObject *file_object,
     libcerror_error_t **error );

int pynk2_file_object_initialize(
     libbfio_handle_t **handle,
     PyObject *file_object,
     libcerror_error_t **error );

int pynk2_file_object_io_handle_free(
     pynk2_file_object_io_handle_t **file_object_io_handle,
     libcerror_error_t **error );

int pynk2_file_object_io_handle_clone(
     pynk2_file_object_io_handle_t **destination_file_object_io_handle,
     pynk2_file_object_io_handle_t *source_file_object_io_handle,
     libcerror_error_t **error );

int pynk2_file_object_io_handle_open(
     pynk2_file_object_io_handle_t *file_object_io_handle,
     int access_flags,
     libcerror_error_t **error );

int pynk2_file_object_io_handle_close(
     pynk2_file_object_io_handle_t *file_object_io_handle,
     libcerror_error_t **error );

ssize_t pynk2_file_object_read_buffer(
         PyObject *file_object,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error );

ssize_t pynk2_file_object_io_handle_read(
         pynk2_file_object_io_handle_t *file_object_io_handle,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error );

ssize_t pynk2_file_object_write_buffer(
         PyObject *file_object,
         const uint8_t *buffer,
         size_t size,
         libcerror_error_t **error );

ssize_t pynk2_file_object_io_handle_write(
         pynk2_file_object_io_handle_t *file_object_io_handle,
         const uint8_t *buffer,
         size_t size,
         libcerror_error_t **error );

int pynk2_file_object_seek_offset(
     PyObject *file_object,
     off64_t offset,
     int whence,
     libcerror_error_t **error );

int pynk2_file_object_get_offset(
     PyObject *file_object,
     off64_t *offset,
     libcerror_error_t **error );

off64_t pynk2_file_object_io_handle_seek_offset(
         pynk2_file_object_io_handle_t *file_object_io_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

int pynk2_file_object_io_handle_exists(
     pynk2_file_object_io_handle_t *file_object_io_handle,
     libcerror_error_t **error );

int pynk2_file_object_io_handle_is_open(
     pynk2_file_object_io_handle_t *file_object_io_handle,
     libcerror_error_t **error );

int pynk2_file_object_get_size(
     PyObject *file_object,
     size64_t *size,
     libcerror_error_t **error );

int pynk2_file_object_io_handle_get_size(
     pynk2_file_object_io_handle_t *file_object_io_handle,
     size64_t *size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYNK2_FILE_OBJECT_IO_HANDLE_H ) */


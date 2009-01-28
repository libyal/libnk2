/*
 * libnk2 Input/Output (IO) handle
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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

#if !defined( _LIBNK2_IO_HANDLE_H )
#define _LIBNK2_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_data_array.h"
#include "libnk2_libbfio.h"
#include "libnk2_list_type.h"
#include "libnk2_tree_type.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_io_handle libnk2_io_handle_t;

struct libnk2_io_handle
{
	/* The descriptor index root tree node
	 */
	libnk2_tree_node_t *descriptor_index_root_node;

	/* The offset index root tree node
	 */
	libnk2_tree_node_t *offset_index_root_node;

	/* The recovered descriptor index root tree node
	 */
	libnk2_tree_node_t *recovered_descriptor_index_root_node;

	/* The recovered offset index root tree node
	 */
	libnk2_tree_node_t *recovered_offset_index_root_node;

	/* The file io handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The file size
	 */
	size64_t file_size;

	/* The encryption type
	 */
	uint8_t encryption_type;

	/* The encryption key
	 */
	uint32_t encryption_key;

	/* The file type
	 */
	uint8_t file_type;
};

int libnk2_io_handle_initialize(
     libnk2_io_handle_t **io_handle,
     liberror_error_t **error );

int libnk2_io_handle_free(
     libnk2_io_handle_t **io_handle,
     liberror_error_t **error );

int libnk2_io_handle_open(
     libnk2_io_handle_t *io_handle,
     const char *filename,
     int flags,
     liberror_error_t **error );

#if defined( LIBNK2_WIDE_CHARACTER_TYPE )
int libnk2_io_handle_open_wide(
     libnk2_io_handle_t *io_handle,
     const wchar_t *filename,
     int flags,
     liberror_error_t **error );
#endif

int libnk2_io_handle_close(
     libnk2_io_handle_t *io_handle,
     liberror_error_t **error );

int libnk2_io_handle_read_file_header(
     libnk2_io_handle_t *io_handle,
     off64_t *offset_index_root_node_offset,
     uint64_t *offset_index_back_pointer,
     off64_t *descriptor_index_root_node_offset,
     uint64_t *descriptor_index_back_pointer,
     int *file_content_type,
     liberror_error_t **error );

int libnk2_io_handle_read_unallocated_data_blocks(
     libnk2_io_handle_t *io_handle,
     libnk2_list_t *unallocated_data_block_list,
     liberror_error_t **error );

int libnk2_io_handle_read_unallocated_index_node_blocks(
     libnk2_io_handle_t *io_handle,
     libnk2_list_t *unallocated_index_node_block_list,
     liberror_error_t **error );

int libnk2_io_handle_read_descriptor_index(
     libnk2_io_handle_t *io_handle,
     off64_t descriptor_index_root_node_offset,
     uint64_t descriptor_index_back_pointer,
     liberror_error_t **error );

int libnk2_io_handle_read_offset_index(
     libnk2_io_handle_t *io_handle,
     off64_t offset_index_root_node_offset,
     uint64_t offset_index_back_pointer,
     liberror_error_t **error );

int libnk2_io_handle_recover_items(
     libnk2_io_handle_t *io_handle,
     libnk2_list_t *unallocated_data_block_list,
     libnk2_list_t *unallocated_index_node_block_list,
     libnk2_list_t *recovered_item_list,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif


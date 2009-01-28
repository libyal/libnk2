/*
 * libnk2 file
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

#if !defined( _LIBNK2_INTERNAL_FILE_H )
#define _LIBNK2_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_extern.h"
#include "libnk2_io_handle.h"
#include "libnk2_tree_type.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_internal_file libnk2_internal_file_t;

struct libnk2_internal_file
{
	/* The item reference list
	 */
	libnk2_list_t *item_reference_list;

	/* The item tree root node
	 */
	libnk2_tree_node_t *item_tree_root_node;

	/* The root folder item tree node
	 */
	libnk2_tree_node_t *root_folder_item_tree_node;

	/* The recovered item list
	 */
	libnk2_list_t *recovered_item_list;

	/* The io handle
	 */
	libnk2_io_handle_t *io_handle;

	/* Value to indicate if the allocation tables
	 * have been read
	 */
	int read_allocation_tables;

	/* The unallocated data block list
	 */
	libnk2_list_t *unallocated_data_block_list;

	/* The unallocated index node block list
	 */
	libnk2_list_t *unallocated_index_node_block_list;

	/* The name to id map list
	 */
	libnk2_list_t *name_to_id_map_list;

	/* The content type
	 */
	int content_type;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

LIBNK2_EXTERN int libnk2_file_initialize(
                   libnk2_file_t **file,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_free(
                   libnk2_file_t **file,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_open(
                   libnk2_file_t *file,
                   const char *filename,
                   int flags,
                   liberror_error_t **error );

#if defined( LIBNK2_WIDE_CHARACTER_TYPE )
LIBNK2_EXTERN int libnk2_file_open_wide(
                   libnk2_file_t *file,
                   const wchar_t *filename,
                   int flags,
                   liberror_error_t **error );
#endif

LIBNK2_EXTERN int libnk2_file_close(
                   libnk2_file_t *file,
                   liberror_error_t **error );

int libnk2_file_open_read(
     libnk2_internal_file_t *internal_file,
     liberror_error_t **error );

int libnk2_file_read_allocation_tables(
     libnk2_internal_file_t *internal_file,
     liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_recover_items(
                   libnk2_file_t *file,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_size(
                   libnk2_file_t *file,
                   size64_t *size,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_content_type(
                   libnk2_file_t *file,
                   uint8_t *content_type,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_type(
                   libnk2_file_t *file,
                   uint8_t *type,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_encryption_values(
                   libnk2_file_t *file,
                   uint8_t *encryption_type,
                   uint32_t *encryption_key,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_ascii_codepage(
                   libnk2_file_t *file,
                   int *ascii_codepage,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_set_ascii_codepage(
                   libnk2_file_t *file,
                   int ascii_codepage,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_amount_of_unallocated_blocks(
                   libnk2_file_t *file,
                   int unallocated_block_type,
                   int *amount_of_unallocated_blocks,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_unallocated_block(
                   libnk2_file_t *file,
                   int unallocated_block_type,
                   int unallocated_block_index,
                   off64_t *offset,
                   size64_t *size,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_root_item(
                   libnk2_file_t *file,
                   libnk2_item_t **root_item,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_message_store(
                   libnk2_file_t *file,
                   libnk2_item_t **message_store,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_root_folder(
                   libnk2_file_t *file,
                   libnk2_item_t **root_folder,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_amount_of_recovered_items(
                   libnk2_file_t *file,
                   int *amount_of_recovered_items,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_file_get_recovered_item(
                   libnk2_file_t *file,
                   int recovered_item_index,
                   libnk2_item_t **recovered_item,
                   liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif


/*
 * Export handle
 *
 * Copyright (C) 2009-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _EXPORT_HANDLE_H )
#define _EXPORT_HANDLE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "item_file.h"
#include "log_handle.h"
#include "nk2tools_libcerror.h"
#include "nk2tools_libnk2.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct export_handle export_handle_t;

struct export_handle
{
	/* Value to indicate item values should be dumped
	 */
	uint8_t dump_item_values;

	/* The input
	 */
	libnk2_file_t *input;

	/* The ascii codepage
	 */
	int ascii_codepage;

	/* The target path
	 */
	system_character_t *target_path;

	/* The target path size
	 */
	size_t target_path_size;

	/* The items export path
	 */
	system_character_t *items_export_path;

	/* The items export path size
	 */
	size_t items_export_path_size;

	/* Value to indicate if status information
	 * should be printed to the notify stream
	 */
	uint8_t print_status_information;

	/* The notification output stream
	 */
	FILE *notify_stream;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int export_handle_initialize(
     export_handle_t **export_handle,
     libcerror_error_t **error );

int export_handle_free(
     export_handle_t **export_handle,
     libcerror_error_t **error );

int export_handle_signal_abort(
     export_handle_t *export_handle,
     libcerror_error_t **error );

int export_handle_set_ascii_codepage(
     export_handle_t *export_handle,
     const system_character_t *string,
     libcerror_error_t **error );

int export_handle_set_target_path(
     export_handle_t *export_handle,
     const system_character_t *target_path,
     libcerror_error_t **error );

int export_handle_set_export_path(
     export_handle_t *export_handle,
     const system_character_t *base_path,
     size_t base_path_length,
     const system_character_t *suffix,
     size_t suffix_length,
     system_character_t **export_path,
     size_t *export_path_size,
     libcerror_error_t **error );

int export_handle_create_items_export_path(
     export_handle_t *export_handle,
     libcerror_error_t **error );

int export_handle_open(
     export_handle_t *export_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int export_handle_close(
     export_handle_t *export_handle,
     libcerror_error_t **error );

/* Item generic export functions
 */
int export_handle_create_default_item_directory(
     export_handle_t *export_handle,
     int item_index,
     const system_character_t *item_prefix,
     size_t item_prefix_length,
     const system_character_t *export_path,
     size_t export_path_length,
     system_character_t **item_directory_path,
     size_t *item_directory_path_size,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_create_item_file(
     export_handle_t *export_handle,
     const system_character_t *path,
     size_t path_length,
     const system_character_t *filename,
     size_t filename_length,
     item_file_t **item_file,
     libcerror_error_t **error );

int export_handle_export_record_entry(
     export_handle_t *export_handle,
     item_file_t *item_file,
     int entry_index,
     libnk2_record_entry_t *record_entry,
     libcerror_error_t **error );

int export_handle_export_item_values(
     export_handle_t *export_handle,
     libnk2_item_t *item,
     const system_character_t *item_values_filename,
     size_t item_values_filename_length,
     const system_character_t *export_path,
     size_t export_path_length,
     log_handle_t *log_handle,
     libcerror_error_t **error );

/* Item specific export functions
 */
int export_handle_export_alias(
     export_handle_t *export_handle,
     libnk2_item_t *alias,
     int alias_index,
     const system_character_t *export_path,
     size_t export_path_length,
     log_handle_t *log_handle,
     libcerror_error_t **error );

/* File export functions
 */
int export_handle_export_items(
     export_handle_t *export_handle,
     libnk2_file_t *file,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_export_file(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _EXPORT_HANDLE_H ) */


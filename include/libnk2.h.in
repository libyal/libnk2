/*
 * Library to access the Nickfile (NK2) format
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

#if !defined( _LIBNK2_H )
#define _LIBNK2_H

#include <libnk2/codepage.h>
#include <libnk2/definitions.h>
#include <libnk2/error.h>
#include <libnk2/extern.h>
#include <libnk2/features.h>
#include <libnk2/mapi.h>
#include <libnk2/types.h>

#include <stdio.h>

#if defined( LIBNK2_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBNK2_EXTERN \
const char *libnk2_get_version(
             void );

/* Returns the access flags for reading
 */
LIBNK2_EXTERN \
int libnk2_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_get_codepage(
     int *codepage,
     libnk2_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_set_codepage(
     int codepage,
     libnk2_error_t **error );

/* Determines if a file contains a NK2 file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_check_file_signature(
     const char *filename,
     libnk2_error_t **error );

#if defined( LIBNK2_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a NK2 file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_check_file_signature_wide(
     const wchar_t *filename,
     libnk2_error_t **error );

#endif /* defined( LIBNK2_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBNK2_HAVE_BFIO )

/* Determines if a file contains a NK2 file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libnk2_error_t **error );

#endif /* defined( LIBNK2_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBNK2_EXTERN \
void libnk2_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_notify_set_stream(
     FILE *stream,
     libnk2_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_notify_stream_open(
     const char *filename,
     libnk2_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_notify_stream_close(
     libnk2_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBNK2_EXTERN \
void libnk2_error_free(
      libnk2_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_error_fprint(
     libnk2_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_error_sprint(
     libnk2_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_error_backtrace_fprint(
     libnk2_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_error_backtrace_sprint(
     libnk2_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * File functions
 * ------------------------------------------------------------------------- */

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_initialize(
     libnk2_file_t **file,
     libnk2_error_t **error );

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_free(
     libnk2_file_t **file,
     libnk2_error_t **error );

/* Signals the libnk2 file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_signal_abort(
     libnk2_file_t *file,
     libnk2_error_t **error );

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_open(
     libnk2_file_t *file,
     const char *filename,
     int access_flags,
     libnk2_error_t **error );

#if defined( LIBNK2_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_open_wide(
     libnk2_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libnk2_error_t **error );

#endif /* defined( LIBNK2_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBNK2_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_open_file_io_handle(
     libnk2_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libnk2_error_t **error );

#endif /* defined( LIBNK2_HAVE_BFIO ) */

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_close(
     libnk2_file_t *file,
     libnk2_error_t **error );

/* Retrieves the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_get_ascii_codepage(
     libnk2_file_t *file,
     int *ascii_codepage,
     libnk2_error_t **error );

/* Sets the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_set_ascii_codepage(
     libnk2_file_t *file,
     int ascii_codepage,
     libnk2_error_t **error );

/* Retrieves the modification time
 * The returned time is a 64-bit version of a filetime value
 * Returns 1 if successful, 0 if not set or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_get_modification_time(
     libnk2_file_t *file,
     uint64_t *filetime,
     libnk2_error_t **error );

/* Retrieves the number of items
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_get_number_of_items(
     libnk2_file_t *file,
     int *number_of_items,
     libnk2_error_t **error );

/* Retrieves a specific item
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_file_get_item(
     libnk2_file_t *file,
     int item_index,
     libnk2_item_t **item,
     libnk2_error_t **error );

/* -------------------------------------------------------------------------
 * Item functions
 * ------------------------------------------------------------------------- */

/* Frees an item
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_item_free(
     libnk2_item_t **item,
     libnk2_error_t **error );

/* Retrieves the identifier of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_item_get_identifier(
     libnk2_item_t *item,
     uint32_t *identifier,
     libnk2_error_t **error );

/* Retrieves the number of entries
 * All sets in an item contain the same number of entries
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_item_get_number_of_entries(
     libnk2_item_t *item,
     int *number_of_entries,
     libnk2_error_t **error );

/* Retrieves a specific entry from the item
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_item_get_entry_by_index(
     libnk2_item_t *item,
     int entry_index,
     libnk2_record_entry_t **record_entry,
     libnk2_error_t **error );

/* Retrieves the record entry matching the entry and value type pair from the item
 *
 * When the LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE is set
 * the value type is ignored and set. The default behavior is a strict
 * matching of the value type. In this case the value type must be filled
 * with the corresponding value type
 *
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_item_get_entry_by_type(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t value_type,
     libnk2_record_entry_t **record_entry,
     uint8_t flags,
     libnk2_error_t **error );

/* -------------------------------------------------------------------------
 * Record entry functions
 * ------------------------------------------------------------------------- */

/* Frees a record entry
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_free(
     libnk2_record_entry_t **record_entry,
     libnk2_error_t **error );

/* Retrieves the entry type
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_entry_type(
     libnk2_record_entry_t *record_entry,
     uint32_t *entry_type,
     libnk2_error_t **error );

/* Retrieves the value type
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_value_type(
     libnk2_record_entry_t *record_entry,
     uint32_t *value_type,
     libnk2_error_t **error );

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_size(
     libnk2_record_entry_t *record_entry,
     size_t *data_size,
     libnk2_error_t **error );

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data(
     libnk2_record_entry_t *record_entry,
     uint8_t *data,
     size_t data_size,
     libnk2_error_t **error );

/* Retrieves the data as a boolean value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_boolean(
     libnk2_record_entry_t *record_entry,
     uint8_t *value_boolean,
     libnk2_error_t **error );

/* Retrieves the data as a 16-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_16bit_integer(
     libnk2_record_entry_t *record_entry,
     uint16_t *value_16bit,
     libnk2_error_t **error );

/* Retrieves the data as a 32-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_32bit_integer(
     libnk2_record_entry_t *record_entry,
     uint32_t *value_32bit,
     libnk2_error_t **error );

/* Retrieves the data as a 64-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_64bit_integer(
     libnk2_record_entry_t *record_entry,
     uint64_t *value_64bit,
     libnk2_error_t **error );

/* Retrieves the data as a 64-bit FILETIME value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_filetime(
     libnk2_record_entry_t *record_entry,
     uint64_t *filetime,
     libnk2_error_t **error );

/* Retrieves the data as a 64-bit floatingtime value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_floatingtime(
     libnk2_record_entry_t *record_entry,
     uint64_t *floatingtime,
     libnk2_error_t **error );

/* Retrieves the data as a size_t value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_size(
     libnk2_record_entry_t *record_entry,
     size64_t *value_size,
     libnk2_error_t **error );

/* Retrieves the floating point value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_floating_point(
     libnk2_record_entry_t *record_entry,
     double *value_floating_point,
     libnk2_error_t **error );

/* Retrieves the size of the data formatted as an UTF-8 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_utf8_string_size(
     libnk2_record_entry_t *record_entry,
     size_t *utf8_string_size,
     libnk2_error_t **error );

/* Retrieves the data formatted as an UTF-8 string
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_utf8_string(
     libnk2_record_entry_t *record_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libnk2_error_t **error );

/* Retrieves the size of the data formatted as an UTF-16 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_utf16_string_size(
     libnk2_record_entry_t *record_entry,
     size_t *utf16_string_size,
     libnk2_error_t **error );

/* Retrieves the data formatted as an UTF-16 string
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_utf16_string(
     libnk2_record_entry_t *record_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libnk2_error_t **error );

/* Retrieves the data as a GUID value
 * Returns 1 if successful or -1 on error
 */
LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_guid(
     libnk2_record_entry_t *record_entry,
     uint8_t *guid_data,
     size_t guid_data_size,
     libnk2_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_H ) */


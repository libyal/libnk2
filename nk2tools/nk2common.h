/*
 * Common functions for the nk2tools
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

#if !defined( _NK2COMMON_H )
#define _NK2COMMON_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#include <stdio.h>

#include <libnk2.h>

#include "character_string.h"
#include "file_io.h"
#include "file_stream_io.h"
#include "system_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( WINAPI )
#define NK2COMMON_PATH_SEPARATOR	'\\'

#else
#define NK2COMMON_PATH_SEPARATOR	'/'
#endif

#define NK2COMMON_EXPORT_FORMAT_ALL	(int) 'a'
#define NK2COMMON_EXPORT_FORMAT_HTML	(int) 'h'
#define NK2COMMON_EXPORT_FORMAT_RTF	(int) 'r'
#define NK2COMMON_EXPORT_FORMAT_TEXT	(int) 't'

#if defined( HAVE_WIDE_SYSTEM_CHARACTER_T )
#define nk2common_fopen( filename, mode ) \
        file_stream_io_wfopen( filename, mode )

#define nk2common_file_exists( filename ) \
        file_io_wexists( filename )

#else
#define nk2common_fopen( filename, mode ) \
        file_stream_io_fopen( filename, mode )

#define nk2common_file_exists( filename ) \
        file_io_exists( filename )

#endif

int nk2common_sanitize_filename(
     uint8_t *filename,
     size_t filename_length,
     liberror_error_t **error );

int nk2common_create_fullname(
     system_character_t *export_path,
     uint8_t *filename,
     size_t filename_size,
     system_character_t **fullname,
     liberror_error_t **error );

int nk2common_export_item(
     FILE *log_file_stream,
     libnk2_item_t *item,
     int item_index,
     int amount_of_items,
     system_character_t *export_path,
     int preferred_export_format,
     liberror_error_t **error );

int nk2common_export_sub_items(
     FILE *log_file_stream,
     libnk2_item_t *item,
     system_character_t *export_path,
     int preferred_export_format,
     liberror_error_t **error );

int nk2common_export_message_header(
     FILE *log_file_stream,
     libnk2_item_t *message,
     int message_index,
     system_character_t *export_path,
     int preferred_export_format,
     liberror_error_t **error );

int nk2common_export_attachment(
     FILE *log_file_stream,
     libnk2_item_t *attachment,
     int attachment_index,
     system_character_t *export_path,
     int preferred_export_format,
     liberror_error_t **error );

int nk2common_export_email(
     FILE *log_file_stream,
     libnk2_item_t *email,
     int email_index,
     system_character_t *export_path,
     int preferred_export_format,
     liberror_error_t **error );

int nk2common_export_email_internet_headers(
     FILE *log_file_stream,
     libnk2_item_t *email,
     system_character_t *export_path,
     liberror_error_t **error );

int nk2common_export_email_body_html(
     FILE *log_file_stream,
     libnk2_item_t *email,
     uint8_t *email_filename,
     size_t email_filename_size,
     size_t email_html_body_size,
     system_character_t *export_path,
     liberror_error_t **error );

int nk2common_export_email_body_rtf(
     FILE *log_file_stream,
     libnk2_item_t *email,
     uint8_t *email_filename,
     size_t email_filename_size,
     size_t email_rtf_body_size,
     system_character_t *export_path,
     liberror_error_t **error );

int nk2common_export_email_body_plain_text(
     FILE *log_file_stream,
     libnk2_item_t *email,
     uint8_t *email_filename,
     size_t email_filename_size,
     size_t email_plain_text_body_size,
     int export_internet_headers,
     system_character_t *export_path,
     liberror_error_t **error );

int nk2common_export_appointment(
     FILE *log_file_stream,
     libnk2_item_t *appointment,
     int appointment_index,
     system_character_t *export_path,
     int preferred_export_format,
     liberror_error_t **error );

int nk2common_export_contact(
     FILE *log_file_stream,
     libnk2_item_t *appointment,
     int appointment_index,
     system_character_t *export_path,
     int preferred_export_format,
     liberror_error_t **error );

int nk2common_export_folder(
     FILE *log_file_stream,
     libnk2_item_t *folder,
     int folder_index,
     system_character_t *export_path,
     int preferred_export_format,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif


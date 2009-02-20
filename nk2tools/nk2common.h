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

#if defined( __cplusplus )
}
#endif

#endif


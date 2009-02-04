/*
 * Codepage definitions for libnk2
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

#if !defined( _LIBNK2_CODEPAGE_H )
#define _LIBNK2_CODEPAGE_H

#include <libnk2/types.h>

/* The ASCII codepages
 */
enum LIBNK2_CODEPAGES
{
	LIBNK2_CODEPAGE_ASCII				= 0x41,
	LIBNK2_CODEPAGE_WINDOWS_1250			= 1250,
	LIBNK2_CODEPAGE_WINDOWS_1251			= 1251,
	LIBNK2_CODEPAGE_WINDOWS_1252			= 1252,
	LIBNK2_CODEPAGE_WINDOWS_1253			= 1253,
	LIBNK2_CODEPAGE_WINDOWS_1254			= 1254,
	LIBNK2_CODEPAGE_WINDOWS_1255			= 1255,
	LIBNK2_CODEPAGE_WINDOWS_1256			= 1256,
	LIBNK2_CODEPAGE_WINDOWS_1257			= 1257,
	LIBNK2_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBNK2_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBPFF_CODEPAGE_WINDOWS_1250
#define LIBNK2_CODEPAGE_WINDOWS_CYRILLIC		LIBPFF_CODEPAGE_WINDOWS_1251
#define LIBNK2_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBPFF_CODEPAGE_WINDOWS_1252
#define LIBNK2_CODEPAGE_WINDOWS_GREEK			LIBPFF_CODEPAGE_WINDOWS_1253
#define LIBNK2_CODEPAGE_WINDOWS_TURKISH			LIBPFF_CODEPAGE_WINDOWS_1254
#define LIBNK2_CODEPAGE_WINDOWS_HEBREW			LIBPFF_CODEPAGE_WINDOWS_1255
#define LIBNK2_CODEPAGE_WINDOWS_ARABIC			LIBPFF_CODEPAGE_WINDOWS_1256
#define LIBNK2_CODEPAGE_WINDOWS_BALTIC			LIBPFF_CODEPAGE_WINDOWS_1257
#define LIBNK2_CODEPAGE_WINDOWS_VIETNAMESE		LIBPFF_CODEPAGE_WINDOWS_1258

#endif


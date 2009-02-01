/*
 * The internal definitions
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

#if !defined( _LIBNK2_INTERNAL_DEFINITIONS_H )
#define _LIBNK2_INTERNAL_DEFINITIONS_H

#include <libnk2/codepage.h>
#include <libnk2/definitions.h>
#include <libnk2/mapi.h>

/* The mask for the (file) offset index identifier
 * The lower order bit of the (file) offset index identifier is used for other purposes
 * and needs to be excluded when the identifier is searched in the index
 */
#define LIBNK2_OFFSET_INDEX_IDENTIFIER_MASK				0xfffffffffffffffeLL

/* The 2nd lower order bit of the (file) offset index identifier is used to flag that the data is encrypted
 */
#define LIBNK2_OFFSET_INDEX_IDENTIFIER_ENCRYPTION_FLAG			0x0000000000000002LL

/* The descriptor list identifiers
 */
#define LIBNK2_DESCRIPTOR_LIST_ATTACHMENTS_IDENTIFIER			0x0671

#endif


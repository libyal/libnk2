/*
 * The file header definition of a Personal Folder File
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

#if !defined( _NK2_FILE_HEADER_H )
#define _NK2_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define NK2_FILE_HEADER_CONTENT_TYPE_PAB	0x4142
#define NK2_FILE_HEADER_CONTENT_TYPE_PST	0x4d53
#define NK2_FILE_HEADER_CONTENT_TYPE_OST	0x4f53

typedef struct nk2_file_header nk2_file_header_t;

struct nk2_file_header
{
	/* Signature
	 * Consists of 4 bytes
	 * 0x21 0x42 0x24 0x2e
	 */
	uint8_t signature[ 4 ];

	/* Weak CRC of the following 471 bytes
	 * Consists of 4 bytes
	 */
	uint8_t crc[ 4 ];

	/* Content type
	 * Consists of 2 bytes
	 * 0x53 0x4d (SM) for PST files
	 * 0x53 0x4f (SO) for OST files
	 */
	uint8_t content_type[ 2 ];

	/* Data version
	 * Consists of 2 byte
	 * 0x000e for 32 bit data type
	 * 0x0015 for 64 bit data type
	 * 0x0017 for 64 bit data type
	 */
	uint8_t data_version[ 2 ];

	/* Content verion
	 * Consists of 2 bytes
	 */
	uint8_t content_version[ 2 ];

	/* Creation platform
	 * Consists of 1 byte
	 */
	uint8_t creation_platform;

	/* Access platform
	 * Consists of 1 byte
	 */
	uint8_t access_platform;

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];
};

typedef struct nk2_file_header_data_32bit nk2_file_header_data_32bit_t;

struct nk2_file_header_data_32bit
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 128 bytes
	 */
	uint8_t unknown4[ 128 ];

	/* Padding
	 * Consists of 4 bytes
	 */
	uint8_t padding1[ 4 ];

	/* File size
	 * Consists of 4 bytes
	 */
	uint8_t file_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];

	/* The back pointer of the root node of the descriptor index
	 * Consists of 4 bytes
	 */
	uint8_t descriptor_index_back_pointer[ 4 ];

	/* The file offset of the root node of the descriptor index
	 * Consists of 4 bytes
	 */
	uint8_t descriptor_index_root_node_offset[ 4 ];

	/* The back pointer of the root node of the (file) offset index
	 * Consists of 4 bytes
	 */
	uint8_t offset_index_back_pointer[ 4 ];

	/* The file offset of the root node of the (file) offset index
	 * Consists of 4 bytes
	 */
	uint8_t offset_index_root_node_offset[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 128 ];

	/* Unknown
	 * Consists of 128 bytes
	 */
	uint8_t unknown10[ 128 ];

	/* Sentinal
	 * Consists of 1 byte
	 * 0x80
	 */
	uint8_t sentinal;

	/* The encryption type
	 * Consists of 1 byte
	 */
	uint8_t encryption_type;

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown11[ 2 ];

	/* Unknown
	 * Consists of 15 bytes
	 */
	uint8_t unknown12[ 15 ];
};

typedef struct nk2_file_header_data_64bit nk2_file_header_data_64bit_t;

struct nk2_file_header_data_64bit
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown2[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 124 bytes
	 */
	uint8_t unknown4[ 128 ];

	/* Padding
	 * Consists of 12 bytes
	 * Sometimes not empty
	 */
	uint8_t padding1[ 12 ];

	/* File size
	 * Consists of 8 bytes
	 */
	uint8_t file_size[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown5[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown6[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown7[ 8 ];

	/* The back pointer of the root node of the descriptor index
	 * Consists of 8 bytes
	 */
	uint8_t descriptor_index_back_pointer[ 8 ];

	/* The file offset of the root node of the descriptor index
	 * Consists of 8 bytes
	 */
	uint8_t descriptor_index_root_node_offset[ 8 ];

	/* The back pointer of the root node of the (file) offset index
	 * Consists of 8 bytes
	 */
	uint8_t offset_index_back_pointer[ 8 ];

	/* The file offset of the root node of the (file) offset index
	 * Consists of 8 bytes
	 */
	uint8_t offset_index_root_node_offset[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown8[ 8 ];

	/* Unknown
	 * Consists of 128 bytes
	 */
	uint8_t unknown9[ 128 ];

	/* Unknown
	 * Consists of 128 bytes
	 */
	uint8_t unknown10[ 128 ];

	/* Sentinal
	 * Consists of 1 byte
	 */
	uint8_t sentinal;

	/* The encryption type
	 * Consists of 1 byte
	 */
	uint8_t encryption_type;

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown11[ 2 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown12[ 8 ];

	/* Weak CRC of the previous 516 bytes
	 * Consists of 4 bytes
	 */
	uint8_t crc[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif


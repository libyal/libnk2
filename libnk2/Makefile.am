AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common -I$(top_srcdir)/liberror -I$(top_srcdir)/libfmapi @LIBUNA_CPPFLAGS@ @LIBBFIO_CPPFLAGS@ @MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = libnk2.la

libnk2_la_SOURCES = \
	libnk2.c \
	libnk2_debug.c libnk2_debug.h \
	libnk2_definitions.h \
	libnk2_error.h \
	libnk2_extern.h \
	libnk2_file.c libnk2_file.h \
	libnk2_guid.c libnk2_guid.h \
	libnk2_item.c libnk2_item.h \
	libnk2_item_values.c libnk2_item_values.h \
	libnk2_io_handle.c libnk2_io_handle.h \
	libnk2_libbfio.h \
	libnk2_libuna.h \
	libnk2_list_type.c libnk2_list_type.h \
	libnk2_notify.c libnk2_notify.h \
	libnk2_string.h \
	libnk2_support.c libnk2_support.h \
	libnk2_system_string.h \
	nk2_file_header.h \
	nk2_item.h

libnk2_la_LIBADD  = ../liberror/liberror.la ../libfmapi/libfmapi.la @LIBUNA_LIBADD@ @LIBBFIO_LIBADD@
libnk2_la_LDFLAGS = -no-undefined -version-info 1:0:0

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libnk2 ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libnk2_la_SOURCES) 


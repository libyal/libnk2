AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libnotify \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@LIBFMAPI_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = libnk2.la

libnk2_la_SOURCES = \
	libnk2.c \
	libnk2_array_type.c libnk2_array_type.h \
	libnk2_codepage.h \
	libnk2_debug.c libnk2_debug.h \
	libnk2_definitions.h \
	libnk2_error.c libnk2_error.h \
	libnk2_extern.h \
	libnk2_file.c libnk2_file.h \
	libnk2_item.c libnk2_item.h \
	libnk2_item_values.c libnk2_item_values.h \
	libnk2_io_handle.c libnk2_io_handle.h \
	libnk2_legacy.c libnk2_legacy.h \
	libnk2_libbfio.h \
	libnk2_libfmapi.h \
	libnk2_libfvalue.h \
	libnk2_libuna.h \
	libnk2_mapi.h \
	libnk2_notify.c libnk2_notify.h \
	libnk2_support.c libnk2_support.h \
	libnk2_types.h \
	libnk2_value_type.c libnk2_value_type.h \
	nk2_file_header.h \
	nk2_item.h

libnk2_la_LIBADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libnotify/libnotify.la \
	@LIBUNA_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@LIBFWNT_LIBADD@ \
	@LIBFMAPI_LIBADD@

libnk2_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libnk2_definitions.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libnk2_definitions.h
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libnk2 ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libnk2_la_SOURCES) 


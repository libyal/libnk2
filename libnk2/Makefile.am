AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@LIBFMAPI_CPPFLAGS@ \
	@LIBNK2_DLL_EXPORT@

lib_LTLIBRARIES = libnk2.la

libnk2_la_SOURCES = \
	libnk2.c \
	libnk2_codepage.h \
	libnk2_debug.c libnk2_debug.h \
	libnk2_definitions.h \
	libnk2_error.c libnk2_error.h \
	libnk2_extern.h \
	libnk2_file.c libnk2_file.h \
	libnk2_file_footer.c libnk2_file_footer.h \
	libnk2_file_header.c libnk2_file_header.h \
	libnk2_item.c libnk2_item.h \
	libnk2_io_handle.c libnk2_io_handle.h \
	libnk2_libbfio.h \
	libnk2_libcdata.h \
	libnk2_libcerror.h \
	libnk2_libclocale.h \
	libnk2_libcnotify.h \
	libnk2_libfdatetime.h \
	libnk2_libfmapi.h \
	libnk2_libuna.h \
	libnk2_mapi.h \
	libnk2_mapi_value.c libnk2_mapi_value.h \
	libnk2_notify.c libnk2_notify.h \
	libnk2_record_entry.c libnk2_record_entry.h \
	libnk2_support.c libnk2_support.h \
	libnk2_types.h \
	libnk2_unused.h \
	nk2_file_footer.h \
	nk2_file_header.h \
	nk2_item.h

libnk2_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFWNT_LIBADD@ \
	@LIBFMAPI_LIBADD@

libnk2_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libnk2_definitions.h.in \
	libnk2.rc \
	libnk2.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libnk2_definitions.h
	/bin/rm -f libnk2.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libnk2 ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libnk2_la_SOURCES)


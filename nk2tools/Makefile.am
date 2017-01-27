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
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@LIBFMAPI_CPPFLAGS@ \
	@LIBNK2_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	nk2export \
	nk2info

nk2export_SOURCES = \
	export_handle.c export_handle.h \
	item_file.c item_file.h \
	log_handle.c log_handle.h \
	nk2export.c \
	nk2tools_i18n.h \
	nk2input.c nk2input.h \
	nk2tools_getopt.c nk2tools_getopt.h \
	nk2tools_libbfio.h \
	nk2tools_libcerror.h \
	nk2tools_libcfile.h \
	nk2tools_libcpath.h \
	nk2tools_libclocale.h \
	nk2tools_libcnotify.h \
	nk2tools_libfdatetime.h \
	nk2tools_libfguid.h \
	nk2tools_libfmapi.h \
	nk2tools_libfvalue.h \
	nk2tools_libfwnt.h \
	nk2tools_libnk2.h \
	nk2tools_libuna.h \
	nk2tools_output.c nk2tools_output.h \
	nk2tools_signal.c nk2tools_signal.h \
	nk2tools_unused.h

nk2export_LDADD = \
	@LIBFMAPI_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@LIBFWNT_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

nk2info_SOURCES = \
	info_handle.c info_handle.h \
	nk2info.c \
	nk2input.c nk2input.h \
	nk2tools_getopt.c nk2tools_getopt.h \
	nk2tools_i18n.h \
	nk2tools_libbfio.h \
	nk2tools_libcerror.h \
	nk2tools_libclocale.h \
	nk2tools_libcnotify.h \
	nk2tools_libfdatetime.h \
	nk2tools_libfguid.h \
	nk2tools_libfmapi.h \
	nk2tools_libfwnt.h \
	nk2tools_libnk2.h \
	nk2tools_libuna.h \
	nk2tools_output.c nk2tools_output.h \
	nk2tools_signal.c nk2tools_signal.h \
	nk2tools_unused.h

nk2info_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on nk2export ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(nk2export_SOURCES)
	@echo "Running splint on nk2info ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(nk2info_SOURCES)


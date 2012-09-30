AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBNK2_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	nk2export \
	nk2info

nk2export_SOURCES = \
	export_handle.c export_handle.h \
	log_handle.c log_handle.h \
	nk2export.c \
	nk2input.c nk2input.h \
	nk2output.c nk2output.h \
	nk2tools_libfdatetime.h \
	nk2tools_libfguid.h \
	nk2tools_libnk2.h \
	nk2tools_libuna.h

nk2export_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

nk2info_SOURCES = \
	info_handle.c info_handle.h \
	nk2info.c \
	nk2input.c nk2input.h \
	nk2output.c nk2output.h \
	nk2tools_libfdatetime.h \
	nk2tools_libfguid.h \
	nk2tools_libnk2.h \
	nk2tools_libuna.h

nk2info_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
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


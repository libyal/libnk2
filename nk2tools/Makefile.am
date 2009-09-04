AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common -I$(top_srcdir)/liberror -I$(top_srcdir)/libsystem @LIBUNA_CPPFLAGS@ @LIBBFIO_CPPFLAGS@ @MEMWATCH_CPPFLAGS@ @LIBNK2_DLL_IMPORT@
AM_LDFLAGS  = @STATIC_LDFLAGS@

bin_PROGRAMS = nk2export nk2info

nk2export_SOURCES = \
	export_handle.c export_handle.h \
	filetime.c filetime.h \
	guid.c guid.h \
	nk2common.h \
	nk2export.c \
	nk2input.c nk2input.h \
	nk2output.c nk2output.h

nk2export_LDADD   = ../liberror/liberror.la ../libnk2/libnk2.la ../libsystem/libsystem.la @MEMWATCH_LIBADD@

nk2info_SOURCES = \
	guid.c guid.h \
	nk2common.h \
	nk2info.c \
	nk2output.c nk2output.h

nk2info_LDADD   = ../liberror/liberror.la ../libnk2/libnk2.la ../libsystem/libsystem.la @MEMWATCH_LIBADD@

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on nk2info ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(nk2info_SOURCES) 


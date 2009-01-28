AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common -I$(top_srcdir)/liberror @LIBUNA_CPPFLAGS@ @LIBBFIO_CPPFLAGS@ @MEMWATCH_CPPFLAGS@

bin_PROGRAMS = nk2info

nk2info_SOURCES = \
	character_string.c character_string.h \
	date_time.c date_time.h \
	directory_io.h \
	error_string.c error_string.h \
	file_io.c file_io.h \
	file_stream_io.h \
	glob.c glob.h \
	guid.c guid.h \
	notify.c notify.h \
	nk2common.c nk2common.h \
	nk2getopt.c nk2getopt.h \
	nk2info.c \
	nk2output.c nk2output.h \
	nk2signal.c nk2signal.h \
	string_conversion.c string_conversion.h \
	system_string.c system_string.h

nk2info_LDADD   = ../liberror/liberror.la ../libnk2/libnk2.la @MEMWATCH_LIBADD@

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on nk2info ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(nk2info_SOURCES) 


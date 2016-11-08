if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

pyexec_LTLIBRARIES = pynk2.la

pynk2_la_SOURCES = \
	pynk2.c pynk2.h \
	pynk2_codepage.c pynk2_codepage.h \
	pynk2_error.c pynk2_error.h \
	pynk2_file.c pynk2_file.h \
	pynk2_file_object_io_handle.c pynk2_file_object_io_handle.h \
	pynk2_integer.c pynk2_integer.h \
	pynk2_libbfio.h \
	pynk2_libcerror.h \
	pynk2_libclocale.h \
	pynk2_libnk2.h \
	pynk2_python.h \
	pynk2_unused.h

pynk2_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pynk2_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pynk2_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile


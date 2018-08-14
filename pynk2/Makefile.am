if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBNK2_DLL_IMPORT@

pyexec_LTLIBRARIES = pynk2.la

pynk2_la_SOURCES = \
	pynk2.c pynk2.h \
	pynk2_codepage.c pynk2_codepage.h \
	pynk2_datetime.c pynk2_datetime.h \
	pynk2_error.c pynk2_error.h \
	pynk2_file.c pynk2_file.h \
	pynk2_file_object_io_handle.c pynk2_file_object_io_handle.h \
	pynk2_guid.c pynk2_guid.h \
	pynk2_integer.c pynk2_integer.h \
	pynk2_item.c pynk2_item.h \
	pynk2_items.c pynk2_items.h \
	pynk2_libbfio.h \
	pynk2_libcerror.h \
	pynk2_libclocale.h \
	pynk2_libfguid.h \
	pynk2_libnk2.h \
	pynk2_record_entries.c pynk2_record_entries.h \
	pynk2_record_entry.c pynk2_record_entry.h \
	pynk2_python.h \
	pynk2_unused.h

pynk2_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

pynk2_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pynk2_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile


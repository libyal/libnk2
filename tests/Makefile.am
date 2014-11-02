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
	@LIBNK2_DLL_IMPORT@

TESTS = \
	test_set_ascii_codepage.sh \
	test_open_close.sh \
	test_nk2info.sh \
	test_nk2export.sh

check_SCRIPTS = \
	test_nk2export.sh \
	test_nk2info.sh \
	test_open_close.sh \
	test_runner.sh \
	test_set_ascii_codepage.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS =  \
	nk2_test_open_close \
	nk2_test_set_ascii_codepage

nk2_test_open_close_SOURCES = \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_libcstring.h \
	nk2_test_open_close.c

nk2_test_open_close_LDADD = \
	../libnk2/libnk2.la \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

nk2_test_set_ascii_codepage_SOURCES = \
	nk2_test_libcerror.h \
	nk2_test_libclocale.h \
	nk2_test_libnk2.h \
	nk2_test_libcstring.h \
	nk2_test_set_ascii_codepage.c

nk2_test_set_ascii_codepage_LDADD = \
	../libnk2/libnk2.la \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile


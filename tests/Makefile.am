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
	@LIBNK2_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYNK2 = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_nk2info.sh \
	test_nk2export.sh \
	$(TESTS_PYNK2)

check_SCRIPTS = \
	pynk2_test_support.py \
	test_library.sh \
	test_nk2export.sh \
	test_nk2info.sh \
	test_python_module.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	nk2_test_error \
	nk2_test_file \
	nk2_test_io_handle \
	nk2_test_item \
	nk2_test_notify \
	nk2_test_record_entry \
	nk2_test_support

nk2_test_error_SOURCES = \
	nk2_test_error.c \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_unused.h

nk2_test_error_LDADD = \
	../libnk2/libnk2.la

nk2_test_file_SOURCES = \
	nk2_test_file.c \
	nk2_test_getopt.c nk2_test_getopt.h \
	nk2_test_libcerror.h \
	nk2_test_libclocale.h \
	nk2_test_libcnotify.h \
	nk2_test_libnk2.h \
	nk2_test_libuna.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h

nk2_test_file_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

nk2_test_io_handle_SOURCES = \
	nk2_test_io_handle.c \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_unused.h

nk2_test_io_handle_LDADD = \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_item_SOURCES = \
	nk2_test_item.c \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_unused.h

nk2_test_item_LDADD = \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_notify_SOURCES = \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_notify.c \
	nk2_test_unused.h

nk2_test_notify_LDADD = \
	../libnk2/libnk2.la

nk2_test_record_entry_SOURCES = \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_record_entry.c \
	nk2_test_unused.h

nk2_test_record_entry_LDADD = \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_support_SOURCES = \
	nk2_test_getopt.c nk2_test_getopt.h \
	nk2_test_libbfio.h \
	nk2_test_libcerror.h \
	nk2_test_libclocale.h \
	nk2_test_libcnotify.h \
	nk2_test_libnk2.h \
	nk2_test_libuna.h \
	nk2_test_macros.h \
	nk2_test_support.c

nk2_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile


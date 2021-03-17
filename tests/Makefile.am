AUTOMAKE_OPTIONS = subdir-objects

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

if HAVE_PYTHON_TESTS
TESTS_PYNK2 = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_nk2info.sh \
	test_nk2export.sh \
	$(TESTS_PYNK2)

check_SCRIPTS = \
	pynk2_test_file.py \
	pynk2_test_support.py \
	test_library.sh \
	test_manpage.sh \
	test_nk2export.sh \
	test_nk2info.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	nk2_test_error \
	nk2_test_file \
	nk2_test_file_footer \
	nk2_test_file_header \
	nk2_test_io_handle \
	nk2_test_item \
	nk2_test_mapi_value \
	nk2_test_notify \
	nk2_test_record_entry \
	nk2_test_support \
	nk2_test_tools_info_handle \
	nk2_test_tools_output \
	nk2_test_tools_signal

nk2_test_error_SOURCES = \
	nk2_test_error.c \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_unused.h

nk2_test_error_LDADD = \
	../libnk2/libnk2.la

nk2_test_file_SOURCES = \
	nk2_test_file.c \
	nk2_test_functions.c nk2_test_functions.h \
	nk2_test_getopt.c nk2_test_getopt.h \
	nk2_test_libbfio.h \
	nk2_test_libcerror.h \
	nk2_test_libclocale.h \
	nk2_test_libcnotify.h \
	nk2_test_libnk2.h \
	nk2_test_libuna.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_unused.h

nk2_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

nk2_test_file_footer_SOURCES = \
	nk2_test_file_footer.c \
	nk2_test_functions.c nk2_test_functions.h \
	nk2_test_libbfio.h \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_unused.h

nk2_test_file_footer_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_file_header_SOURCES = \
	nk2_test_file_header.c \
	nk2_test_functions.c nk2_test_functions.h \
	nk2_test_libbfio.h \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_unused.h

nk2_test_file_header_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

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
	nk2_test_libbfio.h \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_unused.h

nk2_test_item_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_mapi_value_SOURCES = \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_mapi_value.c \
	nk2_test_unused.h

nk2_test_mapi_value_LDADD = \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_notify_SOURCES = \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_notify.c \
	nk2_test_unused.h

nk2_test_notify_LDADD = \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_record_entry_SOURCES = \
	nk2_test_functions.c nk2_test_functions.h \
	nk2_test_libbfio.h \
	nk2_test_libcerror.h \
	nk2_test_libnk2.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_record_entry.c \
	nk2_test_unused.h

nk2_test_record_entry_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_support_SOURCES = \
	nk2_test_functions.c nk2_test_functions.h \
	nk2_test_getopt.c nk2_test_getopt.h \
	nk2_test_libbfio.h \
	nk2_test_libcerror.h \
	nk2_test_libclocale.h \
	nk2_test_libcnotify.h \
	nk2_test_libnk2.h \
	nk2_test_libuna.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_support.c \
	nk2_test_unused.h

nk2_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_tools_info_handle_SOURCES = \
	../nk2tools/info_handle.c ../nk2tools/info_handle.h \
	../nk2tools/nk2input.c ../nk2tools/nk2input.h \
	nk2_test_libcerror.h \
	nk2_test_macros.h \
	nk2_test_memory.c nk2_test_memory.h \
	nk2_test_tools_info_handle.c \
	nk2_test_unused.h

nk2_test_tools_info_handle_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_tools_output_SOURCES = \
	../nk2tools/nk2tools_output.c ../nk2tools/nk2tools_output.h \
	nk2_test_libcerror.h \
	nk2_test_macros.h \
	nk2_test_tools_output.c \
	nk2_test_unused.h

nk2_test_tools_output_LDADD = \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

nk2_test_tools_signal_SOURCES = \
	../nk2tools/nk2tools_signal.c ../nk2tools/nk2tools_signal.h \
	nk2_test_libcerror.h \
	nk2_test_macros.h \
	nk2_test_tools_signal.c \
	nk2_test_unused.h

nk2_test_tools_signal_LDADD = \
	../libnk2/libnk2.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile


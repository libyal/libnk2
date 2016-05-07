MSVSCPP_FILES = \
	libbfio/libbfio.vcproj \
	libcdata/libcdata.vcproj \
	libcerror/libcerror.vcproj \
	libcfile/libcfile.vcproj \
	libclocale/libclocale.vcproj \
	libcnotify/libcnotify.vcproj \
	libcpath/libcpath.vcproj \
	libcsplit/libcsplit.vcproj \
	libcstring/libcstring.vcproj \
	libcsystem/libcsystem.vcproj \
	libcthreads/libcthreads.vcproj \
	libfdatetime/libfdatetime.vcproj \
	libfguid/libfguid.vcproj \
	libfmapi/libfmapi.vcproj \
	libfvalue/libfvalue.vcproj \
	libfwnt/libfwnt.vcproj \
	libnk2/libnk2.vcproj \
	libuna/libuna.vcproj \
	nk2_test_get_version/nk2_test_get_version.vcproj \
	nk2_test_open_close/nk2_test_open_close.vcproj \
	nk2_test_set_ascii_codepage/nk2_test_set_ascii_codepage.vcproj \
	nk2export/nk2export.vcproj \
	nk2info/nk2info.vcproj \
	libnk2.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile


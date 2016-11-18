include_HEADERS = \
	libnk2.h

pkginclude_HEADERS = \
	libnk2/codepage.h \
	libnk2/definitions.h \
	libnk2/error.h \
	libnk2/extern.h \
	libnk2/features.h \
	libnk2/mapi.h \
	libnk2/types.h

EXTRA_DIST = \
	libnk2.h.in \
	libnk2/definitions.h.in \
	libnk2/features.h.in \
	libnk2/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libnk2.h
	/bin/rm -f libnk2/definitions.h
	/bin/rm -f libnk2/features.h
	/bin/rm -f libnk2/types.h
	/bin/rm -f Makefile


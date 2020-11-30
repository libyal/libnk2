#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libnk2/.libs/libnk2.1.dylib && test -f ./pynk2/.libs/pynk2.so;
then
	install_name_tool -change /usr/local/lib/libnk2.1.dylib ${PWD}/libnk2/.libs/libnk2.1.dylib ./pynk2/.libs/pynk2.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};


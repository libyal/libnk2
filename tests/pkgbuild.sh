#!/bin/sh
# Script to build a MacOS pkg
#
# Version: 20201121

set -e

make install DESTDIR=${PWD}/osx-pkg
mkdir -p ${PWD}/osx-pkg/usr/share/doc/libnk2
cp AUTHORS COPYING COPYING.LESSER NEWS README ${PWD}/osx-pkg/usr/share/doc/libnk2

VERSION=`sed '5!d; s/^ \[//;s/\],$//' configure.ac`
pkgbuild --root osx-pkg --identifier com.github.libyal.libnk2 --version ${VERSION} --ownership recommended ../libnk2-${VERSION}.pkg


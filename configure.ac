AC_PREREQ( 2.59 )

AC_INIT(
 [libnk2],
 [20111004],
 [jbmetz@users.sourceforge.net])

AC_CONFIG_SRCDIR(
 [include/libnk2.h.in])

AM_INIT_AUTOMAKE([gnu 1.6])

AC_CONFIG_MACRO_DIR([m4])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for libtool DLL support
AC_LIBTOOL_WIN32_DLL

dnl Checks for programs
AC_PROG_CC
AC_PROG_GCC_TRADITIONAL
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl Support of internationalization (i18n)
AM_GNU_GETTEXT([external])

dnl Check for compiler language support
AC_C_CONST
AC_C_VOLATILE

dnl Check if WINAPI support should be enabled
AX_COMMON_CHECK_ENABLE_WINAPI

dnl Check for type definitions
AX_TYPES_CHECK_LOCAL

dnl Check if wide character type should be enabled
AX_COMMON_CHECK_ENABLE_WIDE_CHARACTER_TYPE

dnl Check for headers

dnl Check for functions

dnl Checks for libraries and library functions
dnl ac_libnk2_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments
AX_COMMON_CHECK_LOCAL
AX_LIBCSTRING_CHECK_LOCAL
AX_LIBERROR_CHECK_LOCAL
AX_LIBNOTIFY_CHECK_LOCAL
AX_LIBSYSTEM_CHECK_LOCAL

dnl Check for enabling libuna for Unicode string support
AX_LIBUNA_CHECK_ENABLE

dnl Check for enabling libbfio for basic file IO support
AX_LIBBFIO_CHECK_ENABLE

dnl Check for enabling libfdatetime for file date and time support
AX_COMMON_ARG_WITH(
 [libfdatetime],
 [libfdatetime],
 [search for libfdatetime in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])

AC_CHECK_LIBFDATETIME

AS_IF(
 [test "x$ac_cv_libfdatetime" = xyes],
 [AC_SUBST(
  [ax_libfdatetime_pc_libs_private],
  [-lfdatetime])
 ])

AS_IF(
 [test "x$ac_cv_libfdatetime" = xyes],
 [AC_SUBST(
  [ax_libfdatetime_spec_requires],
  [libfdatetime])
 AC_SUBST(
  [ax_libfdatetime_spec_build_requires],
  [libfdatetime-devel])
 ])

AS_IF(
 [test "x$ac_cv_libfdatetime" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBFDATETIME],
  [1],
  [Define to 1 if the local version of libfdatetime is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBFDATETIME],
  [1])
 AC_SUBST(
  [LIBFDATETIME_CPPFLAGS],
  [-I../libfdatetime])
 AC_SUBST(
  [LIBFDATETIME_LIBADD],
  [../libfdatetime/libfdatetime.la])
 ac_cv_libfdatetime=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBFDATETIME],
 [test "x$ac_cv_libfdatetime" = xlocal])

dnl Check for enabling libfguid for file GUID/UUID support
AX_COMMON_ARG_WITH(
 [libfguid],
 [libfguid],
 [search for libfguid in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])

AC_CHECK_LIBFGUID

AS_IF(
 [test "x$ac_cv_libfguid" = xyes],
 [AC_SUBST(
  [ax_libfguid_pc_libs_private],
  [-lfguid])
 ])

AS_IF(
 [test "x$ac_cv_libfguid" = xyes],
 [AC_SUBST(
  [ax_libfguid_spec_requires],
  [libfguid])
 AC_SUBST(
  [ax_libfguid_spec_build_requires],
  [libfguid-devel])
 ])

AS_IF(
 [test "x$ac_cv_libfguid" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBFGUID],
  [1],
  [Define to 1 if the local version of libfguid is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBFGUID],
  [1])
 AC_SUBST(
  [LIBFGUID_CPPFLAGS],
  [-I../libfguid])
 AC_SUBST(
  [LIBFGUID_LIBADD],
  [../libfguid/libfguid.la])
 ac_cv_libfguid=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBFGUID],
 [test "x$ac_cv_libfguid" = xlocal])

dnl Check for enabling libfvalue for file value support
AX_COMMON_ARG_WITH(
 [libfvalue],
 [libfvalue],
 [search for libfvalue in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])

AC_CHECK_LIBFVALUE

AS_IF(
 [test "x$ac_cv_libfvalue" = xyes],
 [AC_SUBST(
  [ax_libfvalue_pc_libs_private],
  [-lfvalue])
 ])

AS_IF(
 [test "x$ac_cv_libfvalue" = xyes],
 [AC_SUBST(
  [ax_libfvalue_spec_requires],
  [libfvalue])
 AC_SUBST(
  [ax_libfvalue_spec_build_requires],
  [libfvalue-devel])
 ])

AS_IF(
 [test "x$ac_cv_libfvalue" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBFVALUE],
  [1],
  [Define to 1 if the local version of libfvalue is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBFVALUE],
  [1])
 AC_SUBST(
  [LIBFVALUE_CPPFLAGS],
  [-I../libfvalue])
 AC_SUBST(
  [LIBFVALUE_LIBADD],
  [../libfvalue/libfvalue.la])
 ac_cv_libfvalue=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBFVALUE],
 [test "x$ac_cv_libfvalue" = xlocal])

dnl Check for enabling libfwnt for file Windows NT type support
AX_COMMON_ARG_WITH(
 [libfwnt],
 [libfwnt],
 [search for libfwnt in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])

AC_CHECK_LIBFWNT

AS_IF(
 [test "x$ac_cv_libfwnt" = xyes],
 [AC_SUBST(
  [ax_libfwnt_pc_libs_private],
  [-lfvalue])
 ])

AS_IF(
 [test "x$ac_cv_libfwnt" = xyes],
 [AC_SUBST(
  [ax_libfwnt_spec_requires],
  [libfvalue])
 AC_SUBST(
  [ax_libfwnt_spec_build_requires],
  [libfvalue-devel])
 ])

AS_IF(
 [test "x$ac_cv_libfwnt" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBFWNT],
  [1],
  [Define to 1 if the local version of libfwnt is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBFWNT],
  [1])
 AC_SUBST(
  [LIBFWNT_CPPFLAGS],
  [-I../libfwnt])
 AC_SUBST(
  [LIBFWNT_LIBADD],
  [../libfwnt/libfwnt.la])
 ac_cv_libfwnt=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBFWNT],
 [test "x$ac_cv_libfwnt" = xlocal])

dnl Check for enabling libfmapi for file MAPI types support
AX_COMMON_ARG_WITH(
 [libfmapi],
 [libfmapi],
 [search for libfmapi in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])

AC_CHECK_LIBFMAPI

AS_IF(
 [test "x$ac_cv_libfmapi" = xyes],
 [AC_SUBST(
  [ax_libfwnt_pc_libs_private],
  [-lfvalue])
 ])

AS_IF(
 [test "x$ac_cv_libfmapi" = xyes],
 [AC_SUBST(
  [ax_libfwnt_spec_requires],
  [libfvalue])
 AC_SUBST(
  [ax_libfwnt_spec_build_requires],
  [libfvalue-devel])
 ])

AS_IF(
 [test "x$ac_cv_libfmapi" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBFMAPI],
  [1],
  [Define to 1 if the local version of libfmapi is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBFMAPI],
  [1])
 AC_SUBST(
  [LIBFMAPI_CPPFLAGS],
  [-I../libfmapi])
 AC_SUBST(
  [LIBFMAPI_LIBADD],
  [../libfmapi/libfmapi.la])
 ac_cv_libfmapi=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBFMAPI],
 [test "x$ac_cv_libfmapi" = xlocal])

dnl Check if nk2tools should be build as static executables
AX_COMMON_CHECK_ENABLE_STATIC_EXECUTABLES

dnl Check if libnk2 should be build with verbose output
AX_COMMON_CHECK_ENABLE_VERBOSE_OUTPUT

dnl Check if libnk2 should be build with debug output
AX_COMMON_CHECK_ENABLE_DEBUG_OUTPUT

dnl Check if requires and build requires should be set in spec file
AS_IF(
 [test "x$ac_cv_have_libuna" = xyes || test "x$ac_cv_have_libbfio" = xyes || test "x$ac_cv_have_libfdatetime" = xyes || test "x$ac_cv_have_libfguid" = xyes || test "x$ac_cv_have_libfvalue" = xyes || test "x$ac_cv_have_libfwnt" = xyes || test "x$ac_cv_have_libfmapi" = xyes],
 [AC_SUBST(
  [libnk2_spec_requires],
  [Requires:])
 AC_SUBST(
  [libnk2_spec_build_requires],
  [BuildRequires:])
 ])

dnl Set memwatch support
ac_cv_enable_memwatch=no

AS_IF(
 [test "x$ac_cv_enable_memwatch" != xno ],
 [AC_SUBST(
  [MEMWATCH_CPPFLAGS],
  ["-DMEMWATCH -DMEMWATCH_STDIO"])
 AC_SUBST(
  [MEMWATCH_LIBADD],
  [../common/libmemwatch.la]) ])

AM_CONDITIONAL(
 [HAVE_MEMWATCH],
 [test "x$ac_cv_enable_memwatch" != xno])

dnl Set additional compiler flags
CFLAGS="$CFLAGS -Wall";

dnl Check if DLL support is needed in nk2tools
AS_IF(
 [test "x$enable_shared" = xyes],
 [AS_CASE(
  [$host],
  [*cygwin* | *mingw*],
  [AC_SUBST(
   [LIBNK2_DLL_IMPORT],
   ["-DLIBNK2_DLL_IMPORT"])
  ])
 ])

dnl Have configure make the Makefiles
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([common/Makefile])
AC_CONFIG_FILES([libcstring/Makefile])
AC_CONFIG_FILES([liberror/Makefile])
AC_CONFIG_FILES([libnotify/Makefile])
AC_CONFIG_FILES([libuna/Makefile])
AC_CONFIG_FILES([libbfio/Makefile])
AC_CONFIG_FILES([libfdatetime/Makefile])
AC_CONFIG_FILES([libfguid/Makefile])
AC_CONFIG_FILES([libfvalue/Makefile])
AC_CONFIG_FILES([libfwnt/Makefile])
AC_CONFIG_FILES([libfmapi/Makefile])
AC_CONFIG_FILES([libnk2/Makefile])
AC_CONFIG_FILES([libsystem/Makefile])
AC_CONFIG_FILES([nk2tools/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([po/Makevars])
AC_CONFIG_FILES([manuals/Makefile])
AC_CONFIG_FILES([tests/Makefile])
AC_CONFIG_FILES([examples/Makefile])
AC_CONFIG_FILES([macosx/Makefile])
AC_CONFIG_FILES([msvscpp/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/libnk2.h])
AC_CONFIG_FILES([include/libnk2/definitions.h])
AC_CONFIG_FILES([include/libnk2/features.h])
AC_CONFIG_FILES([include/libnk2/types.h])
AC_CONFIG_FILES([libnk2/libnk2_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([common/types.h])
AC_CONFIG_FILES([libnk2/libnk2.rc])
AC_CONFIG_FILES([macosx/Introduction.rtf])
AC_CONFIG_FILES([libnk2.pc])
AC_CONFIG_FILES([libnk2.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

dnl Print a summary
AC_MSG_NOTICE([
Building:
   libuna support:                           $ac_cv_have_libuna
   libbfio support:                          $ac_cv_have_libbfio
   libfdatetime support:                     $ac_cv_have_libfdatetime
   libfguid support:                         $ac_cv_have_libfguid
   libfvalue support:                        $ac_cv_have_libfvalue
   libfwnt support:                          $ac_cv_have_libfwnt
   libfmapi support:                         $ac_cv_have_libfmapi

Features:
   Wide character type support:              $ac_cv_enable_wide_character_type
   nk2tools are build as static executables: $ac_cv_enable_static_executables
   Verbose output:                           $ac_cv_enable_verbose_output
   Debug output:                             $ac_cv_enable_debug_output
]);



dnl Checks for required headers and functions
dnl
dnl Version: 20200713

dnl Function to detect if libnk2 dependencies are available
AC_DEFUN([AX_LIBNK2_CHECK_LOCAL],
  [dnl Check for internationalization functions in libnk2/libnk2_i18n.c
  AC_CHECK_FUNCS([bindtextdomain])
])

dnl Function to detect if nk2tools dependencies are available
AC_DEFUN([AX_NK2TOOLS_CHECK_LOCAL],
  [AC_CHECK_HEADERS([signal.h sys/signal.h unistd.h])

  AC_CHECK_FUNCS([close getopt setvbuf])

  AS_IF(
   [test "x$ac_cv_func_close" != xyes],
   [AC_MSG_FAILURE(
     [Missing function: close],
     [1])
  ])

  dnl Headers included in nk2tools/log_handle.c
  AC_CHECK_HEADERS([stdarg.h varargs.h])

  AS_IF(
    [test "x$ac_cv_header_stdarg_h" != xyes && test "x$ac_cv_header_varargs_h" != xyes],
    [AC_MSG_FAILURE(
      [Missing headers: stdarg.h and varargs.h],
      [1])
  ])
])

dnl Function to check if DLL support is needed
AC_DEFUN([AX_LIBNK2_CHECK_DLL_SUPPORT],
  [AS_IF(
    [test "x$enable_shared" = xyes && test "x$ac_cv_enable_static_executables" = xno],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw* | *msys*],
      [AC_DEFINE(
        [HAVE_DLLMAIN],
        [1],
        [Define to 1 to enable the DllMain function.])
      AC_SUBST(
        [HAVE_DLLMAIN],
        [1])

      AC_SUBST(
        [LIBNK2_DLL_EXPORT],
        ["-DLIBNK2_DLL_EXPORT"])

      AC_SUBST(
        [LIBNK2_DLL_IMPORT],
        ["-DLIBNK2_DLL_IMPORT"])
      ])
    ])
  ])


dnl Function to detect if libnk2 dependencies are available
AC_DEFUN([AX_LIBNK2_CHECK_LOCAL],
 [dnl Check for internationalization functions in libnk2/libnk2_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])


dnl Function to test if a certain feature was enabled
AC_DEFUN([COMMON_ARG_ENABLE],
 [AC_ARG_ENABLE(
  [$1],
  [AS_HELP_STRING(
   [--enable-$1],
   [$3 [default is $4]])],
  [ac_cv_enable_$2=$enableval],
  [ac_cv_enable_$2=$4])dnl
  AC_CACHE_CHECK(
   [whether to enable $3],
   [ac_cv_enable_$2],
   [ac_cv_enable_$2=$4])dnl
 ])

dnl Function to test if the location of a certain feature was provided
AC_DEFUN([COMMON_ARG_WITH],
 [AC_ARG_WITH(
  [$1],
  [AS_HELP_STRING(
   [--with-$1=[$5]],
   [$3 [default is $4]])],
  [ac_cv_with_$2=$withval],
  [ac_cv_with_$2=$4])dnl
  AC_CACHE_CHECK(
   [whether to use $3],
   [ac_cv_with_$2],
   [ac_cv_with_$2=$4])dnl
 ])


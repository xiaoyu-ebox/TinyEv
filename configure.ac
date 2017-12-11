#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TinyEv], [1.0], [xiaoyu_ebox@163.com])
AM_INIT_AUTOMAKE(TinyEv,1.0)
AC_CONFIG_SRCDIR([src/Ev_Timer.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SSIZE_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([clock_gettime gettimeofday localtime_r memset socket])

AC_CONFIG_FILES([Makefile src/Makefile daemon/Makefile example/Makefile])
AC_OUTPUT

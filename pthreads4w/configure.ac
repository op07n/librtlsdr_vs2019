# configure.ac
# --------------------------------------------------------------------------
#
 *      Pthreads4w - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999-2018, Pthreads4w contributors
 *
 *      Homepage: https://sourceforge.net/projects/pthreads4w/
 *
 *      The current list of contributors is contained
 *      in the file CONTRIBUTORS included with the source
 *      code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      https://sourceforge.net/p/pthreads4w/wiki/Contributors/
 *
 * This file is part of Pthreads4w.
 *
 *    Pthreads4w is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Pthreads4w is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Pthreads4w.  If not, see <http://www.gnu.org/licenses/>. *
#
AC_INIT([pthreads4w],[git])
AC_CONFIG_HEADERS([config.h])

# Checks for build tools.
#
AC_PROG_CC
AC_PROG_CXX
AC_CHECK_TOOLS([AR],[ar],[ar])
AC_CHECK_TOOLS([DLLTOOL],[dlltool],[dlltool])
AC_CHECK_TOOLS([OBJDUMP],[objdump],[objdump])
AC_CHECK_TOOLS([RC],[windres],[windres])
AC_PROG_RANLIB

# Autoconf doesn't normally guard config.h, but we prefer it so;
# this is also a convenient place to force HAVE_C_INLINE, because
# AC_C_INLINE makes it available, even if the build compiler does
# not normally support it.
#
AH_TOP(dnl
[#ifndef PTW32_CONFIG_H]
[#define PTW32_CONFIG_H]dnl
)
# FIXME: AC_C_INLINE defines 'inline' to work with any C compiler,
# whether or not it supports inline code expansion, but it does NOT
# define HAVE_C_INLINE; can we use this standard autoconf feature,
# without also needing to define HAVE_C_INLINE?
#
AC_C_INLINE
AH_BOTTOM([#define HAVE_C_INLINE])
AH_BOTTOM([#endif])

# Checks for data types and structures.
#
PTW32_AC_CHECK_TYPEDEF([mode_t])
PTW32_AC_CHECK_TYPEDEF([sigset_t],[signal.h])
PTW32_AC_CHECK_TYPEDEF([struct timespec],[time.h])

# Checks for __cdecl functions.
#
PTW32_AC_NEED_ERRNO
PTW32_AC_NEED_FUNC([NEED_CALLOC],[calloc])
PTW32_AC_NEED_FUNC([NEED_CREATETHREAD],[_beginthreadex])
PTW32_AC_CHECK_CPU_AFFINITY

# WinAPI functions need a full argument list for detection.
#
PTW32_AC_NEED_WINAPI_FUNC([DuplicateHandle],[NULL,NULL,NULL,NULL,0,0,0])

# Checks for installation tools.
#
AC_PROG_MKDIR_P
AC_PROG_INSTALL

# Build system generation, as configured.
#
AC_CONFIG_FILES([GNUmakefile tests/GNUmakefile])
AC_OUTPUT

/*
 * pthread_getw32threadhandle_np.c
 *
 * Description:
 * This translation unit implements non-portable thread functions.
 *
 * --------------------------------------------------------------------------
 *
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
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "pthread.h"
#include "implement.h"

/*
 * pthread_getw32threadhandle_np()
 *
 * Returns the win32 thread handle that the POSIX
 * thread "thread" is running as.
 *
 * Applications can use the win32 handle to set
 * win32 specific attributes of the thread.
 */
HANDLE
pthread_getw32threadhandle_np (pthread_t thread)
{
  return ((ptw32_thread_t *)thread.p)->threadH;
}

/*
 * pthread_getw32threadid_np()
 *
 * Returns the win32 thread id that the POSIX
 * thread "thread" is running as.
 */
DWORD
pthread_getw32threadid_np (pthread_t thread)
{
  return ((ptw32_thread_t *)thread.p)->thread;
}

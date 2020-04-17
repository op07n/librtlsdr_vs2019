/* 
 * mutex4.c
 *
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
 *
 * --------------------------------------------------------------------------
 *
 * Thread A locks mutex - thread B tries to unlock.
 *
 * Depends on API functions: 
 *	pthread_mutex_lock()
 *	pthread_mutex_trylock()
 *	pthread_mutex_unlock()
 */

#include "test.h"

static int wasHere = 0;

static pthread_mutex_t mutex1;
 
void * unlocker(void * arg)
{
  int expectedResult = (int)(size_t)arg;

  wasHere++;
  assert(pthread_mutex_unlock(&mutex1) == expectedResult);
  wasHere++;
  return NULL;
}
 
int
main()
{
  pthread_t t;
  pthread_mutexattr_t ma;

  assert(pthread_mutexattr_init(&ma) == 0);

  BEGIN_MUTEX_STALLED_ROBUST(ma)

  wasHere = 0;
  assert(pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_DEFAULT) == 0);
  assert(pthread_mutex_init(&mutex1, &ma) == 0);
  assert(pthread_mutex_lock(&mutex1) == 0);
  assert(pthread_create(&t, NULL, unlocker, (void *)(size_t)(IS_ROBUST?EPERM:0)) == 0);
  assert(pthread_join(t, NULL) == 0);
  assert(pthread_mutex_unlock(&mutex1) == 0);
  assert(wasHere == 2);

  wasHere = 0;
  assert(pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_NORMAL) == 0);
  assert(pthread_mutex_init(&mutex1, &ma) == 0);
  assert(pthread_mutex_lock(&mutex1) == 0);
  assert(pthread_create(&t, NULL, unlocker, (void *)(size_t)(IS_ROBUST?EPERM:0)) == 0);
  assert(pthread_join(t, NULL) == 0);
  assert(pthread_mutex_unlock(&mutex1) == 0);
  assert(wasHere == 2);

  wasHere = 0;
  assert(pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_ERRORCHECK) == 0);
  assert(pthread_mutex_init(&mutex1, &ma) == 0);
  assert(pthread_mutex_lock(&mutex1) == 0);
  assert(pthread_create(&t, NULL, unlocker, (void *)(size_t) EPERM) == 0);
  assert(pthread_join(t, NULL) == 0);
  assert(pthread_mutex_unlock(&mutex1) == 0);
  assert(wasHere == 2);

  wasHere = 0;
  assert(pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_RECURSIVE) == 0);
  assert(pthread_mutex_init(&mutex1, &ma) == 0);
  assert(pthread_mutex_lock(&mutex1) == 0);
  assert(pthread_create(&t, NULL, unlocker, (void *)(size_t) EPERM) == 0);
  assert(pthread_join(t, NULL) == 0);
  assert(pthread_mutex_unlock(&mutex1) == 0);
  assert(wasHere == 2);

  END_MUTEX_STALLED_ROBUST(ma)

  return 0;
}
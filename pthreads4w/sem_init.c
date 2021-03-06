/*
 * -------------------------------------------------------------
 *
 * Module: sem_init.c
 *
 * Purpose:
 *	Semaphores aren't actually part of PThreads.
 *	They are defined by the POSIX Standard:
 *
 *		POSIX 1003.1-2001
 *
 * -------------------------------------------------------------
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
#include "semaphore.h"
#include "implement.h"

int
sem_init (sem_t * sem, int pshared, unsigned int value)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function initializes a semaphore. The
 *      initial value of the semaphore is 'value'
 *
 * PARAMETERS
 *      sem
 *              pointer to an instance of sem_t
 *
 *      pshared
 *              if zero, this semaphore may only be shared between
 *              threads in the same process.
 *              if nonzero, the semaphore can be shared between
 *              processes
 *
 *      value
 *              initial value of the semaphore counter
 *
 * DESCRIPTION
 *      This function initializes a semaphore. The
 *      initial value of the semaphore is set to 'value'.
 *
 * RESULTS
 *              0               successfully created semaphore,
 *              -1              failed, error in errno
 * ERRNO
 *              EINVAL          'sem' is not a valid semaphore, or
 *                              'value' >= SEM_VALUE_MAX
 *              ENOMEM          out of memory,
 *              ENOSPC          a required resource has been exhausted,
 *              ENOSYS          semaphores are not supported,
 *              EPERM           the process lacks appropriate privilege
 *
 * ------------------------------------------------------
 */
{
  int result = 0;
  sem_t s = NULL;

  if (pshared != 0)
    {
      /*
       * Creating a semaphore that can be shared between
       * processes
       */
      result = EPERM;
    }
  else if (value > (unsigned int)SEM_VALUE_MAX)
    {
      result = EINVAL;
    }
  else
    {
      s = (sem_t) calloc (1, sizeof (*s));

      if (NULL == s)
        {
          result = ENOMEM;
        }
      else
        {

          s->value = value;
          s->lock = NULL;

#if defined(NEED_SEM)

          s->sem = CreateEvent (NULL,
              PTW32_FALSE,	/* auto (not manual) reset */
              PTW32_FALSE,	/* initial state is unset */
              NULL);

          if (0 == s->sem)
            {
              result = ENOSPC;
            }
          else
            {
              s->leftToUnblock = 0;
            }

#else /* NEED_SEM */

          if ((s->sem = CreateSemaphore (NULL,	/* Always NULL */
              (long) 0,	/* Force threads to wait */
              (long) SEM_VALUE_MAX,	/* Maximum value */
              NULL)) == 0)	/* Name */
            {
              result = ENOSPC;
            }

#endif /* NEED_SEM */

          if (result != 0)
            {
              free(s);
            }
        }
    }

  if (result != 0)
    {
      PTW32_SET_ERRNO(result);
      return -1;
    }

  *sem = s;

  return 0;

}				/* sem_init */

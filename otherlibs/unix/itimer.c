/***********************************************************************/
/*                                                                     */
/*                                OCaml                                */
/*                                                                     */
/*            Xavier Leroy, projet Cristal, INRIA Rocquencourt         */
/*                                                                     */
/*  Copyright 1996 Institut National de Recherche en Informatique et   */
/*  en Automatique.  All rights reserved.  This file is distributed    */
/*  under the terms of the GNU Library General Public License, with    */
/*  the special exception on linking described in file ../../LICENSE.  */
/*                                                                     */
/***********************************************************************/

/* $Id$ */

#include <mlvalues.h>
#include <alloc.h>
#include <fail.h>
#include <memory.h>
#include "unixsupport.h"

#ifdef HAS_SETITIMER

#include <math.h>
#include <sys/time.h>

static void unix_set_timeval(struct timeval * tv, double d)
{
  double integr, frac;
  frac = modf(d, &integr);
  /* Round time up so that if d is small but not 0, we end up with
     a non-0 timeval. */
  tv->tv_sec = integr;
  tv->tv_usec = ceil(1e6 * frac);
  if (tv->tv_usec >= 1000000) { tv->tv_sec++; tv->tv_usec = 0; }
}

static value unix_convert_itimer_r(CAML_R, struct itimerval *tp)
{
#define Get_timeval(tv) (double) tv.tv_sec + (double) tv.tv_usec / 1e6
  value res = caml_alloc_small_r(ctx,Double_wosize * 2, Double_array_tag);
  Store_double_field(res, 0, Get_timeval(tp->it_interval));
  Store_double_field(res, 1, Get_timeval(tp->it_value));
  return res;
#undef Get_timeval
}

static int itimers[3] = { ITIMER_REAL, ITIMER_VIRTUAL, ITIMER_PROF };

CAMLprim value unix_setitimer_r(CAML_R, value which, value newval)
{
  struct itimerval new, old;
  unix_set_timeval(&new.it_interval, Double_field(newval, 0));
  unix_set_timeval(&new.it_value, Double_field(newval, 1));
  if (setitimer(itimers[Int_val(which)], &new, &old) == -1)
    uerror_r(ctx,"setitimer", Nothing);
  return unix_convert_itimer_r(ctx, &old);
}

CAMLprim value unix_getitimer_r(CAML_R, value which)
{
  struct itimerval val;
  if (getitimer(itimers[Int_val(which)], &val) == -1)
    uerror_r(ctx,"getitimer", Nothing);
  return unix_convert_itimer_r(ctx, &val);
}

#else

CAMLprim value unix_setitimer_r(CAML_R, value which, value newval)
{ caml_invalid_argument_r(ctx,"setitimer not implemented"); }
CAMLprim value unix_getitimer_r(CAML_R, value which)
{ caml_invalid_argument_r(ctx,"getitimer not implemented"); }

#endif

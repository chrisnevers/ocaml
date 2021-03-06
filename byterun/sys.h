/***********************************************************************/
/*                                                                     */
/*                                OCaml                                */
/*                                                                     */
/*            Xavier Leroy, projet Cristal, INRIA Rocquencourt         */
/*                                                                     */
/*  Copyright 1996 Institut National de Recherche en Informatique et   */
/*  en Automatique.  All rights reserved.  This file is distributed    */
/*  under the terms of the GNU Library General Public License, with    */
/*  the special exception on linking described in file ../LICENSE.     */
/*                                                                     */
/***********************************************************************/

/* $Id$ */

#ifndef CAML_SYS_H
#define CAML_SYS_H

#include "misc.h"
#include "context.h"

#define NO_ARG Val_int(0)

CAMLextern void caml_sys_error_r (CAML_R, value);
CAMLextern void caml_sys_io_error_r (CAML_R, value);
extern void caml_sys_init_r (CAML_R, char * exe_name, char ** argv);
CAMLextern value caml_sys_exit_r (CAML_R, value);

/* extern char * caml_exe_name; */

#endif /* CAML_SYS_H */

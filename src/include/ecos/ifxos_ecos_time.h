/****************************************************************************

         Copyright (c) 2021 MaxLinear, Inc.
         Copyright (c) 2009 Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

*****************************************************************************/
#ifndef _IFXOS_ECOS_TIME_H
#define _IFXOS_ECOS_TIME_H

#ifdef ECOS
/** \file
   This file contains eCos definitions for timer and wait handling.
*/

/** \defgroup IFXOS_TIME_ECOS Time and Wait (eCos).

   This Group contains the eCos time and wait definitions.

\ingroup IFXOS_LAYER_ECOS
*/

#ifdef __cplusplus
   extern "C" {
#endif

/* ============================================================================
   IFX eCos adaptation - Includes
   ========================================================================= */
#include "ifx_types.h"

/* ============================================================================
   IFX eCos adaptation - supported features
   ========================================================================= */
/** IFX eCos adaptation - support "sleep in us" */
#ifndef IFXOS_HAVE_TIME_SLEEP_US
#  define IFXOS_HAVE_TIME_SLEEP_US                1
#endif

/** IFX eCos adaptation - support "sleep in ms" */
#ifndef IFXOS_HAVE_TIME_SLEEP_MS
#  define IFXOS_HAVE_TIME_SLEEP_MS                1
#endif

/** IFX eCos adaptation - support "sleep in sec" */
#ifndef IFXOS_HAVE_TIME_SLEEP_SEC
#  define IFXOS_HAVE_TIME_SLEEP_SEC               1
#endif

/** IFX eCos adaptation - support "get elapsed time in ms" */
#ifndef IFXOS_HAVE_TIME_ELAPSED_TIME_GET_MS
#  define IFXOS_HAVE_TIME_ELAPSED_TIME_GET_MS     1
#endif

/** IFX eCos adaptation - support "get elapsed time in sec" */
#ifndef IFXOS_HAVE_TIME_ELAPSED_TIME_GET_SEC
#  define IFXOS_HAVE_TIME_ELAPSED_TIME_GET_SEC    1
#endif

/** IFX eCos adaptation - support "get system time in sec" */
#ifndef IFXOS_HAVE_TIME_SYS_TIME_GET
#  define IFXOS_HAVE_TIME_SYS_TIME_GET            1
#endif

#ifdef __cplusplus
}
#endif
#endif      /* #ifdef ECOS */
#endif      /* #ifndef _IFXOS_ECOS_TIME_H */


/****************************************************************************

         Copyright (c) 2021 MaxLinear, Inc.
         Copyright (c) 2009 Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

*****************************************************************************/
#ifndef _IFXOS_WIN32_COMMON_H
#define _IFXOS_WIN32_COMMON_H

#ifdef WIN32
/** \file
   This file contains common definitions used for the Win32 OS adaption.
*/

/** \defgroup IFXOS_IF_WIN32_APPL Defines for Win32 Application Adaptation

   This Group contains the Win32 specific definitions and function.

\par Win32 Application Endianess
   Under Win32 in user space the endianess is defined within the corresponding
   header file <endian.h>.
   The platform endianess is mapped to the internal used IFXOS endianess definitions.

\ingroup IFXOS_INTERFACE
*/

#ifdef __cplusplus
   extern "C" {
#endif

#ifndef _IFXOS_COMMON_H
#  error "missing IFXOS endian defines, include 'ifx_common.h' at first"
#endif

/* ============================================================================
   IFX Win32 adaptation - Includes
   ========================================================================= */

/* ============================================================================
   IFX Win32 adaptation - Macro definitions
   ========================================================================= */

/** \addtogroup IFXOS_IF_WIN32_APPL
@{ */


#ifndef _IFXOS_COMMON_H
#  error "missing IFXOS endian defines, include 'ifx_common.h' at first"
#endif

#define IFXOS_BYTE_ORDER                  IFXOS_LITTLE_ENDIAN

/** @} */

#ifdef __cplusplus
}
#endif
#endif      /* #ifdef WIN32 */
#endif      /* #ifndef _IFXOS_WIN32_COMMON_H */


/****************************************************************************

         Copyright (c) 2021 MaxLinear, Inc.
         Copyright (c) 2009 Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

*****************************************************************************/

#ifdef ECOS

/** \file
   This file contains the IFXOS Layer implementation for eCos
   Physical to Virtual Memory Mapping.
*/

/* ============================================================================
   IFX eCos adaptation - Global Includes
   ========================================================================= */

#include "ifx_types.h"
#include "ifxos_debug.h"
#include "ifxos_rt_if_check.h"
#include "ifxos_memory_map.h"

/* ============================================================================
   IFX eCos adaptation - memory mapping
   ========================================================================= */
/** \addtogroup IFXOS_MEMORY_MAP_ECOS_DRV
@{ */

/**
   eCos - Map the physical address to a virtual memory space.
   For virtual memory management this is required.

\par Implementation
   Under eCos there is no virtual memory management required.
   This function is introduced for compatibility against the LINUX concept.
   A simple assignment of the physical address is done.

\param
   physicalAddr         The physical address for mapping [I]
\param
   addrRangeSize_byte   Range of the address space to map [I]
\param
   pName                The name of the address space, for administration [I]
\param
   ppVirtAddr           Returns the pointer to the virtual mapped address [O]

\return
   IFX_SUCCESS if the mapping was successful and the ppVirtAddr is set, else
   IFX_ERROR   if something was wrong.

\remark
   This function depends on the used OS and also the used controller.
*/
IFX_int32_t IFXOS_Phy2VirtMap(
               IFX_ulong_t    physicalAddr,
               IFX_ulong_t    addrRangeSize_byte,
               IFX_char_t     *pName,
               IFX_uint8_t    **ppVirtAddr)
{
   IFXOS_PRN_USR_DBG_NL( IFXOS, IFXOS_PRN_LEVEL_LOW,
      ("IFXOS: Phy2Virt map - phy 0x%08lX --> virt 0x%08lX, size = 0x%lX" IFXOS_CRLF,
        physicalAddr, physicalAddr, addrRangeSize_byte ));

   IFXOS_RETURN_IF_POINTER_NULL(ppVirtAddr, IFX_ERROR);
   IFXOS_RETURN_IF_POINTER_NOT_NULL(*ppVirtAddr, IFX_ERROR);
   IFXOS_RETURN_IF_ARG_LE_ZERO(addrRangeSize_byte, IFX_ERROR);

   *ppVirtAddr = (IFX_uint8_t *)physicalAddr;

   return IFX_SUCCESS;
}

/**
   eCos - Release the virtual memory range of a mapped physical address.
   For virtual memory management this is required.

\par Implementation
   Under eCos there is no virtual memory management required.
   This function is introduced for compatibility against the LINUX concept.
   The simple assignment of the physical address is cleared.

\param
   pPhysicalAddr        Points to the physical address for release mapping [IO]
                        (Cleared if success)
\param
   addrRangeSize_byte   Range of the address space to map [I]
\param
   ppVirtAddr           Provides the pointer to the virtual mapped address [IO]
                        (Cleared if success)

\return
   IFX_SUCCESS if the release was successful.
               The physicalAddr and the ppVirtAddr pointer is cleared, else
   IFX_ERROR   if something was wrong.
*/
IFX_int32_t IFXOS_Phy2VirtUnmap(
               IFX_ulong_t   *pPhysicalAddr,
               IFX_ulong_t   addrRangeSize_byte,
               IFX_uint8_t    **ppVirtAddr)
{

   /* unmap the virtual address */
   if (ppVirtAddr != IFX_NULL)
   {
      IFXOS_PRN_USR_DBG_NL( IFXOS, IFXOS_PRN_LEVEL_LOW,
         ("IFXOS: Phy2Virt Unmap - unmap virt 0x%08lX, size = 0x%lX" IFXOS_CRLF,
           (IFX_ulong_t)(*ppVirtAddr), addrRangeSize_byte ));

      *ppVirtAddr = IFX_NULL;
   }

   /* release the memory region */
   if (pPhysicalAddr != IFX_NULL)
   {
      IFXOS_PRN_USR_DBG_NL( IFXOS, IFXOS_PRN_LEVEL_LOW,
         ("IFXOS: Phy2Virt Unmap - release region 0x%08lX size = 0x%lX" IFXOS_CRLF,
           (*pPhysicalAddr), addrRangeSize_byte ));

      *pPhysicalAddr = 0;
   }

   return IFX_SUCCESS;
}

/** @} */

#endif      /* #ifdef ECOS */


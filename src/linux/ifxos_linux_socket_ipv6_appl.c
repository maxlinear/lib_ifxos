/****************************************************************************

         Copyright (c) 2021 MaxLinear, Inc.
         Copyright (c) 2014 Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

*****************************************************************************/
#ifdef LINUX

/** \file
   This file contains the IFXOS Layer implementation for LINUX User
   Socket.
*/

/* ============================================================================
   IFX Linux adaptation - Global Includes
   ========================================================================= */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/*
	ToDo: add IP V6 user space includes
*/

#include "ifx_types.h"
#include "ifxos_rt_if_check.h"
#include "ifxos_socket.h"
#include "ifxos_socket_ipv6.h"
#include "ifxos_debug.h"

/* ============================================================================
   IFX Linux adaptation - User Space, Socket
   ========================================================================= */

/** \addtogroup IFXOS_SOCKET_LINUX_IPV6
@{ */

#if (defined(IFXOS_HAVE_SOCKET) && (IFXOS_HAVE_SOCKET == 1))

/**
   LINUX Appl - This function creates a TCP/IP, UDP/IP or raw IPv6 socket.

\par Implementation
   - Create a PF_INET6 socket, no specified protocol.

\param
   socType    specifies the type of the socket
              - IFXOS_SOC_TYPE_STREAM: TCP/IP socket
              - IFXOS_SOC_TYPE_DGRAM:  UDP/IP socket
\param
   pSocketFd  specifies the pointer where the value of the socket should be
              set. Value will be greater or equal zero

\return
   - IFX_SUCCESS in case of success
   - IFX_ERROR   if operation failed
*/
IFX_int_t IFXOS_SocketCreateIpV6(
	IFXOS_socketType_t socType,
	IFXOS_socket_t *pSocketFd)
{
#if defined(HAVE_IFXOS_IPV6_SUPPORT) && (HAVE_IFXOS_IPV6_SUPPORT == 1)
	int soc_protocol = 0; /* PF_INET6 */

	IFXOS_RETURN_IF_POINTER_NULL(pSocketFd, IFX_ERROR);

	/* arg3 = 0: do not specify the protocol */
	if((*pSocketFd = socket(AF_INET6, socType, soc_protocol)) == -1)
		{return IFX_ERROR;}

#if defined( IPV6_V6ONLY )
	if (soc_protocol == PF_INET6 )
	{
		/* Disable IPv4 mapped addresses. */
		int val_v6only = 1;
		if (setsockopt(
			*pSocketFd, IPPROTO_IPV6, IPV6_V6ONLY,
			&val_v6only, sizeof(val_v6only)) != 0)
		{
			IFXOS_PRN_USR_ERR_NL( IFXOS, IFXOS_PRN_LEVEL_WRN,
				("IFXOS ERROR - Socket IP V6 Create, cannot enable V6 only (errno <%s>)" IFXOS_CRLF,
				 strerror(errno)));
		}
	}
#endif

	return IFX_SUCCESS;
#else
	/* not built-in */
	return IFX_ERROR;
#endif
}

/**
   LINUX - Receives data from a datagram socket.

\par Implementation
   -  via "recv_from"

\param
   socFd         specifies the socket. Value has to be greater or equal zero
\param
   pBuffer       specifies the pointer to a buffer where the data will be copied
\param
   bufSize_byte  specifies the size in byte of the buffer 'pBuffer'
\param
   pSocAddr6     specifies a pointer to the IFXOS_sockAddr6_t structure

\return
   Returns the number of received bytes. Returns a negative value if an error
   occurred
*/
IFX_int_t IFXOS_SocketRecvFromIpV6(
	IFXOS_socket_t socFd,
	IFX_char_t *pBuffer,
	IFX_int_t bufSize_byte,
	IFXOS_sockAddr6_t *pSocAddr6)
{
#if defined(HAVE_IFXOS_IPV6_SUPPORT) && (HAVE_IFXOS_IPV6_SUPPORT == 1)
	int ret;
	unsigned int pFromlen = sizeof(IFXOS_sockAddr6_t);

	IFXOS_RETURN_IF_POINTER_NULL(pBuffer, IFX_ERROR);
	IFXOS_RETURN_IF_ARG_LE_ZERO(bufSize_byte, IFX_ERROR);

	ret = (IFX_int_t)recvfrom(
		(int)socFd, (char*)pBuffer, (int)bufSize_byte,
		0, (struct sockaddr *)pSocAddr6, &pFromlen);

	return ret;
#else
	/* not built-in */
	return IFX_ERROR;
#endif
}

/**
   LINUX Appl - Sends data to UDP IPv6 socket.

\par Implementation
   -  via "sock_sendmsg"

\param
   socFd        specifies the socket. Value has to be greater or equal zero
\param
   pBuffer      specifies the pointer to a buffer where the data will be copied
\param
   bufSize_byte specifies the size in byte of the buffer 'pBuffer'
\param
   pSocAddr6    specifies a pointer to the IFXOS_sockAddr_t structure

\return
   Returns the number of sent bytes. Returns a negative value if an error
   occurred
*/
IFX_int_t IFXOS_SocketSendToIpV6(
	IFXOS_socket_t socFd,
	IFX_char_t *pBuffer,
	IFX_int_t bufSize_byte,
	IFXOS_sockAddr6_t *pSocAddr6)
{
#if defined(HAVE_IFXOS_IPV6_SUPPORT) && (HAVE_IFXOS_IPV6_SUPPORT == 1)
	int ret;

	IFXOS_RETURN_IF_POINTER_NULL(pBuffer, IFX_ERROR);
	IFXOS_RETURN_IF_ARG_LE_ZERO(bufSize_byte, IFX_ERROR);

	ret = (IFX_int_t)sendto(
		(int)socFd, (const char*)pBuffer,
		(int)bufSize_byte, 0, pSocAddr6, sizeof(IFXOS_sockAddr6_t));

	return ret;
#else
	/* not built-in */
	return IFX_ERROR;
#endif
}

/**
   LINUX Appl - Assigns a local address to a TCP/IPv6, UDP/IPv6 or raw socket.

\par Implementation
   -  via "bind"

\param
   socFd      specifies the socket should be bind to the address
              Value has to be greater or equal zero
\param
   pSocAddr6  specifies a pointer to the IFXOS_sockAddr6_t structure

\return
   - IFX_SUCCESS in case of success
   - IFX_ERROR if operation failed
*/
IFX_int_t IFXOS_SocketBindIpV6(
	IFXOS_socket_t socFd,
	IFXOS_sockAddr6_t *pSocAddr6)
{
#if defined(HAVE_IFXOS_IPV6_SUPPORT) && (HAVE_IFXOS_IPV6_SUPPORT == 1)
	IFX_int_t ret;

	IFXOS_RETURN_IF_POINTER_NULL(pSocAddr6, IFX_ERROR);

	ret = bind((int)socFd, (struct sockaddr*)pSocAddr6, sizeof(IFXOS_sockAddr6_t) );
	if (ret != 0)
		{return IFX_ERROR;}

	return IFX_SUCCESS;
#else
	/* not built-in */
	return IFX_ERROR;
#endif
}

#endif	/* #if (defined(IFXOS_HAVE_SOCKET) && (IFXOS_HAVE_SOCKET == 1)) */

/** @} */

#endif      /* #ifdef LINUX */


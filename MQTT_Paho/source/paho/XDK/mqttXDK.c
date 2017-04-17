/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander - initial API and implementation and/or initial documentation
 *******************************************************************************/
/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttXDK.c
**
**	DESCRIPTION:	Links the Paho MQTT Client to the XDK Platform
**
**	PURPOSE:        Defines the timer and network functions
**	                the Paho Stack uses to interface with the platform
**
**	AUTHOR(S):      Bosch Connected Devices and Solutions GmbH (BCDS)
**
**	Revision History:
**
**	Date			 Name		Company      Description
**  2016.Apr         crk        BCDS         Edited Paho's CC3200 Platform source
**                                           to port code to the XDK Platform
**
*******************************************************************************/

/* system header files */
#include <stdint.h>

/* interface header files */
#include "BCDS_PowerMgt.h"

/* own header files */
#include "mqttXDK.h"

char expired(Timer* timer) {
    long left = timer->end_time - PowerMgt_GetSystemTimeMs();
    return (left < 0);
}


void countdown_ms(Timer* timer, unsigned int timeout) {
    timer->end_time = PowerMgt_GetSystemTimeMs() + timeout;
}


void countdown(Timer* timer, unsigned int timeout) {
    timer->end_time = PowerMgt_GetSystemTimeMs() + (timeout * 1000);
}


int left_ms(Timer* timer) {
    long left = timer->end_time - PowerMgt_GetSystemTimeMs();
    return (left < 0) ? 0 : left;
}


void InitTimer(Timer* timer) {
    timer->end_time = 0;
}


int xdk_read(Network* n, uint8_t* buffer, int len, int timeout_ms) {
    SlTimeval_t timeVal;
    SlFdSet_t fdset;
    int rc = 0;
    int recvLen = 0;

    SL_FD_ZERO(&fdset);
    SL_FD_SET(n->my_socket, &fdset);

    timeVal.tv_sec = 0;
    timeVal.tv_usec = timeout_ms * 1000;
    if (sl_Select(n->my_socket + 1, &fdset, NULL, NULL, &timeVal) == 1) {
        do {
            rc = sl_Recv(n->my_socket, buffer + recvLen, len - recvLen, 0);
            recvLen += rc;
        } while(recvLen < len);
    }
    return recvLen;
}

int xdk_write(Network* n, uint8_t* buffer, int len, int timeout_ms) {
    SlTimeval_t timeVal;
    SlFdSet_t fdset;
    int rc = 0;
    int readySock;

    SL_FD_ZERO(&fdset);
    SL_FD_SET(n->my_socket, &fdset);

    timeVal.tv_sec = 0;
    timeVal.tv_usec = timeout_ms * 1000;
    do {
        readySock = sl_Select(n->my_socket + 1, NULL, &fdset, NULL, &timeVal);
    } while(readySock != 1);
    rc = sl_Send(n->my_socket, buffer, len, 0);
    return rc;
}
void xdk_disconnect(Network* n) {
    sl_Close(n->my_socket);
}

void NewNetwork(Network* n) {
    n->my_socket = 0;
    n->mqttread = xdk_read;
    n->mqttwrite = xdk_write;
    n->disconnect = xdk_disconnect;
}

int TLSConnectNetwork(Network *n, char* addr, int port, SlSockSecureFiles_t* certificates, unsigned char sec_method, unsigned int cipher, char server_verify) {
	SlSockAddrIn_t sAddr;
	int addrSize;
	int retVal;
	unsigned long ipAddress;

	retVal = sl_NetAppDnsGetHostByName((_i8*) addr, strlen(addr), &ipAddress, AF_INET);
	if (retVal < 0) {
		return -1;
	}

	sAddr.sin_family = AF_INET;
	sAddr.sin_port = sl_Htons((unsigned short)port);
	sAddr.sin_addr.s_addr = sl_Htonl(ipAddress);

	addrSize = sizeof(SlSockAddrIn_t);

	n->my_socket = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, SL_SEC_SOCKET);
	if (n->my_socket < 0) {
		return -1;
	}

	SlSockSecureMethod method;
	method.secureMethod = sec_method;
	retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECMETHOD, &method, sizeof(method));
	if (retVal < 0) {
		return retVal;
	}

	SlSockSecureMask mask;
	mask.secureMask = cipher;
	retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECURE_MASK, &mask, sizeof(mask));
	if (retVal < 0) {
		return retVal;
	}

	if (certificates != NULL) {
		retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECURE_FILES, certificates->secureFiles, sizeof(SlSockSecureFiles_t));
		if(retVal < 0)
		{
			return retVal;
		}
	}

	retVal = sl_Connect(n->my_socket, ( SlSockAddr_t *)&sAddr, addrSize);
	if( retVal < 0 ) {
		if (server_verify || retVal != -453) {
			sl_Close(n->my_socket);
			return retVal;
		}
	}

	return retVal;
}

int ConnectNetwork(Network* n, char* addr, int port)
{
    SlSockAddrIn_t sAddr;
    int addrSize;
    int retVal = -1;
    unsigned long ipAddress;

    sl_NetAppDnsGetHostByName((_i8*) addr, strlen((char*)addr), &ipAddress, AF_INET);

    sAddr.sin_family = AF_INET;
    sAddr.sin_port = sl_Htons((unsigned short)port);
    sAddr.sin_addr.s_addr = sl_Htonl(ipAddress);

    addrSize = sizeof(SlSockAddrIn_t);

    n->my_socket = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, 0);
    if( n->my_socket < 0 ) {
        // error
        return -1;
    }

    retVal = sl_Connect(n->my_socket, ( SlSockAddr_t *)&sAddr, addrSize);
    if( retVal < 0 ) {
        // error
        sl_Close(n->my_socket);
        return retVal;
    }

    return retVal;
}

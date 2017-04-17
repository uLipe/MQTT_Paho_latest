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
**	OBJECT NAME:	mqttXDK.h
**
**	DESCRIPTION:	Configuration header for the XDK Platform
**
**	PURPOSE:        Contains the public macro, typedef, variables and function
**	                definitions for the XDK Platform specific functions
**
**	AUTHOR(S):      Bosch Connected Devices and Solutions GmbH (BCDS)
**
**	Revision History:
**
**	Date			 Name		Company      Description
**  2016.Apr         crk        BCDS         Edited Paho's CC3200 Platform header
**                                           to port code to the XDK Platform
**
*******************************************************************************/

#ifndef _PAHO_XDK_H_
#define _PAHO_XDK_H_

/* additional header files */
#include "simplelink.h"
#include "netapp.h"
#include "socket.h"

typedef struct Timer Timer;

struct Timer {
    unsigned long systick_period;
    unsigned long end_time;
};

typedef struct Network Network;

struct Network
{
	int my_socket;
	int (*mqttread) (Network*, unsigned char*, int, int);
	int (*mqttwrite) (Network*, unsigned char*, int, int);
	void (*disconnect) (Network*);
};

char expired(Timer*);
void countdown_ms(Timer*, unsigned int);
void countdown(Timer*, unsigned int);
int left_ms(Timer*);

void InitTimer(Timer*);

int xdk_read(Network*, unsigned char*, int, int);
int xdk_write(Network*, unsigned char*, int, int);
void xdk_disconnect(Network*);
void NewNetwork(Network*);

int ConnectNetwork(Network*, char*, int);
int TLSConnectNetwork(Network*, char*, int, SlSockSecureFiles_t*, unsigned char, unsigned int, char);

#endif /* _PAHO_XDK_H_ */

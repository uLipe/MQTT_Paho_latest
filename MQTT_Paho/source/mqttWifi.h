/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttWifi.h
**
**	DESCRIPTION:	Public Interface Header for mqttWifi.c source file
**
**	PURPOSE:        Contains the macro, typedef, variables and function
**	                definitions for the wifi module
**
**	AUTHOR(S):      Bosch Connected Devices and Solutions GmbH (BCDS)
**
**	Revision History:
**
**	Date			 Name		Company      Description
**  2016.Apr         crk        BCDS         Initial Release
**
*******************************************************************************/

/* header definition ******************************************************** */
#ifndef _MQTT_WIFI_H
#define _MQTT_WIFI_H

/* public interface declaration ********************************************* */

/* public type and macro definitions */
#define WIFI_DEFAULT_MAC		"00:00:00:00:00:00"         /**< Macro used to specify the Default MAC Address*/
#define WIFI_FAILED 			INT32_C(-1)                 /**< Macro used to return failure message*/
#define WIFI_MAC_ADDR_LEN 	   	UINT8_C(6)                  /**< Macro used to specify MAC address length*/

/* public global variable declarations */
extern void *g_mac_addr;

/* public function prototype declarations */
void wifiInit(void);
void wifiDeinit(void);

/* inline function definitions */

#endif /* _MQTT_WIFI_H */

/** ************************************************************************* */

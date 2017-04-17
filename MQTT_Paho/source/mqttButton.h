/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttButton.h
**
**	DESCRIPTION:	Interface header for the MQTT Button module
**
**	PURPOSE:        Contains all the definitions and macros for the
**                  MQTT button module
**
**	AUTHOR(S):		Bosch Connected Devices and Solutions GmbH (BCDS)
**
**	Revision History:
**
**	Date			 Name		Company      Description
**  2016.Apr         crk        BCDS         Initial Release
**
*******************************************************************************/

/* header definition ******************************************************** */
#ifndef _MQTT_BUTTON_H
#define _MQTT_BUTTON_H

/* Button interface declaration ********************************************** */

/* Button type and macro definitions */
#define CALLBACK_PARAMETER_PB1 UINT32_C(0x11)     /**< Macro represents callback parameter for Button1 */
#define CALLBACK_PARAMETER_PB2 UINT32_C(0x12)     /**< Macro represents callback parameter for Button2 */

/* global function prototype declarations */
void buttonInit(void);
void buttonDeinit(void);

/* global variable declarations */

/* global inline function definitions */

#endif /* _MQTT_BUTTON_H */

/** ************************************************************************* */

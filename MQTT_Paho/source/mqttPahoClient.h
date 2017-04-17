/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttClient.h
**
**	DESCRIPTION:	Interface header for the MQTT Paho Client module
**
**	PURPOSE:        Contains all the definitions and macros for the
**                  MQTT client module
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
#ifndef _MQTT_PAHO_CLIENT_H_
#define _MQTT_PAHO_CLIENT_H_

/* Paho Client interface declaration ********************************************** */

/* paho header files */
#include "MQTTClient.h"

/* Paho Client type and macro definitions */
#define CLIENT_TASK_STACK_SIZE            1024
#define CLIENT_TASK_PRIORITY              1

#define CLIENT_BUFF_SIZE                  1000
#define CLIENT_YIELD_TIMEOUT              10

#define TOPIC_DATA_STREAM        "iot-2/evt/stream_data/fmt/json"
#define TOPIC_DATA_GET           "XDK110/%s/Data/Get"
#define TOPIC_LED_RED            "XDK110/%s/LED/Red"
#define TOPIC_LED_ORANGE         "XDK110/%s/LED/Orange"
#define TOPIC_LED_YELLOW         "XDK110/%s/LED/Yellow"


/* global function prototype declarations */
void clientInit(void);
void clientDeinit(void);
void clientStartTimer(void);
void clientStopTimer(void);

/* global variable declarations */
extern Network n;
extern Client c;

/* global inline function definitions */

#endif /* _MQTT_PAHO_CLIENT_H_ */

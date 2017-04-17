/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttSensor.h
**
**	DESCRIPTION:	Public Interface Header for sensor module
**
**	PURPOSE:        Contains the public macro, typedef, variables and function
**	                definitions for the sensor module
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
#ifndef _MQTT_SENSOR_H_
#define _MQTT_SENSOR_H_

/* Sensor interface declaration ********************************************* */

/* interface header files */
#include "FreeRTOS.h"
#include "timers.h"

/* Sensor type and macro definitions */
#define SENSOR_DATA_BUF_SIZE    1024

typedef struct {
	uint32_t length;
	char data[SENSOR_DATA_BUF_SIZE];
} DataBuffer;

/* public function prototype declarations */
void sensorStreamData(xTimerHandle pvParameters);
void sensorInit(void);
void sensorDeinit(void);

/* public global variable declarations */

// Data Buffers
extern DataBuffer sensorStreamBuffer;

/* inline function definitions */

#endif /* _MQTT_SENSOR_H_ */

/** ************************************************************************* */

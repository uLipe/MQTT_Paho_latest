/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttInit.c
**
**	DESCRIPTION:	Initializes the MQTT Client Project
**
**	PURPOSE:        Initializes the Sensors, Wi-Fi, MQTT Client, and the Buttons.
**	                This is the initial point of entry for the user defined code
**
**	AUTHOR(S):      Bosch Connected Devices and Solutions GmbH (BCDS)
**
**	Revision History:
**
**	Date			 Name		Company      Description
**  2016.Apr         crk        BCDS         Initial Release
**
*******************************************************************************/

/* system header files */
#include <stdint.h>
#include <stdio.h>

/* own header files */
#include "mqttButton.h"
#include "mqttPahoClient.h"
#include "mqttSensor.h"
#include "mqttWifi.h"
#include "mqttConfig.h"

/* additional interface header files */
#include "FreeRTOS.h"
#include "timers.h"
#include "PTD_portDriver_ph.h"
#include "PTD_portDriver_ih.h"
#include "WDG_watchdog_ih.h"

/* paho header files */
#include "MQTTClient.h"

/* constant definitions ***************************************************** */

/* local variables ********************************************************** */

/* global variables ********************************************************* */

/* inline functions ********************************************************* */

/* local functions ********************************************************** */

/* global functions ********************************************************* */

/**
 * @brief Initializes the System
 *
 */
void appInitSystem(xTimerHandle xTimer)
{
    (void) (xTimer);

    /* Initialize Sensors */
    sensorInit();

    /* Initialize WiFi */
    wifiInit();

    /* Initialize Client */
    clientInit();

    /* Initialize Buttons */
    buttonInit();

    WDG_init(WDG_FREQ, WDG_TIMEOUT);

    /* Turn ON Orange LED to indicate Initialization Complete */
    PTD_pinOutSet(PTD_PORT_LED_ORANGE, PTD_PIN_LED_ORANGE);

    printf("Initialization Complete!\r\n");
}

/** ************************************************************************* */

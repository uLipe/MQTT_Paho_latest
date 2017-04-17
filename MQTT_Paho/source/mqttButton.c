/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttButton.c
**
**	DESCRIPTION:	Source Code for the MQTT Button implementation
**
**	PURPOSE:        Initializes the buttons and their callback functions
**
**	AUTHOR(S):		Bosch Connected Devices and Solutions GmbH (BCDS)
**
**	Revision History:
**
**	Date			 Name		Company      Description
**  2016.Apr         crk        BCDS         Initial Release
**
*******************************************************************************/

/* module includes ********************************************************** */

/* system header files */
#include <stdint.h>

/* own header files */
#include "mqttButton.h"
#include "mqttConfig.h"
#include "mqttPahoClient.h"

/* additional interface header files */
#include "XdkBoardHandle.h"
#include "button.h"

/* paho header files */
#include "MQTTClient.h"

/* constant definitions ***************************************************** */

/* local variables ********************************************************** */
static BUTTON_handle_tp Button1Handle = (BUTTON_handle_tp) POINTER_NULL; /**< variable to store button 1 handle */
static BUTTON_handle_tp Button2Handle = (BUTTON_handle_tp) POINTER_NULL; /**< variable to store button 2 handle */

/* global variables ********************************************************* */

/* inline functions ********************************************************* */

/* local functions ********************************************************** */
/*
 * @brief Callback function for a button press
 *
 * @param[in] handle - UNUSED
 * @param[in] userParameter - User defined parameter to identify which button is pressed
 *
 * @return NONE
 */
static void buttonCallback(void *handle, uint32_t userParameter)
{
	(void) handle;

    switch (userParameter)
    {
    /*  Button 1 pressed */
    case CALLBACK_PARAMETER_PB1:
        if (BUTTON_isPressed(handle))
        {
        	clientStartTimer();
        }
        break;
    /* Button 2 pressed */
    case CALLBACK_PARAMETER_PB2:
        if (BUTTON_isPressed(handle))
        {
        	clientStopTimer();
        }
        break;
    default:
        printf("Button not available \n\r");
        break;
    }
    return;
}

/* global functions ********************************************************* */
/*
 * @brief Initializes the buttons
 *
 * @return NONE
 */
void buttonInit(void)
{
    BUTTON_errorTypes_t buttonReturn = BUTTON_ERROR_INVALID_PARAMETER;

    /* Create the Handles */
    Button1Handle = BUTTON_create(gpioButton1_Handle, GPIO_STATE_OFF);
    if (Button1Handle != POINTER_NULL) {
        Button2Handle = BUTTON_create(gpioButton2_Handle, GPIO_STATE_OFF);
    }
    /* Enable the Buttons */
    if (Button2Handle != POINTER_NULL) {
    	buttonReturn = BUTTON_enable(Button1Handle);
    }
    if (buttonReturn == BUTTON_ERROR_OK)
    {
        buttonReturn = BUTTON_enable(Button2Handle);
    }
    /* Set the Callback Function For each Button */
    if (buttonReturn == BUTTON_ERROR_OK)
    {
    	buttonReturn = BUTTON_setCallback(Button1Handle, buttonCallback, CALLBACK_PARAMETER_PB1);
    }
    if (buttonReturn == BUTTON_ERROR_OK)
    {
        buttonReturn = BUTTON_setCallback(Button2Handle, buttonCallback, CALLBACK_PARAMETER_PB2);
    }
    if (buttonReturn != BUTTON_ERROR_OK)
    {
        printf("Buttons FAILED to Initialize!!\r\n");
    }

    PTD_portOutClear(PTD_PORT_LED_RED, PTD_PIN_LED_RED);

    return;
}

/*
 * @brief De-Initializes the buttons
 *
 * @return NONE
 */
void buttonDeinit(void)
{
    BUTTON_errorTypes_t buttonReturn = BUTTON_ERROR_INVALID_PARAMETER;

    buttonReturn = BUTTON_delete(Button1Handle);
    if (buttonReturn == BUTTON_ERROR_OK) {
        buttonReturn = BUTTON_delete(Button2Handle);
    }
    if (buttonReturn != BUTTON_ERROR_OK) {
    	printf("Buttons FAILED to De-Initialize!!\r\n");
    }
    return;
}

/** ************************************************************************* */

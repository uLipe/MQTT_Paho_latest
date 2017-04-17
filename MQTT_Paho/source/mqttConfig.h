/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttConfig.h
**
**	DESCRIPTION:	Configuration header for the MQTT Paho Client
**
**	PURPOSE:        Contains the common macro, typedef, variables and function
**	                definitions for the entire project
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
#ifndef _MQTT_CONFIG_H_
#define _MQTT_CONFIG_H_

/* Config interface declaration ********************************************** */

/* Config type and macro definitions */
#define XDK_PAHO_DEMO_REVISION       "0.2.0"

#define NUMBER_UINT8_ZERO		     UINT8_C(0)     /**< Zero value */
#define NUMBER_UINT32_ZERO 		     UINT32_C(0)    /**< Zero value */
#define NUMBER_UINT16_ZERO 		     UINT16_C(0)    /**< Zero value */
#define NUMBER_INT16_ZERO 		     INT16_C(0)     /**< Zero value */

#define POINTER_NULL 			     NULL          /**< ZERO value for pointers */

#define TIMER_AUTORELOAD_ON          1             /**< Auto reload timer */
#define TIMER_AUTORELOAD_OFF         0             /**< One Shot Timer */

#define ENABLED         1
#define DISABLED        0

#warning Provide Default WLAN and MQTT Configuration Here
// Default Network Configuration Settings
#define	WLAN_SSID	  		"Felipe's iPhone"      	  					  	  /**< WLAN SSID Name */
#define	WLAN_PWD	  		"123456789"          							  /**< WLAN PWD */
#define	MQTT_CLIENT_ID	    "d:bq0tr8:bosch_xdk_huehue_brbr:ulipe_bosch_xdk"  /**< MQTT Client ID */
//#define	MQTT_CLIENT_ID	    "bosch_xdk_huehue_brbr"             	  		/**< MQTT Client ID */

#define MQTT_BROKER_NAME    "bq0tr8.messaging.internetofthings.ibmcloud.com"  /**< MQTT Broker */
#define MQTT_PORT           1883                          					  /**< MQTT Port Number */

#define IBM_BLUEMIX_DEVICE_TOKEN "10gRBU-*FvbHeKxo!@"
#define IBM_BLUEMIX_USERNAME     "use-token-auth"

// Default Data Configuration Settings
#define STREAM_RATE         2000/portTICK_RATE_MS /**< Stream Data Rate in MS */
#define ACCEL_EN            ENABLED               /**< Accelerometer Data Enable */
#define GYRO_EN             DISABLED               /**< Gyroscope Data Enable */
#define MAG_EN              DISABLED               /**< Magnetometer Data Enable */
#define ENV_EN              DISABLED               /**< Environmental Data Enable */
#define LIGHT_EN            DISABLED               /**< Ambient Light Data Enable */

#define WDG_FREQ            1000
#define WDG_TIMEOUT         5000

/* global function prototype declarations */

/* global variable declarations */

/* global inline function definitions */

#endif /* _MQTT_CONFIG_H_ */

/** ************************************************************************* */

/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttSensor.c
**
**	DESCRIPTION:	Manages the Sensors
**
**	PURPOSE:        Initializes the sensors and data buffers,
**					reads the sensor data, and writes the data into a buffer
**
**	AUTHOR(S):      Bosch Connected Devices and Solutions GmbH (BCDS)
**
**	Revision History:
**
**	Date			 Name		Company      Description
**	2016.Apr         crk        BCDS         Initial Release
**
*******************************************************************************/

/* module includes ********************************************************** */

/* system header files */
#include <stdio.h>
#include <stdint.h>

/* own header files */
#include "mqttSensor.h"
#include "mqttConfig.h"

/* interface header files */
#include "XdkSensorHandle.h"
#include "BCDS_PowerMgt.h"
#include "BCDS_Retcode.h"

/* constant definitions ***************************************************** */

/* local variables ********************************************************** */

/* global variables ********************************************************* */
DataBuffer sensorStreamBuffer;  // Data Stream Bufer

/* inline functions ********************************************************* */

/* local functions ********************************************************** */
static void sensorInitializeAccel(void);
static void sensorInitializeGyro(void);
static void sensorInitializeMag(void);
static void sensorInitializeLight(void);
static void sensorInitializeEnv(void);
static Retcode_T sensorPostInitLightSensor(void);
static Retcode_T sensorPostInitMagSensor(void);

/**
 * @brief Inititialize the accelerometer
 */
static void sensorInitializeAccel(void)
{
	Retcode_T _accelReturnValue_BMA280_S = RETCODE_FAILURE;

	_accelReturnValue_BMA280_S = Accelerometer_init(xdkAccelerometers_BMA280_Handle);
	if(RETCODE_SUCCESS != _accelReturnValue_BMA280_S) {
		printf("accelerometerInit BMA280 failed = %ld \r\n",_accelReturnValue_BMA280_S);
	}
}

/**
 * @brief Inititialize the gyroscope
 */
static void sensorInitializeGyro(void)
{
	Retcode_T _gyroG160ReturnValue = RETCODE_FAILURE;

	_gyroG160ReturnValue = Gyroscope_init(xdkGyroscope_BMG160_Handle);
	if(RETCODE_SUCCESS != _gyroG160ReturnValue) {
		printf("gyroscopeInit BMG160 failed = %ld \r\n",_gyroG160ReturnValue);
	}
}

/**
 * @brief Inititialize the magnetometer
 */
static void sensorInitializeMag(void)
{
	Retcode_T _magnetoReturnValue = RETCODE_FAILURE;

	_magnetoReturnValue = Magnetometer_init(xdkMagnetometer_BMM150_Handle);
	if(RETCODE_SUCCESS != _magnetoReturnValue) {
		printf("magnetometerInit BMM150 failed = %ld \r\n",_magnetoReturnValue);
	}

	if(RETCODE_SUCCESS == _magnetoReturnValue  ) {
		_magnetoReturnValue = sensorPostInitMagSensor();
	}

	if(RETCODE_SUCCESS != _magnetoReturnValue) {
		printf("sensorPostInitMagSensor BMM150 failed = %ld \r\n",_magnetoReturnValue);
	}
}

/**
 * @brief Inititialize the ambient light sensor
 */
static void sensorInitializeLight(void)
{
	Retcode_T _lgtReturnValue = RETCODE_FAILURE;

	_lgtReturnValue = LightSensor_init(xdkLightSensor_MAX44009_Handle);
	if(RETCODE_SUCCESS != _lgtReturnValue) {
		printf("lightsensorInit MAX09 failed = %ld \r\n",_lgtReturnValue);
	}

	if(RETCODE_SUCCESS == _lgtReturnValue) {
		_lgtReturnValue = sensorPostInitLightSensor();
	}

	if(RETCODE_SUCCESS != _lgtReturnValue) {
		printf("sensorPostInitLightSensor MAX09 failed = %ld \r\n",_lgtReturnValue);
	}
}

/**
 * @brief Inititialize the environmental sensor
 */
static void sensorInitializeEnv(void)
{
	Retcode_T _envReturnValue = RETCODE_FAILURE;

	_envReturnValue = Environmental_init(xdkEnvironmental_BME280_Handle);
	if(RETCODE_SUCCESS != _envReturnValue) {
		printf("environmentalInit BME280 failed = %ld \r\n",_envReturnValue);
	}
}

/**
 * @brief The function does the post initialisation of the light sensor
 */
static Retcode_T sensorPostInitLightSensor(void)
{
	Retcode_T _res = RETCODE_FAILURE;

    /* Manual Mode should be enable in order to configure the continuous mode, brightness  and integration time */
	_res = LightSensor_setManualMode(xdkLightSensor_MAX44009_Handle, LIGHTSENSOR_MAX44009_ENABLE_MODE);

    return _res;
}

/**
 * @brief The function does the post initialisation of the magnetometer
 */
static Retcode_T sensorPostInitMagSensor(void)
{
	Retcode_T _res = RETCODE_FAILURE;
	_res = Magnetometer_setPowerMode(xdkMagnetometer_BMM150_Handle,
			MAGNETOMETER_BMM150_POWERMODE_NORMAL);
	return _res;
}

/* global functions ********************************************************* */

/**
 * @brief Read the sensors and fill the stream data buffer
 *
 * @param[in] pvParameters - UNUSED
 *
 * @return NONE
 */
void sensorStreamData(xTimerHandle pvParameters)
{
	/* Initialize Variables */
	(void) pvParameters;
	Accelerometer_XyzData_T 	   _accelBMA280Data  = {NUMBER_UINT16_ZERO,NUMBER_UINT16_ZERO,NUMBER_UINT16_ZERO};
	Gyroscope_XyzData_T     	   _gyroBMG160Data	 = {NUMBER_UINT32_ZERO,NUMBER_UINT32_ZERO,NUMBER_UINT32_ZERO};
	Magnetometer_XyzData_T         _magData    	     = {NUMBER_UINT16_ZERO,NUMBER_UINT16_ZERO,NUMBER_UINT16_ZERO,NUMBER_UINT16_ZERO};
	Environmental_Data_T		   _envData		     = {NUMBER_UINT32_ZERO,NUMBER_UINT32_ZERO,NUMBER_UINT32_ZERO};
	uint32_t			           _lgtData		     = {NUMBER_UINT32_ZERO};
	uint32_t                       _timestamp        = {NUMBER_UINT32_ZERO};

	/* Read the Sensors */
	Accelerometer_readXyzGValue    (xdkAccelerometers_BMA280_Handle     , &_accelBMA280Data);
	Gyroscope_readXyzDegreeValue   (xdkGyroscope_BMG160_Handle 	    	, &_gyroBMG160Data);
	Environmental_readData         (xdkEnvironmental_BME280_Handle      , &_envData);
	LightSensor_readLuxData        (xdkLightSensor_MAX44009_Handle  	, &_lgtData);
	Magnetometer_readXyzTeslaData  (xdkMagnetometer_BMM150_Handle       , &_magData);
	_timestamp = PowerMgt_GetSystemTime();

	/* Write the sensor data into the Stream Buffer in JSON Format */
	sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "Device: %s\n",  "XDK110");
	sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "Name: %s\n", MQTT_CLIENT_ID);
	sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "Timestamp: %ld\n",  _timestamp);
	if (ACCEL_EN == ENABLED) {
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "acc (mG):\n");
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     x = %-+5ld\n", _accelBMA280Data.xAxisData);
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     y = %-+5ld\n", _accelBMA280Data.yAxisData);
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     z = %-+5ld\n", _accelBMA280Data.zAxisData);
	}
	if (GYRO_EN == ENABLED) {
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "gyro (mdeg/s):\n");
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     x = %-+5ld\n", _gyroBMG160Data.xAxisData);
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     y = %-+5ld\n", _gyroBMG160Data.yAxisData);
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     z = %-+5ld\n", _gyroBMG160Data.zAxisData);
	}
	if (MAG_EN == ENABLED) {
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "mag (uT):\n");
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     x = %-+5ld\n", _magData.xAxisData);
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     y = %-+5ld\n", _magData.yAxisData);
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "     z = %-+5ld\n", _magData.zAxisData);
	}
	if (LIGHT_EN == ENABLED) {
	    sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "light (mLux) = %ld\n", _lgtData);
	}
	if (ENV_EN == ENABLED) {
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "temp (mCelsius) = %ld\n", _envData.temperature);
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "pressure (Pascal) = %ld\n", _envData.pressure);
		sensorStreamBuffer.length += sprintf(sensorStreamBuffer.data + sensorStreamBuffer.length, "humidity (%%rh) = %ld\n", _envData.humidity);
	}
}

/**
 * @brief initialize the sensors
 *
 * @return NONE
 */
void sensorInit(void)
{
	/* Initialize all sensors */
	if (ACCEL_EN == ENABLED) {
		sensorInitializeAccel();
	}
	if (GYRO_EN == ENABLED) {
		sensorInitializeGyro();
	}
	if (MAG_EN == ENABLED) {
	    sensorInitializeMag();
	}
	if (LIGHT_EN == ENABLED) {
	    sensorInitializeLight();
	}
	if (ENV_EN == ENABLED) {
	    sensorInitializeEnv();
	}

	/* Initialize Memory Buffers */
	memset(sensorStreamBuffer.data, 0x00, SENSOR_DATA_BUF_SIZE);
	sensorStreamBuffer.length = NUMBER_UINT32_ZERO;
}

/**
 * @brief De-Initialize the sensors
 *
 * @return NONE
 */
void sensorDeinit(void)
{
  ;/* nothing to do */
}

/** ************************************************************************* */

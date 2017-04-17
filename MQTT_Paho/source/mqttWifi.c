/******************************************************************************
**	COPYRIGHT (c) 2016		Bosch Connected Devices and Solutions GmbH
**
**	The use of this software is subject to the XDK SDK EULA
**
*******************************************************************************
**
**	OBJECT NAME:	mqttWifi.c
**
**	DESCRIPTION:	Manages the WiFi Network
**
**	PURPOSE:        This file contains the implementation for using the WIFI for
**	                exchanging data with the monitoring device
**
**	AUTHOR(S):      Bosch Connected Devices and Solutions GmbH (BCDS)
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
#include "mqttWifi.h"
#include "mqttConfig.h"

/* interface header files */
#include "PIp.h"
#include "BCDS_WlanConnect.h"
#include "netcfg.h"
#include "BCDS_NetworkConfig.h"
#include "Serval_Ip.h"
#include "BCDS_Retcode.h"

/* constant definitions ***************************************************** */

/* local variables ********************************************************** */
static char wifiMacAddress[]    		  = WIFI_DEFAULT_MAC;    /**< To keep the MAC adress returned by the wifi network device */

/* global variables ********************************************************* */
void *g_mac_addr = (void*)wifiMacAddress;

/* inline functions ********************************************************* */

/* local functions ********************************************************** */

/* global functions ********************************************************* */

/**
 * @brief initialize the Wi-Fi
 *
 * @return NONE
 */
void wifiInit(void)
{
	/* Initialize Variables */
	uint8_t _macVal[WIFI_MAC_ADDR_LEN];
	uint8_t _macAddressLen = WIFI_MAC_ADDR_LEN;
	NetworkConfig_IpSettings_T myIpSettings;
	memset(&myIpSettings, (uint32_t) 0, sizeof(myIpSettings));
	int8_t ipAddress[PAL_IP_ADDRESS_SIZE] = {0};
	Ip_Address_T* IpaddressHex = Ip_getMyIpAddr();
	WlanConnect_SSID_T connectSSID;
	WlanConnect_PassPhrase_T connectPassPhrase;

	WDG_feedingWatchdog();


	/* Initialize the Wireless Network Driver */
	if(RETCODE_SUCCESS != WlanConnect_Init())
	{
		printf("Error occurred initializing WLAN \r\n");
		return;
	}

	/* Get the SSID and PWD for the WiFi Network */
	connectSSID = (WlanConnect_SSID_T) WLAN_SSID;
	connectPassPhrase = (WlanConnect_PassPhrase_T) WLAN_PWD;
	printf("Connecting to %s \r\n", connectSSID);

	Retcode_T retStatusSetIp;
	retStatusSetIp = NetworkConfig_SetIpDhcp(0);

	if (retStatusSetIp != RETCODE_SUCCESS) {
		printf("Setting IP over DHCP Failed");
	}

	/* Connect to the Wireless Network */
	if (RETCODE_SUCCESS == WlanConnect_WPA(connectSSID, connectPassPhrase, NULL)) {
		NetworkConfig_GetIpSettings(&myIpSettings);
		*IpaddressHex = Basics_htonl(myIpSettings.ipV4);
		(void)Ip_convertAddrToString(IpaddressHex,(char *)&ipAddress);
		printf("Connected to WPA network successfully. \r\n");
		printf("Ip address of the device: %s \r\n",ipAddress);
	}
	else  {
		printf("Error occurred connecting %s \r\n ", connectSSID);
		return;
	}

	/* Get the MAC Address */
	memset(_macVal, NUMBER_UINT8_ZERO, WIFI_MAC_ADDR_LEN);
	int8_t _status = sl_NetCfgGet(SL_MAC_ADDRESS_GET,
									NULL,
									&_macAddressLen,
									(uint8_t *) _macVal);

	if (WIFI_FAILED == _status) {
		printf("sl_NetCfgGet Failed\r\n");
	}
	else {
		/* Store the MAC Address into the Global Variable */
		memset(wifiMacAddress, NUMBER_UINT8_ZERO, strlen(wifiMacAddress));
		sprintf(wifiMacAddress,"%02X:%02X:%02X:%02X:%02X:%02X",_macVal[0],
															 _macVal[1],
															 _macVal[2],
															 _macVal[3],
															 _macVal[4],
															 _macVal[5]);
		printf("MAC address of the device: %s \r\n",wifiMacAddress);
	}
}

/**
 * @brief De-Initialize the Wi-Fi
 */
void wifiDeinit(void)
{
    ;/* DO NOTHING */
}
/** ************************************************************************* */

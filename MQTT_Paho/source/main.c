/**
 * This software is copyrighted by Bosch Connected Devices and Solutions GmbH, 2015. 
 * The use of this software is subject to the XDK SDK EULA
 */

/* system header files */
#include <stdint.h>
#include <stdio.h>

/* additional interface header files */
#include "XdkSystemStartup.h"

/* own header files */
void vApplicationIdleHook(void)
{
	/* feed the watchdog each idle execution */
	WDG_feedingWatchdog();
}



/* functions */

int main(void)
{
    systemStartup();
}

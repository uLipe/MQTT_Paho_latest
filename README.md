# MQTT with Bosch XDK
- Simple example to connect Bosch XDK with IBM Bluemix
- The XDK device will boots and will connects to WiFi;
- After a successful connection it will open a MQTT connection;
- The connection follows the IBM IoT platform rules;
- Once connection made the user can press button * to start pusblish data;
- If button ** is pressed the publishing will be stopped;


# Basic usage
- Clone this repository and with Bosch XDK Workbench import it as project;
- After import, hit control+B to build the workspace;
- Connect your XDK device via USB port;
- After build press Flash, the device will start immediately;
- To configure WiFi and MQTT go to mqttConfig.h file



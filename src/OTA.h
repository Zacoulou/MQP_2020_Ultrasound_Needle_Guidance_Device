#pragma once
#ifndef OTA_H
#define OTA_H

#define COMPDATE __DATE__ __TIME__
#define MODEBUTTON 0 // Button pin on the esp for selecting modes. D3 for the Wemos!
//#include "HTTPClient.h"
#include "IOTAppStory.h" // IotAppStory.com library

extern IOTAppStory IAS;
extern boolean wifiConnected;

#endif
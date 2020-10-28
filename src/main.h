#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>
#include "SDFiles.h"
#include "DPad.h"

// --------------------------------- DPAD PINOUT / INITIALIZATION ----------------------------
const int switch_A = 27; // UP
const int switch_B = 32; // LEFT
const int switch_C = 33; // DOWN
const int switch_D = 35; // RIGHT
const int switch_E = 34; // PRESSED
int pos_A, pos_B, pos_C, pos_D, pos_E;
String currentPress = "Neutral";
unsigned int defaultDelay = 250;
unsigned int reducedDelay = 25;
unsigned int increasedDelay = 400;
unsigned int buttonDelay = defaultDelay;
unsigned long timeAtPress = 0;
String lastPress = currentPress;

// --------------------------------- INITIALIZE TFT DISPLAY ----------------------------
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
TFT_eSPI tft = TFT_eSPI();
int timeStamp = 0;
double voltageTotal = 0;
double numReadings = 0;
double batteryVoltage = 0;
TFT_eSprite scrollingBoxSprite = TFT_eSprite(&tft); // Sprite object
boolean isScrolling = false;
int scrollDirectionX = -2;
unsigned long ScrollDelay = 200; //200
unsigned long ScrollInitiateTimer = 0;
int scrollPixelDistance = 0;
boolean firstScroll = false;
int desiredScrollDistance = 0;

// --------------------------------- INITIALIZE AUDIO ----------------------------
AudioFileSource *file;
AudioFileSourceID3 *id3;
AudioOutputI2S *out = new AudioOutputI2S();
AudioGeneratorMP3 *mp3 = new AudioGeneratorMP3();
File root;
File allAudioFiles;
double audioGain = 0.4;
Option* currentAudio;
boolean audioDone = true;

// --------------------------------- INITIALIZE OTA ----------------------------
IOTAppStory IAS(COMPDATE, MODEBUTTON); // Initialize IotAppStory
boolean wifiConnected = false;

// --------------------------------- INITIALIZE GLOBAL VARIABLES ----------------------------
int optionSelected = 0; //Vertical option selection
int prevOption;
int tabSelected = 1; //Horizontal tab selection  0)Settings   1)Main   2)Messages 
int prevTab;
boolean updateAudioFilesList = false;
Preferences preferences;
int PageOptionstartX = 10;
int PageOptionstartY = 70;
int previousPageOptionStartIndex = 0;
int previousPageOptionEndIndex = 0;

// --------------------------------- USING BOTH ESP32s FAST CORES  ----------------------------
// TaskHandle_t Task1;

// --------------------------------- FUNCTION PROTOTYPES ----------------------------
void headerInfo();
void buttonResponse(String button);
void screenUpdate();
void initPages();
void drawFooter();
void drawMainMenu(String direction);
void handleButtonLag();
void backPage();
void audioManager();


// --------------------------------- PAGE AND OPTION CREATION ----------------------------

//EMPTY PAGE
Option emptyOption("");
Option emptyOption2("");
vector<Option*> emptyVector = {&emptyOption, &emptyOption2};
Page EmptyPage("", emptyVector);

//Back button
Option BackButton("<Back");

//MAIN PAGE
Option OrientationOption("Orientation Readings");
Option PerformSweepOption("Perform Sweep");
vector<Option*> mainPageOptions = {&OrientationOption, &PerformSweepOption};
// Decor lowVol(VolumeLow, 70, 180, 15, 15);
// Decor highVol(VolumeHigh, 235, 180, 15, 15);
// vector<Decor*> decorations = {&lowVol, &highVol};
Page MainPage("Menu", mainPageOptions);


//SETTINGS PAGE
Option WiFiOption("WiFi");
Option FirmwareOption("Firmware");
vector<Option*> settingsOptions = {&WiFiOption, &FirmwareOption};
Page SettingsPage("Settings", settingsOptions);

//---->WiFi
Option ConnectOption("Reconnect");
Option ConfigureNewNetworkOption("Configure New Network");
Option DisconnectOption("Disconnect");
Option NetworkDetailsOption("Network Details");
Option DeviceDetailsOption("Device Details");
vector<Option*> WiFiOptions = {&BackButton, &ConnectOption, &ConfigureNewNetworkOption, &DisconnectOption, &NetworkDetailsOption, &DeviceDetailsOption};
Page WiFiPage("WiFi", WiFiOptions);

//---->Firmware
Option UpdateOption("Update");
Option FirmwareDetailOption("Firmware Details");
Option ResetButton("Reset Device");
vector<Option*> FirmwareOptions = {&BackButton, &UpdateOption, &FirmwareDetailOption, &ResetButton};
Page FirmwarePage("Firmware", FirmwareOptions);



//INITIALIZE CURRENT STARTING PAGE
Page* currentPage = &MainPage;

#endif /* _MAIN_H_ */
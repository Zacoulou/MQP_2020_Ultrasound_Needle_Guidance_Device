#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <TFT_eSPI.h>
#include "AudioFileSourceSD.h"
#include "Bitmaps.h"

// Original Pinout for Display
// #define TFT_DC 4
// #define TFT_CS 15
// #define TFT_RST 2
// #define TFT_MISO 12
// #define TFT_MOSI 13
// #define TFT_CLK 14

// 2nd Iteration Pinout for Display
// #define TFT_MISO 19
// #define TFT_MOSI 13
// #define TFT_SCLK 14
// #define TFT_CS   15  
// #define TFT_DC    4  
// #define TFT_RST   2 

// Current Pinout for Display (Refer to User_Setup.h line 188 to see these values being used for TFT_eSPI)
// #define TFT_MISO 19
// #define TFT_MOSI 13
// #define TFT_SCLK 14
// #define TFT_CS   15  // Chip select control pin
// #define TFT_DC    4  // Data Command control pin
// #define TFT_RST   2  // Reset pin (could connect to RST pin)


// Old Pinout for SD
// SD_CS = 5?? (not sure if this is actually what it was)
//SD_MOSI = 23
//SD_MISO = 19
//SD_CLK = 18

// Current Pinout for SD
#define SD_CS 5
//SD_MOSI = 13 (same as Display)
//SD_MISO = 19 (same as Display)
//SD_CLK = 14 (same as Display)

//extern Adafruit_ILI9341 myScreen;
extern TFT_eSPI tft;

extern int timeStamp;
extern double voltageTotal, numReadings, batteryVoltage;

//Function Prototypes
void displayText(String text, int size, int posX, int posY, uint16_t color1, uint16_t color2);
void screenFillDirection(String direction, uint16_t color);
void drawHeader();
int centerX(String txt, int textSize);

#endif /* _DISPLAY_H_ */
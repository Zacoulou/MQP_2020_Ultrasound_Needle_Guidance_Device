#include "Display.h"

void displayText(String text, int size, int posX, int posY, uint16_t textColor, uint16_t highlight) {
  tft.setTextSize(size);
  tft.setTextColor(textColor, highlight);
  tft.setCursor(posX, posY);
  tft.print(text);
}

void screenFillDirection(String direction, uint16_t color) {
  if (direction.equals("Right")) {
    tft.setRotation(0);
    //tft.fillScreen(color);
    tft.fillRect(25, 0, 190, 320, color);
    tft.setRotation(3);
  }
  else if (direction.equals("Left")) {
    tft.setRotation(2);
    //tft.fillScreen(color);
    tft.fillRect(25, 0, 190, 320, color);
    tft.setRotation(3);
  }
  else if (direction.equals("Down")) {
    tft.setRotation(3);
    tft.fillRect(0, 25, 320, 190, color);
    //tft.fillScreen(color);
  }
}

void drawHeader() {
  //Upper Header
  tft.fillRect(0, 0, 320, 25, ILI9341_BLACK);
  tft.drawFastHLine(0, 24, 320, ILI9341_WHITE);
}

int centerX(String txt, int textSize){
  //DISPLAY is 320 x 240 -> 320/2 = 160
  int length = txt.length();
  int xCenter = 0;

  if (textSize == 2){
    //Each letter is 10 pixels wide with 2 pixel spacing, also only need half of length. 12 * 1/2 = 6
    xCenter = 160 - 6*length;
  }

  else if (textSize == 3){
    //Each letter is 15 pixels wide with average of 3 pixel spacing, also only need half of length. 18 * 1/2 = 9
    xCenter = 160 - 9*length;
  }
  
  else if (textSize == 4){
    //Each letter is 20? pixels wide with average of 4? pixel spacing, also only need half of length. 24 * 1/2 = 12
    xCenter = 160 - 12*length;
  }

  return xCenter;
}
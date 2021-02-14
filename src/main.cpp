#include "main.h"

//--------------------------- SETUP --------------------------------------
void setup()
{ 
  //Establish IAS config variables
  IAS.preSetAutoUpdate(false);
  IAS.preSetAutoConfig(true);
  IAS.preSetDeviceName("LuvBuddy");
  
  //Initialize screen and Pages
  tft.begin();
  tft.setRotation(3); //Rotates display be horizontal with right side as "bottom"
  initPages();

  //Display Loading screen
  tft.fillScreen(ILI9341_LIGHTGREY);
  displayText("LOADING...", 3, 90, 100, ILI9341_BLACK, ILI9341_LIGHTGREY);
  IAS.WiFiSetupAndConnect();

  //Initialize UserData preferences that are saved permanently in Flash
  preferences.begin("UserData", false);

  //Attempt to initialize SD card
  // Serial.println("Initializing SD card...");
  // if (!SD.begin(SD_CS)){
  //   Serial.println("ERROR - SD card initialization failed!");
  //   currentAudio = &emptyOption;

  // }else{
  //   Serial.println("Success!");
  //   //If ESP32 First Boot, retrieve directory and establish AudioFilesInfo.txt file
  //   if (preferences.getInt("firstBoot") == 0){
  //     tft.fillScreen(ILI9341_DARKGREY);
  //     Serial.println("First Boot, adding mp3 files to txt file and reseting preferences");
  //     writeOptionsVectorToTextFile("/AudioFilesInfo.txt", retrieveDirectory());
  //     preferences.putInt("firstBoot", 1);
  //   }
  // }
  tft.begin();
  drawHeader();
  displayText("WiFi Off", 2, 5, 5, ILI9341_WHITE, ILI9341_BLACK);
  drawFooter();
  currentPage->displayPage();

  //setting button pins on ESP32 as inputs
  pinMode(switch_A, INPUT);
  pinMode(switch_B, INPUT);
  pinMode(switch_C, INPUT);
  pinMode(switch_D, INPUT);
  pinMode(switch_E, INPUT);

  
  //Initializing Encoder
  pinMode(ENCODER_CS, OUTPUT);
  pinMode(ENCODER_CLOCK, OUTPUT);
  pinMode(ENCODER_DATA, INPUT);

  digitalWrite(ENCODER_CLOCK, HIGH);
  digitalWrite(ENCODER_CS, LOW);

}

//--------------------------- LOOP --------------------------------------
//running on core 1
void loop(void){

  prevOption = optionSelected;
  prevTab = tabSelected;  
  handleButtonLag();
  screenUpdate();
  headerInfo();

  if (isScrolling && (millis() - ScrollInitiateTimer >= ScrollDelay)){
    scrollingBoxSprite.pushSprite(0, 40);
    scrollingBoxSprite.scroll(scrollDirectionX, 0);
    ScrollInitiateTimer = millis();
    scrollPixelDistance += scrollDirectionX*(-1);
    if (firstScroll){
      firstScroll = false;
      desiredScrollDistance = currentAudio->title.length()*18 - (320 - 50);
    }
    else if (scrollPixelDistance >= desiredScrollDistance){
      scrollingBoxSprite.drawString(currentAudio->title.c_str(), 320, 0, 1);
      scrollPixelDistance = 0;
      desiredScrollDistance = currentAudio->title.length()*18 + 50;
    }
  }
  //vTaskDelay(10);
}

//--------------------------- FUNCTION DEFINITIONS --------------------------------------

void handleButtonLag(){
  currentPress = readSwitch();
  if ((currentPress != lastPress) && currentPress != "Neutral"){
    //On first press: Do action
    buttonResponse(currentPress);
    timeAtPress = millis();
  } else if ((lastPress == currentPress) && lastPress != "Neutral"){
    //on subsequent presses of same button, wait X amount of time before registering next press
    if (millis() - timeAtPress >= buttonDelay){
      buttonResponse(currentPress);
      timeAtPress = millis();
    }
  }
  if (currentPress != "Neutral"){
    lastPress = currentPress;
  }
}

void headerInfo()
{

  if (IAS.isConnected() && !wifiConnected)
  {
    displayText("WiFi On ", 2, 5, 5, ILI9341_WHITE, ILI9341_BLACK);
    wifiConnected = true;
  }
  else if (!IAS.isConnected() && wifiConnected)
  {
    displayText("WiFi Off", 2, 5, 5, ILI9341_WHITE, ILI9341_BLACK);
    wifiConnected = false;
  }

  // tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  // tft.setCursor(110, 5);
  // timeStamp = millis() / 1000;
  // String currentTime = "time" + String(timeStamp);
  // tft.print(currentTime);

  // float sensorReading = (float)analogRead(36);
  // if (sensorReading >= 100)
  // {
  //   batteryVoltage = 3.7 + ((sensorReading / 4096) * 0.5 * (366666 / 365000));
  //   voltageTotal = voltageTotal + batteryVoltage;
  //   numReadings++;
  // }
  // // Averages last 50 readings to help smoothen results
  // if (numReadings == 50)
  // {
  //   batteryVoltage = voltageTotal / 50;
  //   int batteryPercent = 1 + (batteryVoltage - 3.7) * 100 / 0.5;

  //   String batVoltage = String(batteryVoltage) + "V";
  //   String batPercent = String(batteryPercent) + "%";
  //   tft.setCursor(190, 5);
  //   tft.print(batVoltage);
  //   tft.setCursor(260, 5);
  //   tft.print(batPercent);
  //   numReadings = 0;
  //   voltageTotal = 0;
  // }

  //Serial.println(sensorReading);
}


void buttonResponse(String button){
  //check if current option exists before initializing variable
  Option* currentOption = &emptyOption;
  if (currentPage->options.size() >= 1){
    currentOption = currentPage->options[currentPage->currentSelection];
  }
  if (button == "Down" && currentPage->options.size() > 1){
    buttonDelay = defaultDelay;
    optionSelected++;
  }
  if (button == "Left"){
    if (currentOption->hasSlider){
      currentOption->runRespectiveSliderTask(-1);
      buttonDelay = reducedDelay;
      tft.fillRect(currentOption->widgetX + currentOption->sliderValue, currentOption->widgetY, currentOption->widgetWidth - currentOption->sliderValue, currentOption->widgetHeight, ILI9341_BLACK);
    }
    else if (tabSelected > 0 ){
      tabSelected--;
      buttonDelay = increasedDelay;
    }
  }
  if (button == "Right"){
    if (currentOption->hasSlider){
      currentOption->runRespectiveSliderTask(1);
      buttonDelay = reducedDelay;
      tft.fillRect(currentOption->widgetX, currentOption->widgetY, currentOption->sliderValue, currentOption->widgetHeight, ILI9341_WHITE);
    }
    else if (tabSelected < 1 ){
      tabSelected++;
      buttonDelay = increasedDelay;
      }
  }
  if (button == "Up" && currentPage->options.size() > 1){
    buttonDelay = defaultDelay;
    optionSelected--;    
  }
  if (button == "Middle"){
    buttonDelay = defaultDelay;
    int err = 0;
    int last = 0;
    try{
      //check if next page is empty and throw error if so
      if (currentPage->Next.empty()){
        err = 1;
        throw err;
      }else{
        //go to next page
        last = currentPage->currentSelection;
        currentPage->options[last]->isSelected = false; //unselect current option
        currentPage->Next[last]->displayPage(); //display next page
        currentPage->currentSelection = 0; // set current option to zero for page that is being left
        currentPage = currentPage->Next[last]; // update current page to new page
        currentPage->currentSelection = 0; // set current option to zero for new page
        prevOption = optionSelected = 0;
      }
    }
    //catch error (next page is empty) and rather than go to next page, run the respective task of the currently selected option
    catch(int err){
      if (currentPage->options[currentPage->currentSelection]->title == "<Back"){
        backPage();
      }else if (currentPage->options.size() >= 1){
        currentPage->options[currentPage->currentSelection]->runRespectiveTask();
      } 
    }
  }
}

void initPages(){
  //SETTINGS PAGE
  FirmwarePage.Prev = &SettingsPage;
  WiFiPage.Prev = &SettingsPage;
  vector<Page*> SettingsPages = {&WiFiPage, &FirmwarePage};
  SettingsPage.Next = SettingsPages;

  //Initialize colors
  EmptyPage.backgroundColor = ILI9341_BLACK;
  MainPage.backgroundColor = ILI9341_BLUE;
  SettingsPage.backgroundColor = ILI9341_BLACK;
  WiFiPage.backgroundColor = ILI9341_BLACK;
  FirmwarePage.backgroundColor = ILI9341_BLACK;
}

void screenUpdate(){

  //Vertical option selected change
  if (prevOption != optionSelected){
    //handles wrap around pressing down on last option or up on first option
    if (optionSelected < 0){
      optionSelected = currentPage->numOptions - 1;
    }else if (optionSelected > currentPage->numOptions - 1){
      optionSelected = 0;
    }
    currentPage->currentSelection = optionSelected;
    currentPage->updateOptionSelected(prevOption, optionSelected);
  }
  //Horizontal tab shift
  else if(prevTab != tabSelected){
    //to settings page
    drawFooter();
    
    //sets previously selected option on the page that is being left to 0
    if (currentPage->options.size() >= 1){
      currentPage->options[currentPage->currentSelection]->isSelected = false; //unselect current option
      currentPage->currentSelection = 0; // set current option to zero for that page      
    }
    
    if(tabSelected == 0){
      screenFillDirection("Left", ILI9341_BLACK);
      currentPage = &SettingsPage;
    }
    if(tabSelected == 1){
      if(prevTab == 0){
        screenFillDirection("Right", ILI9341_RED);
      }
      currentPage = &MainPage;
    }
    
    optionSelected = 0; 
    currentPage->displayPage();
  }
}

void drawFooter() {
  tft.fillRect(0, 216, 320, 25, ILI9341_BLACK);
  tft.drawFastHLine(0, 215, 320, ILI9341_WHITE);
  if (tabSelected == 1) {
    displayText("<Settings", 2, 5, 220, ILI9341_WHITE, ILI9341_BLACK);
  } else if (tabSelected == 0) {
    displayText("Menu>", 2, 250, 220, ILI9341_WHITE, ILI9341_BLACK);
  }
}

void drawMainMenu(String direction){
  screenFillDirection(direction, ILI9341_RED);
  displayText("LuvBuddy", 4, 65, 100, ILI9341_WHITE, ILI9341_RED);
}

void backPage(){
  currentPage = currentPage->Prev;
  currentPage->displayPage();
}

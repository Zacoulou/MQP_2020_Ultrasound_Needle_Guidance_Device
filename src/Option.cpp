#include "Option.h"

void Option::displayItem(int xPos, int yPos, int size, boolean isSelected, uint16_t textColor, uint16_t highlight)
{
    if (this->hasBitmap){
        //Sets favorite button to selected if current song is on the favorites list
        // if (currentAudio->isFavorite){
        //     FavoriteOption.bitmap = MiniHeartSmoothFilled;
        // }else{
        //     FavoriteOption.bitmap = MiniHeartSmooth;
        // }
        //cover past bitmap with background color
        tft.fillRect(this->widgetX, this->widgetY, this->widgetWidth, this->widgetHeight, ILI9341_RED);
        //When selected display bitmap in textcolor, else display in highlight color
        if (isSelected){
            tft.drawBitmap(this->widgetX, this->widgetY, this->bitmap, this->widgetWidth, this->widgetHeight, textColor);
        }else{
            tft.drawBitmap(this->widgetX, this->widgetY, this->bitmap, this->widgetWidth, this->widgetHeight, highlight);
        }
        
    }else if (this->hasSlider){
        if (isSelected){
            tft.fillRect(this->widgetX - 5, this->widgetY - 5, this->widgetWidth + 10, this->widgetHeight + 10, ILI9341_DARKGREY);
        }else{
            tft.fillRect(this->widgetX - 5, this->widgetY - 5, this->widgetWidth + 10, this->widgetHeight + 10, ILI9341_RED);
        }
        tft.fillRect(this->widgetX, this->widgetY, this->sliderValue, this->widgetHeight, textColor);
        tft.fillRect(this->widgetX + this->sliderValue, this->widgetY, this->widgetWidth - this->sliderValue, this->widgetHeight, highlight);
    }else{
        String tempTitle = this->title;
        if (this->title.length() > 24){
            tempTitle.remove(tempTitle.length() - (tempTitle.length()-21), tempTitle.length()-21);
            tempTitle += "...";  
        }
        
        if (isSelected){
            displayText(tempTitle, size, xPos, yPos, highlight, textColor);
        }else{
            displayText(tempTitle, size, xPos, yPos, textColor, highlight);
        }
    }

}

void Option::runRespectiveTask(){

    // if(this->type == "message"){
    //     //Closes previous audioFile to free space for next file
    //     if (!audioDone){
    //         mp3->stop();
    //         id3->close();
    //     }
    //     playMessage(this->fileName);
    //     currentAudio = this;
    //     PlayPauseOption.bitmap = PauseButton;
    //     audioDone = false;
    // }

    if(this->title == "Update"){checkUpdate();}
    if(this->title == "Network Details"){displayNetworkDetails();}
    if(this->title == "Device Details"){displayDeviceDetails();}
    if(this->title == "Firmware Details"){displayFirmwareDetails();}
    if(this->title == "Disconnect"){wifiDisconnect();}
    if(this->title == "Reconnect"){wifiConnect();}
    if(this->title == "Configure New Network"){configureNewNetwork();}
    // if(this->title == "Play/Pause"){playPause();}
    // if(this->title == "Favorite"){favoriteItem();}
    if(this->title == "Reset Device"){resetDevice();}
}

void Option::runRespectiveSliderTask(int side){
    if(this->title == "VolumeBar"){volumeControl(side*0.01);}
}

void Option::checkUpdate(){
    screenFillDirection("Down", ILI9341_BLACK);

    IAS.onFirmwareUpdateDownload([](){
        configStruct configData;
        IAS.readConfig(configData);
        displayText("Update Available", 2, centerX("Update Available", 2), 70, ILI9341_WHITE, ILI9341_BLACK);
        displayText("Downloading Latest Version", 2, centerX("Downloading Latest Version", 2), 90, ILI9341_WHITE, ILI9341_BLACK);
    });

    IAS.onFirmwareUpdateError([](){
        displayText("Update Failed", 2, centerX("Update Failed", 2), 110, ILI9341_BLACK, ILI9341_WHITE);
    });

    IAS.onFirmwareUpdateSuccess([](){
        displayText("Update Successful", 2, centerX("Updated Successful", 2), 110, ILI9341_BLACK, ILI9341_WHITE);
    });

    if(IAS.isConnected()){
        configStruct configDataBefore;
        IAS.readConfig(configDataBefore);
        String prevVersion = (String)configDataBefore.appVersion;
        
        displayText("Checking for update...", 2, centerX("Checking for update...", 2), 50, ILI9341_WHITE, ILI9341_BLACK);
        IAS.callHome();
        
        configStruct configDataAfter;
        IAS.readConfig(configDataAfter);
        String currVersion = (String)configDataAfter.appVersion;

        if (prevVersion == currVersion){
            displayText("No Updates Available", 2, centerX("No Updates Available", 2), 70, ILI9341_WHITE, ILI9341_BLACK);
        }

    }else{
        displayText("Please connect to WiFi", 2, centerX("Please connect to WiFi", 2), 100, ILI9341_WHITE, ILI9341_BLACK);
        displayText("before updating", 2, centerX("before updating", 2), 120, ILI9341_WHITE, ILI9341_BLACK);
    }
}

void Option::displayDeviceDetails(){
    screenFillDirection("Down", ILI9341_BLACK);
    configStruct configData;
    IAS.readConfig(configData);
    displayText("Device Name:", 2, centerX("Device Name:", 2), 50, ILI9341_WHITE, ILI9341_BLACK);
    displayText((String)configData.deviceName, 2, centerX((String)configData.deviceName, 2), 70, ILI9341_WHITE, ILI9341_BLACK);

    displayText("MAC Address:" , 2, centerX("MAC Address:", 2), 100, ILI9341_WHITE, ILI9341_BLACK);
    displayText(WiFi.macAddress(), 2, centerX(WiFi.macAddress(), 2), 120, ILI9341_WHITE, ILI9341_BLACK);
    
    displayText("Local IP Address (IPv4):", 2, centerX("Local IP Address (IPv6):", 2), 150, ILI9341_WHITE, ILI9341_BLACK);
    displayText(WiFi.localIP().toString(), 2, centerX(WiFi.localIP().toString(), 2), 170, ILI9341_WHITE, ILI9341_BLACK);

}

void Option::displayNetworkDetails(){
    screenFillDirection("Down", ILI9341_BLACK);

    displayText("Status:", 2, centerX("Status:", 2), 50, ILI9341_WHITE, ILI9341_BLACK);
    if (IAS.isConnected()){
        displayText("Connected", 2, centerX("Connected", 2), 70, ILI9341_WHITE, ILI9341_BLACK);
        displayText("WiFi Network:", 2, centerX("WiFi Network:", 2), 100, ILI9341_WHITE, ILI9341_BLACK);
        displayText(WiFi.SSID(), 2, centerX(WiFi.SSID(), 2), 120, ILI9341_WHITE, ILI9341_BLACK);

        displayText("Network Address:", 2, centerX("Network Address:", 2), 150, ILI9341_WHITE, ILI9341_BLACK);
        displayText(WiFi.networkID().toString(), 2, centerX(WiFi.networkID().toString(), 2), 170, ILI9341_WHITE, ILI9341_BLACK);
    }else{
        displayText("Disconnected", 2, centerX("Disconnected", 2), 70, ILI9341_WHITE, ILI9341_BLACK);
    }
}

void Option::displayFirmwareDetails(){
    screenFillDirection("Down", ILI9341_BLACK);
    configStruct configData;
    IAS.readConfig(configData);
    displayText("Current Firmware:", 2, centerX("Current Firmware:", 2), 50, ILI9341_WHITE, ILI9341_BLACK);
    displayText((String)configData.appVersion, 2, centerX((String)configData.appVersion, 2), 70, ILI9341_WHITE, ILI9341_BLACK);

    displayText("Device Name:", 2, centerX("Device Name:", 2), 100, ILI9341_WHITE, ILI9341_BLACK);
    displayText((String)configData.deviceName, 2, centerX((String)configData.deviceName, 2), 120, ILI9341_WHITE, ILI9341_BLACK);
}


void Option::wifiDisconnect(){
    screenFillDirection("Down", ILI9341_BLACK);
    displayText("WiFi Disconnected", 2, centerX("WiFi Disconnected", 2), 100, ILI9341_WHITE, ILI9341_BLACK);
    IAS.WiFiDisconnect();
    
}

void Option::wifiConnect(){
    screenFillDirection("Down", ILI9341_BLACK);
    displayText("Connecting...", 2, centerX("Connecting...", 2), 100, ILI9341_WHITE, ILI9341_BLACK);
    IAS.WiFiSetupAndConnect();

    if (IAS.isConnected()){
        displayText("Connected Successfully", 2, centerX("Connected Successfully", 2), 100, ILI9341_WHITE, ILI9341_BLACK);
    }else{
        displayText("Failed Connection", 2, centerX("Failed Connection", 2), 100, ILI9341_WHITE, ILI9341_BLACK);
    }
}

void Option::configureNewNetwork(){
    screenFillDirection("Down", ILI9341_BLACK);
    configStruct configData;
    IAS.readConfig(configData);
    displayText("On a smartphone/computer,", 2, centerX("On a smartphone/computer,", 2), 50, ILI9341_WHITE, ILI9341_BLACK);
    displayText("connect to WiFi Network:" , 2, centerX("connect to WiFi Network:", 2), 70, ILI9341_WHITE, ILI9341_BLACK);
    displayText((String)configData.deviceName, 2, centerX((String)configData.deviceName, 2), 90, ILI9341_WHITE, ILI9341_BLACK);

    displayText("On an internet browser,", 2, centerX("On an internet browser,", 2), 110, ILI9341_WHITE, ILI9341_BLACK);
    //displayText("search: " + WiFi.softAPIP().toString(), 2, centerX("search: " + WiFi.softAPIP().toString()), 130, ILI9341_WHITE, ILI9341_BLACK);
    displayText("search: 192.168.4.1", 2, centerX("search: 192.168.4.1", 2), 130, ILI9341_WHITE, ILI9341_BLACK);

    displayText("Select network and connect", 2, centerX("Select network and connect", 2), 150, ILI9341_WHITE, ILI9341_BLACK);

    IAS.configureNewNetwork();

    if (IAS.isConnected()){
        displayText("Connected Successfully", 2, centerX("Connected Successfully", 2), 180, ILI9341_BLACK, ILI9341_WHITE);
    }else{
        displayText("Failed Connection", 2, centerX("Failed Connection", 2), 180, ILI9341_BLACK, ILI9341_WHITE);
    }
}

void Option::volumeControl(double V){
    
    audioGain += V;
    //max gain is 4.0, min gain is 0.0 (Audio quality goes down severely after gain of 0.7)
    if (audioGain > 0.7){
        audioGain = 0.7;
    }else if (audioGain <= 0){
        audioGain = 0;
    }
    
    out->SetGain(audioGain);
    this->sliderValue = audioGain*200;
}

void Option::playPause(){
    //if no audio is being played, play last selected audio
    if (audioDone){
        playMessage(currentAudio->fileName);
        audioDone = false;
        this->bitmap = PauseButton;
    }else if (mp3->isRunning()){
        //0 to pause
        mp3->pausePlay(0);
        this->bitmap = PlayButton;
        tft.fillRect(this->widgetX, this->widgetY, this->widgetWidth, this->widgetHeight, ILI9341_RED);
        this->displayItem(this->widgetX, this->widgetY, 0, this->isSelected, ILI9341_WHITE, ILI9341_BLACK);
    }else{
        //1 to play
        mp3->pausePlay(1);
        this->bitmap = PauseButton; 
    }

    this->displayItem(this->widgetX, this->widgetY, 0, this->isSelected, ILI9341_WHITE, ILI9341_BLACK);
}

void Option::favoriteItem(){
    if (!currentAudio->isFavorite){
        currentAudio->isFavorite = true;
        this->bitmap = MiniHeartSmoothFilled;
    }else{
        currentAudio->isFavorite = false;
        this->bitmap = MiniHeartSmooth;
    }
    this->displayItem(this->widgetX, this->widgetY, 0, this->isSelected, ILI9341_WHITE, ILI9341_BLACK);
    updateAudioFilesList = true;
}

void Option::resetDevice(){
    //Sets ESP32 to first boot
    Serial.println("Device Reset");
    preferences.clear();
    preferences.putInt("firstBoot", 0);
}
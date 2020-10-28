#ifndef OPTION_H_
#define OPTION_H_

#include "OTA.h"
#include "Audio.h"
#include <arduino.h>
#include <vector>
#include <stdint.h>
using namespace std;

extern boolean updateAudioFilesList;

//OPTION CLASS
class Option{
    public:
    //Menu option variables
    String title;
    boolean isSelected = false;
    int size;
    int xPos;
    int yPos;
    const unsigned char *bitmap;
    bool hasBitmap = false;
    bool hasSlider = false;
    double sliderValue;
    int widgetHeight;
    int widgetWidth;
    int widgetX;
    int widgetY;

    //Message variables
    String type;
    String fileName;
    String senderName;
    boolean isFavorite = false;

    //Constructor for written options
    Option(String name){
        title = name;
        size = 2;
        hasBitmap = false;
    }
    //Constructor for options with a bitmap
    Option(String name, const unsigned char *bm, int x, int y, int w, int h){
        title = name;
        bitmap = bm;
        widgetX = x;
        widgetY = y;
        widgetWidth = w;
        widgetHeight = h;
        hasBitmap = true;
    }
    //Constructor for options with a slider
    Option(String name, double value, int x, int y, int w, int h){
        title = name;
        widgetX = x;
        widgetY = y;
        widgetWidth = w;
        widgetHeight = h;
        hasSlider = true;
        sliderValue = value;
    }

    void displayItem(int xPos, int yPos, int size, boolean isSelected, uint16_t textColor, uint16_t highlight);
    void runRespectiveTask();
    void runRespectiveSliderTask(int direction);

    void checkUpdate();
    void displayDeviceDetails();
    void displayFirmwareDetails();
    void wifiDisconnect();
    void wifiConnect();
    void displayNetworkDetails();
    void configureNewNetwork();
    void playPause();
    void volumeControl(double V);
    void favoriteItem();
    void resetDevice();

    //Destructor
    //~Option();
};


// //MESSAGE CLASS
// class Message : public Option {
//   public:
//     String fileName;
//     String senderName;
//     bool isFavorite;

//     Message(String Name, String FileName)
//       : Option{Name},
//         fileName{FileName},
//         isFavorite{false}
//     {
//     }

// };



extern Option FavoriteOption;
extern Option* currentAudio;
extern Option PlayPauseOption;
extern Option BackButton;
extern Preferences preferences;
#endif
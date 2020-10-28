#include "SDFiles.h"


void writeOptionsVectorToTextFile(const char *filePath, vector<Option*> audioFiles){
  //Serial.println("writing to txt");
  allAudioFiles = SD.open(filePath, FILE_WRITE);
  int sentinel = audioFiles.size();
  int startingIndex = 0;
  if (audioFiles[0]->type != "message"){
    sentinel--;
    startingIndex = 1;
  }
  //Serial.println("sentinel:" + (String)sentinel);
  allAudioFiles.println(sentinel);
  for (int i = startingIndex; i < sentinel + startingIndex; i++){
    if (audioFiles[i]->type == "message"){
      allAudioFiles.println(audioFiles[i]->fileName + '|' + audioFiles[i]->isFavorite);
    }
    //Serial.println(audioFiles[i]->fileName + '|' + audioFiles[i]->isFavorite);
  }
  allAudioFiles.close();
}

vector<Option*> readAudioVectorFromTextFile(const char *filePath){
    //Serial.println("reading from txt");
    vector<Option*> options;
    allAudioFiles = SD.open(filePath, FILE_READ);
    int sentinel = allAudioFiles.parseInt();
    //Serial.println(sentinel);

    options.push_back(&BackButton);
    for (int i = 0; i < sentinel; i++){
        String audioName;
        int isFav;
        audioName = allAudioFiles.readStringUntil('|');
        isFav = allAudioFiles.parseInt();
        Option* audioFile = convertFileNameToOption(audioName);
        audioFile->isFavorite = isFav;
        options.push_back(audioFile);
        //Serial.println(audioName + " | " + isFav);
    }
    allAudioFiles.close();

    return options;
}

// vector<Option*> extractFavoritesFromTextFile(const char *filePath){
//     //Serial.println("extracting favorites from txt");
//     vector<Option*> options;
//     allAudioFiles = SD.open(filePath, FILE_READ);
//     int sentinel = allAudioFiles.parseInt();
//     options.push_back(&BackButton);

//     for (int i = 0; i < sentinel; i++){
//         String audioName;
//         int isFav;
//         audioName = allAudioFiles.readStringUntil('|');
//         isFav = allAudioFiles.parseInt();
//         if (isFav){
//             Option* audioFile = convertFileNameToOption(audioName);
//             audioFile->isFavorite = isFav;
//             options.push_back(audioFile);
//             //Serial.println(audioName + " | " + isFav);  
//         }
//     }
//     allAudioFiles.close();

//     return options;
// }

vector<Option*> extractFavoritesFromPage(Page* page){
    //Serial.println("extracting favorites from page");
    vector<Option*> options = {};
    options.push_back(&BackButton);
    for (int i = 0; i < page->numOptions; i++){
        if (page->options[i]->isFavorite && page->options[i]->type == "message"){
            options.push_back(page->options[i]);
        }
    }
    return options;
}

Option* convertFileNameToOption(String fileName){
  
    while (!fileName.startsWith("/")){
      fileName.remove(0, 1); //removes anything before "/"
    }
    String condensedName = fileName;
    condensedName.remove(0, 1); //removes backslash from front of name
    condensedName.remove(condensedName.length() - 4, 4); //removes ".mp3" from end of string
    Option* m = new Option(condensedName);
    m->fileName = fileName;
    m->type = "message";

    return m;
}

//Looks through the SD card and adds all names of messages (mp3 files) to the messageList vector
vector<Option*> retrieveDirectory() {
  root = SD.open("/");
  vector<Option*> messageList = {};
  String mp3type = ".mp3";
  String name;
  
  while (true) {
    File entry =  root.openNextFile();
    
    //exits loop once there are no more files to check
    if (!entry) {
      break;
    }
    name = entry.name();
    if (name.endsWith(mp3type)){
        messageList.push_back(convertFileNameToOption(name));
    }
    entry.close();
  }
  root.close();

  return messageList;
}


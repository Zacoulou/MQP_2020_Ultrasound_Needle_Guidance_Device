#ifndef _SDFILES_H_
#define _SDFILES_H_

#include "Page.h"

extern File root;
extern File allAudioFiles;

//FUNCTION PROTOTYPES
void writeOptionsVectorToTextFile(const char *filePath, vector<Option*> audioFiles);
vector<Option*> readAudioVectorFromTextFile(const char *filePath);
//vector<Option*> extractFavoritesFromTextFile(const char *filePath);
vector<Option*> extractFavoritesFromPage(Page* page);
Option* convertFileNameToOption(String fileName);
vector<Option*> retrieveDirectory();



#endif /* _SDFILES_H_ */
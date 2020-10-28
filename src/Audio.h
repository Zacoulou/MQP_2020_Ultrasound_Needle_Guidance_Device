#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <Arduino.h>
#include "Display.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourceSD.h"

using namespace std;

extern AudioFileSource *file;
extern AudioGeneratorMP3 *mp3;
extern AudioOutputI2S *out;
extern AudioFileSourceID3 *id3;
extern File root;
extern double audioGain;
extern boolean audioDone;
//Function Definitions
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string);
void playMessage(String m);


#endif /* _AUDIO_H_ */
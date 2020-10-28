#include "Audio.h"

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
    (void)cbData;
    Serial.printf("ID3 callback for: %s = '", type);

    if (isUnicode)
    {
        string += 2;
    }

    while (*string)
    {
        char a = *(string++);
        if (isUnicode)
        {
            string++;
        }
        Serial.printf("%c", a);
    }
    Serial.printf("'\n");
    Serial.flush();
}

void playMessage(String m){
    file = new AudioFileSourceSD(m.c_str());
    id3 = new AudioFileSourceID3(file);
    id3->RegisterMetadataCB(MDCallback, (void *)"ID3TAG");
    out->SetGain(audioGain);
    mp3->begin(id3, out);
}


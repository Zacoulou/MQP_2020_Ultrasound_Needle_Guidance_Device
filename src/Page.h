#ifndef PAGE_H_
#define PAGE_H_

#include <arduino.h>
#include "Option.h"

using namespace std;

extern int PageOptionstartX;
extern int PageOptionstartY;
extern int previousPageOptionStartIndex;
extern int previousPageOptionEndIndex;
extern TFT_eSprite scrollingBoxSprite;
extern boolean isScrolling;
extern boolean firstScroll;
extern int scrollPixelDistance;

class Decor{
    public:

    const unsigned char *bitmap;
    int xPos;
    int yPos;
    int width;
    int height;

    //constructor for decoration
    Decor(const unsigned char *bm, int x, int y, int w, int h){
        bitmap = bm;
        xPos = x;
        yPos = y;
        width = w;
        height = h;
    }
};

class Page{
    public:

    int currentSelection;
    int maxOptionsPerPage = 7;
    String title;
    int numOptions;
    vector<Option*> options;
    vector<Page*> Next;
    Page *Prev;
    vector<Decor*> Decorations;
    //boolean displayTitle = true;
    uint32_t backgroundColor;
    
    //Constructor for empty page
    Page(String name){
        currentSelection = 0;
        title = name;
    }

    //Constructor for default page
    Page(String name, vector<Option*> allOptions){
        currentSelection = 0;
        title = name;
        numOptions = allOptions.size();
        options = allOptions;
    }

    //Constructor for Page with Decorations
    Page(String name, vector<Option*> allOptions, vector<Decor*> details){
        currentSelection = 0;
        title = name;
        numOptions = allOptions.size();
        options = allOptions;
        Decorations = details;
    }

    void displayPage();
    void updateOptionSelected(int currSelection, int nextSelection);
    void updateScrollBar();
    //Destructor
    //~Page();

};

#endif
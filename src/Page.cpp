#include "Page.h"


void Page::displayPage(){
    screenFillDirection("Down", this->backgroundColor);
    isScrolling = false;
    
    //Draw page title
    if (this->title.length() <= 15){
        displayText(this->title, 3, centerX(this->title, 3), 40, ILI9341_WHITE, this->backgroundColor);
    }else{
        scrollingBoxSprite.setColorDepth(8);
        scrollingBoxSprite.createSprite(2000, 24); //large width for scrolling feature
        scrollingBoxSprite.fillSprite(this->backgroundColor);
        scrollingBoxSprite.setScrollRect(0, 0, 2000, 24, this->backgroundColor); //large width for scrolling feature
        scrollingBoxSprite.setTextColor(ILI9341_WHITE, this->backgroundColor);
        scrollingBoxSprite.textsize = 3;
        scrollingBoxSprite.drawString(this->title.c_str(), 0, 0, 1);
        isScrolling = true;
        firstScroll = true;
        scrollPixelDistance = 0;
    }

    int numItemsOnPage = this->options.size();
    if (numItemsOnPage > this->maxOptionsPerPage){
        numItemsOnPage = this->maxOptionsPerPage;
        previousPageOptionEndIndex = numItemsOnPage - 1;
        previousPageOptionStartIndex = 0;
        updateScrollBar();
    }

    //Loop through option instances and print each one
    if (!this->options.empty()){
        this->options[0]->isSelected = true; //First item is always selected at start
        for (int i = 0; i < numItemsOnPage; i++){
            Option* curr = this->options[i];
            curr->yPos = PageOptionstartY + 20*i;
            curr->xPos = PageOptionstartX;
            curr->displayItem(curr->xPos, curr->yPos, curr->size, curr->isSelected, ILI9341_WHITE, this->backgroundColor);
        }

        previousPageOptionEndIndex = numItemsOnPage - 1;
        previousPageOptionStartIndex = 0;
    }

    if (!this->Decorations.empty()){
        for(int i = 0; i < Decorations.size(); i++){
            Decor* currDec = this->Decorations[i];
            tft.drawBitmap(currDec->xPos, currDec->yPos, currDec->bitmap, currDec->width, currDec->height, ILI9341_WHITE);
        }
    }    
}

void Page::updateOptionSelected(int oldSelection, int nextSelection){
    Option* old = this->options[oldSelection];
    Option* next = this->options[nextSelection];

    old->isSelected = false;
    next->isSelected = true;

    if (this->options.size() <= this->maxOptionsPerPage || (nextSelection <= previousPageOptionEndIndex && nextSelection >= previousPageOptionStartIndex)){ //nextSelection <= this->maxOptionsPerPage-1
        old->displayItem(old->xPos, old->yPos, old->size, old->isSelected, ILI9341_WHITE, this->backgroundColor);
        next->displayItem(next->xPos, next->yPos, next->size, next->isSelected, ILI9341_WHITE, this->backgroundColor); 
    }
    else { //if (nextSelection > previousPageOptionEndIndex || nextSelection < previousPageOptionStartIndex)
        int counter = 0;
        int endIndex = 0; //nextSelection
        int startIndex = 0; //endIndex - (this->maxOptionsPerPage - 1)

        //handles edge case where you reach bottom or top of page
        if (nextSelection == 0 || nextSelection > this->options.size() - 1){
            startIndex = 0;
            endIndex = this->maxOptionsPerPage - 1;
        } 
        //Going up
        if (nextSelection == oldSelection + 1){
            startIndex = previousPageOptionStartIndex + 1;
            endIndex = previousPageOptionEndIndex + 1;
        }
        //edge case where at at top of page and press up to go to bottom
        else if (nextSelection == this->options.size() - 1){
            endIndex = nextSelection;
            startIndex = endIndex - (this->maxOptionsPerPage - 1);
        }
        //Going down
        else if (nextSelection == oldSelection - 1){
            startIndex = previousPageOptionStartIndex - 1;
            endIndex = previousPageOptionEndIndex - 1; 
        }

        tft.fillRect(PageOptionstartX, PageOptionstartY, 320- PageOptionstartX*2, 20*maxOptionsPerPage, ILI9341_BLACK);
        for (int i = startIndex; i <= endIndex; i++){
            Option* curr = this->options[i];
            curr->yPos = PageOptionstartY + 20*counter;
            curr->xPos = PageOptionstartX;
            curr->displayItem(curr->xPos, curr->yPos, curr->size, curr->isSelected, ILI9341_WHITE, this->backgroundColor);
            counter++;
        }
        previousPageOptionStartIndex = startIndex;
        previousPageOptionEndIndex = endIndex;
        updateScrollBar();
    }

}

void Page::updateScrollBar(){
    int scrollBarWidth = 10;
    int scrollBarHeight = 20*maxOptionsPerPage;
    int scrollBarX = 320 - PageOptionstartX - scrollBarWidth; 
    double scrollBarIndicatorHeight = ((double)this->maxOptionsPerPage / (double)this->options.size())* scrollBarHeight;
    double scrollBarIndicatorY = PageOptionstartY + ((double)previousPageOptionStartIndex / (double)this->options.size())*scrollBarHeight;

    tft.fillRect(scrollBarX,PageOptionstartY,scrollBarWidth, scrollBarHeight-1, ILI9341_WHITE);
    tft.fillRect(scrollBarX,scrollBarIndicatorY,scrollBarWidth, scrollBarIndicatorHeight, ILI9341_RED);
}

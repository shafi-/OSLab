#include "configuration.h"
#include "LookupResult.cpp"
#include "TranslationLookaheadBuffer.cpp"
#ifndef PageTable_Class
#define PageTable_Class

class PageTableEntry
{
    unsigned char index;
    Instruction instruction;
};


class PageTable
{
public:
    /*
    * Add necessary class variables here
    */
    PageTableEntry* pageTable;
    bool* frameBit;

    TranslationLookaheadBuffer *tlb;

    PageTable()
    {
        //write your code here
        pageTable = new PageTableEntry[numberOfPageFrames];

        frameBit = new  bool[numberOfPageFrames];
        for(int i=0; i<numberOfPageFrames; i++)
        {
            frameBit[i] = false;
        }
    }

    void setTranslationLookaheadBuffer(TranslationLookaheadBuffer *tlb){
        //write your code here
        this.tlb = tlb;
    }

    unsigned char getNextFreePageFrame()
    {
        //write your code here
        for(unsigned char i=0; i<numberOfPageFrames; i++)
        {
            if(frameBit[i] == false)
            {
                return i;
            }
        }
        return -1;
    }

    LookupResult lookup(unsigned char pageNumber)
    {
        //write your code here
    }
    void insert(unsigned char pageNumber)
    {
        //write your code here
        unsigned char freeFrame = getNextFreePageFrame();
        /**
         * insert into freeFrame
         */
    }
    void invalidate(unsigned char pageNumber)
    {
        //write your code here
    }
    int getUsedPageCount()
    {
        //write your code here
    }
};
#endif

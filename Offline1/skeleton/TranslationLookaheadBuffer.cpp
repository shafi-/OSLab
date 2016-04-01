#include <map>
#include <iostream>
#include "configuration.h"
#include "LookupResult.cpp"

using namespace std;
#ifndef TranslationLookaheadBuffer_Class
#define TranslationLookaheadBuffer_Class
class TLBEntry
{
    unsigned char virtualPageNumber;
    int pageFrameNumber;
    char access;
    bool validity;
    TLBEntry *next;
    TLBEntry *prev;

    /**
     *  @access r - readonly
     *          w - writeonly
     *          b - read+write
     */
};

class TranslationLookaheadBuffer
{
public:
    /*
    * Add necessary class variables here
    */
    int bufferSize;
    TLBEntry *tableEntry;
    LookupResult returnLookUp;

    TranslationLookaheadBuffer(int size)
    {
        //write your code here
        bufferSize = size;
        table = new TLBEntry[bufferSize];
    }
    /*
    * Append a new TLB Entry into the end of the LRU Linked List
    * Will only be used in the LRU Implementation
    */
    void append(TLBEntry *t)
    {
        //write your code here
    }
    /*
    * Detach a TLB Entry from the LRU Linked List
    * Will only be used in the LRU Implementation
    */
    void detach(TLBEntry *t)
    {
        //write your code here
    }
    LookupResult lookup(unsigned char pageNumber){
        //write your code here
        for(int i=0; i<bufferSize; i++)
        {
            if(tableEntry[i].virtualPageNumber == pageNumber)
            {
                if(tableEntry[i].validity){
                    returnLookUp.frameIndex = tableEntry[i].pageFrameNumber;
                    returnLookUp.isFound = true;
                }
                else
                {
                    returnLookUp.isFound = false;
                }
                return returnLookUp;
            }
        }
        returnLookUp.isFound = false;
        return new returnLookUp;
    }
    void insert(unsigned char pageNumber, unsigned char frameIndex)
    {
        //write your code here
        int freeIndex = getFreeSpace();
        tableEntry[freeIndex].virtualPageNumber = pageNumber;
        tableEntry[freeIndex].pageFrameNumber = frameIndex;
        tableEntry[freeIndex].validity = true;
    }
    void print()
    {
        //write your code here
        for(int i=0; i<bufferSize; i++)
        {
            cout<<table[i].virtualPageNumber<<" "<<table[i].pageFrameNumber<<" "<<table[i].access<<endl;
        }
    }

    void invalidate(unsigned char pageNumber)
    {
        //write your code here
        for(int i=0; i<bufferSize; i++)
        {
            if(tableEntry[i].virtualPageNumber == pageNumber)
            {
                tableEntry[i].validity = false;
                tableEntry[i].next = nullptr;
                tableEntry[i].next = nullptr;
                tableEntry[i].virtualPageNumber = NULL;
                tableEntry[i].pageFrameNumber = NULL;
            }
        }
    }
};
#endif

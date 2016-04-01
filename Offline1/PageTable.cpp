#include "configuration.h"
#include "LookupResult.cpp"
#include "TranslationLookaheadBuffer.cpp"
#ifndef PageTable_Class
#define PageTable_Class

class PageTableEntry
{
public:
	unsigned char frameIndex;
	bool validity;
	bool isUsed;
};


class PageTable
{
public:
    /*
    * Add necessary class variables here
    */
	PageTableEntry pageTable[16][16];
	TranslationLookaheadBuffer *tLB;
	int numberOfFrames;
	bool *Frames;

    PageTable()
    {
        //write your code here
		/**
		 * @setup pageTable
		 */
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				pageTable[i][j].validity = false;
				pageTable[i][j].isUsed = false;
			}
		}
		/**
		 *
		 *	@setup Frames
		 */
		numberOfFrames = numberOfPageFrames;
		Frames = new bool[numberOfFrames];
		for (int i = 0; i < numberOfFrames; i++)
		{
			Frames[i] = false;
		}
    }
    void setTranslationLookaheadBuffer(TranslationLookaheadBuffer *tlb){
        //write your code here
		tLB = tlb;
    }
    unsigned char getNextFreePageFrame()
    {
        //write your code here
		for (int i = 0; i < numberOfFrames; i++)
		{
			if (Frames[i] == false)
			{
				return i;
			}
		}
		return (numberOfFrames - 1);
    }
    LookupResult lookup(unsigned char pageNumber)
    {
        //write your code here
		LookupResult lur;
		lur.isFound = false;
		int firstIndex = getFirstFourBits(pageNumber);
		int lastIndex = getLastFourbits(pageNumber);
		if (pageTable[firstIndex][lastIndex].validity == true)
		{
			lur.frameIndex = pageTable[firstIndex][lastIndex].frameIndex;
			lur.isFound = true;
		}
		return lur;
    }
    void insert(unsigned char pageNumber)
    {
        //write your code here
		int index = getNextFreePageFrame();
		int firstFour = getFirstFourBits(pageNumber);
		int lastFour = getLastFourbits(pageNumber);
		pageTable[firstFour][lastFour].frameIndex = index;
		pageTable[firstFour][lastFour].validity = true;
		pageTable[firstFour][lastFour].isUsed = true;
		Frames[index] = true;
    }
    void invalidate(unsigned char pageNumber)
    {
        //write your code here
		int firstIndex = getFirstFourBits(pageNumber);
		int lastIndex = getLastFourbits(pageNumber);
		pageTable[firstIndex][lastIndex].validity = false;
		tLB->invalidate(pageNumber);
    }
    int getUsedPageCount()
    {
        //write your code here
		int count = 0;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (pageTable[i][j].isUsed)
					count++;
			}
		}
		return count;
    }

	int getFirstFourBits(unsigned char number)
	{
		number = number >> 4;
		return (int)number;
	}

	int getLastFourbits(unsigned char number)
	{
		number = number << 4;
		number = number >> 4;
		return (int)number;
	}
};
#endif

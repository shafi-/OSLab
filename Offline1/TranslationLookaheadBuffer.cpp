#include <map>
#include <iostream>
#include "configuration.h"
#include "LookupResult.cpp"
#include <vector>

using namespace std;
#ifndef TranslationLookaheadBuffer_Class
#define TranslationLookaheadBuffer_Class

class TLBEntry
{
public:
	unsigned char msbOfVirtualAddress;
	unsigned char frameIndex;
	bool validity;
};

class TranslationLookaheadBuffer
{
public:
    /*
    * Add necessary class variables here
    */
	unsigned char tableSize;
	vector<TLBEntry> table;
	int iterator;

    TranslationLookaheadBuffer(int size)
    {
		tableSize = size;
		cout << "TLB size: " << (int)tableSize << endl;
		TLBEntry tlbEntry;
		tlbEntry.validity = false;
        //write your code here
		for (int i = 0; i < size; i++)
		{
			table.push_back(tlbEntry);
		}
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
		LookupResult lookupResult;
		lookupResult.isFound = false;
		
		for (iterator = 0; iterator < tableSize; iterator++)
		{
			if (table[iterator].msbOfVirtualAddress == pageNumber)
			{
				if (table[iterator].validity)
				{
					lookupResult.isFound = true;
					lookupResult.frameIndex = table[iterator].frameIndex;
					return lookupResult;
				}
			}
		}
		return lookupResult;

    }
    
	int getFreeIndex()
	{
		int index = -1;
		for (iterator = 0; iterator < tableSize; iterator++)
		{
			if (table[iterator].validity == false)
			{
				return iterator;
			}
		}
		index = tableSize - 1;
		table[index].validity = false;
		return index;
	}

	void insert(unsigned char pageNumber, unsigned char frameIndex)
    {
        //write your code here
		int freeIndex = getFreeIndex();
		table[freeIndex].frameIndex = frameIndex;
		table[freeIndex].msbOfVirtualAddress = pageNumber;
		table[freeIndex].validity = true;
    }

    void print()
    {
        //write your code here
		cout << "VirtualpageNumber\tFrameNumber\tValidity\n";

		for (iterator = 0; iterator < tableSize; iterator++)
		{
			cout << table[iterator].msbOfVirtualAddress << "\t" << table[iterator].frameIndex << "\t" << table[iterator].validity << endl;
		}
    }
    void invalidate(unsigned char pageNumber)
    {
        //write your code here
		for (iterator = 0; iterator < tableSize; iterator++)
		{
			if (table[iterator].msbOfVirtualAddress == pageNumber)
			{
				table[iterator].validity = false;
				break;
			}
		}
    }
};
#endif

//%~!@#$%^&*()
//-*- coding: utf-8 -*-
//__author__ = 'tanvir'

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "configuration.h"
#include "Instruction.cpp"
#include "PageTable.cpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "LookupResult.cpp"
#include "TranslationLookaheadBuffer.cpp"

using namespace std;

unsigned int getNearestBiggerPowerOfTwo(unsigned int a)
{
    unsigned int res = 1;
    while(res < a)
    {
        res = res << 1;
    }
    return res;
}

int currentInstructionPageNumber = 0;
int totalNumberOfCacheMisses = 0;
int totalNumberOfPageFaults = 0;
int pageChangeCount = 0;

Instruction getNextInstruction()
{
    int prev=currentInstructionPageNumber;
    if((rand() % pageChangeAfterInstructionCount) == 0)
    {
        currentInstructionPageNumber = rand() % numberOfVirtualPages;
    }
    if(prev!=currentInstructionPageNumber)pageChangeCount+=1;
    Instruction i(currentInstructionPageNumber);
    return i;
}

int main(int argc, char **argv)
{
    //cout<<argc<<endl;
    //srand((int)time(NULL));
    for(int i = 1; i < argc; i++)
    {
        if(i == 1)
        {
            if(strcmp(argv[i], "1") == 0)
            {
                debugMode = true;
            } else {
                debugMode = false;
            }
        } else if(i == 2)
        {
            sscanf(argv[i],"%d",&numberOfTLBEntries);
            numberOfTLBEntries = getNearestBiggerPowerOfTwo(numberOfTLBEntries);
        } else if(i == 3)
        {
            sscanf(argv[i],"%d",&numberOfPageFrames);
            numberOfPageFrames = getNearestBiggerPowerOfTwo(numberOfPageFrames);
        } else if(i == 4)
        {
            sscanf(argv[i],"%d",&numberOfInstructions);
        } else if(i == 5)
        {
            sscanf(argv[i],"%d",&pageChangeAfterInstructionCount);
        }
    }
    cout<<"Debug Mode: "<<debugMode<<endl;
    cout<<"Total number of TLB Entries: "<<numberOfTLBEntries<<endl;
    cout<<"Total number of Page Frames: "<<numberOfPageFrames<<endl;
    cout<<"Total number of Instructions: "<<numberOfInstructions<<endl;
    cout<<"Total number of Virtual Pages: "<<numberOfVirtualPages<<endl;
    cout<<"On Average Virtual Address Page Changes after: "<<pageChangeAfterInstructionCount<<endl;

    PageTable pageTable;
    TranslationLookaheadBuffer tlb(numberOfTLBEntries);
    pageTable.setTranslationLookaheadBuffer(&tlb);

    for(unsigned int i = 0; i < numberOfInstructions; i++)
    {
        Instruction nextInstruction = getNextInstruction();
        if(debugMode)
        {
            nextInstruction.print();
        }
        LookupResult l = tlb.lookup(nextInstruction.msbAddress);
        if(l.isFound == true)
        {
            //do nothing
        } else
        {
            if(debugMode)
            {
                printf("Cache Miss for page %02x\n",nextInstruction.msbAddress);
            }
            totalNumberOfCacheMisses += 1;
            l = pageTable.lookup(nextInstruction.msbAddress);
            if(l.isFound == true)
            {
                //do nothing
            } else
            {
                if(debugMode)
                {
                    printf("Page fault on page %02x\n",nextInstruction.msbAddress);
                }
                totalNumberOfPageFaults += 1;
                pageTable.insert(nextInstruction.msbAddress);
                l = pageTable.lookup(nextInstruction.msbAddress);
/*				if (debugMode)
				{
					cout << "Lookup result: " << (int)l.frameIndex << "\t" << l.isFound << endl;
				}*/
            }
            tlb.insert(nextInstruction.msbAddress, l.frameIndex);
			//pageTable.insert(nextInstruction.msbAddress);
            //l = pageTable.lookup(nextInstruction.msbAddress);
        }
        //
        if(debugMode)
        {
            printf("Virtual Address: %02x%02x, Physical Address: %02x%02x\n", nextInstruction.msbAddress, nextInstruction.lsbAddress, l.frameIndex, nextInstruction.lsbAddress);
        }
    }
    cout<<"Total number of Cache Misses: "<<totalNumberOfCacheMisses<<endl;
    cout<<"Total number of Page Faults: "<<totalNumberOfPageFaults<<endl;
    cout<<"Total number of Page Used: "<<pageTable.getUsedPageCount()<<endl;
    cout<<"Total number of Page Changed: "<<pageChangeCount<<endl;
    /*TranslationLookaheadBuffer tlb;
    unsigned char accessPattern[] = "ABACBDADEDAEBAC";
    for(int i = 0; i < 15; i++)
    {
        cout<<i<<","<<accessPattern[i]<<endl;
        LookupResult result = tlb.lookup(accessPattern[i]);
        if(result.isFound)
        {
            tlb.print();
        } else {
            cout<<"Cache Miss"<<endl;
            tlb.insert(accessPattern[i],accessPattern[i]);
            tlb.print();
        }
    }*/
    return 0;
}

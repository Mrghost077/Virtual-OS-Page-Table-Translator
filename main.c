/*
----------------------------------------------------------
EEI5265 - Operating Systems Mini Project
Group A - Page Table Translator

Description:
This program simulates the translation of logical addresses
into physical addresses using one-level paging.

Author: Safwan
Date: August 2026
----------------------------------------------------------
*/

#include <stdio.h>
#include <stdbool.h>

// constraints mentioned in the project specification
#define MAX_PAGES 16
#define PAGE_SIZE 1024
#define MAX_ADDRESSES ((MAX_PAGES * PAGE_SIZE) - 1)
#define MIN_FRAMES 8
#define MAX_FRAMES 16

// Colours
#define C_RST    "\033[0m"
#define C_CYAN   "\033[1;36m"
#define C_WHITE  "\033[1;37m"
#define C_GREEN  "\033[1;32m"
#define C_RED    "\033[1;31m"
#define C_GREY   "\033[0;90m"

// Function Prototypes
void displayTitle();
int getFrameCount();
void createPageTable(int pageTable[MAX_PAGES], int frameCount);
int getLoadedPageCount(int frameCount);
int getValidPageNumber (int pageTable[]);
int getValidFrameNumber(int frameCount, int pageTable[]);
bool isFrameUsed (int pageTable[], int frameNumber);
void translateLogicalAddress(int pageTable[]);
int calculatePageNumber(int logicalAddress);
int calculateOffset(int logicalAddress);
bool isPageFault (int frameNumber);
int getPhysicalAddress(int frameNumber, int offset);
void displayOutput(int logicalAddress, int pageNumber, int offset, int frameNumber, int physicalAddress);

int main (){

    displayTitle();
    int frameCount = getFrameCount();
    int pageTable[MAX_PAGES];
    createPageTable(pageTable, frameCount);
    translateLogicalAddress(pageTable);

    return 0;
}

void translateLogicalAddress(int pageTable[]){
    printf("Enter Logical Address : ");
    int logicalAddress;

    while(1){

        if(scanf("%d",&logicalAddress) != 1){
            printf("Invalid type. Please enter a valid Logical address");
            while(getchar()!='\n');
            logicalAddress = 0;
            continue;
        }

        if(logicalAddress >= PAGE_SIZE * MAX_PAGES || logicalAddress < 0){
            printf("Logical address exceeded the limit. Address should be less that %d", PAGE_SIZE * MAX_PAGES);
            continue;
        }

        int pageNumber = calculatePageNumber(logicalAddress);
        int offset = calculateOffset(logicalAddress);
        int frameNumber = pageTable[pageNumber];
        int physicalAddress = getPhysicalAddress(frameNumber , offset);

        displayOutput(logicalAddress, pageNumber, offset, frameNumber, physicalAddress);

        break;


    }    
}

void displayOutput(int logicalAddress, int pageNumber, int offset, int frameNumber, int physicalAddress){
    if (physicalAddress == -1 ){

        printf(C_GREY "+------------------------------------------------------------+\n");
        printf("|" C_CYAN "                  ADDRESS TRANSLATION RESULT                " C_GREY "|\n");
        printf("+------------------------------------------------------------+\n");
        printf("|  " C_WHITE "Logical Address" C_GREY "   :  " C_WHITE "%-6d" C_GREY "                                " "|\n", logicalAddress);
        printf("|  " C_WHITE "Page Number" C_GREY "       :  " C_WHITE "%-6d" C_GREY "                                " "|\n", pageNumber);
        printf("|  " C_WHITE "Offset" C_GREY "            :  " C_WHITE "%-6d" C_GREY "                                " "|\n", offset);
        printf("|------------------------------------------------------------|\n");
        printf("|  " C_WHITE "Status" C_GREY "            :  " C_RED "[ !! ] PAGE FAULT OCCURRED" C_GREY "            |\n");
        printf("+------------------------------------------------------------+\n" C_RST);
        
    }
    else{
        printf(C_GREY "+------------------------------------------------------------+\n");
        printf("|" C_CYAN "                  ADDRESS TRANSLATION RESULT                " C_GREY "|\n");
        printf("+------------------------------------------------------------+\n");
        printf("|  " C_WHITE "Logical Address" C_GREY "   :  " C_WHITE "%-6d" C_GREY "                                " "|\n", logicalAddress);
        printf("|  " C_WHITE "Page Number" C_GREY "       :  " C_WHITE "%-6d" C_GREY "                                " "|\n", pageNumber);
        printf("|  " C_WHITE "Offset" C_GREY "            :  " C_WHITE "%-6d" C_GREY "                                " "|\n", offset);
        printf("|------------------------------------------------------------|\n");
        printf("|  " C_WHITE "Frame Number" C_GREY "      :  " C_WHITE "%-6d" C_GREY "                                " "|\n", frameNumber);
        printf("|  " C_WHITE "Physical Address" C_GREY "  :  " C_WHITE "%-6d" C_GREY "                                " "|\n", physicalAddress);
        printf("|------------------------------------------------------------|\n");
        printf("|  " C_WHITE "Status" C_GREY "            :  " C_GREEN "[ OK ]  TRANSLATION SUCCESSFUL" C_GREY "        |\n");
        printf("+------------------------------------------------------------+\n" C_RST);
    }
}

int getPhysicalAddress(int frameNumber, int offset){

    if (isPageFault(frameNumber)){
        return -1;
    }
    else{
        int physicalAddress = frameNumber * PAGE_SIZE + offset;
        return physicalAddress;
    }
}

bool isPageFault (int frameNumber){
    if(frameNumber == -1){
       return true;
    }

    return false;
}

int calculateOffset(int logicalAddress){
    int offset = logicalAddress % PAGE_SIZE;
    return offset;
}

int calculatePageNumber(int logicalAddress){
    int pageNumber = logicalAddress / PAGE_SIZE;
    return pageNumber;
}

bool isFrameUsed (int pageTable[], int frameNumber){
    for (int page = 0; page < MAX_PAGES; page++){
        if (pageTable[page] == frameNumber){
            return true;
        }
    }

    return false;
}

int getValidFrameNumber(int frameCount, int pageTable[]){

    int frameNumber;

    while (1){
        printf("Enter the frame number : ");

        if (scanf("%d", &frameNumber) != 1){
            printf ("Invalid type. Please enter a valid number \n");
            while(getchar() != '\n');
            continue;
        }

        if (frameNumber >= frameCount || frameNumber < 0){
            printf("Invalid Frame number. Input should be between 0 and %d \n", frameCount - 1);
            continue;
        }

        if (isFrameUsed(pageTable, frameNumber)){
            printf("This Frame is already assigned to another page.\n");
            continue;
        }

        return frameNumber;
    }
}

int getValidPageNumber(int pageTable[])
{
    int pageNumber;

    while(1)
    {
        printf("Enter page number: ");

        if(scanf("%d", &pageNumber) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }

        if(pageNumber < 0 || pageNumber >= MAX_PAGES)
        {
            printf("Invalid page number! Enter between 0 and %d.\n",
                   MAX_PAGES - 1);
            continue;
        }

        if(pageTable[pageNumber] != -1)
        {
            printf("This page is already mapped.\n");
            continue;
        }

        return pageNumber;
    }
}

int getLoadedPageCount (int frameCount){

    int loadedPageCount;

    while(1){
        printf("How many pages are loaded currently : ");

        if(scanf("%d", &loadedPageCount) != 1){
            printf("Invalid Input. Please input a valid number.\n");
            while(getchar() != '\n');
            continue;
        }

        if(loadedPageCount < 0 || loadedPageCount > MAX_PAGES){
            printf("Invalid Page Count. Please enter a value between 0 and %d \n", MAX_PAGES);
            continue;
        }

        if (loadedPageCount > frameCount){
            printf("Insufficient Memory. Page count cannot exceed frame count(%d) \n", frameCount);
            continue;
        }

        return loadedPageCount;
    }


}

void createPageTable(int pageTable[MAX_PAGES], int frameCount){

    // Initializing all the values in the array with -1
    for (int i = 0; i < MAX_PAGES; i++){
        pageTable[i] = -1;
    }

     int loadedPageCount = getLoadedPageCount(frameCount);

    for (int i = 0; i < loadedPageCount; i++){
       int pageNumber = getValidPageNumber (pageTable);
       int frameNumber = getValidFrameNumber (frameCount, pageTable);
       pageTable[pageNumber] = frameNumber;

       printf("Mapped page %d --> Frame %d \n", pageNumber , frameNumber);

    }
}

int getFrameCount(){
    int frameCount;

   do {
        printf("Enter the number of Frames : ");

        if(scanf("%d",&frameCount) != 1){

            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            frameCount = 0;
            continue;
        }

        if (frameCount < MIN_FRAMES || frameCount > MAX_FRAMES){
            printf("Invalid number of frames! \n");
            printf("Please enter a value between %d and %d for Frame count!! \n", MIN_FRAMES , MAX_FRAMES);
        }
    } while (frameCount < MIN_FRAMES || frameCount > MAX_FRAMES);

    return frameCount;
}

void displayTitle (){


    printf("+==========================================================================+\n");
    printf("|                                                                          |\n");
    printf("|   ____    _    ____ _____    _____ _    ____  _     _____               |\n");
    printf("|  |  _ \\  / \\  / ___| ____|  |_   _/ \\  | __ )| |   | ____|              |\n");
    printf("|  | |_) |/ _ \\| |  _|  _|      | |/ _ \\ |  _ \\| |   |  _|                |\n");
    printf("|  |  __// ___ \\ |_| | |___     | / ___ \\| |_) | |___| |___               |\n");
    printf("|  |_|  /_/   \\_\\____|_____|    |_/_/   \\_\\____/|_____|_____|              |\n");
    printf("|                                                                          |\n");
    printf("|                T R A N S L A T O R   *   S I M U L A T O R               |\n");
    printf("|                                                                          |\n");
    printf("|           Virtual Address -> Physical Address | Paging Engine            |\n");
    printf("|                                                                          |\n");
    printf("+==========================================================================+\n");


    printf("\n");
}

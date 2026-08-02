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

// constraints mentioned in the project specification
#define MAX_PAGES 16
#define PAGE_SIZE 1024
#define MAX_ADDRESSES 12
#define MIN_FRAMES 8
#define MAX_FRAMES 16

// Function Prototypes
void displayTitle();

int main (){

    displayTitle();

    return 0;
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

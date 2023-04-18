#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>


const char* LanguageCodes[12] = {
    "Japanese",
    "English",
    "French",
    "German",
    "Italian",
    "Spanish",
    "Simplified Chinese",
    "Korean",
    "Dutch",
    "Portuguese",
    "Russian",
    "Traditional Chinese"
};


void getSysLanguage()
{
    //Init service
    cfguInit();

    // setup necessary variables
    u8 language = 0;
    

    CFGU_GetSystemLanguage(&language);
    printf("Selected Language: %s\n", LanguageCodes[(int)language]);

    cfguExit();
}


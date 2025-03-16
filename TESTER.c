#include "MP_V2.c"

int main()
{
    entryType entries[MAX_ENTRIES];
    int entryCount = 0;

    strcpy(entries[0].pairs[0].language, "Japanese");
    strcpy(entries[0].pairs[0].translation, "ai");
    strcpy(entries[0].pairs[1].language, "Filipino");
    strcpy(entries[0].pairs[1].translation, "mahal");
    entries[0].pairCount = 2;
    strcpy(entries[1].pairs[0].language, "Japanese");
    strcpy(entries[1].pairs[0].translation, "ai");
    strcpy(entries[1].pairs[1].language, "English");
    strcpy(entries[1].pairs[1].translation, "love");
    entries[1].pairCount = 2;
    strcpy(entries[2].pairs[0].language, "Spanish");
    strcpy(entries[2].pairs[0].translation, "amor");
    strcpy(entries[2].pairs[1].language, "English");
    strcpy(entries[2].pairs[1].translation, "love");
    entries[2].pairCount = 2;

    strcpy(entries[3].pairs[0].language, "Spanish");
    strcpy(entries[3].pairs[0].translation, "amor");
    strcpy(entries[3].pairs[1].language, "Japanese");
    strcpy(entries[3].pairs[1].translation, "ai");
    entries[3].pairCount = 2;
    
    entryCount = 4;
    addTranslation(entries, entryCount);

    printf("\n\n");
    for (int i = 0; i < entryCount; i++)
    {
        printEntry(entries[i], stdout);
        printf("\n");
    }

}
#include "MP_V2.c"

typedef struct 
{
    int entryIndex;
    int pairIndex;
} LTPairLocation;

void printIntArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d.", arr[i]);
    }
}
int 
searchForLanguageInEntry(entryType entry, char langKey[])
{
    int i;
    int indexOfKey = -1;

    for (i = 0; i < entry.pairCount && indexOfKey == -1; i++)
    {
        if (strcmp(entry.pairs[i].language, langKey) == 0)
        {
            indexOfKey = i;
        }
    }
    return indexOfKey;
}

void 
sortInterEntry2(entryType entries[], int entryCount)
{
    int i;
    LTPairLocation engIndexesLoc[MAX_ENTRIES];
    entryType tempEntries[MAX_ENTRIES];
    entryType tempEntry;
    int engIndexes[MAX_ENTRIES];
    int noEngIndexes[MAX_ENTRIES];
    LTPairLocation tempLoc;
    LTPairType tempPair;
    int engNum = 0;
    int noEngNum = 0;
    int j;
    int temp;
    for (i = 0; i < entryCount; i++)
    {
        if (searchForLanguageInEntry(entries[i], "English") != -1)
        {
            engIndexes[engNum] = i;
            engIndexesLoc[engNum].entryIndex = i;
            engIndexesLoc[engNum].pairIndex = searchForLanguageInEntry(entries[i], "English");
            engNum++;
        }
        else
        {
            noEngIndexes[noEngNum] = i;
            noEngNum++;
        }
    }
   
    for (i = 0; i < engNum - 1; i++)
    {
        for (j = i + 1; j < engNum; j++)
        {
            if (strcmp(entries[engIndexesLoc[i].entryIndex].pairs[engIndexesLoc[i].pairIndex].translation, 
                       entries[engIndexesLoc[j].entryIndex].pairs[engIndexesLoc[j].pairIndex].translation) == -1)
            {
                tempEntry = entries[]
                engIndexes[i] = engIndexes[j];
                engIndexes[j] = temp;
            }
            printIntArray(engIndexes, engNum);
            printf("\n");
        }
    }

    for (i = 0; i < engNum; i++)
    {
        tempEntries[i] = entries[engIndexes[i]];
    }
    for (i = engNum, j = 0; i < entryCount; i++, j++)
    {
        tempEntries[i] = entries[noEngIndexes[j]];
    }
   

}

int main()
{
    entryType entries[MAX_ENTRIES];
    int entryCount = 0;

    importData(entries, &entryCount);
    sortInterEntry2(entries, entryCount);
    
}
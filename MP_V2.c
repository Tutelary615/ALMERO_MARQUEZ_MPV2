#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "MP_HEADER.h"

void 
initString(char str[])
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        str[i] = '\0';
    }
}

bool 
getInteger(int* num)
{
    char firstCharacterEntered;
    char lastCharacterAfterNum;
    bool isInputValid = false;

    firstCharacterEntered = getc(stdin);

    if (firstCharacterEntered != '\n')
    {
        ungetc(firstCharacterEntered, stdin);
        scanf("%d", num);
        lastCharacterAfterNum = getc(stdin);
    }

    if (lastCharacterAfterNum == '\n')
    {
        isInputValid = true;
    }
    fflush(stdin);
    return isInputValid;
}

bool
isMenuInputValid(bool isInputValid, int lowerBound, int upperBound, int input)
{
	bool isValid = true;

	if (!isInputValid || input < lowerBound || input > upperBound)
	{
		printf(REDFORMATSTRING, "Entered number is invalid, try again\n");
		isValid = false;
	}
		
	return isValid;
}

int 
getAndValidateMenuInput(int lowerBound, int upperBound)
{
    int choice;
    bool isChoiceValid;
    do
	{
        printf("Enter choice: ");
		isChoiceValid = getInteger(&choice);
				
	} while (!isMenuInputValid(isChoiceValid, 1, upperBound, choice));
	return choice;
}

void 
printMenu(string30 choices[], int numberOfChoices)
{
    int i;
    for (i = 0; i < numberOfChoices; i++)
    {
        printf("%d - %s\n", (i + 1), choices[i]);
    }
}

int
mainMenu()
{
	int choice;
	bool isChoiceValid;
	string30 options[3] = {"Manage Data", "Translate Menu", "Exit"};
	
	printMenu(options, 3);
	
	do
	{
		printf("Select an option from the menu above: ");
		isChoiceValid = getInteger(&choice);
				
	} while (!isMenuInputValid(isChoiceValid, 1, 3, choice));
	return choice;
}

int 
manageDataMenu(int entryCount)
{
    string30 options[10] = {"Add Entry", "Import Data", "Add Translations", "Delete Entry", "Delete Translation",
                            "Display All Entries", "Search by Word", "Search By Translation", "Export Data", "Exit"};
    int choice;
    int upperBound;
    if (entryCount > 0)
    {
        printMenu(options, 10);
        upperBound = 10;
    }
    else
    {
        printMenu(options, 2);
        upperBound = 2;
    }
    printf("Select and option from the menu above\n");
    choice = getAndValidateMenuInput(1, upperBound);
    return choice;
}

void
getLTPair(string20 tempLanguage, string20 tempTranslation, char* characterAfterLanguage, char* characterAfterTranslation)
{
	
	printf("Enter language: ");
	fgets(tempLanguage, 21, stdin);
    if (strlen(tempLanguage) == 20)
    {
        *characterAfterLanguage = getc(stdin);
    }
    fflush(stdin);
	
	printf("Enter translation: ");
	fgets(tempTranslation, 21, stdin);
    if (strlen(tempTranslation) == 20)
    {
        *characterAfterTranslation = getc(stdin);
    }
    fflush(stdin);	
}

bool 
isLTPairValid(string20 tempLanguage, string20 tempTranslation, char characterAfterLanguage, char characterAfterTranslation)
{
    bool isValid = true;
    if (characterAfterLanguage != '\n' || characterAfterTranslation != '\n' || strlen(tempLanguage) == 0 || strlen(tempTranslation) == 0)
    {
        printf(REDFORMATSTRING, "Input(s) invalid. Try again.\n");
        isValid = false;
    }
    return isValid;
}

bool
isOperationConfirmed()
{
	int input;
	bool isInputValid;
	printf("1 - Yes\n");
	printf("2 - No\n");
	
	do
	{
        printf("Enter the number corresponding to your choice: ");
		isInputValid = getInteger(&input);
	} while (!isMenuInputValid(isInputValid, 1, 2, input));
	
	return (input == 1);
}

void 
formatLanguage(string20 language)
{
    int i;
    int lengthOfLanguage = strlen(language);
    if (lengthOfLanguage < 20)
    {
        language[lengthOfLanguage - 1] = '\0';
        lengthOfLanguage--;
    }
    
    language[0] = toupper(language[0]);
    for (i = 1; i < lengthOfLanguage; i++)
    {
        language[i] = tolower(language[i]);
    }
}

void 
formatTranslation(string20 translation)
{
    int i;
    int lengthOfTranslation = strlen(translation);
    if (lengthOfTranslation < 20)
    {
        translation[lengthOfTranslation - 1] = '\0';
        lengthOfTranslation--;   
    }
    for (i = 0; i < lengthOfTranslation; i++)
    {
        translation[i] = tolower(translation[i]);
    }

}

void 
sortEntry(entryType* entry)
{
    int i; 
    int j;
    LTPairType temp;

    for (i = 0; i < entry->pairCount - 1; i++)
    {
        for (j = 0; j < entry->pairCount - 1 - i; j++)
        {
            if (strcmp(entry->pairs[j].language,  entry->pairs[j + 1].language) == 1)
            {
                temp = entry->pairs[j];
                entry->pairs[j] = entry->pairs[j + 1];
                entry->pairs[j + 1] = temp;
            }
        }
    }
}

int 
searchLTPair(entryType entry, string20 languageKey, string20 translationKey)
{
    int i;
    int indexOfKey = -1;
    int startIndex = 0;
    int endIndex = entry.pairCount - 1;

    while (strcmp(languageKey, entry.pairs[startIndex].language) == 1 && startIndex < entry.pairCount) 
    {
        startIndex++;
    }

    while (strcmp(languageKey, entry.pairs[endIndex].language) == -1 && endIndex > startIndex)
    {
        endIndex--;
    }
    
    for (i = startIndex; i <= endIndex && indexOfKey == -1; i++)
    {
        if((strcmp(languageKey, entry.pairs[i].language) == 0) && 
		   (strcmp(translationKey, entry.pairs[i].translation) == 0))
        {
            indexOfKey = i;
        }
    }

    return indexOfKey;
}

int
searchAllEntriesForLTPair(entryType entries[], int entryCount, string20 langKey, string20 transKey, int entryIndexesWithKey[])
{
    int entriesWithKeyCount = 0;
    int i;
    for (i = 0; i < entryCount; i++)
    {
        if (searchLTPair(entries[i], langKey, transKey) != -1)
        {
            entryIndexesWithKey[entriesWithKeyCount] = i;
            entriesWithKeyCount++;
        }
    }
    return entriesWithKeyCount;
}

void 
printEntry(entryType entry, FILE* outputFile)
{
    int i;
    for (i = 0; i < entry.pairCount; i++)
    {
        fprintf(outputFile, "%s: %s\n", entry.pairs[i].language, entry.pairs[i].translation);
    }
}

void 
printEntryWithHighlight(entryType entry, string20 langKey, string20 transKey)
{
    int i;
    for (i = 0; i < entry.pairCount; i++)
    {
        if (strcmp(entry.pairs[i].language, langKey) == 0 && strcmp(entry.pairs[i].translation, transKey) == 0)
        {
            printf( "\033[0;36m%s: %s <\033[0m\n", entry.pairs[i].language, entry.pairs[i].translation);
        }
        else 
        {
            printf("%s: %s\n", entry.pairs[i].language, entry.pairs[i].translation);
        }
    }
}

void 
printAllEntriesAsMenu(entryType entries[], int entryCount)
{
    int i;
    for (i = 0; i < entryCount; i++)
    {
        printEntry(entries[i], stdout);
        printf("Pair count = %d\n", entries[i].pairCount);
        printf("\033[0;33m - %d\033[0m", i + 1);
    }
}

void
printEntryAsMenu(entryType entry)
{
    int i;

    for (i = 0; i < entry.pairCount; i++)
    {
        printf("%d - %s: %s\n", (i + 1), entry.pairs[i].language, entry.pairs[i].translation);
    }
}

bool
initEntry(entryType entries[], int* entryCount)
{
	string20 tempLang;
	string20 tempTrans;
    bool isNewEntryInitialized = false;
	char afterLang;
	char afterTrans;
	int matchCount = 0;
	int i;
	
	do
	{
		afterLang = '\n';
		afterTrans = '\n';
		initString(tempLang);
		initString(tempTrans);
		getLTPair(tempLang, tempTrans, &afterLang, &afterTrans);
        formatLanguage(tempLang);
        formatTranslation(tempTrans);
	} while (!isLTPairValid(tempLang, tempTrans, afterLang, afterTrans));
	
	
	for (i = 0; i < *entryCount; i++)
	{
		if (searchLTPair(entries[i], tempLang, tempTrans) != -1)
		{
			printEntryWithHighlight(entries[i], tempLang, tempTrans);
			printf("\n");
			matchCount++;
		}			
	}
	
	if (matchCount > 0)
	{
		printf("%d entry/entries with matching translation found.\n", matchCount);	
	}
	
	printf("Would you like to add the entered translation to a new entry?\n");
	if (isOperationConfirmed())
	{
        entries[*entryCount].pairCount = 0;
		strcpy(entries[*entryCount].pairs[entries[*entryCount].pairCount].language, tempLang);
		strcpy(entries[*entryCount].pairs[entries[*entryCount].pairCount].translation, tempTrans);
		entries[*entryCount].pairCount = 1;
		(*entryCount)++;
        printf("\n");
        printf(GREENFORMATSTRING, "New entry successfully created\n");
        isNewEntryInitialized = true;
	}	
	else
	{
        printf("\n");
		printf(YELLOWFORMATSTRING, "Entry addition cancelled. Press any key to return to menu\n");
		getch();
		fflush(stdin);
	}
    return isNewEntryInitialized;
}

void
addLTPair(entryType* entry)
{
    string20 langToAdd;
    string20 transToAdd;
    char charAfterLang;
    char charAfterTrans;

	do 
    {
        initString(langToAdd);
        initString(transToAdd);
        charAfterLang = '\n';
        charAfterTrans = '\n';
        getLTPair(langToAdd, transToAdd, &charAfterLang, &charAfterTrans);
        formatLanguage(langToAdd);
        formatTranslation(transToAdd);

    } while (!isLTPairValid(langToAdd, transToAdd, charAfterLang, charAfterTrans));

    if (searchLTPair(*entry, langToAdd, transToAdd) == -1)
    {
        printf("Would you like to add this translation?\n");
    
        if (isOperationConfirmed())
        {
            strcpy(entry->pairs[entry->pairCount].language, langToAdd);
            strcpy(entry->pairs[entry->pairCount].translation, transToAdd);
            entry->pairCount++;
            sortEntry(entry);
            printf(GREENFORMATSTRING, "Translation successfully added\n");
        }
        else
        {
            printf(YELLOWFORMATSTRING, "Addition cancelled\n");
        } 
    }
    else
    {
        printf(YELLOWFORMATSTRING, "The translation entered already exists in this entry\n");

    }
}

void 
addEntry(entryType entries[], int* entryCount)
{
    bool isNewEntryInitialized;
    bool willAddTranslation;

    isNewEntryInitialized = initEntry(entries, entryCount);

    if (isNewEntryInitialized)
    {
        do
        {
            printf("Would you like to add another translation?\n");
            willAddTranslation = isOperationConfirmed();

            if (willAddTranslation)
            {
                addLTPair(&entries[*entryCount - 1]);
                sortEntry(&entries[*entryCount - 1]);
            }
        
        } while (willAddTranslation);
    }
}

void 
printEntriesAsMenuWithHighlight(entryType entries[], string20 langKey, string20 transKey, int indexesToPrint[], int entriesToPrintCount)
{
    int i;

    for (i = 0; i < entriesToPrintCount; i++)
    {
        printEntryWithHighlight(entries[indexesToPrint[i]], langKey, transKey);
        printf("\033[0;33m - %d\033[0m", i + 1);
        printf("\n");
    }
}

void 
addTranslation(entryType entries[], int entryCount)
{
    string20 langKey;
    string20 transKey;
    char charAfterLang;
    char charAfterTrans;
    int entriesWithKeyCount = 0;
    int indexesOfEntriesWithKey[MAX_ENTRIES];
    int indexOfEntryToEdit;
    int i;
    bool willAddAnotherTranslation;

    printf("Enter the word and language you would like to translate\n");
    do
	{
		charAfterLang = '\n';
		charAfterTrans = '\n';
		initString(langKey);
		initString(transKey);
        getLTPair(langKey, transKey, &charAfterLang, &charAfterTrans);
        formatLanguage(langKey);
		formatTranslation(transKey);
	} while (!isLTPairValid(langKey, transKey, charAfterLang, charAfterTrans));

    
    entriesWithKeyCount = searchAllEntriesForLTPair(entries, entryCount, langKey, transKey, indexesOfEntriesWithKey);
    indexOfEntryToEdit = indexesOfEntriesWithKey[0];
    
    if (entriesWithKeyCount > 1)
    {
        printEntriesAsMenuWithHighlight(entries, langKey, transKey, indexesOfEntriesWithKey, entriesWithKeyCount);
        printf("Choose an entry where you would like to add a translation?\n");
        printf("Enter the number corresponding to the entry (1 - %d)\n", entriesWithKeyCount);
        indexOfEntryToEdit =  indexesOfEntriesWithKey[getAndValidateMenuInput(1, entriesWithKeyCount) - 1];
        system("cls");
    }

    else if (entriesWithKeyCount == 0)
    {
        printf(REDFORMATSTRING, "The word and corresponding language are not found in any entry\n");
        printf("You must first initialize a new entry\n");
        printf("Press any key to continue\n");
        getch();
    }

    if (entriesWithKeyCount > 0 && entries[indexOfEntryToEdit].pairCount < MAX_PAIRS_PER_ENTRY)
    {   
        do
        {   
            printEntry(entries[indexOfEntryToEdit], stdout);
            printf("\n");
            printf("Enter language and translation to be added\n");
            addLTPair(&entries[indexOfEntryToEdit]);
            sortEntry(&entries[indexOfEntryToEdit]);

            if (entries[indexOfEntryToEdit].pairCount < MAX_PAIRS_PER_ENTRY)
            {
                printf("Would you like to add another translation\n");
                willAddAnotherTranslation = isOperationConfirmed();
            }
        } while (willAddAnotherTranslation && entries[indexOfEntryToEdit].pairCount < MAX_PAIRS_PER_ENTRY);
        
        
    }
    
    if (entriesWithKeyCount > 0 && entries[indexOfEntryToEdit].pairCount == MAX_PAIRS_PER_ENTRY)
    {
        printf(YELLOWFORMATSTRING, "The maximum number of translations has been reached\n");
        printf("Press any key to continue\n");
        getch();
    }
    
	   
}

void 
removeLTPair(entryType* entry, int indexOfPairToRemove)
{
    int i;

    for (i = indexOfPairToRemove; i < (entry->pairCount) - 1; i++)
    {
        entry->pairs[i] = entry->pairs[i + 1];
    }
    initString(entry->pairs[entry->pairCount - 1].language);
    initString(entry->pairs[entry->pairCount - 1].translation);
    (entry->pairCount)--;
}

void 
deleteTranslation(entryType entries[], int entryCount)
{
    int indexOfEntryToEdit;
    int indexOfPairToDelete;
    bool willDeleteAnother;
    bool isThereValidInteger;
    printf("Select an entry to delete from.\n");
    printf("\n");

    printAllEntriesAsMenu(entries, entryCount); 
    
    printf("\n");
    printf("Enter the number corresponding to your choice: ");
    getInteger(&indexOfEntryToEdit);
    indexOfEntryToEdit -= 1;

    if (indexOfEntryToEdit >= entryCount)
    {
        printf(REDFORMATSTRING, "The choice entered is invalid.\n");
        printf("Press any key to return to return to \" manage data\" menu\n");
        getch();
        fflush(stdin);
    }

    else
    {
        do
        {
            system("cls");
            printEntryAsMenu(entries[indexOfEntryToEdit]);
            printf("\n");
            printf("Select a translation to delete: \n");
            isThereValidInteger = getInteger(&indexOfPairToDelete);

            if (isMenuInputValid(isThereValidInteger, 1, entries[indexOfEntryToEdit].pairCount, indexOfPairToDelete))
            {
                indexOfPairToDelete -= 1;
                printf("Would you like to delete:\n");
                printf("\t%s: %s", entries[indexOfEntryToEdit].pairs[indexOfPairToDelete].language, 
                                   entries[indexOfEntryToEdit].pairs[indexOfPairToDelete].translation);
                printf("\n");
                if (isOperationConfirmed())
                {
                    removeLTPair(&entries[indexOfEntryToEdit], indexOfPairToDelete);
                    printf(GREENFORMATSTRING, "Translation successfully deleted\n");
                }
                else
                {
                    printf(YELLOWFORMATSTRING, "Deletion cancelled\n");
                }
            }
            else
            {
                printf(REDFORMATSTRING, "The choice entred is invalid\n");
            }

            printf("Would you like to delete another pair\n");
            willDeleteAnother = isOperationConfirmed();

            
        } while (willDeleteAnother);
        
    }
}


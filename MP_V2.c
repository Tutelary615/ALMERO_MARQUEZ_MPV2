#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
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
		isInputValid = getInteger(&input);
	} while (!isMenuInputValid(isInputValid, 1, 2, input));
	
	return input == 1;
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
addLTPair(entryType* entry)
{
	
}

void
addEntry(entryType entries[], int* entryCount)
{
	string20 tempLang;
	string20 tempTrans;
	char afterLang;
	char afterTrans;
	int i;
	
	do
	{
		afterLang = '\n';
		afterTrans = '\n';
		initString(tempLang);
		initString(tempTrans);
		
		getLTPair(tempLang, tempTrans, &afterLang, &afterTrans);
	} while (!isLTPairValid(tempLang, tempTrans, afterLang, afterTrans));
	
	
	
	if (entryCount > 0)
	{
		for (i = 0; i < *entryCount; i++)
		{
			if (searchLTPair(entries[i], tempLang, tempTrans) != -1)
			{
				printEntry(entries[i], stdout);
				printf("\n");
			}			
		}
		
		printf("Entries with matching translation found.\n");
		printf("Would you like to create a new entry? ");
		if (isOperationConfirmed())
		{
			strcpy(entries[*entryCount].pairs[entries[*entryCount].pairCount].language, tempLang);
			strcpy(entries[*entryCount].pairs[entries[*entryCount].pairCount].translation, tempTrans);
			(*entryCount)++;
		}
	}
	
	else
	{
		strcpy(entries[*entryCount].pairs[entries[*entryCount].pairCount].language, tempLang);
		strcpy(entries[*entryCount].pairs[entries[*entryCount].pairCount].translation, tempTrans);
		(*entryCount)++;
	}
}


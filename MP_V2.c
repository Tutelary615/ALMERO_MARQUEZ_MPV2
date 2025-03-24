#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "MP_HEADER.h"

void 
printStringASCII(char str[])
{
    for (int i = 0; i <= strlen(str); i++)
    {
        printf("%d.", str[i]);
    }
}

void 
initString(char str[])
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        str[i] = '\0';
    }
}

void
setEntryData(entryType* entry)
{
    int i;
    for (i = 0; i < entry->pairCount; i++)
    {
        initString(entry->pairs[i].language);
        initString(entry->pairs[i].translation);
    }
    entry->pairCount = 0;
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
isCharInputValid(char input, char validCharacters[])
{
    int i;
    bool isValid = false;
    for (i = 0; i < strlen(validCharacters) && !isValid; i++)
    {
        if (input == validCharacters[i])
        {
            isValid = true;
        }
    }
    return isValid;
}

char 
getAndValidateCharInput(char validCharacters[]) 
{
    char input;
    do 
    {
        input = getch();

    } while (!isCharInputValid(input, validCharacters));

    return input;
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

bool
isThereSpaceInString(string20 str)
{
    int i;
    bool isThereSpace = false;

    for (i = 0; i < strlen(str) && !isThereSpace; i++)
    {
        if (str[i] == ' ')
        {
            isThereSpace = true;
        }
    }
    return isThereSpace;
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
getWordOrLanguge(string20 str, char* characterAfterInput)
{
	fgets(str, 21, stdin);
    if (strlen(str) == 20)
    {
        *characterAfterInput = getc(stdin);
    }
    fflush(stdin);
}

bool
isLanguageValid(string20 language, char charAfterLang)
{
    bool isValid = true;
    if (charAfterLang != '\n')
    {
        printf(REDFORMATSTRING, "Language entered exceeds 20 characters.\n");
        isValid = false;
    }
    else if (isThereSpaceInString(language))
    {
        printf(REDFORMATSTRING, "Language must not contain spaces.\n");
        isValid = false;
    }
    else if (strlen(language) == 0)
    {
        printf(REDFORMATSTRING, "No language entered.\n");
        isValid = false;
    }
    return isValid;
}

bool 
isWordValid(string20 word, char charAfterWord)
{
    bool isValid = true;
    if (charAfterWord != '\n')
    {
        printf(REDFORMATSTRING, "Word entered exceeds 20 characters.\n");
        isValid = false;
    }
    else if (isThereSpaceInString(word))
    {
        printf(REDFORMATSTRING, "Word must not contain spaces.\n");
        isValid = false;
    }
    else if (strlen(word) == 0)
    {
        printf(REDFORMATSTRING, "No word entered.\n");
        isValid = false;
    }
    return isValid;
}

bool 
isLTPairValid(string20 language, string20 translation, char charAfterLang, char charAfterTrans)
{
    bool isValid = true;

    if (!isWordValid(translation, charAfterTrans))
    {
        isValid = false;
    }
    if (!isLanguageValid(language, charAfterLang))
    {
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
    if (language[lengthOfLanguage - 1] == '\n')
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
    if (translation[lengthOfTranslation - 1] == '\n')
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
sortIntraEntry(entryType* entry)
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

void
sortInterEntry(entryType entries[], int entryCount)
{
	entryType engEntries[MAX_ENTRIES];
	int num_engEntries = 0;
	int engIndices[MAX_ENTRIES];
	entryType noEngEntries[MAX_ENTRIES];
	int num_noEngEntries = 0;
	int found = 0;
	entryType tempE;
	int tempI;
	int min;
	int i, j;
	
	for (i = 0; i < entryCount; i++)
	{
		found = 0;
		for (j = 0; j < entries[i].pairCount && !found; j++)
		{
			if (!strcmp(entries[i].pairs[j].language, "English"))
			{
				engEntries[num_engEntries] = entries[i];
				engIndices[num_engEntries] = j;
				num_engEntries++;
				found = 1;
			}
		}
		
		if (!found)
		{
			noEngEntries[num_noEngEntries] = entries[i];
			num_noEngEntries++;
		}
	}
	
	for (i = 0; i < num_engEntries - 1; i++)
	{
		min = i;
		for (j = i+1; j < num_engEntries; j++)
		{
			if (strcmp(engEntries[min].pairs[engIndices[min]].translation,
					   engEntries[j].pairs[engIndices[j]].translation) > 0)
			{
				min = j;
			}
			
			if (min != i)
			{
				tempE = engEntries[i];
				engEntries[i] = engEntries[min];
				engEntries[min] = tempE;
				
				tempI = engIndices[i];
				engIndices[i] = engIndices[min];
				engIndices[min] = tempI;
			}
		}
	}
	
	for (i = 0; i < num_engEntries; i++)
	{
		entries[i] = engEntries[i];
	}
	
	j = 0;
	for (i = num_engEntries; i < entryCount; i++)
	{
		entries[i] = noEngEntries[j];
		j++;
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
printEntryWithHighlightPair(entryType entry, string20 langKey, string20 transKey)
{
    int i;
    for (i = 0; i < entry.pairCount; i++)
    {
        if (strcmp(entry.pairs[i].language, langKey) == 0 && strcmp(entry.pairs[i].translation, transKey) == 0)
        {
            printf(HIGHLIGHTED_PAIR_FORMAT_STRING, entry.pairs[i].language, entry.pairs[i].translation);
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
        printf("\033[0;33m - %d\033[0m\n", i + 1);
        printf("\n");
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
	string20 language;
	string20 word;
    bool isNewEntryInitialized = false;
	char charAfterLang;
	char charAfterWord;
	int matchCount = 0;
	int i;
	
	do
	{
        charAfterWord = '\n';
		charAfterLang = '\n';
        initString(word);
		initString(language);
		
        printf("Enter word: ");
        getWordOrLanguge(word, &charAfterWord);
        printf("Enter language: ");
        getWordOrLanguge(language, &charAfterLang);
        
        formatLanguage(language);
        formatTranslation(word);
	} while (!isLTPairValid(language, word, charAfterLang, charAfterWord));
	
	
	for (i = 0; i < *entryCount; i++)
	{
		if (searchLTPair(entries[i], language, word) != -1)
		{
			printEntryWithHighlightPair(entries[i], language, word);
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
		strcpy(entries[*entryCount].pairs[entries[*entryCount].pairCount].language, language);
		strcpy(entries[*entryCount].pairs[entries[*entryCount].pairCount].translation, word);
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
        printf("Enter translation: ");
        getWordOrLanguge(transToAdd, &charAfterTrans);
        printf("Enter language: ");
        getWordOrLanguge(langToAdd, &charAfterLang);
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
            sortIntraEntry(entry);
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

    entries[*entryCount].pairCount = 0;
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
                sortIntraEntry(&entries[*entryCount - 1]);
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
        printEntryWithHighlightPair(entries[indexesToPrint[i]], langKey, transKey);
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
    bool willAddAnotherTranslation;

    do
	{
		charAfterLang = '\n';
		charAfterTrans = '\n';
		initString(langKey);
		initString(transKey);
        
        printf("Enter word to translate: ");
        getWordOrLanguge(transKey, &charAfterTrans);
        printf("Enter source language: ");
        getWordOrLanguge(langKey, &charAfterTrans);
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
            sortIntraEntry(&entries[indexOfEntryToEdit]);

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

    if (indexOfEntryToEdit >= entryCount || indexOfEntryToEdit < 0)
    {
        printf(REDFORMATSTRING, "The choice entered is invalid.\n");
        printf("Press any key to return to return to \"manage data\" menu\n");
        getch();
        fflush(stdin);
    }

    else
    {
        do
        {
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
                printf(REDFORMATSTRING, "The choice entered is invalid\n");
            }

            printf("Would you like to delete another pair\n");
            willDeleteAnother = isOperationConfirmed();

            
        } while (willDeleteAnother);
        
    }
}

void
deleteEntry(entryType entries[], int *entryCount)
{
    int delIndex;
	int i;
	
	printf("Select an entry to delete.\n");
	printf("\n");
	
	printAllEntriesAsMenu(entries, *entryCount);
	printf("\n");
    printf("Enter the number corresponding to your choice: ");
    getInteger(&delIndex);
    delIndex--;
    
    if (delIndex >= *entryCount || delIndex < 0)
    {
        printf(REDFORMATSTRING, "The choice entered is invalid.\n");
        printf("Press any key to return to \"manage data\" menu\n");
        getch();
        fflush(stdin);
    }
    
    else
    {
    	printf("Would you like to delete:\n");
    	printEntry(entries[delIndex], stdout);
    	
    	if (isOperationConfirmed())
    	{
    		for (i = delIndex; i < *entryCount - 1; i++)
	    	{
	    		entries[i] = entries[i + 1];
			}
            setEntryData(&entries[*entryCount - 1]);
            (*entryCount)--;
			
    		printf(GREENFORMATSTRING, "Entry successfully deleted\n");
		}
		
		else
		{
			printf(YELLOWFORMATSTRING, "Deletion cancelled\n");
		}
        printf("Press any key to return to return to \"manage data\" menu\n");
	    getch();
	    fflush(stdin);
	}
}

void 
printEntryWithHighlightWord(entryType entry, string20 keyWord)
{
    int i;

    for (i = 0; i < entry.pairCount; i++)
    {
        if (strcmp(entry.pairs[i].translation, keyWord) == 0)
        {
            printf(HIGHLIGHTED_PAIR_FORMAT_STRING, entry.pairs[i].language, entry.pairs[i].translation);
        }
        else
        {
            printf("%s: %s\n", entry.pairs[i].language, entry.pairs[i].translation);
        }
    }
}

void 
displayAllEntries(entryType entries[], int entryCount)
{
    int indexOfEntryBeingDisplayed = 0;
    char choice;
   
        do
        {
           printEntry(entries[indexOfEntryBeingDisplayed], stdout);
            printf("(%d/%d)\n", (indexOfEntryBeingDisplayed + 1), entryCount);
            printf("\n");

            if (entryCount == 1)
            {
                printf("Press 'e' to exit\n");
                choice = getAndValidateCharInput("e");   
            }

            else if (indexOfEntryBeingDisplayed == 0)
            {
                printf("Press 'n' to view next entry or 'e' to exit\n");
                choice = getAndValidateCharInput("ne");
            }
            else if (indexOfEntryBeingDisplayed == entryCount - 1)
            {
                printf("Press 'p' to view previous entry or 'e' to exit\n");
                choice = getAndValidateCharInput("pe");
            }
            else
            {
                printf("Press 'p' to view previous entry, 'n' to view next entry, or 'e' to exit\n");
                choice = getAndValidateCharInput("pne");
            }

            if (choice == 'p')
            {
                indexOfEntryBeingDisplayed--;
            }
            else if (choice == 'n')
            {
                indexOfEntryBeingDisplayed++;
            }

        } while (choice != 'e');

}

void 
displaySpecificEntries(entryType entries[], int indexesOfEntriesToDisplay[], int numberOfEntriesToDisplay, string20 langKey, string20 wordKey)
{
    int indexOfEntryBeingDisplayed = 0;
    char choice;
   
        do
        {
            if (langKey == NULL)
            {
                printEntryWithHighlightWord(entries[indexesOfEntriesToDisplay[indexOfEntryBeingDisplayed]], wordKey);
            }
            else
            {
                printEntryWithHighlightPair(entries[indexesOfEntriesToDisplay[indexOfEntryBeingDisplayed]], langKey, wordKey);
            }
            printf("(%d/%d)\n", (indexOfEntryBeingDisplayed + 1), numberOfEntriesToDisplay);
            printf("\n");

            if (numberOfEntriesToDisplay == 1)
            {
                printf("Press 'e' to exit\n");
                choice = getAndValidateCharInput("e");   
            }

            else if (indexOfEntryBeingDisplayed == 0)
            {
                printf("Press 'n' to view next entry or 'e' to exit\n");
                choice = getAndValidateCharInput("ne");
            }
            else if (indexOfEntryBeingDisplayed == numberOfEntriesToDisplay - 1)
            {
                printf("Press 'p' to view previous entry or 'e' to exit\n");
                choice = getAndValidateCharInput("pe");
            }
            else
            {
                printf("Press 'p' to view previous entry, 'n' to view next entry, or 'e' to exit\n");
                choice = getAndValidateCharInput("pne");
            }

            if (choice == 'p')
            {
                indexOfEntryBeingDisplayed--;
            }
            else if (choice == 'n')
            {
                indexOfEntryBeingDisplayed++;
            }

        } while (choice != 'e');

}

int 
searchEntryForKeyWord(entryType entry, string20 keyWord)
{
    int i;
    int indexOfKey = -1;

    for (i = 0; i < entry.pairCount && indexOfKey == -1; i++)
    {
        if (strcmp(entry.pairs[i].translation, keyWord) == 0)
        {
            indexOfKey = i;
        }
    }
    return indexOfKey;
}

void 
searchByWord(entryType entries[], int entryCount)
{
    string20 keyWord;
    int* entriesWithKeyWordIndexes = (int*)malloc(0);
    int entriesWithKeyWordCount = 0;
    int i;
    char charAfterKeyWord;
    do
    {
        charAfterKeyWord = '\n';
        printf("Enter word to search: ");
        getWordOrLanguge(keyWord, &charAfterKeyWord);
        formatTranslation(keyWord);
    } while (!isWordValid(keyWord, charAfterKeyWord));
    
    for (i = 0; i < entryCount; i++)
    {
        if (searchEntryForKeyWord(entries[i], keyWord) != -1)
        {
            entriesWithKeyWordCount++;
            entriesWithKeyWordIndexes = (int*)realloc(entriesWithKeyWordIndexes, entriesWithKeyWordCount * sizeof(int));
            entriesWithKeyWordIndexes[entriesWithKeyWordCount - 1] = i;
        }
    }

    if (entriesWithKeyWordCount > 0)
    {
        displaySpecificEntries(entries, entriesWithKeyWordIndexes, 
                               entriesWithKeyWordCount, NULL, keyWord);
    }
    else
    {
        printf(YELLOWFORMATSTRING, "No matches found\n");
        printf("Press any key to return to \"Manage Data\" menu.\n");
        getch();
        fflush(stdin);
    }
    
}

void
searchByTranslation(entryType entries[], int entryCount)
{
    string20 langKey;
    string20 wordKey;
    char charAfterLangKey;
    char charAfterWordKey;
    int* entriesWithLTPairKeyIndexes = (int*)malloc(0);
    int entriesWithLTPairKeyCount = 0;
    int i;

    do 
    {
        initString(langKey);
        initString(wordKey);
        charAfterLangKey = '\n';
        charAfterWordKey = '\n';

        printf("Enter language: ");
        getWordOrLanguge(langKey, &charAfterLangKey);
        printf("Enter word: ");
        getWordOrLanguge(wordKey, &charAfterWordKey);
        formatLanguage(langKey);
        formatTranslation(wordKey);
    } while (!isLTPairValid(langKey, wordKey, charAfterLangKey, charAfterWordKey));

    for (i = 0; i < entryCount; i++)
    {
        if (searchLTPair(entries[i], langKey, wordKey) != -1)
        {
            entriesWithLTPairKeyCount++;
            entriesWithLTPairKeyIndexes = realloc(entriesWithLTPairKeyIndexes, entriesWithLTPairKeyCount * sizeof(int));
            entriesWithLTPairKeyIndexes[entriesWithLTPairKeyCount - 1] = i;
        }
    }
    if (entriesWithLTPairKeyCount > 0)
    {
        displaySpecificEntries(entries, entriesWithLTPairKeyIndexes, 
                               entriesWithLTPairKeyCount, langKey, wordKey);
    }
    else
    {
        printf(YELLOWFORMATSTRING, "No matches found\n");
        printf("Press any key to return to \"Manage Data\" menu.\n");
        getch();
        fflush(stdin);
    }
    
}

bool
getEntry(FILE* importFile, entryType* tempEntry)
 {
     string50 readLine;
     char* readResult;
     tempEntry->pairCount = 0;
     int i = 0;
     bool wasEntryRead = false;
     
     do
     {
         initString(readLine);
         readResult = fgets(readLine, 51, importFile);
         if (strcmp(readLine, "\n") != 0 && readResult != NULL)
         {
             strcpy(tempEntry->pairs[i].language, strtok(readLine, ": "));
             strcpy(tempEntry->pairs[i].translation, strtok(NULL, ": "));
             formatLanguage(tempEntry->pairs[i].language);
             formatTranslation(tempEntry->pairs[i].translation);
             tempEntry->pairCount++;
             i++;
             wasEntryRead = true;
         }
     } while (strcmp(readLine, "\n") != 0 && readResult != NULL);
    
     return wasEntryRead;   
 }
 
void 
getFilename(string30 filename, char* characterAfterFilename)
{
    printf("Enter filename: ");
    fgets(filename, 31, stdin); 
    if (strlen(filename) == 30)
    {
        *characterAfterFilename = getc(stdin);
    }
    fflush(stdin);
}

void
formatFilename(string30 filename)
{   
    int lengthOfString = strlen(filename);
    
    if (lengthOfString < 30)
    {
        filename[lengthOfString - 1] = '\0';
    }
}

bool
isThereProhibitedCharInFilename(string30 filename)
{
    bool isThereProhibitedCharacter = false;
    char prohibitedCharacters[9] = {'<', '>', ':', '"', '/', '\\', '|', '?', '*'};
    int i;
    int j;

    for (i = 0; i < strlen(filename) && !isThereProhibitedCharacter; i++)
    {
        for (j = 0; j < 9 && !isThereProhibitedCharacter; j++)
        {
            if (filename[i] == prohibitedCharacters[j])
            {
                isThereProhibitedCharacter = true;
            }
        }
    }
    return isThereProhibitedCharacter;
}

bool
isExportFilenameValid(string30 filename, char characterAfterFilename)
{
    bool isValid = true;
    if (strlen(filename) == 0)
    {
        printf(REDFORMATSTRING, "No filename was entered\n");
        isValid = false;
    }
    else if (characterAfterFilename != '\n')
    {
        printf(REDFORMATSTRING, "File name entered contains more than 30 characters\n");
        isValid = false;
    }
    else if (isThereProhibitedCharInFilename(filename))
    {
        printf(REDFORMATSTRING, "Filename entered contains prohibited character(s)\n");
        isValid = false;
    }
    else if (strcmp(filename, ".txt") == 0) 
    {
        printf(REDFORMATSTRING, "There must be at least one character before the \".txt\" extension\n");
        isValid = false;
    }
    else if (strcmp((filename + strlen(filename) - 4), ".txt") != 0)
    {
        printf(REDFORMATSTRING, "Filename must end in \".txt\"\n");
        isValid = false;
    }
    
    return isValid;
}

bool
isImportFilenameValid(string30 filename, char characterAfterFilename, FILE* importFile)
{
    bool isValid = true;
    if (strlen(filename) == 0)
    {
        printf(REDFORMATSTRING, "No filename was entered. Try again\n");
        isValid = false;
    }
    else if (characterAfterFilename != '\n')
    {
        printf(REDFORMATSTRING, "File name entered contains more than 30 characters. Try again\n");
        isValid = false;
    }
    else if ((isThereProhibitedCharInFilename(filename)) || (strcmp(filename, ".txt") == 0))
    {
        printf(REDFORMATSTRING, "File name entered is not valid. Try again\n");
        isValid = false;
    }
    else if (strcmp((filename + strlen(filename) - 4), ".txt") != 0)
    {
        printf(REDFORMATSTRING, "\".txt\" extension was not included in input. Try again\n");
        isValid = false;
    }
    else if (importFile == NULL)
    {
        printf(REDFORMATSTRING, "File not found. Try again\n");
        isValid = false;   
    }
    
    return isValid;
}

void 
printAllEntriesToFile(entryType entries[], int entryCount, FILE* outputFile)
{
    int i;
    
    for (i = 0; i < entryCount; i++)
    {
        printEntry(entries[i], outputFile);
        fprintf(outputFile, "\n");
    }
}

void
importData(entryType entries[], int* entryCount)
 {
     FILE* importFile;
     string30 filename;
     entryType* temp;
     char characterAfterFilename;
     bool wasEntryRead;
     bool willImportEntry;
 
     printf("provide the file name of the text file (.txt) to import from\n");
     printf(" - include the \".txt\" file extension in input\n");
     printf(" - file name should not exceed 30 characters (including file extesion)\n");
     printf("\n");
    
     do
     {
         initString(filename);
         characterAfterFilename = '\n';
         getFilename(filename, &characterAfterFilename);
         formatFilename(filename);
         importFile = fopen(filename, "r");
     } while (!isImportFilenameValid(filename, characterAfterFilename, importFile));
     printf("\n");
     
     printf("Would you like to proceed with import\n");
    
     if (isOperationConfirmed())
     {
        do 
        {   
             temp = (entryType*)malloc(sizeof(entryType));
             willImportEntry = false;
             
             wasEntryRead = getEntry(importFile, temp);
             if (wasEntryRead)
             {
                printEntry(*temp, stdout);
                printf("\n");
                printf("Would you like to import this entry\n");
                willImportEntry =  isOperationConfirmed();
             }
             
             if(willImportEntry)
             {
                 entries[*entryCount] = *temp;
                 sortIntraEntry(&entries[*entryCount]);
                 (*entryCount)++;
             }
             free(temp);
         } while (!feof(importFile) && *entryCount < MAX_ENTRIES);
 
         if (*entryCount == MAX_ENTRIES)
         {
             printf(YELLOWFORMATSTRING, "The maximum of 150 entries has been reached\n");
         }
         sortInterEntry(entries, *entryCount);
         
     }
     else 
     {
         printf(YELLOWFORMATSTRING, "import cancelled\n");
     }
     fclose(importFile);
     printf("Press any key to return to manage data menu\n");
     getch();
     fflush(stdin);
    
     
 }

 void 
 exportData(entryType entries[], int entryCount)
{
    FILE* exportFile;
    string30 filename;
    char characterAfterFilename;

    printf("Provide filename of file where data will be exported to\n");
    printf(" - the file name must end in \".txt\"\n");
    printf(" - There must be at least 1 character before the \".txt\" extension\n");
    printf(" - the file name must not exceed 30 characters (including file extension)\n");
    printf(" - The following characters are not allowed to be used in the file name:\n");
    
    printf("\n");
    printf("   - < (less than)\n");
    printf("   - > (greater than)\n");
    printf("   - : (colon)\n");
    printf("   - \" (double quote)\n");
    printf("   - ' (single quote)\n");
    printf("   - \\ (forward slash)\n");
    printf("   - / (back slash)\n");
    printf("   - | (vertical bar)\n");
    printf("   - ? (question mark)\n");
    printf("   - * (asterisk)\n");
    

    printf("\n");
    do
    {
        characterAfterFilename = '\n';
        initString(filename);
        getFilename(filename, &characterAfterFilename);
        formatFilename(filename);
    } while (!isExportFilenameValid(filename, characterAfterFilename));

    printf("\n");
    printf("Would you like to proceed with export?\n");

    if (isOperationConfirmed())
    {
        exportFile = fopen(filename, "w");
        printAllEntriesToFile(entries, entryCount, exportFile);
        fclose(exportFile);
        printf(GREENFORMATSTRING, "Data successfully exported to ");
        printf(GREENFORMATSTRING, filename);
        printf("\n");
    }
    else
    {
        printf(YELLOWFORMATSTRING, "Export cancelled\n");
    }
    
}

void 
manageData(entryType entries[], int* entryCount)
{
    int choice;
    do
    {
        choice = manageDataMenu(*entryCount);

        switch(choice)
        {
            case 1: addEntry(entries, entryCount);
                    break;
            
            case 2: importData(entries, entryCount);
                    break;
            
            case 3: addTranslation(entries, *entryCount);
                    break;
            
            case 4: deleteEntry(entries, entryCount);
                    break;
            
            case 5: deleteTranslation(entries, *entryCount);
                    break;

            case 6: displayAllEntries(entries, *entryCount);
                    break;

            case 7: searchByWord(entries, *entryCount);
                    break;
            
            case 8: searchByTranslation(entries, *entryCount);
                    break;
            
            case 9: exportData(entries, *entryCount);
                    break;
        }
    } while (choice != 9);
}

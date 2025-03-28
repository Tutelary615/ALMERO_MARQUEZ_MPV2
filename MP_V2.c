#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "MP_HEADER.h"

// TO REMOVE 
void 
printStringASCII(char str[])
{
    for (int i = 0; i <= strlen(str); i++)
    {
        printf("%d.", str[i]);
    }
}

/* initString sets all the characters in a string to '\0'
   @param str - string to be initialized
*/
void 
initString(char str[])
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        str[i] = '\0';
    }
}

/* setEntryData sets the default data for an entry
   @param entry - address of the entry being set
*/
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

/* getInteger gets an integer input
   @param num - address where integer input is stored
   @return true if there is a valid integer input and false otherwise
*/
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

/* isCharInSet checks if a character is among a set of characters
   @param input - character which is being checked
   @param validCharacters - string consisting of valid characters
   @return true if the character bebing checked is among the set of characters
           and false otherwise
*/
bool 
isCharInSet(char charToCheck, char validCharacters[])
{
    int i;
    bool isIn = false;
    for (i = 0; i < strlen(validCharacters) && !isIn; i++)
    {
        if (charToCheck == validCharacters[i])
        {
            isIn = true;
        }
    }
    return isIn;
}

/* getAndValidateCharInput gets a character input and checks if the entered character is 
                           is in the set of valid characters 
   @param validCharacters - string consisting of valid characters
   @return the first valid character entered
*/
char 
getAndValidateCharInput(char validCharacters[]) 
{
    char input;
    do 
    {
        input = getch();
        fflush(stdin);
    } while (!isCharInSet(input, validCharacters));

    return input;
}

/* isMenuInputValid checks if the input for selecting from a menu (type int) is valid
   @param isInputInt - indicates whether a valid integer was entered
   @param lowerBound - the smallest valid integer
   @param upperBound - the largest valid integer
   @param input - the number entered
   @return true if the input is valid and false otherwise
*/
bool
isMenuInputValid(bool isInputInt, int lowerBound, int upperBound, int input)
{
	bool isValid = true;

	if (!isInputInt || input < lowerBound || input > upperBound)
	{
		printf(REDFORMATSTRING, "Entered number is invalid, try again\n");
		isValid = false;
	}
		
	return isValid;
}

/* getAndValidateMenuInput gets and validates an integer input
   @param lowerBound - the smallest valid integer
   @param uppperBound - the greatest valid integer
   @return the first valid integer entered
*/
int 
getAndValidateMenuInput(int lowerBound, int upperBound)
{
    int choice;
    bool isInputInt;
    do
	{
        printf("Enter choice: ");
		isInputInt = getInteger(&choice);
				
	} while (!isMenuInputValid(isInputInt, 1, upperBound, choice));
	return choice;
}

/* printMenu prints menu items
   @param choices - array of menu items
   @param choiceCount - number of menu items
*/
void 
printMenu(string30 choices[], int choiceCount)
{
    int i;
    for (i = 0; i < choiceCount; i++)
    {
        printf("%d - %s\n", (i + 1), choices[i]);
    }
}

/* isThereSpaceInString checks if a string has a space character
   @param str - string being checked
   @return true if the space character is found in the string and false otherwise
*/
bool
isThereSpaceInString(char str[])
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

/* mainMenu contains all functions related to the main menu of the program 
   @return number corresponding to option selected
*/
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

/* manageDataMenu contains all functions related to the "Manage Data" menu 
   @param entryCount - number of entries initialized
   @return number corresponding to option selected
*/
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

/* manageDataMenu contains all functions related to the "Manage Data" menu 
   @param entryCount - number of entries initialized
   @return number corresponding to option selected
*/
int 
translateMenu()
{
    string30 options[3] = {"Translate Text Input", "Translate Text File", "Exit"};
    int choice;
    int upperBound;
    
    printMenu(options, 3);
    upperBound = 3;
    
    printf("Select and option from the menu above\n");
    choice = getAndValidateMenuInput(1, upperBound);
    return choice;
}

/* getTransOrLang gets user input for word or language
  @param str - string where word or language entered will be stored
  @param charAfterInput - address where the first character read from input stream after
                          entered word or language (if any) will be stored
*/
void
getTransOrLang(string20 str, char* charAfterInput)
{
	fgets(str, 21, stdin);
    if (strlen(str) == 20)
    {
        *charAfterInput = getc(stdin);
    }
    fflush(stdin);
}

/* isLanguageValid checks if an entered language is valid and prints error messages 
   when invalid
   conditions for invalidity:
    - language entered exceeds 20 characters 
    - language entered contains spaces 
    - no language was entered
   @param language - string containing the language entered
   @param charAfterLang - first character read from input stream after
                          entered word (if any)
   @return true if the language entered is valid and false otherwise
   Pre-condition: language is formatted using formatLanguage
*/
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

/* isTranslationValid checks if an entered word is valid and prints error messages when invalid
   conditions for invalidity:
    - word entered exceeds 20 characters
    - word entered contains spaces
    - no word was entered
   @param word - string containing the word entered
   @param charAfterWord - first character read from input stream after
                          entered word (if any)
   @return true if the word entered is valid and false otherwise
   Pre-condition: language is formatted using formatTranslation
*/
bool 
isTranslationValid(string20 word, char charAfterWord)
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

/* isLTPairValid checks if a language-translation pair entered is valid and prints 
   error messages when invalid
   @param language - string (formatted using formatLanguage) containing the language entered
   @param translation - string (formatted using formatTranslation) containing the language entered
   @param charAfterLang - first character read from input stream after
                          entered language (if any)
   @param charAfterTrans - first character read from input stream after
                          entered translation (if any)
   @return true if the language-translation pair is valid and false otherwise
*/
bool 
isLTPairValid(string20 language, string20 translation, char charAfterLang, char charAfterTrans)
{
    bool isValid = true;

    if (!isTranslationValid(translation, charAfterTrans))
    {
        isValid = false;
    }
    if (!isLanguageValid(language, charAfterLang))
    {
        isValid = false;
    }
    return isValid;
}

/* asks user to whether or not to proceed with an operation 
   @return true if the user chooses to proceeds and false otherwise
*/
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

/* formatLanguage formats a string such that it begins with a capital letter,
   and all proceeding letters are lowercase and contains no newline character
   @param language - string to be formatted
*/
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

/* formatTranslation formats a string such that all letters are lowercase and
   contains no newline character
   @param translation - string to be formatted
*/
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

/* sortIntraEntry sorts the language-translation pairs of an entry
   @param entry - address of entry being sorted
*/
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

/* searchForLTPair searches for a given language-translation pair in an entry
   @param entry - the entry being searched
   @param langKey - language being searched for
   @param transKey - translation being searched for
   @returns the index of the language-translation pair in the entry if 
            the pair is found and -1 otherwise
    Pre-condition: entry is sorted using sortIntraEntry
*/
int 
searchForLTPair(entryType entry, string20 langKey, string20 transKey) // FOR CHECKING
{
    int i;
    int indexOfKey = -1;
    int startIndex = 0;
    int endIndex = entry.pairCount - 1;

    while (strcmp(langKey, entry.pairs[startIndex].language) == 1 && startIndex < entry.pairCount) 
    {
        startIndex++;
    }

    while (strcmp(langKey, entry.pairs[endIndex].language) == -1 && endIndex > startIndex)
    {
        endIndex--;
    }
    
    for (i = startIndex; i <= endIndex && indexOfKey == -1; i++)
    {
        if((strcmp(langKey, entry.pairs[i].language) == 0) && 
		   (strcmp(transKey, entry.pairs[i].translation) == 0))
        {
            indexOfKey = i;
        }
    }

    return indexOfKey;
}

/* searchAllEntriesForLTPair searches an array of entries for a given language-translation pair key
   @param entries - array of entries to be searched
   @param entryCount - number of entries to be searched 
   @param langKey - language of language-translation pair key
   @param transKey - translation of language-translation pair key
   @param entryIndexesWithKey - array where the indexes of the entries where the 
                                language-translation pair key is found
                                will be stored
   @return the number of entries where the language-translation pair key is found
*/
int
searchAllEntriesForLTPair(entryType entries[], int entryCount, string20 langKey, string20 transKey, int entryIndexesWithKey[])
{
    int entriesWithKeyCount = 0;
    int i;
    for (i = 0; i < entryCount; i++)
    {
        if (searchForLTPair(entries[i], langKey, transKey) != -1)
        {
            entryIndexesWithKey[entriesWithKeyCount] = i;
            entriesWithKeyCount++;
        }
    }
    return entriesWithKeyCount;
}

/* printEntry prints an entry to a file
   @param entry - entry being printed
   @param outputFile - address of file where entry will be printed
*/
void 
printEntry(entryType entry, FILE* outputFile)
{
    int i;
    for (i = 0; i < entry.pairCount; i++)
    {
        fprintf(outputFile, "%s: %s\n", entry.pairs[i].language, entry.pairs[i].translation);
    }
}

/* printEntryWithHighlightedPair prints an entry with a highlighed language-translation pair
   @param entry - entry to be printed
   @param langKey -  language of pair to highlight
   @param transKey - translation of pair to highlight
*/
void 
printEntryWithHighlightedPair(entryType entry, string20 langKey, string20 transKey)
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

/* printAllEntriesAsMenu prints entries formatted as a menu
   @param entries - array of entries to be printed
   @param entryCount - number of entries to be printed
*/
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

/* printEntryAsMenu prints the language-translation pairs of an entry formatted as a menu
   @param entry - entry to be printed
*/
void
printEntryAsMenu(entryType entry)
{
    int i;

    for (i = 0; i < entry.pairCount; i++)
    {
        printf("%d - %s: %s\n", (i + 1), entry.pairs[i].language, entry.pairs[i].translation);
    }
}

/* initEntry contains all functions for initializing a new entry
   @param entries - array of entries where new entry will be initialized
   @param entryCount - address containing the number of initialized entries
   @return true if a new entry was successfully initialized and false otherwise
   Pre-condition: the number of initialized entries is less than the 
                  maximum number of entries (150)
*/
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
        getTransOrLang(word, &charAfterWord);
        printf("Enter language: ");
        getTransOrLang(language, &charAfterLang);
        
        formatLanguage(language);
        formatTranslation(word);
	} while (!isLTPairValid(language, word, charAfterLang, charAfterWord));
	
	
	for (i = 0; i < *entryCount; i++)
	{
		if (searchForLTPair(entries[i], language, word) != -1)
		{
			printEntryWithHighlightedPair(entries[i], language, word);
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

/* add LTPair contains all functions for adding a new language-translation pair
   to an existing entry 
   @param entry - address of entry to be modified
*/
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
        getTransOrLang(transToAdd, &charAfterTrans);
        printf("Enter language: ");
        getTransOrLang(langToAdd, &charAfterLang);
        formatLanguage(langToAdd);
        formatTranslation(transToAdd);

    } while (!isLTPairValid(langToAdd, transToAdd, charAfterLang, charAfterTrans));

    if (searchForLTPair(*entry, langToAdd, transToAdd) == -1)
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

/* addEntry contains all functions for the "Add Entry" feature
   @param entries - array of entries where new entry will be added
   @param entryCount - address containing the number of initialized entries
*/
void 
addEntry(entryType entries[], int* entryCount)
{
    bool isNewEntryInitialized;
    bool willAddTranslation;

   if (*entryCount < MAX_ENTRIES)
   {
        entries[*entryCount].pairCount = 0;
        isNewEntryInitialized = initEntry(entries, entryCount);
   }
   else 
   {
        isNewEntryInitialized = false;
        printf(YELLOWFORMATSTRING, "The maximum of 150 entries has been reached\n");
        printf(YELLOWFORMATSTRING, "You may delete exisiting entries to add new ones\n");
   }

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
        
        } while (willAddTranslation && entries[*entryCount - 1].pairCount < MAX_PAIRS_PER_ENTRY);

        if (entries[*entryCount - 1].pairCount == MAX_PAIRS_PER_ENTRY)
        {
            printf(YELLOWFORMATSTRING, "The maximum of 10 translations has been reached\n");
        }
        if (*entryCount > 1)
        {
            sortInterEntry(entries, *entryCount);
        }
   }
    printf("Press any key to return to manage data menu\n");
    getch();
    fflush(stdin);

}

/* printEntriesAsMenuWithHighlight prints entries formatted as a menu with a 
   highlighted language-translation pair
   @param entries - array of initialized entries
   @param langKey - language of highlighted pair
   @param transKey - translation of highlighted pair
   @param indexesToPrint - array containing the indexes of the entries to be printed
   @param entriesToPrintCount - number of entries to print
*/
void 
printEntriesAsMenuWithHighlight(entryType entries[], string20 langKey, string20 transKey, int indexesToPrint[], int entriesToPrintCount)
{
    int i;

    for (i = 0; i < entriesToPrintCount; i++)
    {
        printEntryWithHighlightedPair(entries[indexesToPrint[i]], langKey, transKey);
        printf("\033[0;33m - %d\033[0m", i + 1);
        printf("\n");
    }
}

/* addTranslation contains all the functions for the "Add Translation" feature
   @param entries - array of entries where translation will be added
   @param entryCount - number of initialized entries
*/
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
        getTransOrLang(transKey, &charAfterTrans);
        printf("Enter source language: ");
        getTransOrLang(langKey, &charAfterTrans);
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

        sortInterEntry(entries, entryCount);
    }
    
    if (entriesWithKeyCount > 0 && entries[indexOfEntryToEdit].pairCount == MAX_PAIRS_PER_ENTRY)
    {
        printf(YELLOWFORMATSTRING, "The maximum number of translations has been reached\n");
        printf("Press any key to continue\n");
        getch();
    }
    
	   
}

/* removeLTPair deletes a specified language-translation pair and 
   rearranges the entry to fill the space of the deleted pair
   @param entry - address of entry to be modified
   @param indexOfPairToRemove - the index of the pair to be deleted
*/
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

/* removeLTPair deletes a specified entry and 
   rearranges the entry array to fill the space of the deleted entry
   @param entries - array of entries to be modified
   @param delIndex - index of entry to delete
   @param entryCount - address containing the number of initialized entries
*/

void removeEntry(entryType entries[], int delIndex, int* entryCount)
{
    int i;
    for (i = delIndex; i < *entryCount - 1; i++)
    {
        entries[i] = entries[i + 1];
    }
    setEntryData(&entries[*entryCount - 1]);
    (*entryCount)--;
    
}

/* contains all functions for the "Delete Translation" feature
   @param entries - array of entries
   @param entryCount - address containing number of initialized entries
*/
void 
deleteTranslation(entryType entries[], int *entryCount)
{
    int indexOfEntryToEdit;
    int indexOfPairToDelete;
    bool willDeleteAnother;
    bool isThereValidInteger;
    printf("Select an entry to delete from.\n");
    printf("\n");

    printAllEntriesAsMenu(entries, *entryCount); 
    
    printf("\n");
    printf("Enter the number corresponding to your choice: ");
    getInteger(&indexOfEntryToEdit);
    indexOfEntryToEdit -= 1;

    if (indexOfEntryToEdit >= *entryCount || indexOfEntryToEdit < 0)
    {
        printf(REDFORMATSTRING, "The choice entered is invalid.\n");
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
                    sortInterEntry(entries, *entryCount);
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
            willDeleteAnother = false;
            if (entries[indexOfEntryToEdit].pairCount > 0)
            {
                printf("Would you like to delete another translation\n");
                willDeleteAnother = isOperationConfirmed();

            }
            
        } while (willDeleteAnother);
        
        if (entries[indexOfEntryToEdit].pairCount == 0)
        {
            removeEntry(entries, indexOfEntryToEdit, entryCount);
            printf(YELLOWFORMATSTRING, "All pairs in this entry have been deleted\n");   
        }
        sortInterEntry(entries,*entryCount);  
        printf("Press any key to return to return to \"manage data\" menu\n");
        getch();
        fflush(stdin); 
    }
}

/* contains all functions for the "Delete Entry" feature
   @param entries - array of entries
   @param entryCount - address containing number of initialized entries
*/
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
            removeEntry(entries, delIndex, entryCount);
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

/* printEntryWithHighlightWord prints an entry with all pairs containing a 
   given word is highlighted
   @param entry - the entry to print
   @param keyWord - the word to highlight
*/
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

/* displayAllEntries displays entries one by one
   @param entries - array of entries to display
   @param entryCount - number of entries to be printed
*/
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

/* displaySpecificEntries 
*/
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
                printEntryWithHighlightedPair(entries[indexesOfEntriesToDisplay[indexOfEntryBeingDisplayed]], langKey, wordKey);
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
    int entriesWithKeyWordIndexes[MAX_ENTRIES];
    int entriesWithKeyWordCount = 0;
    int i;
    char charAfterKeyWord;
    do
    {
        charAfterKeyWord = '\n';
        printf("Enter word to search: ");
        getTransOrLang(keyWord, &charAfterKeyWord);
        formatTranslation(keyWord);
    } while (!isTranslationValid(keyWord, charAfterKeyWord));
    
    for (i = 0; i < entryCount; i++)
    {
        if (searchEntryForKeyWord(entries[i], keyWord) != -1)
        {
            entriesWithKeyWordIndexes[entriesWithKeyWordCount] = i;
            entriesWithKeyWordCount++;
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
    int entriesWithLTPairKeyIndexes[MAX_ENTRIES];
    int entriesWithLTPairKeyCount = 0;
    int i;

    do 
    {
        initString(langKey);
        initString(wordKey);
        charAfterLangKey = '\n';
        charAfterWordKey = '\n';

        printf("Enter language: ");
        getTransOrLang(langKey, &charAfterLangKey);
        printf("Enter word: ");
        getTransOrLang(wordKey, &charAfterWordKey);
        formatLanguage(langKey);
        formatTranslation(wordKey);
    } while (!isLTPairValid(langKey, wordKey, charAfterLangKey, charAfterWordKey));

    for (i = 0; i < entryCount; i++)
    {
        if (searchForLTPair(entries[i], langKey, wordKey) != -1)
        {
            entriesWithLTPairKeyIndexes[entriesWithLTPairKeyCount] = i;
            entriesWithLTPairKeyCount++;
           
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
readEntry(FILE* importFile, entryType* tempEntry)
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
 
     printf("Provide the file name of the text file (.txt) to import from\n");
     printf(" - include the \".txt\" file extension in input\n");
     printf(" - file name should not exceed 30 characters (including file extension)\n");
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
             
             wasEntryRead = readEntry(importFile, temp);
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
         sortInterEntry(entries, *entryCount);

         if (*entryCount == MAX_ENTRIES)
         {
             printf(YELLOWFORMATSTRING, "The maximum of 150 entries has been reached\n");
         }
        
         
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
manageData()
{
    int choice;
    entryType entries[MAX_ENTRIES];
    int entryCount = 0;
    do
    {
        choice = manageDataMenu(entryCount);

        switch(choice)
        {
            case 1: addEntry(entries, &entryCount);
                    break;
            
            case 2: importData(entries, &entryCount);
                    break;
            
            case 3: addTranslation(entries, entryCount);
                    break;
            
            case 4: deleteEntry(entries, &entryCount);
                    break;
            
            case 5: deleteTranslation(entries, &entryCount);
                    break;

            case 6: displayAllEntries(entries, entryCount);
                    break;

            case 7: searchByWord(entries, entryCount);
                    break;
            
            case 8: searchByTranslation(entries, entryCount);
                    break;
            
            case 9: exportData(entries, entryCount);
                    break;
        }
    } while (choice != 10);
}

void
removePunctuation(string150 textInput)
{
    int len = strlen(textInput);
    int i, j;

    for (i = 0; i < len; i++)
        if (ispunct(textInput[i]))
        {
            for (j = i; j < len; j++)
            {
                if (j != len - 1)
                {
                    textInput[j] = textInput[j + 1];
                }
                
                else
                {
                    textInput[j] = '\0';
                }
            }

            i--;
        }
}

void
tokenize(string150 textInput, string50 tokens[], int* n_words)
{
    int i = 0;
    char* token;
    string50 tempTokens[50] = {};
    
    removePunctuation(textInput);

    token = strtok(textInput, " ");

    while (token != NULL)
    {
        strcpy(tempTokens[i], token);
        (*n_words)++;
        token = strtok(NULL, " ");
        i++;
    }
    
    memcpy(tokens, tempTokens, sizeof(tempTokens));
}

void
detokenize(string150 result, string50 tokens[], int n_words)
{
    int i;

    strcpy(result, "");

    for (i = 0; i < n_words; i++)
    {
        strcat(result, tokens[i]);

        if (i != n_words - 1)
        {
            strcat(result, " ");
        }
    }
}

void
formatText(string150 text)
{
    int i;
    int lengthOfText = strlen(text);
    if (text[lengthOfText - 1] == '\n')
    {
        text[lengthOfText - 1] = '\0';
        lengthOfText--;
    }
    
    for (i = 0; i < lengthOfText; i++)
    {
        text[i] = tolower(text[i]);
    }
}

bool
isTextValid(string150 text, char charAfterText)
{
    bool isValid = true;
    if (charAfterText != '\n')
    {
        printf(REDFORMATSTRING, "Text exceeds 150 characters.\n");
        isValid = false;
    }
    else if (strlen(text) == 0)
    {
        printf(REDFORMATSTRING, "No text entered.\n");
        isValid = false;
    }
    return isValid;
}

void
getText(string150 text, char* characterAfterInput)
{
	fgets(text, 151, stdin);
    if (strlen(text) == 150)
    {
        *characterAfterInput = getc(stdin);
    }
    fflush(stdin);
}

int
findKeyEntry(entryType sourceEntries[], int n_sourceEntries, LTPairType keyPair)
{
	int i, j;
	int index = -1;
	int found = 0;
	
	for (i = 0; i < n_sourceEntries && !found; i++)
		for (j = 0; j < sourceEntries[i].pairCount && !found; j++)
			if (!strcmp(keyPair.language, sourceEntries[i].pairs[j].language) &&
				!strcmp(keyPair.translation, sourceEntries[i].pairs[j].translation))
				{
					index = i;
					found = 1;	
				}

	return index;
}

int
findTransInEntry(entryType keyEntry, string20 destLang)
{
	int i;
	int index = -1;
    bool isFound = false;
	
	for (i = 0; i < keyEntry.pairCount && !isFound; i++)
    {
		if (strcmp(keyEntry.pairs[i].language, destLang) == 0)
		{
			index = i;
			isFound = true;
		}
    }
	return index;
}

void
translateInput(entryType sourceEntries[], int n_sourceEntries)
{
	string20 sourceLang;
	string150 input;
	string150 original;
	string20 destLang;
	LTPairType keyPair;
	char charAfterLang;
	char charAfterText;
	string50 tokens[50];
	int n_words;
	int keyEntryIndex;
	entryType keyEntry;
	int transPairIndex;
	string150 result;
	int i;
	
	do
	{
		printf("\n");
		
		do 
	    {
	        initString(sourceLang);
	        charAfterLang = '\n';
	        printf("Enter language of source text: ");
	        getTransOrLang(sourceLang, &charAfterLang);
	        formatLanguage(sourceLang);
	    } while (!isLanguageValid(sourceLang, charAfterLang));
	    
	    strcpy(keyPair.language, sourceLang);
	    
	    do
	    {
	    	initString(input);
	    	charAfterText = '\n';
	        printf("Enter text to translate: ");
			getText(input, &charAfterText);
			formatText(input);
		} while (!isTextValid(input, charAfterText));
	    
	    strcpy(original, input);
	    
	    do
	    {
	        initString(destLang);
	        charAfterLang = '\n';
	        printf("Enter language to translate to: ");
	        getTransOrLang(destLang, &charAfterLang);
	        formatLanguage(destLang);
	    } while (!isLanguageValid(destLang, charAfterLang));
	
		n_words = 0;
		tokenize(input, tokens, &n_words);
	
		for (i = 0; i < n_words; i++)
		{
			strcpy(keyPair.translation, tokens[i]);
			keyEntryIndex = findKeyEntry(sourceEntries, n_sourceEntries, keyPair);
	
			if (keyEntryIndex != -1)
			{
				keyEntry = sourceEntries[keyEntryIndex];
				transPairIndex = findTransInEntry(keyEntry, destLang);
				
				if (transPairIndex != -1)
				{
					strcpy(tokens[i], keyEntry.pairs[transPairIndex].translation);
				}
					
			}
		}
		
		detokenize(result, tokens, n_words);
		
		printf("\n");
		printf("In %s, \"%s\" is \"%s\"\n", destLang, original, result);
		printf("\n");
		
		printf("Would you like to make another translation?\n");			
		
	} while (isOperationConfirmed());
	
	printf("\n");
}

void
translateFile(entryType sourceEntries[], int n_sourceEntries)
{
	
}

void 
translate()
{
    int choice;
    FILE *sourceFile;
    entryType sourceEntries[MAX_ENTRIES];
    int n_sourceEntries = 0;
    string30 filename;
    char characterAfterFilename;
    int i = 0;
    
    
	printf("Provide the file name of the text file (.txt) to obtain translation data from\n");
	printf(" - include the \".txt\" file extension in input\n");
	printf(" - file name should not exceed 30 characters (including file extension)\n");
	printf("\n");
    
	do
	{
		initString(filename);
		characterAfterFilename = '\n';
		getFilename(filename, &characterAfterFilename);
		formatFilename(filename);
		sourceFile = fopen(filename, "r");
	} while (!isImportFilenameValid(filename, characterAfterFilename, sourceFile));
	printf("\n");
	
	do
	{
		readEntry(sourceFile, &sourceEntries[i]);
		i++;
		n_sourceEntries++;
	} while (!feof(sourceFile));
	sortInterEntry(sourceEntries, n_sourceEntries);
    
    do
    {
        choice = translateMenu();
		
        switch(choice)
        {
            case 1: translateInput(sourceEntries, n_sourceEntries);
                    break;
            
            case 2: translateFile(sourceEntries, n_sourceEntries);
                    break;
        }
    } while (choice != 3);
}
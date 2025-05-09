#define REDFORMATSTRING "\033[0;31m%s\033[0m"                           // format string to print string in red
#define YELLOWFORMATSTRING "\033[0;33m%s\033[0m"                        // format string to print string in yellow
#define GREENFORMATSTRING "\033[0;32m%s\033[0m"                         // format string to print string in green                      
#define HIGHLIGHTED_PAIR_FORMAT_STRING "\033[0;36m%s: %s <\033[0m\n"    /* format string to print an language-translation
                                                                           pair in cyan */ 
#define DIVIDER "*************************************************************************************************************\n"
#define MAX_ENTRIES 150
#define MAX_PAIRS_PER_ENTRY 10

typedef char string20[21];
typedef char string30[31];
typedef char string50[51];
typedef char string150[151];

typedef struct {
    string20 language;
    string20 translation;
} LTPairType;

typedef struct {
	LTPairType pairs[MAX_PAIRS_PER_ENTRY];
	int pairCount;
} entryType;

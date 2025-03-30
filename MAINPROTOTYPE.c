#include "MP_V2.c"

int
main()
{
    int choice;

	do
    {
        choice = mainMenu();
		
        switch(choice)
        {
            case 1: manageData();
                    break;
            
            case 2: translate();
                    break;
        }
    } while (choice != 3);
}
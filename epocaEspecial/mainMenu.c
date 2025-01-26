
#define DEFAULT_MESSAGE "Wrong option, please try again\n"

#include "mainMenu.h"
#include "structs.h"
#include "input.h"
#include "manageItems.h"
#include "manageUsers.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This function provides the menu to choose between 3 important options... 
 * manage items, manage users, and to save the changes made.
 * @param db Data base that contains everything.
 */
void mainMenu(DataBase *db) {

    int option;
    DataBase *testFile = NULL;
    db = loadData(db, DATABASE_FILE);

    do {
        puts("------------- MAIN MENU -------------");
        puts("[1] Manage Itens");
        puts("[2] Manage Users");
        puts("[3] Save everything");
        puts("[0] Exit");

        option = getInt(0, 3, "option: ");

        switch (option) {
            case 1:
                manageItems(db);
                break;

            case 2:
                userMainMenu(db);
                break;

            case 3:
                testFile = calloc(1, sizeof (db));
                saveData(db, DATABASE_FILE, testFile);
                puts("Saved...");
                break;

            default:
                DEFAULT_MESSAGE;
        }

    } while (option != 0);
    
    free(db);
}
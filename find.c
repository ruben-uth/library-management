
#define DEFAULT_MESSAGE "Wrong message, please try again\n"

#include "find.h"
#include "manageItems.h"
#include "structs.h"
#include "input.h"
#include "listItems.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Checks if the id provided matches with any created user's id.
 * @param db The data base that contains every data.
 * @param userId The id provided.
 * @return User informations if is found or NULL if don't.
 */
User *findUserByID(DataBase *db, int userId) {

    int i;

    for (i = 0; i < db->userCtr; i++) {
        if (db->userPtr[i].id == userId) {
            return &db->userPtr[i];
        }
    }
    return NULL;
}

/**
 * @brief This function provides a menu to print available and/or checked out items.
 * @param db Receives the data base that contains every information.
 */
void findItemByStatus(DataBase *db) {

    int i;
    int option;

    do {
        puts("---- BY STATUS ----");
        puts("[1] Available");
        puts("[2] Loaned");
        puts("[0] Cancel and Back to Search items menu");

        option = getInt(0, 2, "Option: ");

        switch (option) {
            case 1:
                freeItems(db);
                break;

            case 2:
                listCheckedOutItems(db);
                break;

            case 0:
                puts("Backing to search item menu...");
                break;

            default:
                DEFAULT_MESSAGE;
        }

    } while (option != 0);
}

/**
 * @brief This function provides a menu to print the items with the type we want.
 * @param db Receives the data base that contains every information.
 */
void findItemByType(DataBase *db) {

    int option;

    do {
        puts("---- BY TYPE ----");
        puts("[1] BOOK");
        puts("[2] MAGAZINE");
        puts("[3] JOURNAL");
        puts("[4] DVD");
        puts("[5] CD");
        puts("[6] Other");
        puts("[0] Cancel and Back to Search items menu");

        option = getInt(0, 6, "Option: ");

        switch (option) {
            case 1:
                printItemByType(db, BOOK);
                break;

            case 2:
                printItemByType(db, MAGAZINE);
                break;

            case 3:
                printItemByType(db, JOURNAL);
                break;

            case 4:
                printItemByType(db, DVD);
                break;

            case 5:
                printItemByType(db, CD);
                break;

            case 6:
                printItemByType(db, OTHER);
                break;

            case 0:
                puts("Backing to item management menu...");
                break;

            default:
                DEFAULT_MESSAGE;
        }

    } while (option != 0);

}

#define DEFAULT_MESSAGE "Wrong option, please try again\n"

#include "manageItems.h"
#include "structs.h"
#include "input.h"
#include "listItems.h"
#include "actionsItems.h"
#include "find.h"
#include "mainMenu.h"
#include "dateUsefulFunctions.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This function provide the main menu by offering some important options 
 * to manage items. 
 * @param db Data base that contains everything.
 */
void manageItems(DataBase *db) {

    int option;

    do {
        puts("-------------ITEM MANAGEMENT-------------");
        puts("[1] Add Item");
        puts("[2] Remove Item");
        puts("[3] List Items");
        puts("[4] Actions for Items");
        puts("[5] Requisitions");
        puts("[6] Search Item");
        puts("[0] BACK TO MAIN MENU");
        option = getInt(0, 6, "Option: ");

        switch (option) {
            case 1:
                addItem(db);
                break;

            case 2:
                removeItem(db);
                break;

            case 3:
                listItems(db);
                break;

            case 4:
                actionsForItems(db);
                break;

            case 5:
                requisitionsMenu(db);
                break;

            case 6:
                searchItem(db);
                break;

            default:
                DEFAULT_MESSAGE;
        }

    } while (option != 0);
}

/**
 * @brief The goal of this function is to add an item to the data base by asking 
 * to fill the fields up. Every time an item is created it increments 1 the counter 
 * of the items.
 * @param db Data base that contains everything.
 */
void addItem(DataBase *db) {

    if (db == NULL) {
        return;
    }

    printf("Current item count before adding: %d\n", db->itemCtr);

    db->itemCtr++;

    Item *tempPtr = realloc(db->itemPtr, db->itemCtr * sizeof (Item));
    if (tempPtr == NULL) {
        perror("ERROR ON REALLOCATION FOR ITEMS");
        exit(EXIT_FAILURE);
    }

    db->itemPtr = tempPtr;

    printf("Total item count after realloc: %d\n", db->itemCtr);

    Item *newItem = &db->itemPtr[db->itemCtr - 1];

    newItem->id = db->itemCtr;

    puts("--- CATEGORIES ---");
    puts("[1] BOOK");
    puts("[2] MAGAZINE");
    puts("[3] JOURNAL");
    puts("[4] DVD");
    puts("[5] CD");
    puts("[6] OTHER");
    newItem->type = getInt(1, 6, "Choose the category: ") - 1;

    const char *itemTypes[] = {"Book", "Magazine", "Journal", "DVD", "CD", "Other"};
    char promptMessage[MAX_LETTERS + 20];
    snprintf(promptMessage, sizeof (promptMessage), "Name of the %s: ", itemTypes[newItem->type]);

    readString(newItem->title, MAX_LETTERS, promptMessage);

    do {
        printf("Insert the aquisition date of the %s:\n", itemTypes[newItem->type]);
        newItem->acquisitionDate.day = getInt(1, 31, "Day: ");
        newItem->acquisitionDate.month = getInt(1, 12, "Month: ");
        newItem->acquisitionDate.year = getInt(1900, 2024, "Year: ");

    } while (!(isValidAcquiDate(newItem->acquisitionDate)));

    newItem->status = AVAILABLE;

    newItem->requisitionCtr = 0;
    newItem->requisitionHistory = NULL;

    printf("Item added successfully. Current item count: %d\n", db->itemCtr);

}

/**
 * @brief The goal of this function is to remove an item of the data base. It 
 * prints every created items and asks to choose the id of one of them to remove. 
 * Every time an item is removed it decreases 1 the counter of the items.
 * @param db Data base that contains everything.
 */
void removeItem(DataBase *db) {

    int id;
    int confirmation;


    puts("-- ALL ITEMS --");
    allItems(db);

    id = getInt(1, db->itemCtr, "Please insert the id of the item that you would like to remove: ");

    int i;
    int j;

    for (i = 0; i < db->itemCtr; i++) {
        if (db->itemPtr[i].id == id) {
            printItem(&db->itemPtr[i]);

            puts("Are you sure you want ro remove this item?");
            puts("[1] Yes");
            puts("[2] No");
            confirmation = getInt(1, 2, "Selection: ");

            if (confirmation == 1) {
                for (j = i; j < db->itemCtr - 1; j++) {
                    db->itemPtr[j] = db->itemPtr[j + 1];
                }

                db->itemCtr--;
                db->itemPtr = realloc(db->itemPtr, db->itemCtr * sizeof (Item));

                if (db->itemPtr == NULL && db->itemCtr > 0) {
                    perror("Fail to realloate memory.\n");
                    exit(EXIT_FAILURE);
                }

                printf("Item removed successfully.\n");
                return;

            } else {
                puts("Item removal cancelled.");
                return;
            }
        }
    }

    puts("Item ID not found");

}

/**
 * @brief This function provides a menu to choose what do we want to do with some 
 * item, for example, loan it, return it and even modify the item.
 * @param db Data base that contains everything.
 */
void actionsForItems(DataBase *db) {

    int option;

    do {
        puts("---- ACTIONS FOR ITEMS ----");
        puts("[1] Loan Item");
        puts("[2] Return Item");
        puts("[3] Modify Item");
        puts("[0] Back to item management menu");
        printf("Option: ");
        scanf("%d", &option);
        cleanInputBuffer();

        switch (option) {
            case 1:
                loanItem(db);
                break;

            case 2:
                returnItem(db);
                break;

            case 3:
                modifyItem(db);
                break;

            case 0:
                puts("Backing to Manage Items menu...");
                manageItems(db);
                break;

            default:
                DEFAULT_MESSAGE;
        }

    } while (option != 0);
}

/**
 * @brief This function provides a specific menu about the requisitions. It 
 * offers options to list all requisitions and to see which items has active 
 * requisitions. 
 * @param db Data base that contains everything.
 */
void requisitionsMenu(DataBase *db) {

    int option;

    do {
        puts("---- REQUISITIONS MENU ----");
        puts("[1] View All Requisitions");
        puts("[2] View Active Requisitions");
        puts("[0] Back to Item Management");
        option = getInt(0, 2, "Option: ");

        switch (option) {
            case 1:
                allRequisitions(db);
                break;

            case 2:
                listCheckedOutItems(db);
                break;

            case 0:
                puts("Returning to Item Management Menu...");
                manageItems(db);
                break;

            default:
                DEFAULT_MESSAGE;

        }

    } while (option != 0);

}

/**
 * @brief This function provides a specific menu to search about the items. It 
 * offers 2 different conditions to search: The status and the type.
 * @param db Data base that contains everything.
 */
void searchItem(DataBase *db) {

    int option;

    do {
        puts("---- SEARCH ITEM MENU ----");
        puts("[1] Search by Status");
        puts("[2] Search by Type");
        puts("[0] Cancel and Back to Item Management menu");

        option = getInt(0, 2, "Option: ");

        switch (option) {
            case 1:
                findItemByStatus(db);
                break;

            case 2:
                findItemByType(db);
                break;

            case 0:
                puts("Backing to item management menu...");
                manageItems(db);
                break;

            default:
                DEFAULT_MESSAGE;
        }

    } while (option != 0);

}






#define DEFAULT_MESSAGE "Wrong message, please try again\n"

#include "listItems.h"
#include "data.h"
#include "input.h"
#include "structs.h"
#include "manageItems.h"
#include "toString.h"
#include "dateUsefulFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief This function provides a menu to choose which kind of list the user 
 * want to see.
 * @param db dataBase that has every information.
 */
void listItems(DataBase *db) {

    int option;

    do {
        puts("--- LIST MENU ---");
        puts("[1] List all items");
        puts("[2] List free items");
        puts("[3] List Overdue Items");
        puts("[4] Requests in Chronology");
        puts("[0] Back To Item General Menu");
        option = getInt(0, 4, "Selection: ");

        switch (option) {
            case 1:
                allItems(db);
                break;

            case 2:
                freeItems(db);
                break;

            case 3:
                listOverdueItemsByUserType(db);
                break;

            case 4:
                chronologicReq(db);
                break;

            case 0:
                puts("Backing to Item Management menu");
                manageItems(db);
                break;

            default:
                DEFAULT_MESSAGE;
        }

    } while (option != 0);

}

/**
 * @brief This function lists the details of an item.
 * @param item The item received.
 */
void printItem(Item *item) {

    if (item == NULL) {
        puts("INVALID ITEM POINTER");
        return;
    }

    puts("-----");
    printf("Id: %d\n", item->id);
    printf("Title: '%s'\n", item->title);
    printf("Type: %s\n", itemTypeToString(item->type));
    printf("Status: %s\n", itemStatusToString(item->status));
    printf("Date of acquisition: %02d/%02d/%04d\n",
            item->acquisitionDate.day,
            item->acquisitionDate.month,
            item->acquisitionDate.year);
}

/**
 * @brief This function prints the details of the item including the requisition 
 * data.
 * @param item The item with requisition received.
 * @param req List of the requisitions.
 */
void printItemWithReq(Item *item, Requisition *req) {
    if (item == NULL || req == NULL) {
        puts("Invalid input");
        return;
    }

    printItem(item);
    printf("Date of requisition: %02d/%02d/%04d\n",
            req->requisitionDate.day,
            req->requisitionDate.month,
            req->requisitionDate.year);
    printf("Due Date: %02d/%02d/%04d\n",
            req->returnDate.day,
            req->returnDate.month,
            req->returnDate.year);

    printf("Returned: %s\n", req->returned ? "Yes" : "No");
    puts("--------");

}

/**
 * @brief This function is responsible to find an item that has the status as CHECKED_OUT.
 * If the id provided matches with the item's id, it returns the item.
 * @param db Data base that contains everything.
 * @param id Id provided.
 * @return The item if founded.
 */
Item* findCheckedOutItemById(DataBase *db, int id) {
    for (int i = 0; i < db->itemCtr; i++) {
        Item *item = &db->itemPtr[i];
        if (item->id == id && item->status == CHECKED_OUT) {
            return item;
        }
    }
    return NULL;
}

/**
 * @brief This function prints every item that has active requisitions.
 * @param db Data base that contains everything.
 * @return The number of items found.
 */
int listCheckedOutItems(DataBase *db) {
    int counter = 0;

    for (int i = 0; i < db->itemCtr; i++) {
        Item *item = &db->itemPtr[i];
        if (item->status == CHECKED_OUT) {
            counter++;
        }
    }

    if (counter > 0) {
        printf("Found %d items with CHECKED OUT status.\n", counter);

        for (int i = 0; i < db->itemCtr; i++) {
            Item *item = &db->itemPtr[i];
            if (item->status == CHECKED_OUT) {
                for (int j = 0; j < item->requisitionCtr; j++) {
                    Requisition *req = &item->requisitionHistory[j];
                    if (!req->returned) {
                        printItemWithReq(item, req);
                    }
                }
            }
        }
    } else {
        puts("No loaned items found");
    }

    return counter;
}

/**
 * @brief Prints every created items.
 * @param db Data base that contains everything.
 */
void allItems(DataBase *db) {

    if (db->itemCtr == 0) {
        puts("There isn't any created items...");
        return;
    }
    
    printf("Current item count: %d\n", db->itemCtr);

    int i;

    for (i = 0; i < db->itemCtr; i++) {
        printItem(&db->itemPtr[i]);
    }
}

/**
 * @brief This function compares the length of 2 titles. 
 * @param a 1st title.
 * @param b 2nd title.
 * @return negative if item1 title is less than item2 title, positive value if 
 * item1 title is bigger than item2 title, 0 if the same.
 */
int compareTitles(const void *a, const void *b) {
    const Item *item1 = (const Item *) a;
    const Item *item2 = (const Item *) b;
    return strcmp(item1->title, item2->title);
}

/**
 * @brief This function lists every free items.
 * @param db Data base that contains everything.
 * @return Number of free items.
 */
int freeItems(DataBase *db) {

    if (db->itemCtr == 0) {
        puts("There isn't any created items...");
        return 0;
    }

    Item *freeItems = malloc(db->itemCtr * sizeof (Item));

    int counter = 0;
    int i;
    for (i = 0; i < db->itemCtr; i++) {
        if (db->itemPtr[i].status == AVAILABLE) {
            freeItems[counter++] = db->itemPtr[i];
        }
    }

    if (counter > 0) {

        printf("Found %d items with AVAILABLE status.\n", counter);
        qsort(freeItems, counter, sizeof (Item), compareTitles);

        for (i = 0; i < counter; i++) {
            printItem(&freeItems[i]);
        }
    } else {
        puts("No free items available");
    }

    free(freeItems);

    return counter;

}

/**
 * @brief This function lists every overdue items based on the user's role, that 
 * checks if has 15 days to return or 30.
 * @param db Data base that contains everything.
 */
void listOverdueItemsByUserType(DataBase *db) {

    Date today = getCurrentDate();

    int i;
    int j;

    for (i = 0; i < db->itemCtr; i++) {
        Item *item = &db->itemPtr[i];

        for (j = 0; j < item->requisitionCtr; j++) {
            Requisition *req = &item->requisitionHistory[j];
            if (!req->returned) {
                if (isDatePast(today, req->returnDate)) {
                    printf("-- ITEM OVERDUE! --\n"
                            "User Role: %s\n"
                            "Item Type: %s\n"
                            "Title: %s\n"
                            "Requisition Date: %02d/%02d/%04d\n"
                            "Due Date: %02d/%02d/%04d\n",
                            userRoleToString(req->role),
                            itemTypeToString(item->type),
                            item->title,
                            req->requisitionDate.day,
                            req->requisitionDate.month,
                            req->requisitionDate.year,
                            req->returnDate.day,
                            req->returnDate.month,
                            req->returnDate.year);
                }
            }
        }
    }
}

/**
 * @brief This function lists the details of the item and of the requisition but 
 * by chronology.
 * @param db Data base that contains everything.
 */
void chronologicReq(DataBase *db) {

    if (db->itemCtr == 0) {
        return;
    }

    puts("----- LOAN HISTORY ----");
    int i;
    int j;

    for (i = 0; i < db->itemCtr; i++) {
        Item *item = &db->itemPtr[i];

        if (item->requisitionCtr > 0) {
            sortDate(item->requisitionHistory, item->requisitionCtr);

            for (j = 0; j < item->requisitionCtr; j++) {
                Requisition *req = &item->requisitionHistory[j];
                printItemWithReq(item, req);
            }
        }
    }
}

/**
 * @brief This function lists all the details of the item and the requisition but 
 * not by chronology.
 * @param db Data base that contains everything.
 */
void allRequisitions(DataBase *db) {

    if (db->itemCtr == 0) {
        puts("There isn't any created items");
        return;
    }

    int i;
    int j;
    puts("-- ENTIRE REQUISITION LIST --");

    for (i = 0; i < db->itemCtr; i++) {

        Item *item = &db->itemPtr[i];

        for (j = 0; j < item->requisitionCtr; j++) {

            Requisition *req = &item->requisitionHistory[j];

            printItemWithReq(item, req);

        }
    }
}

/**
 * @brief This function prints the details of the items that has the same type 
 * as the provided one.
 * @param db Data base that contains everything.
 * @param type The item type provided.
 * @return The number of the items with the type provided.
 */
int printItemByType(DataBase *db, ItemType type) {

    int counter = 0;
    int i;

    for (i = 0; i < db->itemCtr; i++) {
        if (db->itemPtr[i].type == type) {
            printItem(&db->itemPtr[i]);
            counter++;
        }
    }

    if (counter > 0) {
        printf("Found %d items of type: %s.\n", counter, itemTypeToString(type));
    } else {
        printf("No items of type %s found.\n", itemTypeToString(type));
    }

    return counter;
}


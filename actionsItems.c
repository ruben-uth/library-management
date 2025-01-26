
#define DEFAULT_MESSAGE "Wrong option, please try again\n"

#include "actionsItems.h"
#include "manageItems.h"
#include "structs.h"
#include "input.h"
#include "listItems.h"
#include "dateUsefulFunctions.h"
#include "find.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief The goal of this function is to loan items to some user.
 * In first place checks if there is any user created to attribute the item to. 
 * If it's 0 users created, then it stops and informs that there isn't any user created.
 * Then checks if there is any item created and if exists, checks if it's free to 
 * loan (if the status is AVAILABLE), by calling freeItems function.
 * 
 * The requisition date has to be posterior to the acquisition date and before the current date.
 * 
 * If there is some user and an available item, then print the item or the items 
 * and asks to put its ID.
 * If the id provided is the same as any available item, then asks for the user 
 * ID to loan to him.
 * 
 * @param db
 */
void loanItem(DataBase *db) {

    if (db->userCtr == 0) {
        puts("-");
        puts("There isn't any user created");
        return;
    }

    if (db->itemCtr == 0) {
        puts("-");
        puts("There isn't any item created");
        return;
    }

    if (freeItems(db) == 0) {
        puts("No available items to loan.");
        return;
    }

    int id, userID;
    int i;
    int flag = 0;
    int confirmation;

    puts("-");

    id = getInt(1, db->itemCtr, "Please provide the item ID you want to loan: ");

    for (i = 0; i < db->itemCtr; i++) {

        Item *item = &db->itemPtr[i];

        if (item->id == id) {
            flag = 1;

            if (item->status == CHECKED_OUT) {
                puts("Sorry, already loaned");
                return;
            } else {
                printItem(item);

                puts("Do you really want to loan this item?");
                confirmation = getInt(1, 2, "[1] Yes\n[2] No\nSelection: ");

                if (confirmation == 1) {

                    Date requisitionDate;

                    requisitionDate.day = getInt(1, 31, "Day: ");
                    requisitionDate.month = getInt(1, 12, "Month: ");
                    requisitionDate.year = getInt(1900, 2024, "Year: ");

                    Date currentDate = getCurrentDate();

                    if (!isRequisitionDateInRange(item->acquisitionDate, requisitionDate, currentDate)) {
                        printf("Please insert between %02d/%02d/%04d and %02d/%02d/%04d\n",
                                item->acquisitionDate.day, item->acquisitionDate.month, item->acquisitionDate.year,
                                currentDate.day, currentDate.month, currentDate.year);
                        return;
                    }

                    item->requisitionCtr++;

                    puts("Please insert User ID.");
                    userID = getInt(1, 100000, "User ID: ");

                    User *user = findUserByID(db, userID);

                    if (user == NULL) {
                        puts("User not found");
                        return;
                    } 

                    if(user->status == INACTIVE && user->activeRequisitionCtr != 0){
                        puts("It's not available to loan more items to this user, unless it's active");
                        break;
                    }
                    
                    
                    user->activeRequisitionCtr++;
                    item->status = CHECKED_OUT;
                    printf("Item status updated to CHECKED_OUT\n");

                    Requisition newReq;
                    newReq.userId = userID;
                    newReq.requisitionId = item->requisitionCtr;
                    newReq.returned = 0;
                    newReq.requisitionDate = requisitionDate;
                    newReq.returnDate = addDays(newReq.requisitionDate, userDays(user));
                    newReq.role = user->role;

                    item->requisitionHistory = realloc(item->requisitionHistory, sizeof (Requisition) * (item->requisitionCtr + 1));
                    item->requisitionHistory[item->requisitionCtr - 1] = newReq;

                    puts("Item Loaned Successfully");
                    printf("Requisition added: userID: %d, requisitionID: %d\n", newReq.userId, newReq.requisitionId);
                    return;

                } else {
                    puts("Item not loaned (Operation canceled)");
                    return;
                }
            }
        }
    }

    if (!flag) {
        puts("ITEM NOT FOUND");
    }
}

/**
 * @brief The goal of this function is to return an loaned item.
 * 
 * It starts by checking if there is any item created, if it doesn't then stops 
 * by informing that there isn't any item created.
 * 
 * In case there is at least one, it asks by the id of the item and if it doesn't 
 * match with any created item's id (by calling findCheckedOutItemById) it stops 
 * by informing that the item wasn´t found.
 * 
 * If it matches with some item's id, then it's returned successfully.
 * 
 * @param db
 */
void returnItem(DataBase *db) {
    if (db->itemCtr == 0) {
        puts("There isn't any item created.");
        return;
    }

    puts("-");
    int id = getInt(1, db->itemCtr, "Please insert the ID of the item to return.\nId: ");
    Item *item = findCheckedOutItemById(db, id);

    if (item == NULL) {
        puts("Item not found or not checked out.");
        return;
    }

    int requisitionFound = 0;
    for (int j = 0; j < item->requisitionCtr; j++) {
        Requisition *req = &item->requisitionHistory[j];
        if (req->userId != -1 && !req->returned) { 
            req->returned = 1;
            item->status = AVAILABLE;
            User *user = findUserByID(db, req->userId);
            user->activeRequisitionCtr--;
            puts("Item Returned successfully");
            requisitionFound = 1;
            break; 
        }
    }

    if (!requisitionFound) {
        puts("No active requisitions found for this item.");
    }
}

/**
 * @brief The goal of this function is to modify the detail of some created item.
 * 
 * It starts by printing all the created items by calling allItems function.
 * The it prompts a message to insert the item id we want to modify, and checks 
 * if it's valid by calling getInt function that has the range from the first to 
 * the last created item.
 * 
 * It prints the details of the respective item with the id provided. It's asked 
 * what is wanted to modify and requests to write or to input the respective 
 * choosed field.
 * 
 * @param db
 */
void modifyItem(DataBase *db) {

    int id;
    int i;

    puts("----- ITEMS LIST -----");

    for (i = 0; i < db->itemCtr; i++) {
        printItem(&db->itemPtr[i]);
    }

    puts("--");
    puts("Please insert the Item ID.");
    id = getInt(1, db->itemCtr, "ID: ");

    for (i = 0; i < db->itemCtr; i++) {
        Item *item = &db->itemPtr[i];

        if (item->id == id) {
            puts("-- DETAILS OF THE ITEM --");
            printItem(item);

            int option;

            do {
                puts("--");
                puts("What would you like to change?");
                puts("[1] Title");
                puts("[2] Type");
                puts("[0] Finish Changes and go back.");
                option = getInt(0, 2, "Option: ");

                switch (option) {
                    case 1:
                        readString(item->title, MAX_LETTERS, "New Title: ");
                        puts("Title changed successfully.");
                        break;

                    case 2:
                        puts("AVAILABLE TYPES:");
                        puts("[1] Book");
                        puts("[2] Magazine");
                        puts("[3] Journal");
                        puts("[4] DVD");
                        puts("[5] CD");
                        puts("[6] Other");
                        item->type = getInt(1, 6, "Choose the new Type: ") - 1;
                        puts("Type changed successfully.");
                        break;

                    case 0:
                        puts("Changes concluded");
                        actionsForItems(db);
                        break;

                    default:
                        DEFAULT_MESSAGE;
                }
            } while (option != 0);
        }
    }
}
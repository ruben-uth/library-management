
#define DEFAULT_MESSAGE "Wrong option, please try again\n"

#include "manageUsers.h"
#include "structs.h"
#include "input.h"
#include "mainMenu.h"
#include "listUsers.h"
#include "find.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief This function provide the main menu by offering some important options 
 * to manage users. 
 * @param db Data base that contains everything.
 */
void userMainMenu(DataBase *db) {

    int option;

    do {
        puts("------------- USER MANAGEMENT -------------");
        puts("[1] Add User");
        puts("[2] Edit User");
        puts("[3] Remove User");
        puts("[4] List users");
        puts("[0] Exit and back to main menu.");

        option = getInt(0, 4, "Option: ");

        switch (option) {

            case 1:
                addUser(db);
                break;

            case 2:
                editUser(db);
                break;

            case 3:
                removeUser(db);
                break;

            case 4:
                listUsers(db);
                break;

            default:
                DEFAULT_MESSAGE;

        }
    } while (option != 0);
}

/**
 * @brief The goal of this function is to add a user to the data base by asking 
 * to fill the fields up. Every time a user is created it increments 1 the counter 
 * of the users.
 * @param db Data base that contains everything.
 */
void addUser(DataBase *db) {

    if (db == NULL) {
        return;
    }

    db->userCtr++;
    User *tempPtr = realloc(db->userPtr, db->userCtr * sizeof (User));
    if (tempPtr == NULL) {
        perror("ERROR ON REALLOCATION FOR USERS");
        exit(EXIT_FAILURE);
    }

    db->userPtr = tempPtr;

    User *newUser = &db->userPtr[db->userCtr - 1];

    readString(newUser->name, MAX_LETTERS, "Please enter the user's name: ");

    newUser->id = getInt(1, 100000, "Please enter the ID: ");

    puts("--- ROLE ---");
    puts("[1] STUDENT");
    puts("[2] TEACHER");
    puts("[3] STAFF");

    newUser->role = getInt(1, 3, "Please choose the role: ") - 1;

    readString(newUser->email.emailUserName, MAX_LETTERS, "Enter the email username (before the '@', please.\nUser name: ");

    puts("Select email domain.");
    puts("[1] @gmail.com");
    puts("[2] @hotmail.com");
    puts("[3] @outlook.com");
    puts("[4] @yahoo.com");
    puts("[5] @estg.ipp.pt");

    newUser->email.domain = getInt(1, 5, "Domain: ") - 1;

    newUser->status = ACTIVE;
    newUser->activeRequisitionCtr = 0;
    newUser->activeRequisitions = NULL;

    printf("User added successfully. Current user count: %d\n", db->userCtr);

}

/**
 * @brief This function provides a menu to list the users based on some conditions... 
 * it can print every user created, active users and inactive users.
 * @param db Data base that contains everything.
 */
void listUsers(DataBase *db) {

    int option;

    do {
        puts("---- List Users Menu ----");
        puts("[1] All users");
        puts("[2] Active users");
        puts("[3] Inactive users");
        puts("[0] Back to item management menu");

        option = getInt(0, 3, "Option: ");

        switch (option) {
            case 1:
                listAllUsers(db);
                break;

            case 2:
                listActiveUsers(db);
                break;

            case 3:
                listInactiveUsers(db);
                break;

            case 0:
                puts("Backing to item management menu...");
                userMainMenu(db);
                break;

            default:
                DEFAULT_MESSAGE;
        }
    } while (option != 0);

}

/**
 * @brief This function is responsible to change the details of the user. It starts 
 * by printing all the users created. Then asks the id of the user we want to modify, 
 * after that checks if matches with some already created user's id.
 * It's only allowed to modify a user if has the status as ACTIVE.
 * Then asks to fill the field we want up.
 * @param db Data base that contains everything.
 */
void editUser(DataBase *db) {

    int id;
    int i;

    puts("---- USERS LIST ----");

    for (i = 0; i < db->userCtr; i++) {
        printUser(&db->userPtr[i]);
    }

    puts("--");
    puts("Please insert the USER ID you want to modify");
    id = getInt(1, 100000, "Id: ");

    for (i = 0; i < db->userCtr; i++) {

        User *user = findUserByID(db, id);

        if (user == NULL) {
            puts("USER NOT FOUND");
            return;
        }
        puts("-- USER'S DETAILS --");
        printUser(user);

        int confirmation;

        if (user->status == INACTIVE) {
            puts("To modify this user, you need to change the status to ACTIVE... Do you still want to proceed?");
            confirmation = getInt(1, 2, "[1] YES\n[2] NO\nConfirmation: ");

            if (confirmation == 1) {
                user->status = ACTIVE;
                puts("STATUS MODIFIED");
            } else {
                puts("OPERATION CANCELLED");
                return;
            }
        }

        int option;
        int emailOption;

        do {
            puts("--");
            puts("What would you like to modify?");
            puts("[1] Name");
            puts("[2] User ID");
            puts("[3] User Role");
            puts("[4] User Status");
            puts("[5] Email");
            puts("[0] Exit and finish changes");

            option = getInt(0, 5, "Option: ");

            switch (option) {
                case 1:
                    readString(user->name, MAX_LETTERS, "New Name: ");
                    puts("User's name updated");
                    break;

                case 2:
                    user->id = getInt(1, 100000, "New ID: ");
                    puts("User's ID updated");
                    break;

                case 3:
                    puts("- SELECT ROLE -");
                    puts("[1] STUDENT");
                    puts("[2] TEACHER");
                    puts("[3] STAFF");

                    user->role = getInt(1, 3, "Role: ") - 1;
                    puts("User's role updated");
                    break;

                case 4:
                    puts("Changing to INACTIVE...");
                    user->status = INACTIVE;
                    puts("As the user's status is now INACTIVE you cannot modify the "
                            "user anymore unless you change back to ACTIVE");
                    userMainMenu(db);
                    break;

                case 5:
                    puts("Do you want to change the user name's before '@' or the domain?");
                    emailOption = getInt(1, 2, "[1] Name\n[2] Domain\nOption: ");

                    if (emailOption == 1) {
                        readString(user->email.emailUserName, MAX_LETTERS, "Enter the email username (before the '@', please.\nUser name: ");
                        puts("Email user name updated.");

                    } else if (emailOption == 2) {

                        puts("- Select Domain -");
                        puts("[1] @gmail.com");
                        puts("[2] @hotmail.com");
                        puts("[3] @outlook.com");
                        puts("[4] @yahoo.com");
                        puts("[5] @estg.ipp.pt");

                        user->email.domain = getInt(1, 5, "Option: ") - 1;

                        puts("Email domain updated.");

                    }
                    break;

                case 0:
                    puts("Bacing to users main menu...");
                    userMainMenu(db);
                    break;

                default:
                    DEFAULT_MESSAGE;
            }

        } while (option != 0);
    }
}

/**
 * @brief The goal of this function is to remove a user of the data base. It 
 * prints every created users and asks to choose the id of one of them to remove. 
 * If the user has some requisition active, it´s not possible to remove him, but 
 * it's possible to change the status to inactive.
 * Every time a user is removed it decreases 1 the counter of the users.
 * @param db Data base that contains everything.
 */
void removeUser(DataBase *db) {

    int id;
    int confirmation;
    int i;

    puts("---- USER LIST ----");
    for (i = 0; i < db->userCtr; i++) {
        printUser(&db->userPtr[i]);
    }

    puts("--");
    puts("Please insert the USER ID you want to remove: ");
    id = getInt(0, 100000, "Id: ");

    User *user = findUserByID(db, id);

    if (user == NULL) {
        puts("USER NOT FOUND");
        return;
    }

    if (user->activeRequisitionCtr > 0) {
        puts("User has active requisitions... changing his status to INACTIVE...");
        user->status = INACTIVE;
        puts("User status changed to INACTIVE successfully");

    } else {
        for (int i = 0; i < db->userCtr; i++) {
            if (db->userPtr[i].id == id) {
                for (int j = 0; j < db->userCtr - 1; j++) {
                    db->userPtr[j] = db->userPtr[j + 1];
                }
                db->userCtr--;
                db->userPtr = realloc(db->userPtr, db->userCtr * sizeof (User));
                if(db->userPtr == NULL && db->userCtr > 0){
                    puts("FAILED TO REALLOCATE MEMORY");
                    exit(EXIT_FAILURE);
                }
                puts("User removed successfully");
                printf("%d users created after this.\n", db->userCtr);
                return;
            }
        }
    }
}

/**
 * @brief This function is responsible to check if some user has active 
 * requisitions or not.
 * @param user It receiver the user to check.
 * @return return 1 if has active requisitions.
 */
int hasActiveRequests(User *user) {
    if (user->activeRequisitionCtr == 0) {
        return 0;
    }

    int i;

    for (i = 0; i < user->activeRequisitionCtr; i++) {
        if (!user->activeRequisitions[i].returned) {
            return 1;
        }
    }

    return 0;

}
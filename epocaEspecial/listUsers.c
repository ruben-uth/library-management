
#include "listUsers.h"
#include "manageUsers.h"
#include "structs.h"
#include "input.h"
#include "mainMenu.h"
#include "toString.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief This function lists the details of an user.
 * @param user The user received.
 */
void printUser(User *user) {

    if (user == NULL) {
        puts("INVALID USER POINTER");
        return;
    }

    puts("-----");
    printf("ID: %d\n", user->id);
    printf("Name: %s\n", user->name);
    printf("Email: %s%s\n", user->email.emailUserName, emailDomainToString(user->email.domain));
    printf("Role: %s\n", userRoleToString(user->role));
    printf("Status: %s\n", userStatusToString(user->status));

}

/**
 * @brief Prints every created users.
 * @param db Data basse that contains everything.
 */
void listAllUsers(DataBase *db) {

    if (db->userCtr == 0) {
        puts("There isn't any users created...");
        return;
    }

    printf("Current users count: %d\n", db->userCtr);

    printf("-- LISTING ALL USERS (%d users found) --\n", db->userCtr);

    for (int i = 0; i < db->userCtr; i++) {
        printUser(&db->userPtr[i]);
    }
}

/**
 * @brief Lists every user that has the status ACTIVE. It creates an array of 
 * active users, to pass by argument to the function printUser.
 * @param db Data base that contains everything.
 * @return The number of active users.
 */
int listActiveUsers(DataBase *db) {

    if (db->userCtr == 0) {
        puts("There isn't any user creater");
        return 0;
    }

    User *activeUsers = malloc(db->userCtr * sizeof (User));

    int i;
    int counter = 0;

    for (i = 0; i < db->userCtr; i++) {
        if (db->userPtr[i].status == ACTIVE) {
            activeUsers[counter++] = db->userPtr[i];
        }
    }

    if (counter > 0) {
        puts("--");
        printf("Found %d ACTIVE users.\n", counter);

        for (i = 0; i < counter; i++) {
            printUser(&activeUsers[i]);
        }
    } else {
        puts("NO ACTIVE USERS AVAILABLE");
    }

    free(activeUsers);

    return counter;

}

/**
 * @brief Lists every user that has the status INACTIVE. It creates an array of 
 * inactive users, to pass by argument to the function printUser.
 * @param db Data base that contains everything.
 * @return The number of inactive users.
 */
int listInactiveUsers(DataBase *db) {

    if (db->userCtr == 0) {
        puts("There isn't any user creater");
        return 0;
    }

    User *inactiveUsers = malloc(db->userCtr * sizeof (User));

    int i;
    int counter = 0;

    for (i = 0; i < db->userCtr; i++) {
        if (db->userPtr[i].status == INACTIVE) {
            inactiveUsers[counter++] = db->userPtr[i];
        }
    }

    if (counter > 0) {
        puts("--");
        printf("Found %d INACTIVE users.\n", counter);

        for (i = 0; i < counter; i++) {
            printUser(&inactiveUsers[i]);
        }
    } else {
        puts("NO INACTIVE USERS AVAILABLE");
    }

    free(inactiveUsers);

    return counter;

}



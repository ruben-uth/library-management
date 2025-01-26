/**
 * @file manageUsers.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file provides a main User menu to do the main 
 * features as adding, removing, editing, list...
 */

#ifndef MANAGEUSERS_H
#define MANAGEUSERS_H

#include "structs.h"

void userMainMenu(DataBase *db);
void addUser(DataBase *db);
void listUsers(DataBase *db);
void editUser(DataBase *db);
void removeUser(DataBase *db);
int hasActiveRequests(User *user);

#endif /* MANAGEUSERS_H */

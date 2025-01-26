/**
 * @file listUsers.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file provides functions to list only users, based on 
 * conditions.
 */

#ifndef LISTUSERS_H
#define LISTUSERS_H

#include "structs.h"

void printUser(User *user);
void listAllUsers(DataBase *db);
int listActiveUsers(DataBase *db);
int listInactiveUsers(DataBase *db);

#endif /* LISTUSERS_H */

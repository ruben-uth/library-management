/**
 * @file find.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file is really useful to use functions that are made to 
 * find users or items with the some conditions.
 */

#ifndef FIND_H
#define FIND_H
#include "structs.h"

User* findUserByID(DataBase *db, int id);
void findItemByStatus(DataBase *db);
void findItemByType(DataBase *db);

#endif /* FIND_H */

/**
 * @file listItems.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file provides functions to list only items, based on 
 * conditions.
 */

#ifndef LISTITEMS_H
#define LISTITEMS_H
#include "structs.h"

void listItems(DataBase *db);
void printItem(Item *item);
void printItemWithReq(Item *item, Requisition *req);
Item* findCheckedOutItemById(DataBase *db, int id);
int listCheckedOutItems(DataBase *db);
void allItems(DataBase *db);
int compareTitles(const void *a, const void *b);
int freeItems(DataBase *db);
void listOverdueItemsByUserType(DataBase *db);
void chronologicReq(DataBase *db);
void allRequisitions(DataBase *db);
int printItemByType(DataBase *db, ItemType type);



#endif /* LISTITEMS_H */

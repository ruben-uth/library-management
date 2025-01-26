/**
 * @file manageItems.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file provides a main Item menu to do the main 
 * features as adding, removing, editing, actions...
 */

#ifndef MANAGAITEMS_H
#define MANAGAITEMS_H

#include "structs.h"

void manageItems(DataBase *itemList);
void addItem(DataBase *itemList);
void removeItem(DataBase *itemList);
void actionsForItems(DataBase *itemList);
void requisitionsMenu(DataBase *itemList);
void searchItem(DataBase *itemList);

#endif /* MANAGAITEMS_H */

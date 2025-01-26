/**
 * @file mainMenu.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file provide the menu where we can manage the items, 
 * manage the users and to save every changes made.
 */

#ifndef MAINMENU_H
#define MAINMENU_H
#include "structs.h"

#define DATABASE_FILE "database.bin"

void mainMenu(DataBase *db);

#endif /* MAINMENU_H */

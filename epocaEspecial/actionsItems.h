/**
 * @file actionsItems.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file contains powerful and useful functions for the items.
 * To loan, to return and to modify the details.
 */
#ifndef ACTIONSITEMS_H
#define ACTIONSITEMS_H

#include "structs.h"

void loanItem(DataBase *db);
void returnItem(DataBase *db);
void modifyItem(DataBase *db);

#endif /* ACTIONSITEMS_H */

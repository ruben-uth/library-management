/**
 * @file data.h
 * @file Rúben Uth
 * @date 07-09-2024
 * @brief This header file is really important because it initializes the data 
 * base, that contains everything of the project. It has some powerful and essential 
 * functions to manipulate the data to be saved and loaded to and from our computer.
 */

#ifndef DATA_H
#define DATA_H
#include "structs.h"
#include <stdio.h>

DataBase *initDataBase(DataBase *dataBase);
DataBase *saveData(DataBase *db, char *filename, DataBase *file);
DataBase *loadData(DataBase *db, char *filename);

#endif /* DATA_H */

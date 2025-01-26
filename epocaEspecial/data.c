
#include "data.h"
#include "structs.h"
#include "mainMenu.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This function is responsible to initialize the data base of the program 
 * and it's used in the beggining of the project.
 * @param dataBase The list to be initialize.
 * @return dataBase modified (initialized) and ready to be manipulated.
 */
DataBase *initDataBase(DataBase *dataBase) {
    dataBase->itemPtr = NULL;
    dataBase->requisitionHistory = NULL;
    dataBase->userPtr = NULL;

    dataBase->itemCtr = 0;
    dataBase->requisitionCtr = 0;
    dataBase->userCtr = 0;

    return dataBase;
}

/**
 * @brief This function is responsible to save all the data made/created during 
 * the project, as for example: created users, items, requisitions.
 * @param db The list that contains all data
 * @param filename Name of the file to be saved there.
 * @param file A list to be manipulated in the beggining of the project.
 * @return dataBase updated.
 */
DataBase *saveData(DataBase *db, char *filename, DataBase *file) {

    int i;

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("ERROR OPENING FILE TO WRITING");
        exit(EXIT_FAILURE);
    }

    fwrite(&db->itemCtr, sizeof (int), 1, fp);
    fwrite(&db->requisitionCtr, sizeof (int), 1, fp);
    fwrite(&db->userCtr, sizeof (int), 1, fp);

    for (i = 0; i < db->itemCtr; i++) {
        fwrite(&db->itemPtr[i], sizeof (Item), 1, fp);
    }

    for (i = 0; i < db->requisitionCtr; i++) {
        fwrite(&db->requisitionHistory[i], sizeof (Requisition), 1, fp);
    }
    for (i = 0; i < db->userCtr; i++) {
        fwrite(&db->userPtr[i], sizeof (User), 1, fp);
    }

    fclose(fp);
    return db;

}

/**
 * @brief This functions is responsible to load the data created before, it it exists... 
 * otherwise it will be initialized the data base for the first use.
 * @param db
 * @param filename
 * @return 
 */
DataBase *loadData(DataBase *db, char *filename) {

    
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("File not found... initializing a new data base");
        db = malloc(1 * sizeof(DataBase));

        db->itemPtr = NULL;
        db->requisitionHistory = NULL;
        db->userPtr = NULL;

        db->itemCtr = 0;
        db->requisitionCtr = 0;
        db->userCtr = 0;

        return db;
    }

    fread(&db->itemCtr, sizeof (int), 1, fp);
    fread(&db->requisitionCtr, sizeof (int), 1, fp);
    fread(&db->userCtr, sizeof (int), 1, fp);

    db->itemPtr = malloc(db->itemCtr * sizeof (Item));
    if (db->itemPtr == NULL) {
        perror("Error allocating memory for items");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    db->requisitionHistory = malloc(db->requisitionCtr * sizeof (Requisition));
    if (db->requisitionHistory == NULL) {
        perror("Error allocating memory for requisitions");
        free(db->itemPtr);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    db->userPtr = malloc(db->userCtr * sizeof (User));
    if (db->userPtr == NULL) {
        perror("Error allocating memory for users");
        free(db->itemPtr);
        free(db->requisitionHistory);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fread(db->itemPtr, sizeof (Item), db->itemCtr, fp);

    fread(db->requisitionHistory, sizeof (Requisition), db->requisitionCtr, fp);

    fread(db->userPtr, sizeof (User), db->userCtr, fp);

    fclose(fp);
    return db;
}
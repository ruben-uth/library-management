
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "mainMenu.h"
#include "data.h"

/**
 * @brief It's in this function where we call the function initDataBase to 
 * initialize everything.
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {

    DataBase *db = calloc(1, sizeof (DataBase));
    db = initDataBase(db);
    
    mainMenu(db);

    return (EXIT_SUCCESS);
}


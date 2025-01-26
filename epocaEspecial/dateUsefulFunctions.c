
#include "dateUsefulFunctions.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief This function is used is some parts of the project, so it's very useful.
 * It's responsible to give the current local time.
 * @return The date with the format day month year.
 */
Date getCurrentDate() {

    time_t now;
    time(&now);
    struct tm today = *localtime(&now);

    Date currentDate;
    currentDate.day = today.tm_mday;
    currentDate.month = today.tm_mon + 1;
    currentDate.year = today.tm_year + 1900;

    return currentDate;

}

/**
 * @brief This function is responsible to tell if the acquisition date is valid 
 * by comparing to the current date.
 * @param date The acquisition date provided
 * @return 1 if is valid and 0 if not.
 */
int isValidAcquiDate(Date date) {

    Date today = getCurrentDate();

    if (date.year < today.year ||
        (date.year == today.year && date.month < today.month) ||
        (date.year == today.year && date.month == today.month && date.day <= today.day)) {
        return 1; 
    }
    
    printf("Please insert a date before or the same as %02d/%02d/%04d\n", today.day, today.month, today.year);
    return 0;
}

/**
 * @brief This function is responsible to put every received dates by chronology.
 * @param date Dates received.
 * @param size Number of requisitions.
 */
void sortDate(Requisition* date, int size) {
    int i;
    int j;
    int swapped;

    for (i = 0; i < size - 1; i++) {
        swapped = 0;
        for (j = 0; j < size - 1; j++) {
            if (compareDate(date[j].requisitionDate, date[j + 1].requisitionDate) > 0) {
                Requisition temp = date[j];
                date[j] = date[j + 1];
                date[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

/**
 * @brief This functions is responsible to compare dates.
 * @param date1 Date to be compared.
 * @param date2 Date to be compared
 * @return Negative value if date1 is before that date2. Positive value if date2 
 * is before that date1. 0 if are the same.
 */
int compareDate(Date date1, Date date2) {

    if (date1.year != date2.year) {
        return date1.year - date2.year;

    } else if (date1.month != date2.month) {
        return date1.month - date2.month;

    } else {
        return date1.day - date2.day;
    }
}

/**
 * @brief This functions determines how many days each user role has to return 
 * an item.
 * @param user User received to check the role.
 * @return 15 if is student and 30 if not
 */
int userDays(User *user) {
    if (user->role == STUDENT) {
        return 15;
    } else {
        return 30;
    }
}

/**
 * @brief This function define the due date to return an item based on the days 
 * that the user has to return.
 * @param startDate The requisition date provided.
 * @param days The days that were calculated on userDays function.
 * @return The due date.
 */
Date addDays(Date startDate, int days) {
    struct tm timeStruct = {
        .tm_year = startDate.year - 1900,
        .tm_mon = startDate.month - 1,
        .tm_mday = startDate.day + days,
        .tm_hour = 0, .tm_min = 0, .tm_sec = 0,
    };

    mktime(&timeStruct);
    return (Date){.year = timeStruct.tm_year + 1900, .month = timeStruct.tm_mon + 1, .day = timeStruct.tm_mday};

}

/**
 * @brief Checks if the return date is posterior of the due date.
 * @param currentDate Today's date.
 * @param dueDate Due date to return the item.
 * @return difference between the 2 dates.
 */
int isDatePast(Date currentDate, Date dueDate) {

    struct tm current = {
        .tm_year = currentDate.year - 1900,
        .tm_mon = currentDate.month - 1,
        .tm_mday = currentDate.day
    };

    struct tm due = {
        .tm_year = dueDate.year - 1900,
        .tm_mon = dueDate.month - 1,
        .tm_mday = dueDate.day
    };

    time_t currentTime = mktime(&current);
    time_t dueTime = mktime(&due);

    return difftime(currentTime, dueTime) > 0;

}

/**
 * @brief Compares 3 dates... checks if the requisition date is after the acquisition 
 * date and before the current date. 
 * @param acquisitionDate 
 * @param requisitionDate
 * @param currentDate
 * @return 0 if before than the acquisition date, 0 if it's after and 1 if is valid.
 */
int isRequisitionDateInRange(Date acquisitionDate, Date requisitionDate, Date currentDate) {

    if (compareDate(requisitionDate, acquisitionDate) < 0) {
        return 0; // A data de requisição é anterior à data de aquisição
    }

    if (compareDate(requisitionDate, currentDate) > 0) {
        return 0; // A data de requisição é posterior à data atual
    }

    return 1; // Data de requisição está entre a data de aquisição e a data atual
}



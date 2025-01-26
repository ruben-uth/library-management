/**
 * @file dateUsefulFunctions.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file has some functions related to dates... it's useful 
 * if we want to compare some, to do a list by chronology,  checking if it's 
 * valid by giving conditions...
 */

#ifndef DATEUSEFULFUNCTIONS_H
#define DATEUSEFULFUNCTIONS_H
#include "structs.h"

Date getCurrentDate();
int isValidAcquiDate(Date date);
void sortDate(Requisition* date, int size);
int compareDate(Date date1, Date date2);
int userDays(User *user);
Date addDays(Date startDate, int days);
int isDatePast(Date currentDate, Date dueDate);
int isRequisitionDateInRange(Date acquisition, Date requisition, Date current);

#endif /* DATEUSEFULFUNCTIONS_H */

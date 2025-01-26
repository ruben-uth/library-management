
#include "toString.h"
#include "listItems.h"
#include "data.h"
#include "input.h"
#include "structs.h"
#include "manageItems.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief This function receives the type of an item and returns the type as a 
 * string.
 * @param type Item's type.
 * @return Item's type as a string.
 */
const char* itemTypeToString(ItemType type) {
    switch (type) {
        case BOOK:
            return "Book";
        case MAGAZINE:
            return "Magazine";
        case JOURNAL:
            return "Journal";
        case DVD:
            return "DVD";
        case CD:
            return "CD";
        case OTHER:
            return "Other";
        default:
            return "Unknown Type";
    }
}

/**
 * @brief This function receives the status of an item and returns the status as a 
 * string.
 * @param status Item's status.
 * @return Item's status as a string.
 */
const char* itemStatusToString(ItemStatus status) {
    switch (status) {
        case AVAILABLE:
            return "Available";
        case CHECKED_OUT:
            return "Checked out";
        default:
            return "Unknown status";
    }
}

/**
 * @brief This function receives the role of a user and returns the role as a 
 * string.
 * @param role User's role.
 * @return User's role as a string.
 */
const char* userRoleToString(UserRole role) {
    switch (role) {
        case STUDENT:
            return "Student";
        case TEACHER:
            return "Teacher";
        case STAFF:
            return "Staff";
        default:
            return "Unknown Role";
    }
}

/**
 * @brief This function receives the status of a user and returns the status as a 
 * string.
 * @param status User's status.
 * @return User's status as a string.
 */
const char* userStatusToString(UserStatus status) {
    switch (status) {
        case ACTIVE:
            return "Active";
        case INACTIVE:
            return "Inactive";
        default:
            return "Unknown Status";
    }
}

/**
 * @brief This function receives the domain of the email and then return the 
 * domain as a string.
 * @param domain Email's domain.
 * @return Email's domain as a string.
 */
const char* emailDomainToString(EmailDomain domain) {
    switch (domain) {
        case GMAIL:
            return "@gmail.com";
        case HOTMAIL:
            return "@hotmail.com";
        case OUTLOOK:
            return "@outlook.com";
        case YAHOO:
            return "@yahoo.com";
        case ESTG:
            return "@estg.ipp.pt";
    }
}
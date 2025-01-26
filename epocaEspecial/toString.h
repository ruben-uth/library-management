/**
 * @file toString.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file contains powerful functions of manipulating the 
 * enums to strings. It's useful to print details of users or items.
 */

#ifndef TOSTRING_H
#define TOSTRING_H
#include "structs.h"

const char* itemTypeToString(ItemType type);
const char* itemStatusToString(ItemStatus status);
const char* userRoleToString(UserRole role);
const char* userStatusToString(UserStatus status);
const char* emailDomainToString(EmailDomain domain);

#endif /* TOSTRING_H */

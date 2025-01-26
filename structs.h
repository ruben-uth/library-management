/**
 * @file structs.h
 * @author Rúben Uth
 * @date 07-09-2024
 * @brief This header file contains powerful enums and structures that define 
 * how the data is going to be manipulated during the program.
 */

#ifndef STRUCTS_H
#define STRUCTS_H
#define MAX_LETTERS 40

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum {
        BOOK, MAGAZINE, JOURNAL, DVD, CD, OTHER
    } ItemType;

    typedef enum {
        AVAILABLE, CHECKED_OUT
    } ItemStatus;

    typedef enum {
        STUDENT, TEACHER, STAFF
    } UserRole;

    typedef enum {
        ACTIVE, INACTIVE
    } UserStatus;

    typedef enum {
        GMAIL, HOTMAIL, OUTLOOK, YAHOO, ESTG
    } EmailDomain;

    typedef struct {
        int day;
        int month;
        int year;
    } Date;

    typedef struct {
        int requisitionId;
        int userId;
        int returned;

        Date requisitionDate;
        Date returnDate;

        int requisitionCtr;
        UserRole role;
    } Requisition;

    typedef struct {
        int id;
        char title[MAX_LETTERS];
        ItemType type;
        Date acquisitionDate;
        ItemStatus status;

        int requisitionCtr;
        Requisition *requisitionHistory;
    } Item;

    typedef struct {
        char emailUserName[MAX_LETTERS];
        EmailDomain domain;
    } Email;
    
    typedef struct {
        int id;
        char name[MAX_LETTERS];
        Email email;

        UserRole role;
        UserStatus status;

        int activeRequisitionCtr;
        Requisition *activeRequisitions;
    } User;


    typedef struct {
        int requisitionCtr;
        Requisition *requisitionHistory;

        int itemCtr;
        Item *itemPtr;

        int userCtr;
        User *userPtr;
    } DataBase;



#ifdef __cplusplus
}
#endif

#endif /* STRUCTS_H */


#pragma once
#ifndef USER_H
#define USER_H

#include "TyreCenterHeader.h"
#include <iostream>
#include <iomanip>
#include <map>

enum class PROGRAM_PRIVILGE
{
    USER        = 0,
    EMPLOYEE    = 1,
    MANAGER     = 2,
    ADMIN       = 3
};

struct User
{
    long int userID{ 0 };
    PROGRAM_PRIVILGE userPrivilge{ PROGRAM_PRIVILGE::EMPLOYEE };
    char userName[STR_LENGTH]{ "" };
    char userPassword[STR_LENGTH]{ "" };

    static std::map<PROGRAM_PRIVILGE, std::string, std::less<PROGRAM_PRIVILGE>> privilgeLevelMap;
    static void displayTableHeaders(void);
    
    void displayTableRow(void);
};


#endif // !USER_H

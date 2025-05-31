#include "User.h"

void User::displayTableHeaders(void)
{
    std::cout
        << std::setw(5) << "ID |"
        << std::setw(20) << "username |"
        << std::setw(20) << "password |"
        << std::setw(20) << "privilge |";
};

void User::displayTableRow(void)
{
    std::cout
        << std::setw(5) << userID
        << std::setw(20) << std::string(userName).substr(0, 19)
        << std::setw(20) << std::string(userPassword).substr(0, 19)
        << std::setw(20) << privilgeLevelMap[userPrivilge];
};

std::map<PROGRAM_PRIVILGE, std::string, std::less<PROGRAM_PRIVILGE>> User::privilgeLevelMap
{
    {PROGRAM_PRIVILGE::USER,"User"},
    {PROGRAM_PRIVILGE::EMPLOYEE,"Employee"},
    {PROGRAM_PRIVILGE::MANAGER,"Manager"},
    {PROGRAM_PRIVILGE::ADMIN,"Administrator"},
};
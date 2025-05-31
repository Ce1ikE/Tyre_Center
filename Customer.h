#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "TyreCenterHeader.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>

enum class CustomerType
{
	CORP = 0, 
	PRIV
};

struct Address
{
	char country[STR_LENGTH]{""};
	char postalCode[STR_LENGTH]{ "" };
	char streetName[STR_LENGTH]{ "" };
	char houseNumber[STR_LENGTH]{ "" };
	char phoneNumber[STR_LENGTH]{ "" };
};

class Customer
{
public:
	Customer();
	Customer(CustomerType,std::string,std::string,Address);

	Customer * clone();

	void setCustomerID(long int);
	long int getCustomerID();

	void setFirstName(std::string);
	std::string getFirstName();

	void setLastName(std::string);
	std::string getLastName();

	void setAddress(Address);
	Address getAddress();

	void setCustomerType(CustomerType);
	CustomerType getCustomerType();

	void displayTableRow(void);
	void displayListItem(void);

	size_t getSize(void);

	std::vector<std::string> toString(void);
	void fromString(std::vector<std::string>);
	std::string toXML(void);
	bool write(std::ofstream&);
	bool read(std::ifstream&);

	static void displayTableHeaders(void);
	static std::vector<std::string> csvHeaders(void);
	static std::map<CustomerType, std::string, std::less<CustomerType>> customerTypeMap;

private:
	long int customerID{ 0 };
	char firstName[STR_LENGTH]{ "" };
	char lastName[STR_LENGTH]{ "" };
	Address customerAddress;
	CustomerType customerType{ CustomerType::PRIV };
};

#endif // CUSTOMER_H!


#include "Customer.h"
#include "TyreCenterHeader.h"

Customer::Customer() 
{

};

Customer::Customer(CustomerType newCustomerType, std::string newFirstName, std::string newLastName, Address newAddress)
{
	setCustomerType(newCustomerType);
	setFirstName(newFirstName);
	setLastName(newLastName);
	setAddress(newAddress);
};

Customer * Customer::clone()
{
	return new Customer(*this);
};


void Customer::setCustomerID(long int newCustomerID)
{
	customerID = newCustomerID;
};

long int Customer::getCustomerID()
{
	return customerID;
};

void Customer::setFirstName(std::string newFirstName)
{
	size_t length{ newFirstName.size() };
	length = (length < STR_LENGTH ? length : STR_LENGTH - 1);
	newFirstName.copy(firstName, length);
	firstName[length] = '\0';
};

std::string Customer::getFirstName()
{
	return std::string(firstName);
};

void Customer::setLastName(std::string newLastName)
{
	size_t length{ newLastName.size() };
	length = (length < STR_LENGTH ? length : STR_LENGTH - 1);
	newLastName.copy(lastName, length);
	lastName[length] = '\0';
};

std::string Customer::getLastName()
{
	return std::string(lastName);
};

void Customer::setAddress(Address newAddress)
{
	std::string(newAddress.country).copy(customerAddress.country, STR_LENGTH);
	std::string(newAddress.houseNumber).copy(customerAddress.houseNumber, STR_LENGTH);
	std::string(newAddress.postalCode).copy(customerAddress.postalCode, STR_LENGTH);
	std::string(newAddress.streetName).copy(customerAddress.streetName, STR_LENGTH);
	std::string(newAddress.phoneNumber).copy(customerAddress.phoneNumber, STR_LENGTH);

	customerAddress.country[STR_LENGTH - 1] = '\0'; ;
	customerAddress.houseNumber[STR_LENGTH - 1] = '\0';
	customerAddress.postalCode[STR_LENGTH - 1] = '\0';
	customerAddress.streetName[STR_LENGTH - 1] = '\0';
	customerAddress.phoneNumber[STR_LENGTH - 1] = '\0';
};

Address Customer::getAddress()
{
	return customerAddress;
};

void Customer::setCustomerType(CustomerType newCustomerType)
{
	customerType = newCustomerType;
};

CustomerType Customer::getCustomerType()
{
	return customerType;
};

void Customer::displayTableHeaders(void)
{
	std::cout << std::right 
		<< std::setw(5) << "ID |"
		<< std::setw(25) << "full name |"
		<< std::setw(10) << "type |"
		<< std::setw(15) << "country |"
		<< std::setw(15) << "postalcode |"
		<< std::setw(20) << "streetname |"
		<< std::setw(15) << "housenumber |"
		<< std::setw(15) << "phonenumber |";
};

std::vector<std::string> Customer::csvHeaders(void)
{
	std::vector<std::string> customerCSV;

	customerCSV.push_back(std::string("customerID"));
	customerCSV.push_back(std::string("customerFirstName"));
	customerCSV.push_back(std::string("customerLastName"));
	customerCSV.push_back(std::string("customerType"));
	customerCSV.push_back(std::string("customerCountry"));
	customerCSV.push_back(std::string("customerPostalCode"));
	customerCSV.push_back(std::string("customerStreetName"));
	customerCSV.push_back(std::string("customerHouseNumber"));
	customerCSV.push_back(std::string("customerPhoneNumber"));

	return customerCSV;
};

void Customer::displayTableRow(void) 
{
	std::cout 
		<< std::setw(5)  << customerID
		<< std::setw(25) << (std::string(firstName) + ' ' + std::string(lastName)).substr(0,24)
		<< std::setw(10) << customerTypeMap[customerType].substr(0,9)
		<< std::setw(15) << std::string(customerAddress.country).substr(0, 14)
		<< std::setw(15) << std::string(customerAddress.postalCode).substr(0, 9)
		<< std::setw(20) << std::string(customerAddress.streetName).substr(0, 19)
		<< std::setw(15) << std::string(customerAddress.houseNumber).substr(0, 4)
		<< std::setw(15) << std::string(customerAddress.phoneNumber).substr(0, 9);
};

void Customer::displayListItem(void) 
{
	std::cout 
		<< std::setw(15) << "firstname:" << firstName
		<< std::setw(15) << "lastname:" << lastName;
	if (customerType == CustomerType::CORP)
	{
		std::cout << std::setw(15) << "type:" << "corporate";
	}
	else
	{
		std::cout << std::setw(15) << "type:" << "private";
	}
	std::cout 
		<< std::setw(15) << "country:" << customerAddress.country
		<< std::setw(15) << "postalcode:" << customerAddress.postalCode
		<< std::setw(15) << "streetname:" << customerAddress.streetName
		<< std::setw(15) << "housenumber:" << customerAddress.houseNumber
		<< std::setw(15) << "phonenumber:" << customerAddress.phoneNumber;
};

size_t Customer::getSize(void)
{
	return sizeof(long int) + sizeof(char[STR_LENGTH]) + sizeof(char[STR_LENGTH]) + sizeof(Address) + sizeof(int);
};

std::vector<std::string> Customer::toString(void)
{
	std::vector<std::string> customer_V;
	customer_V.reserve(9);
	customer_V.push_back(std::to_string(customerID));
	customer_V.push_back(std::string(firstName));
	customer_V.push_back(std::string(lastName));
	customer_V.push_back(Customer::customerTypeMap[customerType]);
	customer_V.push_back(std::string(customerAddress.country));
	customer_V.push_back(std::string(customerAddress.postalCode));
	customer_V.push_back(std::string(customerAddress.streetName));
	customer_V.push_back(std::string(customerAddress.houseNumber));
	customer_V.push_back(std::string(customerAddress.phoneNumber));

	return customer_V;
};

std::string Customer::toXML(void)
{
	std::string customer_XML;
	std::vector<std::string> customer_V{ toString() };

	if (customer_V.size() != 9)
	{
		return customer_XML;
	}

	customer_XML = std::string(CUSTOMER_TO_XML(customer_V));

	return customer_XML;
};

bool Customer::write(std::ofstream& outStream)
{
	int customer_T{ static_cast<int>(customerType) };
	outStream.write(reinterpret_cast<const char*>(&customerID), sizeof(long int));
	outStream.write(reinterpret_cast<const char*>(&firstName), sizeof(char[STR_LENGTH]));
	outStream.write(reinterpret_cast<const char*>(&lastName), sizeof(char[STR_LENGTH]));
	outStream.write(reinterpret_cast<const char*>(&customerAddress), sizeof(Address));
	outStream.write(reinterpret_cast<const char*>(&customer_T), sizeof(int));
	if (outStream.good() == false)
	{
		return false;
	}
	return true;
};

bool Customer::read(std::ifstream& inStream)
{
	int customer_T{ 0 };
	inStream.read(reinterpret_cast<char*>(&customerID), sizeof(long int));
	inStream.read(reinterpret_cast<char*>(&firstName), sizeof(char[STR_LENGTH]));
	inStream.read(reinterpret_cast<char*>(&lastName), sizeof(char[STR_LENGTH]));
	inStream.read(reinterpret_cast<char*>(&customerAddress), sizeof(Address));
	inStream.read(reinterpret_cast<char*>(&customer_T), sizeof(int));
	customerType = static_cast<CustomerType>(customer_T);
	
	return true;
};

void Customer::fromString(std::vector<std::string> customer_V)
{
	setCustomerID(std::stoi(customer_V.at(0)));
	setFirstName(customer_V.at(1));
	setLastName(customer_V.at(2));
 
	auto result = std::find_if(
		Customer::customerTypeMap.begin(), 
		Customer::customerTypeMap.end(), 
		[&customer_V](const std::pair<CustomerType, std::string>& pair) { 
			return pair.second == customer_V.at(3); 
		});

	if (result  != Customer::customerTypeMap.end())
	{
		setCustomerType(result->first);
	}

	Address newCustomerAdd;
	
	customer_V.at(4).copy(newCustomerAdd.country, STR_LENGTH);
	customer_V.at(5).copy(newCustomerAdd.houseNumber, STR_LENGTH);
	customer_V.at(6).copy(newCustomerAdd.postalCode, STR_LENGTH);
	customer_V.at(7).copy(newCustomerAdd.streetName, STR_LENGTH);
	customer_V.at(8).copy(newCustomerAdd.phoneNumber, STR_LENGTH);

	setAddress(newCustomerAdd);
};

std::map<CustomerType, std::string, std::less<CustomerType>> Customer::customerTypeMap
{
	{CustomerType::CORP, std::string("Corporate")},
	{CustomerType::PRIV, std::string("Private")}
};

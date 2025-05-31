#pragma once
#ifndef TYRECENTER_FUNCTIONS

/* Headers *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <ctime>
#include <sstream>
#include <random>
#include "Menu.h"
#include "Controller.h"

/* Enum's *////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum class FILTER_FLAG_CUSTOMER
{
	GET_NO_NEW_LIST = 0,
	GET_NEW_LIST = 1
};

enum class FILTER_FLAG_PRODUCT
{
	GET_NO_NEW_LIST = 0,
	GET_NEW_LIST = 1
};

/* Function declarations */////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hello_World(void);
void Bye_Message(void);

void cursor(void);
void line(int, char);

void sendErrorMessage(int);

void addDumyData(Controller&);

bool prepareProgram(Controller&);
bool checkIDFile(std::ifstream&, Controller&);
bool checkEmployeeFile(std::ifstream&, Controller&);
bool checkCustomerFile(std::ifstream&, Controller&);
bool checkProductFile(std::ifstream&, Controller&);
bool checkInvoiceFile(std::ifstream&, Controller&);
bool checkDiscountFile(std::ifstream&, Controller&);
bool readCustomerFile(std::ifstream&, Controller&);
bool readProductFile(std::ifstream&, Controller&);
bool readInvoiceFile(std::ifstream&, Controller&);
bool readDiscountFile(std::ifstream&, Controller&);

bool loadData(Controller&);

// template functions
template <typename T>
bool showList(std::vector<T*>& list)
{
	std::default_random_engine engine(time(0));
	std::uniform_int_distribution<int> reandomColor{ 20,230 };
	std::cout << "\033[38;5;" + std::to_string(reandomColor(engine)) + "m";

	line(120, '-');
	T::displayTableHeaders();
	line(120, '-');

	for (int i = 0; i < list.size(); ++i)
	{
		list[i]->displayTableRow();
		std::cout << "\n";
	}
	line(120, '-');

	std::cout << RESET_COLOR << std::left << std::endl;

	return true;
};

template <typename T>
bool showList(std::vector<T>& list)
{
	std::default_random_engine engine(time(0));
	std::uniform_int_distribution<int> reandomColor{ 20,230 };
	std::cout << "\033[38;5;" + std::to_string(reandomColor(engine)) + "m";

	line(120, '-');
	T::displayTableHeaders();
	line(120, '-');

	for (int i = 0; i < list.size(); ++i)
	{
		list[i].displayTableRow();
		std::cout << "\n";
	}
	line(120, '-');

	std::cout << RESET_COLOR << std::left << std::endl;

	return true;
};

// i actually noticed that when i wrote "writeCSV" and "writeTXT" that they look quite similar
// but of course the major difference is the leading line which are the column headers
template <typename T>
bool writeCSV(std::ofstream& outputFile, const std::vector<std::string>& csvHeaders, const std::vector<T*>& csvData)
{
	std::vector<std::string> string_V;
	std::ostream_iterator<std::string> fileIterator{ outputFile,"," };
	std::copy(csvHeaders.begin(), csvHeaders.end(), fileIterator);
	outputFile << "\n";
	for (T* csvLine : csvData)
	{
		string_V = csvLine->toString();
		std::copy(string_V.begin(), string_V.end(), fileIterator);
		outputFile << "\n";
	}

	return true;
};

template <typename T>
bool writeTXT(std::ofstream& outputFile, const std::vector<T*>& txtData)
{
	std::string userInput;

	std::vector<std::string> string_V;
	std::ostream_iterator<std::string> fileIterator{ outputFile," " };
	for (T* txtLine : txtData)
	{
		string_V = txtLine->toString();
		std::copy(string_V.begin(), string_V.end(), fileIterator);
		outputFile << "\n";
	}

	return true;
};

template <typename T>
bool writeXML(std::ofstream& outputFile, const std::vector<T*>& xmlData)
{
	for (T * xmlElement : xmlData)
	{
		outputFile << xmlElement->toXML();
	}
	return true;
};

template <typename T>
bool readCSV(std::ifstream& csvFile, std::vector<T*>& dataContainer)
{
	std::vector<std::string> csvLine;
	std::string row;
	std::string column;
	T* data{};
	// first line contains only column names
	if (!std::getline(csvFile, row, '\n'))
	{
		return false;
	}
	// writing my data to a CSV file is quite simple but it becomes a little trickier when
	// reading from a file since i also have to seperate each line and column
	while (std::getline(csvFile, row,'\n'))
	{
		std::istringstream rowStream( row );
		while (std::getline(rowStream, column,','))
		{
			csvLine.push_back(column);
		}
		data->fromString(csvLine);
		dataContainer.push_back(data);

		csvLine.clear();
	}
	return true;
};

template <typename T>
bool readTXT(std::ifstream& inputFile, std::vector<T*>& dataContainer)
{
	std::vector<std::string> txtLine;
	std::string row;
	std::string column;
	T* data{};
	while (std::getline(inputFile, row,'\n'))
	{
		std::istringstream rowStream( row );
		while (std::getline(inputFile, column, ' '))
		{
			txtLine.push_back(column);
		}
		data->fromString(txtLine);
		dataContainer.push_back(data);

		txtLine.clear();
	}
	return true;
};

// Input functions
bool verifyEmployeeCredentials(Controller&);
bool verifyNumericInput(std::string&);
bool verifyAlphaInput(std::string&);
// Input functions (overloaded)
int	input(int, int);
std::string input(std::string, std::string);
std::string input(std::string, std::string, std::string);

// Handle functions
void handleLoginMenuRequest(Menu&, Controller&);
void handleMainMenuRequest(Menu&, Controller&);
void handleCustomersMenuRequest(Menu&, Controller&);
void handleProductsMenuRequest(Menu&, Controller&);
void handleInvoiceMenuRequest(Menu&, Controller&);
void handleDiscountMenuRequest(Menu&, Controller&);
void handleAccountMenuRequest(Menu&, Controller&);

// Product functions
bool saveProductsToBin(std::vector<Product*>&);
bool saveProducts(Controller&);
bool addProduct(Controller&);
bool deleteProduct(Controller&);
bool updateProduct(Controller&);
bool searchProduct(std::vector<Product*>&, long int&);
bool filterProducts(ProductMenuRequest, std::vector<Product*>&);
bool filterProducts(ProductMenuRequest, std::vector<Product*>&, std::vector<Product*>&);
bool handleUserInput(ProductMenuRequest, std::string&);
bool orderProducts(ProductMenuRequest, std::vector<Product*>&);

// Customer functions
bool saveCustomersToBin(std::vector<Customer*>&);
bool saveCustomers(Controller&);
bool addCustomer(Controller&);
bool deleteCustomer(Controller&);
bool updateCustomer(Controller&);
bool searchCustomer(Controller&, long int&);
bool filterCustomers(CustomerMenuRequest,std::vector<Customer*>&);
bool filterCustomers(CustomerMenuRequest,std::vector<Customer*>&, std::vector<Customer*>&);
bool handleUserInput(CustomerMenuRequest, std::string&);
bool orderCustomers(CustomerMenuRequest, std::vector<Customer*>&);

// Invoice functions
bool savePendingInvoicesToBin(std::vector<Invoice*>&);
bool saveInvoices(Controller&);
bool displayPendingInvoice(Controller&);
bool searchHandledInvoices(Controller&);
bool searchPendingInvoices(Controller&, long int&);
bool searchPendingInvoices(Controller&);
bool addProductToInvoice(Controller&);
bool removeProductFromInvoice(Controller&);
bool addInvoice(Controller&);
bool deleteInvoice(Controller&);
bool processInvoice(Controller&);
bool manipulateHandledInvoice(Controller&,Invoice&);
bool handleUseCase(Controller&, std::ifstream&, int&, int&, size_t&, size_t&);

// Discount functions
bool saveDiscounts(Controller&);
bool showCurrentDiscounts(Controller&);
bool showMatchingTable(Controller&);
bool changeDiscount(Controller&);
bool changeDiscountConditions(Controller&);

// Account functions
bool saveAccounts(Controller&);
bool addAccount(Controller&);
bool deleteAccount(Controller&);
bool updateAccount(Controller&);

#endif // !TYRECENTER_FUNCTIONS


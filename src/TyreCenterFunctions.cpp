#include "../headers/Menu.h"
#include "../headers/User.h"
#include "../headers/Controller.h"
#include "../headers/TyreCenterHeader.h"
#include "../headers/TyreCenterFunctions.h"

#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <functional>

/*
 [10;30] file handling error
	10: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new handled invoice file could not be created\""
	11: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new ID file could not be created\""
	12: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new employee file could not be created\""
	13: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new employee file created but writing error occured\""
	14: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new customer file could not be created\""
	15: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new product file could not be created\""
	16: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new pending invoice file could not be created\""
	17: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new discount file could not be created\""
	18: -> "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new discount file created but writing error occured\""
	19: -> "COULD NOT PROPERLY OPEN FILE \"" << EMPLOYEES_BIN_FILE << "\""
	20: -> "COULD NOT PROPERLY WRITE TO FILE -> \"bad writing to " << CUSTOMERS_BIN_FILE << "\""
	21: -> "COULD NOT PROPERLY WRITE TO FILE -> \"bad writing to " << PRODUCTS_BIN_FILE << "\""
	22: -> "COULD NOT PROPERLY WRITE TO FILE -> \"bad writing to " << INVOICES_P_BIN_FILE << "\""
	23: -> "COULD NOT PROPERLY WRITE TO FILE -> \"bad writing to " << INVOICES_H_BIN_FILE << "\""

 [31;50] etc..
*/
void sendErrorMessage(int errorCode)
{
	std::cout << RED;
	switch (errorCode)
	{
	case 10: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new handled invoice file could not be created\""; break;
	case 11: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new ID file could not be created\""; break;
	case 12: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new employee file could not be created\""; break;
	case 13: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new employee file created but writing error occured\""; break;
	case 14: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new customer file could not be created\""; break;
	case 15: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new product file could not be created\""; break;
	case 16: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new pending invoice file could not be created\""; break;
	case 17: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new discount file could not be created\""; break;
	case 18: std::cout << "COULD NOT PROPERLY START THE PROGRAM: ERROR -> \"new discount file created but writing error occured\""; break;
	case 19: std::cout << "COULD NOT PROPERLY OPEN FILE \"" << EMPLOYEES_BIN_FILE << "\""; break;
	case 20: std::cout << "COULD NOT PROPERLY WRITE TO FILE -> \"bad writing to " << CUSTOMERS_BIN_FILE << "\""; break;
	case 21: std::cout << "COULD NOT PROPERLY WRITE TO FILE -> \"bad writing to " << PRODUCTS_BIN_FILE << "\""; break;
	case 22: std::cout << "COULD NOT PROPERLY WRITE TO FILE -> \"bad writing to " << INVOICES_P_BIN_FILE << "\""; break;
	case 23: std::cout << "COULD NOT PROPERLY WRITE TO FILE -> \"bad writing to " << INVOICES_H_BIN_FILE << "\""; break;
	default:
		std::cout << "! default error code !";
		break;
	}
	std::cout << RESET_COLOR;
	exit(-1);
};

void cursor(void)
{
	std::cout << TURQUOISE << "-> " << RESET_COLOR;
};

void line(int length, char letter)
{
	std::cout << "\n";
	char lineCharacter[2]{ letter };
	for (int i = 0; i < length; i++)
	{
		std::cout << lineCharacter;
	}
	std::cout << "\n";
};
// https://cplusplus.com/reference/algorithm/
// https://cplusplus.com/reference/cctype/isdigit/
// https://cplusplus.com/reference/cctype/isalpha/
bool verifyNumericInput(std::string& input)
{
	return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
};

bool verifyAlphaInput(std::string& input)
{
	return !input.empty() && std::all_of(input.begin(), input.end(), ::isalpha);
};

bool prepareProgram(Controller& programController)
{
	std::ifstream idFile{ ID_BIN_FILE, std::ios::binary | std::ios::in };
	std::ifstream employeeFile{EMPLOYEES_BIN_FILE,std::ios::binary | std::ios::in };
	std::ifstream customerFile{ CUSTOMERS_BIN_FILE,std::ios::binary | std::ios::in };
	std::ifstream productFile{ PRODUCTS_BIN_FILE,std::ios::binary | std::ios::in };
	std::ifstream invoiceFilePending{ INVOICES_P_BIN_FILE,std::ios::binary | std::ios::in };
	std::ifstream invoiceFileHandled{ INVOICES_H_BIN_FILE,std::ios::binary | std::ios::in };
	std::ifstream discountFile{ DISCOUNTS_BIN_FILE,std::ios::binary | std::ios::in };

	if (!invoiceFileHandled)
	{
		std::ofstream newInvoiceFileHandled{ INVOICES_H_BIN_FILE,std::ios::binary | std::ios::out };
		if (!newInvoiceFileHandled)
		{
			sendErrorMessage(10);
		}
	}

	checkIDFile(idFile, programController);
	checkEmployeeFile(employeeFile, programController);
	checkCustomerFile(customerFile, programController);
	checkProductFile(productFile, programController);
	checkInvoiceFile(invoiceFilePending, programController);
	checkDiscountFile(discountFile, programController);

	idFile.close();
	employeeFile.close();
	customerFile.close();
	productFile.close();
	invoiceFilePending.close();
	discountFile.close();
	invoiceFileHandled.close();

	return true;
};

bool checkEmployeeFile(std::ifstream& employeeFile, Controller& programController)
{
	if (employeeFile)
	{
		return true;
	}

	User newUser;
	std::string username;
	std::string password;
	std::ofstream newEmployeeFile{ EMPLOYEES_BIN_FILE,std::ios::binary | std::ios::out };

	if (!newEmployeeFile)
	{
		sendErrorMessage(12);
	}

	std::cout << RED << "\n\t! NEW CREATED ACCOUNT HAS MANAGER PRIVILGES !\n" << RESET_COLOR;
	std::cout << "Enter new account's username [max 40 characters]: ";

	do
	{
		cursor();
		std::cin >> username;
	} while (40 < username.size());

	std::cout << "Enter account's password [max 40 characters]: ";
	do
	{
		cursor();
		std::cin >> password;
	} while (40 < password.size());

	
	username.copy(newUser.userName, STR_LENGTH);
	password.copy(newUser.userPassword, STR_LENGTH);

	newUser.userPrivilge = PROGRAM_PRIVILGE::MANAGER;
	newUser.userName[STR_LENGTH - 1] = '\0';
	newUser.userPassword[STR_LENGTH - 1] = '\0';

	programController.setUser(newUser);

	newEmployeeFile.seekp(0);
	newEmployeeFile.write(reinterpret_cast<const char*>(&newUser), sizeof(User));


	// afterwards i check if writing was done correctly
	if (newEmployeeFile.good() == false)
	{
		sendErrorMessage(13);
	}
	// and of course inform the user
	std::cout << HOME_CURSOR << WIPE_SCREEN;
	std::cout << GREEN << "\n\tNEW ACCOUNT CREATED\n";

	newEmployeeFile.close();
	
	return true;
}

bool checkIDFile(std::ifstream& idFile, Controller& programController)
{
	long int newCustomerID{ 1 };
	long int newProductID{ 1 };
	long int newInvoiceID{ 1 };
	long int newUserID{ 1 };

	if (!idFile)
	{
		std::ofstream newIdFile{ ID_BIN_FILE, std::ios::binary | std::ios::out };

		if (!newIdFile)
		{
			sendErrorMessage(11);
		}

		newCustomerID = 1;
		newProductID = 1;
		newInvoiceID = 1;
		newUserID = 1;

		programController.setCurrentCustomerID(newCustomerID);
		programController.setCurrentProductID(newProductID);
		programController.setCurrentInvoiceID(newInvoiceID);
		programController.setCurrentUserID(newUserID);

		programController.writeID(newIdFile);
		
		newIdFile.close();

		return true;
	}

	idFile.seekg(0);
	programController.readID(idFile);
	return true;
};

bool loadData(Controller& programController)
{
	std::string userInput;
	int userChoice{ 0 };
	std::vector<Product*> newProductList;
	std::vector<Customer*> newCustomerList;

	std::ifstream productFile;
	std::ifstream customerFile;

	std::cout
		<< VIOLET
		<< "1 |--> load Customer Data\n"
		<< "2 |--> load Product Data\n"
		<< "5 |<-- Back to Main Menu\n"
		<< RESET_COLOR;
	
	userChoice = input(1, 5);

	switch (userChoice)
	{
	case 1:
		productFile.open(PRODUCTS_CSV_FILE, std::ios::in);
		readCSV(productFile, newProductList);
		productFile.close();
		break;
	case 2:
		customerFile.open(PRODUCTS_CSV_FILE, std::ios::in);
		readCSV(customerFile, newCustomerList);
		customerFile.close();
		break;
	default:
		break;
	}

	return true;
};

int input(int lowerLimit = 1, int upperLimit = 2)
{
	// this a general purpose function to check user input 
	// in a very straight forward way (nothing to fancy)

	std::string userInput;
	int userChoice{ 0 };

	do
	{
		cursor();
		std::cin >> userInput;
		
		if (!verifyNumericInput(userInput))
		{
			std::cout << RED << "\n\tINVALID OPTION\n" << RESET_COLOR;
			userChoice = 0;
		}
		else
		{
			userChoice = std::stoi(userInput);
		}

	} while (userChoice < lowerLimit || upperLimit < userChoice);

	return userChoice;
};

std::string input(std::string firstChoice, std::string secondChoice)
{
	std::string userInput;
	do
	{
		cursor();
		std::cin >> userInput;
	} while (userInput != firstChoice && userInput != secondChoice);

	return userInput;
};

std::string input(std::string firstChoice, std::string secondChoice, std::string thirdChoice)
{
	std::string userInput;
	do
	{
		cursor();
		std::cin >> userInput;
	} while (userInput != firstChoice && userInput != secondChoice && userInput != thirdChoice);

	return userInput;
};

//	 __                            __                   ______                                  __      __                               
//	/  |                          /  |                 /      \                                /  |    /  |                              
//	$$ |        ______    ______  $$/  _______        /$$$$$$  |__    __  _______    _______  _$$ |_   $$/   ______   _______    _______ 
//	$$ |       /      \  /      \ /  |/       \       $$ |_ $$//  |  /  |/       \  /       |/ $$   |  /  | /      \ /       \  /       |
//	$$ |      /$$$$$$  |/$$$$$$  |$$ |$$$$$$$  |      $$   |   $$ |  $$ |$$$$$$$  |/$$$$$$$/ $$$$$$/   $$ |/$$$$$$  |$$$$$$$  |/$$$$$$$/ 
//	$$ |      $$ |  $$ |$$ |  $$ |$$ |$$ |  $$ |      $$$$/    $$ |  $$ |$$ |  $$ |$$ |        $$ | __ $$ |$$ |  $$ |$$ |  $$ |$$      \ 
//	$$ |_____ $$ \__$$ |$$ \__$$ |$$ |$$ |  $$ |      $$ |     $$ \__$$ |$$ |  $$ |$$ \_____   $$ |/  |$$ |$$ \__$$ |$$ |  $$ | $$$$$$  |
//	$$       |$$    $$/ $$    $$ |$$ |$$ |  $$ |      $$ |     $$    $$/ $$ |  $$ |$$       |  $$  $$/ $$ |$$    $$/ $$ |  $$ |/     $$/ 
//	$$$$$$$$/  $$$$$$/   $$$$$$$ |$$/ $$/   $$/       $$/       $$$$$$/  $$/   $$/  $$$$$$$/    $$$$/  $$/  $$$$$$/  $$/   $$/ $$$$$$$/  
//	                    /  \__$$ |                                                                                                       
//	                    $$    $$/                                                                                                        
//	                     $$$$$$/                                                                                                         

bool verifyEmployeeCredentials(Controller& programController)
{
	User user,userFromFile;
	bool match{ false };
	int privilgeUser{ 0 };
	
	std::string userInput;
	std::ifstream employeeFile{ EMPLOYEES_BIN_FILE , std::ios::binary | std::ios::in };

	if (!employeeFile)
	{
		sendErrorMessage(19);
	}

	employeeFile.seekg(0);

	std::cout << "Username: ";
	cursor();
	std::cin >> userInput;
	userInput.copy(user.userName, STR_LENGTH);
	user.userName[STR_LENGTH - 1] = '\0';

	std::cout << "Password: ";
	cursor();
	std::cin >> userInput;
	userInput.copy(user.userPassword, STR_LENGTH);
	user.userPassword[STR_LENGTH - 1] = '\0';

	while (employeeFile.eof() == false && match == false)
	{
		employeeFile.read(reinterpret_cast<char*>(&userFromFile), sizeof(User));

		if (std::strcmp(userFromFile.userPassword, user.userPassword) == 0 && std::strcmp(userFromFile.userName,user.userName) == 0)
		{
			user.userPrivilge = userFromFile.userPrivilge;
			user.userID = userFromFile.userID;
			match = true;
		}
	};

	employeeFile.close();

	if (match)
	{
		programController.setCurrentUser(user);
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		std::cout << GREEN << "\nWELCOME " << user.userName << "\n" << RESET_COLOR;
		return true;
	}

	std::cout << RED << "\nNO RECORD FOUND\n" << RESET_COLOR;
	return false;
};

//   _______                            __                        __             ______                                  __      __                               
//  /       \                          /  |                      /  |           /      \                                /  |    /  |                              
//  $$$$$$$  | ______    ______    ____$$ | __    __   _______  _$$ |_         /$$$$$$  |__    __  _______    _______  _$$ |_   $$/   ______   _______    _______ 
//  $$ |__$$ |/      \  /      \  /    $$ |/  |  /  | /       |/ $$   |        $$ |_ $$//  |  /  |/       \  /       |/ $$   |  /  | /      \ /       \  /       |
//  $$    $$//$$$$$$  |/$$$$$$  |/$$$$$$$ |$$ |  $$ |/$$$$$$$/ $$$$$$/         $$   |   $$ |  $$ |$$$$$$$  |/$$$$$$$/ $$$$$$/   $$ |/$$$$$$  |$$$$$$$  |/$$$$$$$/ 
//  $$$$$$$/ $$ |  $$/ $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |        $$ | __       $$$$/    $$ |  $$ |$$ |  $$ |$$ |        $$ | __ $$ |$$ |  $$ |$$ |  $$ |$$      \ 
//  $$ |     $$ |      $$ \__$$ |$$ \__$$ |$$ \__$$ |$$ \_____   $$ |/  |      $$ |     $$ \__$$ |$$ |  $$ |$$ \_____   $$ |/  |$$ |$$ \__$$ |$$ |  $$ | $$$$$$  |
//  $$ |     $$ |      $$    $$/ $$    $$ |$$    $$/ $$       |  $$  $$/       $$ |     $$    $$/ $$ |  $$ |$$       |  $$  $$/ $$ |$$    $$/ $$ |  $$ |/     $$/ 
//  $$/      $$/        $$$$$$/   $$$$$$$/  $$$$$$/   $$$$$$$/    $$$$/        $$/       $$$$$$/  $$/   $$/  $$$$$$$/    $$$$/  $$/  $$$$$$/  $$/   $$/ $$$$$$$/  

bool saveProductsToBin(std::vector<Product*>& productList)
{
	std::ofstream productFile;
	std::ofstream tempFile{ "temp.bin" ,std::ios::binary | std::ios::trunc | std::ios::out };
	// to be certain copy the file contents to a temporary file
	// "rdbuf" returns a pointer to the stream buffer. The reason i need this is because a 
	// "fstream" objects are only overloaded only with a other "fstream" object with their stream buffer 
	for (Product* productInList : productList)
	{
		if (!productInList->write(tempFile))
		{
			tempFile.close();
			std::remove("temp.bin");
			std::cout << RED << "\n\tSOMETHING OCCURED : WRITING ERROR TO TEMPORARY FILE FAILED\n" << RESET_COLOR;
			return false;
		}
	}
	tempFile.close();

	std::ifstream tempFileInput("temp.bin", std::ios::binary | std::ios::in);
	productFile.open(PRODUCTS_BIN_FILE, std::ios::binary | std::ios::out);
	if (!productFile)
	{
		tempFileInput.close();
		productFile.close();
		std::cout << RED << "\n\tSOMETHING OCCURED : PRODUCT DELETED BUT COULD NOT OPEN BINARY FILE\n" << PRODUCTS_BIN_FILE << RESET_COLOR;
		return false;
	}
	
	productFile << tempFileInput.rdbuf();

	tempFileInput.close();
	productFile.close();
	std::remove("temp.bin");
	return true;
};

bool saveProducts(Controller& programController)
{
	std::ofstream productFile;
	std::string userInput;
	std::vector<Product*> productList = programController.getProductListReference();
	std::vector<Product*> productFilteredList;
	std::ostream_iterator<std::string> productFileIterator{ productFile,"," };

	int userChoice;

	
	std::cout
		<< VIOLET
		<< "save products\n"
		<< "1 |--> save as BIN\n"
		<< "2 |--> save as CSV\n"
		<< "3 |--> save as TXT\n"
		<< "4 |--> save as XML\n"
		<< "5 |--> Back to Product Menu\n"
		<< RESET_COLOR;
	
	userChoice = input(1, 5);

	switch (userChoice)
	{
	case 1:
		saveProductsToBin(productList);
		break;
	case 2:
		productFile.open(PRODUCTS_CSV_FILE, std::ios::out);

		std::cout
			<< VIOLET
			<< "create CSV file for\n"
			<< "1 |--> Tyres\n"
			<< "2 |--> Rims\n"
			<< "3 |--> Back to Product Menu\n"
			<< RESET_COLOR;
		
		userChoice = input(1, 3);

		switch (userChoice)
		{
		case 1:
			filterProducts(ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE, productList, productFilteredList);
			writeCSV(productFile, Tyre::csvHeaders(), productFilteredList);
			break;
		case 2:
			filterProducts(ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM, productList, productFilteredList);
			writeCSV(productFile, Rim::csvHeaders(), productFilteredList);
			break;
		case 3:
			break;
		default:
			break;
		}
		productFile.close();
		break;
	case 3:
		productFile.open(PRODUCTS_TXT_FILE, std::ios::out);
		writeTXT(productFile, productList);
		productFile.close();
		break;
	case 4:
		productFile.open(PRODUCTS_XML_FILE, std::ios::out);
		productFile << _START_XML;
		productFile << _START_PRODUCT_LIST_XML;
		writeXML(productFile, productList);
		productFile << _STOP_PRODUCT_LIST_XML;
		productFile.close();
		break;
	default:
		break;
	}
	
	
	return true;
};

bool checkProductFile(std::ifstream& productFile, Controller& programController)
{
	if (!productFile)
	{
		std::ofstream newProductFile{ PRODUCTS_BIN_FILE,std::ios::binary | std::ios::out };
		if (!newProductFile)
		{
			sendErrorMessage(15);
		}
		newProductFile.close();
		return true;
	}
	readProductFile(productFile, programController);
	return true;
};

bool readProductFile(std::ifstream& productFile, Controller& programController)
{
	productFile.seekg(0,std::ios::end);
	size_t length = productFile.tellg();
	productFile.seekg(0);

	if (length == 0)
	{
		return false;
	}

	long int productFromFile_ID{ 0 };
	int productFromFile_Type{ 0 };
	Tyre tyreProductFromFile{};
	Rim rimProductFromFile{};
	size_t byteCounter{ 0 };
	while (productFile)
	{
		// i have to first pass the productID and then read the product type
		productFile.seekg(byteCounter, std::ios::beg);
		productFile.read(reinterpret_cast<char*>(&productFromFile_ID), sizeof(long int));
		productFile.read(reinterpret_cast<char*>(&productFromFile_Type), sizeof(int));
		productFile.seekg(byteCounter, std::ios::beg);

		switch (static_cast<ProductType>(productFromFile_Type))
		{
		case ProductType::Tyre:
			tyreProductFromFile.read(productFile);
			byteCounter += tyreProductFromFile.getSize();
			programController.setProduct(&tyreProductFromFile);
			break;
		case ProductType::Rim:
			rimProductFromFile.read(productFile);
			byteCounter += rimProductFromFile.getSize();
			programController.setProduct(&rimProductFromFile);
			break;
		default:
			break;
		}
	}
	return true;
};

bool addProduct(Controller& programController)
{
	int userChoice{ 0 }, userFlow{ 0 };
	bool nextCase{ false };

	std::string userInput;
	Product* newProduct{};
	Rim* newRim{};
	Tyre* newTyre{};
	ProductType newProductType{};
	
	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		switch (userFlow)
		{
		case 0:
			std::cout << "Add new product" << PINK << " [tyre product (t) , rim product (r)]\n" << RESET_COLOR;

			if ("t" == userInput)
			{
				newProduct->setType(ProductType::Tyre);
				nextCase = true;
			}

			if ("r" == userInput)
			{
				newProduct->setType(ProductType::Rim);
				nextCase = true;
			}

			break;
		case 1:
			std::cout << "Enter the product's name " << RED << " [min " << PRODUCT_NAME_MIN_LEN << " characters]: \n" << RESET_COLOR;

			if (PRODUCT_NAME_MIN_LEN <= userInput.size())
			{
				newProduct->setName(userInput);
				nextCase = true;
			}

			break;
		case 2:
			std::cout << "Enter the product's manufacturer " << RED << " [min " << PRODUCT_MANUFACTURER_MIN_LEN << " characters]: \n" << RESET_COLOR;

			if (PRODUCT_MANUFACTURER_MIN_LEN <= userInput.size())
			{
				newProduct->setManufacturer(userInput);
				nextCase = true;
			}

			break;
		case 3:
			std::cout << "Enter the product's diameter " << RED << " [min " << PRODUCT_DIAMETER_MIN_LEN << " number]: \n" << RESET_COLOR;

			if (PRODUCT_DIAMETER_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				newProduct->setDiameter(std::stoi(userInput));
				nextCase = true;
			}

			break;
		case 4:
			std::cout << "Enter the product's price " << RED << " [min " << PRODUCT_PRICE_MIN_LEN << " number]: \n" << RESET_COLOR;

			if (PRODUCT_PRICE_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				newProduct->setPrice(std::stoi(userInput));
				nextCase = true;
			}

			break;
		case 5:
			std::cout << "Enter the product's quantity " << RED << " [min " << PRODUCT_QUANTITY_MIN_LEN << " number]: \n" << RESET_COLOR;

			if (PRODUCT_QUANTITY_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				newProduct->setQuantity(std::stoi(userInput));
				nextCase = true;
			}

			break;
		case 6:
			std::cout << "Enter the product's width " << RED << " [min " << PRODUCT_WIDTH_MIN_LEN << " numbers]: \n" << RESET_COLOR;

			if (PRODUCT_WIDTH_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				newProduct->setWidth(std::stoi(userInput));
				nextCase = true;

				if (newProduct->getType() == ProductType::Rim)
				{
					newRim = dynamic_cast<Rim*>(newProduct);
				}
				else
				{
					newTyre = dynamic_cast<Tyre*>(newProduct);
				}
			}

			break;
		case 7:
			if (newProduct->getType() == ProductType::Rim)
			{
				std::cout << "Enter the product's color " << RED << " [min " << PRODUCT_COLOR_MIN_LEN << " characters]: \n" << RESET_COLOR;

				if (PRODUCT_COLOR_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
				{
					newRim->setColor(userInput);
					nextCase = true;
				}
			}
			else
			{
				nextCase = true;
			}
			break;
		case 8:
			if (newProduct->getType() == ProductType::Rim)
			{
				std::cout << "Enter the product's rim Material " << PINK << " [1: STEEL , 2: ALUMINIUM]:\n" << RESET_COLOR;

				if (verifyNumericInput(userInput) && ("2" == userInput || "1" == userInput))
				{
					newRim->setRimMaterial(static_cast<RimMaterial>(std::stoi(userInput)));
					nextCase = true;
				}
			}
			else
			{
				nextCase = true;
			}
			break;
		case 9:			
			if (newProduct->getType() == ProductType::Tyre)
			{
				std::cout << "Enter the product's height " << RED << " [min " << PRODUCT_HEIGHT_MIN_LEN << " number]: \n" << RESET_COLOR;
				if (PRODUCT_HEIGHT_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
				{
					newTyre->setHeight(std::stoi(userInput));
					nextCase = true;
				}
			}
			else
			{
				nextCase = true;
			}
			break;
		case 10:
			if (newProduct->getType() == ProductType::Tyre)
			{
				std::cout << "Enter the product's tyre markings " << RED << " [min " << PRODUCT_MARKINGS_MIN_LEN << " number]: \n" << RESET_COLOR;
				if (PRODUCT_MARKINGS_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
				{
					newTyre->setTyreMarkings(userInput);
					nextCase = true;
				}
			}
			else
			{
				nextCase = true;
			}
			break;
		case 11:
			if (newProduct->getType() == ProductType::Tyre)
			{
				std::cout << "Enter the product's speed index:\n";
				for (std::pair<SpeedIndex, std::string> mapItem : Tyre::speedIndexMap)
				{
					std::cout << static_cast<int>(mapItem.first) << " -> " << mapItem.second;
				}

				if (verifyNumericInput(userInput) && 0 <= std::stoi(userInput) && std::stoi(userInput) <= Tyre::speedIndexMap.size())
				{
					newTyre->setSpeedIndex(static_cast<SpeedIndex>(std::stoi(userInput)));
					nextCase = true;
				}
			}
			else
			{
				nextCase = true;
			}
			break;
		default:
			return false;
			break;
		}

		if (nextCase)
		{
			userInput = "";
			userFlow++;
			nextCase = false;
		}
		else
		{
			std::cout << "\n[cancel -> (stop)]" << std::endl;
			cursor();
			std::cin >> userInput;
		}

		if ("stop" == userInput)
		{
			return false;
		}

	} while (userFlow < 12);

	newProduct->getType() == ProductType::Rim ? programController.setProduct(newRim) : programController.setProduct(newTyre);

	saveProductsToBin(programController.getProductListReference());

	std::ofstream idFile{ ID_BIN_FILE,std::ios::binary | std::ios::in | std::ios::out };

	if (idFile)
	{
		programController.writeID(idFile);

		idFile.close();
	}


	std::cout << GREEN << "\n\tPRODUCT CREATED\n" << RESET_COLOR << std::endl;

	return true;
};

bool deleteProduct(Controller& programController)
{
	Product * foundProduct{};
	std::vector<Product*> invoiceProduct;
	std::vector<Invoice*> invoiceList = programController.getInvoiceList();
	std::string userInput;
	long int productID{ 0 };
	long int inputID{ 0 };
	bool match{ false };

	if (!searchProduct(programController.getProductListReference(), productID))
	{
		return false;
	}

	std::cout << HOME_CURSOR << WIPE_SCREEN;

	foundProduct = programController.getProduct(productID);

	Product::displayTableHeaders();
	foundProduct->Product::displayTableRow();
	std::cout << "Do you wish to delete this product ? [y : yes , n : no]\n";

	userInput = input("y", "n");

	if (userInput == "n")
	{
		return false;
	}

	if (userInput == "y")
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
	}

	Product::displayTableHeaders();
	line(120, '-');
	foundProduct->Product::displayTableRow();
	line(120, '-');

	std::cout << "Confirm by entering the product ID:";
	cursor();
	
	std::cin >> userInput;

	try
	{
		inputID = std::stoi(userInput);
	}
	catch (const std::exception e)
	{
		return false;
	}

	std::fstream pendingInvoiceFile{ INVOICES_P_BIN_FILE ,std::ios::binary | std::ios::in | std::ios::out };

	if (!pendingInvoiceFile)
	{
		std::cout << RED << "\n\tSOMETHING OCCURED : COULD NOT OPEN BINARY FILE TEMPORARY FILE\n" << RESET_COLOR;
		std::cout << RED << "\n\tSOMETHING OCCURED : COULD NOT OPEN BINARY FILE\n" << INVOICES_P_BIN_FILE << RESET_COLOR;
		return false;
	}

	if (productID == inputID)
	{
		std::vector<Invoice*>::iterator iterator = invoiceList.begin();
		
		while (iterator != invoiceList.end())
		{
			invoiceProduct = (*iterator)->getInvoiceProducts();
			std::vector<Product*>::iterator iterator_P = std::find_if(invoiceProduct.begin(), invoiceProduct.end(), 
				[&productID](Product* invoiceProduct) 
				{
					return invoiceProduct->getProductID() == productID; 
				});

			if (iterator_P != invoiceProduct.end())
			{
				invoiceProduct.erase(iterator_P);
				match = true;
			}
			else
			{
				iterator++;
			}
		}

		if (match)
		{
			savePendingInvoicesToBin(programController.getInvoiceListReference());
			std::cout << ORANGE << foundProduct->getName() <<  " is deleted from any associated pending invoices" << RESET_COLOR << std::endl;
		}
		else
		{
			std::cout << RED << "\n\tNO INVOICES FOUND WITH\n" << foundProduct->getName() << RESET_COLOR;
		}

		if (programController.deleteProduct(productID))
		{
			saveProductsToBin(programController.getProductListReference());
			std::cout << GREEN << "\n\tPRODUCT DELETED\n" << RESET_COLOR;
		}
		else
		{
			std::cout << RED << "\n\tPRODUCT NOT DELETED\n" << RESET_COLOR;
		}

	}
	pendingInvoiceFile.close();
	return true;
};

bool updateProduct(Controller& programController)
{
	Product * foundProduct{};
	long int productID{ 0 };
	int userChoice{ 0 };
	int newQuantity{ 0 };
	std::string userInput;

	if (!searchProduct(programController.getProductListReference(), productID))
	{
		return false;
	}

	foundProduct = programController.getProduct(productID);

	Product::displayTableHeaders();
	line(120, '-');
	foundProduct->Product::displayTableRow();
	line(120, '-');
	std::cout << "Do you wish to update this product ? " << PINK << " [y : yes , n : no]\n" << RESET_COLOR;

	userInput = input("y", "n");

	if (userInput == "n")
	{
		return false;
	}

	do
	{
		switch (userChoice) 
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			std::cout << "New product name" << RED << " [min " << PRODUCT_NAME_MIN_LEN << " characters]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (PRODUCT_NAME_MIN_LEN <= userInput.size())
			{
				foundProduct->setName(userInput);
				userChoice = 0;
			}
			break;
		case 4:
			std::cout << "New product manufacturer" << RED << " [min " << PRODUCT_MANUFACTURER_MIN_LEN << " characters]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (PRODUCT_MANUFACTURER_MIN_LEN <= userInput.size())
			{
				foundProduct->setManufacturer(userInput);
				userChoice = 0;
			}
			break;

		case 5:
			std::cout 
				<< "Current quantity: " << foundProduct->getQuantity()
			    << "\nSubstract (s) or Add (a) ?";

			userInput = input("s", "a");
			
			if (userInput == "s")
			{
				std::cout << "How much do you wish to substract ?";
				
				newQuantity = input(0, 100);

				*foundProduct -= newQuantity;
				userChoice = 0;
			}

			if (userInput == "a")
			{
				std::cout << "How much do you wish to add ?";

				newQuantity = input(0, 100);

				*foundProduct += newQuantity;
				userChoice = 0;
			}
			break;
		case 6:
			std::cout
				<< "Current diameter: " << foundProduct->getDiameter()
				<< "New diameter: " << RED << " [min " << PRODUCT_DIAMETER_MIN_LEN << " number]: " << RESET_COLOR;
			std::cin >> userInput;
			if (PRODUCT_DIAMETER_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				foundProduct->setDiameter(std::stoi(userInput));
				userChoice = 0;
			}
			break;
		case 7:
			std::cout
				<< "Current price: " << foundProduct->getPrice()
				<< "New price: " << RED << " [min " << PRODUCT_PRICE_MIN_LEN << " number]: " << RESET_COLOR;
			std::cin >> userInput;
			if (PRODUCT_PRICE_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				foundProduct->setPrice(std::stoi(userInput));
				userChoice = 0;
			}
			break;
		case 8:
			std::cout
				<< "Current width: " << foundProduct->getWidth()
				<< "New width: " << RED << " [min " << PRODUCT_WIDTH_MIN_LEN << " numbers]: " << RESET_COLOR;
			std::cin >> userInput;
			if (PRODUCT_WIDTH_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				foundProduct->setWidth(std::stoi(userInput));
				userChoice = 0;
			}
			break;
		case 9:
			switch (foundProduct->getType())
			{
			case ProductType::Tyre:
				
				std::cout
					<< "Current height: " << dynamic_cast<Tyre*>(foundProduct)->getHeight()
					<< "New height: " << RED << " [min " << PRODUCT_HEIGHT_MIN_LEN << " number]: " << RESET_COLOR;
				std::cin >> userInput;
				if (PRODUCT_HEIGHT_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
				{
					dynamic_cast<Tyre*>(foundProduct)->setHeight(std::stoi(userInput));
					userChoice = 0;
				}

				break;
			case ProductType::Rim:
				
				std::cout
					<< "Current color: " << dynamic_cast<Rim*>(foundProduct)->getColor()
					<< "New color: " << RED << " [min " << PRODUCT_COLOR_MIN_LEN << " characters]: " << RESET_COLOR;
				std::cin >> userInput;
				if (PRODUCT_COLOR_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
				{
					dynamic_cast<Rim*>(foundProduct)->setColor(userInput);
					userChoice = 0;
				}
				
				break;
			default:
				break;
			}

			break;
		case 10:
			switch (foundProduct->getType())
			{
			case ProductType::Tyre:
				std::cout
					<< "Current tyremarkings : " << dynamic_cast<Tyre*>(foundProduct)->getTyreMarkings()
					<< "New tyremarkings " << RED << " [min " << PRODUCT_MARKINGS_MIN_LEN << " characters]: " << RESET_COLOR;
				std::cin >> userInput;
				if (PRODUCT_MARKINGS_MIN_LEN <= userInput.size())
				{
					dynamic_cast<Tyre*>(foundProduct)->setTyreMarkings(userInput);
					userChoice = 0;
				}
				break;
			case ProductType::Rim:
				std::cout
					<< "\nCurrent material: "
					<< Rim::materialMap[dynamic_cast<Rim*>(foundProduct)->getRimMaterial()]
					<< "\nNew material " << PINK << " [1: STEEL , 2: ALUMINIUM]:\n " << RESET_COLOR;

				userChoice = input(1, (int)Rim::materialMap.size());
				dynamic_cast<Rim*>(foundProduct)->setRimMaterial(static_cast<RimMaterial>(userChoice));
				userChoice = 0;
				break;
			default:
				break;
			}
			break;
		case 11:
			if (foundProduct->getType() == ProductType::Tyre)
			{
				std::cout
					<< "Current speed index: "
					<< Tyre::speedIndexMap[dynamic_cast<Tyre*>(foundProduct)->getSpeedIndex()]
					<< "\nNew speed index " << PINK << "[";
				
				for (std::pair<SpeedIndex,std::string> mapItem : Tyre::speedIndexMap)
				{
					std::cout << static_cast<int>(mapItem.first) << " -> " << std::setw(3) << mapItem.second << " | ";
					if (static_cast<int>(mapItem.first) % 3)
					{
						std::cout << "\n";
					}
				}

				std::cout << "]" << RESET_COLOR;

				userChoice = input(1, (int)Tyre::speedIndexMap.size());
				dynamic_cast<Tyre*>(foundProduct)->setSpeedIndex(static_cast<SpeedIndex>(userChoice));
				userChoice = 0;
			}
			break;
		default:
			std::cout << HOME_CURSOR << WIPE_SCREEN;

			switch (foundProduct->getType())
			{
			case ProductType::Tyre:
				Tyre::displayTableHeaders();
				break;
			case ProductType::Rim:
				Rim::displayTableHeaders();
				break;
			default:
				break;
			}

			line(120, '-');
			foundProduct->displayTableRow();
			line(120, '-');

			std::cout << "What do you wish to update ?\n"
				<< "1 |--> save\n"
				<< "2 |--> cancel\n"
				<< "3 |--> product name\n"
				<< "4 |--> product manufacturer\n"
				<< "5 |--> quantity\n"
				<< "6 |--> diameter\n"
				<< "7 |--> price\n"
				<< "8 |--> width\n";

			switch (foundProduct->getType())
			{
			case ProductType::Tyre:
				std::cout
					<< "9 |--> height\n"
					<< "10|--> tyremarkings\n"
					<< "11|--> speed index\n";
				userChoice = input(1, 11);
				break;
			case ProductType::Rim:
				std::cout
					<< "9 |--> color\n"
					<< "10|--> material\n";
				userChoice = input(1, 10);
				break;
			default:
				break;
			}

			break;
		}

	} while (userChoice != 1);

	if (userChoice == 1)
	{
		programController.setProduct(foundProduct);
		saveProductsToBin(programController.getProductListReference());
	}

	return true;
};

bool searchProduct(std::vector<Product*>& productList, long int& productID)
{
	// this search function is implemented a little bit different then the customer search function
	// because i wanted to reuse this function to search both the product list in the controller or any invoice
	std::string userInput;
	int userChoice{ 0 };
	int counter{ 0 };
	bool result{ false };
	std::vector<Product*> newProductList;
	std::vector<Product*> oldProductList = productList;
	std::vector<Product*>::iterator iterator;

	do
	{
		switch (userChoice)
		{
		case 1:
			std::cout << "Enter product ID" << PINK << " [cancel -> 0] :" << RESET_COLOR;
			cursor();
			std::cin >> userInput;

			if (userInput != "0" && verifyNumericInput(userInput))
			{
				productID = static_cast<long int>(std::stoi(userInput));
				iterator = std::find_if(productList.begin(), productList.end(), [&productID](Product* product) { return product->getProductID() == productID; });
				if (iterator != productList.end())
				{
					// the "find" function gives back a iterator from the position the element is found so if i want to
					// get the index, I use the difference between the vector's begin iterator and the iterator itself
					newProductList.push_back(productList[std::distance(productList.begin(), iterator)]);
					result = true;
				}
			}
			else
			{
				result = false;
			}

			break;
		case 2:
			result = filterProducts(ProductMenuRequest::FILTER_ON_PRODUCTS_NAME, oldProductList, newProductList);
			break;
		case 3:
			result = filterProducts(ProductMenuRequest::FILTER_ON_PRODUCTS_MANUFACTURER, oldProductList, newProductList);
			break;
		case 4:
			result = filterProducts(ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM, oldProductList, newProductList);
			break;
		case 5:
			result = filterProducts(ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE, oldProductList, newProductList);
			break;
		case 6:
			return false;
			break;
		default:
			std::cout
				<< VIOLET
				<< "Do you want to select a product by their :\n"
				<< "1 |--> ID\n"
				<< "2 |--> product name\n"
				<< "3 |--> product manufacturer\n"
				<< "4 |--> product of type Rim\n"
				<< "5 |--> product of type Tyre\n"
				<< "6 |--> Go back to Product menu\n"
				<< RESET_COLOR;
			userChoice = input(1, 6);
			counter = 0;
			break;
		}

		if (result == false && counter != 0)
		{
			userChoice = 0;
		}

		if (1 < newProductList.size() && result == true)
		{
			oldProductList = newProductList;
			newProductList.clear();
			userChoice = 0;

			showList(oldProductList);

			result = false;
		}

		if (newProductList.size() == 0 && result == true)
		{
			std::cout << RED << "\n\tNO RESULTS FOUND\n" << RESET_COLOR;
			userChoice = 0;
			std::vector<Product*> oldProductList = productList;
			newProductList.clear();
			result = false;
		}

		counter++;
	} while (newProductList.size() != 1);

	productID = newProductList[0]->getProductID();

	std::cout << HOME_CURSOR << WIPE_SCREEN;

	return true;
};

bool orderProducts(ProductMenuRequest request,std::vector<Product*>& productList)
{
	std::vector<Product*> newProductList = productList;
	std::function<bool(Product*, Product*)> lambdaHolder;
	switch (request)
	{
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getType() > product_B->getType(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getType() < product_B->getType(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_NAME:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getName() < product_B->getName(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_DIAMETER:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getDiameter() < product_B->getDiameter(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_MANUFACTURER:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getManufacturer() < product_B->getManufacturer(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_NAME:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getName() < product_B->getName(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_DIAMETER:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getDiameter() < product_B->getDiameter(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_MANUFACTURER:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getManufacturer() < product_B->getManufacturer(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_WIDTH:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getWidth() < product_B->getWidth(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_HEIGHT:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  dynamic_cast<Tyre*>(product_A)->getHeight() < dynamic_cast<Tyre*>(product_B)->getHeight(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_SPEEDINDEX:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  dynamic_cast<Tyre*>(product_A)->getSpeedIndex() < dynamic_cast<Tyre*>(product_B)->getSpeedIndex(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_TYREMARKINGS:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  dynamic_cast<Tyre*>(product_A)->getTyreMarkings() < dynamic_cast<Tyre*>(product_B)->getTyreMarkings(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_NAME:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getName() < product_B->getName(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_DIAMETER:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getDiameter() < product_B->getDiameter(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_MANUFACTURER:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getManufacturer() < product_B->getManufacturer(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_WIDTH:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  product_A->getWidth() < product_B->getWidth(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_COLOR:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return  dynamic_cast<Rim*>(product_A)->getColor() < dynamic_cast<Rim*>(product_B)->getColor(); };
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_MATERIAL:
		lambdaHolder = [&productList](Product* product_A, Product* product_B) { return   dynamic_cast<Rim*>(product_A)->getRimMaterial() < dynamic_cast<Rim*>(product_B)->getRimMaterial(); };
		break;
	default:
		break;
	}

	if (lambdaHolder)
	{
		std::sort(productList.begin(), productList.end(), lambdaHolder);
	}

	showList(newProductList);
	// i dont need the product list anymore after i have finished ordering the list
	return true;
};

bool filterProducts(ProductMenuRequest request,std::vector<Product*>& productList, std::vector<Product*>& filteredList)
{
	std::string userInput;
	bool matches{ false };

	if ("1" == userInput || !handleUserInput(request, userInput))
	{
		return 0;
	}

	for (int i = 0; i < productList.size(); ++i)
	{
		switch (request)
		{
		case ProductMenuRequest::FILTER_ON_PRODUCTS_NAME:
			matches = productList[i]->getName().find(userInput) != std::string::npos;
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_DIAMETER:
			matches = productList[i]->getDiameter() == std::stoi(userInput);
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_MANUFACTURER:
			matches = productList[i]->getManufacturer().find(userInput) != std::string::npos;
			break;
			// Additional cases for Tyre-specific attributes
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE:
			matches = productList[i]->getType() == ProductType::Tyre;
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_NAME:
			matches = productList[i]->getType() == ProductType::Tyre && productList[i]->getName().find(userInput) != std::string::npos;
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_DIAMETER:
			matches = productList[i]->getType() == ProductType::Tyre && productList[i]->getDiameter() == std::stoi(userInput);
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_MANUFACTURER:
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_WIDTH:
			matches = productList[i]->getType() == ProductType::Tyre && productList[i]->getWidth() == std::stoi(userInput);
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_HEIGHT:
			matches = productList[i]->getType() == ProductType::Tyre && dynamic_cast<Tyre*>(productList[i])->getHeight() == std::stoi(userInput);
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_SPEEDINDEX:
			matches = productList[i]->getType() == ProductType::Tyre && dynamic_cast<Tyre*>(productList[i])->getSpeedIndex() == static_cast<SpeedIndex>(std::stoi(userInput));
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_TYREMARKINGS:
			matches = productList[i]->getType() == ProductType::Tyre && dynamic_cast<Tyre*>(productList[i])->getTyreMarkings().find(userInput) != std::string::npos;
			break;
			// Additional cases for Rim-specific attributes
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM:
			matches = productList[i]->getType() == ProductType::Rim;
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_NAME:
			matches = productList[i]->getType() == ProductType::Rim && productList[i]->getName().find(userInput) != std::string::npos;
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_MANUFACTURER:
			matches = productList[i]->getType() == ProductType::Rim && productList[i]->getManufacturer().find(userInput) != std::string::npos;
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_WIDTH:
			matches = productList[i]->getType() == ProductType::Rim && productList[i]->getWidth() == std::stoi(userInput);
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_DIAMETER:
			matches = productList[i]->getType() == ProductType::Rim && productList[i]->getDiameter() == std::stoi(userInput);
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_MATERIAL:
			matches = productList[i]->getType() == ProductType::Rim && dynamic_cast<Rim*>(productList[i])->getRimMaterial() == static_cast<RimMaterial>(std::stoi(userInput));
			break;
		case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_COLOR:
			matches = productList[i]->getType() == ProductType::Rim && dynamic_cast<Rim*>(productList[i])->getColor().find(userInput) != std::string::npos;
			break;
		default:
			matches = false;
			break;
		}

		if (matches)
		{
			productList[i]->displayTableRow();
			std::cout << "\n";
			filteredList.push_back(productList[i]);
		}

	}

	return true;
};

bool filterProducts(ProductMenuRequest request,std::vector<Product*>& productList)
{
	std::vector<Product*> newProductList;
	filterProducts(request, productList, newProductList);
	showList(newProductList);
	return true;
};

bool handleUserInput(ProductMenuRequest request, std::string& userInput) {

	switch (request)
	{
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE:
	case ProductMenuRequest::SHOW_ALL_PRODUCTS:
		return true;
		break;
	case ProductMenuRequest::FILTER_ON_PRODUCTS_NAME:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_MANUFACTURER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_NAME:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_MANUFACTURER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_NAME:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_MANUFACTURER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_TYREMARKINGS:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_COLOR:
		std::cout
			<< VIOLET
			<< "Enter filter value : \n"
			<< "1 |<-- Cancel \n"
			<< RESET_COLOR;
		cursor();
		std::cin >> userInput;
		return true;
		break;
	case ProductMenuRequest::FILTER_ON_PRODUCTS_DIAMETER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_DIAMETER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_WIDTH:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_DIAMETER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_HEIGHT:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_WIDTH:
		std::cout
			<< VIOLET
			<< "Enter filter value : \n"
			<< "1 |<-- Cancel \n"
			<< RESET_COLOR;
		cursor();
		std::cin >> userInput;

		if (!verifyNumericInput(userInput))
		{
			return false;
		}
		return true;

		break;
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_MATERIAL:
		try
		{
			std::cout
				<< VIOLET
				<< "Enter filter value : \n" 
				<< "1 |<-- Cancel \n"
				<< PINK 
				<< "[1: STEEL , 2: ALUMINIUM]: \n" 
				<< RESET_COLOR;
			cursor();
			std::cin >> userInput;

			if (std::stoi(userInput) == 1 || std::stoi(userInput) == Rim::materialMap.size())
			{
				return true;
			}
		}
		catch (const std::exception&)
		{
			return false;
		}
		break;
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_SPEEDINDEX:
		try
		{
			std::cout
				<< VIOLET
				<< "Enter filter value : "
				<< PINK;
			for (std::pair<SpeedIndex, std::string> mapItem : Tyre::speedIndexMap)
			{
				std::cout << static_cast<int>(mapItem.first) << " -> " << mapItem.second;
			}
			std::cout << RESET_COLOR;
			cursor();
			std::cin >> userInput;

			if (1 <= std::stoi(userInput) && std::stoi(userInput) <= Tyre::speedIndexMap.size())
			{
				return true;
			}
		}
		catch (const std::exception&)
		{
			return false;
		}
		break;
	default:
		return false;
		break;
	}

	return false;
}

//	  ______                         __                                                         ______                                  __      __                               
//	 /      \                       /  |                                                       /      \                                /  |    /  |                              
//	/$$$$$$  | __    __   _______  _$$ |_     ______   _____  ____    ______    ______        /$$$$$$  |__    __  _______    _______  _$$ |_   $$/   ______   _______    _______ 
//	$$ |  $$/ /  |  /  | /       |/ $$   |   /      \ /     \/    \  /      \  /      \       $$ |_ $$//  |  /  |/       \  /       |/ $$   |  /  | /      \ /       \  /       |
//	$$ |      $$ |  $$ |/$$$$$$$/ $$$$$$/   /$$$$$$  |$$$$$$ $$$$  |/$$$$$$  |/$$$$$$  |      $$   |   $$ |  $$ |$$$$$$$  |/$$$$$$$/ $$$$$$/   $$ |/$$$$$$  |$$$$$$$  |/$$$$$$$/ 
//	$$ |   __ $$ |  $$ |$$      \   $$ | __ $$ |  $$ |$$ | $$ | $$ |$$    $$ |$$ |  $$/       $$$$/    $$ |  $$ |$$ |  $$ |$$ |        $$ | __ $$ |$$ |  $$ |$$ |  $$ |$$      \ 
//	$$ \__/  |$$ \__$$ | $$$$$$  |  $$ |/  |$$ \__$$ |$$ | $$ | $$ |$$$$$$$$/ $$ |            $$ |     $$ \__$$ |$$ |  $$ |$$ \_____   $$ |/  |$$ |$$ \__$$ |$$ |  $$ | $$$$$$  |
//	$$    $$/ $$    $$/ /     $$/   $$  $$/ $$    $$/ $$ | $$ | $$ |$$       |$$ |            $$ |     $$    $$/ $$ |  $$ |$$       |  $$  $$/ $$ |$$    $$/ $$ |  $$ |/     $$/ 
//	 $$$$$$/   $$$$$$/  $$$$$$$/     $$$$/   $$$$$$/  $$/  $$/  $$/  $$$$$$$/ $$/             $$/       $$$$$$/  $$/   $$/  $$$$$$$/    $$$$/  $$/  $$$$$$/  $$/   $$/ $$$$$$$/  

bool saveCustomersToBin(std::vector<Customer*>& customerList)
{
	std::ofstream customerFile;
	std::ofstream tempFile{ "temp.bin" ,std::ios::binary | std::ios::trunc | std::ios::out };
	// to be certain copy the file contents to a temporary file
	// "rdbuf" returns a pointer to the stream buffer. The reason i need this is because a 
	// "fstream" objects are only overloaded only with a other "fstream" object with their stream buffer 
	for (Customer * customerInList : customerList)
	{
		if (!customerInList->write(tempFile))
		{
			tempFile.close();
			std::remove("temp.bin");
			std::cout << RED << "\n\tSOMETHING OCCURED : WRITING ERROR TO TEMPORARY FILE FAILED\n" << RESET_COLOR;
			return false;
		}
	}
	tempFile.close();

	std::ifstream tempFileInput("temp.bin", std::ios::binary | std::ios::in);
	customerFile.open(CUSTOMERS_BIN_FILE, std::ios::binary | std::ios::out);
	if (!customerFile || !tempFileInput)
	{
		tempFileInput.close();
		customerFile.close();
		std::cout << RED << "\n\tSOMETHING OCCURED : COULD NOT OPEN BINARY FILE\n" << CUSTOMERS_BIN_FILE << RESET_COLOR;
		return false;
	}
	
	customerFile << tempFileInput.rdbuf();

	tempFileInput.close();
	customerFile.close();
	std::remove("temp.bin");
	return true;
};

bool saveCustomers(Controller& programController)
{
	std::ofstream customerFile;
	std::string userInput;
	std::string fileName;
	std::vector<Customer*> customerList = programController.getCustomerListReference();
	int userChoice;


	std::cout
		<< VIOLET
		<< "Save customers\n"
		<< "1 |--> save as BIN\n"
		<< "2 |--> save as CSV\n"
		<< "3 |--> save as TXT\n"
		<< "4 |--> save as XML\n"
		<< "5 |--> Back to Customer Menu\n"
		<< RESET_COLOR;

	userChoice = input(1, 5);

	switch (userChoice)
	{
	case 1: 
		saveCustomersToBin(customerList);
		break;
	case 2:
		customerFile.open(CUSTOMERS_CSV_FILE, std::ios::out);
		writeCSV(customerFile, Customer::csvHeaders(), customerList);
		customerFile.close();
		break;
	case 3:
		customerFile.open(CUSTOMERS_TXT_FILE, std::ios::out);
		writeTXT(customerFile, customerList);
		customerFile.close();
		break;
	case 4:
		customerFile.open(CUSTOMERS_XML_FILE, std::ios::out);
		customerFile << _START_XML;
		customerFile << _START_CUSTOMER_LIST_XML;
		writeXML(customerFile, customerList);
		customerFile << _STOP_CUSTOMER_LIST_XML;
		customerFile.close();
		break;
	case 5:
		break;
	default:
		break;
	}
	return true;
};

bool checkCustomerFile(std::ifstream& customerFile, Controller& programController)
{
	if (!customerFile)
	{
		std::ofstream newCustomerFile{ CUSTOMERS_BIN_FILE,std::ios::binary | std::ios::out };
		if (!newCustomerFile)
		{
			sendErrorMessage(14);
		}
		newCustomerFile.close();
		return true;
	}
	readCustomerFile(customerFile, programController);
	return true;
};

bool readCustomerFile(std::ifstream& customerFile, Controller& programController)
{
	customerFile.seekg(0,std::ios::end);
	size_t length = customerFile.tellg();

	if (length == 0)
	{
		return false;
	}

	customerFile.seekg(0);

	Customer customerFromFile{};

	while (customerFile)
	{
		customerFromFile.read(customerFile);
		programController.setCustomer(customerFromFile);
	}

	return true;
};

bool addCustomer(Controller& programController)
{
	int userChoice{ 0 };
	int userFlow{ 0 };
	bool nextCase{ false };
	Customer newCustomer{};
	Address newCustomerAddress;
	std::string userInput;

	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		Customer::displayTableHeaders();
		line(120, '-');
		newCustomer.displayTableRow();
		line(120, '-');

		switch (userFlow)
		{
		case 0:
			std::cout << "Enter the customer's type" << PINK << " [private customer (p) , corporate customer (c)]: " << RESET_COLOR;

			if ("p" == userInput)
			{
				newCustomer.setCustomerType(CustomerType::PRIV);
				nextCase = true;
			}

			if ("c" == userInput)
			{
				newCustomer.setCustomerType(CustomerType::CORP);
				nextCase = true;
			}

			break;
		case 1:
			std::cout << "Enter the customer's firstname" << RED << " [min " << CUSTOMER_FIRSTNAME_MIN_LEN << " characters, NO NUMBERS ALLOWED]: " << RESET_COLOR;

			if (CUSTOMER_FIRSTNAME_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
			{
				newCustomer.setFirstName(userInput);
				nextCase = true;
			}

			break;
		case 2:
			std::cout << "Enter the customer's lastname" << RED << " [min " << CUSTOMER_LASTNAME_MIN_LEN << " characters, NO NUMBERS ALLOWED]: " << RESET_COLOR;

			if (CUSTOMER_LASTNAME_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
			{
				newCustomer.setLastName(userInput);
				nextCase = true;
			}

			break;
		case 3:
			std::cout << "Enter the customer's country" << RED << " [min " << CUSTOMER_COUNTRY_MIN_LEN << " characters, NO NUMBERS ALLOWED]: " << RESET_COLOR;

			if (CUSTOMER_COUNTRY_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
			{
				userInput.substr(0, STR_LENGTH - 1).copy(newCustomerAddress.country, STR_LENGTH - 1);
				newCustomer.setAddress(newCustomerAddress);
				nextCase = true;
			}

			break;
		case 4:
			std::cout << "Enter the customer's postalCode" << RED << " [min " << CUSTOMER_POSTALCODE_MIN_LEN << " characters]: " << RESET_COLOR;

			if (CUSTOMER_POSTALCODE_MIN_LEN <= userInput.size())
			{
				userInput.substr(0, STR_LENGTH - 1).copy(newCustomerAddress.postalCode, STR_LENGTH - 1);
				newCustomer.setAddress(newCustomerAddress);
				nextCase = true;
			}

			break;
		case 5:
			std::cout << "Enter the customer's streetname" << RED << " [min " << CUSTOMER_STREETNAME_MIN_LEN << " characters, NO NUMBERS ALLOWED]: " << RESET_COLOR;

			if (CUSTOMER_STREETNAME_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
			{
				userInput.substr(0, STR_LENGTH - 1).copy(newCustomerAddress.streetName, STR_LENGTH - 1);
				newCustomer.setAddress(newCustomerAddress);
				nextCase = true;
			}

			break;
		case 6:
			std::cout << "Enter the customer's housenumber" << RED << " [min " << CUSTOMER_HOUSENUMBER_MIN_LEN << " number]: " << RESET_COLOR;

			if (CUSTOMER_HOUSENUMBER_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				userInput.substr(0, STR_LENGTH - 1).copy(newCustomerAddress.houseNumber, STR_LENGTH - 1);
				newCustomer.setAddress(newCustomerAddress);
				nextCase = true;
			}

			break;
		case 7:
			std::cout << "Enter the customer's phonenumber" << RED << " [min " << CUSTOMER_PHONENUMBER_MIN_LEN << " numbers]: " << RESET_COLOR;

			if (CUSTOMER_PHONENUMBER_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				userInput.substr(0, STR_LENGTH - 1).copy(newCustomerAddress.phoneNumber, STR_LENGTH - 1);
				newCustomer.setAddress(newCustomerAddress);
				nextCase = true;
			}

			break;
		default:
			return false;
			break;
		}

		if (nextCase)
		{
			userInput = "";
			userFlow++;
			nextCase = false;
		}
		else
		{
			std::cout << "\n[cancel -> stop]" << std::endl;
			cursor();
			std::cin >> userInput;
		}

		if ("stop" == userInput)
		{
			return false;
		}

	} while (userFlow < 8);

	newCustomer.setAddress(newCustomerAddress);
	programController.setCustomer(newCustomer);

	std::ofstream idFile{ ID_BIN_FILE,std::ios::binary | std::ios::in | std::ios::out };

	if (idFile)
	{
		programController.writeID(idFile);

		idFile.close();
	}

	std::cout << GREEN << "\n\tUSER CREATED\n" << RESET_COLOR << std::endl;

	return true;
};

bool deleteCustomer(Controller& programController)
{
	Customer * foundCustomer{};
	std::string userInput;
	std::vector<Invoice*> invoiceList = programController.getInvoiceList();
	long int customerID{ 0 };
	long int inputID{ 0 };
	bool match{ false };

	if (!searchCustomer(programController, customerID))
	{
		return false;
	}

	foundCustomer = programController.getCustomer(customerID);

	std::cout << HOME_CURSOR << WIPE_SCREEN;
	
	customerID = foundCustomer->getCustomerID();
	Customer::displayTableHeaders();
	line(120, '-');
	foundCustomer->displayTableRow();
	line(120, '-');
	std::cout << "Do you wish to delete this customer ? [y : yes , n : no]\n";

	userInput = input("y", "n");

	if (userInput == "n")
	{
		return false;
	}

	if (userInput == "y")
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
	}

	Customer::displayTableHeaders();
	line(120, '-');
	foundCustomer->displayTableRow();
	line(120, '-');
	std::cout << "Confirm by entering the customers ID:";
	cursor();

	std::cin >> userInput;

	try
	{
		inputID = std::stoi(userInput);
	}
	catch (const std::exception e)
	{
		return false;
	}

	if (customerID == inputID)
	{
		std::vector<Invoice*>::iterator iterator = invoiceList.begin();
		
		while (iterator != invoiceList.end())
		{
			if ((*iterator)->getCustomer()->getCustomerID() == customerID)
			{
				iterator = invoiceList.erase(iterator);
				match = true;
			}
			else
			{
				iterator++;
			}
		}

		if (match)
		{
			std::cout << ORANGE << "associated pending invoices to " << foundCustomer->getFirstName() + ' ' + foundCustomer->getLastName() << " are deleted" << RESET_COLOR << std::endl;
		}
		else
		{
			std::cout << RED << "\n\tNO INVOICES FOUND MATCHING " << foundCustomer->getFirstName() + ' ' + foundCustomer->getLastName() << RESET_COLOR;
		}

		if (programController.deleteCustomer(customerID))
		{
			std::cout << GREEN << "\n\tCUSTOMER DELETED\n" << RESET_COLOR;
		}
	}

	return true;
};

bool updateCustomer(Controller& programController)
{
	Customer * foundCustomer{};
	long int customerID{ 0 };
	int userChoice{ 0 };
	std::string userInput;
	if (!searchCustomer(programController, customerID))
	{
		return false;
	}

	foundCustomer = programController.getCustomer(customerID)->clone();

	Customer::displayTableHeaders();
	line(120, '-');
	foundCustomer->displayTableRow();
	line(120, '-');

	std::cout << "\nDo you wish to update this customer ? [y : yes , n : no]\n";

	userInput = input("y", "n");

	if (userInput == "n")
	{
		return false;
	}

	Address customerAddress = foundCustomer->getAddress();

	do
	{
		switch (userChoice)
		{
		case 1:
			break;
		case 2:
			std::cout << "new Firstname" << RED <<  " [min " << CUSTOMER_FIRSTNAME_MIN_LEN << " characters, NO NUMBERS ALLOWED] : " << RESET_COLOR;
			cursor();
			std::cin >> userInput;

			if (CUSTOMER_FIRSTNAME_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
			{
				foundCustomer->setFirstName(userInput.substr(0, STR_LENGTH - 1));
				userChoice = 0;
			}

			break;
		case 3:
			std::cout << "new Lastname" << RED << " [min " << CUSTOMER_LASTNAME_MIN_LEN << " characters, NO NUMBERS ALLOWED]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;

			if (CUSTOMER_LASTNAME_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
			{
				foundCustomer->setLastName(userInput.substr(0, STR_LENGTH - 1));
				userChoice = 0;
			}

			break;
		case 4:
			std::cout << "new Type" << PINK << " [private customer (p) , corporate customer (c)]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if ("p" == userInput)
			{
				foundCustomer->setCustomerType(CustomerType::PRIV);
				userChoice = 0;
			}

			if ("c" == userInput)
			{
				foundCustomer->setCustomerType(CustomerType::CORP);
				userChoice = 0;
			}
			break;
		case 5:
			std::cout << "new Country" << RED << " [min " << CUSTOMER_COUNTRY_MIN_LEN << " characters, NO NUMBERS ALLOWED]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (CUSTOMER_COUNTRY_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
			{
				userInput.substr(0, STR_LENGTH - 1).copy(customerAddress.country, STR_LENGTH - 1);
				foundCustomer->setAddress(customerAddress);
				userChoice = 0;
			}
			break;
		case 6:
			std::cout << "new Postalcode" << RED << " [min " << CUSTOMER_POSTALCODE_MIN_LEN << " characters]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (CUSTOMER_POSTALCODE_MIN_LEN <= userInput.size())
			{
				userInput.substr(0, STR_LENGTH - 1).copy(customerAddress.postalCode, STR_LENGTH - 1);
				foundCustomer->setAddress(customerAddress);
				userChoice = 0;
			}
			break;
		case 7:
			std::cout << "new Streetname" << RED << " [min " << CUSTOMER_STREETNAME_MIN_LEN << " characters, NO NUMBERS ALLOWED]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (CUSTOMER_STREETNAME_MIN_LEN <= userInput.size() && verifyAlphaInput(userInput))
			{
				userInput.substr(0, STR_LENGTH - 1).copy(customerAddress.streetName, STR_LENGTH - 1);
				foundCustomer->setAddress(customerAddress);
				userChoice = 0;
			}
			break;
		case 8:
			std::cout << "new Housenumber" << RED << " [min " << CUSTOMER_HOUSENUMBER_MIN_LEN <<" number, ONLY NUMBERS ALLOWED]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (CUSTOMER_HOUSENUMBER_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				userInput.substr(0, STR_LENGTH - 1).copy(customerAddress.houseNumber, STR_LENGTH - 1);
				foundCustomer->setAddress(customerAddress);
				userChoice = 0;
			}
			break;
		case 9:
			std::cout << "new Phonenumber" << RED << " [min " << CUSTOMER_PHONENUMBER_MIN_LEN <<" numbers, ONLY NUMBERS ALLOWED]: " << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (CUSTOMER_PHONENUMBER_MIN_LEN <= userInput.size() && verifyNumericInput(userInput))
			{
				userInput.substr(0, STR_LENGTH - 1).copy(customerAddress.phoneNumber, STR_LENGTH - 1);
				foundCustomer->setAddress(customerAddress);
				userChoice = 0;
			}
			break;
		case 10:
			delete foundCustomer;
			return false;
			break;
		default:
			std::cout << HOME_CURSOR << WIPE_SCREEN;

			Customer::displayTableHeaders();
			line(120, '-');
			foundCustomer->displayTableRow();
			line(120, '-');

			std::cout << "What do you wish to update ?\n"
				<< "1 |--> Save\n"
				<< "2 |--> FirstName\n"
				<< "3 |--> LastName\n"
				<< "4 |--> Type\n"
				<< "5 |--> Country\n"
				<< "6 |--> PostalCode\n"
				<< "7 |--> Streetname\n"
				<< "8 |--> Housenumber\n"
				<< "9 |--> Phonenumber\n"
				<< "10|--> return to Customer Menu\n";
			userChoice = input(1, 10);
			
			break;
		}

	} while (userChoice != 1);

	// a new copy is made in the programController
	// and the original is deleted
	programController.setCustomer(*foundCustomer);
	delete foundCustomer;
	return true;
};

bool searchCustomer(Controller& programController, long int& customerID)
{
	bool result{ false };
	int userChoice{ 0 };
	int counter{ 0 };
	std::vector<Customer*> newCustomerList;
	std::vector<Customer*> oldCustomerList = programController.getCustomerList();

	do
	{
		switch (userChoice)
		{
		case 1:
			std::cout << "Enter customerID " << PINK << " [cancel -> 0] " << RESET_COLOR;

			customerID = (long int)input(0, programController.getCurrentCustomerID());
			// the ID of the customer can only be in the range => [ 1 ; currentID ]
			// but...
			// if the ID is entered however we still need to check whether this customer still exists in the program (could be erased!)
			if (programController.checkCustomerExistence(customerID))
			{
				newCustomerList.push_back(programController.getCustomer(customerID));
				result = true;
			}
			else
			{
				result = false;
			}

			break;
		case 2:
			result = filterCustomers(CustomerMenuRequest::FILTER_ON_CUSTOMERS_FIRSTNAME, oldCustomerList, newCustomerList);
			break;
		case 3:
			result = filterCustomers(CustomerMenuRequest::FILTER_ON_CUSTOMERS_LASTNAME, oldCustomerList, newCustomerList);
			break;
		case 4:
			result = filterCustomers(CustomerMenuRequest::FILTER_ON_CUSTOMERS_TYPE_CORP, oldCustomerList, newCustomerList);
			break;
		case 5:
			result = filterCustomers(CustomerMenuRequest::FILTER_ON_CUSTOMERS_TYPE_PRIV, oldCustomerList, newCustomerList);
			break;
		case 6:
			return false;
			break;
		default:
			std::cout
				<< VIOLET
				<< "Search customer by :\n"
				<< "1 |--> ID\n"
				<< "2 |--> firstname\n"
				<< "3 |--> lastname\n"
				<< "4 |--> type corporate\n"
				<< "5 |--> type private\n"
				<< "6 |--> go back to Customer menu\n"
				<< RESET_COLOR;
			userChoice = input(1, 6);
			counter = 0;
			break;
		}

		if (result == false && counter != 0)
		{
			userChoice = 0;
		}

		// if the result of the filtering is still not equal to 1 unique customer
		// but it succeeded we set the old list equal to the newFilterd list and clear the newList 
		// to prepare to filter again till we have a unique customer
		if (1 < newCustomerList.size() && result == true)
		{
			oldCustomerList = newCustomerList;
			newCustomerList.clear();
			userChoice = 0;

			showList(oldCustomerList);
			result = false;
		}

		// if the filtered list has a size of 0 it means no result was found so we start again
		// by resetting the lists to their initial state
		if (newCustomerList.size() == 0 && result == true)
		{
			std::cout << RED << "\n\tNO RESULTS FOUND\n" << RESET_COLOR;
			std::vector<Customer*> oldCustomerList = programController.getCustomerList();
			newCustomerList.clear();
			result = false;
		}

		counter++;
	} while (newCustomerList.size() != 1);
	// if we found a unique customer we can quit the while loop
	// and set the customerID in order to use the customer outside the function
	customerID = newCustomerList[0]->getCustomerID();

	std::cout << HOME_CURSOR << WIPE_SCREEN;

	return true;
};

bool orderCustomers(CustomerMenuRequest request,std::vector<Customer*>& customerList)
{
	// "customerList"
	// this is a copy to the customerlist stored in the controller
	// Actually could also not be a copy see => NRVO
	// => https://en.cppreference.com/w/cpp/language/copy_elision
	// we use lambda expressions here inside the "sort" function see 
	// => Chap 16.3 "C++ How To Program" by Paul Deitel and Harvey Deitel
	// => https://codeforces.com/blog/entry/92918

	std::function<bool(Customer*, Customer*)> lambdaHolder;
	std::string userInput;

	// depending on the user's request we order by a different metric 
	switch (request)
	{
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_FIRSTNAME:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  customer_A->getFirstName() < customer_B->getFirstName(); };
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_LASTNAME:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  customer_A->getLastName() < customer_B->getLastName(); };
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_COUNTRY:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  std::string(customer_A->getAddress().country) < std::string(customer_B->getAddress().country); };
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_POSTALCODE:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  std::string(customer_A->getAddress().postalCode) < std::string(customer_B->getAddress().postalCode); };
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_STREETNAME:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  std::string(customer_A->getAddress().streetName) < std::string(customer_B->getAddress().streetName); };
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_HOUSENUMBER:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  std::string(customer_A->getAddress().houseNumber) < std::string(customer_B->getAddress().houseNumber); };
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_PHONENUMBER:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  std::string(customer_A->getAddress().phoneNumber) < std::string(customer_B->getAddress().phoneNumber); };
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_TYPE_PRIV:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  customer_A->getCustomerType() > customer_B->getCustomerType(); };
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_TYPE_CORP:
		lambdaHolder = [&customerList](Customer* customer_A, Customer* customer_B) { return  customer_A->getCustomerType() < customer_B->getCustomerType(); };
		break;
	default:
		break;
	}

	if (lambdaHolder)
	{
		std::sort(customerList.begin(), customerList.end(), lambdaHolder);
	}

	showList(customerList);
	
	return true;
};

bool filterCustomers(CustomerMenuRequest request,std::vector<Customer*>& customerList)
{
	std::vector<Customer*> newCustomerList;
	if (!filterCustomers(request, customerList, newCustomerList))
	{
		return false;
	}
	showList(newCustomerList);
	return true;
};

bool filterCustomers(CustomerMenuRequest request, std::vector<Customer*>& customerList, std::vector<Customer*>& filteredList)
{
	std::string userInput;
	bool matches{ false };

	if (!handleUserInput(request, userInput) && "1" == userInput)
	{
		std::cout << RED << "\n\tCANCELED\n" << RESET_COLOR;
		return false;
	}

	if (customerList.size() == 0)
	{
		std::cout << RED << "\n\tCANCELED : NO CUSTOMERS ADDED\n" << RESET_COLOR;
		return false;
	}

	for (int i = 0; i < customerList.size(); i++)
	{
		switch (request)
		{
		case CustomerMenuRequest::SHOW_ALL_CUSTOMERS:
			matches = true;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_FIRSTNAME:
			matches = customerList[i]->getFirstName().find(userInput) != std::string::npos;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_LASTNAME:
			matches = customerList[i]->getLastName().find(userInput) != std::string::npos;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_COUNTRY:
			matches = std::string(customerList[i]->getAddress().country).find(userInput) != std::string::npos;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_POSTALCODE:
			matches = std::string(customerList[i]->getAddress().postalCode).find(userInput) != std::string::npos;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_STREETNAME:
			matches = std::string(customerList[i]->getAddress().streetName).find(userInput) != std::string::npos;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_HOUSENUMBER:
			matches = std::string(customerList[i]->getAddress().houseNumber).find(userInput) != std::string::npos;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_PHONENUMBER:
			matches = std::string(customerList[i]->getAddress().phoneNumber).find(userInput) != std::string::npos;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_TYPE_PRIV:
			matches = customerList[i]->getCustomerType() == CustomerType::PRIV;
			break;
		case CustomerMenuRequest::FILTER_ON_CUSTOMERS_TYPE_CORP:
			matches = customerList[i]->getCustomerType() == CustomerType::CORP;
			break;
		default:
			break;
		}

		if (matches)
		{
			filteredList.push_back(customerList[i]);
		}
	}
	return true;
};

bool handleUserInput(CustomerMenuRequest request, std::string& userInput)
{
	// depending on the user's request we filter by a different metric 
	// here we ask the user on what we should filter
	switch (request)
	{
	// check for user input, wich will be our "needle" (needle - haystack) to filter on, for following cases : 
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_FIRSTNAME:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_LASTNAME:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_COUNTRY:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_POSTALCODE:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_STREETNAME:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_HOUSENUMBER:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_PHONENUMBER:
		std::cout
			<< VIOLET
			<< "Enter filter value : \n"
			<< "1 |<-- Cancel\n"
			<< RESET_COLOR;
		cursor();
		std::cin >> userInput;
		break;
	default:
		break;
	}
	return true;
};

//	 ______                                __                             ______                                  __      __                               
//	/      |                              /  |                           /      \                                /  |    /  |                              
//	$$$$$$/  _______   __     __  ______  $$/   _______   ______        /$$$$$$  |__    __  _______    _______  _$$ |_   $$/   ______   _______    _______ 
//	  $$ |  /       \ /  \   /  |/      \ /  | /       | /      \       $$ |_ $$//  |  /  |/       \  /       |/ $$   |  /  | /      \ /       \  /       |
//	  $$ |  $$$$$$$  |$$  \ /$$//$$$$$$  |$$ |/$$$$$$$/ /$$$$$$  |      $$   |   $$ |  $$ |$$$$$$$  |/$$$$$$$/ $$$$$$/   $$ |/$$$$$$  |$$$$$$$  |/$$$$$$$/ 
//	  $$ |  $$ |  $$ | $$  /$$/ $$ |  $$ |$$ |$$ |      $$    $$ |      $$$$/    $$ |  $$ |$$ |  $$ |$$ |        $$ | __ $$ |$$ |  $$ |$$ |  $$ |$$      \ 
//	 _$$ |_ $$ |  $$ |  $$ $$/  $$ \__$$ |$$ |$$ \_____ $$$$$$$$/       $$ |     $$ \__$$ |$$ |  $$ |$$ \_____   $$ |/  |$$ |$$ \__$$ |$$ |  $$ | $$$$$$  |
//	/ $$   |$$ |  $$ |   $$$/   $$    $$/ $$ |$$       |$$       |      $$ |     $$    $$/ $$ |  $$ |$$       |  $$  $$/ $$ |$$    $$/ $$ |  $$ |/     $$/ 
//	$$$$$$/ $$/   $$/     $/     $$$$$$/  $$/  $$$$$$$/  $$$$$$$/       $$/       $$$$$$/  $$/   $$/  $$$$$$$/    $$$$/  $$/  $$$$$$/  $$/   $$/ $$$$$$$/  

bool savePendingInvoicesToBin(std::vector<Invoice*>& invoiceList)
{
	std::ofstream pendingInvoiceFile;
	std::ofstream tempFile{ "temp.bin" ,std::ios::binary | std::ios::trunc | std::ios::out };
	// to be certain copy the file contents to a temporary file
	// "rdbuf" returns a pointer to the stream buffer. The reason i need this is because a 
	// "fstream" objects are only overloaded only with a other "fstream" object with their stream buffer 
	for (Invoice * invoiceInList : invoiceList)
	{
		if (!invoiceInList->writePendingInvoice(tempFile))
		{
			tempFile.close();
			std::cout << RED << "\n\tSOMETHING OCCURED : WRITING ERROR TO TEMPORARY FILE FAILED\n" << RESET_COLOR;
			return false;
		}
	}
	tempFile.close();

	std::ifstream tempFileInput("temp.bin", std::ios::binary | std::ios::in);
	pendingInvoiceFile.open(INVOICES_P_BIN_FILE, std::ios::binary | std::ios::out);
	if (!pendingInvoiceFile)
	{
		std::cout << RED << "\n\tSOMETHING OCCURED : COULD NOT OPEN BINARY FILE\n" << INVOICES_P_BIN_FILE << RESET_COLOR;
		return false;
	}
	pendingInvoiceFile << tempFileInput.rdbuf();
	tempFileInput.close();
	pendingInvoiceFile.close();
	std::remove("temp.bin");
	return true;
};

bool saveInvoices(Controller& programController)
{
	std::ofstream invoiceFile;
	std::ifstream invoiceHandledFile;
	

	std::string userInput;
	std::string fileName;
	
	Invoice invoiceFromFile;
	std::vector<Invoice*> invoiceList = programController.getInvoiceListReference();
	
	int userChoice;


	std::cout
		<< VIOLET
		<< "save invoices\n"
		<< "1 |--> save pending invoices as BIN\n"
		<< "2 |--> export handled invoices to XML\n"
		<< "3 |<-- Back to Customer Menu\n"
		<< RESET_COLOR;

	userChoice = input(1, 3);

	switch (userChoice)
	{
	case 1:
		savePendingInvoicesToBin(programController.getInvoiceListReference());
		break;
	case 2:
		invoiceHandledFile.open( INVOICES_H_BIN_FILE,std::ios::binary | std::ios::in );
		invoiceFile.open(INVOICES_H_XML_FILE, std::ios::out);

		if (!invoiceHandledFile)
		{
			invoiceHandledFile.close();
			invoiceFile.close();

			std::cout << RED << "NO HANDLED INVOICES" << RESET_COLOR;
			return false;
		}

		invoiceFile << _START_XML;
		invoiceFile << _START_INVOICE_LIST_XML;

		while (invoiceHandledFile)
		{
			if (invoiceFromFile.readHandledInvoice(invoiceHandledFile))
			{
				invoiceFile << invoiceFromFile.toXML();
			}
		}

		invoiceFile << _STOP_INVOICE_LIST_XML;
		invoiceHandledFile.close();
		invoiceFile.close();
		break;
	default:
		break;
	}

	return true;
};

bool checkInvoiceFile(std::ifstream& invoiceFile, Controller& programController)
{
	invoiceFile.seekg(0, std::ios::end);
	size_t length = invoiceFile.tellg();

	if (length == 0)
	{
		return false;
	}

	invoiceFile.seekg(0);

	if (!invoiceFile)
	{
		std::ofstream newInvoiceFile{ INVOICES_P_BIN_FILE,std::ios::binary | std::ios::out };
		if (!newInvoiceFile)
		{
			sendErrorMessage(16);
		}
		newInvoiceFile.close();
		return true;
	}
	readInvoiceFile(invoiceFile, programController);
	return true;
};

bool readInvoiceFile(std::ifstream& invoiceFile, Controller& programController)
{
	long int customerID{ 0 };
	long int productID{ 0 };
	bool match{ false };

	Invoice invoiceFromFile{};
	Customer * customer_ptr;
	Tyre tyreFromInvoice;
	Rim  rimFromInvoice;

	std::vector<Product*> placeHolderProducts;

	invoiceFile.seekg(0);

	while (invoiceFromFile.readPendingInvoice(invoiceFile))
	{
		// !! first ALL products + customer from this invoice are created on the heap to create a temporary invoice
		// !! DELETE -> is required to swap the "invoice" products with the "programController" products
		// !! same for the "invoice" customer
		customerID = invoiceFromFile.getCustomer()->getCustomerID();
		// we have to check whether the customer exist/still exist in the program otherwise the whole 
		// invoice is invalid and the pending invoice should be destroyed
		if (programController.checkCustomerExistence(customerID))
		{
			// remember "invoiceFromFile" is just a placeholder until the invoice products and customer are replaced
			// by the products and customer from the "programController" because the "programController" holds all currently possible products and/or customers
			customer_ptr = invoiceFromFile.getCustomer();
			invoiceFromFile.setCustomer(programController.getCustomer(customerID));
			delete customer_ptr;
			// "placeHolderProducts" will hold the products that exist in the "programController"
			placeHolderProducts.clear();
			placeHolderProducts.reserve(invoiceFromFile.getInvoiceProducts().size());

			for (Product* productFromInvoice : invoiceFromFile.getInvoiceProducts())
			{
				// it can be possible that products are deleted so i have to check wether the productID i have read from
				// the invoiceFile is actually a real product in the "programController". (i have already told you this but i am repeating myself)
				productID = productFromInvoice->getProductID();
				// check if product still exists
				if (programController.getProduct(productID)->getProductID() != 0)
				{
					// if exists add to the vector
					placeHolderProducts.push_back(programController.getProduct(productID));
				}
			}

			// afterwards i delete all products in the invoice and replace it with the new vector "placeHolderProducts"
			for (Product* productFromInvoice : invoiceFromFile.getInvoiceProducts())
			{
				delete productFromInvoice;
			}
			invoiceFromFile.setInvoiceProducts(placeHolderProducts);
			programController.setInvoice(invoiceFromFile);

			invoiceFromFile.getInvoiceProductsQuantity().clear();
		}
		else
		{
			// if the customer does NOT exist => destroy the whole invoice along with all it's products and customer
			delete invoiceFromFile.getCustomer();
			invoiceFromFile.getInvoiceProductsQuantity().clear();
			for (Product* productFromInvoice : invoiceFromFile.getInvoiceProducts())
			{
				delete productFromInvoice;
			}
		}
	}

	return true;
};

bool displayPendingInvoice(Controller& programController)
{
	std::cout << CYAN;
	Invoice::displayBriefTableHeaders();
	line(120, '-');
	for (Invoice* invoiceInList : programController.getInvoiceListReference())
	{
		invoiceInList->displayBriefInvoice();
		std::cout << "\n";
	}
	line(120, '-');
	std::cout << RESET_COLOR;

	return true;
};

bool searchHandledInvoices(Controller& programController)
{
	std::ifstream invoiceHandledFile{ INVOICES_H_BIN_FILE,std::ios::binary | std::ios::in };
	Invoice invoiceFromFile;
	Customer customerFromFile;
	size_t sizeInvoicesPrevious_page{ 0 };
	size_t sizeInvoicesCurrent_page{ 0 };
	size_t sizeInvoices{ 0 };
	std::string userInput;
	int rowCount{ 0 };
	int userCase{ 0 };
	int userChoice{ 0 };
	
	bool getInput{ false };
	bool match{ false };

	invoiceFromFile.setCustomer(&customerFromFile);

	if (!invoiceHandledFile)
	{
		std::ofstream newInvoiceHandledFile{ INVOICES_H_BIN_FILE,std::ios::binary | std::ios::out };
		newInvoiceHandledFile.close();
		invoiceHandledFile.close();

		std::cout << RED << "NO HANDLED INVOICES" << RESET_COLOR;
		return false;
	}

	std::cout << HOME_CURSOR << WIPE_SCREEN;
	while (invoiceHandledFile)
	{
		// this means NO RECORDS yet
		// exit the function
		if (invoiceHandledFile.eof() == true && rowCount == 0)
		{
			invoiceHandledFile.close();
			std::cout << RED << "NO HANDLED INVOICES" << RESET_COLOR;
			return false;
		}
		// this means => number of records <= 1 page : case 1
		if (invoiceHandledFile.eof() == true && rowCount <= MAX_ROW_COUNT && rowCount > 0)
		{
			std::cout
				<< VIOLET
				<< "1 |--> show Invoice (ID)\n"
				<< "2 |<-- Back to Invoice Menu\n"
				<< RESET_COLOR;
			userChoice = input(1, 2);
			userCase = 1;
		}
		// this means records > 1 page and begin of file : case 3
		if (invoiceHandledFile.eof() == false && rowCount == MAX_ROW_COUNT)
		{
			std::cout
				<< VIOLET
				<< "1 |--> show Invoice (ID)\n"
				<< "2 |--> next page\n"
				<< "3 |--> Go to end\n"
				<< "4 |<-- Back to Invoice Menu\n"
				<< RESET_COLOR;
			userChoice = input(1, 4);
			userCase = 2;
		}
		// this means recors > 1 page and middle of file : case 4
		if (invoiceHandledFile.eof() == false && rowCount > MAX_ROW_COUNT && rowCount % MAX_ROW_COUNT == 0)
		{
			std::cout
				<< VIOLET
				<< "1 |--> show Invoice (ID)\n"
				<< "2 |--> next page\n" 
				<< "3 |--> previous page\n"
				<< "4 |--> Go to beginning\n"
				<< "5 |--> Go to end\n"
				<< "6 |<-- Back to Invoice Menu\n"
				<< RESET_COLOR;
			userChoice = input(1, 6);
			userCase = 3;
		}
		// this means recors > 1 page and end of file : case 5
		if ((invoiceHandledFile.eof() == true && rowCount > MAX_ROW_COUNT) || (invoiceHandledFile.eof() == true && rowCount > MAX_ROW_COUNT && rowCount % MAX_ROW_COUNT == 0))
		{
			std::cout
				<< VIOLET
				<< "1 |--> show Invoice (ID)\n"
				<< "2 |--> previous page\n"
				<< "3 |--> Go to beginning\n"
				<< "4 |<-- Back to Invoice Menu\n"
				<< RESET_COLOR;
			userChoice = input(1, 6);
			userCase = 4;
		}

		if (userCase != 0)
		{
			handleUseCase(programController, invoiceHandledFile, userCase, userChoice, sizeInvoicesCurrent_page, sizeInvoicesPrevious_page);
			userCase = 0;
			std::cout << HOME_CURSOR << WIPE_SCREEN;
			if (invoiceHandledFile.eof() == true)
			{
				invoiceHandledFile.clear();
				invoiceHandledFile.seekg(sizeInvoices);
			}
		}
		else
		{
			invoiceFromFile.readHandledInvoice(invoiceHandledFile);
			invoiceFromFile.displayBriefInvoice();
			rowCount++;
			sizeInvoicesCurrent_page += invoiceFromFile.getHandledSize();
			sizeInvoices += sizeInvoicesCurrent_page;
			invoiceFromFile.cleanup();
		}
	}


	invoiceHandledFile.close();
	return true;
};

bool handleUseCase(Controller& programController,std::ifstream& inputFile,int& userCase,int& userChoice,size_t& sizeCurrent_page, size_t& sizePrevious_page)
{
	int Counter{ 0 };
	bool match{ false };
	Invoice invoiceFromFile;

	switch (userCase)
	{
	case 1:
		if (userChoice == 1)
		{
			std::cout << "select invoice : ";
			userChoice = input(1, programController.getCurrentInvoiceID());
			// if i want to read all the invoices from the current page i go back by a size of "sizeCurrent_page"
			inputFile.seekg(-(std::streamoff)sizeCurrent_page, std::ios::cur);

			while (!match && inputFile && Counter < MAX_ROW_COUNT)
			{
				invoiceFromFile.readHandledInvoice(inputFile);

				if ((long int)userChoice == invoiceFromFile.getInvoiceID())
				{
					manipulateHandledInvoice(programController, invoiceFromFile);
					inputFile.seekg(0);
					match = true;
				}
				Counter++;
			}
		}

		if (userChoice == 2)
		{
			inputFile.close();
			return false;
		}

		break;
	case 2:

		if (userChoice == 1)
		{
			std::cout << "select invoice : ";
			userChoice = input(1, programController.getCurrentInvoiceID());
			
			inputFile.seekg(-(std::streamoff)sizeCurrent_page, std::ios::cur);

			while (!match && inputFile && Counter < MAX_ROW_COUNT)
			{
				invoiceFromFile.readHandledInvoice(inputFile);

				if ((long int)userChoice == invoiceFromFile.getInvoiceID())
				{
					manipulateHandledInvoice(programController, invoiceFromFile);
					inputFile.seekg(0);
					match = true;
				}
				Counter++;
			}
		}

		if (userChoice == 2)
		{
			// next page
			sizePrevious_page = sizeCurrent_page;
			sizeCurrent_page = 0;
		}

		if (userChoice == 3)
		{
			// Go to end
			inputFile.seekg(0, std::ios::end);
		}

		if (userChoice == 4)
		{
			// Back to Menu
			inputFile.close();
			return false;
		}

		break;
	case 3:

		if (userChoice == 1)
		{
			std::cout << "select invoice : ";
			userChoice = input(1, programController.getCurrentInvoiceID());

 			inputFile.seekg(-(std::streamoff)sizeCurrent_page, std::ios::cur);

			while (!match && inputFile && Counter < MAX_ROW_COUNT)
			{
				invoiceFromFile.readHandledInvoice(inputFile);

				if ((long int)userChoice == invoiceFromFile.getInvoiceID())
				{
					manipulateHandledInvoice(programController, invoiceFromFile);
					inputFile.seekg(0);
					match = true;
				}
				Counter++;
			}
		}

		if (userChoice == 2)
		{
			// next page
			sizePrevious_page = sizeCurrent_page;
			sizeCurrent_page = 0;
		}

		if (userChoice == 3)
		{
			// previous page // go back the size of current page + size of previous page
			inputFile.seekg(-(std::streamoff)(sizeCurrent_page + sizePrevious_page), std::ios::cur);
			sizePrevious_page = sizeCurrent_page;
			sizeCurrent_page = 0;
		}

		if (userChoice == 4)
		{
			// Go to beginning
			inputFile.seekg(0, std::ios::beg);
		}

		if (userChoice == 5)
		{
			// Go to end
			inputFile.seekg(0, std::ios::end);
		}

		if (userChoice == 6)
		{
			inputFile.close();
			return false;
		}

		break;
	case 4:

		if (userChoice == 1)
		{
			std::cout << "select invoice : ";
			userChoice = input(1, programController.getCurrentInvoiceID());

			inputFile.seekg(-(std::streamoff)sizeCurrent_page, std::ios::cur);

			while (!match && inputFile && Counter < MAX_ROW_COUNT)
			{
				invoiceFromFile.readHandledInvoice(inputFile);

				if ((long int)userChoice == invoiceFromFile.getInvoiceID())
				{
					manipulateHandledInvoice(programController, invoiceFromFile);
					inputFile.seekg(0);
				}
				Counter++;
			}
		}

		if (userChoice == 2)
		{
			// previous page // go back the size of current page + size of previous page
			inputFile.seekg(-(std::streamoff)(sizeCurrent_page + sizePrevious_page), std::ios::cur);
			sizePrevious_page = sizeCurrent_page;
			sizeCurrent_page = 0;
		}

		if (userChoice == 3)
		{
			// Go to beginning
			inputFile.seekg(0, std::ios::beg);
		}

		if (userChoice == 4)
		{
			inputFile.close();
			return false;
		}

		break;
	default:
		break;
	}
};

bool searchPendingInvoices(Controller& programController, long int& invoiceID)
{
	bool match{ false };
	long int userChoice{ 0 };
	std::string userInput;
	std::vector<Invoice*> invoiceList = programController.getInvoiceListReference();

	if (programController.getInvoiceList().size() == 0)
	{
		std::cout << RED << "NO PENDING INVOICES" << RESET_COLOR;
		return false;
	}


	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		displayPendingInvoice(programController);
		std::cout
			<< VIOLET
			<< "\nWhat do you wish to do\n"
			<< "1 |--> Select Invoice by ID\n"
			<< "2 |<-- Go back to Invoice Menu\n"
			<< RESET_COLOR;
		userChoice = (long int)input(1, 2);

		switch (userChoice)
		{
		case 1:
			std::cout << HOME_CURSOR << WIPE_SCREEN;
			displayPendingInvoice(programController);
			std::cout
				<< VIOLET
				<< "\nEnter invoice ID " << PINK " [cancel -> 0]\n"
				<< RESET_COLOR;
			userChoice = (long int)input(0, programController.getCurrentInvoiceID());

			if (!programController.checkInvoiceExistence(userChoice))
			{
				std::cout << RED << "\n\tINVALID INVOICE ID\n" << RESET_COLOR;
			}
			else
			{
				match = true;
			}
			break;
		case 2: return false; break;
		default:
			break;
		}
	} while (!match);


	invoiceID = userChoice;
	return true;
};

bool searchPendingInvoices(Controller& programController)
{
	if (programController.getInvoiceList().size() == 0)
	{
		std::cout << RED << "NO PENDING INVOICES" << RESET_COLOR;
		return false;
	}

	std::string userInput;
	std::vector<Invoice*> invoiceList = programController.getInvoiceListReference();
	displayPendingInvoice(programController);

	std::cout
		<< "Select the Invoice ID: \n"
		<< PINK << "[cancel -> (stop)]\n" << RESET_COLOR;
	do
	{
		cursor();
		std::cin >> userInput;
		if (!verifyNumericInput(userInput))
		{
			return false;
		}
	} while (userInput != "stop" || programController.checkInvoiceExistence(std::stoi(userInput)));

	if (userInput == "stop")
	{
		return false;
	}
	long int invoiceID = std::stoi(userInput);

	programController.getInvoice(invoiceID)->displayInvoice();

	return true;
};

bool addProductToInvoice(Controller& programController)
{
	std::string userInput;
	int userChoice{ 0 };
	int quantityToAdd{ 0 };

	Invoice * invoiceFromList;
	Product * productFromStock;

	long int invoiceID{ 0 };
	long int productID{ 0 };

	bool addNewProduct{ true };

	if (!searchPendingInvoices(programController, invoiceID))
	{
		return false;
	}

	invoiceFromList = programController.getInvoice(invoiceID);

	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		invoiceFromList->displayInvoice();

		std::cout
			<< VIOLET
			<< "add product:\n"
			<< "1 |--> from stock \n"
			<< "2 |--> from invoice\n"
			<< "3 |<-- Back to Invoice Menu\n"
			<< RESET_COLOR;

		userChoice = input(1, 3);

		switch (userChoice)
		{
		case 1: addNewProduct = true; break;
		case 2: addNewProduct = false; break;
		case 3: return false; break;
		default:
			return false;
			break;
		}

		if (addNewProduct)
		{
			if (!searchProduct(programController.getProductListReference(), productID))
			{
				return false;
			}
		}

		if (!addNewProduct)
		{
			if (!searchProduct(invoiceFromList->getInvoiceProducts(), productID))
			{
				return false;
			}
		}
		
		productFromStock = programController.getProduct(productID);

		if (productFromStock->getType() == ProductType::Tyre)
		{
			std::cout
				<< VIOLET
				<< "Do you want to add:\n"
				<< "1 |--> a piece (1)\n"
				<< "2 |--> a set   (2)\n"
				<< "3 |--> a set   (4)\n"
				<< "4 |--> Go Back to Invoices\n"
				<< RESET_COLOR;

			userChoice = input(1, 4);

			switch (userChoice)
			{
			case 1: quantityToAdd = 1; break;
			case 2: quantityToAdd = 2; break;
			case 3: quantityToAdd = 4; break;
			case 4: return false; break;
			default:
				return false;
				break;
			}
		}

		if (productFromStock->getType() == ProductType::Rim)
		{
			quantityToAdd = 4;
		}

		if (productFromStock->getQuantity() < quantityToAdd)
		{
			std::cout << RED << "NOT ENOUGH PRODUCT LEFT IN STOCK" << RESET_COLOR;
		}
		else
		{
			invoiceFromList->setProduct(productFromStock, quantityToAdd);
			addNewProduct = true;
		}

	} while (addNewProduct);

	return true;
};

bool removeProductFromInvoice(Controller& programController)
{
	std::string userInput;
	int userChoice{ 0 };
	
	Invoice * invoiceFromList;
	Product * productFromInvoice;

	std::vector<Product*>* productListFromInvoice;
	std::vector<Product*>::iterator iterator;

	long int invoiceID{ 0 };
	long int productID{ 0 };

	bool match{ false };

	if (!searchPendingInvoices(programController, invoiceID))
	{
		return false;
	}

	invoiceFromList = programController.getInvoice(invoiceID);

	if (invoiceFromList->getInvoiceProducts().size() == 0)
	{
		std::cout << RED << "INVOICE IS EMPTY : NO PRODUCTS ADDED\n" << RESET_COLOR;
		return true;
	}

	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		invoiceFromList->displayInvoice();
		std::cout
			<< VIOLET
			<< "What do you wish to do ?\n"
			<< "1 |--> Empty whole invoice\n"
			<< "2 |--> Remove product from invoice\n"
			<< "3 |<-- Cancel\n"
			<< RESET_COLOR;
		userChoice = input(1, 3);

		if (userChoice == 1)
		{
			std::cout
				<< "Are you sure you wish to empty the whole product list from this invoice ?\n"
				<< "y : yes\n"
				<< "n : no\n";
			userInput = input("y", "n");

			if (userInput == "y")
			{
				invoiceFromList->getInvoiceProducts().clear();
				invoiceFromList->getInvoiceProductsQuantity().clear();

				std::cout << GREEN << "ALL PRODUCT HAVE BEEN DELETED" << RESET_COLOR;
				return true;
			}
			else
			{
				match = false;
			}
		}

		if (!searchProduct(invoiceFromList->getInvoiceProducts(), productID))
		{
			std::cout << RED << "NO PRODUCT FOUND" << RESET_COLOR;
			match = false;
		}
		
		if(match)
		{
			productFromInvoice = programController.getProduct(productID);
			
			std::cout << HOME_CURSOR << WIPE_SCREEN;
			line(100, '-');
			Product::displayTableHeaders();
			line(100, '-');
			productFromInvoice->Product::displayTableRow();
			
			std::cout
				<< "1 |--> remove all\n"
				<< "2 |--> remove X\n"
				<< "3 |<-- Back to Invoices\n";

			userChoice = input(1,3);

			size_t index{ 0 };
			switch (userChoice)
			{
			case 1:
				std::cout
					<< "Are you sure you wish to delete this product from this invoice ?\n"
					<< "y : yes\n"
					<< "n : no\n";
				userInput = input("y", "n");

				if (userInput == "y")
				{
					productListFromInvoice = &invoiceFromList->getInvoiceProducts();
					iterator = productListFromInvoice->begin();

					while (iterator != productListFromInvoice->end() && match == false)
					{
						if ((*iterator)->getProductID() == productFromInvoice->getProductID())
						{
							iterator = productListFromInvoice->erase(iterator);
							match = true;
						}
						else
						{
							iterator++;
						}
					}
				}


				break;
			case 2:

				productListFromInvoice = &invoiceFromList->getInvoiceProducts();
				iterator = productListFromInvoice->begin();

				while (iterator != productListFromInvoice->end() && match == false)
				{
					if ((*iterator)->getProductID() == productFromInvoice->getProductID())
					{
						iterator = productListFromInvoice->erase(iterator);
						match = true;
					}
					else
					{
						iterator++;
					}
				}
				
				index = std::distance(productListFromInvoice->begin(), iterator);

				std::cout << "Enter the quantity you wish to delete " << RED << "[0 ; " << invoiceFromList->getInvoiceProductsQuantity()[index] << " ]" << RESET_COLOR;

				userChoice = input(0, invoiceFromList->getInvoiceProductsQuantity()[index]);

				invoiceFromList->getInvoiceProductsQuantity()[index] -= userChoice;

				break;
			case 3:
				return true;
				break;
			default:
				break;
			}
		}
	} while (userChoice != 3);

	return true;
};

bool addInvoice(Controller& programController)
{
	Invoice newInvoice;
	long int customerID{ 0 };
	if (!searchCustomer(programController, customerID))
	{
		return false;
	}
	newInvoice.setCustomer(programController.getCustomer(customerID));
	programController.setInvoice(newInvoice);

	savePendingInvoicesToBin(programController.getInvoiceListReference());

	std::ofstream idFile{ ID_BIN_FILE,std::ios::binary | std::ios::in | std::ios::out };

	if (idFile)
	{
		programController.writeID(idFile);

		idFile.close();
	}


	std::cout << GREEN << "\n\tNEW INVOICE CREATED\n" << RESET_COLOR;
	return true;
};

bool deleteInvoice(Controller& programController)
{
	std::string userInput;

	if (programController.getInvoiceList().size() == 0)
	{
		std::cout << RED << "NO PENDING INVOICES" << RESET_COLOR;
		return false;
	}

	displayPendingInvoice(programController);

	std::cout 
		<< "Which invoice do you want to delete ?\n"
		<< PINK << "[cancel -> (stop)]\n" << RESET_COLOR;
	do
	{
		cursor();
		std::cin >> userInput;
		if (!verifyNumericInput(userInput))
		{
			return false;
		}
	} while (userInput != "stop" && !programController.checkInvoiceExistence((long)std::stoi(userInput)));

	if (userInput == "stop")
	{
		return false;
	}

	int invoiceID = std::stoi(userInput);

	programController.deleteInvoice(invoiceID);

	savePendingInvoicesToBin(programController.getInvoiceListReference());

	std::cout << GREEN << "INVOICE DELETED" << RESET_COLOR;

	return true;
};

bool processInvoice(Controller& programController)
{
	std::string userInput;
	bool acceptProccessing{ false };

	if (programController.getInvoiceList().size() == 0)
	{
		std::cout << RED << "NO PENDING INVOICES" << RESET_COLOR;
		return false;
	}

	displayPendingInvoice(programController);

	std::cout
		<< "Which invoice do you want to process " 
		<< RED << " [Enter ID number] ?\n"
		<< PINK << "[cancel (stop)]\n" 
		<< RESET_COLOR;
	do
	{
		cursor();
		std::cin >> userInput;
		if (!verifyNumericInput(userInput))
		{
			return false;
		}
	} while (userInput != "stop" && !programController.checkInvoiceExistence(std::stoi(userInput)));

	if (userInput == "stop")
	{
		return false;
	}

	int invoiceID = std::stoi(userInput);

	std::ofstream invoiceHandledFile{ INVOICES_H_BIN_FILE,std::ios::in | std::ios::binary | std::ios::app };

	if (!invoiceHandledFile)
	{
		return false;
	}

	int index{ 0 };

	Invoice* invoice = programController.getInvoice(invoiceID);
	std::vector<Product*> invoiceProducts = invoice->getInvoiceProducts();
	std::vector<Product*>::iterator it_1;
	std::vector<int> invoiceProductsQuantity = invoice->getInvoiceProductsQuantity();
	std::vector<int>::iterator it_2;
	
	for (Product * productFromInvoice : invoiceProducts)
	{
		
		// we can only process a invoice if enough products are left in stock 
		while (productFromInvoice->getQuantity() < invoiceProductsQuantity[index])
		{

			acceptProccessing = false;

			std::cout
				<< RED << "\n\tUNABLE TO PROCESS INVOICE : NOT ENOUGH PRODUCTS LEFT IN STOCK FOR : \n" << RESET_COLOR
				<< productFromInvoice->getName() << "\n"
				<< std::setw(25) << "Quantity in Invoice " << " : " << ORANGE << invoiceProductsQuantity[index] << "\n" << RESET_COLOR
				<< std::setw(25) << "Quantity in Stock " << " : " << CYAN << productFromInvoice->getQuantity() << "\n" << RESET_COLOR;

			std::cout
				<< "\nWhat do you wish to do ?\n"
				<< "s : reduce to " << productFromInvoice->getQuantity() << "\n"
				<< "d : delete product from invoice\n"
				<< "c : cancel\n";

			userInput = input("s", "d", "c");

			switch (userInput[0])
			{
			case 's':
				invoiceProductsQuantity[index] = productFromInvoice->getQuantity();
				break;
			case 'd':
				it_1 = std::next(invoiceProducts.begin(), index);
				it_1 = invoiceProducts.erase(it_1);

				it_2 = std::next(invoiceProductsQuantity.begin(), index);
				it_2 = invoiceProductsQuantity.erase(it_2);
				break;
			case 'c':
				return false;
				break;
			default:
				return false;
				break;
			}

		}
	}

	if (invoice->writeHandledInvoice(invoiceHandledFile))
	{
		std::cout << GREEN << "\n\tINVOICE WAS CORRECTLY HANDLED\n" << RESET_COLOR;
	}

	if (!programController.deleteInvoice(invoiceID))
	{
		std::cout << GREEN << "\n\tINVOICE WAS NOT CORRECTLY DELETED\n" << RESET_COLOR;
	}

	return true;
};

bool manipulateHandledInvoice(Controller& programController, Invoice& handledInvoice)
{
	std::ofstream invoiceFile;
	int userChoice{ 0 };
	long int invoiceID = handledInvoice.getInvoiceID();
	long int customerID = handledInvoice.getCustomer()->getCustomerID();
	std::string fileName{ INVOICE_H_X_FROM_Y(std::to_string(invoiceID),std::to_string(customerID)) };
	std::string userInput;
	std::vector<std::string> invoice_ToString;

	std::cout << HOME_CURSOR << WIPE_SCREEN;

	Invoice::displayTableHeaders();
	handledInvoice.displayInvoice();

	std::cout
		<< "\nWhat do you want to do ?"
		<< "1 |--> export to TXT"
		<< "2 |--> export to BIN"
		<< "3 |--> print to TXT"
		<< "4 |--> Back to search";

	userChoice = input(1, 4);

	switch (userChoice)
	{
	case 1:
		invoiceFile.open(_TXT(fileName),std::ios::out );
		break;
	case 2:
		invoiceFile.open(_BIN(fileName), std::ios::out);
		break;
	case 3:
		// printify
		break;
	case 4:
		break;
	default:
		break;
	}

	invoiceFile.close();
	return true;
};

//	 _______   __                                                      __             ______                                  __      __                               
//	/       \ /  |                                                    /  |           /      \                                /  |    /  |                              
//	$$$$$$$  |$$/   _______   _______   ______   __    __  _______   _$$ |_         /$$$$$$  |__    __  _______    _______  _$$ |_   $$/   ______   _______    _______ 
//	$$ |  $$ |/  | /       | /       | /      \ /  |  /  |/       \ / $$   |        $$ |_ $$//  |  /  |/       \  /       |/ $$   |  /  | /      \ /       \  /       |
//	$$ |  $$ |$$ |/$$$$$$$/ /$$$$$$$/ /$$$$$$  |$$ |  $$ |$$$$$$$  |$$$$$$/         $$   |   $$ |  $$ |$$$$$$$  |/$$$$$$$/ $$$$$$/   $$ |/$$$$$$  |$$$$$$$  |/$$$$$$$/ 
//	$$ |  $$ |$$ |$$      \ $$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |  $$ | __       $$$$/    $$ |  $$ |$$ |  $$ |$$ |        $$ | __ $$ |$$ |  $$ |$$ |  $$ |$$      \ 
//	$$ |__$$ |$$ | $$$$$$  |$$ \_____ $$ \__$$ |$$ \__$$ |$$ |  $$ |  $$ |/  |      $$ |     $$ \__$$ |$$ |  $$ |$$ \_____   $$ |/  |$$ |$$ \__$$ |$$ |  $$ | $$$$$$  |
//	$$    $$/ $$ |/     $$/ $$       |$$    $$/ $$    $$/ $$ |  $$ |  $$  $$/       $$ |     $$    $$/ $$ |  $$ |$$       |  $$  $$/ $$ |$$    $$/ $$ |  $$ |/     $$/ 
//	$$$$$$$/  $$/ $$$$$$$/   $$$$$$$/  $$$$$$/   $$$$$$/  $$/   $$/    $$$$/        $$/       $$$$$$/  $$/   $$/  $$$$$$$/    $$$$/  $$/  $$$$$$/  $$/   $$/ $$$$$$$/  

bool saveDiscounts(Controller& programController)
{
	std::fstream discountFile{ DISCOUNTS_BIN_FILE,std::ios::binary | std::ios::out | std::ios::in };

	if (!discountFile)
	{
		std::cout << RED << "\n\tSOMETHING OCCURRED : COULD NOT OPEN " << DISCOUNTS_BIN_FILE << RESET_COLOR;
		return false;
	}
	Discount * currentDiscount = programController.getDiscount();

	discountFile.read(reinterpret_cast<char*>(&(*currentDiscount)), sizeof(Discount));

	return true;
};

bool checkDiscountFile(std::ifstream& discountFile, Controller& programController)
{
	Discount discount;


	if (!discountFile)
	{
		std::ofstream newDiscountFile{ DISCOUNTS_BIN_FILE,std::ios::binary | std::ios::out };
		if (!newDiscountFile)
		{
			sendErrorMessage(17);
		}

		newDiscountFile.write(reinterpret_cast<const char*>(&discount), sizeof(Discount));

		programController.setDiscount(discount);

		if (newDiscountFile.good() == false)
		{
			sendErrorMessage(18);
		}

		newDiscountFile.close();
		return true;
	}
	
	discountFile.seekg(0,std::ios::end);
	size_t length = discountFile.tellg();
	discountFile.seekg(0);
	if (length == 0)
	{
		programController.setDiscount(discount);
		return false;
	}


	readDiscountFile(discountFile, programController);
	return true;
};

bool readDiscountFile(std::ifstream& discountFile, Controller& programController)
{
	Discount discountFromFile{};
	discountFile.read(reinterpret_cast<char*>(&discountFromFile), sizeof(Discount));
	programController.setDiscount(discountFromFile);

	return true;
};

bool showCurrentDiscounts(Controller& programController)
{
	Controller::discountsList->displayDiscountTable();
	return true;
};

bool showMatchingTable(Controller& programController)
{
	Controller::discountsList->displayMatch_Tyre_Rim();
	return true;
};

bool changeDiscount(Controller& programController)
{
	int userChoice{ 0 };
	int userFlow{ 0 };
	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		programController.getDiscount()->displayDiscountTable();
		std::cout
			<< VIOLET
			<< "Which discount do you wish to change ?\n"
			<< "1 |--> Discount Corporate customers\n"
			<< "2 |--> Discount private customers\n"
			<< "3 |--> Extra Discount private customers\n"
			<< "4 |--> Save Discounts\n"
			<< "5 |<-- Back to Discount Menu\n"
			<< RESET_COLOR;

		userFlow = input(1, 5);

		switch (userFlow)
		{
		case 1:
			std::cout << "\nEnter new discount amount " << PINK << "[0 ; 100]" << RESET_COLOR;
			userChoice = input(0, 100);
			Controller::discountsList->setDiscountCorpCust(userChoice);
			break;
		case 2:
			std::cout << "\nEnter new discount amount " << PINK << "[0 ; 100]" << RESET_COLOR;
			userChoice = input(0, 100);
			Controller::discountsList->setDiscountPrivCust(userChoice);
			break;
		case 3:
			std::cout << "\nEnter new discount amount " << PINK << "[0 ; 100]" << RESET_COLOR;
			userChoice = input(0, 100);
			Controller::discountsList->setDiscountExPrivCust(userChoice);
			break;
		case 4:
			break;
		case 5:
			return false;
			break;
		default:
			break;
		}

	} while (userFlow != 4);

	saveDiscounts(programController);


	return true;
};

bool changeDiscountConditions(Controller& programController)
{
	Discount * discount = programController.getDiscount();
	int userChoice{ 0 };



	std::cout
		<< VIOLET
		<< "What do you want to change ?\n"
		<< "1 |--> Corporate customer sets requirement\n"
		<< "2 |--> Private customer sets requirement\n"
		<< "3 |--> Private customer matching sets requirement\n"
		<< "4 |<-- Back to Discount Menu\n"
		<< RESET_COLOR;

	switch (userChoice)
	{
	case 1:
		std::cout 
			<< "Current requirement : " << discount->getAmountDiscountRequirement_Corp() << " sets"
			<< "\nEnter new required amount " << PINK << "[0 ; 15]" << RESET_COLOR;
		userChoice = input(0, 15);
		Controller::discountsList->setAmountDiscountRequirement_Corp(userChoice);
		break;
	case 2:
		std::cout
			<< "Current requirement : " << discount->getAmountDiscountRequirement_Priv() << " sets"
			<< "\nEnter new required amount " << PINK << "[0 ; 15]" << RESET_COLOR;
		userChoice = input(0, 15);
		Controller::discountsList->setAmountDiscountRequirement_Priv(userChoice);
		break;
	case 3:
		std::cout
			<< "Current requirement : " << discount->getMatchingDiscountRequirement_Priv() << " matching sets"
			<< "\nEnter new required amount " << PINK << "[0 ; 15]" << RESET_COLOR;
		userChoice = input(0, 15);
		Controller::discountsList->setMatchingDiscountRequirement_Priv(userChoice);
		break;
	case 4:
		return false;
		break;
	default:
		break;
	}

	saveDiscounts(programController);
	return true;
};

//	  ______                                                       __             ______                                  __      __                               
//	 /      \                                                     /  |           /      \                                /  |    /  |                              
//	/$$$$$$  |  _______   _______   ______   __    __  _______   _$$ |_         /$$$$$$  |__    __  _______    _______  _$$ |_   $$/   ______   _______    _______ 
//	$$ |__$$ | /       | /       | /      \ /  |  /  |/       \ / $$   |        $$ |_ $$//  |  /  |/       \  /       |/ $$   |  /  | /      \ /       \  /       |
//	$$    $$ |/$$$$$$$/ /$$$$$$$/ /$$$$$$  |$$ |  $$ |$$$$$$$  |$$$$$$/         $$   |   $$ |  $$ |$$$$$$$  |/$$$$$$$/ $$$$$$/   $$ |/$$$$$$  |$$$$$$$  |/$$$$$$$/ 
//	$$$$$$$$ |$$ |      $$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |  $$ | __       $$$$/    $$ |  $$ |$$ |  $$ |$$ |        $$ | __ $$ |$$ |  $$ |$$ |  $$ |$$      \ 
//	$$ |  $$ |$$ \_____ $$ \_____ $$ \__$$ |$$ \__$$ |$$ |  $$ |  $$ |/  |      $$ |     $$ \__$$ |$$ |  $$ |$$ \_____   $$ |/  |$$ |$$ \__$$ |$$ |  $$ | $$$$$$  |
//	$$ |  $$ |$$       |$$       |$$    $$/ $$    $$/ $$ |  $$ |  $$  $$/       $$ |     $$    $$/ $$ |  $$ |$$       |  $$  $$/ $$ |$$    $$/ $$ |  $$ |/     $$/ 
//	$$/   $$/  $$$$$$$/  $$$$$$$/  $$$$$$/   $$$$$$/  $$/   $$/    $$$$/        $$/       $$$$$$/  $$/   $$/  $$$$$$$/    $$$$/  $$/  $$$$$$/  $$/   $$/ $$$$$$$/  

bool addAccount(Controller& programController)
{
	int userFlow{ 0 };
	bool nextCase{ false };

	std::string userInput;
	User newUser; 
	std::ofstream employeeFile;
	std::ofstream idFile;

	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		User::displayTableHeaders();
		line(120, '-');
		newUser.displayTableRow();
		line(120, '-');

		switch (userFlow)
		{
		case 0:
			std::cout << "Enter the user's username" << RED << " [min " << MIN_USERNAME_LENGTH << " characters, NO NUMBERS ALLOWED] :" << RESET_COLOR;

			if (MIN_USERNAME_LENGTH <= userInput.size() && verifyAlphaInput(userInput))
			{
				userInput.copy(newUser.userName, STR_LENGTH);
				newUser.userName[STR_LENGTH - 1] = '\0';
				nextCase = true;
			}

			break;
		case 1:
			std::cout << "Enter the user's password" << RED << " [min " << MIN_PWD_LENGTH << " characters] :" << RESET_COLOR;

			if (MIN_PWD_LENGTH <= userInput.size() && verifyAlphaInput(userInput))
			{
				userInput.copy(newUser.userPassword, STR_LENGTH);
				newUser.userPassword[STR_LENGTH - 1] = '\0';
				nextCase = true;
			}
			
			break;
		case 2:
			std::cout << "Enter the user's privilge level:";

			for (std::pair<PROGRAM_PRIVILGE,std::string> mapItem : User::privilgeLevelMap)
			{
				std::cout << "\n" << PINK << static_cast<int>(mapItem.first) << " -> " << mapItem.second << RESET_COLOR;
			}

			if (verifyNumericInput(userInput) && 0 <= std::stoi(userInput) && std::stoi(userInput) <= User::privilgeLevelMap.size())
			{
				newUser.userPrivilge = static_cast<PROGRAM_PRIVILGE>(std::stoi(userInput));
				nextCase = true;
			}

			break;
		default:
			break;
		}

		if (nextCase)
		{
			userInput = "";
			userFlow++;
			nextCase = false;
		}
		else
		{
			std::cout << "\n[cancel -> (stop)]" << std::endl;
			cursor();
			std::cin >> userInput;
		}

		if ("stop" == userInput)
		{
			return false;
		}

	} while (userFlow < 3);


	std::cout << HOME_CURSOR << WIPE_SCREEN;
	User::displayTableHeaders();
	line(120, '-');
	newUser.displayTableRow();
	line(120, '-');

	std::cout << "\nIs this correct " << PINK << " [y : yes , n : no]:" << RESET_COLOR;

	userInput = input("y", "n");

	if (userInput == "n")
	{
		std::cout << RED << "\n\tCANCELED\n" << RESET_COLOR;
		return false;
	}

	employeeFile.open(EMPLOYEES_BIN_FILE,std::ios::out | std::ios::in | std::ios::binary | std::ios::ate);
	idFile.open(ID_BIN_FILE, std::ios::in | std::ios::binary | std::ios::out);

	if (!employeeFile)
	{
		employeeFile.close();
		idFile.close();
		std::cout << RED << "\n\tFAILED TO OPEN FILE " << EMPLOYEES_BIN_FILE << "\n" << RESET_COLOR;
		return false;
	}

	if (!idFile)
	{
		employeeFile.close();
		idFile.close();
		std::cout << RED << "\n\tFAILED TO OPEN FILE " << ID_BIN_FILE << "\n" << RESET_COLOR;
		return false;
	}

	newUser.userID = programController.getCurrentUserID();

	programController.setUser(newUser);

	employeeFile.write(reinterpret_cast<const char*>(&newUser), sizeof(User));
	
 	programController.writeID(idFile);

	employeeFile.close();
	idFile.close();
	std::cout << GREEN << "\n\tNEW USER CREATED\n" << RESET_COLOR;
	return true;
};

bool deleteAccount(Controller& programController)
{
	long int userChoice{ 0 };
	bool match{ false };
	User userFromFile;
	User currentUser = programController.getCurrentUser();
	std::string userInput;
	std::vector<User> allUsersFromFile;
	std::fstream employeeFile{EMPLOYEES_BIN_FILE , std::ios::binary | std::ios::out | std::ios::in };

	if (!employeeFile)
	{
		employeeFile.close();
		std::cout << RED << "\n\tFAILED TO OPEN FILE " << EMPLOYEES_BIN_FILE << "\n" << RESET_COLOR;
		return false;
	}

	while (employeeFile.eof() == false)
	{
		if (userFromFile.userID != 0 && userFromFile.userID != currentUser.userID)
		{
			allUsersFromFile.push_back(userFromFile);
		}
		employeeFile.read(reinterpret_cast<char*>(&userFromFile), sizeof(User));
	}

	employeeFile.clear();

	if (allUsersFromFile.size() == 0)
	{
		std::cout << RED << "\n\tNO OTHER USERS FOUND\n" << RESET_COLOR;
		return false;
	}

	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		showList(allUsersFromFile);

		std::cout << "Which account do you want to delete ? " << PINK << " [Enter ID , cancel -> 0]:\n"  << RESET_COLOR;
		userChoice = (long int)input(0, programController.getCurrentUserID());

		if (userChoice == 0)
		{
			std::cout << RED << "\n\tCANCELED\n" << RESET_COLOR;
			employeeFile.close();
			return false;
		}

		for (int i = 0; i < allUsersFromFile.size(); i++)
		{
			if (userChoice == allUsersFromFile[i].userID)
			{
				userFromFile = allUsersFromFile[i];
				match = true;
			}
		}


		if (!match)
		{
			std::cout << RED << "\n\tNO RECORD FOUND MATCHING ID " << userChoice << "\n" << RESET_COLOR;
			std::cout
				<< "What do you wish to do ?\n"
				<< "1 |--> search again\n"
				<< "2 |<-- cancel\n";

			userChoice = input(1, 2);

			if (userChoice == 2)
			{
				employeeFile.close();
				return false;
			}
		}
	} while (match == false);


	if (match)
	{
		User emptyUser;

		std::cout << HOME_CURSOR << WIPE_SCREEN;
		std::cout << CYAN;
		User::displayTableHeaders();
		line(120, '-');
		userFromFile.displayTableRow();
		line(120, '-');
		std::cout << RESET_COLOR;

		std::cout 
			<< "Confirm by entering this user's ID\n"
			<< PINK << "[cancel -> 0]" << RESET_COLOR;
		userChoice = (long int)input(0, programController.getCurrentUserID());

		if (userChoice == 0)
		{
			std::cout << RED << "\n\tCANCELED\n" << RESET_COLOR;
			employeeFile.close();
			return false;
		}
		
		size_t position{ 0 };
		employeeFile.seekg(0);
		employeeFile.clear();

		if (userChoice == userFromFile.userID)
		{
			do
			{
				employeeFile.read(reinterpret_cast<char*>(&userFromFile), sizeof(User));
				position += sizeof(User);
			} while (userChoice != userFromFile.userID && employeeFile.eof() == false);
		}

		employeeFile.seekp(0);
		employeeFile.clear();

		if (userChoice == userFromFile.userID)
		{
			position = position - sizeof(User);
			employeeFile.seekp(position, std::ios::beg);
			employeeFile.write(reinterpret_cast<const char*>(&emptyUser), sizeof(User));

			if (!employeeFile)
			{
				std::cout << RED << "\n\tERROR WRITING TO FILE\n" << RESET_COLOR;
				employeeFile.close();
				return false;
			}

			std::cout << GREEN << "\n\tUSER DELETED\n" << RESET_COLOR;
		}
		else
		{
			std::cout << RED << "\n\tFAILED TO DELETE : USER RECORD MISMATCH\n" << RESET_COLOR;
		}
	}

	employeeFile.close();
	
	return true;
};

bool updateAccount(Controller& programController)
{

	int userChoice{ 0 };
	std::fstream employeeFile;
	std::string userInput;
	User currentUser = programController.getCurrentUser();

	do
	{
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		User::displayTableHeaders();
		line(120, '-');
		currentUser.displayTableRow();
		line(120, '-');

		switch (userChoice)
		{
		case 1:
			break;
		case 2:
			std::cout << HOME_CURSOR << WIPE_SCREEN;
			return false;
			break;
		case 3:
			std::cout << "Enter the user's new username" << RED << " [min " << MIN_USERNAME_LENGTH << " characters, NO NUMBERS ALLOWED] :" << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (MIN_USERNAME_LENGTH <= userInput.size() && verifyAlphaInput(userInput))
			{
				userInput.copy(currentUser.userName, STR_LENGTH);
				currentUser.userName[STR_LENGTH - 1] = '\0';
				userChoice = 0;
			}
			break;
		case 4:
			std::cout << "Enter the user's new password" << RED << " [min " << MIN_PWD_LENGTH << " characters] :" << RESET_COLOR;
			cursor();
			std::cin >> userInput;
			if (MIN_PWD_LENGTH <= userInput.size() && verifyAlphaInput(userInput))
			{
				userInput.copy(currentUser.userPassword, STR_LENGTH);
				currentUser.userPassword[STR_LENGTH - 1] = '\0';
				userChoice = 0;
			}
			break;
		default:
			std::cout
				<< VIOLET
				<< "What do you wish to update ?\n"
				<< "1 |--> Save\n"
				<< "2 |--> Cancel\n"
				<< "3 |--> change username\n"
				<< "4 |--> change password\n"
				<< RESET_COLOR;
			userChoice = input(1, 4);
			
			break;
		}
	} while (userChoice != 1);

	employeeFile.open(EMPLOYEES_BIN_FILE, std::ios::binary | std::ios::out | std::ios::in );
	User userFromFile;

	if (!employeeFile)
	{
		employeeFile.seekg((currentUser.userID - 1) * sizeof(User));
		employeeFile.read(reinterpret_cast<char*>(&userFromFile), sizeof(User));
		if (userFromFile.userID == currentUser.userID)
		{
			employeeFile.seekp((currentUser.userID - 1) * sizeof(User));
			employeeFile.write(reinterpret_cast<const char*>(&currentUser), sizeof(User));
		}
		else
		{
			std::cout << RED << "\n\tRECORD MISMATCH\n" << RESET_COLOR;
			return false;
		}
	}

	return true;
};
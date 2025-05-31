#include "../headers/Controller.h"

Controller::Controller()
{
	std::string("").copy(currentUser.userName, STR_LENGTH - 1);
	std::string("").copy(currentUser.userPassword, STR_LENGTH - 1);
	currentUser.userPrivilge = PROGRAM_PRIVILGE::USER;
};

void Controller::setInvoice(Invoice& newInvoice)
{
	bool match{ false };
	for (int i = 0; i < invoicesList.size(); i++)
	{
		if (newInvoice.getInvoiceID() == invoicesList[i]->getInvoiceID())
		{
			*invoicesList[i] = newInvoice;
			match = true;
		}
	}

	if (newInvoice.getInvoiceID() == 0)
	{
		newInvoice.setInvoiceID(currentInvoiceID++);
	}

	if (match == false)
	{
		Invoice* invoice = new Invoice{ newInvoice };
		invoicesList.push_back(invoice);
	}
};

Invoice* Controller::getInvoice(long int invoiceID)
{
	for (int i = 0; i < invoicesList.size(); i++)
	{
		if(invoiceID == invoicesList[i]->getInvoiceID())
		{
			return invoicesList[i];
		}
	}
	Invoice* emptyInvoice{};
	return emptyInvoice;
};

bool Controller::checkInvoiceExistence(long int invoiceID)
{
	for (int i = 0; i < invoicesList.size(); i++)
	{
		if (invoiceID == invoicesList[i]->getInvoiceID())
		{
			return true;
		}
	}
	return false;
};

std::vector<Invoice*>& Controller::getInvoiceListReference()
{
	return invoicesList;
};

std::vector<Invoice*> Controller::getInvoiceList()
{
	return invoicesList;
};

void Controller::setProduct(Product* newProduct)
{
	bool match{ false };

	for (int i = 0; i < productsList.size(); i++)
	{
		if (newProduct->getProductID() == productsList[i]->getProductID())
		{
			*productsList[i] = *newProduct;
			match = true;
			return;
		}
	}

	if (newProduct->getProductID() == 0)
	{
		newProduct->setProductID(currentProductID++);
	}

	if (match == false)
	{
		switch (newProduct->getType())
		{
		case ProductType::Tyre: 
			productsList.push_back( new Tyre{ *(dynamic_cast<Tyre*>(newProduct)) });
			break;
		case ProductType::Rim:  
			productsList.push_back( new Rim{ *(dynamic_cast<Rim*>(newProduct)) });
			break;
		default:
			break;
		}

	}
};

Product* Controller::getProduct(long int productID)
{
	for (int i = 0; i < productsList.size(); i++)
	{
		if(productID == productsList[i]->getProductID())
		{
			return productsList[i];
		}
	}
	Product* emptyProduct{};
	return emptyProduct;
};

bool Controller::checkProductExistence(long int productID)
{
	for (int i = 0; i < productsList.size(); i++)
	{
		if (productID == productsList[i]->getProductID())
		{
			return true;
		}
	}
	return false;
};

std::vector<Product*>& Controller::getProductListReference()
{
	return productsList;
};

std::vector<Product*> Controller::getProductList()
{
	return productsList;
};

void Controller::setCustomer(Customer& newCustomer)
{
	bool match{ false };
	for (int i = 0; i < customersList.size(); i++)
	{
		if (newCustomer.getCustomerID() == customersList[i]->getCustomerID())
		{
			*customersList[i] = newCustomer;
			match = true;
		}
	}

	if (match == false)
	{
		if (newCustomer.getCustomerID() == 0)
		{
			newCustomer.setCustomerID(currentCustomerID++);
		}
		
		Customer* customer = new Customer{ newCustomer };
		
		customersList.push_back(customer);
	}
};

Customer * Controller::getCustomer(long int customerID)
{
	for (int i = 0; i < customersList.size(); i++)
	{
		if (customerID == customersList[i]->getCustomerID())
		{
			return customersList[i];
		}
	}
	Customer* emptyCustomer{};
	return emptyCustomer;
};

bool Controller::checkCustomerExistence(long int customerID)
{
	for (int i = 0; i < customersList.size(); i++)
	{
		if (customerID == customersList[i]->getCustomerID())
		{
			return true;
		}
	}
	return false;
};

std::vector<Customer*>& Controller::getCustomerListReference()
{
	return customersList;
};

std::vector<Customer*> Controller::getCustomerList()
{
	return customersList;
};

void Controller::setDiscount(Discount& newDiscount)
{
	Discount* discount = new Discount{ newDiscount };
	Controller::discountsList = discount;
};

Discount * Controller::getDiscount()
{
	return Controller::discountsList;
};

void Controller::setUser(User& newUser)
{
	newUser.userID = currentUserID++;
};

void Controller::setCurrentUser(User& newUser)
{
	currentUser = newUser;
};

User Controller::getCurrentUser(void)
{
	return currentUser;
};

void Controller::setCurrentCustomerID(long int currentID)
{
	currentCustomerID = currentID;
};

long int Controller::getCurrentCustomerID()
{
	return currentCustomerID;
};

void Controller::setCurrentProductID(long int currentID)
{
	currentProductID = currentID;
};

long int Controller::getCurrentProductID()
{
	return currentProductID;
};

void Controller::setCurrentInvoiceID(long int currentID)
{
	currentInvoiceID = currentID;
};

long int Controller::getCurrentInvoiceID()
{
	return currentInvoiceID;
};

void Controller::setCurrentUserID(long int currentID)
{
	currentUserID = currentID;
};

long int Controller::getCurrentUserID()
{
	return currentUserID;
};

bool Controller::writeID(std::ofstream& outStream)
{
	outStream.write(reinterpret_cast<const char*>(&currentCustomerID), sizeof(long int));
	outStream.write(reinterpret_cast<const char*>(&currentProductID), sizeof(long int));
	outStream.write(reinterpret_cast<const char*>(&currentInvoiceID),sizeof(long int));
	outStream.write(reinterpret_cast<const char*>(&currentUserID), sizeof(long int));
	return true;
};

bool Controller::readID(std::ifstream& inStream)
{
	inStream.read(reinterpret_cast<char*>(&currentCustomerID), sizeof(long int));
	inStream.read(reinterpret_cast<char*>(&currentProductID), sizeof(long int));
	inStream.read(reinterpret_cast<char*>(&currentInvoiceID), sizeof(long int));
	inStream.read(reinterpret_cast<char*>(&currentUserID), sizeof(long int));
	return true;
};

bool Controller::deleteCustomer(long int customerID)
{
	for (auto iterator = customersList.begin(); iterator != customersList.end(); iterator++)
	{
		if (customerID == (*iterator)->getCustomerID())
		{
			Customer* customer_p = *iterator;
			customersList.erase(iterator);
			delete customer_p;
			return true;
		}
	}
	return false;
};

bool Controller::deleteProduct(long int productID)
{
	for (auto iterator = productsList.begin();iterator != productsList.end(); iterator++)
	{
		if (productID == (*iterator)->getProductID())
		{
			Product* product_p = *iterator;
			productsList.erase(iterator);
			delete product_p;
			return true;
		}
	}
	return false;
};

bool Controller::deleteInvoice(long int invoiceID)
{
	for (auto iterator = invoicesList.begin(); iterator != invoicesList.end(); iterator++)
	{
		if (invoiceID == (*iterator)->getInvoiceID())
		{
			Invoice * invoice_p = *iterator;
			invoicesList.erase(iterator);
			delete invoice_p;
			return true;
		}
	}
	return false;
};

Discount * Controller::discountsList{};

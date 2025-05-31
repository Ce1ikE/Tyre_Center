#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

// std C++ libs
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

// custom C++ classes
#include "Rim.h"
#include "Tyre.h"
#include "User.h"
#include "Menu.h"
#include "Product.h"
#include "Customer.h"
#include "Invoice.h"
#include "Discount.h"
#include "TyreCenterHeader.h"

class Controller
{
public:
	Controller();

	void setInvoice(Invoice&);
	Invoice* getInvoice(long int);
	bool checkInvoiceExistence(long int);

	std::vector<Invoice*>& getInvoiceListReference();
	std::vector<Invoice*> getInvoiceList();

	void setProduct(Product*);
	Product* getProduct(long int);
	bool checkProductExistence(long int);
	
	std::vector<Product*>& getProductListReference();
	std::vector<Product*> getProductList();

	void setCustomer(Customer&);
	Customer * getCustomer(long int);
	bool checkCustomerExistence(long int);

	std::vector<Customer*>& getCustomerListReference();
	std::vector<Customer*> getCustomerList();

	void setDiscount(Discount&);
	Discount * getDiscount();
	
	void setCurrentUser(User&);
	User getCurrentUser(void);

	void setCurrentCustomerID(long int);
	long int getCurrentCustomerID();

	void setCurrentProductID(long int);
	long int getCurrentProductID();

	void setCurrentInvoiceID(long int);
	long int getCurrentInvoiceID();

	void setCurrentUserID(long int);
	long int getCurrentUserID();
	void setUser(User&);

	bool readID(std::ifstream&);
	bool writeID(std::ofstream&);

	bool deleteCustomer(long int);
	bool deleteProduct(long int);
	bool deleteInvoice(long int);

	static Discount * discountsList;
private:
	long int currentCustomerID{ 0 };
	long int currentProductID{ 0 };
	long int currentInvoiceID{ 0 };
	long int currentUserID{ 0 };
	std::vector<Invoice*>	invoicesList;
	std::vector<Customer*>	customersList;
	std::vector<Product*>	productsList;
	User currentUser;
};

#endif // CONTROLLER_H!


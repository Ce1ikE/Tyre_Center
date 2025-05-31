#pragma once
#ifndef INVOICE_H
#define INVOICE_H

#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include <fstream>

#include "Discount.h"
#include "Customer.h"
#include "Product.h"
#include "Tyre.h"
#include "Rim.h"

class Invoice
{
public:
	Invoice(); 
	Invoice(Customer);

	void setInvoiceID(long int);
	long int getInvoiceID();
	
	void setDiscount(int);
	int getDiscount(void);

	void setProduct(Product*);
	void setProduct(Product*,int);
	Product* getProduct(long int);
	std::vector<Product*>& getInvoiceProducts(void);
	void setInvoiceProducts(std::vector<Product*>&);

	void setCustomer(Customer*);
	Customer * getCustomer(void);

	void setInvoiceProductQuantity(int);
	std::vector<int>& getInvoiceProductsQuantity(void);

	void displayInvoice(void);
	void displayBriefInvoice(void);

	size_t getHandledSize(void);
	size_t getPendingSize(void);

	bool writePendingInvoice(std::ofstream&);
	bool readPendingInvoice(std::ifstream&);

	bool writeHandledInvoice(std::ofstream&);
	bool readHandledInvoice(std::ifstream&);
	
	std::vector<std::string> toString(void);

	std::string toXML();

	Invoice& operator+=(Tyre&);
	Invoice& operator-=(Tyre&);
	Invoice& operator+=(Rim&);
	Invoice& operator-=(Rim&);

	static void displayTableHeaders(void);
	static void displayBriefTableHeaders(void);

	int calculatePrice(); 
	int calculateDiscount();

	void cleanup(Customer*, std::vector<Product*>&);
	void cleanup(void);
private:
	long int invoiceID{ 0 };
	Customer * invoiceCustomer{};
	std::vector<Product*> invoiceProducts{};
	std::vector<int> invoiceProductsQuantity;
	int discount{ 0 };
	int Totalprice{ 0 };

};

#endif // INVOICE_H!



#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include "TyreCenterHeader.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>

enum class ProductType
{
	Tyre = 1,
	Rim
};

enum class SpeedIndex
{
	A1 = 1, A2, A3, A4, A5, A6,
	A7, A8, B, C, D, E,
	F, G, J, K, L, M,
	N, P, Q, R, S, T,
	H, V, W, Y, VR, ZR,
};

enum class RimMaterial
{
	STEEL = 1, ALUMINIUM
};

class Product
{
public:
	Product();
	Product(ProductType,std::string,std::string,int,int,int);
	virtual ~Product() {};

	void setProductID(long int);
	long int getProductID();

	ProductType getType(void);
	void setType(ProductType);

	std::string getName();
	void setName(std::string);

	std::string getManufacturer();
	void setManufacturer(std::string);

	int getDiameter();
	void setDiameter(int);

	int getQuantity();
	void setQuantity(int);

	int getPrice();
	void setPrice(int);


	virtual void setWidth(int) = 0;
	virtual int getWidth() = 0;
	virtual Product* clone() = 0;
	virtual std::string toXML(void) = 0;
	virtual void displayTableRow(void);
	virtual bool write(std::ofstream&);
	virtual bool read(std::ifstream&);
	virtual std::vector<std::string> toString(void);
	virtual void fromString(std::vector<std::string>);

	Product& operator+=(unsigned int);
	Product& operator-=(unsigned int);
	
	static void displayTableHeaders(void);
	static std::vector<std::string> csvHeaders(void);
	static size_t getSize(void);
	static std::map<ProductType, std::string, std::less<ProductType>>  productTypeMap;

private:
	long int productID{ 0 };
	char name[STR_LENGTH] = "";
	char manufacturer[STR_LENGTH] = "";
	int diameter{ 0 };
	int quantity{ 0 };
	int price{ 0 }; 
	ProductType productType{ProductType::Tyre};
};

#endif // PRODUCT_H !




#pragma once
#ifndef TYRE_H
#define TYRE_H

#include "Product.h"

class Tyre : public Product
{
public:
	Tyre(ProductType, std::string ,std::string, int, int, int,SpeedIndex,std::string,int,int);
	Tyre();
	virtual ~Tyre() {};

	void setSpeedIndex(SpeedIndex);
	SpeedIndex getSpeedIndex();

	void setTyreMarkings(std::string);
	std::string getTyreMarkings();

	void setHeight(int);
	int getHeight();

	virtual int getWidth() override;
	virtual void setWidth(int) override;
	
	// allows us to get a pointer with the current attributes  
	virtual Product* clone() override;
	
	// this function allows me to display the attributes 
	// of the object in a formatted way 
	virtual void displayTableRow(void) override;

	// allows me to write the object to a binary file MANUALLY
	// and to read from that binary file
	virtual bool write(std::ofstream&) override;
	virtual bool read(std::ifstream&) override;
	
	// converts all attributes of the object to strings in order to write them to a human readable file
	// and reconverts all attributes from string to the correct data type when read from a human readable file
	virtual std::vector<std::string> toString(void) override;
	virtual void fromString(std::vector<std::string>) override;
	// coordinates with the "toString" member function, to allow me to add "tags" around the attributes
	// such that it can be written to a XML file
	virtual std::string toXML(void) override;

	// all standard headers and maps shared across all the "Tyre" objects 
	static void displayTableHeaders(void);
	static std::vector<std::string> csvHeaders(void);
	static size_t getSize(void);
	static std::map<SpeedIndex, std::string, std::less<SpeedIndex>>  speedIndexMap;

private:
	int width{ 0 };
	int height{ 0 };
	char tyreMarkings[STR_LENGTH] = "";
	SpeedIndex speedIndex{ SpeedIndex::A1 };
};

#endif // TYRE_H !


#pragma once
#ifndef RIM_H
#define RIM_H

#include "Product.h"

class Rim : public Product
{
public:
	Rim(ProductType, std::string,std::string, int, int, int,RimMaterial,std::string,int);
	Rim();
	virtual ~Rim() {};

	void setRimMaterial(RimMaterial);
	RimMaterial getRimMaterial();


	void setColor(std::string);
	std::string getColor(void);
	
	virtual int getWidth(void) override;
	virtual void setWidth(int) override;
	virtual Product* clone() override;
	virtual void displayTableRow(void) override;
	virtual bool write(std::ofstream&) override;
	virtual bool read(std::ifstream&) override;
	virtual std::vector<std::string> toString(void) override;
	virtual void fromString(std::vector<std::string>) override;
	virtual std::string toXML(void) override;

	static void displayTableHeaders(void);
	static std::vector<std::string> csvHeaders(void);
	static size_t getSize(void);
	static std::map<RimMaterial, std::string, std::less<RimMaterial>> materialMap;

private:
	int width{ 0 };
	RimMaterial material{RimMaterial::STEEL};
	char color[STR_LENGTH] = "";
};

#endif // RIM_H !


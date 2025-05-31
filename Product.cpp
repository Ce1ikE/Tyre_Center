#include "Product.h"

Product::Product()
{

};

Product::Product(ProductType newProductType,std::string newManufacturer,std::string newProductName, int newDiameter, int newQuantity, int newPrice)
{
	this->setType(newProductType);
	this->setManufacturer(newManufacturer);
	this->setName(newProductName);
	this->setDiameter(newDiameter);
	this->setQuantity(newQuantity);
	this->setPrice(newPrice);
};

void Product::setProductID(long int newProductID)
{
	productID = newProductID;
};

long int Product::getProductID()
{
	return productID;
};

ProductType Product::getType(void)
{
	return productType;
};

void Product::setType(ProductType newProductType)
{
	productType = newProductType;
};

std::string Product::getName()
{
	return std::string(name);
};

void Product::setName(std::string newName)
{
	size_t length{ newName.size() };
	length = (length < STR_LENGTH ? length : STR_LENGTH - 1);
	newName.copy(name, length);
	name[length] = '\0';
};

std::string Product::getManufacturer()
{
	return std::string(manufacturer);
};

void Product::setManufacturer(std::string newManufacturer)
{
	size_t length{ newManufacturer.size() };
	length = (length < STR_LENGTH ? length : STR_LENGTH - 1);
	newManufacturer.copy(manufacturer, length);
	manufacturer[length] = '\0';
};

int Product::getDiameter()
{
	return diameter;
};

void Product::setDiameter(int newDiameter)
{
	if (newDiameter < 0)
	{
		newDiameter = 0;
	}
	diameter = newDiameter;
};

int Product::getQuantity()
{
	return quantity;
};

void Product::setQuantity(int newQuantity)
{
	if (newQuantity < 0)
	{
		newQuantity = 0;
	}
	quantity = newQuantity;
};

int Product::getPrice()
{
	return price;
};

void Product::setPrice(int newPrice)
{
	price = newPrice;
};

void Product::setWidth(int)
{
	
};

int Product::getWidth()
{
	return 0;
};

std::vector<std::string> Product::csvHeaders(void)
{
	std::vector<std::string> productCSV;	
	
	productCSV.push_back(std::string("productID"));
	productCSV.push_back(std::string("productName"));
	productCSV.push_back(std::string("productManufacturer"));
	productCSV.push_back(std::string("productDiameter"));
	productCSV.push_back(std::string("productQuantity"));
	productCSV.push_back(std::string("productPrice"));

	return productCSV;
};

void Product::displayTableHeaders(void) 
{
	std::cout
		<< std::right 
		<< std::setw(5) << "id |"
		<< std::setw(5) << "type |"
		<< std::setw(20) << "name |"
		<< std::setw(20) << "manufacturer |"
		<< std::setw(10) << "diameter |"
		<< std::setw(15) << "quantity |"
		<< std::setw(10) << "price |";
};

void Product::displayTableRow(void)
{
	std::cout 
		<< std::setw(5)  << productID
		<< std::setw(5)  << productTypeMap[productType].substr(0,4)
		<< std::setw(20) << std::string(name).substr(0, 19)
		<< std::setw(20) << std::string(manufacturer).substr(0, 19)
		<< std::setw(10) << diameter
		<< std::setw(15) << quantity
		<< std::setw(10) << price;
};

size_t Product::getSize(void)
{
	return (sizeof(long int) + sizeof(char[STR_LENGTH]) + sizeof(char[STR_LENGTH]) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int));
};

Product& Product::operator+=(unsigned int productQuantityToAdd)
{
	quantity += productQuantityToAdd;
	return *this;
};

Product& Product::operator-=(unsigned int productQuantityToSubtract)
{
	quantity += productQuantityToSubtract;
	return *this;
};

bool Product::write(std::ofstream& outStream)
{
	int product_T{ static_cast<int>(productType) };

	outStream.write(reinterpret_cast<const char*>(&productID), sizeof(long int));
	outStream.write(reinterpret_cast<const char*>(&product_T), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&name), sizeof(char[STR_LENGTH]));
	outStream.write(reinterpret_cast<const char*>(&manufacturer), sizeof(char[STR_LENGTH]));
	outStream.write(reinterpret_cast<const char*>(&diameter), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&quantity), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&price), sizeof(int));
	if (outStream.good() == false)
	{
		return false;
	}
	return true;
};

bool Product::read(std::ifstream& inStream)
{
	int product_T{0};

	inStream.read(reinterpret_cast<char*>(&productID), sizeof(long int));
	inStream.read(reinterpret_cast<char*>(&product_T), sizeof(int));
	inStream.read(reinterpret_cast<char*>(&name), sizeof(char[STR_LENGTH]));
	inStream.read(reinterpret_cast<char*>(&manufacturer), sizeof(char[STR_LENGTH]));
	inStream.read(reinterpret_cast<char*>(&diameter), sizeof(int));
	inStream.read(reinterpret_cast<char*>(&quantity), sizeof(int));
	inStream.read(reinterpret_cast<char*>(&price), sizeof(int));

	productType = static_cast<ProductType>(product_T);
	return true;
};

std::vector<std::string> Product::toString(void)
{
	std::vector<std::string> product_V;

	product_V.reserve(7);

	product_V.push_back(std::to_string(productID));
	product_V.push_back(productTypeMap[productType]);
	product_V.push_back(std::string(name));
	product_V.push_back(std::string(manufacturer));
	product_V.push_back(std::to_string(diameter));
	product_V.push_back(std::to_string(quantity));
	product_V.push_back(std::to_string(price));

	return product_V;
};

void Product::fromString(std::vector<std::string> product_V)
{

	setProductID(std::stoi(product_V.at(0)));
	
	auto result = std::find_if(
		productTypeMap.begin(), 
		productTypeMap.end(), 
		[&](const std::pair<ProductType, std::string>& pair) { 
			return pair.second == product_V.at(1); 
		});
	if (result != std::end(productTypeMap))
	{
		setType(result->first);
	}

	setName(product_V.at(2));
	setManufacturer(product_V.at(3));
	setDiameter(std::stoi(product_V.at(4)));
	setQuantity(std::stoi(product_V.at(5)));
	setPrice(std::stoi(product_V.at(6)));
};

std::map<ProductType, std::string, std::less<ProductType>>  Product::productTypeMap
{
	{ProductType::Tyre, std::string("Tyre")},
	{ProductType::Rim,  std::string("Rim")},
};

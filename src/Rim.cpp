#include "../headers/Rim.h"

Rim::Rim()
{

};

Rim::Rim(ProductType newProductType, std::string newManufacturer, std::string newProductName, int newDiameter, int newQuantity, int newPrice,RimMaterial newRimMaterial,std::string newColor,int newWidth)
	:Product::Product(newProductType, newManufacturer,newProductName, newDiameter, newQuantity, newPrice)
{
	this->setRimMaterial(newRimMaterial);
	this->setColor(newColor);
	this->setWidth(newWidth);
};

void Rim::setRimMaterial(RimMaterial newMaterial)
{
	material = newMaterial;
};

RimMaterial Rim::getRimMaterial()
{
	return material;
};

void Rim::setColor(std::string newColor)
{
	size_t length{ newColor.size() };
	length = (length < STR_LENGTH ? length : STR_LENGTH - 1);
	newColor.copy(color, length);
	color[length] = '\0';
};

std::string Rim::getColor()
{
	return color;
};

void Rim::setWidth(int newWidth)
{
	width = newWidth;
};

int Rim::getWidth()
{
	return width;
};

Product* Rim::clone()
{
	return new Rim(*this);
};

void Rim::displayTableHeaders(void)
{
	Product::displayTableHeaders();
	std::cout
		<< std::setw(15) << "rim material |"
		<< std::setw(15) << "color |"
		<< std::setw(5) << "rim width |";
};

std::vector<std::string> Rim::csvHeaders(void)
{
	std::vector<std::string> rimCSV;

	rimCSV.insert(rimCSV.begin(), Product::csvHeaders().begin(), Product::csvHeaders().end());
	rimCSV.push_back(std::string("productWidth"));
	rimCSV.push_back(std::string("productMaterial"));
	rimCSV.push_back(std::string("productColor"));

	return rimCSV;
};

void Rim::displayTableRow(void)
{
	Product::displayTableRow();
	std::cout
		<< std::setw(15) << materialMap[material].substr(0,14)
		<< std::setw(15) << std::string(color).substr(0,14)
		<< std::setw(5) << width;

};

size_t Rim::getSize(void)
{
	return (Product::getSize() + sizeof(int) + sizeof(int) + sizeof(char[STR_LENGTH]));
};

bool Rim::write(std::ofstream& outStream)
{
	Product::write(outStream);
	int rimMaterial{static_cast<int>(material)};
	
	outStream.write(reinterpret_cast<const char*>(&width), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&rimMaterial), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&color), sizeof(char[STR_LENGTH]));

	if (outStream.good() == false)
	{
		return false;
	}
	return true;
};

bool Rim::read(std::ifstream& inStream)
{
	Product::read(inStream);
	int rimMaterial{0};
	
	inStream.read(reinterpret_cast<char*>(&width), sizeof(int));
	inStream.read(reinterpret_cast<char*>(&rimMaterial), sizeof(int));
	inStream.read(reinterpret_cast<char*>(&color), sizeof(char[STR_LENGTH]));

	material = static_cast<RimMaterial>(rimMaterial);

	return true;
};

std::vector<std::string> Rim::toString(void)
{
	std::vector<std::string> rim;

	rim.insert(rim.end(), Product::toString().begin(), Product::toString().end());
	rim.push_back(std::to_string(width));
	rim.push_back(materialMap[material]);
	rim.push_back(std::string(color));

	return rim;
};

std::string Rim::toXML(void)
{
	std::string rim_XML;
	std::vector<std::string> rim_V{ toString() };

	rim_XML = RIM_TO_XML(rim_V);

	return rim_XML;
};

void Rim::fromString(std::vector<std::string> rim_V)
{
	Product::fromString(rim_V);

	auto result = std::find_if(
		materialMap.begin(), 
		materialMap.end(), 
		[&](const std::pair<RimMaterial, std::string>& pair) { 
			return pair.second == rim_V.at(8); 
		});
	
	setWidth(std::stoi(rim_V.at(7)));
	if (result != std::end(materialMap))
	{
		setRimMaterial(result->first);
	}
	setColor(rim_V.at(9));
};

std::map<RimMaterial, std::string, std::less<RimMaterial>> Rim::materialMap
{
	{RimMaterial::STEEL, std::string("Steel")},
	{RimMaterial::ALUMINIUM, std::string("Steel")}
};


#include "Tyre.h"

Tyre::Tyre(ProductType newProductType, std::string newManufacturer,std::string newProductName, int newDiameter, int newQuantity, int newPrice,SpeedIndex newSpeedIndex,std::string newTyreMarkings,int newHeight,int newWidth)
	:Product::Product(newProductType, newManufacturer,newProductName,newDiameter,newQuantity,newPrice)
{
	this->setSpeedIndex(newSpeedIndex);
	this->setTyreMarkings(newTyreMarkings);
	this->setHeight(newHeight);
	this->setWidth(newWidth);
};

Tyre::Tyre()
{

};

void Tyre::setSpeedIndex(SpeedIndex newSpeedIndex)
{
	speedIndex = newSpeedIndex;
};

SpeedIndex Tyre::getSpeedIndex()
{
	return speedIndex;
};

void Tyre::setTyreMarkings(std::string newTyreMarkings)
{
	size_t length{ newTyreMarkings.size() };
	length = (length < STR_LENGTH ? length : STR_LENGTH - 1);
	newTyreMarkings.copy(tyreMarkings, length);
	tyreMarkings[length] = '\0';
};

std::string Tyre::getTyreMarkings()
{
	return tyreMarkings;
};

void Tyre::setHeight(int newHeight)
{
	height = newHeight;
};

int Tyre::getHeight()
{
	return height;
};

void Tyre::setWidth(int newWidth)
{
	width = newWidth;
};

int Tyre::getWidth()
{
	return width;
};

Product* Tyre::clone()
{
	return new Tyre(*this);
};

std::vector<std::string> Tyre::csvHeaders(void)
{
	std::vector<std::string> tyreCSV;

	tyreCSV.insert(tyreCSV.begin(), Product::csvHeaders().begin(), Product::csvHeaders().end());
	tyreCSV.push_back(std::string("productWidth"));
	tyreCSV.push_back(std::string("productSpeedIndex"));
	tyreCSV.push_back(std::string("productHeight"));
	tyreCSV.push_back(std::string("productTyreMarkings"));

	return tyreCSV;
};

void Tyre::displayTableHeaders(void)
{
	Product::displayTableHeaders();
	std::cout
		<< std::setw(15) << "speedindex |"
		<< std::setw(20) << "tyre markings |"
		<< std::setw(15) << "tyre width |";
};

void Tyre::displayTableRow(void)
{
	Product::displayTableRow();
	std::cout
		<< std::setw(15) << Tyre::speedIndexMap[speedIndex].substr(0,14)
		<< std::setw(20) << std::string(tyreMarkings).substr(0,19)
		<< std::setw(15) << width;
};

size_t Tyre::getSize(void)
{
	return (Product::getSize() + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(char[STR_LENGTH]));
};

bool Tyre::write(std::ofstream& outStream)
{
	Product::write(outStream);
	int tyreSpeedIndex{ static_cast<int>(speedIndex) };

	outStream.write(reinterpret_cast<const char*>(&width), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&tyreSpeedIndex), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&height), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&tyreMarkings), sizeof(char[STR_LENGTH]));

	if (outStream.good() == false)
	{
		return false;
	}
	return true;
};

bool Tyre::read(std::ifstream& inStream)
{
	Product::read(inStream);
	int tyreSpeedIndex{0};

	inStream.read(reinterpret_cast<char*>(&width), sizeof(int));
	inStream.read(reinterpret_cast<char*>(&tyreSpeedIndex), sizeof(int));
	inStream.read(reinterpret_cast<char*>(&height), sizeof(int));
	inStream.read(reinterpret_cast<char*>(&tyreMarkings), sizeof(char[STR_LENGTH]));
	
	speedIndex = static_cast<SpeedIndex>(tyreSpeedIndex);
	return true;
};

std::vector<std::string> Tyre::toString(void)
{
	std::vector<std::string> tyre;

	tyre.insert(tyre.end(), Product::toString().begin(), Product::toString().end());
	tyre.push_back(std::to_string(width));
	tyre.push_back(speedIndexMap[speedIndex]);
	tyre.push_back(std::to_string(height));
	tyre.push_back(std::string(tyreMarkings));

	return tyre;
};

std::string Tyre::toXML(void)
{
	std::string tyre_XML;
	std::vector<std::string> tyre_V{ toString() };

	tyre_XML = TYRE_TO_XML(tyre_V);

	return tyre_XML;
};

void Tyre::fromString(std::vector<std::string> tyre_V)
{
	Product::fromString(tyre_V);

	setWidth(std::stoi(tyre_V.at(7)));

	auto result = std::find_if(
		speedIndexMap.begin(), 
		speedIndexMap.end(), 
		[&tyre_V](const std::pair<SpeedIndex, std::string>& pair) { 
			return pair.second == tyre_V.at(8); 
		});
	if (result != speedIndexMap.end())
	{
		setSpeedIndex(result->first);
	}

	setHeight(std::stoi(tyre_V.at(9)));
	setTyreMarkings(tyre_V.at(10));
};


std::map<SpeedIndex, std::string, std::less<SpeedIndex>> Tyre::speedIndexMap = {
		{SpeedIndex::A1, std::string("A1")},
		{SpeedIndex::A2, std::string("A2")},
		{SpeedIndex::A3, std::string("A3")},
		{SpeedIndex::A4, std::string("A4")},
		{SpeedIndex::A5, std::string("A5")},
		{SpeedIndex::A6, std::string("A6")},
		{SpeedIndex::A7, std::string("A7")},
		{SpeedIndex::A8, std::string("A8")},
		{SpeedIndex::B,  std::string("B")},
		{SpeedIndex::C,  std::string("C")},
		{SpeedIndex::D,  std::string("D")},
		{SpeedIndex::E,  std::string("E")},
		{SpeedIndex::F,  std::string("F")},
		{SpeedIndex::G,  std::string("G")},
		{SpeedIndex::J,  std::string("J")},
		{SpeedIndex::K,  std::string("K")},
		{SpeedIndex::L,  std::string("L")},
		{SpeedIndex::M,  std::string("M")},
		{SpeedIndex::N,  std::string("N")},
		{SpeedIndex::P,  std::string("P")},
		{SpeedIndex::Q,  std::string("Q")},
		{SpeedIndex::R,  std::string("R")},
		{SpeedIndex::S,  std::string("S")},
		{SpeedIndex::T,  std::string("T")},
		{SpeedIndex::H,  std::string("H")},
		{SpeedIndex::V,  std::string("V")},
		{SpeedIndex::W,  std::string("W")},
		{SpeedIndex::Y,  std::string("Y")},
		{SpeedIndex::VR, std::string("VR")},
		{SpeedIndex::ZR, std::string("ZR")},
};

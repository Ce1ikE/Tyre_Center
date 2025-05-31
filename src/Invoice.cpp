#include "../headers/Invoice.h"
#include "../headers/TyreCenterHeader.h"
#include "../headers/Controller.h"

Invoice::Invoice()
{

};

Invoice::Invoice(Customer newInvoiceCustomer)
{
	this->setCustomer(&newInvoiceCustomer);
};

void Invoice::setInvoiceID(long int newInvoiceID)
{
	invoiceID = newInvoiceID;
};

long int Invoice::getInvoiceID()
{
	return invoiceID;
};

int Invoice::calculatePrice()
{
	int price{ 0 };

	for (int i = 0; i < invoiceProducts.size(); i++)
	{
		price += invoiceProducts[i]->getPrice() * invoiceProductsQuantity[i];
	}

	if (invoiceCustomer->getCustomerType() == CustomerType::PRIV)
	{
		// exclusive VAT == price/VAT
		price -= (int)((float)(Controller::discountsList->getVAT() / 100) * (float)price);
	}

	if (invoiceCustomer->getCustomerType() == CustomerType::CORP)
	{
		// inclusive VAT == price*VAT
		price += (int)((float)(Controller::discountsList->getVAT() / 100) * (float)price);
	}

	return price;
};

int Invoice::calculateDiscount()
{
	int discount{ 0 };
	// just a variable to keep track of how many sets are present
	int set_Counter{ 0 };
	int match_Counter{ 0 };
	bool match{ false };

	//	Banden worden verkocht per stuk of per set van 2 of 4 stuks, velgen
	//	steeds in sets van 4.
	
	//	Particuliere klanten krijgen een korting
	//	bij aankoop van een set van vier banden en extra korting bij de aankoop van een bijpassende set velgen.
	//  1 set	== 4 banden == 4 tyres
	//  + extra == 4 velgen == 4 rims (rims.manufacturer + rims.diameter == tyres.manufacturer + tyres.diameter)
	if (invoiceCustomer->getCustomerType() == CustomerType::PRIV)
	{
		for (int i = 0; i < invoiceProducts.size(); i++)
		{
			if (invoiceProducts[i]->getType() == ProductType::Tyre && invoiceProductsQuantity[i] >= 4)
			{
				set_Counter++;

				for (int n = 0; n < invoiceProducts.size(); n++)
				{
					// int diameter_r, int diameter_t, int width_r, int width_t
					match = Controller::discountsList->calculateMatch(
						invoiceProducts[n]->getDiameter(), invoiceProducts[i]->getDiameter(), invoiceProducts[n]->getWidth(), invoiceProducts[i]->getWidth());
					if (match)
					{
						match_Counter++;
					}
				}
			}

		}

		if (Controller::discountsList->getAmountDiscountRequirement_Priv() <= set_Counter)
		{
			discount += Controller::discountsList->getDiscountPrivCust();
		}

		if (Controller::discountsList->getMatchingDiscountRequirement_Priv() <= match_Counter)
		{
			discount += Controller::discountsList->getDiscountExPrivCust();
		}
	}


	//  Bedrijfsklanten kunnen een extra korting krijgen bij de aankoop vanaf 10 sets.
	//  1 piece == 1 band   == 1 tyre
	//  1 set	== 2 banden == 2 tyres
	//  of		== 4 banden == 4 tyres
	//  of		== 4 velgen == 4 rims
	if (invoiceCustomer->getCustomerType() == CustomerType::CORP)
	{
		for (int i = 0; i < invoiceProducts.size(); i++)
		{
			if (invoiceProducts[i]->getType() == ProductType::Rim)
			{
				set_Counter++;
			}

			if (invoiceProducts[i]->getType() == ProductType::Tyre && invoiceProductsQuantity[i] / 4)
			{
				set_Counter++;
			}
		}

		if (Controller::discountsList->getAmountDiscountRequirement_Corp() <= set_Counter)
		{
			discount += Controller::discountsList->getDiscountCorpCust();
		}
	}


	return discount;
};

void Invoice::setDiscount(int newDiscount)
{
	discount = newDiscount;
};

int Invoice::getDiscount(void)
{
	return calculateDiscount();
};

void Invoice::setProduct(Product * newProduct)
{
	for (int i = 0; i < invoiceProducts.size(); i++)
	{
		if (newProduct->getProductID() == invoiceProducts[i]->getProductID())
		{
			invoiceProductsQuantity[i] += 1;
			return;
		}
	}
	invoiceProducts.push_back(newProduct);
	invoiceProductsQuantity.push_back(1);
};

void Invoice::setProduct(Product* newProduct,int quantity)
{
	for (int i = 0; i < invoiceProducts.size(); i++)
	{
		if (newProduct->getProductID() == invoiceProducts[i]->getProductID())
		{
			invoiceProductsQuantity[i] += quantity;
			return;
		}
	}
	invoiceProducts.push_back(newProduct);
	invoiceProductsQuantity.push_back(quantity);
};

Product * Invoice::getProduct(long int productID)
{
	for (int i = 0; i < invoiceProducts.size(); i++)
	{
		if (productID == invoiceProducts[i]->getProductID())
		{
			return invoiceProducts[i];
		}
	}
	Product* emptyProduct{};
	return emptyProduct;
};

std::vector<Product*>& Invoice::getInvoiceProducts(void)
{
	return invoiceProducts;
};

void Invoice::setInvoiceProducts(std::vector<Product*>& newProducts)
{
	invoiceProducts = newProducts;
};

void Invoice::setCustomer(Customer * newCustomer)
{
	invoiceCustomer = newCustomer;
};

Customer * Invoice::getCustomer(void)
{
	return invoiceCustomer;
};

void Invoice::setInvoiceProductQuantity(int newQuantity)
{
	invoiceProductsQuantity.push_back(newQuantity);
};

std::vector<int>& Invoice::getInvoiceProductsQuantity(void)
{
	return invoiceProductsQuantity;
};

void Invoice::displayTableHeaders(void)
{
	std::cout << std::right
		<< std::setw(5) << "ID |"
		<< std::setw(15) << "customer ID |"
		<< std::setw(40) << "name |"
		<< std::setw(10) << "type |";
};

void Invoice::displayBriefTableHeaders(void)
{
	std::cout << std::right
		<< std::setw(5) << "ID |"
		<< std::setw(10) << "customer ID |"
		<< std::setw(25) << "customer |"
		<< std::setw(15) << "products |"
		<< std::setw(10) << "price |"
		<< std::setw(15) << "discount |";
};

void Invoice::displayBriefInvoice(void)
{
	std::cout << std::right
		<< std::setw(5) << invoiceID
		<< std::setw(10) << invoiceCustomer->getCustomerID()
		<< std::setw(25) << (invoiceCustomer->getFirstName() + ' ' + invoiceCustomer->getLastName()).substr(0, 24)
		<< std::setw(15) << static_cast<int>(invoiceProducts.size())
		<< std::setw(10) << calculatePrice()
		<< std::setw(15) << calculateDiscount();
};

void Invoice::displayInvoice(void)
{
	std::cout << "\n| " << invoiceID << " |\n";
	std::cout << TXT_COLOR(33);
	line(120, '-');
	Customer::displayTableHeaders();
	line(120, '-');
	invoiceCustomer->displayTableRow();
	line(120, '-');

	std::cout << "\n\n";
	std::cout << TXT_COLOR(203);
	Product::displayTableHeaders();
	line(120, '-');
	for (int i = 0;i < invoiceProducts.size();i++)
	{
		std::cout << "\033[38;5;" << (i + 17) % 230 << "m";
		std::cout
			<< std::setw(5) << invoiceProducts[i]->getProductID()
			<< std::setw(5) << Product::productTypeMap[invoiceProducts[i]->getType()].substr(0, 4)
			<< std::setw(20) << std::string(invoiceProducts[i]->getName()).substr(0, 19)
			<< std::setw(20) << std::string(invoiceProducts[i]->getManufacturer()).substr(0, 19)
			<< std::setw(10) << invoiceProducts[i]->getDiameter()
			<< std::setw(15) << invoiceProductsQuantity[i]
			<< std::setw(10) << invoiceProducts[i]->getPrice()
			<< "\n";
	}
	line(120, '-');
	std::cout << RESET_COLOR;
}

Invoice& Invoice::operator+=(Tyre& newProduct)
{
	setProduct(&newProduct);
	return *this;
};

Invoice& Invoice::operator-=(Tyre& productToRemove)
{
	return *this;
};

Invoice& Invoice::operator+=(Rim& newProduct)
{
	setProduct(&newProduct);
	return *this;
};

Invoice& Invoice::operator-=(Rim& productToRemove)
{
	return *this;
};

size_t Invoice::getHandledSize(void)
{
	size_t byteCounter{ 0 };
	// ID size
	byteCounter += sizeof(long int);
	// Customer size
	byteCounter += invoiceCustomer->getSize();
	// n * (Products size + Quantity Size)
	for (Product* product : invoiceProducts)
	{
		byteCounter += product->getSize();
		byteCounter += sizeof(int);
	}
	// Discount
	byteCounter += sizeof(int);
	// Price
	byteCounter += sizeof(int);
	return byteCounter;
};

size_t Invoice::getPendingSize(void)
{
	size_t byteCounter{ 0 };
	// ID size
	byteCounter += sizeof(long int);
	// Customer ID
	byteCounter += sizeof(long int);
	// n * (Products ID + Quantity Size)
	byteCounter += invoiceProducts.size()*(sizeof(long int) + sizeof(int));
	return byteCounter;
};

std::vector<std::string> Invoice::toString(void)
{
	std::vector<std::string> invoice;

	if (invoiceProductsQuantity.size() != invoiceProducts.size())
	{
		return invoice;
	}

	int discount = calculateDiscount();
	int price = calculatePrice();
	int counter{ 0 };
	
	invoice.push_back(std::to_string(invoiceID));
	invoice.push_back(std::to_string(discount));
	invoice.push_back(std::to_string(price));

	invoice.insert(invoice.end(), invoiceCustomer->toString().begin(), invoiceCustomer->toString().end());
	
	for (Product * productFromInvoice : invoiceProducts)
	{
		invoice.insert(invoice.end(), productFromInvoice->toString().begin(), productFromInvoice->toString().end());
		invoice.push_back(std::to_string(invoiceProductsQuantity[counter++]));
	}

	return invoice;
};

std::string Invoice::toXML(void)
{
	std::string invoice_XML;
	if (invoiceProductsQuantity.size() != invoiceProducts.size())
	{
		return invoice_XML;
	}

	int discount = calculateDiscount();
	int price = calculatePrice();
	int counter{ 0 };

	invoice_XML += _START_INVOICE_XML(std::to_string(invoiceID));

	for (int i = 0; i < invoiceProducts.size(); i++)
	{
		Product* productFromInvoice = invoiceProducts[i]->clone();
		productFromInvoice->setQuantity(invoiceProductsQuantity[i]);
		invoice_XML += productFromInvoice->toXML();
		delete productFromInvoice;
	}

	invoice_XML += "<discount>" + std::to_string(discount) + "</discount>";
	invoice_XML += "<totalprice>" + std::to_string(price - price * (discount/100)) + "</totalprice>";
	invoice_XML += _STOP_INVOICE_XML;
	return invoice_XML;
};

bool Invoice::writePendingInvoice(std::ofstream& outStream)
{
	if (invoiceProductsQuantity.size() != invoiceProducts.size())
	{
		return false;
	}

	size_t invoiceSize_P{ getPendingSize() };
	long int customerID{ invoiceCustomer->getCustomerID() };
	long int productID{ 0 };
	int productType{ 0 };
	int quantity{ 0 };
	int counter{ 0 };

	outStream.write(reinterpret_cast<const char*>(&invoiceSize_P), sizeof(size_t));
	outStream.write(reinterpret_cast<const char*>(&invoiceID), sizeof(long int));
	outStream.write(reinterpret_cast<const char*>(&customerID), sizeof(long int));
	for (Product* productInList : invoiceProducts)
	{
		productID = productInList->getProductID();
		productType = static_cast<int>(productInList->getType());
		quantity = invoiceProductsQuantity[counter++];
		outStream.write(reinterpret_cast<const char*>(&productID), sizeof(long int));
		outStream.write(reinterpret_cast<const char*>(&productType), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(&quantity), sizeof(int));
	}

	return true;
};

bool Invoice::readPendingInvoice(std::ifstream& inStream)
{
	size_t invoiceSize_P{ 0 };
	Customer* customerFromFile;
	long int customerID{ 0 };
	long int productID{ 0 };
	int productType{ 0 };
	int quantity{ 0 };

	// fail early if the read operation fails :)
	if (!inStream.read(reinterpret_cast<char*>(&invoiceSize_P), sizeof(size_t)))
	{
		return false; 
	}

	if (!inStream.read(reinterpret_cast<char*>(&invoiceID), sizeof(long int)))
	{
		return false;
	}

	if (!inStream.read(reinterpret_cast<char*>(&customerID), sizeof(long int)))
	{
		return false;
	}
	
	invoiceSize_P -= sizeof(long int) + sizeof(long int);
	customerFromFile = new Customer;
	customerFromFile->setCustomerID(customerID);
	invoiceCustomer = customerFromFile;

	while (invoiceSize_P >= sizeof(long int) + sizeof(int) + sizeof(int))
	{
		if (!inStream.read(reinterpret_cast<char*>(&productID), sizeof(long int)) ||
			!inStream.read(reinterpret_cast<char*>(&productType), sizeof(int)) ||
			!inStream.read(reinterpret_cast<char*>(&quantity), sizeof(int)))
		{
			cleanup(customerFromFile, invoiceProducts);
			return false;
		}

		switch (static_cast<ProductType>(productType))
		{
		case ProductType::Tyre:
		{
			Tyre* tyreFromFile = new Tyre;
			tyreFromFile->setProductID(productID);
			invoiceProducts.push_back(tyreFromFile);
			break;
		}
		case ProductType::Rim:
		{
			Rim* rimFromFile = new Rim;
			rimFromFile->setProductID(productID);
			invoiceProducts.push_back(rimFromFile);
			break;
		}
		default:
			std::cout << RED << "\nUNKNOWN PRODUCT TYPE: " << productType << "\n" << RESET_COLOR;
			break;
		}

		invoiceSize_P -= sizeof(long int) + sizeof(int) + sizeof(int);
	}

	// final fail check after all reads
	if (inStream.fail())
	{
		cleanup(customerFromFile, invoiceProducts);
		return false;
	}

	return true;
}

void Invoice::cleanup(Customer* customer, std::vector<Product*>& products)
{
	delete customer;
	for (Product* product : products)
	{
		delete product;
	}
	products.clear();
};

void Invoice::cleanup()
{
	delete invoiceCustomer;
	for (Product* product : invoiceProducts)
	{
		delete product;
	}
	invoiceProductsQuantity.clear();
};

bool Invoice::writeHandledInvoice(std::ofstream& outStream)
{
	if (invoiceProductsQuantity.size() != invoiceProducts.size())
	{
		return false;
	}

	size_t invoiceSize_H{ getHandledSize() };
	discount = calculateDiscount();
	Totalprice = calculatePrice();
	int counter{ 0 };
	int quantity{ 0 };
	
	outStream.write(reinterpret_cast<const char*>(&invoiceSize_H), sizeof(size_t));
	outStream.write(reinterpret_cast<const char*>(&invoiceID), sizeof(long int));
	outStream.write(reinterpret_cast<const char*>(&discount), sizeof(int));
	outStream.write(reinterpret_cast<const char*>(&Totalprice), sizeof(int));
	invoiceCustomer->write(outStream);
	for (Product* productInList : invoiceProducts)
	{
		productInList->write(outStream);
		// reduce the quantity in stock by the quantity stored in the invoice
		productInList -= invoiceProductsQuantity[counter];
		quantity = invoiceProductsQuantity[counter];
		outStream.write(reinterpret_cast<const char*>(&quantity), sizeof(int));
		counter++;
	}

	return true;
};

bool Invoice::readHandledInvoice(std::ifstream& inStream)
{
	size_t invoiceSize_H{ 0 };
	size_t offsetSize{ sizeof(long int) + sizeof(int) };
	int counter{ 0 };
	int quantity{ 0 };
	int productType{ 0 };
	long int productID{ 0 };

	invoiceCustomer = new Customer;

	if (!inStream.read(reinterpret_cast<char*>(&invoiceSize_H), sizeof(size_t)) ||
		!inStream.read(reinterpret_cast<char*>(&invoiceID), sizeof(long int)) ||
		!inStream.read(reinterpret_cast<char*>(&discount), sizeof(int)) ||
		!inStream.read(reinterpret_cast<char*>(&Totalprice), sizeof(int)))
	{
		return false;
	}
	invoiceCustomer->read(inStream);
	// invoiceSize - sizeof( invoiceID + discount + price)
	invoiceSize_H -= (std::streamoff)(sizeof(long int) + sizeof(int) + sizeof(int) + invoiceCustomer->getSize());
	// size remaining == (x*Tyre + y*Rim + (x + y) * quantity)
	// EOF - size remaining == begin products 
	while (invoiceSize_H != 0)
	{
		inStream.read(reinterpret_cast<char*>(&productID), sizeof(long int));
		inStream.read(reinterpret_cast<char*>(&productType), sizeof(int));
		inStream.seekg( -(std::streamoff)offsetSize, std::ios::cur);
		// each time we reduce the size of the invoice such that we get closer and closer to the end of the invoice
		Tyre* tyreFromFile;
		Rim* rimFromFile;
		switch (static_cast<ProductType>(productType))
		{
		case ProductType::Tyre:
			tyreFromFile  = new Tyre;
			tyreFromFile->read(inStream);
			invoiceProducts.push_back(tyreFromFile);
			invoiceSize_H -= tyreFromFile->getSize();
			break;
		case ProductType::Rim:
			rimFromFile = new Rim;
			rimFromFile->read(inStream);
			invoiceProducts.push_back(rimFromFile);
			invoiceSize_H -= rimFromFile->getSize();
			break;
		default:
			break;
		}

		inStream.read(reinterpret_cast<char*>(&quantity), sizeof(int));
		invoiceProductsQuantity.push_back(quantity);
	}
	
	return true;
};


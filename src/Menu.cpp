#include "../headers/Menu.h"


////////////////////////////////////////////////////////////////////////

Menu::Menu()
{
	
};

////////////////////////////////////////////////////////////////////////

MenuType Menu::getCurrentMenuType(void)
{
	return currentMenu;
};

void Menu::setCurrentMenuType(MenuType newMenu)
{
	currentMenu = newMenu;
};

////////////////////////////////////////////////////////////////////////

void Menu::setRequest(int newRequest)
{
	switch (currentMenu)
	{
	case MenuType::LOGIN:
		request.currentLoginRequest = (LoginMenuRequest)newRequest;
		break;
	case MenuType::MAIN:
		request.currentMainRequest = (MainMenuRequest)newRequest;
		break;
	case MenuType::CUSTOMER:
		request.currentCustomerRequest = (CustomerMenuRequest)newRequest;
		break;
	case MenuType::PRODUCT:
		request.currentProductRequest = (ProductMenuRequest)newRequest;
		break;
	case MenuType::INVOICE:
		request.currentInvoiceRequest = (InvoiceMenuRequest)newRequest;
		break;
	case MenuType::DISCOUNT:
		request.currentDiscountRequest = (DiscountMenuRequest)newRequest;
		break;
	case MenuType::ACCOUNT:
		request.currentAccountRequest = (AccountMenuRequest)newRequest;
		break;
	case MenuType::EXIT:
		break;
	default:
		break;
	}
};

int Menu::getRequest(void)
{
	switch (currentMenu)
	{
	case MenuType::LOGIN:
		return  static_cast<int>(request.currentLoginRequest);
		break;
	case MenuType::MAIN:
		return  static_cast<int>(request.currentMainRequest);
		break;
	case MenuType::CUSTOMER:
		return  static_cast<int>(request.currentCustomerRequest);
		break;
	case MenuType::PRODUCT:
		return  static_cast<int>(request.currentProductRequest);
		break;
	case MenuType::INVOICE:
		return  static_cast<int>(request.currentInvoiceRequest);
		break;
	case MenuType::DISCOUNT:
		return  static_cast<int>(request.currentDiscountRequest);
		break;
	case MenuType::ACCOUNT:
		return  static_cast<int>(request.currentAccountRequest);
		break;
	case MenuType::EXIT:
		return 0;
		break;
	default:
		return 0;
		break;
	}
};

////////////////////////////////////////////////////////////////////////

void Menu::displayMenu(User currentUser) 
{
	// so my first implementation of this function (and subfunctions)
	// was to go to the current menu based upon the "MenuType" and inside this subfunction
	// based upon the "request" print the right submenu
	// however this method is actually not very scalable for different type of users who have different privilges
	// instead i pick up the different options to print in a struct

	currentSubMenu.menuOptions.clear();
	// 8 == +/- the biggest submenu in the program
	currentSubMenu.menuOptions.reserve(8);
	
	switch (currentMenu)
	{
	case MenuType::LOGIN:
		displayLoginMenu();
		break;
	case MenuType::MAIN:
		displayMainMenu();
		break;
	case MenuType::CUSTOMER:
		displayCustomerMenu();
		break;
	case MenuType::PRODUCT:
		displayProductMenu();
		break;
	case MenuType::INVOICE:
		displayInvoiceMenu();
		break;
	case MenuType::DISCOUNT:
		displayDiscountMenu();
		break;
	case MenuType::ACCOUNT:
		displayAccountMenu();
		break;
	case MenuType::EXIT:
		break;
	default:
		break;
	}

	// keeps track of what the programs sees and what the user sees
	// more about it in "doc.txt"
	std::unordered_map<int, int> optionMap;
	// so this will be the "key" the pysical option in the menu that the user can choose
	int optionCounterUser{ 1 };
	// and this the "value" the logical option which is the real value of that option
	int optionProgram{ 1 };

	std::cout << VIOLET << currentSubMenu.menuTitle << RESET_COLOR << "\n";
	for (MenuOption option : currentSubMenu.menuOptions)
	{
		if (option.privilgeLevel <= currentUser.userPrivilge)
		{
			std::cout
				<< TXT_COLOR(73) << std::setw(2) << optionCounterUser << " > " << RESET_COLOR
				<< VIOLET << option.optionDescription << RESET_COLOR << "\n";

			
			// a map between what the user sees and the program sees
			optionMap.insert(std::make_pair(optionCounterUser, optionProgram));

			// increment the option Counter of the user
			optionCounterUser++;
		}
		// 
		optionProgram++;
	}

	// after printing we need to ask the user to selcect a option
	verifyMenuInput(currentUser, optionMap);
};

void Menu::verifyMenuInput(User currentUser, std::unordered_map<int, int> optionMap)
{
	int newRequest{ 0 };

	// options in a menu range from [ 1 ; maxOptions ]
	newRequest = input(1, (int)optionMap.size());

	if (0 != currentSubMenu.lowerBound)
	{
		newRequest = optionMap[newRequest] + currentSubMenu.lowerBound - 1;
	}

	setRequest(newRequest);
};


void Menu::displayLoginMenu(void)
{
	switch (request.currentLoginRequest)
	{
	case LoginMenuRequest::LOGIN_MAIN_MENU:
		currentSubMenu.lowerBound = static_cast<int>(LoginMenuRequest::LOGIN_MAIN_MENU);
		currentSubMenu.menuTitle = "Login Menu";
		currentSubMenu.menuOptions.push_back({ "--> Login",			PROGRAM_PRIVILGE::USER});
		currentSubMenu.menuOptions.push_back({ "--> Quit program",	PROGRAM_PRIVILGE::USER});
		break;
	case LoginMenuRequest::LOGIN:
		break;
	case LoginMenuRequest::QUIT_PROGRAM:
		break;
	default:
		break;
	}
};

////////////////////////////////////////////////////////////////////////

void Menu::displayMainMenu(void)
{
	currentSubMenu.lowerBound = static_cast<int>(MainMenuRequest::MAIN_MENU);
	currentSubMenu.menuTitle = "Main Menu";

	std::vector<MenuOption> newOptions
	{
		{ "--> Customer Menu",	PROGRAM_PRIVILGE::EMPLOYEE },
		{ "--> Product Menu",	PROGRAM_PRIVILGE::EMPLOYEE },
		{ "--> Invoice Menu",	PROGRAM_PRIVILGE::EMPLOYEE },
		{ "--> Discount Menu",	PROGRAM_PRIVILGE::EMPLOYEE },
		{ "--> Account Menu",	PROGRAM_PRIVILGE::EMPLOYEE },
		{ "--> Load Menu",		PROGRAM_PRIVILGE::EMPLOYEE },
		{ "--> Logout",			PROGRAM_PRIVILGE::EMPLOYEE },
	};
	
	currentSubMenu.menuOptions = newOptions;
};

////////////////////////////////////////////////////////////////////////

void Menu::displayCustomerMenu(void)
{
	switch (request.currentCustomerRequest)
	{
	case CustomerMenuRequest::EXIT_CUSTOMER_SUBMENU_1:
	case CustomerMenuRequest::CUSTOMER_MAIN_MENU:

		currentSubMenu.lowerBound = static_cast<int>(CustomerMenuRequest::BACK_TO_MAIN_MENU);
		currentSubMenu.menuTitle = "Customer Menu";
		currentSubMenu.menuOptions.push_back({ "<-- Back To Main Menu",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Customer List",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Save Changes",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Add Customer",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Delete Customer",	PROGRAM_PRIVILGE::MANAGER });
		currentSubMenu.menuOptions.push_back({ "--> Update Customer",	PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case CustomerMenuRequest::EXIT_CUSTOMER_SUBMENU_3:
	case CustomerMenuRequest::EXIT_CUSTOMER_SUBMENU_2:
	case CustomerMenuRequest::DISPLAY_CUSTOMER_LIST:

		currentSubMenu.lowerBound = static_cast<int>(CustomerMenuRequest::SHOW_ALL_CUSTOMERS);
		currentSubMenu.menuTitle = "Customer List";
		currentSubMenu.menuOptions.push_back({ "--> Show All",				PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On",				PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By",				PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Back to Customer Menu",	PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case CustomerMenuRequest::EXIT_CUSTOMER_SUBMENU_4:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS:

		currentSubMenu.lowerBound = static_cast<int>(CustomerMenuRequest::FILTER_ON_CUSTOMERS_FIRSTNAME);
		currentSubMenu.menuTitle = "Filter On";
		currentSubMenu.menuOptions.push_back({ "--> FirstName",				PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> LastName",				PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Type",					PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Address",				PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Back to Customer List",	PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_TYPE:

		currentSubMenu.lowerBound = static_cast<int>(CustomerMenuRequest::FILTER_ON_CUSTOMERS_TYPE_PRIV);
		currentSubMenu.menuTitle = "Filter On Type";
		currentSubMenu.menuOptions.push_back({ "--> Private",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Corporate",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Filter On",	PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case CustomerMenuRequest::EXIT_CUSTOMER_SUBMENU_5:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS:

		currentSubMenu.lowerBound = static_cast<int>(CustomerMenuRequest::ORDER_BY_CUSTOMERS_FIRSTNAME);
		currentSubMenu.menuTitle = "Order By";
		currentSubMenu.menuOptions.push_back({ "--> FirstName",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> LastName",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Type",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Address",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Customer List",	PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_TYPE:

		currentSubMenu.lowerBound = static_cast<int>(CustomerMenuRequest::ORDER_BY_CUSTOMERS_TYPE_PRIV);
		currentSubMenu.menuTitle = "Order By Type";
		currentSubMenu.menuOptions.push_back({ "--> Private",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Corporate",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Order By",		PROGRAM_PRIVILGE::EMPLOYEE });
		
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS:

		currentSubMenu.lowerBound = static_cast<int>(CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_COUNTRY);
		currentSubMenu.menuTitle = "Order By Address";
		currentSubMenu.menuOptions.push_back({ "--> Country",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> PostalCode",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Streetname",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Housenumber",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Phonenumber",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Order By",		PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS:

		currentSubMenu.lowerBound = static_cast<int>(CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_COUNTRY);
		currentSubMenu.menuTitle = "Filter On Address";
		currentSubMenu.menuOptions.push_back({ "--> Country",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> PostalCode",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Streetname",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Housenumber",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Phonenumber",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Filter On",		PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	default:
		break;
	}
};

////////////////////////////////////////////////////////////////////////

void Menu::displayProductMenu(void)
{
	switch (request.currentProductRequest)
	{
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_1:
	case ProductMenuRequest::PRODUCT_MAIN_MENU:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::BACK_TO_MAIN_MENU);
		currentSubMenu.menuTitle = "Product Menu";
		currentSubMenu.menuOptions.push_back({ "<-- Back To Main Menu",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Product List",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Save Changes",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Add Product",		PROGRAM_PRIVILGE::MANAGER });
		currentSubMenu.menuOptions.push_back({ "--> Delete Product",	PROGRAM_PRIVILGE::MANAGER });
		currentSubMenu.menuOptions.push_back({ "--> Update Product",	PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_2:
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_6:
	case ProductMenuRequest::DISPLAY_PRODUCT_LIST:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::SHOW_ALL_PRODUCTS);
		currentSubMenu.menuTitle = "Product List";
		currentSubMenu.menuOptions.push_back({ "--> Show All",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Product Menu",	PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_3:
	case ProductMenuRequest::FILTER_ON_PRODUCTS:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::FILTER_ON_PRODUCTS_NAME);
		currentSubMenu.menuTitle = "Filter On";
		currentSubMenu.menuOptions.push_back({ "--> Filter on Product's Name",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter on Product's Diameter",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter on Product's Manufacturer",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter on Product's Type",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Product List",						PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_7:
	case ProductMenuRequest::ORDER_BY_PRODUCTS:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::ORDER_BY_PRODUCTS_NAME);
		currentSubMenu.menuTitle = "Order by";
		currentSubMenu.menuOptions.push_back({ "--> Order by Product's Name",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order by Product's Diameter",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order by Product's Manufacturer",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order by Product's Type",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Product List",						PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_5:
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_4:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM);
		currentSubMenu.menuTitle = "Filter On Type";
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Type Tyre",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Type Rim",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Filter On",						PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_NAME);
		currentSubMenu.menuTitle = "Filter On Type Tyre";
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Name",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Diameter",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Manufacturer",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Width",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Height",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's SpeedIndex",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's TyreMarkings",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Filter On Type",					PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_NAME);
		currentSubMenu.menuTitle = "Filter On Type Rims";
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Name",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Diameter",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Manufacturer",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Width",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Material",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Filter On Product's Color",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Filter On Type",					PROGRAM_PRIVILGE::EMPLOYEE });
		
		break;
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_9:
	case ProductMenuRequest::EXIT_PRODUCT_SUBMENU_8:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE);
		currentSubMenu.menuTitle = "Order By Type";
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Tyre",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Rims",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Order By Type",				PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_NAME);
		currentSubMenu.menuTitle = "Order By Type Tyre";
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Name",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Diameter",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Manufacturer",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Width",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Material",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Color",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Order By Type",						PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM:

		currentSubMenu.lowerBound = static_cast<int>(ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_NAME);
		currentSubMenu.menuTitle = "Order By Type Rims";
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Name",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Diameter",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Manufacturer",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Width",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Material",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Order By Product's Color",			PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Order By Type",						PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	default:
		break;
	}
};

////////////////////////////////////////////////////////////////////////

void Menu::displayInvoiceMenu(void)
{
	switch (request.currentInvoiceRequest)
	{
	case InvoiceMenuRequest::EXIT_INVOICE_SUBMENU_1:
	case InvoiceMenuRequest::EXIT_INVOICE_SUBMENU_2:
	case InvoiceMenuRequest::INVOICE_MAIN_MENU:

		currentSubMenu.lowerBound = static_cast<int>(InvoiceMenuRequest::BACK_TO_MAIN_MENU);
		currentSubMenu.menuTitle = "Invoice Menu";
		currentSubMenu.menuOptions.push_back({ "<-- Back to Main Menu",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Create Invoice",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Search Invoices",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Active Invoices",	PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case InvoiceMenuRequest::SEARCH_CUSTOMER_INVOICES:
		currentSubMenu.lowerBound = static_cast<int>(InvoiceMenuRequest::SEARCH_CUSTOMER_INVOICES_HANDLED);
		currentSubMenu.menuTitle = "Search Invoices";
		currentSubMenu.menuOptions.push_back({ "--> Handled Invoices",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Pending Invoices",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Invoice Menu",		PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	case InvoiceMenuRequest::ACTIVE_INVOICES:
		currentSubMenu.lowerBound = static_cast<int>(InvoiceMenuRequest::DELETE_INVOICE);
		currentSubMenu.menuTitle = "Open Active Invoices";
		currentSubMenu.menuOptions.push_back({ "--> Delete Invoice",				PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Process Invoice",				PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Add Product to Invoice",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Remove Product from Invoice",	PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Display Pending Invoices",		PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "--> Save Changes",					PROGRAM_PRIVILGE::EMPLOYEE });
		currentSubMenu.menuOptions.push_back({ "<-- Invoice Menu",					PROGRAM_PRIVILGE::EMPLOYEE });

		break;
	default:
		break;
	}
};

////////////////////////////////////////////////////////////////////////

void Menu::displayDiscountMenu(void)
{
	currentSubMenu.lowerBound = static_cast<int>(DiscountMenuRequest::BACK_TO_MAIN_MENU);
	currentSubMenu.menuTitle = "Discount Menu";
	currentSubMenu.menuOptions.push_back({ "<-- Back to Main Menu",				PROGRAM_PRIVILGE::EMPLOYEE });
	currentSubMenu.menuOptions.push_back({ "--> Show Current Discounts",		PROGRAM_PRIVILGE::EMPLOYEE });
	currentSubMenu.menuOptions.push_back({ "--> Show Tyre/Rim matching table",	PROGRAM_PRIVILGE::EMPLOYEE });
	currentSubMenu.menuOptions.push_back({ "--> Save Discounts",				PROGRAM_PRIVILGE::EMPLOYEE });
	currentSubMenu.menuOptions.push_back({ "--> Change Discounts",				PROGRAM_PRIVILGE::MANAGER });
	currentSubMenu.menuOptions.push_back({ "--> Change Discounts Conditions",	PROGRAM_PRIVILGE::MANAGER });
};

////////////////////////////////////////////////////////////////////////

void Menu::displayAccountMenu(void)
{
	currentSubMenu.lowerBound = static_cast<int>(AccountMenuRequest::BACK_TO_MAIN_MENU);
	currentSubMenu.menuTitle = "Account Menu";
	currentSubMenu.menuOptions.push_back({ "<-- Back to Main Menu",		PROGRAM_PRIVILGE::EMPLOYEE });
	currentSubMenu.menuOptions.push_back({ "--> Add Account",			PROGRAM_PRIVILGE::EMPLOYEE });
	currentSubMenu.menuOptions.push_back({ "--> Delete Account",		PROGRAM_PRIVILGE::MANAGER });
	currentSubMenu.menuOptions.push_back({ "--> Update Account",		PROGRAM_PRIVILGE::EMPLOYEE });
};

////////////////////////////////////////////////////////////////////////

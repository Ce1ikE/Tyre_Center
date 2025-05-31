/*

	Object Oriented Programming Labo - YT5984

	Name:		Celik
	Firstname:	Ennis
	Group:		2EICT - Apllied AI
	
*/
// things to consider further down the line or improvements to make :
// ------------------------------------------------------------------------------------

// TIME FUNCTIONALITY =================================================================
// is depricated :
//std::time_t currentTime;
//std::time(&currentTime);
//std::cout << std::ctime(&currentTime);
//
// consider using the "chrono" library
// see => https://www.geeksforgeeks.org/date-and-time-parsing-in-cpp/

// COUNTRIES LIST TO CHOOSE FROM FOR CUSTOMERS ADDRESS ================================
// std::array<std::string, 11> countries{ "Germany", "France", "Italy", "Spain", "Sweden","Belgium","United Kingdom", "Norway", "Mexico", "Canada", "United States" }; 
// etc...

// OS CHECK TO SAVE FILE IN HOME DIRECTORY ============================================
// https://terminalroot.com/how-to-check-which-operating-system-with-cpp/
//#if _linux_
//	std::string homeDirectory{ "$HOME/Tyrecenter/" };
//#elif _WIN32
//	std::string homeDirectory{ "C:\\Tyrecenter\\" };
//#endif

// SAVE OBJECTS IN BINARY FILES BUT WITH MORE COMPATIBILITY ================================
// serilization
// see => https://www.geeksforgeeks.org/serialize-and-deserialize-an-object-in-cpp/
// see => https://liamappelbe.medium.com/serialization-in-c-3d381e66ecec

// TEMPLATE FUNCTIONS REMARK ==========================================================
// a compiler has 2 fases :
// (1) the compiling fase
// (2) the linking fase
// Its during fase (2) that a error is thrown (LNK2019) 
// when a program is compiled it generates .o (linux) or .obj (windows) aka object files
// each function call has a reference to the function's definition in these files
// problem is that when a program is compiled (1) into these object files 
// each .cpp (translation units)  + .h (headers) file is preprocessed and compiled to a object file indivually
// wich means when function call is made to a class's template function 
// in a other .cpp file (A.cpp) then where it's definition is (B.cpp) no code will be generated
// by the compiler for these functions.
// see => https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
// see => https://hackingcpp.com/cpp/lang/separate_compilation.html

// STREAMOFF CLASS ====================================================================
// because sometimes i have to move back in a binary file i cast to the std::streamoff 
// see => https://en.cppreference.com/w/cpp/io/streamoff

// ------------------------------------------------------------------------------------



#include <chrono>
#include <ctime>
#include "../headers/Menu.h"
#include "../headers/Controller.h"
#include "../headers/TyreCenterHeader.h"
#include "../headers/TyreCenterFunctions.h"

/* Using namespace *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

	
	//   __		  __			__
	//	/  \     /  |          /  |          
	//	$$  \   /$$ |  ______  $$/  _______  
	//	$$$  \ /$$$ | /      \ /  |/       \ 
	//	$$$$  /$$$$ | $$$$$$  |$$ |$$$$$$$  |
	//	$$ $$ $$/$$ | /    $$ |$$ |$$ |  $$ |
	//	$$ |$$$/ $$ |/$$$$$$$ |$$ |$$ |  $$ |
	//	$$ | $/  $$ |$$    $$ |$$ |$$ |  $$ |
	//	$$/      $$/  $$$$$$$/ $$/ $$/   $$/ 
	// 

int main(void)
{
	
	Controller programController;
	Menu menuInterface;

	// the "prepareProgram" function checks if the files that are required for the program to run
	// are created or not => ONLY BINARY FILES 
	// => load data by creating the appropriate CSV and XML files
	if (!prepareProgram(programController))
	{
		menuInterface.setCurrentMenuType(MenuType::EXIT);
	}

	Hello_World();

	// enables no wrapping because it's annoying => zoom out instead => don't like it ? => comment the line
	// if the VT doesn't support ANSI CLI's then this is ignored
	std::cout << "\033[?7l";

	// if you don't know what ANSI CLI's are
	// see => https://vt100.net/docs/vt510-rm/chapter4.html

	// a "While" loop that keeps running as long as the "menuInterface" doesn't switch it's current MenuType to "EXIT"
	// depending on the "menuInterface" MenuType we choose the appropriate menu + submenus  to display
	while (menuInterface.getCurrentMenuType() != MenuType::EXIT)
	{
		std::cout << VIOLET;
		// show the menu and verifies the user input
		menuInterface.displayMenu(programController.getCurrentUser());
		// set cursor to (y,x) and wipes the whole screen
		std::cout << HOME_CURSOR << WIPE_SCREEN;
		switch (menuInterface.getCurrentMenuType())
		{
		case MenuType::LOGIN:
			handleLoginMenuRequest(menuInterface, programController);
			break;
		case MenuType::MAIN:
			handleMainMenuRequest(menuInterface,programController);
			break;
		case MenuType::CUSTOMER:
			handleCustomersMenuRequest(menuInterface, programController);
			break;
		case MenuType::PRODUCT:
			handleProductsMenuRequest(menuInterface, programController);
			break;
		case MenuType::INVOICE:
			handleInvoiceMenuRequest(menuInterface, programController);
			break;
		case MenuType::DISCOUNT:
			handleDiscountMenuRequest(menuInterface, programController);
			break;
		case MenuType::ACCOUNT:
			handleAccountMenuRequest(menuInterface,programController);
			break;
		case MenuType::EXIT:
			break;
		default:
			std::cout << "Wrong Menu";
			break;
		}
	}


	Bye_Message();
	return 0;
};

/* Function definitions */////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Some additional functions for aesthetic purposes
void Hello_World(void)
{
	std::cout << GREEN << "\n\n";

	std::cout 
		<< "\n\t      \x5F\x5F\x5F\x5F          \x5F\x5F\x5F\x5F           \x5F\x5F\x5F\x5F        \x5F\x5F\x5F\x5F        \x5F\x5F\x5F\x5F              "
		<< "\n\t     \x2F   \x2F\x5C        \x2F   \x2F\x5C         \x2F   \x2F\x5C      \x2F   \x2F\x5C      \x2F   \x2F\x5C             "
		<< "\n\t    \x2F   \x2F\x3A\x2F       \x2F   \x2F\x3A\x3A\x5C       \x2F   \x2F\x3A\x2F     \x2F   \x2F\x3A\x2F     \x2F   \x2F\x3A\x3A\x5C            "
		<< "\n\t   \x2F   \x2F\x3A\x2F       \x2F   \x2F\x3A\x2F\x5C\x3A\x5C     \x2F   \x2F\x3A\x2F     \x2F   \x2F\x3A\x2F     \x2F   \x2F\x3A\x2F\x5C\x3A\x5C           "
		<< "\n\t  \x2F   \x2F\x3A\x3A\x5C \x5F\x5F\x5F  \x2F   \x2F\x3A\x3A\x5C \x5C\x3A\x5C   \x2F   \x2F\x3A\x2F     \x2F   \x2F\x3A\x2F     \x2F   \x2F\x3A\x2F  \x5C\x3A\x5C          "
		<< "\n\t \x2F\x5F\x5F\x5F\x2F\x3A\x2F\x5C\x3A\x5C  \x2F\x5C\x2F\x5F\x5F\x5F\x2F\x3A\x2F\x5C\x3A\x5C \x5C\x3A\x5C \x2F\x5F\x5F\x5F\x2F\x3A\x2F     \x2F\x5F\x5F\x5F\x2F\x3A\x2F     \x2F\x5F\x5F\x5F\x2F\x3A\x2F \x5C\x5F\x5F\x5C\x3A\x5C         "
		<< "\n\t \x5C\x5F\x5F\x5F\x5C\x2F  \x5C\x3A\x5C\x2F\x3A\x2F\x5C   \x5C\x3A\x5C \x5C\x3A\x5C\x5F\x5C\x2F \x5C   \x5C\x3A\x5C     \x5C   \x5C\x3A\x5C     \x5C   \x5C\x3A\x5C \x2F  \x2F\x3A\x2F         "
		<< "\n\t      \x5C\x5F\x5F\x5F\x5C\x3A\x3A\x2F  \x5C   \x5C\x3A\x5C \x5C\x3A\x5C    \x5C   \x5C\x3A\x5C     \x5C   \x5C\x3A\x5C     \x5C   \x5C\x3A\x5C  \x2F\x3A\x2F          "
		<< "\n\t      \x2F   \x2F\x3A\x2F    \x5C   \x5C\x3A\x5C\x5F\x5C\x2F     \x5C   \x5C\x3A\x5C     \x5C   \x5C\x3A\x5C     \x5C   \x5C\x3A\x5C\x2F\x3A\x2F           "
		<< "\n\t     \x2F\x5F\x5F\x5F\x2F\x3A\x2F      \x5C   \x5C\x3A\x5C        \x5C   \x5C\x3A\x5C     \x5C   \x5C\x3A\x5C     \x5C   \x5C\x3A\x3A\x2F            "
		<< "\n\t     \x5C\x5F\x5F\x5F\x5C\x2F        \x5C\x5F\x5F\x5F\x5C\x2F         \x5C\x5F\x5F\x5F\x5C\x2F      \x5C\x5F\x5F\x5F\x5C\x2F      \x5C\x5F\x5F\x5F\x5C\x2F             ";

	std::cout << RESET_COLOR << "\n\n\n";
}

void Bye_Message(void)
{
	std::cout << "\n\n" << BLUE;

	std::cout 
		<< "\n\t\t\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\x20\x20\xB2\xB2\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\x20\xDC\xB2\xDF\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\x20\xB2\xB2\xDC\xDC\xDC\xDC\xDC\x20\x20\x20\xDC\xDC\x20\x20\x20\x20\x20\xDC\xDC\x20\x20\x20\xDC\xDC\xDC\xDC\xDC\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\x20\xB2\xB2\xDF\x20\x20\xDF\xB2\xB2\x20\x20\x20\xB2\xB2\x20\x20\x20\xB2\xB2\x20\x20\x20\xB2\xB2\x20\x20\x20\xB2\xB2\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\xB2\xB2\x20\x20\x20\x20\x20\xB2\xB2\x20\x20\x20\xB2\xDF\x20\x20\x20\xB2\xB2\x20\x20\xB2\xB2\xDC\xDC\xDC\xB2\xDF\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\xB2\xB2\x20\x20\x20\x20\xDC\xB2\x20\x20\x20\xB2\xB2\x20\x20\x20\xDC\xB2\x20\x20\x20\xB2\xB2\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\xB2\xB2\x20\xDC\xDC\xB2\xDF\x20\x20\x20\x20\xDF\xB2\xDC\xDC\xDC\xB2\xDF\x20\x20\x20\xDF\xB2\xDC\xDC\xDC\xB2\xDF\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\x20\xDF\xDF\xDF\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB2\xB2\x20\x20\x20\x20\x20\x20\xDF\xDF\x20\x20\x20\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xB2\xDC\x20\xDC\xB2\xDF\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
		<< "\n\t\t\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xDF\xDF\xDF\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20";

	std::cout << "\n\n\n" << RESET_COLOR;
}

	//   __    __                            __  __                   ______                                  __      __
	//	/  |  /  |                          /  |/  |                 /      \                                /  |    /  |                              
	//	$$ |  $$ |  ______   _______    ____$$ |$$ |  ______        /$$$$$$  |__    __  _______    _______  _$$ |_   $$/   ______   _______    _______ 
	//	$$ |__$$ | /      \ /       \  /    $$ |$$ | /      \       $$ |_ $$//  |  /  |/       \  /       |/ $$   |  /  | /      \ /       \  /       |
	//	$$    $$ | $$$$$$  |$$$$$$$  |/$$$$$$$ |$$ |/$$$$$$  |      $$   |   $$ |  $$ |$$$$$$$  |/$$$$$$$/ $$$$$$/   $$ |/$$$$$$  |$$$$$$$  |/$$$$$$$/ 
	//	$$$$$$$$ | /    $$ |$$ |  $$ |$$ |  $$ |$$ |$$    $$ |      $$$$/    $$ |  $$ |$$ |  $$ |$$ |        $$ | __ $$ |$$ |  $$ |$$ |  $$ |$$      \ 
	//	$$ |  $$ |/$$$$$$$ |$$ |  $$ |$$ \__$$ |$$ |$$$$$$$$/       $$ |     $$ \__$$ |$$ |  $$ |$$ \_____   $$ |/  |$$ |$$ \__$$ |$$ |  $$ | $$$$$$  |
	//	$$ |  $$ |$$    $$ |$$ |  $$ |$$    $$ |$$ |$$       |      $$ |     $$    $$/ $$ |  $$ |$$       |  $$  $$/ $$ |$$    $$/ $$ |  $$ |/     $$/ 
	//	$$/   $$/  $$$$$$$/ $$/   $$/  $$$$$$$/ $$/  $$$$$$$/       $$/       $$$$$$/  $$/   $$/  $$$$$$$/    $$$$/  $$/  $$$$$$/  $$/   $$/ $$$$$$$/  

// The "handle" functions are ment  to select the appropriate function that needs to handle user's request such functions are adding or deleting items.
// This is the core of the navigation part of the program. For each "MenuType" we have a function that handles the user's request and each "handle" functions has it's
// own enumeration type for the request. The reason why i chose to do this is for splitting the program up in smaller chunks. 
/*
	function					| Menu type						| Request Type
	---------------------------------------------------------------------------------------------
	"handleLoginMenuRequest"	| "LOGIN"						| "LoginMenuRequest"
	"handleMainMenuRequest"		| "MAIN"						| "MainMenuRequest"
	"handleCustomerMenuRequest"	| "CUSTOMER"					| "CustomerMenuRequest"
	"handleProductMenuRequest"	| "PRODUCT"						| "ProductMenuRequest"
	etc....

*/

void handleLoginMenuRequest(Menu& menuInterface,Controller& programController)
{
	switch ((LoginMenuRequest)menuInterface.getRequest())
	{
	case LoginMenuRequest::LOGIN:
		if (verifyEmployeeCredentials(programController))
		{
			menuInterface.setCurrentMenuType(MenuType::MAIN);
		}
		menuInterface.setRequest((int)LoginMenuRequest::LOGIN_MAIN_MENU);
		break;
	case LoginMenuRequest::QUIT_PROGRAM:
		menuInterface.setCurrentMenuType(MenuType::EXIT);
		menuInterface.setRequest((int)LoginMenuRequest::QUIT_PROGRAM);
		break;
	default:
		break;
	}
};

void handleMainMenuRequest(Menu& menuInterface, Controller& programController)
{
	switch ((MainMenuRequest)menuInterface.getRequest())
	{
	case MainMenuRequest::LOGOUT:
		menuInterface.setCurrentMenuType(MenuType::LOGIN);
		menuInterface.setRequest((int)MainMenuRequest::MAIN_MENU);
		break;
	case MainMenuRequest::GO_TO_CUSTOMER_MENU:
		menuInterface.setCurrentMenuType(MenuType::CUSTOMER);
		menuInterface.setRequest((int)MainMenuRequest::MAIN_MENU);
		break;
	case MainMenuRequest::GO_TO_PRODUCT_MENU:
		menuInterface.setCurrentMenuType(MenuType::PRODUCT);
		menuInterface.setRequest((int)MainMenuRequest::MAIN_MENU);
		break;
	case MainMenuRequest::GO_TO_INVOICE_MENU:
		menuInterface.setCurrentMenuType(MenuType::INVOICE);
		menuInterface.setRequest((int)MainMenuRequest::MAIN_MENU);
		break;
	case MainMenuRequest::GO_TO_DISCOUNT_MENU:
		menuInterface.setCurrentMenuType(MenuType::DISCOUNT);
		menuInterface.setRequest((int)MainMenuRequest::MAIN_MENU);
		break;
	case MainMenuRequest::GO_TO_ACCOUNT_MENU:
		menuInterface.setCurrentMenuType(MenuType::ACCOUNT);
		menuInterface.setRequest((int)MainMenuRequest::MAIN_MENU);
		break;
	case MainMenuRequest::LOAD_DATA:
		loadData(programController);
		menuInterface.setRequest((int)MainMenuRequest::MAIN_MENU);
		break;
	case MainMenuRequest::MAIN_MENU:
		menuInterface.setCurrentMenuType(MenuType::MAIN);
		menuInterface.setRequest((int)MainMenuRequest::MAIN_MENU);
		break;
	default:
		break;
	}
};

void handleCustomersMenuRequest(Menu& menuInterface, Controller& programController)
{
	switch ((CustomerMenuRequest)menuInterface.getRequest())
	{
	case CustomerMenuRequest::BACK_TO_MAIN_MENU:
		menuInterface.setCurrentMenuType(MenuType::MAIN);
		menuInterface.setRequest((int)CustomerMenuRequest::CUSTOMER_MAIN_MENU);
		break;
	case CustomerMenuRequest::SAVE_CUSTOMERS:
		saveCustomers(programController);
		menuInterface.setRequest((int)CustomerMenuRequest::CUSTOMER_MAIN_MENU);
		break;
	case CustomerMenuRequest::ADD_CUSTOMER:
		addCustomer(programController);
		menuInterface.setRequest((int)CustomerMenuRequest::CUSTOMER_MAIN_MENU);
		break;
	case CustomerMenuRequest::DELETE_CUSTOMER:
		deleteCustomer(programController);
		menuInterface.setRequest((int)CustomerMenuRequest::CUSTOMER_MAIN_MENU);
		break;
	case CustomerMenuRequest::UPDATE_CUSTOMER:
		updateCustomer(programController);
		menuInterface.setRequest((int)CustomerMenuRequest::CUSTOMER_MAIN_MENU);
		break;
	case CustomerMenuRequest::SHOW_ALL_CUSTOMERS:
		showList(programController.getCustomerListReference());
		menuInterface.setRequest((int)CustomerMenuRequest::DISPLAY_CUSTOMER_LIST);
		break;
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_COUNTRY:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_POSTALCODE:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_STREETNAME:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_HOUSENUMBER:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_ADDRESS_PHONENUMBER:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_FIRSTNAME:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_LASTNAME:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_TYPE_PRIV:
	case CustomerMenuRequest::FILTER_ON_CUSTOMERS_TYPE_CORP:
		filterCustomers((CustomerMenuRequest)menuInterface.getRequest(), programController.getCustomerListReference());
		menuInterface.setRequest((int)CustomerMenuRequest::FILTER_ON_CUSTOMERS);
		break;
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_COUNTRY:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_POSTALCODE:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_STREETNAME:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_HOUSENUMBER:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_ADDRESS_PHONENUMBER:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_FIRSTNAME:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_LASTNAME:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_TYPE_PRIV:
	case CustomerMenuRequest::ORDER_BY_CUSTOMERS_TYPE_CORP:
		orderCustomers((CustomerMenuRequest)menuInterface.getRequest(), programController.getCustomerListReference());
		menuInterface.setRequest((int)CustomerMenuRequest::ORDER_BY_CUSTOMERS);
		break;
	default:
		break;
	}
};

void handleProductsMenuRequest(Menu& menuInterface, Controller& programController)
{
	switch ((ProductMenuRequest)menuInterface.getRequest())
	{
	case ProductMenuRequest::BACK_TO_MAIN_MENU:
		menuInterface.setCurrentMenuType(MenuType::MAIN);
		break;
	case ProductMenuRequest::SAVE_PRODUCTS:
		saveProducts(programController);
		menuInterface.setRequest((int)ProductMenuRequest::PRODUCT_MAIN_MENU);
		break;
	case ProductMenuRequest::ADD_PRODUCT:
		addProduct(programController);
		menuInterface.setRequest((int)ProductMenuRequest::PRODUCT_MAIN_MENU);
		break;
	case ProductMenuRequest::DELETE_PRODUCT:
		deleteProduct(programController);
		menuInterface.setRequest((int)ProductMenuRequest::PRODUCT_MAIN_MENU);
		break;
	case ProductMenuRequest::UPDATE_PRODUCT:
		updateProduct(programController);
		menuInterface.setRequest((int)ProductMenuRequest::PRODUCT_MAIN_MENU);
		break;
	case ProductMenuRequest::SHOW_ALL_PRODUCTS:
		showList(programController.getProductListReference());
		menuInterface.setRequest((int)ProductMenuRequest::PRODUCT_MAIN_MENU);
		break;
	case ProductMenuRequest::FILTER_ON_PRODUCTS_NAME:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_DIAMETER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_MANUFACTURER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_NAME:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_DIAMETER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_MANUFACTURER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_WIDTH:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_HEIGHT:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_SPEEDINDEX:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_TYRE_TYREMARKINGS:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_NAME:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_DIAMETER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_MANUFACTURER:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_WIDTH:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_MATERIAL:
	case ProductMenuRequest::FILTER_ON_PRODUCTS_TYPE_RIM_COLOR:
		filterProducts((ProductMenuRequest)menuInterface.getRequest(), programController.getProductListReference());
		menuInterface.setRequest((int)ProductMenuRequest::FILTER_ON_PRODUCTS);
		break;
	case ProductMenuRequest::ORDER_BY_PRODUCTS_NAME:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_DIAMETER:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_MANUFACTURER:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_NAME:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_DIAMETER:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_MANUFACTURER:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_WIDTH:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_HEIGHT:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_SPEEDINDEX:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_TYRE_TYREMARKINGS:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_NAME:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_DIAMETER:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_MANUFACTURER:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_WIDTH:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_MATERIAL:
	case ProductMenuRequest::ORDER_BY_PRODUCTS_TYPE_RIM_COLOR:
		orderProducts((ProductMenuRequest)menuInterface.getRequest(), programController.getProductListReference());
		menuInterface.setRequest((int)ProductMenuRequest::ORDER_BY_PRODUCTS);
		break;
	default:
		break;
	}
};

void handleInvoiceMenuRequest(Menu& menuInterface, Controller& programController)
{
	switch ((InvoiceMenuRequest)menuInterface.getRequest())
	{
	case InvoiceMenuRequest::BACK_TO_MAIN_MENU:
		menuInterface.setCurrentMenuType(MenuType::MAIN);
		break;
	case InvoiceMenuRequest::SEARCH_CUSTOMER_INVOICES_HANDLED:
		searchHandledInvoices(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::SEARCH_CUSTOMER_INVOICES);
		break;
	case InvoiceMenuRequest::SEARCH_CUSTOMER_INVOICES_PENDING:
		searchPendingInvoices(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::SEARCH_CUSTOMER_INVOICES);
		break;
	case InvoiceMenuRequest::DISPLAY_ACTIVE_INVOICES:
		displayPendingInvoice(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::ACTIVE_INVOICES);
		break;
	case InvoiceMenuRequest::CREATE_CUSTOMER_INVOICE:
		addInvoice(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::INVOICE_MAIN_MENU);
		break;
	case InvoiceMenuRequest::DELETE_INVOICE:
		deleteInvoice(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::ACTIVE_INVOICES);
		break;
	case InvoiceMenuRequest::PROCESS_INVOICE:
		processInvoice(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::ACTIVE_INVOICES);
		break;
	case InvoiceMenuRequest::ADD_INVOICE_PRODUCT:
		addProductToInvoice(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::ACTIVE_INVOICES);
		break;
	case InvoiceMenuRequest::REMOVE_INVOICE_PRODUCT:
		removeProductFromInvoice(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::ACTIVE_INVOICES);
		break;
	case InvoiceMenuRequest::SAVE_ACTIVE_INVOICES:
		saveInvoices(programController);
		menuInterface.setRequest((int)InvoiceMenuRequest::ACTIVE_INVOICES);
		break;
	default:
		break;
	}
};

void handleDiscountMenuRequest(Menu& menuInterface, Controller& programController)
{
	switch ((DiscountMenuRequest)menuInterface.getRequest())
	{
	case DiscountMenuRequest::BACK_TO_MAIN_MENU:
		menuInterface.setRequest((int)DiscountMenuRequest::DISCOUNT_MAIN_MENU);
		menuInterface.setCurrentMenuType(MenuType::MAIN);
		break;
	case DiscountMenuRequest::SHOW_CURRENT_DISCOUNTS:
		showCurrentDiscounts(programController);
		menuInterface.setRequest((int)DiscountMenuRequest::DISCOUNT_MAIN_MENU);
		break;
	case DiscountMenuRequest::SHOW_MATCHING_TABLE:
		showMatchingTable(programController);
		menuInterface.setRequest((int)DiscountMenuRequest::DISCOUNT_MAIN_MENU);
		break;
	case DiscountMenuRequest::CHANGE_DISCOUNT:
		changeDiscount(programController);
		menuInterface.setRequest((int)DiscountMenuRequest::DISCOUNT_MAIN_MENU);
		break;
	case DiscountMenuRequest::CHANGE_DISCOUNT_CONDITIONS:
		changeDiscountConditions(programController);
		menuInterface.setRequest((int)DiscountMenuRequest::DISCOUNT_MAIN_MENU);
		break;
	case DiscountMenuRequest::SAVE_DISCOUNTS:
		saveDiscounts(programController);
		menuInterface.setRequest((int)DiscountMenuRequest::DISCOUNT_MAIN_MENU);
		break;
	default:
		break;
	}
};

void handleAccountMenuRequest(Menu& menuInterface, Controller& programController)
{
	switch ((AccountMenuRequest)menuInterface.getRequest())
	{
	case AccountMenuRequest::BACK_TO_MAIN_MENU:
		menuInterface.setRequest((int)AccountMenuRequest::ACCOUNT_MAIN_MENU);
		menuInterface.setCurrentMenuType(MenuType::MAIN);
		break;
	case AccountMenuRequest::ADD_ACCOUNT:
		addAccount(programController);
		menuInterface.setRequest((int)AccountMenuRequest::ACCOUNT_MAIN_MENU);
		break;
	case AccountMenuRequest::DELETE_ACCOUNT:
		deleteAccount(programController);
		menuInterface.setRequest((int)AccountMenuRequest::ACCOUNT_MAIN_MENU);
		break;
	case AccountMenuRequest::UPDATE_ACCOUNT:
		updateAccount(programController);
		menuInterface.setRequest((int)AccountMenuRequest::ACCOUNT_MAIN_MENU);
		break;
	default:
		break;
	}
};
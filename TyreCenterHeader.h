#pragma once
#ifndef TYRECENTER
#define TYRECENTER

/* Macro's *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RED							"\033[38;5;196m"
#define PINK						"\033[38;5;198m"
#define YELLOW						"\033[38;5;226m" 
#define BLUE						"\033[38;5;33m" 
#define CYAN						"\033[38;5;87m"
#define TURQUOISE					"\033[38;5;30m"
#define OLIVE						"\033[38;5;58m"
#define ORANGE						"\033[38;5;202m"
#define GREEN						"\033[38;5;118m" 
#define VIOLET						"\033[38;5;141m" 
#define TXT_COLOR(X)                "\033[38;5;"#X"m"
#define BG_COLOR(X)                 "\033[48;5;"#X"m"
#define ITALIC                      "\033[3m"
#define RESET_COLOR					"\033[0m"
#define WIPE_SCREEN					"\033[J"
#define HOME_CURSOR					"\033[H"
// binary files *//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CUSTOMERS_BIN_FILE			"_CustomersList.bin"
#define PRODUCTS_BIN_FILE			"_ProductsList.bin" 
#define INVOICES_P_BIN_FILE			"_InvoicesList_pending.bin"
#define INVOICES_H_BIN_FILE			"_InvoicesList_handled.bin"
#define DISCOUNTS_BIN_FILE			"_DiscountsList.bin"
#define EMPLOYEES_BIN_FILE			"_EmployeesList.bin"
#define ID_BIN_FILE					"_Id_file_.bin"
// text files *////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CUSTOMERS_TXT_FILE			"_CustomersList.txt"
#define PRODUCTS_TXT_FILE			"_ProductsList.txt" 
#define INVOICES_P_TXT_FILE			"_InvoicesList_pending.txt"
#define INVOICES_H_TXT_FILE			"_InvoicesList_handled.txt"
#define DISCOUNTS_TXT_FILE			"_DiscountsList.txt"
#define EMPLOYEES_TXT_FILE			"_EmployeesList.txt"
#define ID_TXT_FILE					"_Id_file_.txt"
// csv files */////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CUSTOMERS_CSV_FILE			"_CustomersList.csv"
#define PRODUCTS_CSV_FILE			"_ProductsList.csv" 
#define INVOICES_P_CSV_FILE			"_InvoicesList_pending.csv"
#define INVOICES_H_CSV_FILE			"_InvoicesList_handled.csv"
#define DISCOUNTS_CSV_FILE			"_DiscountsList.csv"
#define EMPLOYEES_CSV_FILE			"_EmployeesList.csv"
#define ID_CSV_FILE					"_Id_file_.csv"
// xml files */////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CUSTOMERS_XML_FILE			"_CustomersList.xml"
#define PRODUCTS_XML_FILE			"_ProductsList.xml" 
#define INVOICES_P_XML_FILE			"_InvoicesList_pending.xml"
#define INVOICES_H_XML_FILE			"_InvoicesList_handled.xml"
#define DISCOUNTS_XML_FILE			"_DiscountsList.xml"
#define EMPLOYEES_XML_FILE			"_EmployeesList.xml"
// xml tags *//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _START_XML					    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
#define _START_INVOICE_LIST_XML		    "\n<invoicelist>\n"
#define _STOP_INVOICE_LIST_XML		    "\n</invoicelist>\n"
#define _START_INVOICE_XML(id)		    "\n<invoice id=\""##+id+##"\">\n"
#define _STOP_INVOICE_XML		        "\n</invoice>\n"

#define _START_PRODUCT_LIST_XML		    "\n<productlist>\n"
#define _STOP_PRODUCT_LIST_XML		    "\n</productlist>\n"
#define _START_PRODUCT_XML(id,type)		"\n<product id=\""##+id+##"\" type=\""##+type+##"\">\n"
#define _STOP_PRODUCT_XML		        "\n</product>\n"

#define _START_CUSTOMER_LIST_XML	    "\n<customerlist>\n"
#define _STOP_CUSTOMER_LIST_XML		    "\n</customerlist>\n"
#define _START_CUSTOMER_XML(id,type)    "\n<customer id=\""##+id+##"\" type=\""##+type+##"\">\n"
#define _STOP_CUSTOMER_XML		        "\n</customer>\n"

#define PRODUCT_TO_XML_FIELDS(product_V)                                \
        "<name>" + product_V[2] + "</name>\n" +                         \
        "<manufacturer>" + product_V[3] + "</manufacturer>\n" +         \
        "<diameter>" + product_V[4] + "</diameter>\n" +                 \
        "<quantity>" + product_V[5] + "</quantity>\n" +                 \
        "<price>" + product_V[6] + "</price>\n"

#define RIM_TO_XML_FIELDS(rim_V)                                        \
        PRODUCT_TO_XML_FIELDS(rim_V)                                    \
        +                                                               \
        "<width>"    + rim_V[7] + "</width>\n" +                        \
        "<material>" + rim_V[8] + "</material>\n" +                     \
        "<color>"    + rim_V[9] + "</color>\n"

#define TYRE_TO_XML_FIELDS(tyre_V)                                      \
        PRODUCT_TO_XML_FIELDS(tyre_V)                                   \
        +                                                               \
        "<width>" + tyre_V[7] + "</width>\n" +                          \
        "<speedIndex>" + tyre_V[8] + "</speedIndex>\n" +                \
        "<height>" + tyre_V[9] + "</height>\n" +                        \
        "<tyreMarkings>" + tyre_V[10] + "</tyreMarkings>\n"

#define CUSTOMER_TO_XML_FIELDS(customer_V)                              \
        "<firstname>" + customer_V[1] + "</firstname>\n" +              \
        "<lastname>" + customer_V[2] + "</lastname>\n" +                \
        "<address>\n" +                                                   \
            "<country>" + customer_V[4] + "</country>\n" +              \
            "<postalcode>" + customer_V[5] + "</postalcode>\n" +        \
            "<streetname>" + customer_V[6] + "</streetname>\n" +        \
            "<housenumber>" + customer_V[7] + "</housenumber>\n" +      \
            "<phonenumber>" + customer_V[8] + "</phonenumber>\n" +      \
        "</address>\n"

#define CUSTOMER_TO_XML(customer_V)                                 \
        _START_CUSTOMER_XML(customer_V[0],customer_V[3]) +          \
        CUSTOMER_TO_XML_FIELDS(customer_V) +                        \
        _STOP_CUSTOMER_XML
#define RIM_TO_XML(rim_V)                                           \
        _START_PRODUCT_XML(rim_V[0],rim_V[1]) +                     \
        RIM_TO_XML_FIELDS(rim_V) +                                  \
        _STOP_PRODUCT_XML
#define TYRE_TO_XML(tyre_V)                                         \
        _START_PRODUCT_XML(tyre_V[0],tyre_V[1])                     \
        TYRE_TO_XML_FIELDS(tyre_V) +                                \
        _STOP_PRODUCT_XML


// temp files *////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INVOICE_H_X_FROM_Y(x,y)		"Invoice_"##+x+##"_Customer_"##+y
#define _CSV(name)					name+##".csv"			
#define _TXT(name)					name+##".txt"
#define _BIN(name)					name+##".bin"
#define _XML(name)					name+##".xml"

// standard configurations *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// standard string length in the program !!! IF CHANGED => binary files will not be read correctly
#define STR_LENGTH					    50
#define MAX_ROW_COUNT				    10
// standard minimum length for customer attributes
#define CUSTOMER_FIRSTNAME_MIN_LEN      2
#define CUSTOMER_LASTNAME_MIN_LEN       2
#define CUSTOMER_COUNTRY_MIN_LEN        3
#define CUSTOMER_POSTALCODE_MIN_LEN     4
#define CUSTOMER_STREETNAME_MIN_LEN     4
#define CUSTOMER_HOUSENUMBER_MIN_LEN    1
#define CUSTOMER_PHONENUMBER_MIN_LEN    9
// standard minimum length for product attributes
#define PRODUCT_NAME_MIN_LEN            4
#define PRODUCT_MANUFACTURER_MIN_LEN    4
#define PRODUCT_QUANTITY_MIN_LEN        1
#define PRODUCT_DIAMETER_MIN_LEN        1
#define PRODUCT_PRICE_MIN_LEN           1
#define PRODUCT_WIDTH_MIN_LEN           2
// standard minimum length for tyre attributes
#define PRODUCT_HEIGHT_MIN_LEN          1
#define PRODUCT_MARKINGS_MIN_LEN        4
// standard minimum length for rim attributes
#define PRODUCT_COLOR_MIN_LEN           4
// standard minimum length for user's
#define MIN_PWD_LENGTH                  10
#define MIN_USERNAME_LENGTH             5


/* Enum's *////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Structures *////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Functions */////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void line(int, char);
void cursor(void);
int input(int, int);

#endif // !TYRECENTER

#ifndef COMPANY_DATABASE_PRIVATE
#define COMPANY_DATABASE_PRIVATE
#include "CompanyDatabase_int.h"

Employee * create_node (void) ;
char validate_EmployeeName ( char ** temp_string ) ;
char validate_EmployeeNumber ( char ** temp_string  ) ;
char validate_EmployeeEmail ( char ** temp_string  ) ;
char validate_EmployeeBirthDate ( char ** temp_string  ) ;
char validate_EmployeeJob ( char ** temp_string  ) ;
unsigned long getFile_Information (char *fileName ,char ** fileInfo) ;
void determine_leapYear ( unsigned short user_year ) ;
char getEffectiveString (char * fileInfo, char ** tempString, char check_char , unsigned long *fileInfo_index , char flag) ;
void optomizeName ( char ** temp_string ) ;
void optomizeJob ( char ** temp_string ) ;
char sort_two_strings (char * string_1 , char * string_2 ) ;
char * print_scan_EmployeeElments (unsigned long printf_parameter, char validation_function (char **) ) ;
void free_employElments (Employee * temp_Employee) ;
void insertNode ( Employee *nodePtr ) ;
Employee*  createNode ( void ) ;
Employee* searchNode ( char *employeeName ) ;
Employee* deleteNode ( char *employeeName ) ;
char sort_1 (Employee * temp_Employee_1, Employee * temp_Employee_2 , unsigned long algorithm) ;

#endif

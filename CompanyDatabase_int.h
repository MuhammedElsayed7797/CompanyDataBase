#ifndef COMPANY_DATABASE_INT
#define COMPANY_DATABASE_INT

#define MAX_NAME_LENGTH 151
#define MAX_NUMBER_LENGTH 12
#define MAX_EMAIL_LENGTH 101
#define MAX_BIRTH_LENGTH 11
#define MIN_EMPLOYEE_YEAR 1959
#define MAX_EMPLOYEE_YEAR 1996
#define MAX_JOB_LENGTH 101
#define JOB_TITLES_FILE "CompanyInfo.txt"
#define EMPLOYEES_FILE "CompanyDatabase.txt"
#define FORMAT_FILE "formatFile.txt"
#define SAVE_FILE "saveData.txt"
#define TEMP_FILE "tempFile.txt"
#define FORMAT_LENGTH 200

typedef unsigned long u32 ;

typedef struct Employee
{
    char * Employee_phoneNumber ;
    char * Employee_name ;
    char * Employee_email ;
    char * Employee_birthDate ;
    char * Employee_jobTittle ;
    struct Employee * Employee_nextPtr ;
    struct Employee * Employee_prePtr ;

}Employee ;

struct
{
    Employee * Employee_firsPtr ;
    Employee * Employee_lastPtr ;
    u32 Employees_number ;
} Employee_list  ;

char initialization (void) ;
char ADD_Employee (void) ;
char LOAD_Employee (char * fileName) ;
char SEARCH_Employee (void) ;
char DELETE_Employee (void) ;
void SAVE_Employee (char * fileName) ;
char MODIFY_Employee (void) ;
char SORT_Employee (unsigned long user_choose) ;

#endif

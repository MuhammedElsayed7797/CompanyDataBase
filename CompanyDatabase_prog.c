#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CompanyDatabase_int.h"
#include "CompanyDatabase_private.h"

struct
{
    unsigned long year ;
    unsigned char month ;
    unsigned char day ;
}ref_date = {2020, 1, 1} ; /* used by function determineLeapYear */

unsigned char days_in_month [12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ; /* used by function determineLeapYear */
char * jobTitles_fileInfo = NULL ; /* to contain all available job titles */
char * format_fileInfo = NULL ; /* to contain strings of printf and scanf in add employee */
char * printf_string = NULL, * scanf_string = NULL ;
static unsigned long format_fileInfo_index = 0 , global_counter = 0 ;
unsigned long global_algorithm = 1 ;

/****************************************************************************/
char initialization (void) /* used to initialize Employ list and to scan job titles file and optimize it to used later in validation */
{
    char * temp_string = NULL , * temp_jobTitles_fileInfo = NULL ;

    unsigned long jobTitles_fileInfo_index = 0 ;
    Employee_list.Employees_number = 0 ;
    Employee_list.Employee_firsPtr = NULL ;
    Employee_list.Employee_lastPtr = NULL ;

    printf_string = (char *) malloc( sizeof(char) * FORMAT_LENGTH ) ; /* free before return */
    scanf_string = (char *) malloc( sizeof(char) * FORMAT_LENGTH ) ; /* free before return */

    if ( ! getFile_Information(FORMAT_FILE, &format_fileInfo) ) /* scan all characters in JOB_TITLES_FILE*/
    {
        printf("\n%s file not exist please check file", JOB_TITLES_FILE);
        return 1 ;
    }

    if ( ! getFile_Information(JOB_TITLES_FILE, &jobTitles_fileInfo) ) /* scan all characters in JOB_TITLES_FILE*/
    {
        printf("\nfile not exist please check file");
        return 1 ;
    }

    temp_jobTitles_fileInfo = (char *) malloc( sizeof(char) * (strlen(jobTitles_fileInfo)+1) ) ; /* free before return */
    * temp_jobTitles_fileInfo = '\0' ; /*to avoid garbage in strcat with temp string */
    temp_string = (char *) malloc( sizeof(char) * MAX_JOB_LENGTH ) ; /* free before return */

    while ( getEffectiveString(jobTitles_fileInfo, &temp_string, '.', &jobTitles_fileInfo_index, 0) )  /* to get pieces of string separated by '.' */
    {
        optomizeJob(&temp_string) ;  /* to eliminate extra white spaces */

        if ('.' != temp_string[0]) /* when to successive '.' is exit will return '.'*/
        {
            strcat(temp_jobTitles_fileInfo, temp_string) ;
        }
    }
    free(jobTitles_fileInfo);
    free(temp_string) ;
    jobTitles_fileInfo = temp_jobTitles_fileInfo ;
    jobTitles_fileInfo = realloc(jobTitles_fileInfo, strlen(jobTitles_fileInfo)+ 1);

    return 0 ;
}

/****************************************************************************/

char ADD_Employee (void)
{
    char * temp_string = NULL  , * employElements [5] = {0} ;
    unsigned long maxLength [5] = {MAX_NAME_LENGTH, MAX_NUMBER_LENGTH, MAX_EMAIL_LENGTH, MAX_BIRTH_LENGTH, MAX_JOB_LENGTH} , counter = 0 ;
    Employee * temp_Employee = NULL ;
    char ( * validate_functions [5] ) (char **) = {validate_EmployeeName, validate_EmployeeNumber, validate_EmployeeEmail, validate_EmployeeBirthDate, validate_EmployeeJob } ;
    temp_Employee = create_node () ;

    printf("\nto exit and return from this function enter '0' \n\n");

    for (counter = 0 ; counter< 5 ; counter ++)
    {
        if ( ! (temp_string = print_scan_EmployeeElments ( maxLength[counter], validate_functions[counter] ) ) )
        {
            free_employElments (temp_Employee) ;
            free(temp_Employee);
            return  0 ;
        }
        employElements [counter]= temp_string ;
    }

    temp_Employee->Employee_name = employElements[0] ;
    temp_Employee->Employee_phoneNumber = employElements[1] ;
    temp_Employee->Employee_email = employElements[2] ;
    temp_Employee->Employee_birthDate = employElements[3] ;
    temp_Employee->Employee_jobTittle = employElements[4] ;
    insertNode(temp_Employee) ;
    printf("\nemployee added successfully") ;
    return 1 ;
}

/****************************************************************************/

char LOAD_Employee (char * fileName)
{
    Employee * temp_Employee = NULL ;
    char * LOAD_employeesInfo = NULL , * temp_ptr = NULL, * employ_Info = NULL , * temp_string = NULL , flag = 0, flag_2 = 0 , *temp_ptr_2 = NULL ;
    char  * employElements [5] = {0}  ;
    unsigned long LOAD_employeesInfo_index = 0  , employ_Info_index = 0 ;
    unsigned long counter = 0 , counter_2 = 0 ;
    signed long counter_3 = 0 ;
    char ( * validate_functions [5] ) (char **) = {validate_EmployeeName, validate_EmployeeNumber, validate_EmployeeEmail, validate_EmployeeBirthDate, validate_EmployeeJob } ;

    printf("\nplease note every employee's section in file");
    printf("\nincluding white spaces mustn't exceed size of %d",MAX_NAME_LENGTH + MAX_NUMBER_LENGTH + MAX_EMAIL_LENGTH + MAX_BIRTH_LENGTH + MAX_JOB_LENGTH + 1);
    printf("\n\n\n");
    temp_ptr = (char *) malloc( sizeof(char) * (MAX_NAME_LENGTH + MAX_NUMBER_LENGTH + MAX_EMAIL_LENGTH + MAX_BIRTH_LENGTH + MAX_JOB_LENGTH) ) ;
    employ_Info = (char *) malloc( sizeof(char) * (MAX_NAME_LENGTH + MAX_NUMBER_LENGTH + MAX_EMAIL_LENGTH + MAX_BIRTH_LENGTH + MAX_JOB_LENGTH) ) ;

    temp_Employee = create_node () ;

    if ( ! getFile_Information(fileName, &LOAD_employeesInfo) )
    {
        printf("\n%s file not exist please check file",fileName);
        return 1 ;
    }
    while ( '"' != LOAD_employeesInfo [counter])
    {
        counter ++ ;
    }
    LOAD_employeesInfo = &(LOAD_employeesInfo [counter]) ;
    counter_2 ++ ;
    while(LOAD_employeesInfo[counter_2] != '\0')
    {
        if ( ('"' == LOAD_employeesInfo[counter_2] ) &&  (0 == flag_2 ) )
        {
            LOAD_employeesInfo[counter_2] = ' ' ;
            flag_2 = 1 ;
        }
        else if ( ('"' == LOAD_employeesInfo[counter_2] ) )
        {
            flag_2 = 0 ;
        }

        counter_2 ++ ;
    }
    LOAD_employeesInfo[counter_2-1] = '"' ;

    counter_2 = 0 ;
    while ( getEffectiveString(LOAD_employeesInfo, &temp_ptr, '"', & LOAD_employeesInfo_index,0) )
    {
        employ_Info_index = 0 ;
        if (flag)
        {
            flag = 0 ;
            printf("\nerror in employee number : %lu",counter_2);
        }

        strcpy(employ_Info, temp_ptr) ;
        temp_ptr_2 = strchr(employ_Info, '"');

        temp_ptr_2[0] = ',' ;
        temp_ptr_2[1] = '\0' ;

        temp_Employee = create_node () ;
        counter_2 ++ ;

        for (counter_3 = 0 ; counter_3 < 5 ; counter_3 ++)
        {

            temp_string = (char *) malloc( sizeof(char) * (MAX_NAME_LENGTH ) ) ; /* won't be freed*/

            getEffectiveString(employ_Info, &temp_string, ',', &employ_Info_index,1) ;
            optomizeJob(&temp_string) ;

            if ((validate_functions[counter_3])(&temp_string))
            {
                counter_3 -- ;
                while (counter_3 >= 0)
                {
                    free(employElements [counter_3]);
                    counter_3 -- ;
                }

                free(temp_Employee);
                flag = 1 ;
                counter_3 = 6 ;

                break ;
            }
            else
            {
                employElements [counter_3] = temp_string ;
            }
        }
        if ( counter_3 == 6 )
        {
            continue ;
        }

        temp_Employee->Employee_name = employElements[0] ;
        temp_Employee->Employee_phoneNumber = employElements[1] ;
        temp_Employee->Employee_email = employElements[2] ;
        temp_Employee->Employee_birthDate = employElements[3] ;
        temp_Employee->Employee_jobTittle = employElements[4] ;
        insertNode(temp_Employee) ;
    }
    LOAD_employeesInfo -= counter ;
    free(LOAD_employeesInfo) ;
    printf("\nLoad done successfully") ;
    return 0 ;
}

/****************************************************************************/

char SEARCH_Employee (void)
{
    char *employName = NULL ;
    Employee * temp_Employee = NULL ;

    employName = print_scan_EmployeeElments(MAX_NAME_LENGTH,validate_EmployeeName) ;
    format_fileInfo_index = 0 ;
    global_counter = 0 ;

    if (NULL == employName)
    {
        return 0 ;
    }
    temp_Employee = searchNode (employName) ;
    if (temp_Employee)
    {
        printf("\nEmployee Name : %s",temp_Employee->Employee_name);
        printf("\nEmployee Phone Number : %s",temp_Employee->Employee_phoneNumber);
        printf("\nEmployee Email : %s",temp_Employee->Employee_email);
        printf("\nEmployee Birth date : %s",temp_Employee->Employee_birthDate);
        printf("\nEmployee Job title : %s",temp_Employee->Employee_jobTittle);
        printf("\n\n\n") ;
    }
    else
    {
        printf("\nNO Employee with this name please check entered name ");
    }
    return 1;
}

/****************************************************************************/

char DELETE_Employee (void)
{
    char *employName = NULL ;
    Employee * temp_Employee = NULL ;

    employName = print_scan_EmployeeElments(MAX_NAME_LENGTH,validate_EmployeeName) ;
    format_fileInfo_index = 0 ;
    global_counter = 0 ;
    if (NULL == employName)
    {
        return 0 ;
    }

    temp_Employee = deleteNode(employName) ;

    if (temp_Employee)
    {
        free_employElments(temp_Employee);
        free(temp_Employee);
        printf("\nemployee deleted successfully") ;
    }
    else
    {
        printf("\nNO Employee with this name please check entered name ");
    }
    return 1 ;
}

/****************************************************************************/

void SAVE_Employee (char * fileName)
{
    FILE * fpointer_1 = NULL ;
    Employee * temp_Employee = NULL ;

    fpointer_1 = fopen( fileName, "w" ) ;     /* open database file to write it */
    temp_Employee = Employee_list.Employee_firsPtr ;
    while (temp_Employee)
    {
        fprintf(fpointer_1,"\"") ;
        fprintf(fpointer_1," %s, ",temp_Employee->Employee_name) ;
        fprintf(fpointer_1,"%s, ",temp_Employee->Employee_phoneNumber) ;
        fprintf(fpointer_1,"%s, ",temp_Employee->Employee_email) ;
        fprintf(fpointer_1,"%s, ",temp_Employee->Employee_birthDate) ;
        fprintf(fpointer_1,"%s ",temp_Employee->Employee_jobTittle) ;
        fprintf(fpointer_1,"\"") ;
        fprintf(fpointer_1,"\n") ;
        temp_Employee = temp_Employee->Employee_nextPtr  ;
    }
    fclose(fpointer_1) ;
    printf("\nData saved successfully");
    return ;
}

/****************************************************************************/

char MODIFY_Employee (void)
{
    char *employName = NULL , counter = 0 , flag = 0 ;
    unsigned long user_chose = 0 ;
    unsigned long maxLength [5] = {MAX_NAME_LENGTH, MAX_NUMBER_LENGTH, MAX_EMAIL_LENGTH, MAX_BIRTH_LENGTH, MAX_JOB_LENGTH} ;
    Employee * temp_Employee = NULL ;
    char ( * validate_functions [5] ) (char **) = {validate_EmployeeName, validate_EmployeeNumber, validate_EmployeeEmail, validate_EmployeeBirthDate, validate_EmployeeJob } ;

    employName = print_scan_EmployeeElments(MAX_NAME_LENGTH,validate_EmployeeName) ;
    format_fileInfo_index = 0 ;
    global_counter = 0 ;

    if (NULL == employName)
    {
        return 0 ;
    }

    temp_Employee = searchNode (employName) ;
    if (!temp_Employee)
    {
       printf("\nNO Employee with this name please check entered name ");
       return 1 ;
    }

    while (1)
    {
        printf("\nplease select option to modify \nnote any modification won't be ignored");
        printf("\n1: Modify Name");         printf("\t\t2: Modify Phone Number");
        printf("\n3: Modify Email");        printf("\t\t4: Modify Birth Date");
        printf("\n5: Modify Job_Title");    printf("\t6: Exit");
        printf("\n");
        scanf("%lu",&user_chose);
        fflush(stdin) ;
        for (counter = 0 ; counter < user_chose-1 ; counter ++)
        {
            getEffectiveString(format_fileInfo, &printf_string, '.', &format_fileInfo_index, 1);
            getEffectiveString(format_fileInfo, &scanf_string, '.', &format_fileInfo_index, 1);
        }

        switch (user_chose)
        {
            case 1 :
            {
                employName = print_scan_EmployeeElments( maxLength[user_chose-1], validate_functions[user_chose-1] ) ;
                free(temp_Employee->Employee_name) ;
                temp_Employee->Employee_name = employName ;
                printf("\nmodified successfully");
                break ;
            }

            case 2 :
            {
                employName = print_scan_EmployeeElments( maxLength[user_chose-1], validate_functions[user_chose-1]) ;
                free(temp_Employee->Employee_phoneNumber) ;
                temp_Employee->Employee_phoneNumber = employName ;
                printf("\nmodified successfully");
                break ;
            }

            case 3 :
            {
                employName = print_scan_EmployeeElments( maxLength[user_chose-1],validate_functions[user_chose-1]) ;
                free(temp_Employee->Employee_email) ;
                temp_Employee->Employee_email = employName ;
                printf("\nmodified successfully");
                break ;
            }

            case 4 :
            {
                employName = print_scan_EmployeeElments( maxLength[user_chose-1],validate_functions[user_chose-1]) ;
                free(temp_Employee->Employee_birthDate) ;
                temp_Employee->Employee_birthDate = employName ;
                printf("\nmodified successfully");
                break ;
            }

            case 5 :
            {
                employName = print_scan_EmployeeElments( maxLength[user_chose-1],validate_functions[user_chose-1]) ;
                free(temp_Employee->Employee_jobTittle) ;
                temp_Employee->Employee_jobTittle = employName ;
                printf("\nmodified successfully");
                break ;
            }

            case 6 :
            {
                flag = 1 ;
                break ;
            }

            default :
            {
                printf("\ninvalid option") ;
                break ;
            }
        }
        printf("\n\n\n");
        format_fileInfo_index = 0 ;
        global_counter = 0 ;
        if (flag)
        {
            break ;
        }
    }
    return 0 ;
}

/****************************************************************************/

char SORT_Employee (unsigned long user_choose)
{
    Employee * temp_Employee =  NULL ;
    if (0 == user_choose)
    {
        return 0 ;
    }
    else if (user_choose > 0 && user_choose < 5)
    {
        global_algorithm = user_choose ;
        temp_Employee = Employee_list.Employee_firsPtr ;
        SAVE_Employee (TEMP_FILE) ;
        while (temp_Employee)
        {
            deleteNode(temp_Employee->Employee_name) ;
            temp_Employee = temp_Employee->Employee_nextPtr ;
        }

        LOAD_Employee(TEMP_FILE) ;
        printf("\nDate sorted successfully");
        return 0 ;
    }
    else
    {
        printf("\ninvalid option try again or enter '0' to exit\n") ;
        return 1 ;
    }
    return 0 ;
}


/****************************************************************************/

char validate_EmployeeName ( char ** temp_string  )
{
    unsigned char counter = 0  , counter_2 = 0 ;
    strlwr((*temp_string)) ;
    while ((*temp_string) [counter_2] == ' ')
    {
        counter_2 ++ ;
    }

    while (counter < MAX_NAME_LENGTH)
    {
        if ( ( ((*temp_string) [counter] >= 'A') && ((*temp_string) [counter] <= 'z') ) || ((*temp_string) [counter] == ' ') )
        {

        }
        else if ( ((*temp_string) [counter] == '\0') && (counter != counter_2) )
        {
            optomizeName(&(*temp_string));
            return 0 ;
        }
        else
        {
            printf("\ninvalid name contain non allowed characters or empty ");
            return 1 ;
        }
        counter ++ ;
    }

    printf("\ninvalid name exceed maximum allowed characters");
    return 1 ;
}

/****************************************************************************/

char validate_EmployeeNumber ( char ** temp_string  )
{
    unsigned char counter = 0 ;
    if ( '0' != (*temp_string)[counter++] )
    {

    }
    else if ( '1' != (*temp_string)[counter++] )
    {

    }
    else if ( ('0' != (*temp_string)[counter]) && ('1' != (*temp_string)[counter]) && ( '2'!= (*temp_string)[counter]) && ('5' != (*temp_string)[counter]) )
    {

    }
    else
    {
        counter ++ ;
        while (counter < MAX_NUMBER_LENGTH)
        {
            if ( ( ((*temp_string) [counter] >= '0') && ((*temp_string) [counter] <= '9') ) )
            {

            }
            else if ( ((*temp_string) [counter] == '\0') )
            {
                if (counter != MAX_NUMBER_LENGTH-1)
                {
                    break ;
                }
                else
                {
                    return 0 ;
                }

            }
            else
            {
                printf("\ninvalid number contain non allowed characters or empty ");
                return 1 ;
            }
            counter ++ ;
        }
        printf("\ninvalid number missing numbers or exceed allowed characters");
        return 1 ;
    }
    printf("\ninvalid number");
    return 1 ;
}

/****************************************************************************/

char validate_EmployeeEmail ( char ** temp_string  )
{
    unsigned char counter = 0 ;
    char * website = NULL ;
    char Yahoo [11]= "@yahoo.com" ;
    char Gmail [11]= "@gmail.com" ;
    optomizeJob(temp_string) ;
    strlwr ((*temp_string));
    website = strrchr((*temp_string), '@') ;
    if ( NULL == website)
    {
        printf("\ninvalid website");
        return 1 ;
    }
    if ( ( 0 != strcmp(website , Yahoo) ) && ( 0 != strcmp(website , Gmail) ) )
    {
        printf("\ninvalid website");
        return 1 ;
    }

    else
    {
        website [0] = '\0' ;
        while (counter < MAX_EMAIL_LENGTH )
        {
            if ( (( ((*temp_string) [counter] >= '0') && ((*temp_string) [counter] <= '9') )) || (( ((*temp_string) [counter] >= 'A') && ((*temp_string) [counter] <= 'z') )) || (*temp_string) [counter] == '_' || (*temp_string) [counter] == '.')
            {

            }
            else if ( ((*temp_string) [counter] == '\0') )
            {
                website [0] = '@' ;
                (*temp_string) = realloc((*temp_string), strlen((*temp_string))+1 );
                return 0 ;
            }
            else
            {
                printf("\ninvalid mail contain non allowed characters or empty ");
                return 1 ;
            }
            counter ++ ;
        }
        printf("\ninvalid  email exceed allowed characters");
        return 1 ;
    }
    return 1 ;
}


/****************************************************************************/

char validate_EmployeeBirthDate ( char ** temp_string  )
{
    unsigned char counter = 0 ,day = 0, month = 0 ;
    unsigned short year = 0 ;
    if ( MAX_BIRTH_LENGTH-1 != strlen((*temp_string)) )
    {

    }
    else if ( '/' != (*temp_string) [2] || '/' != (*temp_string) [5] )
    {

    }
    else
    {
        while (counter < MAX_BIRTH_LENGTH-1)
        {
            if( ( ((*temp_string) [counter] < '0') || ((*temp_string) [counter] > '9') ) && ((*temp_string) [counter] != '/') )
            {
                printf("\ninvalid birth date contain non allowed characters");
                return 1 ;
            }
            counter ++ ;
        }
        day = ((*temp_string)[0]-48)*10 ;
        day += (*temp_string)[1]-48 ;

        month = ((*temp_string)[3]-48)*10 ;
        month += (*temp_string)[4]-48 ;

        year =  ((*temp_string)[6]-48)*1000 ;
        year += ((*temp_string)[7]-48)*100 ;
        year += ((*temp_string)[8]-48)*10 ;
        year += ((*temp_string)[9]-48) ;
        if ( (year >= MIN_EMPLOYEE_YEAR ) && (month <= MAX_EMPLOYEE_YEAR ) )
        {
            determine_leapYear (year) ;
            if ( (month > 0 ) && (month <= 12 ) )
            {
                if ( (day > 0 ) && (day <= days_in_month[month-1] ) )
                {
                    return 0 ;
                }
            }
        }
        printf("\ninvalid birth date input");
        return 1 ;
    }
    printf("\ninvalid birth date format");
    return 1 ;
}

/****************************************************************************/

char validate_EmployeeJob ( char ** temp_string  )
{
    char * temp_ptr = NULL , *temp_ptr_2 = NULL, * temp_string_2 , cons[2] = ".";
    temp_string_2 = (char *) malloc( sizeof(char) * MAX_JOB_LENGTH ) ; /* freed before return */
    temp_ptr_2 = (char *) malloc( sizeof(char) * (strlen(jobTitles_fileInfo) + 1) ) ; /* freed before return */

    optomizeJob(&(*temp_string)) ;
    strcpy(temp_ptr_2,jobTitles_fileInfo) ;
    strlwr((*temp_string)) ;
    temp_ptr = strtok(temp_ptr_2,cons) ;
    strcpy(temp_string_2, temp_ptr) ;
    strlwr(temp_ptr) ;

    do
    {
        if (!strcasecmp(temp_ptr,(*temp_string)))
        {
            break ;
        }
        else
        {
            temp_ptr = strtok(NULL,cons) ;
            if (temp_ptr)
            {
                strcpy(temp_string_2, temp_ptr) ;
                strlwr(temp_ptr) ;
            }
        }
    }while (NULL != temp_ptr) ;
    strcpy((*temp_string), temp_string_2) ;
    free(temp_ptr_2);
    free(temp_string_2);
    if (NULL != temp_ptr)
    {
        (*temp_string) = realloc( (*temp_string), (strlen((*temp_string))+1) ) ;
        return 0 ;
    }
    else
    {
        printf("\ninvalid job title");
        return 1 ;
    }
}

/****************************************************************************/

void  optomizeName ( char ** temp_string )
{
    unsigned char counter = 0 ,counter_2  = 0 ;
    char * temp_string_2 = NULL ;
    temp_string_2 = (char *) malloc( sizeof(char) * MAX_NAME_LENGTH ) ; /* free before return */

    while ( (*temp_string) [counter] != '\0' ) /* to eliminate extra white spaces and capitalize first characters */
    {

        if ( (*temp_string) [counter] == ' ' && (*temp_string) [counter+1] != ' ' && (*temp_string) [counter+1] != '\0')
        {
            if ( (*temp_string) [counter+1] >=97)
            {
                (*temp_string) [counter+1] -= 32 ;
            }

            if (counter_2 != 0  )
            {
                temp_string_2[counter_2] = ' ' ;
                counter_2 ++ ;
            }

        }
        else if ( (*temp_string) [counter] != ' ' )
        {
            if ( 0 == counter && (*temp_string) [counter] >=97)
            {
                (*temp_string) [counter] -= 32 ;
            }
            temp_string_2[counter_2] = (*temp_string) [counter] ;
            counter_2 ++ ;
        }
        counter ++ ;
    }
    temp_string_2[counter_2] = '\0' ;
    strcpy( (*temp_string) , temp_string_2) ;
    (*temp_string) = realloc( (*temp_string), (strlen((*temp_string))+1) ) ;
    free (temp_string_2) ;

    return  ;
}

/****************************************************************************/

void optomizeJob ( char ** temp_string )
{

    unsigned char counter = 0 ,counter_2  = 0 ;
    char * temp_string_2 = NULL ;

    temp_string_2 = (char *) malloc( sizeof(char) * MAX_JOB_LENGTH ) ; /* free before return */

    while ( (*temp_string) [counter] != '\0' ) /* to eliminate extra white spaces and capitalize first characters */
    {

        if ( ( (*temp_string) [counter] == ' ' ||  (*temp_string) [counter] == '\n' )&& ( (*temp_string) [counter+1] != ' ' && (*temp_string) [counter+1] != '\n' )&& (*temp_string) [counter+1] != '\0')
        {

            if (counter_2 != 0  )
            {
                temp_string_2[counter_2] = ' ' ;
                counter_2 ++ ;
            }

        }
        else if ( (*temp_string) [counter] != ' ' && (*temp_string) [counter] != '\n' && (*temp_string) [counter] != '\t')
        {
            temp_string_2[counter_2] = (*temp_string) [counter] ;
            counter_2 ++ ;
        }
        counter ++ ;
    }
    temp_string_2[counter_2] = '\0' ;
    strcpy( (*temp_string) , temp_string_2) ;
    free (temp_string_2) ;

    return  ;
}

/****************************************************************************/

void determine_leapYear ( unsigned short user_year ) /* to determine which if passed year is a leap year or not */
{
    signed short year_diff = 0 ;

    year_diff = user_year - ref_date.year ;

    if ( 0 == year_diff%4 )
    {
        days_in_month [1] = 29 ;
    }
    else
    {
        days_in_month [1] = 28 ;
    }
    return ;
}

/****************************************************************************/

unsigned long getFile_Information (char *fileName ,char ** fileInfo) /* to get all character inside a file and put them in dynamic array */
{
    FILE * fpointer_1 = NULL, * fpointer_2 = NULL ;    /* pointer to file which will point to */
    char tempChar = 0 ;       /* used to determine number of characters in file */
    unsigned long numberOf_fCharacters = 0;     /* used to store number of characters in file */
    unsigned long fileInfo_index = 0 ;       /* used to index the memory store data inside file */

    fpointer_1 = fopen( fileName, "r" ) ;     /* open database file to read it */
    fpointer_2 = fopen( fileName, "r" ) ;     /* open database file to read it */

    if ( NULL == fpointer_1 ) /* can't open file with this name -> fileName */
	{

		printf( "Could not open file\n" );
        return 0 ; /* failure */
	} /* if */

	else
    {

        while(  EOF != tempChar )  /* scan every character in array till its end */
		{

			tempChar = fgetc(fpointer_1);
			numberOf_fCharacters ++ ;

		} /* while */

        tempChar = 0 ;
		fclose( fpointer_1 ) ;  /* close database file to read it */


		*fileInfo = (char *) malloc( sizeof(char) * numberOf_fCharacters ) ; /* allocate memory contain all file data */

		while(  EOF != tempChar )  /* scan every character in array till its end and store them inside fileInfo */
		{

			tempChar = fgetc(fpointer_2);   //Storing the number into the array
            (*fileInfo)[fileInfo_index] = tempChar ;
			fileInfo_index ++;

		}   /* while */

        (*fileInfo)[numberOf_fCharacters-1] = '\0' ; /* to terminate string */
        fclose( fpointer_2 ) ;  /* close database file to read it */
        return   numberOf_fCharacters ;
    } /* else */


}

/****************************************************************************/

char getEffectiveString (char * fileInfo, char ** tempString, char check_char , unsigned long *fileInfo_index , char flag) /* to get names of categories and sub categories in temp string*/
{
    unsigned char tempCounter = 0 ;     /* used as temporary counter*/

    while( ( check_char != fileInfo[(*fileInfo_index)] || 0 == tempCounter )&& fileInfo[(*fileInfo_index)] != '\0')  /* to count number of characters in one effective string */\
    {
        if( check_char != fileInfo[(*fileInfo_index)])
        {
            tempCounter ++ ;
        }
        (*fileInfo_index) ++ ;


    } /* while */

    (*fileInfo_index) -= tempCounter ;  /*get start of string */
    tempCounter = 0 ;
    while(  check_char != fileInfo[*fileInfo_index] && fileInfo[*fileInfo_index] != '\0')  /* to copy effective string in tempString pointer */
    {
        if (check_char != fileInfo[*fileInfo_index])
        {
            (*tempString)[tempCounter] = fileInfo[*fileInfo_index] ;
            tempCounter ++ ;
        }

        (*fileInfo_index) ++ ;


    } /* while */
    if (0 == flag)
    {
        (*tempString) [tempCounter++] = check_char ;
    }
    else
    {

    }
    (*tempString) [tempCounter] = '\0' ;   /*to terminate string */

    if ( '\0' == fileInfo[(*fileInfo_index)] ) /* end of information of file */
    {

        (*fileInfo_index) = 0 ; /* so when use this function again */
        return 0 ;
    } /* if */
    else
    {
        (*fileInfo_index) ++ ; /* to put index on start of new effective string */
        return 1 ;
    }

} /* function */

/****************************************************************************/

char sort_two_strings (char * string_1 , char * string_2 ) /* to sort two string according to their characters */
{
    unsigned char counter = 0 ;
    while(1)
    {

        if ( string_1[counter] < string_2[counter] )
        {
            return 1 ;
        }
        else if ( string_1[counter] > string_2[counter] )
        {
            return 0 ;
        }
        else if ( (string_1[counter] == '\0' ) && (string_2[counter] == '\0' ) )
        {
            return 2 ;
        }
        else
        {
            counter ++ ;
        }
    }
    return 0 ;
}

/****************************************************************************/

char * print_scan_EmployeeElments ( unsigned long printf_parameter, char validation_function (char **) ) /* scan string from user and validate it according to validation function*/
{
    char * temp_string = NULL , * printf_string = NULL, * scanf_string = NULL , check [2] = "0" ;

    printf_string = (char *) malloc( sizeof(char) * FORMAT_LENGTH ) ; /* free before return */
    scanf_string = (char *) malloc( sizeof(char) * FORMAT_LENGTH ) ; /* free before return */
    temp_string = (char *) malloc( sizeof(char) * (printf_parameter) ) ; /* won't be freed */
    getEffectiveString(format_fileInfo, &printf_string, '.', &format_fileInfo_index, 1);
    getEffectiveString(format_fileInfo, &scanf_string, '.', &format_fileInfo_index, 1);
    global_counter ++ ;
    if ( 5 == global_counter)
    {
        global_counter = 0 ;
        format_fileInfo_index = 0 ;
    }
    do
    {
        printf(printf_string, printf_parameter-1) ;
        scanf(scanf_string, temp_string);
        fflush(stdin); /* to prevent '\n' error */
    }
    while ( strcmp(temp_string, check) && validation_function (&temp_string) ) ;
    free (printf_string) ;
    free (scanf_string) ;
    if ( !strcmp(temp_string, check))
    {
        global_counter = 0 ;
        format_fileInfo_index = 0 ;
        free(temp_string) ;
        return NULL ;
    }

    return temp_string ;
}

/****************************************************************************/

void free_employElments (Employee * temp_Employee)  /* to free all elements inside employee's node */
{
    unsigned long counter = 0 ;
    char * employElements [5] = {0} ;
    employElements[0] = temp_Employee->Employee_name ;
    employElements[1] = temp_Employee->Employee_phoneNumber ;
    employElements[2] = temp_Employee->Employee_email ;
    employElements[3] = temp_Employee->Employee_birthDate ;
    employElements[4] = temp_Employee->Employee_jobTittle ;

    for (counter = 0 ; counter< 5 ; counter ++)
    {
        if (NULL == employElements[counter])
        {
            return ;
        }
        else
        {
            free(employElements[counter]) ;
        }
    }
    return ;
}

/****************************************************************************/

char sort_1 (Employee * temp_Employee_1, Employee * temp_Employee_2 , unsigned long algorithm)
{
    char * temp_string_1 = NULL,  * temp_string_2  = NULL ;
    unsigned long age_1 = 0 , age_2 = 0 ;
    unsigned char counter = 0 ;

    if ( (3 == algorithm) || (4 == algorithm) )
    {
        temp_string_1 = temp_Employee_1->Employee_birthDate ;
        temp_string_2 = temp_Employee_2->Employee_birthDate ;
        age_1  = temp_string_1[6]*1000*365 ;
        age_1 += temp_string_1[7]*100*365 ;
        age_1 += temp_string_1[8]*10*365 ;
        age_1 += temp_string_1[9]*1*365 ;
        age_1 += temp_string_1[4]*1*30 ;
        age_1 += temp_string_1[3]*10*30 ;
        age_1 += temp_string_1[1]*1;
        age_1 += temp_string_1[0]*10;

        age_2  = temp_string_2[6]*1000*365 ;
        age_2 += temp_string_2[7]*100*365 ;
        age_2 += temp_string_2[8]*10*365 ;
        age_2 += temp_string_2[9]*1*365 ;
        age_2 += temp_string_2[4]*1*30 ;
        age_2 += temp_string_2[3]*10*30 ;
        age_2 += temp_string_2[1]*1;
        age_2 += temp_string_2[0]*10;
    }
    else
    {
        temp_string_1 = temp_Employee_1->Employee_name ;
        temp_string_2 = temp_Employee_2->Employee_name ;
    }
    switch (algorithm)
    {
        case 1 :
        {
            while(1)
            {
                if (temp_string_1[counter] > temp_string_2[counter])
                {
                    return 1 ;
                }
                else if (temp_string_1[counter] < temp_string_2[counter])
                {
                    return 0 ;
                }
                else if ( (temp_string_1[counter] == '\0' ) && (temp_string_2[counter] == '\0' ) )
                {
                    return 2 ;
                }
                else
                {
                    counter ++ ;
                }
            }
            break ;
        }

        case 2 :
        {
            while(1)
            {
                if (temp_string_1[counter] < temp_string_2[counter])
                {
                    return 1 ;
                }
                else if (temp_string_1[counter] > temp_string_2[counter])
                {
                    return 0 ;
                }
                else if ( (temp_string_1[counter] == '\0' ) && (temp_string_2[counter] == '\0' ) )
                {
                    return 2 ;
                }
                else
                {
                    counter ++ ;
                }
            }
            break ;
        }

        case 3 :
        {
            if (age_1 > age_2)
            {
                return 1 ;
            }
            else if (age_1 < age_2)
            {
                return 0 ;
            }
            else
            {
                return 2 ;
            }
            break ;
        }


        case 4 :
        {
            if (age_1 < age_2)
            {
                return 1 ;
            }
            else if (age_1 > age_2)
            {
                return 0 ;
            }
            else
            {
                return 2 ;
            }
            break ;
        }
    }
    return 0 ;
}

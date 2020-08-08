#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CompanyDatabase_int.h"


int main(void)
{
    unsigned long user_option = 0 ;
    char file_name [100]= {0} , flag = 0;
    printf ("\nwelcome to CompanyDatabase\n");
    if ( initialization() )
    {
        return 0 ;
    }

    while (1)
    {
        printf("\nplease choose option number and follow its instruction to work in proper way");
        printf("\nenter '0' to quit from any option");
        printf("\n\n\n");
        printf("\n1: ADD EMPLOYEE");            printf("\t\t\t2: LOAD EPLOYEES");
        printf("\n3: DELETE EMPLOYEE");         printf("\t\t4: SAVE EPLOYEES");
        printf("\n5: SEARCH EMPLOYEE");         printf("\t\t6: MODIFY EPLOYEES");
        printf("\n7: SORT EPLOYEES");           printf("\t\t8: QUIT");
        printf("\n");
        scanf("%lu",&user_option);
        fflush(stdin);
        switch (user_option)
        {
            case 1 :
            {
                printf("\nenter '0' to quit");
                printf("\nthis option will scan employee's information one by one from you");
                while(ADD_Employee()) ;
                printf("\n\n\n") ;
                break ;
            }

            case 2 :
            {
                printf("\nenter '0' to quit");
                printf("\nenter a file name to load data from \nenter 1 to load from default file %s\n",EMPLOYEES_FILE);
                scanf("%s",file_name);
                fflush(stdin);
                if (!strcmp(file_name,"1"))
                {
                    LOAD_Employee(EMPLOYEES_FILE) ;
                }
                else if (!strcmp(file_name,"0"))
                {

                }
                else
                {
                    LOAD_Employee(file_name) ;
                }
                printf("\n\n\n") ;
                break ;
            }

            case 3 :
            {
                printf("\nenter '0' to quit");
                printf("enter name of employee to delete its data") ;
                while(DELETE_Employee());
                printf("\n\n\n") ;
                break ;
            }

            case 4 :
            {
                printf("\nenter '0' to quit");
                printf("\nenter name of file to save data in \nenter 1 to load from default file %s\n",SAVE_FILE) ;
                scanf("%s",file_name);
                fflush(stdin);
                if (!strcmp(file_name,"1"))
                {
                    SAVE_Employee(SAVE_FILE) ;
                }
                else if (!strcmp(file_name,"0"))
                {

                }
                else
                {
                    SAVE_Employee(file_name) ;
                }
                printf("\n\n\n") ;
                break ;
            }

            case 5 :
            {
                printf("\nenter '0' to quit");
                printf("\nthis option will search employee's data and display it \nplease enter name of employee to search");
                while(SEARCH_Employee()) ;
                printf("\n\n\n") ;
                break ;
            }

            case 6 :
            {
                printf("\nenter '0' to quit");
                printf("\nthis option will modify employee's data field by field \nplease enter name of employee to modify");
                while (MODIFY_Employee()) ;
                printf("\n\n\n") ;
                break ;
            }
            case 7 :
            {
                printf("\nenter '0' to quit");
                printf("\nthis option will determine how to sort data of employees in save option \nchoose from following options to sort according to :");
                printf("\n\n\n");
                printf("\n1: Name A~Z");
                printf("\n2: Name Z~A");
                printf("\n3: Age oldest first");
                printf("\n4: Age youngest first\n");

                scanf("%lu",&user_option) ;
                fflush(stdin) ;
                while (SORT_Employee(user_option))
                {
                    scanf("%lu",&user_option) ;
                    fflush(stdin) ;
                }
                printf("\n\n\n") ;
                break ;
            }
            case 8 :
            {
                printf("\nenter '0' to return main ");
                printf("\nthis will exit the program \nenter '1' to exit without save & '2' to save before exit\n");
                scanf("%s",file_name);
                fflush(stdin);
                if (!strcmp(file_name,"1"))
                {
                    flag = 1 ;
                }
                else if (!strcmp(file_name,"0"))
                {

                }
                else if (!strcmp(file_name,"2"))
                {
                    printf("\nenter name of file to save data in \nenter 1 to load from default file %s\n",SAVE_FILE) ;
                    scanf("%s",file_name);
                    fflush(stdin);
                    if (!strcmp(file_name,"1"))
                    {
                        SAVE_Employee(SAVE_FILE) ;
                    }
                    else
                    {
                        SAVE_Employee(file_name) ;
                    }
                    flag = 1 ;
                }
                else
                {
                    printf("\ninvalid option ") ;
                }
                printf("\n\n\n") ;
                break ;
            }
            default  :
            {
                printf("\ninvalid option please try again");
                break ;
            }
        }
        if (flag)
        {
            break ;
        }
    }

    return 0;
}


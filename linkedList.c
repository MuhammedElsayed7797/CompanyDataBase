#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CompanyDatabase_private.h"
#include "CompanyDatabase_int.h"

extern unsigned long global_algorithm ;
/**********************************************************************/

Employee * create_node (void)
{
    Employee * temp_Employee = NULL ;
    temp_Employee = (Employee *) malloc( sizeof(Employee) ) ;
    temp_Employee->Employee_nextPtr = NULL ;
    temp_Employee->Employee_prePtr = NULL ;
    temp_Employee->Employee_name = NULL ;
    temp_Employee->Employee_phoneNumber = NULL ;
    temp_Employee->Employee_email = NULL ;
    temp_Employee->Employee_birthDate = NULL ;
    temp_Employee->Employee_jobTittle = NULL ;
    return  temp_Employee ;
}

/**********************************************************************/

Employee* searchNode ( char *employeeName )
{

    Employee *tempNode_ptr = Employee_list.Employee_firsPtr ;
    if ( (NULL == tempNode_ptr) || ( NULL == employeeName) )
    {

        return NULL ;
    }

    while ( strcmp( tempNode_ptr->Employee_name, employeeName ) )
    {
        if ( NULL == tempNode_ptr->Employee_nextPtr )
        {
            return NULL ;
        }
        tempNode_ptr = tempNode_ptr->Employee_nextPtr ;
    }

    return tempNode_ptr ;

}

/**********************************************************************/

void insertNode ( Employee *nodePtr )
{
    Employee * temp_EmployeePtr = NULL , *temp_2_EmployeePtr = NULL ;
    Employee_list.Employees_number ++ ;
    if (1 == Employee_list.Employees_number )
    {
        Employee_list.Employee_firsPtr = nodePtr ;
        Employee_list.Employee_lastPtr = nodePtr ;

        return ;
    }
    temp_EmployeePtr = Employee_list.Employee_firsPtr ;
    temp_2_EmployeePtr = temp_EmployeePtr ;
    while (sort_1(nodePtr , temp_EmployeePtr , global_algorithm))
    {

        temp_2_EmployeePtr = temp_EmployeePtr ;
        temp_EmployeePtr = temp_EmployeePtr->Employee_nextPtr ;
        if (NULL == temp_EmployeePtr)
        {
            temp_EmployeePtr = temp_2_EmployeePtr ;
            temp_2_EmployeePtr = NULL ;
            break ;
        }
    }

    if(NULL ==  temp_2_EmployeePtr) /* last node*/
    {
        nodePtr->Employee_prePtr = temp_EmployeePtr ;
        nodePtr->Employee_nextPtr = NULL ;
        temp_EmployeePtr->Employee_nextPtr = nodePtr ;
        Employee_list.Employee_lastPtr = nodePtr ;
        return ;
    }

    if (NULL == temp_EmployeePtr->Employee_prePtr) /* first node */
    {

        nodePtr->Employee_nextPtr = temp_EmployeePtr ;
        nodePtr->Employee_prePtr = NULL ;

        temp_EmployeePtr->Employee_prePtr = nodePtr ;
        Employee_list.Employee_firsPtr = nodePtr ;

        return ;
    }
    else
    {
        nodePtr->Employee_nextPtr = temp_EmployeePtr ;
        nodePtr->Employee_prePtr = temp_EmployeePtr->Employee_prePtr ;
        temp_EmployeePtr->Employee_prePtr->Employee_nextPtr = nodePtr ;
        temp_EmployeePtr->Employee_prePtr = nodePtr ;
    }


    return ;
}

/**********************************************************************/

Employee* deleteNode ( char *employeeName )
{
    Employee *tempNode_ptr =  NULL ;
    tempNode_ptr = searchNode(employeeName) ;
    if (NULL == tempNode_ptr)
    {
        return NULL ;
    }
    if (1 == Employee_list.Employees_number)
    {
        Employee_list.Employee_firsPtr = NULL ;
        Employee_list.Employee_lastPtr =  NULL ;
    }
    else if (NULL == tempNode_ptr->Employee_prePtr)
    {
        tempNode_ptr->Employee_nextPtr->Employee_prePtr =  NULL ;
        Employee_list.Employee_firsPtr = tempNode_ptr->Employee_nextPtr ;
    }
    else if (NULL == tempNode_ptr->Employee_nextPtr)
    {
        tempNode_ptr->Employee_prePtr->Employee_nextPtr =  NULL ;
        Employee_list.Employee_lastPtr = tempNode_ptr->Employee_prePtr ;
    }
    else
    {
        tempNode_ptr->Employee_nextPtr->Employee_prePtr = tempNode_ptr->Employee_prePtr ;
        tempNode_ptr->Employee_prePtr->Employee_nextPtr =  tempNode_ptr->Employee_nextPtr ;
    }

    Employee_list.Employees_number -- ;
    return tempNode_ptr ;
}

/**********************************************************************/




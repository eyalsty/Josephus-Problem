/************************
* Student name: Eyal Styskin
* Student: 206264749
* Course Exercise Group: 06
* Exercise name: ex6
************************/

#include<stdio.h>
#include "utils.h"

/*******************************************************************************************************
* Function Name:PrintCircle
* Input:Person* person
* Output: -
* Function Operation: The function prints all the date of the people standing in the circle according
					  to their standing order.
********************************************************************************************************/

void PrintCircle(Person* head)
{
	//if the circle is not empty
	if (NULL != head)
	{
		Person*current = head;
		//send the first person in the circle to be printed
		head->Print(head);
		//print all the rest until the ened of the circle
		while (current->next != head)
		{
			//if only 1 person standing in the circle stop
			if (NULL == current->next)
				break;
			//print the next person standing
			current->Print(current->next);
			//promote the pointer to the next person in the circle
			current = current->next;
		}
		printf(BORDER);
	}
}
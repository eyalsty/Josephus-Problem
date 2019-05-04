/************************
* Student name: Eyal Styskin
* Student: 206264749
* Course Exercise Group: 06
* Exercise name: ex6
************************/


#include <stdio.h>
#include <string.h>
#include "sorting.h"

Person* MainSortFunc(Person* head, int sort);
int CompareName(Person* a, Person* b);
int CompareID(Person* a, Person* b);
int(*funcs[])(Person* a, Person* b) = { CompareID ,CompareName };

/*******************************************************************************************************
* Function Name:SortCircleByID
* Input:Person* head
* Output: Person* head, int 0
* Function Operation: The function recieves the first person in the circle, and sends him together with
					  the 0 integer (the index of sorting by id the in function-pointers-array) to the
					  main sorting function.
********************************************************************************************************/

Person* SortCircleByID(Person* head)
{
	int id = 0;
	//send the first person and 0 (the index of id sorting in the array) to the sorting function
	head = MainSortFunc(head, id);
	return head;
}

/*******************************************************************************************************
* Function Name:SortCircleByName
* Input:Person* head
* Output: Person* head, int 1
* Function Operation: The function recieves the first person in the circle, and sends him together with
					  the 1 integer (the index of sorting by id the in function-pointers-array) to the
					  main sorting function.
********************************************************************************************************/

Person* SortCircleByName(Person* head)
{
	int name = 1;
	//send the first person and 1 (the index of name sorting in the array) to the sorting function
	head = MainSortFunc(head, name);
	return head;
}

/*******************************************************************************************************
* Function Name:CompareID
* Input: Person* a, Person* b
* Output: int (1/-1)
* Function Operation: The function recieves two person* type pointers to people who stand one next to
				      each other and compares between their id's.
					  if the second person's id is smaller it returns 1, otherwise -1.
********************************************************************************************************/

int CompareID(Person* a, Person* b)
{
	if ((a->id) > (b->id))
		return 1;
	else
		return -1;
}

/*******************************************************************************************************
* Function Name:CompareName
* Input: Person* a, Person* b
* Output: int (1/-1)
* Function Operation: The function recieves two person* type pointers to people who stand one next to
					  each other and compares between their names.
					  if the second person's name in lexicographic order comes before the first it
					  returns 1, otherwise -1.
********************************************************************************************************/

int CompareName(Person* a, Person* b)
{
	int compare = strcmp(a->name,b->name);
	return compare;
}

/*******************************************************************************************************
* Function Name:MainSortFunc
* Input: Person* a, Person* b
* Output: int (1/-1)
* Function Operation: The main sorting function that recieve the first person in a circle and receives
					  an integer which indicates whether to sort by name or by ID.
					  The function sorts the circle from smallest to largest and finally returns the
					  pointer to new first person in the circle.
********************************************************************************************************/

Person* MainSortFunc(Person* head, int sort)
{
	//empty circle
	if (head == NULL)
		return NULL;
	//only 1 person in circle
	if (head->next == NULL)
		return head;
	Person* swapA = head;
	Person* swapB = swapA;
	Person* last = head;
	//flag to know if switch was made
	int isSwitch = 0;
	do
	{
		//set all the pointers to the first person
		Person* swapA = head;
		Person* swapB = swapA;
		Person* last = head;
		//loop to run until the last person in the circle
		while (swapB->next != head)
		{
			//promote swapB to point on the person standing after swapA
			swapB = swapA->next;
			last = head;
			//check if the first person need to be swaped with the one after him
			if (funcs[sort](head, head->next) == 1)
			{
				//means 2 in circle
				if (swapA == swapB->next)
				{
					//set swapB as the first person and stop the sorting
					head = swapB;
					isSwitch = 0;
					break;
				}
				//if more then 2 people in the circle
				else {
					//restart the pointers searcingh for swap
					swapA = head;
					//swapB to point the next after swapA
					swapB = swapA->next;
					//find the last person in the circle
					while (last->next != head)
						last = last->next;
					//the first person being swapped to point the person that the second swapped person pointing
					swapA->next = swapB->next;
					//the second swapped person point to the first
					swapB->next = swapA;
					swapA = swapB;
					//the last person in the circle to point to the new head
					last->next = swapA;
					//set the swapped to be the head
					head = swapA;
					isSwitch = 1;
					break;
				}
			}
			else {
				//if found 2 people to be switched and are not first
				if (funcs[sort](swapA, swapB) == 1)
				{
					//find the person standing before the people need to change places
					while (last->next != swapA)
						last = last->next;
					//switch the 2 standing people's place 
					swapA->next = swapB->next;
					swapB->next = swapA;
					swapA = swapB;
					last->next = swapA;
					isSwitch = 1;
					break;
				}
				//if no change need to be made, promote the pointers to the next person
				else
				{
					swapA = swapB;
					isSwitch = 0;
				}
			}
		}
		//continue as long as changings are made
	}while (1 == isSwitch);
	//after the sorting, return the first standing person
	return head;
}
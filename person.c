/************************
* Student name: Eyal Styskin
* Student: 206264749
* Course Exercise Group: 06
* Exercise name: ex6
************************/


#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include "person.h"
#include "utils.h"

void CreateNext(Person* this, int isNextNext, ...);
void Print(Person* this);
Person* SelfDestruct(struct Person* this);
void KillNext(struct Person* this);
void InitPersonValues(Person* person);
Person* CreatePerson();

/*******************************************************************************************************
* Function Name:InitPersonValues
* Input:Person* person
* Output: - 
* Function Operation: the function is being called from the function CreatePerson and it initializes
					  the new person's struct fields. all the integers recieve 0, all the arrays recieve
					  NULL, and the function pointers recieve the function's name.
********************************************************************************************************/

void InitPersonValues(Person* person)
{
	person->name = NULL;
	person->id = 0;
	person->numOfKids = 0;
	person->kids = NULL;
	person->next = NULL;
	person->Print = Print;
	person->KillNext = KillNext;
	person->SelfDestruct = SelfDestruct;
	person->CreateNext = CreateNext;
}

/*******************************************************************************************************
* Function Name:Person* CreatePerson()
* Input:
* Output: Person* person
* Function Operation: the function is being called from the function CreatePerson and it initializes
the new person's struct fields. all the integers recieve 0, all the arrays recieve
NULL, and the function pointers recieve the function's name.
********************************************************************************************************/

Person* CreatePerson()
{
	char newName[NAME_SIZE];
	int i,j;
	char dummy;
	char **kids = NULL, kidName[NAME_SIZE];
	//dynamically allocated memory for new struct
	Person*newPerson = (Person*)malloc(sizeof(Person));
	//if the allocation did not succeed return NULL
	if (NULL == newPerson)
	{
		return NULL;
	}
	//send the new person's struct to a initializing function
	InitPersonValues(newPerson);
	//get a name input from the user
	printf(NAME);
	scanf("%s%c", newName, &dummy);
	//dynamically allocated memory for person's name
	newPerson->name = (char*)malloc(strlen(newName)*sizeof(char) +1);
	//if the allocation fail
	if (NULL == newPerson->name)
	{
		//free the struct allocated before
		free(newPerson);
		//return null for failing
		return NULL;
	}
	//if allocation succeeded
	else {
		//copy the inputed name to the name field of the created person
		strcpy(newPerson->name, newName);
		//get id id from the user
		printf(ID);
		scanf("%d%c", &(newPerson->id), &dummy);
		//get the number of kids of the new person from the user
		printf(KIDS_NUM);
		scanf("%d%c", &(newPerson->numOfKids), &dummy);
		//negative number of kids is not allowed, so print error
		if (newPerson->numOfKids < 0)
		{
			printf(ERROR);
			return NULL;
		}
		//dynamically allocated memory for an array of kids
		newPerson->kids = (char**)calloc(newPerson->numOfKids, sizeof(char*));
		//if allocation fails free the allocated before name and struct and return null
		if (newPerson->kids == NULL)
		{
			free(newPerson->name);
			free(newPerson);
			return NULL;
		}
		/*a for loop to get the names of the kids from the user. the integer i is set to 0, and as long as its
		smaller then the number of the kids, it will continue to receieve the names, dynamically allocare
		memory for each of them, and if it fails, to free everything that was allocated before*/
		for (i = 0; i < newPerson->numOfKids; i++)
		{
			//recieve the kid's name
			printf(KID_NAME, i + 1);
			scanf("%s%c", kidName, &dummy);
			newPerson->kids[i] = (char*)malloc((strlen(kidName) * sizeof(char)) + 1);
			//if allocation fails, free all the allocated before memory
			if (newPerson->kids[i] == NULL)
			{
				//loop to free all the kids (from j=0 to i = the failed kid)
				for (j = 0; j < i; j++)
				{
					free(newPerson->kids[j]);
				}
				free(kids);
				free(newPerson->name);
				free(newPerson);
				return NULL;
			}
			//if did not fail, copy the inputed kid's name to the kids array in the struct
			strcpy(newPerson->kids[i], kidName);
		}
	}
	//return the pointer to the new created person
	return newPerson;
}

/*******************************************************************************************************
* Function Name:CreateNext
* Input:Person* person, int isNextNext, ..
* Output: -
* Function Operation: The function assigns memory to a new person and places it after the person from
					  whom the function was triggered. The second parameter of The function is boolean:
					  1- If such a person exists(person after), such a situation will occur when
					  trying to add someone who is late to the circle. 
********************************************************************************************************/

void CreateNext(Person* this, int isNextNext, ...)
{
	//new Person* type
	Person* midNew;
	va_list last;
	va_start(last, isNextNext);
	Person* lastPerson = va_arg(last, Person*);
	//create new person after the one triggered
	this->next = CreatePerson();
	//set midNew to point on the new person
	midNew = this->next;
	//the the new person to point on the next person in the circle
		midNew->next = lastPerson;
	va_end(last);
}

/*******************************************************************************************************
* Function Name:Print
* Input:Person* this
* Output: -
* Function Operation: The function printing all the data in the struct field of the person was sent to her.
********************************************************************************************************/

void Print(Person* this)
{
	int i;
	printf(BORDER);
	//print the persons name
	printf(PRT_NAME, this->name);
	//print the persons id
	printf(PRT_ID, this->id);
	//a loop to print the persons kid's name
	for (i = 0; i < this->numOfKids; i++)
		printf(PRT_KID_NAME, i + 1, this->kids[i]);
}

/*******************************************************************************************************
* Function Name:KillNext
* Input:Person* this
* Output: -
* Function Operation: the function prints the progress of the game. it says the name of the killer, and
					  the name of the person he killed (the one after him in the circle) and his children,
					  after the printing the function sends the dead person to the function "SelfDestruct"
					  in order to free all of his data and prevent memory leaks.
********************************************************************************************************/

void KillNext(struct Person* this)
{
	//the a pointer to next person in the circle named "dead"
	Person* dead = this->next;
	int i;
	//print the progress of the killing game ( killer and dead)
	printf(KILL_MSG, this->name, dead->name);
	if (dead->numOfKids > 0)
		for (i = 0; i < dead->numOfKids; i++)
		{
			printf(KILL_KID, dead->kids[i]);
		}
	//send the dead person to a free memory function 
	dead->SelfDestruct(dead);
	printf(NEW_LINE);
}

/*******************************************************************************************************
* Function Name:SelfDestruct
* Input:Person* this
* Output: Person* (tempPerson/NULL)
* Function Operation: the function recieves a person who needs to die and free all of his data from the
					  heap. after the free it returns the person standing after him in the circle,
					  after the sent person was alone in the circle, the function returns NULL.
********************************************************************************************************/

Person* SelfDestruct(struct Person* this)
{
	int whatReturn;
	//saves the next person after the dead with a pointer
	Person* tempPerson = this->next;
	//means only 1 person in circle
	if (this->next == NULL)
	{
		//return NULL	
		whatReturn = 0;
	}
	else {
		//means 2 in circle
		if (tempPerson->next == this)
			tempPerson->next = NULL;
		//return the next person (tempPerson)
		whatReturn = 1;
	}
	//free the dynamic allocated name
	free(this->name);
	//if the person has kids, we free their allocated memory
	if (this->numOfKids > 0)
	{
		for (int i = 0;i < this->numOfKids;i++)
			free(this->kids[i]);
	}
	//free the kids dynamic allocated array
	free(this->kids);
	//free the person's struct
	free(this);
	if (whatReturn = 0)
		//means the circle is now empty
		return NULL;
	else {
		//return the next person after the one that was freed
		return tempPerson;
	}
}



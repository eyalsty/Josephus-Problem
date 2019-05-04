/************************
* Student name: Eyal Styskin
* Student: 206264749
* Course Exercise Group: 06
* Exercise name: ex6
************************/

#include <stdio.h>
#include <string.h>
#include "person.h"
#include "utils.h"

/*******************************************************************************************************
* Function Name:InitTheHungerGame
* Input:
* Output: Person* head	
* Function Operation: The function initializes the game and adds people to the circle of game.
					  After the reading of the function a pointer to the head (first person) will be returned.
					  In case of failure, or no people at all the function will return NULL.
					  every call to this function creates a new independent circle, and if wont be a call
					  to begin the game for each one of them - a memory leak might occur.
********************************************************************************************************/

Person* InitTheHungerGame()
{
	int addPerson;
	int firstPerson = 0;
	int i, counter = 0;
	Person* head = NULL;
	Person* current = NULL;
	//as the user if to add new person
	printf(ADD_PERSON);
	scanf("%d", &addPerson);
	//if the user chooses '1' we enter the while loop and create a new person
	while (1 == addPerson)
	{
		//if the integer firstPerson is 0 we add new person and set it as head 
		if (0 == firstPerson)
		{
			head = CreatePerson();
			current = head;
			//means we already added the first person
			firstPerson = 1;

		}
		//means that there is at least 1 person in circle
		else {
			//create a new person to stand after the last one added
			current->next = CreatePerson();
			//set the new person as the last (current)
			current = current->next;
		}
		//if the new person creation fails (Current is equal =NULL) we stop adding
		if (NULL == current)
			break;
		//add +1 to the counter of the people
		counter++;
		//ask if continue to add more people
		printf(ADD_PERSON);
		scanf("%d", &addPerson);
	}
	//if no people was added to the circle(no first person) return NULL
	if (0 == firstPerson)
		return NULL;
	//if creation of new person failed, i free all the people that was created before in this current circle
	if (NULL == current)
	{
		//set current to the head(the first standing person)
		current = head;
		//loop to free all the people standing already in the circle
		for (i = 0;i < counter; i++)
		{
			current = current->SelfDestruct(current);
		}
	}
	//if only 1 person in circle, the next one will be NULL
	if (1 == counter)
		head->next = NULL;
	//close the circle, the next standing after the last will be the first
	else
		current->next = head;
	//return the first standing in the circle
	return head;
}

/*******************************************************************************************************
* Function Name:InsertLaters
* Input:Person* head
* Output: -
* Function Operation: This function brings in other people who are late to arrive, and want to enter
					  the circle and to stand right after Their best friend.
					  the head of the circle cannot be changed, and a later cannot join an empty circle.
********************************************************************************************************/

void InsertLaters(Person* head)
{
	if (NULL != head)
	{
		//indicates if to add a later
		int isLate;
		int bestFId;
		//flag to stop
		int toStop;
		Person* current = head;
		//as the user if there is a later
		printf(LATE_MSG);
		scanf("%d", &isLate);
		//if there is a later, we add him to the circle to stand after his best friend
		while (1 == isLate)
		{
			current = head;
			toStop = 0;
			//ask the later for the id of his best friend, to set him after him.
			printf(FRIEND_ID);
			scanf("%d", &bestFId);
			//check for a match between the inputed id to the people standing in the circle (when match "toStop" is 1)
			while (0 == toStop)
			{
				//if we find a match between the input id to standing person's id
				if (current->id == bestFId)
				{
					//if its the first person (there is no next person to its NULL)
					if (NULL == current->next)
					{
						//i create the later to stand after him in the circle (2nd)
						current->CreateNext(current, isLate, current->next);
						Person* newPerson = current->next;
						newPerson->next = head;
						break;
					}
					//create a new person to stand between his best friend and the next person after him
					else {
						current->CreateNext(current, isLate, current->next);
						break;
					}
				}
				//if the id doe not match the current person, run loop agein and check the next person
				else {
					current = current->next;
				}
				//if we check the whole circle without match or current is NULL
				if (head == current || NULL == current)
				{
					//print that no id exsists in the circle
					printf(NO_ID, bestFId);
					//stop the search
					toStop = 1;
				}
			}
			//ask for a next later
			printf(LATE_MSG);
			scanf("%d", &isLate);
		}
	}
}

/*******************************************************************************************************
* Function Name:RemoveCowards
* Input:Person* head
* Output: Person* head
* Function Operation: The function removes from the circle the cowards who do not have the courage to
					  participate In the game. the function search for the coward's id in the circle,
					  and free all of his data, so the person standing before him, will point to the
					  person after him.the first person can be removed, if all the people Cowards
					  or of the circle is empty the function will return NULL.
********************************************************************************************************/

Person* RemoveCowards(Person* head)
{
	//if circle is empty, return null to the menu
	if (NULL == head)
		return NULL;
	int isCoward;
	int cowardID;
	int toStop = 0;
	char cowardName[NAME_SIZE];
	Person* current = head;
	Person* prev;
	//ask for a coward in the circle
	printf(COWARD_MSG);
	scanf("%d", &isCoward);
	//if there is a coward in the circle we enter the loop and look for him
	while (isCoward == 1)
	{
		//set the person* type pointers to point on the first person in the circle
		current = head;
		prev = head;
		toStop = 0;
		//as for the coward's id
		printf(COWARD_ID);
		scanf("%d", &cowardID);
		//start a loop to search for the coward with the inputed id
		while (0 == toStop)
		{
			//if the first person in the circle is the coward
			if (head->id == cowardID)
			{
				//save coward's name in a string (array of chars)
				strcpy(cowardName, head->name);
				//set the person* type pointer "late" to point on the first person
				Person* last = head;
				//run for all of the people on the circle until it reaches the last
				while (last->next != head && last->next != NULL)
					last = last->next;
				//send the coward to the SelfDestruct function in order to free him, and return the next person stand
				current = prev->SelfDestruct(prev);
				head = current;
				//if the next person that standing is null it means, the head was alone,
				if (NULL == current)
					break;
				//close the circle if more then 1 person
				if (last != current)
				{
					last->next = head;
					break;
				}
				break;
			}
			//if we find the coward in the circle and he is not the first
			if (current->id == cowardID)
			{
				//save coward's name
				strcpy(cowardName, current->name);
				//loop for the person before the coward
				while (prev->next != current)
					prev = prev->next;
				//send the coward to selfdestruct
				current = current->SelfDestruct(current);
				//means only 2 in circle
				if (current == prev)
					break;
				//set the person stood before the coward to point next to the person stood after the coward
				prev->next = current;
				break;
			}
			else {
				//if the checked person is not the coward, check the next one.
				current = current->next;
			}
			//if we finished the loop and the coward was not found or its null 
			if (current == head|| current == NULL)
			{
				//print the id does not exist
				printf(NO_ID, cowardID);
				//stop the search
				toStop = 1;
				//set to 0 in order to look for the next coward
				isCoward = 0;
				current = head;
			}

		}
		//if a coward was found, tell the world his name
		if (isCoward)
			printf(COWARD_NAME, cowardName);
		//if the circle became empty, return NULL	
		if (NULL == current)
			return NULL;
		//search for the next coward
		printf(COWARD_MSG);
		scanf("%d", &isCoward);
	}
	//return the new first person standing in the circle
	return head;
}

/*******************************************************************************************************
* Function Name:LetTheHungerGameBegin
* Input:Person* head
* Output: -
* Function Operation: The function begins the game, during the game the function printe to screen its
					  progress and who kills who. Eventually it announces who won and survived.
					  if the circle empty it returns NULL, and in a circle the size of 1 game is very
					  short (instant victory).
********************************************************************************************************/

void LetTheHungerGameBegin(Person* head)
{
	if (head != NULL)
	{
		int isWinner = 0;
		Person* prev = head;
		//if no one stands after the first person, it means he is alone and is the winner
		if (head->next == NULL)
			isWinner = 1;
		//if no winner yet
		while (isWinner == 0)
		{
			Person* current = prev->next;
			//save the pointer to the person after the one suppost to die
			current = current->next;
			//save the person to a function that kills the one after him and free his memory
			prev->KillNext(prev);
			//if last one stayed he is the winner
			if (prev->next == NULL)
			{
				isWinner = 1;
				break;
			}
			//the saved person is set to stand after the person that stood before the dead
			prev->next = current;
			//promote the killer	
			prev = prev->next;
		}
		//print the name of the last man standing as the winner
		printf(WIN_MSG, prev->name);
		//free the last person to prevent memory leak
		prev->SelfDestruct(prev);
	}
}
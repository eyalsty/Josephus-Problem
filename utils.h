/************************
* Student name: Eyal Styskin
* Student: 206264749
* Course Exercise Group: 06
* Exercise name: ex6
************************/

#ifndef UTILS_H
#define UTILS_H

#include "person.h"

#define NAME_SIZE 80
#define WIN_MSG "Ah, ha, ha, ha, stayin\' alive, stayin\' alive! Ah, ha, ha, ha, \"%s\" stayin\' alive!\n"
#define KILL_MSG "%s kills %s"
#define KILL_KID " and %s"
#define KID_NAME "Kid #%d name: \n"
#define ID "ID: \n"
#define PRT_ID "ID: %d\n"
#define KIDS_NUM "Num of kids: \n"
#define ERROR "Error\n"
#define NAME "Name: \n"
#define PRT_NAME "Name: %s\n"
#define NEW_LINE "\n"
#define ADD_PERSON "Add a person to the game? (0|1)\n"
#define LATE_MSG "Are you late? (0|1)\n"
#define FRIEND_ID "Insert your best friend's ID:\n"
#define NO_ID "No Such ID: %d\n"
#define COWARD_MSG "Is there a coward in here? (0|1)\n"
#define COWARD_ID "Insert your ID, you, lame pudding-heart coward:\n"
#define COWARD_NAME "Let the world know that you are a coward, %s!\n"
#define BORDER "----------\n"
#define PRT_KID_NAME "Kid #%d: %s\n"

//a function to print the circle by the people's standing order
void PrintCircle(Person* head);


#endif

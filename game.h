#ifndef GAME_H
#define GAME_H

#include "person.h"

Person* InitTheHungerGame();
void InsertLaters(Person* head);
Person* RemoveCowards(Person* head);
void LetTheHungerGameBegin(Person* head);

#endif

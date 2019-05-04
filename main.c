#include "person.h"
#include "utils.h"
#include "sorting.h"
#include "game.h"

int main() {
	Person* head = InitTheHungerGame();
	PrintCircle(head);
	head = SortCircleByName(head);
	PrintCircle(head);
	LetTheHungerGameBegin(head);
	InsertLaters(head);
	InsertLaters(head);
	PrintCircle(head);
	head = RemoveCowards(head);
	PrintCircle(head);
    InsertLaters(head);
    PrintCircle(head);
    head = RemoveCowards(head);
    PrintCircle(head);
    head = SortCircleByName(head);
    PrintCircle(head);
    head = SortCircleByID(head);
    PrintCircle(head);
    LetTheHungerGameBegin(head);
    return 0;
}

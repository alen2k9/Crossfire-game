#include <stdio.h>
#include "crossfireOperations2.h"

int main()
{
	playerInformation();		

	createBoard(BOARD_SIZE);	
	
	playerINslots(BOARD_SIZE);	
	
	while(NumberPlayers >1)	
	{
		playersGO();			
	}	
	return 0;
	
	if(NumberPlayers = 1)
	{
		printf("------------------------\n");
		printf("------------------------\n");
		printf("%s is the winner \n", Players[0].player_Name);
		printf("------------------------\n");
		printf("------------------------\n");
	}
	return 0;
}

char *findSlotType(enum slotType type)
{
	switch (type)			
	{
		case Level_Ground:
			return "Level Ground";
		case Hill:
			return "Hill";
		case City:
			return "City";
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crossfireOperations2.h"

#define MAX_PLAYER_SIZE 6


void playerInformation()
{
	int i, Type[6];

	//while loop to make sure user selects amount of players between 2 and 6
	while(NumberPlayers > 6 || NumberPlayers <= 1)
	{
		//asks user how many players they want
		puts("enter number of players (Max 6)");
		scanf("%d", &NumberPlayers);

	} 

	//	loop to get player name and type
	for ( i = 0 ; i < NumberPlayers ; i++)
	{
		printf("\nenter player %d name: ", i+1);
		scanf("%s", &Players[i].player_Name);
		
		while(Type[i] > 4 || Type[i] <= 0)//while loop keeps going until 1 of the 4 options is picked
		{
			printf("What player type do you want %s\n", &Players[i].player_Name);
			printf("[1] Ogre\n[2] Human\n[3] Wizard\n[4] Elf\n");
			scanf("%d", &Type[i]);//stores answer in an integer array
		}
	}
	for(i=0 ; i<NumberPlayers; i++)
	{

		if(Type[i] == 1)//checks if player type is ogre
		{
			Players[i].Life_pts = 100;
			Players[i].Luck = 60;
			Players[i].Magic_Skills=0;
			Players[i].Smartness = (rand() %21);
			Players[i].Strength = ((rand() %21)+80);
			Players[i].Dexterity = ((rand() %21)+80);
			while(Players[i].Luck+Players[i].Smartness>50)//makes sure that luck and smartness combined are less than 50
			{
				Players[i].Luck = (rand() %51);
			}
			//prints out the result
			printf("\nPlayer %s", Players[i].player_Name);
			printf("\nMagic skills: %d\n", Players[i].Magic_Skills);
			printf("Smartness: %d\n", Players[i].Smartness);
			printf("Strength: %d\n", Players[i].Strength);
			printf("Dexterity: %d\n", Players[i].Dexterity);
			printf("Luck: %d\n", Players[i].Luck);
		}

		if(Type[i] == 2)//checks if player type is human
		{
			Players[i].Magic_Skills = 100;
			Players[i].Smartness = 100;
			Players[i].Strength = 100;
			Players[i].Dexterity = 100;
			Players[i].Luck = 100;
			Players[i].Life_pts = 100;
			
			//while loop that ends when combined abilities are less than or equal to 300
			while(Players[i].Magic_Skills+Players[i].Smartness+Players[i].Strength+Players[i].Dexterity+Players[i].Luck>=300)
			{
				Players[i].Magic_Skills = ((rand() %100)+1);
				Players[i].Smartness = ((rand() %100)+1);
				Players[i].Strength = ((rand() %100)+1);
				Players[i].Dexterity = ((rand() %100)+1);
				Players[i].Luck = ((rand() %100)+1);
			}
			//prints out the result
			printf("\nPlayer %s, Type: %s", Players[i].player_Name);
			printf("\nMagic skills: %d\n", Players[i].Magic_Skills);
			printf("Smartness: %d\n", Players[i].Smartness);
			printf("Strength: %d\n", Players[i].Strength);
			printf("Dexterity: %d\n", Players[i].Dexterity);
			printf("Luck: %d\n", Players[i].Luck);
		}

		if(Type[i] == 3)//checks if player type is a wizard
		{
			Players[i].Magic_Skills = ((rand() %21)+80);
			Players[i].Smartness = ((rand() %11)+90);
			Players[i].Strength = ((rand() %20)+1);
			Players[i].Dexterity = ((rand() %100)+1);
			Players[i].Luck = ((rand() %51)+50);
			Players[i].Life_pts = 100;
			
			//prints out the result
			printf("\nPlayer %s ", Players[i].player_Name);
			printf("\nMagic skills: %d\n", Players[i].Magic_Skills);
			printf("Smartness: %d\n", Players[i].Smartness);
			printf("Strength: %d\n", Players[i].Strength);
			printf("Dexterity: %d\n", Players[i].Dexterity);
			printf("Luck: %d\n", Players[i].Luck);

		}

		if(Type[i] == 4)//checks if player type is elf

		{

			Players[i].Magic_Skills = 0;
			Players[i].Smartness = ((rand() %31)+70);
			Players[i].Strength = ((rand() %50)+1);
			Players[i].Dexterity = ((rand() %100)+1);
			Players[i].Luck = ((rand() %41)+60);
			Players[i].Life_pts = 100;

			while(Players[i].Magic_Skills<=50)//while loop that ends when magic skills are greater than 50

			{
				Players[i].Magic_Skills = ((rand() %30)+50);
			}
			//prints out the result
			printf("\nPlayer %s", Players[i].player_Name);
			printf("\nMagic skills: %d\n", Players[i].Magic_Skills);
			printf("Smartness: %d\n", Players[i].Smartness);
			printf("Strength: %d\n", Players[i].Strength);
			printf("Dexterity: %d\n", Players[i].Dexterity);
			printf("Luck: %d\n", Players[i].Luck);

		}

	}

}

void playerINslots(int boardsize)//assigns players to slots randomly at the start
{
	for (int i = 0 ; i < NumberPlayers ; i++)
	{
		Players[i].place = &board[rand() % boardsize][rand() % boardsize];//picks a random number between 0 and 6 for first and second part of multidimensional array
		
	}

	for (int i = 0 ; i < NumberPlayers ; i++)
	{
		//prints out all places of players at start
		printf("Player %s is at [%d,%d], %s.\n", Players[i].player_Name, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}
}


void affectedAbilities(int i)
{
	//	Switch statement to change players abilities
	switch(Players[i].place->type)
	{
		case Level_Ground:	//	level Ground case nothing changes
			printf("\nNo abilities changed!");
			break;
		case Hill:	//	Hill case changes depend on current abilities
			if (Players[i].Dexterity < 50)
			{
				Players[i].Strength -= 10;
				printf("\nLose 10 strength. (Strength: %d)", Players[i].Strength);
			}
			else if (Players[i].Dexterity >= 60)
			{
				if (Players[i].Strength >= 100)
				{
					printf("\nStrength Max.");
				}
				else
				{
					Players[i].Strength += 10;
					printf("\nGain 10 strength. (Strength: %d)", Players[i].Strength);
				}
			}
			else printf("\nNo abilitiess changed!");
			break;
			
		case City:	//	City case changes depend on current abilities
			if (Players[i].Smartness > 60)
			{
				if (Players[i].Magic_Skills >= 100)
				{
					printf("\nMagic Max");
				}
				else
				{
					Players[i].Magic_Skills += 10;
					printf("\nGain 10 magic. (Magic: %d)", Players[i].Magic_Skills);
				}
			}
			else if (Players[i].Smartness <= 50)
			{
				Players[i].Dexterity -= 10;
				printf("\nLose 10 dexterity. (Dexterity: %d)", Players[i].Dexterity);
			}
			else printf("No abilities changed!");
			break;
	}
}
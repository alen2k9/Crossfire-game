#include <stdio.h>
#include <stdlib.h>
#include "crossfireOperations2.h"


void Decision();

//all decision functions
void Attack();
void Move();
void Quit();

//all attacking functions
void Near();
void Distant();
void Magical();

//Sort players so that the last player in array is a dead player
void sort(); 

int i;//global variable

void playersGO()
{
	int j;

	//for loop to go through each players and allow them to make a move
	for(i = 0 ; i < NumberPlayers ; i++)
	{
		if(Players[i].Life_pts > 0) //prints which players turn it is
		{
			printf("\n\n%s's turn.", Players[i].player_Name);
			Decision();	//calls to function Decision
		}

	}
	
	sort();
	//after each round prints out all remaining player information
	if(NumberPlayers != 1)
	{
		//prints remaining players, health and position
		printf("\n%d Remaining Players:", NumberPlayers);
		for(i = 0 ; i < NumberPlayers ; i++)
		{
			printf("\n%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		}
	}
}

void Decision()
{
	bool end = false;//boolean variable used for easier while loops
	int decision = 0;

	
	 while(end != true)
	{
		printf("Would you like to \n[1]attack\n[2]move\n[3]quit\n"); //asks user for input 1, 2 or 3
		scanf("%d", &decision);

		if(decision == 1)//player attacking option
		{
			Attack(i);//calls to attack function
			end = true;//sets boolean value to true to exit the while loop
		}

		else if(decision == 2)//player moving option
		{
			Move(i);//calls to moving function
			affectedAbilities(i);//calls to ability changing function as different slots give increased or decreased abilities
			end = true;
		}

		else if(decision == 3)//player leaves game
		{
			Quit(i);//calls to quit function
			end = true;
		}
	}
}

void Attack(int i)
{
	int action;
	bool end = false;//boolean variable used for easier while loops

	//If players magic + smartness is greater than 150 allow magic attack
	if((Players[i].Magic_Skills + Players[i].Smartness) > 150)
	{
		printf("\nwhat attack do you want to do \n[1]near\n[2]distant\n[3]magic\n");//asks user for input 1, 2 or 3
		while(end != true)
		{
			printf("\nwhat attack do you want to do \n[1]near\n[2]distant\n[3]magic\n");
			scanf("%d", &action);
			
			if(action == 1)//short range attack
			{
				Near(i);//calls to function near
				end = true;
			}
			
			else if(action == 2)//long range attack
			{
				Distant(i);//calls to function distant
				end = true;
			}
			
			else if(action == 3)//magic attack
			{
				Magical(i);//calls to function magical
				end = true;
			}
		}
	}

	else//same as before just without magic attacks as player does not have enough combined smartness and magic
	{
		printf("\nwhat attack do you want to do \n[1]near\n[2]distant\n");
		while(end != true)
		{
			printf("\nwhat attack do you want to do \n[1]near\n[2]distant\n");
			scanf("%d", &action);

			if(action == 1)
			{
				Near(i);
				end = true;
			}
		
			else if(action == 2)
			{
				Distant(i);
				end = true;
			}
		}
	}
	for( i = 0; i < NumberPlayers; i++ )
	{
		if(Players[i].Life_pts <= 0)
		{
			printf("\nPlayer %s is dead \n", Players[i].player_Name);
		}
	}
}

void Move(int i)//move function
{
	int direction;
	bool end;//boolean variable used for easier while loops

	if(Players[i].place == upRight)	//if position was in the top right corner you can only move left or down
	{
		//prints current position 
		printf("\n%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		while(end != true)
		{
			printf("\n[1]move left to [%d,%d], %s\n[2]move down to [%d,%d], %s.\n", Players[i].place->left->row, Players[i].place->left->column, findSlotType(Players[i].place->left->type), Players[i].place->down->row, Players[i].place->down->column, findSlotType(Players[i].place->down->type));
			scanf("%d", &direction);//takes user input
			if(direction == 1)//moves player left
			{
				Players[i].place = Players[i].place->left;
				end = true;
			}
			else if(direction == 2)//moves player down
			{
				Players[i].place = Players[i].place->down;
				end = true;
			}
		}
		printf("\n%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}

	else if(Players[i].place == upLeft)//if position was in the top left corner you can only move right or down
	{
		//prints current position (rest follows same format)
		printf("\n%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		
		while(end != true)
		{
			printf("\n[1]move right to [%d,%d], %s\n[2]move down to [%d,%d], %s.\n", Players[i].place->right->row, Players[i].place->right->column, findSlotType(Players[i].place->right->type), Players[i].place->down->row, Players[i].place->down->column, findSlotType(Players[i].place->down->type));
			scanf("%d", &direction);//takes user input
			if(direction == 1)//moves player right
			{
				Players[i].place = Players[i].place->right;
				end = true;
			}
			else if(direction == 2)//moves player down
			{
				Players[i].place = Players[i].place->down;
				end = true;
			}
		}
		printf("\n%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}

	else if(Players[i].place == downRight)//if position was in the bottom right corner you can only move left or up
	{
		printf("%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		while(end != true)
		{
			printf("\n[1]move left to [%d,%d], %s\n[2]move up to [%d,%d], %s.\n", Players[i].place->left->row, Players[i].place->left->column, findSlotType(Players[i].place->left->type), Players[i].place->up->row, Players[i].place->up->column, findSlotType(Players[i].place->up->type));
			scanf("%d", &direction);
			if(direction == 1)
			{
				Players[i].place = Players[i].place->left;
				end = true;
			}
			else if(direction == 2)
			{
				Players[i].place = Players[i].place->up;
				end = true;
			}
		}
		printf("\n%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}

	else if(Players[i].place == downLeft)//if position was in the botom left corner you can only move right or up
	{
		printf("%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		
		while(end != true)
		{
			printf("\n[1]move right to [%d,%d], %s\n[2]move up to [%d,%d], %s.\n", Players[i].place->right->row, Players[i].place->right->column, findSlotType(Players[i].place->right->type), Players[i].place->up->row, Players[i].place->up->column, findSlotType(Players[i].place->up->type));
			scanf("%d", &direction);
			if(direction == 1)
			{
				Players[i].place = Players[i].place->right;
				end = true;
			}
			else if(direction == 2)
			{
				Players[i].place = Players[i].place->up;
				end = true;
			}
		}
		printf("\n%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}



	else if(Players[i].place->row == 0)	//if position was along the top row you can only move right or left or down
	{
		printf("%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		
		while(end != true)
		{
			printf("\n[1]move right to [%d,%d], %s\n[2]move left to [%d,%d], %s\n[3]move down to [%d,%d], %s\n", Players[i].place->right->row, Players[i].place->right->column, findSlotType(Players[i].place->right->type), Players[i].place->left->row, Players[i].place->left->column, findSlotType(Players[i].place->left->type), Players[i].place->down->row, Players[i].place->down->column, findSlotType(Players[i].place->down->type));
			scanf("%d", &direction);
			if(direction == 1)
			{
				Players[i].place = Players[i].place->right;
				end = true;
			}
			else if(direction == 2)
			{
				Players[i].place = Players[i].place->left;
				end = true;
			}
			else if(direction == 3)
			{
				Players[i].place = Players[i].place->down;
				end = true;
			}
		} 
		printf("\n%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}

	else if(Players[i].place->row == BOARD_SIZE - 1)//if position was along the bottom row you can only move right or left or up
	{
		printf("%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		
		while(end != true)
		{
			printf("\n[1]move right to [%d,%d], %s\n[2]move left to [%d,%d], %s\n[3]move up to [%d,%d], %s\n", Players[i].place->right->row, Players[i].place->right->column, findSlotType(Players[i].place->right->type), Players[i].place->left->row, Players[i].place->left->column, findSlotType(Players[i].place->left->type), Players[i].place->up->row, Players[i].place->up->column, findSlotType(Players[i].place->up->type));
			scanf("%d", &direction);
			if(direction == 1)
			{
				Players[i].place = Players[i].place->right;
				end = true;
			}
			else if(direction == 2)
			{
				Players[i].place = Players[i].place->left;
				end = true;
			}
			else if(direction == 3)
			{
				Players[i].place = Players[i].place->up;
				end = true;
			}
		} 
		printf("\n%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}

	else if(Players[i].place->column == 0)
	{
		printf("%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		
		while(end != true)
		{
			printf("\n[1]move right to [%d,%d], %s\n[2]move up to [%d,%d], %s\n[3]move down to [%d,%d], %s\n", Players[i].place->right->row, Players[i].place->right->column, findSlotType(Players[i].place->right->type), Players[i].place->up->row, Players[i].place->up->column, findSlotType(Players[i].place->up->type), Players[i].place->down->row, Players[i].place->down->column, findSlotType(Players[i].place->down->type));
			scanf("%d", &direction);
			if(direction == 1)
			{
				Players[i].place = Players[i].place->right;
				end = true;
			}
			else if(direction == 2)
			{
				Players[i].place = Players[i].place->up;
				end = true;
			}
			else if(direction == 3)
			{
				Players[i].place = Players[i].place->down;
				end = true;
			}
		} 
		printf("\n%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}

	else if(Players[i].place->column == BOARD_SIZE - 1)	
	{
		printf("%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		
		while(end != true)
		{
			printf("\n[1]move left to [%d,%d], %s\n[2]move up to [%d,%d], %s\n[3]move down to [%d,%d], %s\n", Players[i].place->left->row, Players[i].place->left->column, findSlotType(Players[i].place->left->type), Players[i].place->up->row, Players[i].place->up->column, findSlotType(Players[i].place->up->type), Players[i].place->down->row, Players[i].place->down->column, findSlotType(Players[i].place->down->type));
			scanf("%d", &direction);
			if(direction == 1)
			{
				Players[i].place = Players[i].place->left;
				end = true;
			}
			else if(direction == 2)
			{
				Players[i].place = Players[i].place->up;
				end = true;
			}
			else if(direction == 3)
			{
				Players[i].place = Players[i].place->down;
				end = true;
			}
		} 
		printf("\n%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}
	
	else
	{
		printf("%s (%d) is at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
		
		while(end != true)
		{
			printf("\n[1]move right to [%d,%d], %s\n[2]move left to [%d,%d], %s\n[3]move up to [%d,%d], %s\n[4]move down to [%d,%d], %s\n", Players[i].place->right->row, Players[i].place->right->column, findSlotType(Players[i].place->right->type), Players[i].place->left->row, Players[i].place->left->column, findSlotType(Players[i].place->left->type), Players[i].place->up->row, Players[i].place->up->column, findSlotType(Players[i].place->up->type), Players[i].place->down->row, Players[i].place->down->column, findSlotType(Players[i].place->down->type));
			scanf("%d", &direction);
			if(direction == 1)
			{
				Players[i].place = Players[i].place->right;
				end = true;
			}
			else if(direction == 2)
			{
				Players[i].place = Players[i].place->left;
				end = true;
			}
			else if(direction == 3)
			{
				Players[i].place = Players[i].place->up;
				end = true;
			}
			else if(direction == 4)
			{
				Players[i].place = Players[i].place->down;
				end = true;
			}
		}
		printf("%s (%d) is now at [%d,%d], %s.", Players[i].player_Name, Players[i].Life_pts, Players[i].place->row, Players[i].place->column, findSlotType(Players[i].place->type));
	}
}

void Quit()
{
	printf("\n%s has quit the game.", Players[i].player_Name);//haven't done the quit part or dying part yet
	Players[i].Life_pts = 0;
}

void Near()
{
	
	slot *currSlot = Players[i].place;//assigns the pointer currslot to the slot the player is occupying
	slot *foundSlots = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(slot));
	player * *victims = malloc(NumberPlayers * NumberPlayers * sizeof(player));
	bool allslots[BOARD_SIZE][BOARD_SIZE];
	int count = 0, num = 0, answer = 0;

	for(int j = 0; j < BOARD_SIZE ; j++)
	{
		for(int k = 0; k < BOARD_SIZE ; k++)
		{
			allslots[j][k] = false;
		}
	}

	if (currSlot != NULL)
	{
	
		findSlots(1, 0, currSlot, foundSlots, &count, allslots);

		for (int k = 0 ; k < NumberPlayers ; k++)
		{
			if ((Players[k].place == Players[i].place) && (k != i))
			{
				victims[num] = &Players[k];	
				num++;									
			}
		}

		for (int j = 0 ; j < count ; j++)
		{
			for (int k = 0 ; k < NumberPlayers ; k++)
			{
				if ((Players[k].place->row == foundSlots[j].row) && (Players[k].place->column == foundSlots[j].column))
				{
					victims[num] = &Players[k];	
					num++;									
				}
			}
		}

		if (num >= 1)
		{
			if (num == 1) num = 0;
			else
			{
				while(answer < 1 || answer > num);
				{
					printf("\nwho do you want to attack:");
					for (int j = 0 ; j < num ; j++)
					{
						printf("\n[%d] %s (%d)", j+1, victims[j]->player_Name, victims[j]->Life_pts);
					}
					scanf("%d", &answer);
				}
				num = answer - 1;
			}

			if(victims[num]->Strength <= 70) 
			{
				printf("\nPlayer %s attacks %s for %d Life points.", Players[i].player_Name, victims[num]->player_Name, (int)((double)Players[i].Strength * 0.5));
				victims[num]->Life_pts -= (int)((double)Players[i].Strength * 0.5);
			}
			else 
			{
				printf("\nPlayer %s attacks %s for %d Life points.", victims[num]->player_Name, Players[i].player_Name, (int)((double)victims[num]->Strength * 0.3));
				Players[i].Life_pts -= (int)((double)victims[num]->Strength * 0.3);
			}
		}

		else if (num == 0)
		{
			puts("\nNo players nearby!");
			Decision();
		}
	}
}

void Distant()
{
	slot *currSlot = Players[i].place;
	slot *foundSlots = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(slot));
	player * *victims = malloc(NumberPlayers * NumberPlayers * sizeof(player));
	bool allslots[BOARD_SIZE][BOARD_SIZE];
	int count = 0, num = 0, answer;

	if(currSlot != NULL)
	{
		for(int j = 0; j < BOARD_SIZE ; j++)
		{
			for(int k = 0; k < BOARD_SIZE ; k++)
			{
				allslots[j][k] = false;
			}
		}

		findSlots(2, 0, currSlot, foundSlots, &count, allslots);
		findSlots(3, 0, currSlot, foundSlots, &count, allslots);
		findSlots(4, 0, currSlot, foundSlots, &count, allslots);

		for(int j = 0 ; j < count ; j++)
		{
			for(int k = 0 ; k < NumberPlayers ; k++)
			{
				if(((Players[k].place->row == foundSlots[j].row) && (Players[k].place->column == foundSlots[j].column)) && (k != i))
				{
					victims[num] = &Players[k];	
					num++;									
				}
			}
		}

		if(num >= 1)
		{
			if(num == 1) num = 0;
			else
			{
				while(answer < 1 || answer > num)
				{
					printf("\nwho do you want to attack:");
					for (int j = 0 ; j < num ; j++)
					{
						printf("\n[%d] %s (%d)", j+1, victims[j]->player_Name, victims[j]->Life_pts);
						puts("");
					}
					scanf("%d", &answer);
				} 
				num = answer - 1;
			}

			if(victims[num]->Dexterity < Players[i].Dexterity) 
			{
				printf("\nPlayer %s attacks %s for %d Life points.", Players[i].player_Name, victims[num]->player_Name, (int)((double)Players[i].Strength * 0.5));
				victims[num]->Life_pts -= (int)((double)Players[i].Strength * 0.5);
			}
			else printf("\n%s (%d) dodges your attack", victims[num]->player_Name, victims[num]->Life_pts);
		}

		else if(num == 0)
		{
			puts("\nNo players in range!");
			Decision();
		}
	}
}

void Magical()
{

	player * *victims = malloc(NumberPlayers * NumberPlayers * sizeof(player));
	int num = 0;
	int answer = 0;

	for(int j = 0 ; j < NumberPlayers ; j++)
	{
		if(j != i)
		{
			victims[num] = &Players[j];
			num++;									
		}
	}

	if(NumberPlayers == 2) num = 0;
	else
	{
		while(answer < 1 || answer > num)
		{
			printf("\nwho do you want to attack:");
			for (int j = 0 ; j < num ; j++)
			{
				printf("\n[%d] %s (%d)", j+1, victims[j]->player_Name, victims[j]->Life_pts);
			}
			scanf("%d", &answer);
		}
		num = answer - 1;
	}
	printf("Player %s attacks %s for %d Life points.", Players[i].player_Name, victims[num]->player_Name, (int)(((double)Players[i].Magic_Skills * 0.5)+((double)Players[i].Smartness * 0.2)));
	victims[num]->Life_pts -= (int)(((double)Players[i].Magic_Skills * 0.5)+((double)Players[i].Smartness * 0.2));
}

void sort() //Sort players so that Last player is the dead player and reduce number of player
{
	for( i = 0; i < NumberPlayers; i++)	//When player life points is less than 0, the player is pushed to the end of the array and number op players is decreased so that struct isnt used anymore
	{
		if(Players[i].Life_pts <= 0)
		{
			strcpy(Players[i].player_Name, Players[i+1].player_Name);
			Players[i].Life_pts = Players[i+1].Life_pts;
			Players[i].Dexterity = Players[i+1].Dexterity;
			Players[i].Luck = Players[i+1].Luck;
			Players[i].Magic_Skills = Players[i+1].Magic_Skills;
			Players[i].Smartness = Players[i+1].Smartness;
			Players[i].Strength = Players[i+1].Strength;
			Players[i].place = Players[i+1].place;
			
			Players[i+1].Life_pts = 0;
			
			NumberPlayers = NumberPlayers - 1;
			
		}
	}
}

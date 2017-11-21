#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This file contains all the header files combined into one single file for easier excecution
//This file is used to test the code and not the original submission

#define MAX_PLAYER_SIZE 6
#define BOARD_SIZE 7

void playerInformation();		
void createBoard(int boardSize);	
void playerINslots(int Size);
void playerInformation();											
void affectedAbilities(int i);	
void playersGO();	
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

typedef int bool;
enum {false, true };
enum slotType {Level_Ground, Hill, City};
int NumberPlayers;

typedef struct slot
{
	int row;				
	int column;				
	enum slotType type;		
	struct slot *left;		
	struct slot *right;		
	struct slot *up;		
	struct slot *down;		
} slot;

typedef struct player_Attributes
{
	char player_Name[20];
	int Life_pts;
	int Dexterity;
	int Luck;
	int Magic_Skills;
	int Smartness;
	int Strength;
	slot *place;
} player;


player Players[6];
slot ** board;

slot *upLeft;	
slot *upRight;		
slot *downLeft;		
slot *downRight;	

char *findSlotType(enum slotType type);
void findSlots(int reqDist, int currDist, struct slot * currSlot, struct slot * foundSlots, int *count, bool explored[BOARD_SIZE][BOARD_SIZE]);

int main()
{
	playerInformation();		

	createBoard(BOARD_SIZE);	
	
	playerINslots(BOARD_SIZE);	
	
	while(NumberPlayers >1)	
	{
		playersGO();			
	}	
	
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
			printf("\nPlayer %s", Players[i].player_Name);
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

void createBoard(int boardSize){
	
	board = malloc(boardSize * sizeof(slot *));

	for (int i = 0 ; i < boardSize ; i++){
		//This allocates in memory the space for the slots in each row of the board
		board[i] = malloc(boardSize * sizeof(slot));

		//For each slot it sets up the row and column number
		for(int j = 0 ; j < boardSize ; j++){
			board[i][j].row = i;
			board[i][j].column = j;
			
			int rand_num = ((rand() %3)+1);// makes a random number between 1 and 3
		//player and type remain empty as no players in slots yet
			if(rand_num == 1) //if the random number is equal to 1 puts level ground into slot.
			{
				board[i][j].type = Level_Ground;
			}
			else if(rand_num == 2) //if the random number is equal to 2 puts hill into slot
			{
				board[i][j].type = Hill;
			}
			else	//if the random number is equal to 3 puts city into slot
			{
				board[i][j].type = City;
			}					
		}
	}

	//It sets up the adjacent slots for the slots that are
	//not at the borders. These slots have 4 adjacent elements
	for (int i = 1 ; i < boardSize - 1 ; i++){
		for(int j = 1 ; j < boardSize - 1 ; j++){
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last row, except the slots at the edges.
	for(int j = 1; j < boardSize - 1 ; j++){
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on top of them
		// because they are on the first row of the board
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on down them
		// because they are on the last row of the board
		board[boardSize - 1][j].right = &board[boardSize - 1][j+1];
		board[boardSize -1][j].left = &board[boardSize - 1][j-1];
		board[boardSize - 1][j].up = &board[boardSize - 2][j];
		board[boardSize - 1][j].down = NULL;
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last column, except the slots at the edges.
	//
	for(int i = 1; i < boardSize - 1 ; i++){
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on the left
		// because they are on the first column of the board
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];
		board[i][0].left = NULL;

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on the right
		// because they are on the last column of the board
		board[i][boardSize-1].left = &board[i][boardSize-2];
		board[i][boardSize-1].up = &board[i-1][boardSize-1];
		board[i][boardSize-1].down = &board[i+1][boardSize -1];
		board[i][boardSize-1].right = NULL;
	}


	//It sets up the adjacent slots for the slot at position (0,0).
	//This only has only 2 adjacent slots: right and down
	board[0][0].right = &board[0][1];
	board[0][0].down = &board[1][0];
	board[0][0].up = NULL;
	board[0][0].left = NULL;

	//It sets up the adjacent slots for the slot at position (0,boardSize -1).
	//This only has only 2 adjacent slots: left and down
	board[0][boardSize-1].left = &board[0][boardSize-2];
	board[0][boardSize -1].down = &board[1][boardSize -1];
	board[0][boardSize-1].right = NULL;
	board[0][boardSize -1].up = NULL;

	//It sets up the adjacent slots for the slot at position (boarSize -1 ,0).
	//This only has only 2 adjacent slots: up and right
	board[boardSize -1][0].right = &board[boardSize -1][1];
	board[boardSize -1][0].up = &board[boardSize -2][0];
	board[boardSize -1][0].left = NULL;
	board[boardSize -1][0].down = NULL;

	//It sets up the adjacent slots for the slot at position (boarSize -1 ,boardSize-1).
	//This only has only 2 adjacent slots: up and left
	board[boardSize - 1][boardSize-1].up = &board[boardSize-2][boardSize-1];
	board[boardSize - 1][boardSize -1].left = &board[boardSize -1][boardSize -2];
	board[boardSize - 1][boardSize-1].right = NULL;
	board[boardSize - 1][boardSize -1].down = NULL;

	//assigns a pointer to slot at position (0, 0)
	upLeft = &board[0][0];
	//assigns pointer of pointer to slot at position (0, boardSize -1)
	upRight = &board[0][boardSize -1];
	//assigns pointer of pointer to slot at position ( boardSize -1,)
	downLeft = &board[boardSize -1][0];
	//assigns pointer of pointer to slot at position (boardSize -1, boardSize -1)
	downRight = &board[boardSize -1][boardSize -1];

}

/*
 * The recursive function that traverses the board to find the slots at a predefined
 * distance from the current slot and place them in foundSlots.
 * Parameters:
 * 	reqDist: the required distance from the starting slot
 * 	currDist: the distance of the current slot from the starting slot
 * 	currSlot: a pointer to the current slot that is traversed
 * 	foundSlots: the array of slots that are at a required distance from the starting slot
 * 	count: pointer to an integer representing the number of slots that are found to be at a required distance from the starting slot
 * 	explored: matrix indicating for each slot at row x and column y has been traversed (true) or not (false)
 */
void findSlots(int reqDist, int currDist, slot * currSlot, slot * foundSlots, int *count, bool explored[BOARD_SIZE][BOARD_SIZE])
{
	//The base case: the current slot is at the required distance from the starting slot
	if (currDist == reqDist)
	{
		//the current slot was not explored
		if ((explored[currSlot->row][currSlot->column] == false))
		{
			//The next available position (indicated by count) at foundSlots points to the current slot
			*(foundSlots + *count) = *currSlot;
			//the counter is incremented
			(*count)++;
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
		}
	}
	//The recursive call: the current slot is at a distance that is less than the required distance (more slots still have to be traversed)
	else
	{
		//the matrix of the explored slots set to true the element at the row and column of the current slot
		explored[currSlot->row][currSlot->column] = true;

		//if the current slot has the up slot != NULL (i.e. the slot is not in the first row)
		if (currSlot->up != NULL)
		{
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the up slot
			findSlots(reqDist, currDist + 1, currSlot->up, foundSlots, count, explored);
		}
		//if the current slot has the right slot != NULL (i.e. the slot is not in the last column)
		if (currSlot->right != NULL)
		{
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the right slot
			findSlots(reqDist, currDist + 1, currSlot->right, foundSlots, count, explored);
		}
		//if the current slot has the down slot != NULL (i.e. the slot is not in the last row)
		if (currSlot->down != NULL)
		{
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the down slot
			findSlots(reqDist, currDist + 1, currSlot->down, foundSlots, count, explored);
		}
		//if the current slot has the left slot != NULL (i.e. the slot is not in the first column)
		if (currSlot->left != NULL)
		{
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the left slot
			findSlots(reqDist, currDist + 1, currSlot->left, foundSlots, count, explored);
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

void playersGO()
{
	int j;

	//for loop to go through each players and allow them to make a move
	for(i = 0 ; i < NumberPlayers ; i++)
	{
		if(Players[i].Life_pts > 0) //prints which players turn it is
		{
			printf("\n\n%s's turn.\n", Players[i].player_Name);
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


void sort()
{
	for( i = 0; i < NumberPlayers; i++)
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

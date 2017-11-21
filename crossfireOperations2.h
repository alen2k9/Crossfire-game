#ifndef CROSSFIREOPERATIONS2_H_
#define CROSSFIREOPERATIONS2_H_

#define BOARD_SIZE 7

typedef int bool;
enum {false, true };
enum slotType {Level_Ground, Hill, City};

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


void createBoard(int boardSize);
void findSlots(int reqDist, int currDist, struct slot * currSlot, struct slot * foundSlots, int *count, bool explored[BOARD_SIZE][BOARD_SIZE]);


int NumberPlayers;

void playerInformation();							
void playerINslots(int Size);					
void affectedAbilities(int i);	
void playersGO();							


char *findSlotType(enum slotType type);	
				
#endif
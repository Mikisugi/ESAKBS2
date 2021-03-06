/*#include <stdio.h>
#include "includes.h"

/* Definition of Task Stacks
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];

/* Definition of Task Priorities

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2

/* Prints "Hello World" and sleeps for three seconds
void task1(void* pdata)
{
  while (1)
  {
    printf("Hello from task1\n");
    OSTimeDlyHMSM(0, 0, 3, 0);
  }
}
/* Prints "Hello World" and sleeps for three seconds
void task2(void* pdata)
{
  while (1)
  {
    printf("Hello from task2\n");
    OSTimeDlyHMSM(0, 0, 3, 0);
  }
}
/* The main function creates two task and starts multi-tasking
int main(void)
{

  OSTaskCreateExt(task1,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE-1],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);


  OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE-1],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  OSStart();
  return 0;
}
*/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"
#include "vector.h"
#include "includes.h"

//definition of Task Stacks
#define   TASK_STACKSIZE 512
OS_STK    taskStartGame_stk[TASK_STACKSIZE];


//definition of Task Priorities
#define TASKSTARTGAME_PRIORITY 1

//the main board
unsigned char board [10][10];

//Node for the linked list of scores made in minimaxAlgorithmRecursive
typedef struct Node
{
	struct Node * next;
	int score;
} node_t;

//Node for the linked list of moves and scores made in minimaxAlgorithm
typedef struct NodeMove
{
	struct NodeMove * next;
	int score;
	unsigned char row;
	unsigned char field;
	unsigned char dir;
	unsigned char isCapture;
} nodemove_t;

//function definitions
void printCountPieces();
void printBoard(unsigned char * tempBoard[], unsigned char changedRow, unsigned char changedField, unsigned char oldRow, unsigned char oldField);
//Vector *kingCapture(Location currentLocation, unsigned char tempBoard [10][10], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing);
//void deleteKingCapture(Capture *capture);
//unsigned char stripKingCapture(Vector *vector, unsigned char count);
//unsigned char manCapture(unsigned char * tempBoard[], unsigned char row, unsigned char field, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing);
//unsigned char manMove(unsigned char * tempBoard[], unsigned char row, unsigned field, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed direction);
//int checkIfCanMove(unsigned char * tempBoard[], int row, int field, int dir, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed direction);
//int capture(int row,int field,int king);
//void move(unsigned char * tempBoard[], unsigned char row, unsigned char field, unsigned char dir, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction);
//void createKing(unsigned char * tempBoard[]);
//int minimaxAlgorithmRecursive(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction, int depth);
//int minimaxAlgorithm(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction, int depth);
//unsigned char algorithm(unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction);
//unsigned char playerInput();
//void play();
void createBoard();
void createEmptyBoard();

void taskStartGame(void* pdata);


int main(void)
{
	OSInit();
	printf("hai\n");
	OSTaskCreateExt(taskStartGame,NULL,(void *)&taskStartGame_stk[TASK_STACKSIZE-1],TASKSTARTGAME_PRIORITY,TASKSTARTGAME_PRIORITY,taskStartGame_stk,TASK_STACKSIZE,NULL,0);
  printf("hoi\n");
  OSStart();
  return 0;
}

void taskStartGame(void* pdata)
{
	printf("aardappel\n");
	createBoard();
	printf("kakkie\n");
	printBoard((unsigned char **)board,100,100,100,100);
	printf("poepie\n");
	//play();
}


void printCountPieces(){
	//Count vars that will be printed
	unsigned char enemyCount = 0;
	unsigned char friendlyCount = 0;

	//Check every field on the board
	for(unsigned char row = 0; row < 10; row++){
		for(unsigned char field = 0; field < 10; field++){

			//If the field has a friendly man or king on it, add to the friendly counter
			if(board[row][field] == FRIENDLY || board[row][field] == FRIENDLYKING){
				friendlyCount++;

			//If the field has an enemy man or king on it, add to the enemy counter
			}else if(board[row][field] == ENEMY || board[row][field] == ENEMYKING){
				enemyCount++;
			}
		}
	}

	//Print the amount
	//printf("%s %d%c", "Enemy #", enemyCount, '\n');
	//printf("%s %d%c", "Friendly #", friendlyCount, '\n');
}

/*
Draw the board.
Vars are for coloring changes on the board. Not important if COLORS_ENABLED is 0
changedRow	= The row where the piece has gone
changedField	= The field where the piece has gone
oldRow		= The row where the piece previously was
oldField	= The field where the piece previously was
*/

void printBoard(unsigned char * tempBoard[], unsigned char changedRow, unsigned char changedField, unsigned char oldRow, unsigned char oldField)
{
	unsigned char b[10][10];
	memcpy(b,tempBoard,100);

	if(COLORS_ENABLED) printf("  0  1  2  3  4  5  6  7  8  9");
	else printf("   0   1   2   3   4   5   6   7   8   9\n");

	for(unsigned char row = 0; row < 10; row++){

		if(!COLORS_ENABLED) printf(" |");

		for(unsigned char o = 0; o < 10; o++){
			if(!COLORS_ENABLED) printf("---|");
		}

		if(COLORS_ENABLED) printf("\n%i",row);
		else printf("\n%i|",row);

		for(unsigned char field = 0; field < 10; field++){

			/*
			Give field the appropriate color
			30;40 = black on black (empty black field)
			37;40 = white on black (black field with piece)
			37;47 = white on white (empty white field)
			*/
			if(COLORS_ENABLED){
				switch(b[row][field]){
					case BLACK :
						printf("\e[30;40m");
						break;
					case FRIENDLY :
						printf("\e[37;40m");
						break;
					case FRIENDLYKING :
						printf("\e[37;40m");
						break;
					case ENEMY :
						printf("\e[37;40m");
						break;
					case ENEMYKING :
						printf("\e[37;40m");
						break;
					default :
						printf("\e[37;47m");
						break;
				}
			}

			//Give changed piece and previous location of that piece a special color
			if(COLORS_ENABLED && row == changedRow && field == changedField){
				printf("\x1b[33m");
			}else if(COLORS_ENABLED && row == oldRow && field == oldField){
				printf("\x1b[33m");
			}

			//Draw the item on the board
			switch(b[row][field]){
				case BLACK :
					if(COLORS_ENABLED) printf(" ■ ");
					else printf("   ");
					break;
				case FRIENDLY :
					if(UNICODE_ENABLED) printf(" ⛂ ");
					else printf(" F ");
					break;
				case FRIENDLYKING :
					if(UNICODE_ENABLED) printf(" ⛃ ");
					else printf("F K");
					break;
				 case ENEMY :
					if(UNICODE_ENABLED) printf(" ⛀ ");
					else printf(" E ");
					break;
				case ENEMYKING :
					if(UNICODE_ENABLED) printf(" ⛁ ");
					else printf("E K");
					break;
				default :
					printf("   ");
					break;
			}

			//reset color or draw | to the right of the item
			if(COLORS_ENABLED) printf("\x1b[0m");
			else printf("|");
		}

		//Next row
		if(!COLORS_ENABLED) printf("\n");
	}

	//Print the last line
	if(!COLORS_ENABLED) printf(" |");
	for(unsigned char o = 0; o < 10; o++){
		if(!COLORS_ENABLED) printf("---|");
	}

	//done done
	printf("\n\n\n");
}

/*
Vector *kingCapture(Location currentLocation, unsigned char tempBoard [10][10], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing){
	printf("begin king capture");
	Vector *captureVector = vectorInit();
	Location possibleEnemy, possibleLanding;
	for(signed char rowDirection = -1; rowDirection < 2; rowDirection = rowDirection + 2){
		for(signed char fieldDirection = -1; fieldDirection < 2; fieldDirection = fieldDirection + 2){
			printf("Row direction: %d, Field Direction: %d\n", rowDirection, fieldDirection);
			possibleEnemy.row = currentLocation.row;
			possibleEnemy.field = currentLocation.field;
			while(possibleEnemy.row + rowDirection > 0 && possibleEnemy.row + rowDirection < 9 && possibleEnemy.field + fieldDirection > 0 && possibleEnemy.field + fieldDirection < 9){
				possibleEnemy.row += rowDirection;
				possibleEnemy.field += fieldDirection;
				printf("possible enemy row: %d, possible enemy field: %d\n", possibleEnemy.row, possibleEnemy.field);
				if(tempBoard[possibleEnemy.row][possibleEnemy.field] == enemy || tempBoard[possibleEnemy.row][possibleEnemy.field] == enemyKing){
					printf("beeb boop enemy detected\n");
					possibleLanding.row = possibleEnemy.row;
					possibleLanding.field = possibleEnemy.field;

					unsigned char i = 0;
					while(possibleLanding.row + rowDirection > -1 && possibleLanding.row + rowDirection < 10 && possibleLanding.field + fieldDirection > -1 && possibleLanding.field + fieldDirection < 10){
						possibleLanding.row += rowDirection;
						possibleLanding.field += fieldDirection;
						if(tempBoard[possibleLanding.row][possibleLanding.field] == BLACK){
							printf("LANDINGMAYDAYMAYDAY %d \n", i);
							i++;

							printf("LandROW : %d\n LandField: %d\n\n", possibleLanding.row, possibleLanding.field);
							Capture *capture = malloc(sizeof(Capture)) ;
							capture->oldLocation = currentLocation;
							capture->captureLocation = possibleEnemy;
							capture->newLocation = possibleLanding;
							capture->piece = tempBoard[possibleEnemy.row][possibleEnemy.field];
							tempBoard[currentLocation.row][currentLocation.field] = BLACK;
							tempBoard[possibleLanding.row][possibleLanding.field] = friendlyKing;
							tempBoard[possibleEnemy.row][possibleEnemy.field] = BLACK;

							capture->nextCaptures = kingCapture(possibleLanding, tempBoard,friendly, friendlyKing, enemy, enemyKing);
							printf("add stuff to vector\n");
							vectorAdd(captureVector, (void*)capture);

							printf("restore board");
							tempBoard[currentLocation.row][currentLocation.field] = friendlyKing;
							tempBoard[possibleLanding.row][possibleLanding.field] = BLACK;
							tempBoard[possibleEnemy.row][possibleEnemy.field] = capture->piece;
						}
					}
					break;
				}
			}

		}
	}
	return captureVector;
}
*/
/*
void deleteKingCapture(Capture *capture){
	if(capture->nextCaptures != NULL){
		Vector * vector = capture->nextCaptures;
		for(unsigned char i = 0; i < vector->count; i++){
			if(vector->data[i] != NULL){
				deleteKingCapture(vector->data[i]);
			}
		}
		vectorFree(vector);
	}
	free(capture);
}

unsigned char stripKingCapture(Vector *vector, unsigned char count){
	unsigned char oldCount = 0;
	count++;
	for(unsigned char i = 0; i < vector->count; i++){
		Capture *capture = ((Capture *)vector->data[i]);
		if(capture->nextCaptures->count == 0){
			vectorFree(capture->nextCaptures);
			capture->nextCaptures = NULL;
		}else if(((Capture *)vector->data[i])->nextCaptures != NULL){
			unsigned char newCount = stripKingCapture(((Capture *)vector->data[i])->nextCaptures, count);
			if(oldCount < newCount){
				for(unsigned char delI = i; delI > 0; delI--){
					if(vector->data[delI] != NULL){
						deleteKingCapture(vector->data[delI]);
						vector->data[delI] = NULL;
					}
				}
				oldCount = newCount;
			}else if(oldCount > newCount){
				if(vector->data[i] != NULL){
					// delete recursive
					deleteKingCapture(vector->data[i]);
					vector->data[i] = NULL;
				}
			}
		}

	}
	return oldCount;
}
*/
/*
//TODO: Doesn't pick the longest capture yet
unsigned char manCapture(unsigned char * tempBoard[], unsigned char row, unsigned char field, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing){

	unsigned char b[10][10];
	memcpy(b,tempBoard,100);

	unsigned char possibleEnemyRow, possibleEnemyField, possibleNewRow, possibleNewField;

	for(signed char rowDirection = -1; rowDirection < 2; rowDirection = rowDirection + 2){

		for(signed char fieldDirection = -1; fieldDirection < 2; fieldDirection = fieldDirection + 2){

			possibleEnemyRow = row + rowDirection;
			possibleEnemyField = field + fieldDirection;

			// Dont check the side for enemies you cant capture them there
			if(possibleEnemyRow > 0 && possibleEnemyRow < 9 && possibleEnemyField > 0 && possibleEnemyField < 9){
			//	printf("%s %d%c", "enemy in range?", board[possibleEnemyRow][possibleEnemyField] == enemy || board[possibleEnemyRow][possibleEnemyField] == enemyKing, '\n');
				if(b[possibleEnemyRow][possibleEnemyField] == enemy || b[possibleEnemyRow][possibleEnemyField] == enemyKing){

				//	printf("%s %d%c%d%c", "beeb boob enemy detected at",  possibleEnemyRow, '.', possibleEnemyField, '\n');
					possibleNewRow = possibleEnemyRow + rowDirection;
					possibleNewField = possibleEnemyField + fieldDirection;

					if(b[possibleNewRow][possibleNewField] == BLACK){

					//	printf("charge!!!!!!!!!\n");
						b[possibleNewRow][possibleNewField] = board[row][field];
						b[row][field] = BLACK;
						b[possibleEnemyRow][possibleEnemyField] = BLACK;
						#if DEBUG
							printBoard((unsigned char **)b,possibleNewRow, possibleNewField, row, field);
							printf("%s %d %s %d%c", "old row", row, "old field", field,'\n');
							printf("%s %d %s %d%c", "new row", possibleNewRow, "new field", possibleNewField,'\n');
						#endif
						//printCountPieces();
						manCapture((unsigned char **)b, possibleNewRow, possibleNewField, friendly, friendlyKing, enemy, enemyKing);
						memcpy(tempBoard,b,100);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
*/
/*
unsigned char manMove(unsigned char * tempBoard[], unsigned char row, unsigned field, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed direction){
	signed char possibleNewField;
	signed char possibleNewRow = row + direction;

	if(possibleNewRow > -1 && possibleNewRow < 10){
		for(signed char fieldDirection = -1; fieldDirection < 2; fieldDirection = fieldDirection + 2){
			possibleNewField = field + fieldDirection;

			if(possibleNewField > -1 && possibleNewField < 10 && board[possibleNewRow][possibleNewField] == BLACK){
				tempBoard[possibleNewRow][possibleNewField] = tempBoard[row][field];
				tempBoard[row][field] = BLACK;
				#if DEBUG
					printBoard((unsigned char **)tempBoard,possibleNewRow, possibleNewField, row, field);
				#endif
				return 1;
			}
		}
	}
	return 0;
}
*/
/*
int checkIfCanMove(unsigned char * tempBoard[], int row, int field, int dir, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed direction){

	int retVal = 0;

	unsigned char b[10][10];
	memcpy(b,tempBoard,100);

	int stone = b[row][field];

	if(stone == FRIENDLY || stone == ENEMY)
	{
		if(direction == FRIENDLYDIRECTION)
		{
			if(dir == 1)
			{
				if(b[row-1][field-1] == BLACK) retVal = 1;
				else retVal = 0;
			}
			else if(dir == 2)
			{
				if(b[row-1][field+1] == BLACK) retVal = 1;
				else retVal = 0;
			}
		}
		else if(direction == ENEMYDIRECTION)
		{
			if(dir == 3)
			{
				if(b[row+1][field-1] == BLACK) retVal = 1;
				else retVal = 0;
			}
			else if(dir == 4)
			{
				if(b[row+1][field+1] == BLACK) retVal = 1;
				else retVal = 0;
			}
		}
	}
	else if(stone == FRIENDLYKING || stone == ENEMYKING)
	{

	}

	//if(retVal) printf("can move!\n\n");
	//else printf("can't move :(\n\n");

	return retVal;
}
*/
/*
//TODO: make this obsolete, replace with manCapture
int capture(int row,int field,int king){

	if((board[row-1][field-1] == ENEMY || board[row-1][field-1] == ENEMYKING)
	&&
	(board[row-2][field-2] == BLACK || board[row-2][field-2] == BLACK)){

		board[row-2][field-2] = board[row][field];
		board[row-1][field-1] = BLACK;
		board[row][field] = BLACK;
		#if DEBUG
			printBoard((unsigned char **)board,row-2,field-2,row,field);
		#endif
		return 1;
	}

	else if((board[row-1][field+1] == ENEMY || board[row-1][field+1] == ENEMYKING)
	&&
	(board[row-2][field+2] == BLACK || board[row-2][field+2] == BLACK)){

		board[row-2][field+2] = board[row][field];
		board[row-1][field+1] = BLACK;
		board[row][field] = BLACK;
		#if DEBUG
			printBoard((unsigned char **)board,row-2,field+2,row,field);
		#endif
		return 1;
	}

	else if((board[row+1][field-1] == ENEMY || board[row+1][field-1] == ENEMYKING)
	&&
	(board[row+2][field-2] == BLACK || board[row+2][field-2] == BLACK)){

		board[row+2][field-2] = board[row][field];
		board[row+1][field-1] = BLACK;
		board[row][field] = BLACK;
		#if DEBUG
			printBoard((unsigned char **)board,row+2,field-2,row,field);
		#endif
		return 1;
	}

	else if((board[row+1][field+1] == ENEMY || board[row+1][field+1] == ENEMYKING)
	&&
	(board[row+2][field+2] == BLACK || board[row+2][field+2] == BLACK)){

		board[row+2][field+2] = board[row][field];
		board[row+1][field+1] = BLACK;
		board[row][field] = BLACK;
		#if DEBUG
			printBoard((unsigned char **)board,row+2,field+2,row,field);
		#endif
		return 1;
	}

	else return 0;
}
*/
/*
//TODO: make this obsolete, replace with manMove
void move(unsigned char * tempBoard[], unsigned char row, unsigned char field, unsigned char dir, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction){

	unsigned char b[10][10];
	memcpy(b,tempBoard,100);

	int stone = b[row][field];

	b[row][field] = BLACK;

	switch(dir){
		case 1:
			b[row-1][field-1] = stone;
			#if DEBUG
				printBoard((unsigned char **)b,row-1,field-1,row,field);
			#endif
			break;
		case 2:
			b[row-1][field+1] = stone;
			#if DEBUG
				printBoard((unsigned char **)b,row-1,field+1,row,field);
			#endif
			break;
		case 3:
			b[row+1][field-1] = stone;
			#if DEBUG
				printBoard((unsigned char **)b,row+1,field-1,row,field);
			#endif
			break;
		case 4:
			b[row+1][field+1] = stone;
			#if DEBUG
				printBoard((unsigned char **)b,row+1,field+1,row,field);
			#endif
			break;
	}
	memcpy(tempBoard,b,100);
}
*/
/*
void createKing(unsigned char * tempBoard[])
{
	unsigned char b[10][10];
	memcpy(b,tempBoard,100);

	for(unsigned char field = 0; field<10; field++)
	{
		if(b[0][field] == FRIENDLY)
			b[0][field] = FRIENDLYKING;

		if(b[9][field] == ENEMY)
			b[0][field] = ENEMYKING;
	}

	memcpy(tempBoard,b,100);
}
*/
/*
int minimaxAlgorithmRecursive(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction, int depth)
{
	int bestScore;

	unsigned char b[10][10];
	memcpy(b,tempBoard,100);

	createKing((unsigned char **)b);

	if(depth > 0)
	{
		node_t * head = NULL;
		head = malloc(sizeof(node_t));

		node_t * current = head;

		for(unsigned char row = 0; row < 10; row++)
		{
			for(unsigned char field = 0; field < 10; field++)
			{
				if(b[row][field] == friendly)
				{
					int nextDirection;
					if(direction == -1) nextDirection = 1;
					if(direction == 1) nextDirection = -1;

					unsigned char newBoard[10][10];
					memcpy(newBoard,b,100);

					int captured = manCapture((unsigned char **)newBoard, row, field, friendly, friendlyKing, enemy, enemyKing);
					if(captured)
					{
						#if DEBUG
							printf("R%i: [%i][%i] can capture\n",depth,row,field);
						#endif
						int enemiesLeft = 0;
						for(unsigned char r = 0; r < 10; r++)
						{
							for(unsigned char f = 0; f < 10; f++)
							{
								if(b[row][field] == enemy || b[row][field] == enemyKing)
									enemiesLeft++;
							}
						}
						if(enemiesLeft)
						{
							#if DEBUG
								printf("R%i: there are enemies left after the capture\n",depth);
								printf("R%i: calling minimaxAlgorithmRecursive with depth %i\n",depth,depth-1);
							#endif
							int score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);
							#if DEBUG
								printf("R%i: adding score %i to linked list\n",depth,score);
							#endif
							current = head;
							while (current->next != NULL) current = current->next;
							current->next = malloc(sizeof(node_t));
							current->score = score;
						}
						else
						{
							#if DEBUG
								printf("R%i: there are enemies left after the capture\n",depth);
								printf("R%i: calling minimaxAlgorithmRecursive with depth 0\n",depth);
							#endif
							//TODO should i do this? this is a dirty fix for when after a capture, the same stone is used twice.
							int score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, 0);
							#if DEBUG
								printf("R%i: adding score %i to list\n",depth,score);
							#endif
							current = head;
							while (current->next != NULL) current = current->next;
							current->next = malloc(sizeof(node_t));
							current->score = score;
						}
					}

					#if DEBUG
						printf("R%i: checking if [%i][%i] can move\n",depth,row,field);
					#endif
					for(int d = 1;d<=4;d++)
					{
						if(checkIfCanMove((unsigned char **)b, row, field, d, friendly, friendlyKing, enemy, enemyKing, direction) == 1)
						{
							#if DEBUG
								printf("R%i: [%i][%i] can move with dir %i\n",depth,row,field,d);
							#endif
							unsigned char newBoard[10][10];
							memcpy(newBoard,b,100);
							move((unsigned char **)newBoard, row, field, d, friendly, friendlyKing, enemy, enemyKing, direction);
							int score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);
							#if DEBUG
								printf("R%i: adding score %i to linked list\n",depth,score);
							#endif
							current = head;
							while (current->next != NULL) current = current->next;
							current->next = malloc(sizeof(node_t));
							current->score = score;
						}
					}
				}
				else if(b[row][field] == friendlyKing)
				{
					#if DEBUG
						printf("R%i: yo dude lmao HAHAHA this is a king SAYONARA NIGGA\n",depth);
					#endif
					//TODO: kingCapture
					//TODO: kingMove
				}
			}
		}

		if(direction == FRIENDLYDIRECTION) bestScore = -1000;
		else bestScore = 1000;

		//remove the last item in the list

		//if there is only one item in the list, remove it
		if (head->next == NULL) free(head);
		//get to the second to last node in the list
		current = head;
		while (current->next->next != NULL) current = current->next;
		//now current points to the second to last item of the list, so let's remove current->next
		free(current->next);
		current->next = NULL;

		#if DEBUG
			printf("R%i list: \n",depth);
			current = head;
			while(current != NULL)
			{
				printf("score: %i\n",current->score);
				current = current->next;
			}
		#endif

		current = head;

		while (current != NULL)
		{
			if(direction == FRIENDLYDIRECTION && current->score > bestScore)
			{
				#if DEBUG
					printf("score %i is bigger than best score %i, overwriting\n",current->score,bestScore);
				#endif
				bestScore = current->score;
			}
			else if(direction == ENEMYDIRECTION && current->score < bestScore)
			{
				#if DEBUG
					printf("score %i is smaller than best score %i, overwriting\n",current->score,bestScore);
				#endif
				bestScore = current->score;
			}
			#if DEBUG
				else
				{
					printf("score %i is not better than best score %i, not overwriting\n",current->score,bestScore);
				}
			#endif
			current = current->next;
		}
		#if DEBUG
			printf("R%i: iterated, bestScore is %i\n",depth,bestScore);
		#endif
	}
	else
	{
		bestScore = 0;
		//calculate score to return
		for(unsigned char row = 0;row<10;row++)
		{
			for(unsigned char field = 0;field<10;field++)
			{
				if(b[row][field] == FRIENDLY)		bestScore = bestScore + (9-row);
				else if(b[row][field] == FRIENDLYKING)	bestScore = bestScore + 9;
				else if(b[row][field] == ENEMY)		bestScore = bestScore - row;
				else if(b[row][field] == ENEMYKING)	bestScore = bestScore - 9;
			}
		}
		#if DEBUG
			printf("R%i: calculated score: %i\n",depth,bestScore);
		#endif
	}

	//free the whole list
	node_t * tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}

	return bestScore;
}
*/
/*
int minimaxAlgorithm(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction, int depth)
{
	unsigned char b[10][10];
	memcpy(b,tempBoard,100);

	createKing((unsigned char **)b);

	//if(direction == FRIENDLYDIRECTION) best->score = -1000;
	//else best->score = 1000;
	//printf("S: made best score %i\n",best->score);

	nodemove_t * head = NULL;
	head = malloc(sizeof(nodemove_t));
	nodemove_t * current = head;

	for(unsigned char row = 0; row < 10; row++)
	{
		for(unsigned char field = 0; field < 10; field++)
		{
			if(b[row][field] == friendly)
			{
				int nextDirection;
				if(direction == FRIENDLYDIRECTION) nextDirection = ENEMYDIRECTION;
				if(direction == ENEMYDIRECTION) nextDirection = FRIENDLYDIRECTION;

				unsigned char newBoard[10][10];
				memcpy(newBoard,b,100);

				int captured = manCapture((unsigned char **)newBoard, row, field, friendly, friendlyKing, enemy, enemyKing);
				if(captured)
				{
					#if DEBUG
						printf("S : [%i][%i] can capture\n",row,field);
					#endif
					int enemiesLeft = 0;
					for(unsigned char r = 0; r < 10; r++)
					{
						for(unsigned char f = 0; f < 10; f++)
						{
							if(newBoard[row][field] == enemy || newBoard[row][field] == enemyKing)
							{
								enemiesLeft = 1;
							}
						}
					}
					#if DEBUG
						printf("enemiesLeft: %i\n",enemiesLeft);
					#endif
					if(enemiesLeft == 1)
					{
						#if DEBUG
							printf("S : there are enemies left");
						#endif
						int score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);
						#if DEBUG
							printf("S : adding score %i to linked list\n",score);
						#endif
						current = head;
						while (current->next != NULL) current = current->next;
						current->next = malloc(sizeof(nodemove_t));
						current->score = score;
						current->row = row;
						current->field = field;
						current->dir = 0;
						current->isCapture = 1;
					}
					else
					{
						#if DEBUG
							printf("S : there are no enemies left");
						#endif
						// if there are no enemies left
						int score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, 0);
						#if DEBUG
							printf("S : adding score %i to list\n",score);
						#endif
						current = head;
						while (current->next != NULL) current = current->next;
						current->next = malloc(sizeof(nodemove_t));
						current->score = score;
						current->row = row;
						current->field = field;
						current->dir = 0;
						current->isCapture = 1;
					}
				}

				for(int d = 1;d<=4;d++)
				{
					if(checkIfCanMove((unsigned char **)b, row, field, d, friendly, friendlyKing, enemy, enemyKing, direction) == 1)
					{
						#if DEBUG
							printf("S : [%i][%i] dir %i can move\n",row,field,d);
						#endif
						unsigned char newBoard[10][10];
						memcpy(newBoard,b,100);
						move((unsigned char **)newBoard, row, field, d, friendly, friendlyKing, enemy, enemyKing, direction);
						int score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);
						#if DEBUG
							printf("S : adding score %i to linked list\n",score);
						#endif
						current = head;
						while (current->next != NULL) current = current->next;
						current->next = malloc(sizeof(nodemove_t));
						current->score = score;
						current->row = row;
						current->field = field;
						current->dir = d;
						current->isCapture = 0;
					}
				}
			}
			else if(b[row][field] == friendlyKing)
			{

			}
		}
	}

	//remove last item in the list
	if there is only one item in the list, remove it
	if (head->next == NULL) free(head);
	 get to the second to last node in the list
	current = head;
	while (current->next->next != NULL) current = current->next;
	 now current points to the second to last item of the list, so let's remove current->next
	free(current->next);
	current->next = NULL;

	#if DEBUG
		printf("S : final list: \n");
		current = head;
		while(current != NULL)
		{
			printf("score: %i\nrow: %i\nfield: %i\ndir: %i\nisCapture: %i\n\n",current->score,current->row,current->field,current->dir,current->isCapture);
			current = current->next;
		}
	#endif

	nodemove_t * bestMove = malloc(sizeof(nodemove_t));

	if(direction == FRIENDLYDIRECTION) bestMove->score = -1000;
	else bestMove->score = 1000;

	current = head;
	while (current != NULL)
	{
		if(direction == FRIENDLYDIRECTION && current->score > bestMove->score)
		{
			#if DEBUG
				printf("score %i is bigger than best score %i, overwriting\n",current->score,bestMove->score);
			#endif
			bestMove = current;
		}
		else if(direction == ENEMYDIRECTION && current->score < bestMove->score)
		{
			#if DEBUG
				printf("score %i is smaller than best score %i, overwriting\n",current->score,bestMove->score);
			#endif
			bestMove = current;
		}
		#if DEBUG
			else printf("score %i is not better than best score %i, not overwriting\n",current->score,bestMove->score);
		#endif

		current = current->next;
	}

	if(bestMove != NULL)
	{
		if(bestMove->isCapture == 1)
		{
			int captured = manCapture((unsigned char **)board, bestMove->row, bestMove->field, friendly, friendlyKing, enemy, enemyKing);
			#if DEBUG
				if(!captured) printf("ERROR: not captured\n");
			#endif
		}
		else
		{
			move((unsigned char **)board, bestMove->row, bestMove->field, bestMove->dir, friendly, friendlyKing, enemy, enemyKing, direction);
		}

		//TODO: make this look prettier?
		printBoard((unsigned char **)board, bestMove->row, bestMove->field,100,100);

		return 1;
	}
	else
	{
		return 0;
	}
}
*/
/*
//Oude algoritme. Plan B als minimax aan het eind helemaal ontploft
unsigned char algorithm(unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction){
	unsigned char captured = 0;
	unsigned char moved = 0;
	unsigned char couldNotCapture = 0;
	unsigned char couldNotMove = 0;

	while(couldNotMove == 0){
		for(unsigned char row = 0; row < 10; row++){
		//	printf("friest for\n");
			for(unsigned char field = 0; field < 10; field++){
			//	printf("friendly check\n");
				// piece check if a piece can capture
				if(board[row][field] == friendly){
				//	printf("friendly\n");
					if(couldNotCapture == 0){
						captured = manCapture((unsigned char **)board, row, field, friendly, friendlyKing, enemy, enemyKing);
					}else{
						moved = manMove((unsigned char **)board, row, field, friendly, friendlyKing, enemy, enemyKing, direction);
					}

					if(moved == 1 || captured == 1){
						#if DEBUG
							printf("moved or captured\n");
						#endif
						return 1;
					}
				}
			}
		}
		if(couldNotCapture == 1 && moved == 0){
			couldNotMove = 1;
			#if DEBUG
				printf("could not move\n");
			#endif
		}else if(captured == 0){
			couldNotCapture = 1;
			#if DEBUG
				printf("could not capture\n");
			#endif
		}
	}
	return 0;
}
*/
/*
unsigned char playerInput()
{
	int stuffToDo = 0;

	//Check if we can capture, capture and check if we can still make moves all in one loop :)
	for(int row = 0; row < 10; row++)
	{
		for(int field = 0; field < 10; field++)
		{
			if(board[row][field] == FRIENDLY)
			{
				stuffToDo = 1;
				if(manCapture((unsigned char **)board, row, field, FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING)) return 1;
			}
			else if(board[row][field] == FRIENDLYKING)
			{
				stuffToDo = 1;
				if(capture(row, field, 1)) return 1;
			}
		}
	}

	createKing((unsigned char **)board);

	//If there are no friendly units on the board, return 0, which will end the game.
	if(!stuffToDo) return 0;

	int pRow = -1;
	int pField = -1;

	printf("Row to select: ");

	char *p, s[100];
    	while (fgets(s, sizeof(s), stdin)) {
    	    pRow = strtol(s, &p, 10);
    	    if (p == s || *p != '\n') {
    	        printf("Please enter a number: ");
    	    } else break;
    	}

    	if(pRow < 0 || pRow > 9){

    		printf("Invalid number, try again\n");
    		return playerInput();
    	}

	printf("Field to select: ");

    	while (fgets(s, sizeof(s), stdin)) {
    	    pField = strtol(s, &p, 10);
    	    if (p == s || *p != '\n') {
    	        printf("Please enter a number: ");
    	    } else break;
    	}

    	if(pField < 0 || pField > 9){

    		printf("Invalid number, try again\n");
    		return playerInput();
    	}

	int stone = board[pRow][pField];

	if(stone == FRIENDLY || stone == FRIENDLYKING){

		int isKing;
		if(stone == FRIENDLYKING) isKing = 1;
		else isKing = 0;

		printf("\n1   2\n");
		printf(" \\ /\n");
		printf("  x\n");
		printf(" / \\ \n");
		printf("3   4\n\n");

		printf("Select a direction: ");
		int pDir = -1;
		scanf("%i", &pDir);
		printf("\n");

		printf("\npRow: %d\npField: %d\npDir: %d\n\n",pRow,pField,pDir);

		if(checkIfCanMove((unsigned char **)board,pRow,pField,pDir, FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION)){
			move((unsigned char **)board,pRow,pField,pDir, FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION);
			createKing((unsigned char **)board);
			printBoard((unsigned char **)board,pRow,pField,100,100);
			return 1;
		}else{
			printf("Can't move to that field! Try again.\n");
			return playerInput();
		}
	}else{
		printf("Wrong piece selected, try again\n");
		return playerInput();
	}
}
*/
/*
void play(){
	unsigned char friendlyMoved = 1;
	unsigned char enemyMoved = 1;
	unsigned char turn = 0;
	unsigned char turnCounter = 0;

	while(friendlyMoved == 1 && enemyMoved == 1){
		if(turn == 0){
			printf("FRIENDLY TURN\n");
			if(PLAYER_INPUT){
				friendlyMoved = playerInput();
			}else{
				//friendlyMoved = bfAlgorithm(FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION);
				friendlyMoved = minimaxAlgorithm((unsigned char **)board,FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION,4);
				//friendlyMoved = 1;
				//friendlyMoved = algorithm(FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION);
			}
			turn = 1;
		}else{
			printf("ENEMY TURN\n");
			//enemyMoved = bfAlgorithm(ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION);
			enemyMoved = minimaxAlgorithm((unsigned char **)board,ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION,3);
			//enemyMoved = 1;
			//enemyMoved = algorithm(ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION);
			turn = 0;
		}
		turnCounter++;
	}

	if(friendlyMoved == 0){
		printf("YOU LOST\n");
	}else{
		printf("YOU WON\n");
	}
	turnCounter--;
	printf("%s %d %s", "the game lasted for # turns", turnCounter, "\n");
}
*/

void createBoard(){
	unsigned char x = 1;
	unsigned char y = 0;
	unsigned char even = 1;
	printf("\nkat\n");

	while(y < 10){
		printf("%i %i %i\n", x, y, even);
		board[y][x] = BLACK;
		if(y < 4){
			board[y][x] = ENEMY;
		}
		if(y > 5){
			board[y][x] = FRIENDLY;
		}

		if(x + 2 < 10 ){
			x = x + 2;
		}else{
			y++;
			x = 0;
			even = !even;
			if(even > 0){
				x++;
			}
		}
	}
}

void createEmptyBoard()
{
	unsigned char x = 1;
	unsigned char y = 0;
	unsigned char even = 1;

	while(y < 10){
		board[y][x] = BLACK;

		if(x + 2 < 10 ){
			x = x + 2;
		}else{
			y++;
			x = 0;
			even = !even;
			if(even > 0){
				x++;
			}
		}
	}
}


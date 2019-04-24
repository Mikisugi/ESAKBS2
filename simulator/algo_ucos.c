#include <stdio.h>
#include "includes.h"
#include <math.h>

#define UNICODE_ENABLED 0
#define COLORS_ENABLED 0

#define EMPTY 0
#define BLACK 1
#define FRIENDLY 2
#define FRIENDLYKING 3
#define ENEMY 4
#define ENEMYKING 5
#define FRIENDLYDIRECTION -1
#define ENEMYDIRECTION 1

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */
#define TASK1_PRIORITY      1

unsigned char board [10][10];

void printCountPieces(){
	unsigned char enemyCount = 0;
	unsigned char friendlyCount = 0;
	for(unsigned char row = 0; row < 10; row++){
		for(unsigned char field = 0; field < 10; field++){
			if(board[row][field] == FRIENDLY){
				friendlyCount++;
			}else if(board[row][field] == ENEMY){
				enemyCount++;
			}
		}
	}
	
	printf("%s %d%c", "Enemy #", enemyCount, '\n');
	printf("%s %d%c", "Friendly #", friendlyCount, '\n');	
}

void printBoard(unsigned char changedRow, unsigned char changedField, unsigned char oldRow, unsigned char oldField){
	for(unsigned char row = 0; row < 10; row++){
		if(!COLORS_ENABLED) printf("|");
		for(unsigned char o = 0; o < 10; o++){
			if(!COLORS_ENABLED) printf("---|");
		}
		if(!COLORS_ENABLED) printf("\n|");
		for(unsigned char field = 0; field < 10; field++){
			
			if(COLORS_ENABLED){
				switch(board[row][field]){
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
			
			if(COLORS_ENABLED && row == changedRow && field == changedField){	
				printf("\x1b[33m");
			}else if(COLORS_ENABLED && row == oldRow && field == oldField){
				printf("\x1b[33m");
			}
			switch(board[row][field]){
				case BLACK :
					if(COLORS_ENABLED) printf(" ■ ");
					else printf("   ");
					break;
				case FRIENDLY :
					if(UNICODE_ENABLED) printf(" ⛀ ");
					else printf(" F ");
					break;
				case FRIENDLYKING :
					if(UNICODE_ENABLED) printf(" ⛁ ");
					else printf("F K");
					break;
				case ENEMY :
					if(UNICODE_ENABLED) printf(" ⛂ ");
					else printf(" E ");
					break;
				case ENEMYKING :
					if(UNICODE_ENABLED) printf(" ⛃ ");
					else printf("E K");
					break;
				default : 
					printf("   ");
					break;
			}
			if(COLORS_ENABLED) printf("\x1b[0m");
			else printf("|");
		}
		printf("\n");
	}
	if(!COLORS_ENABLED) printf("|");
	for(unsigned char o = 0; o < 10; o++){
		if(!COLORS_ENABLED) printf("---|");
	}
	printf("\n\n\n");
}

unsigned char manCapture(unsigned char row, unsigned char field, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing){
	unsigned char possibleEnemyRow, possibleEnemyField, possibleNewRow, possibleNewField;
	for(signed char rowDirection = -1; rowDirection < 2; rowDirection = rowDirection + 2){
		for(signed char fieldDirection = -1; fieldDirection < 2; fieldDirection = fieldDirection + 2){
			possibleEnemyRow = row + rowDirection;
			possibleEnemyField = field + fieldDirection;
			// Dont check the side for enemies you cant capture them there
			if(possibleEnemyRow > 0 && possibleEnemyRow < 9 && possibleEnemyField > 0 && possibleEnemyField < 9){						
			//	printf("%s %d%c", "enemy in range?", board[possibleEnemyRow][possibleEnemyField] == enemy || board[possibleEnemyRow][possibleEnemyField] == enemyKing, '\n');
				if(board[possibleEnemyRow][possibleEnemyField] == enemy || board[possibleEnemyRow][possibleEnemyField] == enemyKing){
				//	printf("%s %d%c%d%c", "beeb boob enemy detected at",  possibleEnemyRow, '.', possibleEnemyField, '\n');
					possibleNewRow = possibleEnemyRow + rowDirection;
					possibleNewField = possibleEnemyField + fieldDirection;
					if(board[possibleNewRow][possibleNewField] == BLACK){
					//	printf("charge!!!!!!!!!\n");
						board[possibleNewRow][possibleNewField] = board[row][field];
						board[row][field] = BLACK;
						board[possibleEnemyRow][possibleEnemyField] = BLACK;
						printBoard(possibleNewRow, possibleNewField, row, field);	
						printf("%s %d %s %d%c", "old row", row, "old field", field,'\n');
						printf("%s %d %s %d%c", "new row", possibleNewRow, "new field", possibleNewField,'\n');
						printCountPieces();
						manCapture(possibleNewRow, possibleNewField, friendly, friendlyKing, enemy, enemyKing);
						return 1;
					}
				}
			}	
		}	
	}
	return 0;
}

unsigned char manMove(unsigned char row, unsigned field, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed direction){
	signed char possibleNewField;
	signed char possibleNewRow = row + direction;
	
	if(possibleNewRow > -1 && possibleNewRow < 10){
		for(signed char fieldDirection = -1; fieldDirection < 2; fieldDirection = fieldDirection + 2){
			possibleNewField = field + fieldDirection;
		
			if(possibleNewField > -1 && possibleNewField < 10 && board[possibleNewRow][possibleNewField] == BLACK){	
				board[possibleNewRow][possibleNewField] = board[row][field];
				board[row][field] = BLACK;
				printBoard(possibleNewRow, possibleNewField, row, field);	
				return 1;
			}
		}
	}	
	return 0;
}

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
						captured = manCapture(row, field, friendly, friendlyKing, enemy, enemyKing);
					}else{
						moved = manMove(row, field, friendly, friendlyKing, enemy, enemyKing, direction);
					}
					
					if(moved == 1 || captured == 1){
						printf("moved or captured\n");
						return 1;
					}
				}
			}
		}
		if(couldNotCapture == 1 && moved == 0){				
			couldNotMove = 1;
			printf("could not move\n");
		}else if(captured == 0){
			couldNotCapture = 1;
			printf("could not capture\n");
		}
	}
	return 0;
}

void play(){
	unsigned char friendlyMoved = 1;
	unsigned char enemyMoved = 1;
	unsigned char turn = 0;
	unsigned char turnCounter = 0;
	while(friendlyMoved == 1 && enemyMoved == 1){
		if(turn == 0){
			printf("FRIENDLY TURN\n");
			friendlyMoved = algorithm(FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION);
			turn = 1;
		}else{
			printf("ENEMY TURN\n");
			enemyMoved = algorithm(ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION);
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

/* Task 1 is de main van het C algoritme */
void task1(void* pdata)
{
	unsigned char x = 1;
	unsigned char y = 0;
	unsigned char even = 1;
	unsigned char captured = 1; 
	unsigned char moved = 0;
	
	while(y < 10){
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

//	printBoard(100,100,100,100);	
//	printCountPieces();

	play();
	
//	printBoard(100,100,100,100);
//	printCountPieces();
}

/* The main function creates two task and starts multi-tasking */
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
  OSStart();
  return 0;
}

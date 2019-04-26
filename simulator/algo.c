#include <stdio.h>
#include <math.h>

// Print unicode checkers instead of text
#define UNICODE_ENABLED 1
// Draw the board with colors instead of lines
#define COLORS_ENABLED 0

// if 0, computer will play against itself
#define PLAYER_INPUT 0

#define EMPTY 0
#define BLACK 1
#define FRIENDLY 2
#define FRIENDLYKING 3
#define ENEMY 4
#define ENEMYKING 5

#define FRIENDLYDIRECTION -1
#define ENEMYDIRECTION 1

unsigned char board [10][10];

/*
Print the amount of pieces each player has on the board
*/
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
	printf("%s %d%c", "Enemy #", enemyCount, '\n');
	printf("%s %d%c", "Friendly #", friendlyCount, '\n');	
}

/*
Draw the board.

Vars are for coloring changes on the board. Not important if COLORS_ENABLED is 0
changedRow	= The row where the piece has gone
changedField	= The field where the piece has gone
oldRow		= The row where the piece previously was
oldField	= The field where the piece previously was
*/
void printBoard(unsigned char changedRow, unsigned char changedField, unsigned char oldRow, unsigned char oldField){
	
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
			
			//Give changed piece and previous location of that piece a special color
			if(COLORS_ENABLED && row == changedRow && field == changedField){
				printf("\x1b[33m");
			}else if(COLORS_ENABLED && row == oldRow && field == oldField){
				printf("\x1b[33m");
			}
			
			//Draw the item on the board
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
	Capture an enemy with a man
*/
unsigned char manCapture(unsigned char row, 
		unsigned char field, 
		unsigned char friendly,
		unsigned char friendlyKing, 
		unsigned char enemy, 
		unsigned char enemyKing){
	
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

unsigned char algorithm2(unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction){
	
	for(unsigned char row = 0; row < 10; row++){
	
		for(unsigned char field = 0; field < 10; field++){
		
			if(board[row][field] == friendly){
			
				if(checkIfMustCapture(row,field,0)){
				
					manCapture(row,field,friendly,friendlyKing,enemy,enemyKing);
				}else{
				
					
					if(checkIfCanMove(row,field,0)){
					
						//manMove(row,field,friendly,friendlyKing,enemy,enemyKing);
					}else{
					
						//TODO NEXT
					}
				}
			}
		}
	}
}

//TODO: fly
int checkIfMustCapture(int row,int field,int king){
	
	if((board[row-1][field-1] == ENEMY || board[row-1][field-1] == ENEMYKING)
	&&
	(board[row-2][field-2] == BLACK || board[row-2][field-2] == BLACK))
		return 1;
	
	else if((board[row-1][field+1] == ENEMY || board[row-1][field+1] == ENEMYKING)
	&&
	(board[row-2][field+2] == BLACK || board[row-2][field+2] == BLACK))
		return 2;
	
	else if((board[row+1][field-1] == ENEMY || board[row+1][field-1] == ENEMYKING)
	&&
	(board[row+2][field-2] == BLACK || board[row+2][field-2] == BLACK))
		return 3;
	
	else if((board[row+1][field+1] == ENEMY || board[row+1][field+1] == ENEMYKING)
	&&
	(board[row+2][field+2] == BLACK || board[row+2][field+2] == BLACK))
		return 4;
	
	else return 0;
}

int checkIfCanMove(int row,int field,int king,int dir){
	
	if(board[row][field] == FRIENDLY && (dir == 3 || dir == 4)){
		return 0;
	}
	
	switch(dir){
		case 1:
			if(board[row-1][field-1] == BLACK){
				return 1;
			}else return 0;
			break;
		case 2:
			if(board[row-1][field+1] == BLACK){
				return 1;
			}else return 0;
			break;
		case 3:
			if(board[row+1][field-1] == BLACK){
				return 1;
			}else return 0;
			break;
		case 4:
			if(board[row+1][field+1] == BLACK){
				return 1;
			}else return 0;
			break;
	}
}

unsigned char playerInput(){
	
	printf("Row to select: ");
	int pRow = -1;
	scanf("%d", &pRow);
	printf("Field to select: ");
	int pField = -1;
	scanf("%d", &pField);
	
	int stone = board[pRow][pField];
	
	if(stone == FRIENDLY || stone == FRIENDLYKING){
	
		int isKing;
		if(stone == FRIENDLYKING) isKing = 1;
		else isKing = 0;
		
		int mustMove = 0;
		
		int printB = 1;
		switch(checkIfMustCapture(pRow,pField,isKing)){
			case 0:
				printB = 0;
				break;
			case 1:
				board[pRow-2][pField-2] = stone;
				board[pRow-1][pField-1] = BLACK;
				printBoard(pRow-2,pField-2,pRow,pField);
				break;
			case 2:
				board[pRow-2][pField+2] = stone;
				board[pRow-1][pField+1] = BLACK;
				printBoard(pRow-2,pField+2,pRow,pField);
				break;
			case 3:
				board[pRow+2][pField-2] = stone;
				board[pRow+1][pField-1] = BLACK;
				printBoard(pRow+2,pField-2,pRow,pField);
				break;
			case 4:
				board[pRow+2][pField+2] = stone;
				board[pRow+1][pField+1] = BLACK;
				printBoard(pRow+2,pField+2,pRow,pField);
				break;
		}
		
		//wordt bij 1 2 3 en 4 gedaan, niet bij 0
		if(printB){
			board[pRow][pField] = BLACK;
			return 1;
		}
		
		printf("\n1   2\n");
		printf(" \\ /\n");
		printf("  x\n");
		printf(" / \\ \n");
		printf("3   4\n\n");
		
		printf("Select a direction: ");
		int pDir = -1;
		scanf("%i", &pDir);
		printf("\n");
		
		if(checkIfCanMove(pRow,pField,isKing,pDir)){
					
			board[pRow][pField] = BLACK;
			switch(pDir){
				case 1:
					board[pRow-1][pField-1] = FRIENDLY;
					printBoard(pRow-1,pField-1,pRow,pField);
					break;
				case 2:
					board[pRow-1][pField+1] = FRIENDLY;
					printBoard(pRow-1,pField+1,pRow,pField);
					break;
				case 3:
					board[pRow+1][pField-1] = FRIENDLY;
					printBoard(pRow+1,pField-1,pRow,pField);
					break;
				case 4:
					board[pRow+1][pField+1] = FRIENDLY;
					printBoard(pRow+1,pField+1,pRow,pField);
					break;
			}
			return 1;
		}else{
			printf("Can't move to that field! Try again.\n");
				return playerInput();
		}			
	}else{
		printf("Wrong piece selected, try again");
		return playerInput();
	}
}

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
				friendlyMoved = algorithm(FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION);
			}
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

void createBoard(){
	unsigned char x = 1;
	unsigned char y = 0;
	unsigned char even = 1;
	
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
}

int main(){
//	printBoard(100,100,100,100);
//	printCountPieces();

	createBoard();
	
	printBoard(100,100,100,100);

	play();
	
//	printBoard(100,100,100,100);
//	printCountPieces();	
	return 0;
}	

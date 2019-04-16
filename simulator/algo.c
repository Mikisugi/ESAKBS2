#include <math.h>
#include <stdio.h>

#define empty 0
#define black 1
#define friendly 2
#define friendlyKing 3
#define enemy 4
#define enemyKing 5


unsigned char board [10][10];


void algorithm(){
	unsigned char possibleEnemyRow, possibleEnemyField, possibleNewRow, possibleNewField, captured;
	for(unsigned char row = 0; row < 10; row++){
	//	printf("friest for\n");
		for(unsigned char field = 0; field < 10; field++){
			captured = 0;
		//	printf("friendly check\n");
			// piece check if a piece can capture
			if(board[row][field] == friendly){
			//	printf("friendly\n");
				// check front left
				for(signed char rowDirection = -1; rowDirection < 2; rowDirection = rowDirection + 2){
					for(signed char fieldDirection = -1; fieldDirection < 2; fieldDirection = fieldDirection + 2){
						possibleEnemyRow = row + rowDirection;
						possibleEnemyField = field + fieldDirection;
						// Dont check the side for enemies you cant capture them there
						if(possibleEnemyRow > 0 && possibleEnemyRow < 99 && possibleEnemyField > 0 && possibleEnemyRow < 99){						
						//	printf("%s %d%c", "enemy in range?", board[possibleEnemyRow][possibleEnemyField] == enemy || board[possibleEnemyRow][possibleEnemyField] == enemyKing, '\n');
							if(board[possibleEnemyRow][possibleEnemyField] == enemy || board[possibleEnemyRow][possibleEnemyField] == enemyKing){
							//	printf("%s %d%c%d%c", "beeb boob enemy detected at",  possibleEnemyRow, '.', possibleEnemyField, '\n');
								possibleNewRow = possibleEnemyRow + rowDirection;
								possibleNewField = possibleEnemyField + fieldDirection;
								if(board[possibleNewRow][possibleNewField] == black){
								//	printf("charge!!!!!!!!!\n");
									board[possibleNewRow][possibleNewField] = board[row][field];
									board[row][field] = black;
									board[possibleEnemyRow][possibleEnemyField] = black;
									printBoard(possibleNewRow, possibleNewField, row, field);	
									printf("%s %d %s %d%c", "old row", row, "old field", field,'\n');
									printf("%s %d %s %d%c", "new row", possibleNewRow, "new field", possibleNewField,'\n');
									printCountPieces();
									captured = 1;
									break;
								}
							}
						}	
					}
					if(captured == 1){
						break;
					}
				}
			}
		}
	}	
}


void printBoard(unsigned char changedRow, unsigned char changedField, unsigned char oldRow, unsigned char oldField){
	for(unsigned char row = 0; row < 10; row++){
		printf("|");
		for(unsigned char o = 0; o < 10; o++){
			printf("--|");
		}
		printf("\n|");
		for(unsigned char field = 0; field < 10; field++){
			if(row == changedRow && field == changedField){	
				printf("\x1b[31m");
			}else if(row == oldRow && field == oldField){
				printf("\x1b[35m");
			}
			switch(board[row][field]){
				case black :
					printf("■■");
					break;
				case friendly :
					printf("F ");
					break;
				case friendlyKing :
					printf("FK");
					break;
				case enemy :
					printf("E ");
					break;
				case enemyKing :
					printf("EK");
					break;
				default : 
					printf("  ");
					break;
			}
			printf("\x1b[0m");
			printf("|");
		}
		printf("\n");
	}
	printf("|");
	for(unsigned char o = 0; o < 10; o++){
		printf("--|");
	}
	printf("\n\n\n");

}


void printCountPieces(){
	unsigned char enemyCount = 0;
	unsigned char friendlyCount = 0;
	for(unsigned char row = 0; row < 10; row++){
		for(unsigned char field = 0; field < 10; field++){
			if(board[row][field] == friendly){
				friendlyCount++;
			}else if(board[row][field] == enemy){
				enemyCount++;
			}
		}
	}
	
	printf("%s %d%c", "Enemy #", enemyCount, '\n');
	printf("%s %d%c", "Friendly #", friendlyCount, '\n');	
}

int main(){
	unsigned char x = 1;
	unsigned char y = 0;
	unsigned char even = 1;
	while(y < 10){
		board[y][x] = black;
		if(y < 4){
			board[y][x] = enemy;
		}
		if(y > 5){		
			board[y][x] = friendly;
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
	board[1][2] = friendly;
	board[2][3] = friendly;
	board[2][5] = friendly;
	board[0][3] = black;
	board[5][4] = enemy;
	board[5][8] = enemy;
	board[4][5] = friendly;

	printBoard(100,100,100,100);	
	printCountPieces();

	algorithm();

	printBoard(100,100,100,100);
	printCountPieces();
	return 0;
}	

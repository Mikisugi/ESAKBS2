#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "constants.h"
#include "vector.h"

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
void printBoard(unsigned char * tempBoard[], unsigned char changedRow, unsigned char changedField, unsigned char oldRow, unsigned char oldField){

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

int checkIfGetsHit(){

	
}

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
						printBoard((unsigned char **)board,possibleNewRow, possibleNewField, row, field);	
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
				printBoard((unsigned char **)board,possibleNewRow, possibleNewField, row, field);	
				return 1;
			}
		}
	}	
	return 0;
}


//TODO: fly
int capture(int row,int field,int king){
	
	if((board[row-1][field-1] == ENEMY || board[row-1][field-1] == ENEMYKING)
	&&
	(board[row-2][field-2] == BLACK || board[row-2][field-2] == BLACK)){
	
		board[row-2][field-2] = board[row][field];
		board[row-1][field-1] = BLACK;
		board[row][field] = BLACK;
		printBoard((unsigned char **)board,row-2,field-2,row,field);
		return 1;
	}
	
	else if((board[row-1][field+1] == ENEMY || board[row-1][field+1] == ENEMYKING)
	&&
	(board[row-2][field+2] == BLACK || board[row-2][field+2] == BLACK)){
	
		board[row-2][field+2] = board[row][field];
		board[row-1][field+1] = BLACK;
		board[row][field] = BLACK;
		printBoard((unsigned char **)board,row-2,field+2,row,field);
		return 1;
	}
		
	else if((board[row+1][field-1] == ENEMY || board[row+1][field-1] == ENEMYKING)
	&&
	(board[row+2][field-2] == BLACK || board[row+2][field-2] == BLACK)){
		
		board[row+2][field-2] = board[row][field];
		board[row+1][field-1] = BLACK;
		board[row][field] = BLACK;
		printBoard((unsigned char **)board,row+2,field-2,row,field);
		return 1;
	}
	
	else if((board[row+1][field+1] == ENEMY || board[row+1][field+1] == ENEMYKING)
	&&
	(board[row+2][field+2] == BLACK || board[row+2][field+2] == BLACK)){
		
		board[row+2][field+2] = board[row][field];
		board[row+1][field+1] = BLACK;
		board[row][field] = BLACK;
		printBoard((unsigned char **)board,row+2,field+2,row,field);
		return 1;
	}
	
	else return 0;
}

int checkIfCanMove(unsigned char * tempBoard[], int row,int field,int king,int dir){

	unsigned char b[10][10];
	memcpy(b,tempBoard,100);
	
	//TODO direction
	if(b[row][field] == FRIENDLY && (dir == 3 || dir == 4)){
		return 0;
	}
	
	switch(dir){
		case 1:
			if(b[row-1][field-1] == BLACK){
				return 1;
			}else return 0;
			break;
		case 2:
			if(b[row-1][field+1] == BLACK){
				return 1;
			}else return 0;
			break;
		case 3:
			if(b[row+1][field-1] == BLACK){
				return 1;
			}else return 0;
			break;
		case 4:
			if(b[row+1][field+1] == BLACK){
				return 1;
			}else return 0;
			break;
	}
	return 1;
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

void move(unsigned char * tempBoard[], unsigned char row, unsigned char field, unsigned char dir, unsigned char isKing, unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction){

	unsigned char b[10][10];
	memcpy(b,tempBoard,100);
	
	b[row][field] = BLACK;
	
	int stone = -1;
	if(isKing) stone = friendlyKing;
	else stone = friendly;

	switch(dir){
		case 1:
			b[row-1][field-1] = stone;
			break;
		case 2:
			b[row-1][field+1] = stone;
			break;
		case 3:
			b[row+1][field-1] = stone;
			break;
		case 4:
			b[row+1][field+1] = stone;
			break;
	}
	printBoard((unsigned char **)b,100,100,100,100);
	memcpy(tempBoard,b,100);
}

typedef struct move_
{
	double score;
	unsigned char row;
	unsigned char field;
	unsigned char dir;
} Move;

Move minimaxAlgorithmRecursive(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction, int depth)
{
	unsigned char b[10][10];
	memcpy(b,tempBoard,100);
	
	Move best;
	best.score = 0;
	
	if(depth > 0)
	{
		for(unsigned char row = 0; row < 10; row++)
		{
			for(unsigned char field = 0; field < 10; field++)
			{
				if(b[row][field] == friendly)
				{
					if(direction == -1)
					{
						if(checkIfCanMove((unsigned char **)b,row,field,0,1) == 1)
						{
							unsigned char newBoard[10][10];
							memcpy(newBoard,b,100);
							move((unsigned char **)newBoard, row, field, 1, 0, friendly, friendlyKing, enemy, enemyKing, direction);
							Move s = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, 1, depth-1);
							if(best.score < s.score)
							{
								best = s;
								printf("New score %d is better than best score %d, overwriting\n",s.score,best.score);
							}
						}
						if(checkIfCanMove((unsigned char **)b,row,field,0,2) == 1)
						{
							unsigned char newBoard[10][10];
							memcpy(newBoard,b,100);
							move((unsigned char **)newBoard, row, field, 2, 0, friendly, friendlyKing, enemy, enemyKing, direction);
							Move s = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, 1, depth-1);
							if(best.score < s.score)
							{
								best = s;
								printf("New score %d is better than best score %d, overwriting\n",s.score,best.score);
							}
						}
					}
					else if(direction == 1)
					{
						if(checkIfCanMove((unsigned char **)b,row,field,0,3) == 1)
						{
							unsigned char newBoard[10][10];
							memcpy(newBoard,b,100);
							move((unsigned char **)newBoard, row, field, 3, 0, friendly, friendlyKing, enemy, enemyKing, direction);
							Move s = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, -1, depth-1);
							if(best.score > s.score)
							{
								best = s;
								printf("New score %d is better than best score %d, overwriting\n",s.score,best.score);
							}
						}
						if(checkIfCanMove((unsigned char **)b,row,field,0,4) == 1)
						{
							unsigned char newBoard[10][10];
							memcpy(newBoard,b,100);
							move((unsigned char **)newBoard, row, field, 4, 0, friendly, friendlyKing, enemy, enemyKing, direction);
							Move s = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, -1, depth-1);
							if(best.score > s.score)
							{
								best = s;
								printf("New score %d is better than best score %d, overwriting\n",s.score,best.score);
							}
						}
					}
				}
				else if(b[row][field] == friendlyKing)
				{
					//TODO: kingMove
				}
			}
		}
	}
	else
	{
		//calculate score to return
		for(unsigned char row = 0;row<10;row++)
		{
			for(unsigned char field = 0;field<10;field++)
			{
				if(b[row][field] == friendly)		best.score = best.score + row;
				else if(b[row][field] == friendlyKing)	best.score = best.score + 5*row;
				else if(b[row][field] == enemy)		best.score = best.score - (10-row);
				else if(b[row][field] == enemyKing)	best.score = best.score - (10-5*row);
			}
		}
	}
	
	for(int i = depth; i>0; i--) printf("\t");
	printf("best.score = %d\n",best.score);
	for(int i = depth; i>0; i--) printf("\t");
	printf("best.row = %d\n",best.row);
	for(int i = depth; i>0; i--) printf("\t");
	printf("best.field = %d\n",best.field);
	for(int i = depth; i>0; i--) printf("\t");
	printf("best.dir = %d\n",best.dir);
	
	return best;
}

int minimaxAlgorithm(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction, int depth)
{
	Move best = minimaxAlgorithmRecursive((unsigned char **)tempBoard, friendly, friendlyKing, enemy, enemyKing, direction, depth);
	
	//Make the move
	int isKing;
	if(board[best.row][best.field] == friendlyKing) isKing = 1;
	else isKing = 0;
	
	//TODO: Check if there is actually a move to be made and the game isn't over
	
	move((unsigned char **)board, best.row, best.field, best.dir, isKing, friendly, friendlyKing, enemy, enemyKing, direction);
	printBoard((unsigned char **)board,best.row,best.field,100,100);
	return 1;
}

/*
unsigned char bfAlgorithm(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction){

	//TODO: Go past every item in the singly linked list and predict every future scenario. Positive futures means a high score for the initial move
	//TODO: singly linked list with moves, not items
	
	typedef struct node {
		struct node * next;
		int row;
		int field;
		int dir;
		int score;
	} node_t;
	
	
	node_t * head = NULL;
	head = malloc(sizeof(node_t));
	
	node_t * current = head;
	
	for(unsigned char row = 0; row < 10; row++){

		for(unsigned char field = 0; field < 10; field++){
		
			if(tempBoard[row][field] == friendly || tempBoard[row][field] == friendlyKing){
				
				//TODO: Don't use capture(), it's made for blacks only. use manCapture & kingCapture when finished
				//if(capture(row,field,0)){
				//	
				//	printf("Captured\n");
				//	return 1;
				//}else{
					if(checkIfCanMove((unsigned char **)tempBoard,row,field,0,3) == 1){
					
						current = head;
						while (current->next != NULL)
							current = current->next;
						
						current->next = malloc(sizeof(node_t));
						current->next->row = row;
						current->next->field = field;
						current->next->dir = 3;
						current->next->score = 0;
						current->next->next = NULL;
					}
					if(checkIfCanMove((unsigned char **)tempBoard,row,field,0,4) == 1){
					
						current = head;
						while (current->next != NULL)
							current = current->next;
						
						current->next = malloc(sizeof(node_t));
						current->next->row = row;
						current->next->field = field;
						current->next->dir = 4;
						current->next->score = 0;
						current->next->next = NULL;
					}
				//}
			}
		}
	}
	
	//TODO go through linked list, make tempBoards out of them and check their value, then call bfAlgorithm
	current = head;
	unsigned char newBoard[10][10];
	newBoard = tempBoard;
	
	while (current->next != NULL){
	
		//Make the move in current
		unsigned char isKing = -1;
		if(newBoard[current->row][current->field] == friendly) isKing = 0;
		else if(newBoard[current->row][current->field] == friendlyKing) isKing = 1;
		else printf("ERROR: Stone is not friendly or friendlyKing");
		
		move((unsigned char **)newBoard, current->row, current->field, current->dir, isKing, friendly, friendlyKing, enemy, enemyKing, current->direction);
		
		//Calculate the board's value
		for(unsigned char row = 0;row<10;row++){
			for(unsigned char field = 0;field<10;field++){
				switch(newBoard[row][field]){
					//friendly
					case 2:
						current->score = current->score + 1;
						break;
					//friendlyKing
					case 3:
						current->score = current->score + 5;
						break;
					//enemy
					case 4:
						current->score = current->score - 2;
						break;
					//enemyKing
					case 5:
						current->score = current->score - 6;
						break;
				}
			}
		}
		
		//call bfAlgorithm recursively
		bfAlgorithm((unsigned char **)newBoard, friendly, friendlyKing, enemy, enemyKing, direction);
		
		//bfAlgorithm should return the node with the highest score
		
		
		current = current->next;
	}
	
	/*
	// Print the linked list
	current = head;
	while (current != NULL) {
		printf("Item:\n\tRow: %d\n\tField: %d\n\tScore: %d\n\n", 
			current->row,current->field,current->score);
		current = current->next;
	}
	*
	
	free(head);
	
	return 1;
}
*/

unsigned char playerInput(){

	for(int row = 0; row < 10; row++){
	
		for(int field = 0; field < 10; field++){
		
			if(board[row][field] == FRIENDLY){
			
				if(capture(row,field,0)) return 1;
			}
			else if(board[row][field] == FRIENDLYKING){
			
				if(capture(row,field,1)) return 1;
			}
		}
	}
	
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
		
		if(checkIfCanMove((unsigned char **)board,pRow,pField,isKing,pDir)){
			move((unsigned char **)board,pRow,pField,pDir,isKing, FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION);
			return 1;
		}else{
			printf("Can't move to that field! Try again.\n");
			return playerInput();
		}
		
		////int asdf = 1;
		//int asdf = checkIfCanMove((unsigned char **)board,pRow,pField,isKing,pDir);
		//printf("%d\n",asdf);
		//return 1;
	}else{
		printf("Wrong piece selected, try again\n");
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
				//friendlyMoved = bfAlgorithm(FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION);
				friendlyMoved = minimaxAlgorithm((unsigned char **)board,FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION,2);
				//friendlyMoved = 1;
				//friendlyMoved = algorithm(FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION);
			}
			turn = 1;
		}else{
			printf("ENEMY TURN\n");
			//enemyMoved = bfAlgorithm(ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION);
			enemyMoved = minimaxAlgorithm((unsigned char **)board,ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION,2);
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

void createBoard(){
	unsigned char x = 1;
	unsigned char y = 0;
	unsigned char even = 1;
	
	while(y < 10){
		board[y][x] = BLACK;
		if(y < 4){
		//	board[y][x] = ENEMY;
		}
		if(y > 5){		
		//	board[y][x] = FRIENDLY;
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
//	printBoard((unsigned char **)board,100,100,100,100);
//	printCountPieces();

	/*
	createBoard();
	board[8][7] = ENEMY;
	board[6][5] = FRIENDLYKING;
	board[5][4] = ENEMY;
	board[5][2] = ENEMY;
	board[2][5] = ENEMY;

/*	Vector testVector;
	vectorInit(&testVector);
	Capture capture;
	vectorAdd(&testVector, (void*)&capture);
*/
	printBoard((unsigned char **)board,100,100,100,100);
	
	Location location;
	location.row = 6;
	location.field = 5;
	Vector *vector;
	printf("test");
	vector = kingCapture(location,board ,FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING);
	printf("test");
//	stripKingCapture(vector, 0);	
//	printVector(&vector);

//	vector->size;


	createBoard();
	printBoard((unsigned char **)board,100,100,100,100);
	play();
	
//	printBoard((unsigned char **)board,100,100,100,100);
//	printCountPieces();	
	return 0;
}


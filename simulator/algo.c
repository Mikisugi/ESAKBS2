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
	for(unsigned char row = 0; row < 10; row++)
	{
		for(unsigned char field = 0; field < 10; field++)
		{
			//If the field has a friendly man or king on it, add to the friendly counter
			if(board[row][field] == FRIENDLY || board[row][field] == FRIENDLYKING)
			{
				friendlyCount++;
			}
			
			//If the field has an enemy man or king on it, add to the enemy counter
			else if(board[row][field] == ENEMY || board[row][field] == ENEMYKING)
			{
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

Vector * kingCapture(Location currentLocation, unsigned char * tempBoard [], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing){
	#if DEBUG
		printf("begin king capture\n");
	#endif
	
	unsigned char b[10][10];
	memcpy(b,tempBoard,100);
	
	Vector *captureVector = vectorInit();
	Location possibleEnemy, possibleLanding;
	for(signed char rowDirection = -1; rowDirection < 2; rowDirection = rowDirection + 2){
		for(signed char fieldDirection = -1; fieldDirection < 2; fieldDirection = fieldDirection + 2){
			#if DEBUG
				printf("Row direction: %d, Field Direction: %d\n", rowDirection, fieldDirection);
			#endif
			possibleEnemy.row = currentLocation.row;
			possibleEnemy.field = currentLocation.field;
			while(possibleEnemy.row + rowDirection > 0 && possibleEnemy.row + rowDirection < 9 && possibleEnemy.field + fieldDirection > 0 && possibleEnemy.field + fieldDirection < 9){
				possibleEnemy.row += rowDirection;
				possibleEnemy.field += fieldDirection;
				#if DEBUG
					printf("possible enemy row: %d, possible enemy field: %d\n", possibleEnemy.row, possibleEnemy.field);
				#endif
				if(b[possibleEnemy.row][possibleEnemy.field] == enemy || b[possibleEnemy.row][possibleEnemy.field] == enemyKing){
					#if DEBUG
						printf("beeb boop enemy detected\n");
					#endif
					possibleLanding.row = possibleEnemy.row;
					possibleLanding.field = possibleEnemy.field;
					
					unsigned char i = 0;
					while(possibleLanding.row + rowDirection > -1 && possibleLanding.row + rowDirection < 10 && possibleLanding.field + fieldDirection > -1 && possibleLanding.field + fieldDirection < 10){
						possibleLanding.row += rowDirection;
						possibleLanding.field += fieldDirection;
						if(b[possibleLanding.row][possibleLanding.field] == BLACK){
							#if DEBUG
								printf("LANDINGMAYDAYMAYDAY %d \n", i);
							#endif
							i++;	
						
							#if DEBUG
								printf("LandROW : %d\n LandField: %d\n\n", possibleLanding.row, possibleLanding.field);
							#endif
							VectorCapture *capture = malloc(sizeof(VectorCapture)) ;
							capture->oldLocation = currentLocation;
							capture->captureLocation = possibleEnemy;
							capture->newLocation = possibleLanding;
							capture->piece = b[possibleEnemy.row][possibleEnemy.field];
							b[currentLocation.row][currentLocation.field] = BLACK;
							b[possibleLanding.row][possibleLanding.field] = friendlyKing;
							b[possibleEnemy.row][possibleEnemy.field] = BLACK;

							capture->nextCaptures = kingCapture(possibleLanding, (unsigned char **)b, friendly, friendlyKing, enemy, enemyKing);
							#if DEBUG
								printf("add stuff to vector\n");
							#endif
							vectorAdd(captureVector, (void*)capture);

							#if DEBUG
								printf("restore board\n");
							#endif
							b[currentLocation.row][currentLocation.field] = friendlyKing;
							b[possibleLanding.row][possibleLanding.field] = BLACK;
							b[possibleEnemy.row][possibleEnemy.field] = capture->piece;
						}
					}
					break;	
				}
			}
	
		}
	}		
	return captureVector;
}

void deleteCaptureVector(VectorCapture *capture){
	if(capture->nextCaptures != NULL){
		Vector * vector = capture->nextCaptures; 
		for(unsigned char i = 0; i < vector->count; i++){
			if(vector->data[i] != NULL){
				deleteCaptureVector(vector->data[i]);
			}
		}
		vectorFree(vector);
	}
	free(capture);
}

void deleteMoveVector(Vector * vector){
	for(unsigned char i = 0; i < vector->count; i++){
		struct Move * moveList = (struct Move *) vector->data[i];
		struct Move * nextMoveList;
		while(moveList != NULL){
			nextMoveList = moveList->nextMove;
			free(moveList);
			moveList = nextMoveList;
		}
	}
	free(vector);
}

unsigned char stripCaptureVector(Vector *vector, unsigned char count){
	unsigned char oldCount = 0;
	count++;
	if(vector->count == 0){
		#if DEBUG
			printf("Vector 0\n");
		#endif
		vectorFree(vector);
		oldCount = count;
	}else{
		for(unsigned char i = 0; i < vector->count; i++){
			#if DEBUG
				printf("count === %d\n", count);
			#endif
			if(vector->data[i] != NULL){
				VectorCapture *capture = ((VectorCapture *)vector->data[i]);
				if(capture->nextCaptures != NULL){
					#if DEBUG
						printf("Next captures != NULL\n");
						printf("Vector count != 0\n");
					#endif
					unsigned char newCount = stripCaptureVector(capture->nextCaptures, count);
					#if DEBUG
						printf("Oldcount: %i\n Newcount: %i\n I: %i\n", oldCount ,newCount, i);
					#endif
					if(oldCount < newCount){
						for(signed char delI = i-1; delI >= 0; delI--){
							#if DEBUG
								printf("Deleting prevous items\n");
							#endif
							if(vector->data[delI] != NULL){
								deleteCaptureVector(vector->data[delI]);
								vector->data[delI] = NULL;		
							}
						}
						oldCount = newCount;
					}else if(oldCount > newCount){
						if(vector->data[i] != NULL){
							#if DEBUG
								printf("deleting current item\n");
							#endif
							// delete recursive
							deleteCaptureVector(vector->data[i]);
							vector->data[i] = NULL;
						}
					}
				}
			}
		}

	}	
	return oldCount;
}


void initMoveList(VectorCapture * capture, struct Move * newMove){
	newMove->oldLocation = capture->oldLocation;
	newMove->newLocation = capture->newLocation;
	newMove->nextMove = NULL;

	newMove->capture.piece = capture->piece;
	newMove->capture.captureLocation = capture->captureLocation;
}

void addToMoveList(struct Move * newMove, struct Move * origin){	
	printf("add move list loop\n");
	while(origin->nextMove){
		origin = origin->nextMove;
	}
	printf("found it\n");
	
	origin->nextMove = newMove;
}

void copyMoveList(struct Move * originalOrigin, struct Move * newOrigin, unsigned char depth){
	while(depth > 0){
		depth = depth - 1;
		newOrigin->oldLocation = originalOrigin->oldLocation;
		newOrigin->newLocation = originalOrigin->newLocation;
		newOrigin->capture = originalOrigin->capture;

		if(originalOrigin->nextMove != NULL){
			newOrigin->nextMove = malloc(sizeof(struct Move));
			newOrigin = newOrigin->nextMove;
			originalOrigin = originalOrigin->nextMove;
		}		
	}

}

unsigned char countMoveList(struct Move * moveList)
{
	unsigned char counter = 0;
	while(moveList != NULL){
		counter++;
		moveList = moveList->nextMove;
	}
	return counter;
}

void generateCaptureList(Vector* captureVector, struct Move * moveList, Vector * moveVector, unsigned char depth){
	depth++;
	for(unsigned char i = 0; i < captureVector->count; i++){
		if(captureVector->data[i] != NULL){
			printf("kaasten\n");
			VectorCapture * capture = (VectorCapture *)captureVector->data[i];
			struct Move * newMove = malloc(sizeof(struct Move));
			printf("add to move list\n");
			initMoveList(capture, newMove);
			if(moveList == NULL){
				printf("NEW LIST\n");
				moveList = newMove;
			}else{
				addToMoveList(newMove, moveList);
			}
			
			if(capture->nextCaptures == NULL || capture->nextCaptures->count == 0){
				#if DEBUG
					printf("add\n");
					printf("malloccing vectorMove\n");
				#endif
				#if DEBUG
					printf("mallocced vectorMove\n");
				#endif
				printf("starting copy\n");

				vectorAdd(moveVector, (void *)moveList);
				#if DEBUG
					printf("moves added\n");
				#endif
				
			}else{
				printf("Of ANDERS\n");
				struct Move * newMoveList; 
				if(countMoveList(moveList) - 2 == depth){
					printf("DIT\n");
					newMoveList = malloc(sizeof(struct Move));
					printf("its the evil wizard again\n");
					copyMoveList(moveList, newMoveList, depth);
				}else{
					printf("DAT\n");
					newMoveList = moveList;
				}
				generateCaptureList(capture->nextCaptures, newMoveList, moveVector, depth);
			}
		}
	}		
}

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
		switch(dir)
		{
			case 1:
				if(b[row-1][field-1] == BLACK) retVal = 1;
				break;
			case 2:
				if(b[row-1][field+1] == BLACK) retVal = 1;
				break;
			case 3:
				if(b[row+1][field-1] == BLACK) retVal = 1;
				break;
			case 4:
				if(b[row+1][field+1] == BLACK) retVal = 1;
				break;
		}
	}
	
	return retVal;
}

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

void createKing(unsigned char * tempBoard[])
{
	unsigned char b[10][10];
	memcpy(b,tempBoard,100);
	
	for(unsigned char field = 0; field <= 9; field++)
	{
		if(b[0][field] == FRIENDLY)
		{
			b[0][field] = FRIENDLYKING;
		}
		
		if(b[9][field] == ENEMY)
		{
			b[9][field] = ENEMYKING;
		}
	}
	
	memcpy(tempBoard,b,100);
}

int minimaxAlgorithmRecursive(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction, int depth)
{
	int bestScore;
	
	createKing((unsigned char **)tempBoard);
	
	unsigned char b[10][10];
	memcpy(b,tempBoard,100);
	
	if(depth > 0)
	{
		Vector * scoreList = vectorInit();

		for(unsigned char row = 0; row < 10; row++)
		{
			for(unsigned char field = 0; field < 10; field++)
			{
				if(b[row][field] == friendly)
				{
					#if DEBUG
						printf("R%i: [%i][%i] is friendly\n",depth,row,field);
					#endif
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
									enemiesLeft = 1;
							}
						}
						int score;
						if(enemiesLeft == 1)
						{
							#if DEBUG
								printf("R%i: there are enemies left after the capture\n",depth);
								printf("R%i: calling minimaxAlgorithmRecursive with depth %i\n",depth,depth-1);
							#endif
							score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);
						}
						else if(enemiesLeft == 0)
						{
							#if DEBUG
								printf("R%i: there are no enemies left after the capture\n",depth);
								printf("R%i: calling minimaxAlgorithmRecursive with depth 0\n",depth);
							#endif
							//TODO should i do this? this is a dirty fix for when after a capture, the same stone is used twice.
							score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, 0);
						}
						
						#if DEBUG
							printf("R%i: manCapture: adding score %i to linked list\n",depth,score);
						#endif
						vectorAdd(scoreList,(void *)score);
						//push((node_t **)head,score);
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
								printf("R%i: manMove: adding score %i to linked list\n",depth,score);
							#endif
							vectorAdd(scoreList,(void *)score);
						}
					}
				}
				else if(b[row][field] == friendlyKing)
				{
					int nextDirection;
					if(direction == FRIENDLYDIRECTION) nextDirection = ENEMYDIRECTION;
					if(direction == ENEMYDIRECTION) nextDirection = FRIENDLYDIRECTION;
					
					Location l;
					l.row = row;
					l.field = field;
					Vector * captures = kingCapture(l,(unsigned char **)tempBoard, friendly, friendlyKing, enemy, enemyKing);				
					
					if(captures->count != 0)
					{
						#if DEBUG
							printf("R%i: [%i][%i] can capture\n",depth,row,field);
						#endif
						
						stripCaptureVector(captures, 0);
						
						struct Move * moveList = malloc(sizeof(struct Move));	
						moveList->nextMove = NULL;
						Vector * moveVector = malloc(sizeof(Vector));
						moveVector = vectorInit();
						generateCaptureList(captures, moveList, moveVector, -1);
						deleteMoveVector(moveVector);
						
						//for every S in V
						//TODO segfault if we do this multiple times
						printf("moveVector->count = %i\n",moveVector->count);
						for(int i = 0; i < moveVector->count; i++)
						{
							unsigned char newBoard[10][10];
							//copyBoard(((VectorMove *)vectorGet(moveVector,i))->board,newBoard);
							
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
								printf("R%i: enemiesLeft: %i\n",depth,enemiesLeft);
							#endif
							
							int score;
							if(enemiesLeft == 1)
							{
								#if DEBUG
									printf("R%i: there are enemies left",depth);
								#endif
								score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);	
							}
							else if(enemiesLeft == 0)
							{
								#if DEBUG
									printf("R%i: kingCapture: there are no enemies left\n",depth);
								#endif
								// if there are no enemies left
								score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, 0);
							}
							#if DEBUG
								printf("R%i: kingCapture: adding score %i to list\n",depth,score);
							#endif
							vectorAdd(scoreList,(void *)score);
							
							#if DEBUG
								printf("R%i: done %i\n",depth,i);
							#endif
						}
					}
				
					for(int d = 1;d<=4;d++)
					{
						if(checkIfCanMove((unsigned char **)b, row, field, d, friendly, friendlyKing, enemy, enemyKing, direction) == 1)
						{
							#if DEBUG
								printf("R%i: [%i][%i] dir %i can move\n",depth,row,field,d);
							#endif
							unsigned char newBoard[10][10];
							memcpy(newBoard,b,100);
							move((unsigned char **)newBoard, row, field, d, friendly, friendlyKing, enemy, enemyKing, direction);
							int score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);	
							#if DEBUG
								printf("R%i: kingMove: adding score %i to linked list\n",depth,score);
							#endif
							vectorAdd(scoreList,(void *)score);
							//push((node_t **)head,score);
						}
					}
				}
			}
		}
		
		if(direction == FRIENDLYDIRECTION) bestScore = -1000;
		else bestScore = 1000;
		
		for(int count = 0; count < vectorCount(scoreList);count++)
		{
			int thisScore = (int)vectorGet(scoreList,count);
			#if DEBUG
				printf("thisScore: %i\n",thisScore);
			#endif
			if(direction == FRIENDLYDIRECTION && thisScore > bestScore)
			{
				#if DEBUG
					printf("score %i is bigger than best score %i, overwriting\n",thisScore,bestScore);
				#endif
				bestScore = thisScore;
			}
			else if(direction == ENEMYDIRECTION && thisScore < bestScore)
			{
				#if DEBUG
					printf("score %i is smaller than best score %i, overwriting\n",thisScore,bestScore);
				#endif
				bestScore = thisScore;
			}
			#if DEBUG
				else
				{
					printf("score %i is not better than best score %i, not overwriting\n",thisScore,bestScore);
				}
			#endif
		}
		
		vectorFree(scoreList);
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
	
	return bestScore;
}

struct nodeMove
{
	int score;
	unsigned char row;
	unsigned char field;
	unsigned char dir;
	unsigned char isCapture;
	struct Move * kingCaptureMoveList;
};

int minimaxAlgorithm(unsigned char * tempBoard[], unsigned char friendly, unsigned char friendlyKing, unsigned char enemy, unsigned char enemyKing, signed char direction, int depth)
{
	createKing((unsigned char **)tempBoard);
	
	unsigned char b[10][10];
	memcpy(b,tempBoard,100);
	
	Vector * scoreList = vectorInit();
	
	int thereAreFriendliesLeft = 0;
	
	for(unsigned char row = 0; row < 10; row++)
	{
		for(unsigned char field = 0; field < 10; field++)
		{
			if(b[row][field] == friendly)
			{
				thereAreFriendliesLeft = 1;
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
					int score;
					if(enemiesLeft == 1)
					{
						#if DEBUG
							printf("S : there are enemies left");
						#endif
						score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);
					}
					else
					{
						#if DEBUG
							printf("S : manCapture: there are no enemies left\n");
						#endif
						// if there are no enemies left
						score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, 0);
					}
					#if DEBUG
						printf("S : manCapture: adding score %i to list\n",score);
					#endif
					
					struct nodeMove * currentMove;
					currentMove->score = score;
					currentMove->row = row;
					currentMove->field = field;
					currentMove->dir = 0;
					currentMove->isCapture = 1;
					vectorAdd(scoreList,(void *)currentMove);
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
							printf("S : manMove: adding score %i to linked list HI\n",score);
						#endif
						
						struct nodeMove * currentMove = malloc(sizeof(struct nodeMove));
						currentMove->score = score;
						currentMove->row = row;
						currentMove->field = field;
						currentMove->dir = d;
						currentMove->isCapture = 0;
						
						#if DEBUG
							printf("S : manMove: calling vectorAdd\n");
						#endif
						
						vectorAdd(scoreList,(void *)currentMove);
						
						#if DEBUG
							printf("S : manMove: added score to list\n");
						#endif
					}
				}
			}
			else if(b[row][field] == friendlyKing)
			{
				thereAreFriendliesLeft = 1;
				int nextDirection;
				if(direction == FRIENDLYDIRECTION) nextDirection = ENEMYDIRECTION;
				if(direction == ENEMYDIRECTION) nextDirection = FRIENDLYDIRECTION;
				
				Location l;
				l.row = row;
				l.field = field;
				Vector * captures = kingCapture(l,(unsigned char **)tempBoard, friendly, friendlyKing, enemy, enemyKing);				
				
				if(captures->count != 0)
				{
					#if DEBUG
						printf("S : [%i][%i] can capture\n",row,field);
					#endif
					
					stripCaptureVector(captures, 0);

					Vector * moveVector = vectorInit();
					generateCaptureList(captures, NULL, moveVector, -1);
					
					#if DEBUG
						printf("moveVector->count: %i\n",moveVector->count);
					#endif
					
					//for every S in V
					for(int i = 0; i < moveVector->count; i++)
					{
						struct Move * moveList = (struct Move *)vectorGet(moveVector,i);
						#if DEBUG
							printf("yes\n");
						#endif
						
						unsigned char newBoard[10][10];
						
						memcpy(newBoard, board, 100);
						while(moveList->nextMove != NULL){
							newBoard[moveList->newLocation.row][moveList->newLocation.field] = board[moveList->oldLocation.row][moveList->oldLocation.field];
							newBoard[moveList->oldLocation.row][moveList->oldLocation.field] = BLACK;
							newBoard[moveList->capture.captureLocation.row][moveList->capture.captureLocation.field] = BLACK;	
							moveList = moveList->nextMove;
						}

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
						
						int score;
						if(enemiesLeft == 1)
						{
							#if DEBUG
								printf("S : there are enemies left\n");
							#endif
							score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, depth-1);
						}
						else
						{
							#if DEBUG
								printf("S : kingCapture: there are no enemies left\n");
							#endif
							// if there are no enemies left
							score = minimaxAlgorithmRecursive((unsigned char **)newBoard, enemy, enemyKing, friendly, friendlyKing, nextDirection, 0);
						}
						#if DEBUG
							printf("S : kingCapture: adding score %i to list\n",score);
						#endif
						
						struct nodeMove * currentMove;
						currentMove->score = score;
						currentMove->row = row;
						currentMove->field = field;
						currentMove->dir = 0;
						currentMove->isCapture = 1;
						currentMove->kingCaptureMoveList = (struct Move *)vectorGet(moveVector,i);
						vectorAdd(scoreList,(void *)currentMove);
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
							printf("S : kingMove: adding score %i to linked list\n",score);
						#endif
						
						struct nodeMove * currentMove;
						currentMove->score = score;
						currentMove->row = row;
						currentMove->field = field;
						currentMove->dir = d;
						currentMove->isCapture = 0;
						vectorAdd(scoreList,(void *)currentMove);
					}
				}
			}
		}
	}
	
	if(!thereAreFriendliesLeft) 
	{
		#if DEBUG
			printf("there are no friendlies left to move, returning 0\n");
		#endif
		return 0;
	}
	
	struct nodeMove bestMove;
	//nodemove_t * bestMove = malloc(sizeof(nodemove_t));
	
	if(direction == FRIENDLYDIRECTION) bestMove.score = -1000;
	else bestMove.score = 1000;
	
	//if there are captures in the list, remove all non-captures
	int thereAreCaptures = 0;
	
	for(int count = 0; count < vectorCount(scoreList); count++)
	{
		if(((struct nodeMove *)vectorGet(scoreList,count))->isCapture == 1) thereAreCaptures = 1;
	}
	
	//stuff to do if there are in fact captures in the list
	if(thereAreCaptures)
	{
		#if DEBUG
			printf("S : it seems like there are captures in this list\n");
		#endif
		
		Vector * cScoreList = vectorInit();
		
		for(int count = 0; count < vectorCount(scoreList); count++)
		{
			struct nodeMove * cNodeMove = ((struct nodeMove *)vectorGet(scoreList,count));
			
			if(cNodeMove->isCapture == 1)
			{
				vectorAdd(cScoreList,(void *)cNodeMove);
			}
		}
		
		//capture vector becomes the normal vector
		scoreList = cScoreList;
		
		vectorFree(cScoreList);
	}
	
	for(int count = 0; count < vectorCount(scoreList); count++)
	{
		struct nodeMove * currentnm = ((struct nodeMove *)vectorGet(scoreList,count));
		
		if(direction == FRIENDLYDIRECTION && currentnm->score > bestMove.score && !(currentnm->row == 0 && currentnm->field == 0))
		{
			#if DEBUG
				printf("S : score %i is bigger than best score %i, overwriting\n",currentnm->score,bestMove.score);
			#endif
			bestMove = * currentnm;
		}
		else if(direction == ENEMYDIRECTION && currentnm->score < bestMove.score && !(currentnm->row == 0 && currentnm->field == 0))
		{
			#if DEBUG
				printf("S : score %i is smaller than best score %i, overwriting\n",currentnm->score,bestMove.score);
			#endif
			bestMove = * currentnm;
		}
		#if DEBUG
			else printf("S : score %i is not better than best score %i, not overwriting\n",currentnm->score,bestMove.score);
		#endif
	}
	
	vectorFree(scoreList);
	
	#if DEBUG
		printf("S : bestMove\nscore: %i\nrow: %i\nfield: %i\ndir: %i\nisCapture: %i\n\n",bestMove.score,bestMove.row,bestMove.field,bestMove.dir,bestMove.isCapture);
	#endif
	
	if(bestMove.isCapture == 1)
	{
		if(board[bestMove.row][bestMove.field] == friendly)
			manCapture((unsigned char **)board, bestMove.row, bestMove.field, friendly, friendlyKing, enemy, enemyKing);
		if(board[bestMove.row][bestMove.field] == friendlyKing)
		{
			//copyBoard(bestMove->kingCaptureVectorMove->board,board);
			//TODO print every move in VectorMove
			//Vector * captured = kingCapture((unsigned char **)board, bestMove->row, bestMove->field, friendly, friendlyKing, enemy, enemyKing);
		}
	}
	else
	{
		move((unsigned char **)board, bestMove.row, bestMove.field, bestMove.dir, friendly, friendlyKing, enemy, enemyKing, direction);
	}
	
	//TODO: make this look prettier?
	printBoard((unsigned char **)board, bestMove.row, bestMove.field,100,100);
	
	return 1;
}

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
	printf("the game lasted for %i turns\n",turnCounter);
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

int main(){
	
/*	printBoard((unsigned char **)board,100,100,100,100);
	printCountPieces();

	
	createEmptyBoard();
	board[8][7] = ENEMY;
	board[6][5] = FRIENDLYKING;
	board[5][4] = ENEMY;
	board[5][2] = ENEMY;
	board[2][5] = ENEMY;
*
	Vector testVector;
	vectorInit(&testVector);
	Capture capture;
	vectorAdd(&testVector, (void*)&capture);
	printBoard((unsigned char **)board, 100,100,100,100);
*
	
	Location location;
	location.row = 6;
	location.field = 5;
	Vector *vector;
	printf("test");
	vector = kingCapture(location,board ,FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING);
	printf("\n\ntestietestietest\n\n");
	stripCaptureVector(vector, 0);
	printVector(vector, 0);

	stripCaptureVector(vector, 0);	
	printf("----------------------------------------------------\nstripped VECTOR DINGES\n----------------------------------------------------\n");
	printVector(vector, 0);

	vector->size;

	Vector * moveVector = vectorInit();	
	generateCaptureList(vector, NULL, moveVector, -1);

	printBoard((unsigned char **)board, 100,100,100,100);
	struct Move * move = (struct Move *)moveVector->data[0];

	unsigned char tempBoard[10][10];
	memcpy(tempBoard, board, sizeof(tempBoard));
	while(move->nextMove != NULL){
		move = move->nextMove;
		tempBoard[move->newLocation.row][move->newLocation.field] = board[move->oldLocation.row][move->oldLocation.field];
		tempBoard[move->oldLocation.row][move->oldLocation.field] = BLACK;
		tempBoard[move->capture.captureLocation.row][move->capture.captureLocation.field] = BLACK;	
	}
	
	
	printBoard((unsigned char **)tempBoard,100,100,100,100);
*
	createEmptyBoard();
	board[6][1] = FRIENDLYKING;
	board[3][6] = ENEMYKING;
	printBoard((unsigned char **)board,100,100,100,100);
	printf("FRIENDLY'S TURN\n");
	minimaxAlgorithm((unsigned char **)board,FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION,6);
	printf("ENEMY'S TURN\n");
	minimaxAlgorithm((unsigned char **)board,ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION,6);
	minimaxAlgorithm((unsigned char **)board,FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION,3);
	minimaxAlgorithm((unsigned char **)board,ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION,3);
	minimaxAlgorithm((unsigned char **)board,FRIENDLY, FRIENDLYKING, ENEMY, ENEMYKING, FRIENDLYDIRECTION,3);
	minimaxAlgorithm((unsigned char **)board,ENEMY, ENEMYKING, FRIENDLY, FRIENDLYKING, ENEMYDIRECTION,3);
	*/	
	createBoard();
	printBoard((unsigned char **)board,100,100,100,100);
	play();	

	printBoard((unsigned char **)board,100,100,100,100);
	return 0;
}

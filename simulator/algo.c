#include <math.h>
#include <stdio.h>

#define empty 0
#define black 1
#define friendly 2
#define friendlyKing 3
#define enemy 4
#define enemyKing 5


unsigned char  board [10][10];

int main(){
	unsigned char x = 0;
	unsigned char y = 0;
	unsigned char even = 0;
	while(y < 10){
		board[y][x] = black;
		if(y < 5){
			board[y][x] = friendly;
		}
		if(y > 6){		
			board[y][x] = enemy;
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
	printBoard();	

	return 0;
}

void printBoard(){
	for(unsigned char i = 0; i < 10; i++){
		printf("|");
		for(unsigned char o = 0; o < 10; o++){
			printf("--|");
		}
		printf("\n|");
		for(unsigned char p = 0; p < 10; p++){
			switch(board[i][p]){
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
			printf("|");
		}
		printf("\n");
	}
	printf("|");
	for(unsigned char o = 0; o < 10; o++){
		printf("--|");
	}
	printf("\n");
}	

//|--|
//|FK|
//|--|


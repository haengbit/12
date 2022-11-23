#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bingoBoard.h"

#define BINGO_RES_UNFINISHED -1 // 아직 안 끝났을 때 리턴값 
#define BINGO_RES_FINISHED 0 // 끝났을 때 리턴값 

// main.c : 게임의 주요 흐름 

// 빙고보드가 조건을 만족시켜서 함수가 종료되었음을 체크 

int check_gameEnd(void)
{
	int res = BINGO_RES_UNFINISHED;
	if (bingo_countCompletedLine() >= N_LINE ) // 핵심 
		res = BINGO_RES_FINISHED; // 끝났음에 해당하는 리턴값 반환 
	return res;
}

int get_number(void) 
{
	int selNum = 0;
	
	do {
		printf("select a number : ");
		scanf("%d", &selNum);
		fflush(stdin);
		if (selNum < 1 || selNum > N_SIZE * N_SIZE || bingo_checkNum(selNum) == BINGO_NUMSTATUS_ABSENT) // if문 조건도 while문 조건과 동일하게 수정! 
		{
			printf("%i is not on the board! select other one.\n", selNum);
		}
	} while (selNum < 1 || selNum > N_SIZE * N_SIZE || bingo_checkNum(selNum) == BINGO_NUMSTATUS_ABSENT);
	
	return selNum;
}

int main(int argc, char *argv[]) {
	
	int selNum; 
	
	srand( (unsigned)(time(NULL)) );
	
	//opening
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("☆☆☆☆☆----------☆☆☆☆☆\n");
	printf("☆☆☆☆  BINGO GAME  ☆☆☆☆\n");
	printf("☆☆☆☆☆----------☆☆☆☆☆\n");
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n\n\n");
	
	//game
	bingo_init();
	//	bingo_print();
	////	selNum = get_number(); // 검증 
	////	bingo_inputNum(selNum); // 검증 
	//	bingo_print(); 
	//	
	//	//generate numbers
	//	bingo_init();
	//	bingo_printBoard();
	//	bingo_inputNum(5);
	//	bingo_printBoard();
	//	bingo_inputNum(12);
	
	//initialize bingo boards
	
	while (check_gameEnd() == BINGO_RES_UNFINISHED) // 줄 수가 N_BINGO보다 작음 
	{
		//bingo board printing - bingo_printBoard() 
		bingo_print();
		
		//print no. of completed lines - bingo_countCompletedLine()
		printf("No. of completed line : %i\n", bingo_countCompletedLine());
		
		//select a proper number - get_number() (빙고보드와는 관련이 없는 동작. 단순히 숫자 정하는 것) 
		selNum = get_number();
		
		//update the board status 
		bingo_inputNum(selNum);
	}
	
	 
	//ending
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆ ☆\n");
	printf("☆☆☆☆--------------☆☆☆ ☆\n");
	printf("☆☆☆  CONGRATULATION!  ☆☆☆\n");
	printf("☆☆☆☆  YOU WIN! ☆☆☆☆☆☆\n");
	printf("☆☆☆☆☆---------☆☆☆☆☆☆\n");
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆ ☆☆\n\n");
	
	bingo_print();
	
	return 0;
}

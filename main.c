#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bingoBoard.h"

#define BINGO_RES_UNFINISHED -1 // ���� �� ������ �� ���ϰ� 
#define BINGO_RES_FINISHED 0 // ������ �� ���ϰ� 

// main.c : ������ �ֿ� �帧 

// �����尡 ������ �������Ѽ� �Լ��� ����Ǿ����� üũ 

int check_gameEnd(void)
{
	int res = BINGO_RES_UNFINISHED;
	if (bingo_countCompletedLine() >= N_LINE ) // �ٽ� 
		res = BINGO_RES_FINISHED; // �������� �ش��ϴ� ���ϰ� ��ȯ 
	return res;
}

int get_number(void) 
{
	int selNum = 0;
	
	do {
		printf("select a number : ");
		scanf("%d", &selNum);
		fflush(stdin);
		if (selNum < 1 || selNum > N_SIZE * N_SIZE || bingo_checkNum(selNum) == BINGO_NUMSTATUS_ABSENT) // if�� ���ǵ� while�� ���ǰ� �����ϰ� ����! 
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
	printf("�١١١١١١١١١١١١١١�\n");
	printf("�١١١١�----------�١١١١�\n");
	printf("�١١١�  BINGO GAME  �١١١�\n");
	printf("�١١١١�----------�١١١١�\n");
	printf("�١١١١١١١١١١١١١١�\n\n\n");
	
	//game
	bingo_init();
	//	bingo_print();
	////	selNum = get_number(); // ���� 
	////	bingo_inputNum(selNum); // ���� 
	//	bingo_print(); 
	//	
	//	//generate numbers
	//	bingo_init();
	//	bingo_printBoard();
	//	bingo_inputNum(5);
	//	bingo_printBoard();
	//	bingo_inputNum(12);
	
	//initialize bingo boards
	
	while (check_gameEnd() == BINGO_RES_UNFINISHED) // �� ���� N_BINGO���� ���� 
	{
		//bingo board printing - bingo_printBoard() 
		bingo_print();
		
		//print no. of completed lines - bingo_countCompletedLine()
		printf("No. of completed line : %i\n", bingo_countCompletedLine());
		
		//select a proper number - get_number() (������ʹ� ������ ���� ����. �ܼ��� ���� ���ϴ� ��) 
		selNum = get_number();
		
		//update the board status 
		bingo_inputNum(selNum);
	}
	
	 
	//ending
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("�١١١١١١١١١١١١١� ��\n");
	printf("�١١١�--------------�١١� ��\n");
	printf("�١١�  CONGRATULATION!  �١١�\n");
	printf("�١١١�  YOU WIN! �١١١١١�\n");
	printf("�١١١١�---------�١١١١١�\n");
	printf("�١١١١١١١١١١١١� �١�\n\n");
	
	bingo_print();
	
	return 0;
}

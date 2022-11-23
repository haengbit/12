#include <stdio.h>
#include "bingoBoard.h" 

#define BINGONUM_HOLE -1

// bingoBoard.c : 보드와 관련된 단편적인 동작 수행 

static int bingoBoard[N_SIZE][N_SIZE]; // 여기저기서 건드릴거니 전역변수로 선언해주자. 2차원 배열 
static int numberStatus[N_SIZE*N_SIZE];

int bingo_checkNum(int selNum)
{
	if (numberStatus[selNum-1] == BINGONUM_HOLE) // 배열의 값이  
		return BINGO_NUMSTATUS_ABSENT;
	return BINGO_NUMSTATUS_PRESENT; 
}

void bingo_init(void)
{
	int i, j, k;
	int randNum;
	int maxNum = N_SIZE*N_SIZE;
	
	for (i=0;i<N_SIZE*N_SIZE;i++)
		numberStatus[i] = BINGO_NUMSTATUS_ABSENT;
		
	for (i=0; i<N_SIZE;i++)
		for (j=0;j<N_SIZE;j++)
		{
			randNum = rand()%maxNum;
			
			for (k=0; k<N_SIZE*N_SIZE; k++)
			{
				if (numberStatus[k] == BINGO_NUMSTATUS_ABSENT )
				{
					if (randNum == 0)
						break;
					else
						randNum--;
				}
			}
			
			numberStatus[k] = i*N_SIZE + j;
			bingoBoard[i][j] = k+1;
			maxNum--;
		}	
	
}

void bingo_print(void)
{
	int i, j;
	printf("=====================\n");
	for (i=0;i<N_SIZE;i++) {
		for(j=0;j<N_SIZE;j++)
		{
			if (bingoBoard[i][j] == BINGONUM_HOLE)
				printf("X\t");
			else
				printf("%i\t", bingoBoard[i][j]);
		}
		printf("\n");
	}
	
	printf("=====================\n\n");
}

void bingo_inputNum(int sel)
{
	// 각자 해보기! 
	int row, col;
	row = numberStatus[sel-1] / N_SIZE;
	col = numberStatus[sel-1] % N_SIZE;
	
	bingoBoard[row][col] = BINGONUM_HOLE;
	numberStatus[sel - 1] = BINGONUM_HOLE;
}
 
int bingo_countCompletedLine(void)
{
	int i, j;
	int cnt=0;
	int checkBingo;
	
	// row : 가로줄이 몇 개가 생겼 
	for (i=0;i<N_SIZE;i++) 
	{
		checkBingo=1;
		for (j=0;j<N_SIZE;j++)
			if(bingoBoard[i][j] > 0)
			{
				checkBingo = 0;
				break;
			}
		if (checkBingo == 1)
			cnt++;
	}
	
	// col
	for (j=0; j<N_SIZE; j++) 
	{
		checkBingo = 1;
		for (i=0;i<N_SIZE;i++)
			if(bingoBoard[i][j] > 0)
			{
				checkBingo = 0;
				break;
			}
			
		if (checkBingo == 1)
			cnt++;
	}
	
	
	// diagonal
	checkBingo = 1;
	for (i=0; i<N_SIZE;i++)
	{
		if(bingoBoard[i][i] > 0)
		{
			checkBingo = 0;
			break;
		}
	}
	if (checkBingo == 1)
		cnt++;
		
	checkBingo = 1;
	for (i=0; i<N_SIZE;i++)
	{
		if(bingoBoard[i][N_SIZE-i-1] > 0) // i가 0일때, 1일때를 생각해 보세요! 
		{
			checkBingo = 0;
			break;
		}
	}
	if (checkBingo == 1)
		cnt++;	
		
		
	return cnt;
}

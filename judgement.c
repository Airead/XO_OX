#include <stdio.h>
#include <SDL/SDL.h>
#include "xoox.h"
#include "judgement.h"

#define TEST 1

static int leader;

#if TEST

void print_array(int num[][CHESSBOARD_COLUMN], char *name)
{
	int i, j;
	
	printf("%s:\n", name);
	for(i = 0; i < CHESSBOARD_ROW; i++){
		for(j = 0; j < CHESSBOARD_COLUMN; j++){
			printf("%4d", num[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

#endif
int mouse_to_piece_map(int mouse_map[][CHESSBOARD_COLUMN], int pieces_map[][CHESSBOARD_COLUMN])
{
	int i, j;
	int win = 0;
	int play_stat;
#if TEST
	print_array(pieces_map, "mouse to piece map: receive pieces_map");
#endif
	for(i = 0; i < CHESSBOARD_ROW; i++){
		for(j = 0; j < CHESSBOARD_COLUMN; j++){
			if(mouse_map[i][j] & MOUSECLICK ){
				if(pieces_map[i][j] == 0){
					win = leader++ % 2 + 1;
					pieces_map[i][j] = win;		  
				}
				mouse_map[i][j] = 0; /* set mouse map empty */
			}
		}
	}
	play_stat = judge_win(win, pieces_map);
#if TEST
	printf("leader = %d\n", leader - 1);
	printf("mouse to picec map: win = %d\n", win);
	printf("play_stat = %d\n", play_stat);
#endif
	return  play_stat;
}







int judge_win(int win, int pieces[][CHESSBOARD_COLUMN]) /*l 为玩家编号，同时也是玩家棋子编号*/
{
	int i ,j, flag = 0, k = 0;   
#if TEST
	printf("judge_win: win = %d\n", win);
	print_array(pieces, "judge_win: receive pieces[][]");
#endif
/********************行判断********************/
	for(i = 0; i < CHESSBOARD_ROW; i++)
	{
		flag = 0;
		for(j = 0; j < CHESSBOARD_COLUMN; j++)
		{
			if(pieces[i][j] == win)
			{
				flag++;
				if(flag == W) return win; //返回和玩家编号相同，以此定
			}
			
			if(pieces[i][j] != win)
			{
				flag = 0;
			}
		}
	}
/********************列判断********************/	
	for(j = 0; j < CHESSBOARD_ROW; j++)
	{
		flag = 0;
		for(i = 0; i < CHESSBOARD_ROW; i++)
		{
			if(pieces[i][j] == win)
			{
				flag++;
#if TEST
				printf("flag = %d\n", flag);
#endif
				if(flag == W) return win;
			}
			
			if(pieces[i][j] != win)
			{
				flag = 0;
			}
		}
	}

/********************右斜判断********************/		
	for(k = 0; k < CHESSBOARD_ROW ; k++)
	{	
		flag = 0;
		for(i = k, j = 0; j < CHESSBOARD_COLUMN ; i--, j++)
		{

		
			if(pieces[i][j] == win)
			{
				flag++;
				if(flag == W) return win;
			}
			
			if(pieces[i][j] != win)
			{
				flag = 0;
			}
		}
	}

	for(k = 2 * CHESSBOARD_ROW - 2; k >=  CHESSBOARD_ROW; k--)
	{	
		flag = 0;
		for(i = CHESSBOARD_ROW - 1, j = k - CHESSBOARD_ROW + 1; j < CHESSBOARD_ROW; i--, j++)
		{

		
			if(pieces[i][j] == win)
			{
				flag++;
				if(flag == W) return win;
			}
			
			if(pieces[i][j] != win)
			{
				flag = 0;
			}
		}
	}

/********************左斜判断********************/

	for(k = CHESSBOARD_ROW - 1; k >= 0; k--)

	{
		flag = 0;
		for(i = 0, j = k; j < CHESSBOARD_ROW; j++, i++)
		{
				
	
			if(pieces[i][j] == win)
			{
				flag++;
				if(flag == W) return win;
			}
			
			if(pieces[i][j] != win)
			{
				flag = 0;
			}
		}
	}

	for(k = 1; k < CHESSBOARD_ROW; k++)

	{
		flag = 0;
		for(i = k, j = 0; i < CHESSBOARD_ROW; j++, i++)
		{
				
	
			if(pieces[i][j] == win)
			{
				flag++;
				if(flag == W) return win;
			}
			
			if(pieces[i][j] != win)
			{
				flag = 0;
			}
		}
	}


/****************判断和棋****************************************/
	for(i = 0 ; i < CHESSBOARD_ROW; i++)
	{
		for(j = 0; j < CHESSBOARD_ROW; j++)
		{
			if(pieces[i][j] == 0)
				return 0;	/*返回0代表继续*/
		}
	
	}

	return 3;	/*返回为3代表和棋*/
}

int get_leader()
{
	return leader % 2 + 1;
}

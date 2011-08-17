#ifndef JUDGEMENT
#define JUDGEMENT

#include"xoox.h"

int mouse_to_piece_map(int mouse_map[][CHESSBOARD_COLUMN], int pieces_map[][CHESSBOARD_COLUMN]);
int judge_win(int win, int pieces[][CHESSBOARD_COLUMN]);

#define W 5

typedef struct
{
	int leader;
	int win;
}PLAY;

#endif

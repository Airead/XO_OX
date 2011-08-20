#ifndef JUDGEMENT
#define JUDGEMENT

#include"xoox.h"

#define W 5

int mouse_to_piece_map(int mouse_map[][CHESSBOARD_COLUMN], int pieces_map[][CHESSBOARD_COLUMN]);
int judge_win(int win, int pieces[][CHESSBOARD_COLUMN]);
int get_leader();


#endif

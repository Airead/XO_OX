/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 19 21:27:12 CST			*
 ********************************************************
 *		after studying C 63 days		*
 *		after studying APUE 28 days		*
 ********************************************************/

#ifndef JUDGEMENT
#define JUDGEMENT

#include"xoox.h"

#define W 5

int mouse_to_piece_map(int mouse_map[][CHESSBOARD_COLUMN], int pieces_map[][CHESSBOARD_COLUMN]);
int judge_win(int win, int pieces[][CHESSBOARD_COLUMN]);
int get_leader();


#endif

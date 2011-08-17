#ifndef XOOX
#define XXOX

#include "button.h"

/* Screen Attributes */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define SCREEN_BPP 32

/* Frame rate */
#define FRAME_PER_SECOND 30

/* Chess status */
#define PIECE_STAT 4

/* Chess board */
#define CHESSBOARD_ROW 8
#define CHESSBOARD_COLUMN 8

/* Declare function protype */
SDL_Surface *load_image(char *filename);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface* destination);
void pieces_handle_event(Button bt[][CHESSBOARD_COLUMN], int mouse_map[][CHESSBOARD_COLUMN], SDL_Event *event);
void pieces_show(SDL_Surface *piece_stat_img[], int pieces_map[][CHESSBOARD_COLUMN], SDL_Surface *screen);
void subchessboard_show(SDL_Surface *mouseover, SDL_Surface *mouseother, int mouse_map[][CHESSBOARD_COLUMN], SDL_Surface *screen);


#endif

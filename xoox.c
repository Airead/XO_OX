/*
 * @file   xoox.c
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date   2011.08.15
 *  
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include "xoox.h"


int main(int argc, int *argv[])
{
	bool quit = false;	/* quit flag */
	int i;
	SDL_Surface *screen;		 /* main screen */
	SDL_Surface *chessboard;	 /* chess board */
	SDL_Surface *pieces[PIECE_STAT]; /* pieces image */
	bool click_map[CHESSBOARD_ROW][CHESSBOARD_COLUMN]; /* click or not */
	int pieces_map[CHESSBOARD_ROW][CHESSBOARD_COLUMN]; /* pieces state */
	
	/* Init SDL lib*/
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return 1;
	}
	
	/* Init screen */
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen == NULL){
		return 1;
	}
	SDL_WM_SetCaption("XO_OX", NULL);
	
	/* Load resource */
	
	/* Main loop */
	
	/* Free resource */
	SDL_FreeSurface(chessboard);
	for(i = 0; i < PIECE_STAT; i++){
		SDL_FreeSurface(pieces[i]);
	}

	return 0;
}

/* 
 * Load a image to a temporary image, optimized the image 
 * and free the temporary image.
 *
 */
SDL_Surface *load_image(char *filename)
{
	SDL_Surface *img_tmp = NULL;
	SDL_Surface *img_opt = NULL;
	Uint32 colork = 0;

	img_tmp = IMG_Load(filename);
	if(img_tmp != NULL){
		img_opt = SDL_DisplayFormat(img_tmp);
		SDL_FreeSurface(img_tmp);
		if(img_opt != NULL){
			colork = SDL_MapRGB(img_opt->format, 0x00, 0xFF, 0xFF);
			SDL_SetColorKey(img_opt, SDL_SRCCOLORKEY, colork);
		}
	}
	return img_opt;
}

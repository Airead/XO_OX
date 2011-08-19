/*
 * @file   xoox.c
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date   2011.08.15
 * @date   2011.08.16 
 */

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "xoox.h"
#include "button.h"
#include "timer.h"
#include "judgement.h"

#define TEST 1

int main(int argc, int *argv[])
{
	bool quit = false;	/* quit flag */
	int i, j;
	int play_stat = 0;
	Timer fps;		/* cap frame rate */
	SDL_Event event;
	SDL_Surface *mouseover;
	SDL_Surface *mouseother;
	SDL_Surface *wintitle[3];
	SDL_Surface *screen;		 /* main screen */
	SDL_Surface *chessboard;	 /* chess board */
	Button pieces[CHESSBOARD_ROW][CHESSBOARD_COLUMN] = {{0}};
	SDL_Surface *piece_stat_img[PIECE_STAT + 1] = {NULL}; /* pieces image */
	int mouse_map[CHESSBOARD_ROW][CHESSBOARD_COLUMN] = {{0}}; /* click or not */
	int pieces_map[CHESSBOARD_ROW][CHESSBOARD_COLUMN] = {{0}}; /* pieces state */
	
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
	piece_stat_img[1] = load_image("xooxres/chess1.png");
	piece_stat_img[2] = load_image("xooxres/chess2.png");
	piece_stat_img[3] = piece_stat_img[1]; /* for special show, but no time to do */
	piece_stat_img[4] = piece_stat_img[2]; /* for special show, but no time to do */
	chessboard = load_image("xooxres/chessboard.png");
	mouseover = load_image("xooxres/mouseover.png");
	mouseother = load_image("xooxres/mouseother.png");
	wintitle[0] = load_image("xooxres/wintitle1.png");
	wintitle[1] = load_image("xooxres/wintitle2.png");
	wintitle[2] = load_image("xooxres/wintitle3.png");

	/* Init timer */
	timer_init(&fps);

	/* Init button */
	for(i = 0; i < CHESSBOARD_ROW; i++){
		for(j = 0; j < CHESSBOARD_COLUMN; j++){
			button_init(&pieces[i][j], SUBBOARD_WIDTH  * i, SUBBOARD_HEIGHT  * j, SUBBOARD_WIDTH , SUBBOARD_HEIGHT );
			button_set_stat_img(&pieces[i][j], BUTTON_MOUSEOVER, mouseover);
			button_set_stat_img(&pieces[i][j], BUTTON_MOUSEOUT, mouseother);
			button_set_stat_img(&pieces[i][j], BUTTON_MOUSEUP, mouseother);
			button_set_stat_img(&pieces[i][j], BUTTON_MOUSEDOWN, mouseother);
		}
	}

	/* Main loop */
	while(quit == false){
		/* timer start */
		timer_start(&fps); 
		while(SDL_PollEvent(&event)){
			/* Pieces input handle */
			pieces_handle_event(pieces, mouse_map, &event);
			
			/* User quit */
			if(event.type == SDL_QUIT){
				quit = true;
			}
		}
		play_stat = mouse_to_piece_map(mouse_map, pieces_map);
		subchessboard_show(mouseover, mouseother, mouse_map, screen);
		pieces_show(piece_stat_img, pieces_map, screen);
		if(play_stat != 0){
			printf("play_stat = %d\n", play_stat);
			apply_surface((SCREEN_WIDTH - wintitle[play_stat - 1]->w) / 2, (SCREEN_HEIGHT - wintitle[play_stat - 1]->h) / 2, wintitle[play_stat - 1], screen);
		}

		/* Update screen */
		if(SDL_Flip(screen) == -1){
			return 1;
		}
		
		if(play_stat != 0){
			SDL_Delay(3000);
			quit = true;
		}
		/* cap frame rate */
		if(timer_get_ticks(&fps) < 1000 / FRAME_PER_SECOND){
			SDL_Delay((1000 / FRAME_PER_SECOND) - timer_get_ticks(&fps));
		}
	}

	/* Free resource */
	SDL_FreeSurface(chessboard);
	SDL_FreeSurface(mouseover);
	SDL_FreeSurface(mouseother);
	for(i = 0; i < 2; i++){
		SDL_FreeSurface(piece_stat_img[i]);
	}
	for(i = 0; i < 3; i++){
		SDL_FreeSurface(wintitle[i]);
	}
	
	SDL_Quit();
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
			colork = SDL_MapRGB(img_opt->format, 0xFF, 0xFF, 0xFF);
			SDL_SetColorKey(img_opt, SDL_SRCCOLORKEY, colork);
		}
	}
	return img_opt;
}

/* 
 * Simple apply source to destination at (x, y)
 *
 */
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface* destination)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}
/* 
 * every pieces handle event
 * get mouse_map
 */
void pieces_handle_event(Button bt[][CHESSBOARD_COLUMN], int mouse_map[][CHESSBOARD_COLUMN], SDL_Event *event)
{
	int i, j;
	
	for(i = 0; i < CHESSBOARD_ROW; i++){
		for(j = 0; j < CHESSBOARD_COLUMN; j++){
			button_handle_event(&bt[i][j], event);
			mouse_map[i][j] = bt[i][j].cur_stat;
		}
	}
}
/* 
 * show all pieces according to pieces map
 */
void pieces_show(SDL_Surface *piece_stat_img[], int pieces_map[][CHESSBOARD_COLUMN], SDL_Surface *screen)
{
	int i, j;
	
	for(i = 0; i < CHESSBOARD_ROW; i++){
		for(j = 0; j < CHESSBOARD_COLUMN; j++){
			if(pieces_map[i][j] != 0){
				apply_surface(i * SUBBOARD_WIDTH + 4, j * SUBBOARD_HEIGHT + 4, piece_stat_img[pieces_map[i][j]], screen);
			}
		}
	}
}

/* 
 * show chessboard 
 */
void subchessboard_show(SDL_Surface *mouseover, SDL_Surface *mouseother, int mouse_map[][CHESSBOARD_COLUMN], SDL_Surface *screen)
{
	int i, j;
	
	for(i = 0; i < CHESSBOARD_ROW; i++){
		for(j = 0; j < CHESSBOARD_COLUMN; j++){
			if(mouse_map[i][j] & MOUSEOVER ){
				apply_surface(i * SUBBOARD_WIDTH , j * SUBBOARD_HEIGHT , mouseover, screen);
			}else{
				apply_surface(i * SUBBOARD_WIDTH , j * SUBBOARD_HEIGHT , mouseother, screen);
			}
		}
	}
}



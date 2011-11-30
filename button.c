/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 19 21:26:11 CST			*
 ********************************************************
 *		after studying C 63 days		*
 *		after studying APUE 28 days		*
 ********************************************************/

#include <SDL/SDL.h>
#include <stdbool.h>
#include "button.h"

/* 
 * Init a button, set it's (x,y), width and height;
 * set it's mouse state image
 *
 */

Button *button_init(Button *bt, int x, int y, int w, int h)
{
	int i;	

	/* Set the button's attributes */
	bt->box.x = x;
	bt->box.y = y;
	bt->box.w = w;
	bt->box.h = h;

	/* Set the button's downing or not */
	bt->downing = false;

	/* Set the button's current stat */
	bt->cur_stat = BUTTON_MOUSEOUT;

	/* Set the default img_stat */
	for(i = 0; i < BUTTON_MOUSESTAT; i++){
		bt->img_mouse_stat[i] = NULL;
	}	
	return bt;
}

/* 
 * set a image to a button mouse state
 */
Button *button_set_stat_img(Button *bt, int mouse_stat, SDL_Surface *img)
{
	bt->img_mouse_stat[mouse_stat] = img;
	return bt;
}

/* 
 * get button current stat
 */
int button_get_stat(Button *bt)
{
	return bt->cur_stat;
}

/* 
 * Button handle event
 * The buuton have four state image
 *   1.BUTTON_MOUSEOVER
 *   2.BUTTON_MOUSEOUT
 *   3.BUTTON_MOUSEDOWN
 *   4.BUTTON_MOUSEUP
 * set button current stat according to event
 */
void button_handle_event(Button *bt, SDL_Event *event)
{
	/* The mouse offsets */
	int x = 0, y = 0;
	
	bt->cur_stat = 0;
	/* If the mouse moved */
	if(event->type == SDL_MOUSEMOTION){
		/* Get the mouse offsets */
		x = event->motion.x;
		y = event->motion.y;

		/* If the mouse is over the button */
		if( (x > bt->box.x) && (x < bt->box.x + bt->box.w) && (y > bt->box.y) && ( y < bt->box.y + bt->box.h) ){
			/* Set the button sprite */
			bt->cur_stat |= MOUSEOVER;
		}else{
			bt->cur_stat |= MOUSEOUT;
		}
	}
	if(event->type == SDL_MOUSEBUTTONDOWN){
		if(event->button.button == SDL_BUTTON_LEFT){
			x = event->motion.x;
			y = event->motion.y;
			if( (x > bt->box.x) && (x < bt->box.x + bt->box.w) && (y > bt->box.y) && ( y < bt->box.y + bt->box.h) ){
				/* Set the button sprite */
				bt->cur_stat |= MOUSEDOWN;
				bt->downing = true;
			}
		}
	}
	if(event->type == SDL_MOUSEBUTTONUP){
		if(event->button.button == SDL_BUTTON_LEFT){
			x = event->motion.x;
			y = event->motion.y;
			if( (x > bt->box.x) && (x < bt->box.x + bt->box.w) && (y > bt->box.y) && ( y < bt->box.y + bt->box.h) ){
				/* Set the button sprite */
				bt->cur_stat |= MOUSEUP;
				if(bt->downing = true){
					bt->downing = false;
					bt->cur_stat |= MOUSECLICK;
				}
			}
		}
	}
}

/* 
 * simple put button to screen
 */
void buttonShow(Button *bt, SDL_Surface *screen)
{
	int i;

	/* Mouse over */
	if(bt->cur_stat & (1 << 1)){
		i = 1;
	}
	/* Mouse out */
	SDL_BlitSurface(bt->img_mouse_stat[i], NULL, screen, &bt->box);
}

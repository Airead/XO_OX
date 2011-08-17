#ifndef BUTTON
#define BUTTON

#include <stdbool.h>

#define BUTTON_MOUSESTAT 4
#define BUTTON_MOUSEOUT 0
#define BUTTON_MOUSEOVER 1
#define BUTTON_MOUSEUP 2
#define BUTTON_MOUSEDOWN 3

#define MOUSEOUT 0X0001
#define MOUSEOVER 0X0002
#define MOUSEUP 0X0004
#define MOUSEDOWN 0X0008
#define MOUSECLICK 0x0010


typedef struct{
	SDL_Rect box;
	Uint32 cur_stat;
	bool downing;
	SDL_Surface *img_mouse_stat[BUTTON_MOUSESTAT];
}Button;

Button *button_init(Button *bt, int x, int y, int w, int h);
Button *button_set_stat(Button *bt, int mouse_stat, SDL_Surface *img);
int button_get_stat(Button *bt);
void button_handle_event(Button *bt, SDL_Event *event);
void button_show(const Button *bt, SDL_Surface screen);


#endif

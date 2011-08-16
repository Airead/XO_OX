#include <stdbool.h>
#include "timer.h"

/* 
 * Copyright (c) 2011 Airead Fan <fgh189168@gmail.com>
 * Timer function DOWN
 * 
 */
Timer *timer_init(Timer *ptime){
	ptime->startTicks = 0;
	ptime->pausedTicks = 0;
	ptime->paused = false;
	ptime->started = false;
	return ptime;
}

void timer_start(Timer *ptime){
	ptime->started = true;
	ptime->paused = false;
	ptime->startTicks = SDL_GetTicks();
}

void timer_stop(Timer *ptime){
	ptime->started = false;
	ptime->paused = false;
}

void timer_pause(Timer *ptime){
	if( (ptime->started == true) && (ptime->paused == false) ){
		ptime->paused = true;
		ptime->pausedTicks = SDL_GetTicks() - ptime->startTicks;
	}
}

void timer_unpause(Timer *ptime){
	if(ptime->paused == true){
		ptime->paused = false;
		ptime->startTicks = SDL_GetTicks() - ptime->pausedTicks;
		ptime->pausedTicks = 0;
	}
}

int timer_get_ticks(Timer *ptime){
	if(ptime->started == true){
		if(ptime->paused == true){
			return ptime->pausedTicks;
		}else{
			return SDL_GetTicks() - ptime->startTicks;
		}
	}
	/* If the timer isn't runnig */
	return 0;
}

bool timer_isstarted(Timer *ptime){
	return ptime->started;
}

bool timer_ispaused(Timer *ptime){
	return ptime->paused;
}
/* 
 *
 * Timer function UP 
 * 
 */

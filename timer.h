/* 
 * Copyright (c) 2011 Airead Fan <fgh189168@gmail.com>
 * Timer function DOWN
 * 
 */

#ifndef TIMER
#define TIMER

typedef struct{
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;
}Timer;

#endif

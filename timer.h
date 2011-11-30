/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    2011 9月 19 21:26:56 CST			*
 ********************************************************
 *		after studying C 63 days		*
 *		after studying APUE 28 days		*
 ********************************************************/

#ifndef TIMER
#define TIMER

typedef struct{
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;
}Timer;

#endif

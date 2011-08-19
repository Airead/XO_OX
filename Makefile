xoox : xoox.o button.o timer.o judgement.o
	gcc -g -o xoox  -lm -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer xoox.o button.o timer.o judgement.o

xoox.o : xoox.c xoox.h
	gcc -g -c xoox.c
button.o : button.c button.h
	gcc -g -c button.c
timer.o : timer.c timer.h
	gcc -g -c timer.c
judgement.o : judgement.c judgement.h xoox.h
	gcc -g -c judgement.c

install: 
	mkdir /usr/games/xooxres/
	cp xooxres/*.png /usr/games/xooxres/
	cp xoox /usr/games/

uninstall:
	rm /usr/games/xoox
	rm -r /usr/games/xooxres

clean :
	rm *.o *~ xoox

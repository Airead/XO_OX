xoox : xoox.o button.o timer.o
	gcc -g -o xoox  -lm -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer xoox.o button.o timer.o

xoox.o : xoox.c xoox.h
	gcc -g -c xoox.c
button.o : button.c button.h
	gcc -g -c button.c
timer.o : timer.c timer.h
	gcc -g -c timer.c
clean :
	rm *.o
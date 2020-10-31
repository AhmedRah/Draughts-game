#Constants
CC=gcc
O=bin
S=src
FLAGS=-w -Werror -Wall -g
SDL_CFLAGS=`sdl2-config --cflags --libs`


#Compilation
run: $(O)/game.o
	$(CC) -o run $^ $(SDL_CFLAGS) $(FLAGS) 
$(O)/game.o:
	$(CC) -o $(O)/game.o -c $(S)/game.c $(SDL_CFLAGS) $(FLAGS)
clean:
	rm -rf bin/*.o

cleanrun: clean
	make run
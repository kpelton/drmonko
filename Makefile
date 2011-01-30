CC = g++  -g  -Wall  `sdl-config --cflags --libs` -lGL -lGLU -lSDL_net -lSDL_mixer -lSDL_ttf 
CFLAGS =    -c

all: drmonko


drmonko: timer.o main.o board.o   piece.o  sdlWindow.o boardview.o GLscene.o 
	$(CC) -g main.o timer.o piece.o sdlWindow.o boardview.o  board.o GLscene.o -o drmonko

main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp 

timer.o: timer.cpp
	$(CC) $(CFLAGS) timer.cpp	
player.o: player.cpp player.h 
	$(CC) $(CFLAGS) player.cpp player.h 

nplayer.o: nplayer.h nplayer.cpp
	$(CC) $(CFLAGS) nplayer.h nplayer.cpp	

GLscene.o:  GLscene.cpp 
	$(CC) $(CFLAGS)  GLscene.cpp 

piece.o: piece.cpp piece.h
	$(CC) $(CFLAGS) piece.cpp

sdlWindow.o: sdlWindow.cpp sdlWindow.h
	$(CC) $(CFLAGS)  sdlWindow.cpp sdlWindow.h

boardview.o: boardview.cpp boardview.h
	$(CC) $(CFLAGS) boardview.cpp boardview.h

board.o:board.h board.cpp
	$(CC)$(CFLAGS)  board.h board.cpp


clean:
	@echo Cleaning up...
	@rm *.o
	@rm *.gch
	@rm drmonko
	@echo Done.

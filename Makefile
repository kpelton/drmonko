CC = g++  -O2  -Wall  `sdl-config --cflags --libs` -lGL -lGLU -lglut -lSDL_net -lSDL_mixer -lSDL_ttf 
CFLAGS =    -c

all: drmonko

drmonko: main.o   piece.o  sdlWindow.o background.o GLscene.o 
	$(CC) main.o  piece.o sdlWindow.o background.o GLscene.o -o drmonko

main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp 


player.o: player.cpp player.h 
	$(CC) $(CFLAGS) player.cpp player.h 

nplayer.o: nplayer.h nplayer.cpp
	$(CC) $(CFLAGS) nplayer.h nplayer.cpp	

GLscene.o: GLobject.h GLscene.h GLscene.cpp 
	$(CC) $(CFLAGS)  GLobject.h  GLscene.cpp 

piece.o: piece.cpp piece.h
	$(CC) $(CFLAGS) piece.cpp

sdlWindow.o: sdlWindow.cpp sdlWindow.h
	$(CC) $(CFLAGS)  sdlWindow.cpp sdlWindow.h

background.o: background.cpp background.h
	$(CC) $(CFLAGS) background.cpp background.h

board.o:board.cpp board.h
	$(CC)$(CFLAGS)  board.h board.cpp

gpacket.o:gpacket.cpp gpacket.h
	$(CC)$(CFLAGS) gpacket.h gpacket.cpp

clean:
	@echo Cleaning up...
	@rm *.o
	@rm *.gch
	@rm tetris
	@echo Done.

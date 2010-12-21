CC = g++  -O2  -Wall  `sdl-config --cflags --libs` -lGL -lGLU -lglut -lSDL_net -lSDL_mixer 
CFLAGS =    -c

all: tetris

tetris: main.o   piece.o  sdlWindow.o background.o GLscene.o board.o player.o nplayer.o gpacket.o
	$(CC) main.o  nplayer.o piece.o sdlWindow.o background.o GLscene.o board.o player.o gpacket.o -o tetris

main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp 


player.o: player.cpp player.h 
	$(CC) $(CFLAGS) player.cpp player.h 

nplayer.o: nplayer.h nplayer.cpp
	$(CC) $(CFLAGS) nplayer.h nplayer.cpp	

GLscene.o: GLscene.h GLscene.cpp GLobject.h
	$(CC) $(CFLAGS) GLscene.cpp GLobject.h

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

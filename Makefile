CC = g++ -O2 -g  -Wall  `sdl-config --cflags --libs` -lGL -lGLU -lSDL_net -lSDL_mixer -lSDL_ttf 
CFLAGS =    -c

all: drmonko


drmonko: timer.o main.o board.o   piece.o  sdlWindow.o boardview.o GLscene.o game.o MenuWindow.o particle.o splayer.o
	$(CC) -g main.o timer.o piece.o splayer.o particle.o sdlWindow.o boardview.o  board.o GLscene.o game.o MenuWindow.o -o drmonko

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
	$(CC) $(CFLAGS)  board.h board.cpp

game.o:game.h game.cpp
	$(CC) $(CFLAGS)  game.h game.cpp

MenuWindow.o:MenuWindow.h MenuWindow.cpp
	$(CC) $(CFLAGS)  MenuWindow.h MenuWindow.cpp

particle.o:particle.h particle.cpp
	$(CC) $(CFLAGS)  particle.h particle.cpp
	
splayer.o:splayer.h splayer.cpp
	$(CC) $(CFLAGS)  splayer.h splayer.cpp
	
clean:
	@echo Cleaning up...
	@rm *.o
	@rm *.gch
	@rm drmonko
	@echo Done.

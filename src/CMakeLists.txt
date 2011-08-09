Project ( drmonko )
cmake_minimum_required(VERSION 2.6)
set (
   SOURCES
   board.cpp
   board.h
   boardview.cpp
   boardview.h
   game.cpp
   game.h
   GLobject.h
   GLscene.cpp
   GLscene.h
   main.cpp
   MenuWindow.cpp
   MenuWindow.h
   mtrand.cpp
   mtrand.h
   netgame.cpp
   netgame.h
   networkplayer.cpp
   networkplayer.h
   particle.cpp
   particle.h
   piece.cpp
   piece.h
   player.h
   sdlWindow.cpp
   sdlWindow.h
   splayer.cpp
   splayer.h
   timer.cpp
   timer.h
   twoplayer.cpp
   twoplayer.h
   types.h
)

Find_Package ( SDL REQUIRED )
Find_Package ( SDL_net REQUIRED )
Find_Package ( SDL_ttf REQUIRED ) 
Find_Package ( SDL_mixer REQUIRED ) 
Find_Package(OpenGL REQUIRED )

include_directories (
   ${SDL_INCLUDE_DIRS}
)

link_libraries (
   ${SDL_LIBRARY}
   ${SDLMIXER_LIBRARY}
   ${SDLTTF_LIBRARY}
   ${SDLNET_LIBRARY}
   ${OPENGL_LIBRARY}
   SDLmain 
)

add_executable (
   drmonko
   WIN32 
   MACOSX_BUNDLE
   ${SOURCES} 
)
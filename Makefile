# #CC specifies which compiler we're using
CC = g++

#OBJS specifies which files to compile as part of the project
OBJS = main.cpp game.cpp level.cpp player.cpp

# #INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\Dev\SDL-for-Mingw\SDL2-2.30.0\i686-w64-mingw32\include\SDL2 -IC:\Dev\SDL-for-Mingw\SDL_Image\SDL2_image-2.8.2\i686-w64-mingw32\include\SDL2

# #LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\Dev\SDL-for-Mingw\SDL2-2.30.0\i686-w64-mingw32\lib -LC:\Dev\SDL-for-Mingw\SDL_Image\SDL2_image-2.8.2\i686-w64-mingw32\lib

# #COMPILER_FLAGS specifies the additional compilation options we're using
# # -w suppresses all warnings
# # -Wl,-subsystem,windows gets rid of the console window
# # COMPILER_FLAGS = -w -Wl,-subsystem,windows

# #LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

OBJ_NAME = main

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean: 
	del *.o main game.exe



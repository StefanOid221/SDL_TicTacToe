#OBJS specifies which files to compile as part of the project
OBJS = server.cpp LTexture.cpp LButton.cpp Globals.cpp Util.cpp

#CC specifies which compiler we're using
CC = g++

# Relative paths from the current directory to include and library folders
RELATIVE_INCLUDE_PATH = ./src/include
RELATIVE_LIBRARY_PATH = ./src/lib

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I$(RELATIVE_INCLUDE_PATH)

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L$(RELATIVE_LIBRARY_PATH)

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -g includes debugging symbols
# -O0 turns off optimization
# -Wall enables most compiler warnings
COMPILER_FLAGS = -w -g -O0 -Wall

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_net

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = server

#This is the target that compiles our executable
all : $(OBJS)
		$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


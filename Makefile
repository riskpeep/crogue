#OBJS specifies which files to compile as part of the project
OBJS = main.c console.c texture.c

#CC specifies which compiler we'll be using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wall turns on lots of warnings
COMPILER_FLAGS = -Wall -Wpedantic -ansi

#LINKER_FLAGS specializes the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our executable
OBJ_NAME = crogue

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

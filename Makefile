#OBJS specifies which files to compile as part of the project
OBJS_CPP = CG.cpp Mesh.cpp
OBJS_MAIN = main.cpp 
#OBJ_NAME specifies the name of our exectuable
OBJ_TARGET = exec

CC = g++

FLAGS = -w -lSDL -lGL -lGLU -lglut -o
#This is the target that compiles our executable
all : $(OBJS_MAIN)
	$(CC) $(OBJS_CPP) $(OBJS_MAIN) $(FLAGS) $(OBJ_TARGET)

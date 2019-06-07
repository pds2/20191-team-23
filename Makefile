CC=g++
ENGINE=source/Engine/*.cpp
GAME=source/*.cpp

OUT=bin/app.exe

#INCLUDE_PATH= -IC:\extern\win64\include
#LIB_PATH= -LC:\extern\win64\lib

COMPILER_FLAGS = -w -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

all:
	$(CC) -std=c++11 $(ENGINE) $(GAME) $(COMPILER_FLAGS) -o $(OUT) $(LINKER_FLAGS)
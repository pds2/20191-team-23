CC=g++
ENGINE=source/engine/*.cpp
GAME=source/game/*.cpp source/*.cpp
#GAME=source/*.cpp

OUT=bin/app.exe

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#INCLUDE_PATH= -IC:\extern\win64\include
#LIB_PATH= -LC:\extern\win64\lib
#COMPILER_FLAGS = -w -Wl,-subsystem,windows
# $(COMPILER_FLAGS)

all:
	$(CC) -std=c++11 $(ENGINE) $(GAME) -o $(OUT) $(LINKER_FLAGS)
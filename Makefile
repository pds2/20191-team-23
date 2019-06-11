CC=g++
ENGINE=source/engine/*.cpp
GAME=source/game/*.cpp source/*.cpp

WIN_OUT=bin/app.exe
LIN_OUT=bin/app

FLAGS = -lSDL2main -lSDL2 -lSDL2_image

LINKER_FLAGS :=
OUT := 
BUILD_SETUP :=

ifeq ($(OS), Windows_NT)
	LINKER_FLAGS += -lmingw32 $(FLAGS)
	# -w -Wl,-subsystem,windows
	OUT += $(WIN_OUT)
	#BUILD_SETUP += if not exists %cd%+"bin" mkdir %cd%+"bin"
else
	LINKER_FLAGS += $(FLAGS)
	OUT += $(LIN_OUT)
	#BUILD_SETUP += sudo apt-get install libsdl2-dev libsdl2-image-dev
	BUILD_SETUP += mkdir -p bin
endif


all:
	$(BUILD_SETUP)
	$(CC) -std=c++11 $(ENGINE) $(GAME) -o $(OUT) $(LINKER_FLAGS)

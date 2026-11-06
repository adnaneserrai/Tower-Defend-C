# Tower Defend — build with SDL2
#   Linux / macOS / MSYS2:  make && ./towerdefend
CC      ?= gcc
CFLAGS  ?= -std=c99 -Wall -pedantic -O2
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS   := $(shell sdl2-config --libs)

SRC = src/main.c src/towerdefend.c src/maSDL.c
OBJ = $(SRC:.c=.o)
BIN = towerdefend

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(SDL_LIBS) -lm

src/%.o: src/%.c src/towerdefend.h src/maSDL.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN) $(BIN).exe

.PHONY: all clean

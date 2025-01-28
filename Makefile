ifeq ($(OS), Windows_NT)
    RM = del /F /Q
    RMDIR = rmdir /S /Q
    TARGET = game.exe
else
    OS := $(shell uname)
    ifeq ($(OS), Linux)
        RM = rm -f
        RMDIR = rm -rf
        TARGET = game
    else ifeq ($(OS), Darwin)
        RM = rm -f
        RMDIR = rm -rf
        TARGET = game
    endif
endif

CC = gcc

CFLAGS = -Wall -Wextra

INCLUDES = -Iinclude

SRC = game.c engine/evaluate.c engine/minimax.c

OBJ = $(SRC:.c=.o)

DEPS = include/game.h include/evaluate.h include/minimax.h

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o
	$(RMDIR) engine
	$(RM) $(TARGET)
CC = gcc

CFLGS = -Wall -Wextra

INCLUDES = -Iinclude

SRC = game.c engine/evaluate.c engine/minimax.c

OBJ = $(SRC:.c=.o)

TARGET = game.exe

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	del *.o
	del engine\*.o
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -I. 
LIBFLAGS = -lncurses

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = main

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

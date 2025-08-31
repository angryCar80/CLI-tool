CC = g++
CFLAGS = -Wall -std=c99
LIBS = -lraylib -lm -ldl -lpthread -lGL -lX11

SRC = main.cpp
OBJ = $(SRC:.c=.o)
OUT = todolist

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)

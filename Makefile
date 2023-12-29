CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = main
SRC = main.c regles.c baseC.c baseF.c moteurInference.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

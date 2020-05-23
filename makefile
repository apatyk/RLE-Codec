CC = gcc
CFLAGS = -Wall -g

BIN1 = rlecomp
BIN2 = rledecomp

all: $(BIN1) $(BIN2)

$(BIN1):  $(BIN1).c
	$(CC) -o $(BIN1) $(BIN1).c $(CFLAGS)

$(BIN2):  $(BIN2).c
	$(CC) -o $(BIN2) $(BIN2).c $(CFLAGS)

style:
	astyle --style=banner *.c

clean:
	rm $(BIN1)
	rm $(BIN2)
	rm *.rle
	rm *-recovered*

cleano:
	rm *.orig

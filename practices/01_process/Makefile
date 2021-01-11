CC=gcc
CFLAGS=-Wall
PROJECT=main

all: $(PROJECT)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) $^ -o $@

clean:
	rm -f *.o $(PROJECT)

run: $(PROJECT)
	./$(PROJECT)
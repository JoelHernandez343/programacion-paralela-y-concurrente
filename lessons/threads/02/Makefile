CC=gcc
CFLAGS=-Wall
PROJECT=main
LDFLAGS=-lm -lpthread

all: $(PROJECT)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o $(PROJECT)

run: $(PROJECT)
	./$(PROJECT)
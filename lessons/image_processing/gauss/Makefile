CC=gcc
CFLAGS=-Wall
PROJECT=principal
LDFLAGS=-lm -lpthread
DESTDIR=/usr/local/bin

all: $(PROJECT)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean run install uninstall

clean:
	rm -f *.o $(PROJECT) result.bmp

run: $(PROJECT)
	./$(PROJECT)

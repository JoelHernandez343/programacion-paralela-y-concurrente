CC=gcc
CFLAGS=-Wall
PROJECT=main
LDFLAGS=-lm -lpthread
DESTDIR=/usr/local/bin

all: $(PROJECT)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean run install uninstall

clean:
	rm -f *.o $(PROJECT) hann.data result.data

run_thread: $(PROJECT)
	./$(PROJECT) thread

run_process: $(PROJECT)
	./$(PROJECT) process
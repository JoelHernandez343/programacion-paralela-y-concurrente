CC=gcc
CFLAGS=-Wall
PROJECT=main
DESTDIR=/usr/local/bin

all: $(PROJECT)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) $^ -o $@

.PHONY: clean run install uninstall

clean:
	rm -f *.o $(PROJECT)

run: $(PROJECT)
	./$(PROJECT)

install: all
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR) ; \
	fi; \
	sudo cp $(PROJECT) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROJECT)

CC=gcc
CFLAGS=-Wall
E1=example_01
E2=example_02
E3=example_03

all: $(E1) $(E2) $(E3)

$(E1): $(E1).c
	$(CC) $^ -o $@ $(CFLAGS)

$(E2): $(E2).c
	$(CC) $^ -o $@ $(CFLAGS)

$(E3): $(E3).c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f $(E1) $(E2) $(E3)
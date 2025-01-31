CC=gcc
CFLAGS=-Wall -Werror

all: act1 act2 act3 act4

act1: act1.o gameoflife.o
	$(CC) $(CFLAGS) -o act1 act1.o gameoflife.o

act2: act2.o gameoflife.o
	$(CC) $(CFLAGS) -o act2 act2.o gameoflife.o

act3: act3.o gameoflife.o
	$(CC) $(CFLAGS) -o act3 act3.o gameoflife.o

act4: act4.o gameoflife.o
	$(CC) $(CFLAGS) -o act4 act4.o gameoflife.o
ex2: ex2.o gameoflife.o
	$(CC) $(CFLAGS) -o ex2 ex2.o gameoflife.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f act1 ex2 act2 act3 act4 *.o

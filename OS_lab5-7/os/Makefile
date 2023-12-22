CC = g++
CFLAGS = -lzmq -w -pthread

all: main child

main: main.cpp
	$(CC) main.cpp $(CFLAGS) -o main

child: child.cpp
	$(CC) child.cpp $(CFLAGS) -o child

clean:
	rm -f main child

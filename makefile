CC = g++ 

CFLAGS = -std=c++11

#all: Fibonacci.o dijikstra.o  main.o
#	$(CC) -std=c++11 Fibonacci.o dijikstra.o  main.o -o main 

all: Fibonacci.o leftist.o dijikstra.o  main.o
	$(CC)  $(CFLAGS) Fibonacci.o leftist.o dijikstra.o main.o -o main 

main.o: main.cpp
	$(CC) $(CFLAGS) -c  main.cpp

dijikstra.o: dijikstra.cpp
	$(CC) $(CFLAGS) -c dijikstra.cpp

leftist.o: leftist.cpp
	$(CC) $(CFLAGS) -c leftist.cpp

Fibonacci.o: Fibonacci.cpp
	$(CC) $(CFLAGS) -c Fibonacci.cpp

clean:
	rm -f sample
	rm -f *.o
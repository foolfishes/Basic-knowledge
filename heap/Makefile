all:heap
heap: heap.o
		g++ heap.o -o heap
heap.o: heap_test.cpp
		g++ -g -Wall -c heap_test.cpp -o heap.o

.PHONY:clean
clean:
		rm heap.o

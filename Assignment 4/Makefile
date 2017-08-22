all: tracker test

tracker:
	gcc -Wall -std=c99 -Iinclude src/linkedList.c src/tracker.c src/count.c -o tracker

test:
	gcc -Wall -std=c99 -Iinclude src/test.c src/linkedList.c -o test


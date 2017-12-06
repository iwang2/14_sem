all: sem.c
	gcc sem.c

clean:
	rm a.out
	rm *~

run: all
	./a.out

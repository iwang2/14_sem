all: sem.c
	gcc sem.c

clean:
	rm a.out
	rm *~

run: all
	./a.out -c 222
	./a.out -v
	./a.out -r
	./a.out -c 111 -v -r

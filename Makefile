
all: main.c
	gcc main.c -lev3dev-c -o bin
clean:
	rm -rf *.o
	rm bin


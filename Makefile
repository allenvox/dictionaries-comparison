all: main
-include *.d

main: main.o bstree.o hashtab.o
	gcc -Wall -o $@ $^

*.o:
	gcc -Wall -c -o $@ $<

clean:
	rm *.o main
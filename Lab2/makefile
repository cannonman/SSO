CC=gcc
CFLAGS= -Wall -g
all:
	g++ -g -o minishell.o minishell.c

shell:
	g++ -g -o shell.o shell.c
	./shell.o ls -l  cat 'end_of_ls'
zip:
	Lab2.zip

clean:
	rm -f *.o

Lab1.zip: *.c *.h Makefile
	zip $@ $^

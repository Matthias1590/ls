CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g

bin/ls: src/ls.c
	$(CC) $(CFLAGS) -o bin/ls src/ls.c

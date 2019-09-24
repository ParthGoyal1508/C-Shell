LDFLAGS=-lncurses
terminal: main.c builtin-commands.c history.c input.c ls.c pinfo.c 
	gcc -o shell main.c -lncurses
all: rasum.c
	gcc -Ircheevos/include rasum.c rcheevos/src/rhash/hash.c rcheevos/src/rhash/md5.c rcheevos/src/rcheevos/consoleinfo.c -o rasum

clean:
	rm rasum

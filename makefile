all: settimes.c
	gcc -g -Wall -o settimes settimes.c

clean:
	$(RM) settimes

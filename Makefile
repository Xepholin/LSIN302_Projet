all: additionneur

additionneur: additionneur.c
	gcc additionneur.c -Wall -o additionneur

clean:
	rm additionneur


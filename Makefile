all: additionneur

additionneur: additionneur.c
	gcc additionneur.c -Wall -lm -o additionneur

clean:
	rm additionneur


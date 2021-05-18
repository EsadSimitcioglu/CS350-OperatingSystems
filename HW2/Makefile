CC=gcc
DEPS=meal.h
LDFLAGS=-pthread

make: kitchen.c meal.h
	@gcc -o kitchen kitchen.c -w -lpthread
	@export PATH="$PATH:."
clean:
	@rm -f kitchen

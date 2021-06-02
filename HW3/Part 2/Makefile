CC=gcc
LDFLAGS=-pthread

make: client.c server.c
	@gcc -o server server.c -lpthread
	@export PATH="$PATH:."
	@gcc -o client client.c
	@export PATH="$PATH:."
clean:
	@rm -f server
	@rm -f client



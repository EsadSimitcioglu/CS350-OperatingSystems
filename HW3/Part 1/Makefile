CC=gcc
LDFLAGS=-pthread

make: echo_client.c echo_server.c
	@gcc -o server echo_server.c -lpthread
	@export PATH="$PATH:."
	@gcc -o client echo_client.c
	@export PATH="$PATH:."
clean:
	@rm -f server
	@rm -f client


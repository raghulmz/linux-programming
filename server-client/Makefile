CC=gcc

server: server.c
	$(CC) -o server server.c

run-server: server
	./server

client: client.c
	$(CC) -o client client.c

run-client: client
	./client

clean:
	rm -f server client *.log
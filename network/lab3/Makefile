
all: client server

client: client.cpp
	g++ -std=c11 -o client client.cpp

server: server.cpp threads.h request.h response.h
	g++ -pthread -std=c11 -o server server.cpp
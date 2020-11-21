#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

#include <iostream>

#include <string>
#include <cstdlib>

#define MSG_LEN 512
#define BUFFER_SIZE 10240
#define SRV_IP "127.0.0.1"
#define SOCK_PORT 9010


std::string create_request(std::string url) {
    std::string req = "";
    req += "GET ";
    req += url;
    req += " HTTP/1.1\r\n";
    
    req += "Host: localhost:" + std::to_string(SOCK_PORT) + "\r\n\r\n"; 
    
    return req;
}


int main(void)
{
    int clientSock = socket(AF_INET,  SOCK_STREAM, IPPROTO_TCP);
    if (clientSock < 0)
    {
        perror("socket error");
        exit(clientSock);
    }

    struct hostent* host = gethostbyname("localhost");
    if (!host)
    {
        perror("gethostbyname error");
        return -1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SOCK_PORT);
    serverAddr.sin_addr = *((struct in_addr*) host->h_addr_list[0]);

    if (connect(clientSock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect error");
        return -1;
    }

    char buf[BUFFER_SIZE];
    const char *message;
    std::string file;


    puts("input file name for HTTP GET: ");
    std::getline(std::cin, file);

    std::string mes =  create_request(file);
    message = mes.c_str();

    sendto(clientSock, message, strlen(message), 0, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

    unsigned int sAddrlen = sizeof(serverAddr);
    if (recvfrom(clientSock, buf, BUFFER_SIZE, 0, (struct sockaddr*) &serverAddr, &sAddrlen) == -1) {
                perror("recvfrom()");
                exit(1);
            }
    std::cout << buf;
    
    close(clientSock);
    return 0;
}

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define MSG_LEN 512
#define SRV_IP "127.0.0.1"
#define SOCK_PORT 9100

#define symbols "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

void from_dec_to_other(int num, int base) {
    if (num) {
        int tmp = num%base;
        num = num/base;
        from_dec_to_other(num, base);
        printf("%c", symbols[tmp]);
    }
}

void print_result(int num) {
    printf("Result: \n");
    printf("binary: ");
    from_dec_to_other(num, 2);
    printf("\noct: ");
    from_dec_to_other(num, 8);
    printf("\nhex: ");
    from_dec_to_other(num, 16);
    printf("\n19th: ");
    from_dec_to_other(num, 19);
    printf("\n");
}

int main(void)
{
	struct sockaddr_in serverAddr, clientAddr;
	int sock, clientAddrLen = sizeof(clientAddr);
	char buf[MSG_LEN];

	printf("Server started\n");

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Socket error");
        exit(1);
    }

	//memset((char *)&server_addr, 0, sizeof(server_addr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SOCK_PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) {
        close(sock);
		perror("bind");
        exit(1);
    }


	printf("Server is ready to receive messages\n");

	while (1)
	{
		if (recvfrom(sock, buf, MSG_LEN, 0, (struct sockaddr*) &clientAddr, &clientAddrLen) == -1) {
			perror("recvfrom()"); 
            exit(1);
        }
		printf("Received packet from %s:%d\nData: %s\n\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buf);
        print_result(atoi(buf));
        
	}

	close(sock);
	return 0;
}
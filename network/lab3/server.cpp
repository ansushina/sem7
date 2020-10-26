#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <map>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <vector>
#include "threads.h"

#include "response.h"
#include "request.h"

#define MSG_LEN 512
#define SRV_IP "127.0.0.1"
#define SOCK_PORT 9111
#define THREADS 16
#define BUFFER_SIZE 10240
#define ROOT "/home/nastya"

#define OK 200
#define BAD_REQUEST 400
#define FORBIDDEN  403
#define NOT_FOUND  404
#define NOT_ALLOWED  405




void read_file( std::vector<char> &readedData,FILE* input) {
    unsigned char byte;
    readedData.clear();
    while (fread(&byte, sizeof(char), 1, input)) {
        readedData.push_back(byte);
    };
}

std::string parse_url(const std::string url, const std::string root) {
    std::string new_url(url);
    int pos = new_url.find("?");
    if (pos != std::string::npos) {
        new_url = new_url.substr(0, pos);
    }
    std::string path = root + new_url;
    return path;
}

std::string create_res(Request &req, const std::string root) {

    std::map<std::string, std::string> types = {
        {    "html", "text/html"},
        {    "js", "application/javascript"},
        {    "css", "text/css"},
        {    "jpg", "image/jpeg"},
        {    "jpeg", "image/jpeg"},
        {    "png", "image/png"},
        {    "gif", "image/gif"},
        {    "swf", "application/x-shockwave-flash"},
        {    "txt", "text/plain"},
    };

    std::vector<char> data;
    if (!req.get_ok()) {
        Response res(BAD_REQUEST);
        return res.get_string("", 0, data);
    }
    if (req.get_method() != "GET" && req.get_method() != "HEAD") {
        Response res(NOT_ALLOWED);
        return res.get_string("",0, data);
    }

    std::string path = parse_url(req.get_url(), root);

    if (path.find("../") != std::string::npos) {
        Response res(FORBIDDEN);
        return res.get_string("", 0, data);
    }

    bool isDir = false;
    struct stat s;
    if( stat(path.c_str(),&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            path += "index.html";
            isDir = true;
        }
    }

    FILE *f = fopen(path.c_str(), "rb");
    if (!f) {
        if (isDir) {
            Response res(FORBIDDEN);
            return res.get_string("",0, data);
        } else {
            Response res(NOT_FOUND);
            return res.get_string("",0, data);
        }
    }

    Response res(OK);

    read_file(data, f);
    fclose(f);

    int dotpos = path.rfind('.');
    std::string type = path;
    type.erase(0, dotpos+1);

    std::string cont_type = types[type];
    if (cont_type == "") {
        cont_type = "text/plain";
    }

    if (req.get_method() == "HEAD") {
        std::vector<char> nulldata; 
        return res.get_string(cont_type, data.size(), nulldata);
    }
    return res.get_string(cont_type, data.size(), data);
}


void handler(int sock) {
    int request;
    char buf[BUFFER_SIZE], *request_lines[3];
    char *file_name;

    request = recv(sock, buf, BUFFER_SIZE, 0);

    if (request < 0)
    {
        return;
        puts("Recv failed");
        close(sock);
        return;
    }
    else if (request == 0)
    {
        puts("Client disconnected upexpectedly.");
        close(sock);
        return;
    }
    printf("%s", buf);

    Request req(buf);
    std::string result = create_res(req, ROOT);
    std::cout << result;  
    send(sock, result.c_str(), result.size(), 0);

    close(sock);
}



int main(void)
{
    struct sockaddr_in serverAddr, clientAddr;
    int sock, new_socket;
    unsigned int clientAddrLen = sizeof(clientAddr);
    char buf[MSG_LEN];

    printf("Server started\n");

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("Socket error");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SOCK_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) {
        close(sock);
        perror("bind");
        exit(1);
    }

    printf("Bind ended\n");

    listen(sock, 1);
    printf("Server is listening...\n");

   
    // while(1)
    // {
    // new_socket = accept(sock, (struct sockaddr*) &clientAddr, &clientAddrLen);
    // handler(new_socket); 
    // }

    ThreadPool pool(THREADS);

    while ((new_socket = accept(sock, (struct sockaddr*) &clientAddr, &clientAddrLen))) {
           pool.enqueue(handler, new_socket);
    }

    //close(sock);
    return 0;
}

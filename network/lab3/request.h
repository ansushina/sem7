#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <map>
#include <cstring>
#include <string.h>
#include <iostream>

class Request {
public :
    Request(char* req) {
        char * elems[4];
        elems[0] = strtok(req, " \r\n");
        if (!elems[0]) {
            ok = false;
            return;
        }
        this->method = elems[0];
        elems[1] = strtok(NULL, " \r\n");
        if (!elems[1]) {
            ok = false;
            return;
        }
        this->url = elems[1];
        elems[2] = strtok(NULL, " \r\n");
        if (!elems[2]) {
            ok = false;
            return;
        }
        this->version = elems[2];
        while ((elems[3] = strtok(NULL, "\r\n"))) {
            std::string str = elems[3];
            int pos = str.find(": ");
            if (pos == std::string::npos){
                ok = false;
                return;
            }
            std::string token;
            token = str.substr(0, pos);
            str.erase(0, pos + 2);
            this->headers[token] = str;
        }

        ok = true;

        std::cout << "ok=true" << '\n';
        return;
    }

    std::string get_method() {
        return this->method;
    }
    std::string get_url() {
        return this->url;
    }
    std::string get_version() {
        return this->version;
    }
    std::map<std::string, std::string> get_headers() {
        return this->headers;
    }
    bool get_ok() {
        return this->ok;
    }
private:
    std::string method, url, version;
    std::map<std::string, std::string> headers;
    bool ok;
};

#endif // REQUEST_H

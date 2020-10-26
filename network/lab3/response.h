#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <map>

#include <vector>
#include <string>

class Response {
public:
    Response(int status){
        this->status = this->codes[status];
        this->main = ("HTTP/1.1 " + this->status + "\r\n" +
                "Connection: close\r\n" +
                      "Server: localhost\r\n"
                      );
    }

    std::string get_string(std::string cont_type, int cont_len, std::vector<char> data){
        if (this->status != this->codes[200]) {
            return main;
        }
        this->main += ("Content-Type: " + cont_type + "\r\n" +
                       "Content-Length: " + std::to_string(cont_len) + "\r\n\r\n");
        for (int i =0; i < data.size(); i++) {
             this->main += data[i];
        }
        return this->main;
    }
private:
    std::string status;
    std::string main;
    std::map<int, std::string> codes = {{200, "200 OK"},
                                 {400, "400 Bad Request"},
                                 {403, "403 Forbidden"},
                                 {404,"404 Not Found"},
                                 {405, "405 Method Not Allowed"}};
};


#endif // RESPONSE_H

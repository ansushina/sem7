#include<map>
#include<vector>
#include<string>
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <fstream>


class History {
public: 
    History(const char *filename) {
        this->read_from_file(filename);
        this->filename = filename;
    }

    void setHistory(std::string ip, std::string his) {
        this->read_from_file(this->filename.c_str());
        std::vector<std::string> his_vec = this->history_vec[ip];
        his_vec.push_back(his);
        this->history_vec[ip] = his_vec;
        this->write_in_file(this->filename.c_str());
    }

    void write_in_file(const char*  filename) {
        std::ofstream myfile;
        myfile.open(filename);
        std::map<std::string, std::vector<std::string>> copy = this->history_vec;
        for (std::pair<std::string, std::vector<std::string>> element : copy) {
            // Accessing KEY from element
            std::string ip = element.first;
            // Accessing VALUE from element.
            std::vector<std::string> his = element.second;
            myfile << ip << std::endl;
            for (int i = 0; i < his.size(); i++) {
                myfile << his[i] << std::endl;
            }
            myfile << std::endl;
        }
        myfile.close();
    }

    void read_from_file(const char*  filename) {
        std::ifstream myfile;
        myfile.open(filename);
        bool is_ip = true; 
        std::string ip;
        for( std::string line; std::getline(myfile, line ); )
        {
            if (line == "") {
                is_ip = true;
            } else if (is_ip) {
                ip = line;
                is_ip=false;
            } else {
                this->history_vec[ip].push_back(line);
            }
        } 
        myfile.close();
    }

    private: 
    std::string filename;
    std::map<std::string, std::vector<std::string>> history_vec;
};
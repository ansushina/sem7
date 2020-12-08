#ifndef HAFFMANCODER_HPP
#define HAFFMANCODER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include "node.hpp"

using namespace std;

class HaffmanCoder
{
public:
    HaffmanCoder(vector<unsigned char> s)
    {
        this->data = s;
        amounts.resize(256, 0);
        for(auto i: s) amounts[i]++;
        for (int i = 0; i < 256; i++) {
            if (amounts[i] > 0) {
                 graph.push(Node(i, amounts[i]));
            }
        }
        build();
        root.traversal_code("");
        cout << root.to_str();
        codes.resize(256);
        save_codes(root);
        cout << "OK!";
    }

    vector<unsigned char> code(){
        string bit_data;
        for (auto i: data) {
            string code = codes[i];
            for (auto j: code) {
                bit_data.push_back(j);
            }
        }

        vector<unsigned char> code_data;
        for (int i = 0; i < 256; i++){
//            code_data.push_back(i);
            std::string encoded_sym_bits = this->num_to_bits(amounts[i], 32);
            for (int sym_to_print = 0; sym_to_print < 4; sym_to_print++)
               {
                  int to_print = this->bit_to_nums(encoded_sym_bits.substr(sym_to_print*8, 8));
                  code_data.push_back(to_print);
            }

        }
        int i = 0;
        int last = 0;
        while (i < bit_data.size()) {
            int to_print;
            if (i + 8 >= bit_data.size()){
                last = i + 8 - bit_data.size();
                string a;
                for (int k =0; k < last; k++) {
                    a.push_back('0');
                }
                to_print = this->bit_to_nums(bit_data.substr(i, 8) + a);
            } else {
                to_print = this->bit_to_nums(bit_data.substr(i, 8));
            }
            code_data.push_back(to_print);
            i += 8;
        }
        code_data.push_back(last);
        return code_data;
    }
    string num_to_bits(int num, int size)
    {
        string bit_size_input;

        for (int j = size - 1; j > -1; j--)
            bit_size_input.push_back(((num >> j) & 1)+'0');

        return bit_size_input;
    }

    int bit_to_nums(std::string bits)
    {
        int num = 0;

        for (int c : bits)
            num = (num << 1) | (c - '0');

        return num;
    }

     void decode();


private:
    priority_queue<Node, vector<Node>, Node> graph;
    Node root;
    vector<string> codes;
    vector<int> amounts;

    vector<unsigned char> data;

    void build(){
        while(graph.size() > 1){
            Node n1 = graph.top();
            graph.pop();
            Node n2 = graph.top();
            graph.pop();

            Node *left = new Node(n1);
            Node *right = new Node(n2);

            Node center = Node(n1.sym + n2.sym, n1.count + n2.count, right, left);
            graph.push(center);
        }
        root = graph.top();
    }


    void save_codes(Node n) {
            if (n.left != 0 || n.right != 0) { // дерево таково, что либо есть оба ребенка либо нет ни одного
                    save_codes(*n.left);
                    save_codes(*n.right);
                } else {
                   codes[n.sym] = n.code;
                }
                return;
    }
};


#endif // HAFFMANCODER_HPP

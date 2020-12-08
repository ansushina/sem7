#ifndef HAFFMANDECODER_HPP
#define HAFFMANDECODER_HPP
#include "node.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>

class HaffmanDecoder
{
public:
    HaffmanDecoder(vector<unsigned char> s)
    {
        amounts.resize(256, 0);

        char sym;
        int bytes = 0;
        std::string decoded_sym_bits = "";

        for (int i = 0; i < 256 * 4; i++){
            sym = s[i];
            decoded_sym_bits += this->num_to_bits((unsigned)sym, 8);
            bytes++;
            if (bytes == 4)
            {
                int to_print = this->bit_to_nums(decoded_sym_bits);
                amounts[i/4] = to_print;
                decoded_sym_bits.clear();
                decoded_sym_bits = "";
                bytes = 0;
            }
        }
        for (int i = 256 * 4; i < s.size(); i++){
            this->data.push_back(s[i]);
        }
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

    vector<unsigned char> decode(){
        string bit_data;
        for (int i = 0; i < this->data.size() - 1; i++ ) {
            string byte = num_to_bits(data[i], 8);
            for (int j: byte){
                bit_data.push_back(j);
            }
        }

        int last = this->data[data.size() -1];

        vector<unsigned char> decoded_data;
        int i = 0;
        while (i < bit_data.size() - last) {
            Node *tmp = new Node(root);
            while(tmp->left && tmp->right) {
                if (bit_data[i] == '0')
                 {
                     tmp = tmp->right;
                 }
                 else
                 {
                     tmp = tmp->left;
                 }
                i++;
            }
            decoded_data.push_back(tmp->sym);
        }
        return decoded_data;
    }




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
};


#endif // HAFFMANDECODER_HPP

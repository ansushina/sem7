#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>

using namespace std;

struct Node
{
    Node(int sym=0, const int count = 0, Node *right= NULL, Node *left = NULL):
        sym(sym),
        count(count),
        code(""),
        right(right),
        left(left)
    {}

    Node(const Node &n):
        sym(n.sym),
        count(n.count),
        code(n.code),
        right(n.right),
        left(n.left)
    {}

    string code;
    int sym;
    int count;
    Node *right;
    Node *left;

    bool operator() (const Node& x, const Node& y) const {
            if (x.count == y.count) {
                return x.sym > y.sym;
            }
            return x.count > y.count;
        }

    string to_str() {
            ostringstream x;
            if (left != 0 || right != 0) { // дерево таково, что либо есть оба ребенка либо нет ни одного
              //  x << "\t\"" << code << ": " << sym << "[" << count << "]\" -> \""  << left->code << ": " << left->sym << "[" << left->count << "]\";\n";
                x << left->to_str();
               // x << "\t\"" << code << ": " << sym << "[" << count << "]\" -> \""  << right->code << ": " << right->sym << "[" << right->count << "]\";\n";
                x << right->to_str();
            } else {
                //x << "\t\"" << code << ": " << sym << "[" << count << "]\"";
                x << "\t" << sym << ": " << code << " \t[" << count << "] \n";
            }
            return x.str();
        }

    void traversal_code(string code) {
            this->code = code;
            if (left != 0 || right != 0) {
                left->traversal_code(code + "1");
                right->traversal_code(code + "0");
            }
        }
};

#endif // NODE_HPP

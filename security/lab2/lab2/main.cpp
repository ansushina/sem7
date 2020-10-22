#include <iostream>
#include "rotor.h"
#include "reflector.h"
#include "enigma.h"
#include <stdio.h>
#include <vector>
using namespace std;

int read_file( vector<int> &readedData,const char* filename) {
    unsigned char byte;
    FILE * input = fopen(filename, "rb");
    if(!input) {
     cout << "file does not exist.....";
     return 1;
    }
   readedData.clear();
    while (fread(&byte, sizeof(char), 1, input)) {
        readedData.push_back(int(byte));
    };
    fclose(input);
    return 0;
}

void to_file( vector<int> data, const char* filename) {
    FILE * output = fopen(filename, "wb");
    for (int i = 0; i < data.size(); i++) {
        unsigned char byte = char( data[i]);
        fwrite(&byte, sizeof(char), 1, output);
    }
    fclose(output);
}

int main()
{
    std::string  filename;

    cout << "Input filename:";
    cin >> filename;
    vector<int> str;

    Enigma e;
    char efile[] = "enigma.state";
    e.saveState(efile);


    int error = read_file(str, filename.c_str());
    if (error){
        return -1;
    }

//    cout << "\nReaded:\n";
//    for (int i = 0 ; i < str.size(); i++) {
//        cout << char(str[i]);
//    }
//    cout << "\n";

    vector<int> a =  e.encode(str);

//    cout << "\nEncoded\n";
//    for (int i = 0 ; i < a.size(); i++) {
//        cout <<char(a[i]);
//    }
//    cout << "\n";

    to_file(a, (filename + ".encoded").c_str());
    Enigma e1(efile);

    vector<int> str1;
    read_file(str1,  (filename + ".encoded").c_str());

//    cout << "\nReaded:\n";
//    for (int i = 0 ; i < str.size(); i++) {
//        cout << char(str1[i]);
//    }
//    cout << "\n";

    vector<int> b = e1.encode(str1);

//    cout << "\nDecoded:\n";
//    for (int i = 0 ; i < b.size(); i++) {
//        cout << char(b[i]);
//    }
//    cout << "\n";

    to_file(b, (filename + ".decoded").c_str());

    return 0;
}

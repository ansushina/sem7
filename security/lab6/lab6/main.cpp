#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include "node.hpp"
#include "haffmancoder.hpp"
#include "haffmandecoder.hpp"
#include <locale.h>
#include <dirent.h>

using namespace std;


int read_file( vector<unsigned char> &readedData, const char* filename) {
    unsigned char byte;
    FILE * input = fopen(filename, "rb");
    if(!input) {
     cout << "file does not exist.....";
     return 1;
    }
    readedData.clear();
    while (fread(&byte, sizeof(char), 1, input)) {
        readedData.push_back(byte);
    };
    fclose(input);
    return 0;
}

void to_file( vector<unsigned char> data, const char* filename) {
    FILE * output = fopen(filename, "wb");
    for (int i = 0; i < data.size(); i++) {
        unsigned char byte =  data[i];
        fwrite(&byte, sizeof(char), 1, output);
    }
    fclose(output);
}

int main()
{
    setlocale(LC_CTYPE, "");
    cout << " Input filename: ";
    string fname;

    cin >> fname;
    vector<unsigned char> data;
    read_file(data, fname.c_str());

    cout << "Data was read" << endl;
    if (data.size() < 3){
        cout << "TOO LOW DATA TO CODE" << endl;
        return(0);
    }

    HaffmanCoder h(data);
    vector<unsigned char> data_coded =  h.code();
    to_file(data_coded, (fname + ".encoded").c_str());

    cout << "Data was encoded" << endl;

    vector<unsigned char> data_readed;
    read_file(data_readed, (fname + ".encoded").c_str());

    cout << "Encoded data was read" << endl;
    HaffmanDecoder dec(data_readed);

    vector<unsigned char> data_decoded = dec.decode();

    to_file(data_decoded, (fname + ".decoded").c_str());
    cout << "Data was decoded" << endl;

    return 0;
}

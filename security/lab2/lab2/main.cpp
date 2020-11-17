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
    //Ввод имени файла
    std::string  filename;
    cout << "Input filename:";
    cin >> filename;


    // Создаем новую энигму и сохраняем ее состояние
    Enigma e;
    char efile[] = "enigma.state";
    e.saveState(efile);


    //Читаем файл
    vector<int> str;
    int error = read_file(str, filename.c_str());
    if (error){
        return -1;
    }

    // шифруем файл
    vector<int> a =  e.encode(str);
    to_file(a, (filename + ".encoded").c_str());

    //Декодируем файл

    //Новая энигма со старым состоянием
    Enigma e1(efile);

    //Читаем закодированный файл
    vector<int> str1;
    read_file(str1,  (filename + ".encoded").c_str());

    // Декодируем и записываем в файл
    vector<int> b = e1.encode(str1);
    to_file(b, (filename + ".decoded").c_str());

    return 0;
}

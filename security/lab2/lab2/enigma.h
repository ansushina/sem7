#ifndef ENIGMA_H
#define ENIGMA_H

#include "rotor.h"
#include "reflector.h"
#include <vector>


const int N_ROTORS = 3;



class Enigma
{
public:
    Enigma(){
        this->reflector =  Reflector();

        for (int i = 0; i < N_ROTORS; i++) {
            this->rotors.push_back(Rotor());
        }
    }
    Enigma(char * filename){

        FILE *f = fopen(filename, "rb");
        std::vector<int> readedData;
        unsigned char byte;

        for (int i = 0; i < N_ROTORS; i++) {
            readedData.clear();
             for (int i = 0; i < BASE_NUM; i++) {
                 fread(&byte, sizeof(char), 1, f);
                 readedData.push_back(int(byte));
             }
             rotors.push_back(Rotor(readedData));
        }
         readedData.clear();
         for (int i = 0; i < BASE_NUM; i++) {
             fread(&byte, sizeof(char), 1, f);
             readedData.push_back(int(byte));
         }
         reflector= Reflector(readedData);
         fclose(f);
    }


    std::vector<int> encode(const std::vector<int> str) {
        std::vector<int> encodeStr =  std::vector<int>(str);

        for (int i = 0; i < str.size(); i++){
            encodeStr[i] = codeOneSymbol(str[i]);
        }
        return encodeStr;
    }

    void saveState(char *filename) {
        FILE *f = fopen(filename, "wb");

        std::vector<int> base = std::vector<int>(BASE_NUM);
        for (int i = 0; i < rotors.size(); i++) {
            rotors[i].SaveConnections(base);
            for (int i = 0; i < base.size(); i++) {
                unsigned char byte = char( base[i]);
                fwrite(&byte, sizeof(char), 1, f);
            }
        }
        reflector.SaveConnections(base);
        for (int i = 0; i < base.size(); i++) {
            unsigned char byte = char( base[i]);
            fwrite(&byte, sizeof(char), 1, f);
        }
        fclose(f);
    }

private:
    std::vector<Rotor> rotors;
    Reflector reflector;

    int codeOneSymbol(int s) {
        for (int i = 0; i < rotors.size(); i++) {
            s = this->rotors[i].get(s);
        }

        s = this->reflector.get(s);

        for (int i = rotors.size()-1; i >= 0; i--) {
            s = this->rotors[i].getIndex(s);
        }

        for (int i = 0, res = 0; i < rotors.size() && res == 0; i++){
            res = this->rotors[i].Rotate();
        }
        return s;
    }
};

#endif // ENIGMA_H

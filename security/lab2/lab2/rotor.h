#ifndef ROTOR_H
#define ROTOR_H
#include <vector>
#include <cstdlib>
#include <algorithm>

const int BASE_NUM = 256;

class Rotor
{
public:
    Rotor() {
        CreateConnections();
    }
    Rotor(std::vector<int> base){
        SetConnections(base);
    }

    void SaveConnections(std::vector<int> &base) {
        for (int i = 0; i < BASE_NUM; i++) {
            base[i] = this->connections[i];
        }
    }

    int get(int i) {
        return this->connections[i];
    }

    int getIndex(int value) {
        for (int i = 0; i < BASE_NUM; i++) {
            if (this->connections[i] == value)
                return i;
        }
        return 0;
    }

    int Rotate() {
        int first = this->connections[0];

        for (int i = 0; i < BASE_NUM-1; i++) {
            this->connections[i] = this->connections[i+1];
        }
        this->connections[BASE_NUM-1] = first;
        this->rotations = (this->rotations+1) % BASE_NUM;
        return this->rotations;
    }

private:
   std::vector<int>  connections = std::vector<int>(BASE_NUM);
   int rotations = 0;

   void CreateConnections() {
       for (int i = 0; i < BASE_NUM; i++) {
           this->connections[i] = i;
       }
       std::sort (connections.begin(), connections.end(), [](int a, int b) -> bool
       {
           return std::rand() % 2 == 0;
       });
   }
   void SetConnections(std::vector<int> base){
       for (int i = 0; i < BASE_NUM; i++) {
           this->connections[i] = base[i];
       }
   }

};

#endif // ROTOR_H

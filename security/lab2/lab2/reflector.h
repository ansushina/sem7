#ifndef REFLECTOR_H
#define REFLECTOR_H


#include<vector>

class Reflector
{
public:
    Reflector(){
       CreateConnections();
   }
   Reflector(std::vector<int> base){
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


private:
  std::vector<int>  connections = std::vector<int>(BASE_NUM);
  int rotations = 0;

  void CreateConnections() {
      for (int i = 0; i < (BASE_NUM)/2; i++) {
          this->connections[i] = (BASE_NUM)/2 + i;
          this->connections[BASE_NUM/2 + i] = i;
      }
  }
  void SetConnections(std::vector<int> base){
      for (int i = 0; i < BASE_NUM; i++) {
          this->connections[i] = base[i];
      }
  }

};

#endif // REFLECTOR_H

#include <iostream>
#include <string>
#include  "functions.h"
#include "rsa.h"

using namespace std;

int main()
{

    std::string in_file;
    std::string keyfile = "key.txt";
    cout << "Hello World!" << endl;
    cout << "Input filename: ";
    cin >> in_file;

    Rsa rsa;

    rsa.generate_keys();
    rsa.save_keys_to_file(keyfile);

    rsa.encode_file(in_file, in_file + ".encoded");

    Rsa rsa2;

    rsa2.load_keys_from_file(keyfile);
    rsa2.decode_file(in_file + ".encoded", in_file + ".decoded");

    return 0;
}

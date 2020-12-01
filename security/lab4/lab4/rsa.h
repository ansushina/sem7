#ifndef RSA_H
#define RSA_H

#include <vector>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "functions.h"
int generate_prime();

int generate_coprime(int n);

int modular_inverse(int n, int mod);

bool rabin_miller(int n);

int log_power(int n, int p, int mod);


class Rsa {
public:
    Rsa(){
      srand(time(NULL));
    }

    void generate_keys() {
        int p,q;

        p = generate_prime();
        q = generate_prime();

        int n = p*q;
        int phi = (p - 1) * (q - 1);
        int e = generate_coprime(phi);
        int d = modular_inverse(e, phi);

        this->m_public_key = std::make_pair(e, n);
        this->m_private_key = std::make_pair(d, n);
    }


    void save_keys_to_file(std::string filename)
    {
        std::ofstream out(filename, std::ios::out);

        out << m_private_key.first << " " << m_private_key.second << std::endl;
        out << m_public_key.first << " " << m_public_key.second << std::endl;

        out.close();
    }

    void load_keys_from_file(std::string filename)
    {
        std::ifstream in(filename, std::ios::in);
        std::string buffer;

        getline(in, buffer);
        std::string first, second;
        std::stringstream file_buffer(buffer);

        file_buffer >> first;
        file_buffer >> second;

        this->m_private_key = std::make_pair(std::stoi(first), std::stoi(second));

        getline(in, buffer);
        std::stringstream file_buffer1(buffer);

        file_buffer1 >> first;
        file_buffer1 >> second;

        this->m_public_key = std::make_pair(std::stoi(first), std::stoi(second));

        in.close();
    }

    void encode_file(std::string filename, std::string output_filename)
    {
        std::ifstream in(filename, std::ios::binary | std::ios::in);
        std::ofstream out(output_filename, std::ios::binary | std::ios::out);

        char sym;
        while (in.get(sym))
        {
            int encoded_sym = this->encode_sym(sym);

            std::string encoded_sym_bits = this->num_to_bits(encoded_sym, 32);
            for (int sym_to_print = 0; sym_to_print < 4; sym_to_print++)
            {
                int to_print = this->bit_to_nums(encoded_sym_bits.substr(sym_to_print*8, 8));
                out << (char)to_print;
            }
        }

        in.close();
        out.close();
    }

    void decode_file(std::string filename, std::string output_filename)
    {
        std::ifstream in(filename, std::ios::binary | std::ios::in);
        std::ofstream out(output_filename, std::ios::binary | std::ios::out);

        char sym;
        int bytes = 0;
        std::string decoded_sym_bits = "";

        while (in.get(sym))
        {
            decoded_sym_bits += this->num_to_bits((unsigned)sym, 8);
            bytes++;

            if (bytes == 4)
            {
                int to_print = this->decode_sym(this->bit_to_nums(decoded_sym_bits));
                out << (char)to_print;

                decoded_sym_bits.clear();
                decoded_sym_bits = "";
                bytes = 0;
            }
        }

        in.close();
        out.close();
    }

private:
    std::pair<int, int> m_private_key;
    std::pair<int, int> m_public_key;

    int encode_sym(int value)
    {
        return log_power(value, this->m_public_key.first, this->m_public_key.second);
    }

    int decode_sym(int value)
    {
        return log_power(value, this->m_private_key.first, this->m_private_key.second);
    }

    std::string num_to_bits(int num, int size)
    {
        std::string bit_size_input;

        for (int j = size - 1; j > -1; j--)
            bit_size_input.push_back(((num >> j) & 1) + '0');

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

#endif // RSA_H

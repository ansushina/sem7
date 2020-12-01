#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <ctime>
#include <random>
#define LIMIT 100

int gcd(int a, int b)
{
    while (b)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int generate_coprime(int n)
{
    int generated = rand() % LIMIT;
    while (gcd(n, generated) != 1)
        generated = rand() % LIMIT;
    return generated;
}

std::pair<int, int> euclid_extended(int a, int b)
{
    if(!b)
        return std::make_pair(1, 0);

    auto result = euclid_extended(b, a % b);
    return std::make_pair(result.second, result.first - (a / b) * result.second);
}

int modular_inverse(int n, int mod)
{
    int inverse = euclid_extended(n, mod).first;
    while(inverse < 0)
        inverse += mod;
    return inverse;
}

int log_power(int n, int p, int mod)
{
    int result = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            result = (1LL * result * n) % mod;
        n = (1LL * n * n) % mod;
    }
    return result;
}

bool rabin_miller(int n)
{
    bool ok = true;

    for (int i = 1; i <= 5 && ok; i++)
    {
        int a = rand() + 1;
        int result = log_power(a, n - 1, n);
        ok &= (result == 1);
    }

    return ok;
}


int generate_prime()
{
    int generated = rand() % LIMIT;
    while (!rabin_miller(generated))
        generated = rand() % LIMIT;

    return generated;
}

#endif

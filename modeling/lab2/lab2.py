import matplotlib.pyplot as plt
from scipy.stats import uniform, norm, erlang
import numpy as np
import math

def erlang_cdf(k, l, x):
    if x < 0:
        return 0
    return 1 - (1 + l * x) * np.exp( - l * x);

def erlang_pdf(k, l , x):
    if x < 0: 
        return 0
    return pow(l, k+1) * pow(x,k) *np.exp(- l * x) / math.factorial(k);


def main():
    a = 0
    b = 5
    x = np.linspace(a-1, b+1, 100)
    dist = uniform(loc=a, scale=abs(a - b))
    figure, ax = plt.subplots(figsize=(9, 9))
    plt.subplot(221)
    plt.title("Функция распределения")
    plt.plot(x, dist.cdf(x), color='r', label=r'F({0}, {1})'.format(a, b))
    plt.legend()

    plt.subplot(222)
    plt.title("Функция плотности распределения")
    plt.plot(x, dist.pdf(x), color='b', label=r'f({0}, {1})'.format(a, b))
    plt.legend()

    dist = erlang(a=2)
    plt.subplot(223)
    plt.title('Функция распределения')
    cdf = [erlang_cdf(2, 2, i) for i in x]
    plt.plot(x, cdf, color='r', label=r'F({0}, {1})'.format(a, b))
    plt.legend()

    plt.subplot(224)
    plt.title('Функция плотности распределения')
    pdf = [erlang_pdf(2,2,i) for i in x]
    plt.plot(x, pdf , color='b', label=r'f({0}, {1})'.format(a, b))
    plt.legend()
    
    plt.show()

if __name__ == '__main__':
    main()
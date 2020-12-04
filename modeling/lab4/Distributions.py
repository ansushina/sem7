  
from numpy.random import gamma, normal
import random
import numpy as np
import math

class UniformDistribution:
    def __init__(self, a: float, b: float):
        self.a = a
        self.b = b

    def generate(self):
        return self.a + (self.b - self.a) * random.random()



class ErlangDistribution:
    def __init__(self, k, l):
        self.l = l
        self.k = k

    def _erlang_pdf(self, x):
        if x < 0: 
            return 0
        return (pow(self.l, self.k+1) * 
                pow(x, self.k) * 
                np.exp(- self.l * x) / 
                math.factorial(self.k))
    def _erlang_cdf(self, x):
        if x < 0:
            return 0
        return 1 - (1 + self.l * x) * np.exp( - self.l * x)


    def generate(self):
        # return self._erlang_cdf(random.random())
        return gamma(self.k, self.l)
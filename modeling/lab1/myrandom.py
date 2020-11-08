# Класс, реализующий простой рандомайзер
# Для генерации случайных чисел используется Линейный конгруэнтный метод 

class MyRandom:
    def __init__(self):
        self.current = 10
        self.m = 2.**31
        self.a = 1664525
        self.c = 1013904223

    def get_number(self, low=0, high=100):
        self.current = (self.a * self.current + self.c) % self.m
        result = int(low + self.current % (high - low))
        return result

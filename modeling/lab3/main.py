import random
from prettytable import PrettyTable
from numpy import linalg

def get_Kolmogorov_coeffs(matrix):
    n = len(matrix)

    return [
        [matrix[j][i] if j != i else -sum(matrix[i]) for j in range(n)]
        if i != (n - 1) else [1 for i in range(n)]
        for i in range(n)
        ]


def get_limit_probabilities(matrix):
    coeffs = get_Kolmogorov_coeffs(matrix)
    return linalg.solve(coeffs, [0 if i != (len(matrix) - 1) else 1 for i in range(len(matrix))]).tolist()


def calculate(matrix):
    limit_p = [round(x, 4) for x in get_limit_probabilities(matrix)]
    return limit_p


def print_matrix(matrix):
    print(" ");
    print("Матрица: ")
    table = PrettyTable()
    names = []
    names.extend([("s" +str(i + 1)) for i in range(len(matrix))])
    table.field_names = names
    for i in range(len(matrix)):
        tmp = [item for item in matrix[i]]
        table.add_row(tmp)
    print(table)
    print(" ")


def print_results(results_p):
    print("Результат:")
    table = PrettyTable()
    table.add_column("Состояния", [("s" + str(i + 1)) for i in range(len(results_p))])
    table.add_column("Предельные вероятности", results_p)
    print(table)

def generate_matrix(size):
    return [
        [round(random.random(), 4) if i != j else 0.00 for j in range(size)]
        for i in range(size)
    ]


if __name__ == '__main__':
    random.seed()
    system_size = int(input("Введите количество состояний системы: "))
    if (system_size > 10 or system_size <= 0):
        print("Количество состояний системы должно быть от 1 до 10.")
        exit(1);
    matrix = generate_matrix(system_size)
    print_matrix(matrix)
    results_p = calculate(matrix)
    print_results(results_p)
    



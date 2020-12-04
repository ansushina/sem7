from Modeller import Modeller
from prettytable import PrettyTable

if __name__ == '__main__':
    a, b = 0, 10

    er_k, er_lambda = 2, 2

    total_tasks = 10000
    repeat_probality= 0.99 # количество возвращаемых 
    step = 0.01


    model = Modeller(a, b, er_k, er_lambda, repeat_probality)
    result1  = model.event_based_modelling(total_tasks)
    model2 = Modeller(a, b, er_k, er_lambda, repeat_probality)
    result2 = model2.time_based_modelling(total_tasks, step)
    
    table = PrettyTable()
    table.add_column("Метод", ["Событийный", "Пошаговый"])
    table.add_column("Обработанные запросы", [result1[0], result2[0]])
    table.add_column("Возвращенные запросы", [result1[1], result2[1]])
    table.add_column("Мах размер очереди", [result1[2], result2[2]])
    table.add_column("Время работы", [result1[3], result2[3]])
    print(table)

    



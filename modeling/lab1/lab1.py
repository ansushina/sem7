from prettytable import PrettyTable
from myrandom import MyRandom
from itertools import islice

COUNT = 10000

def table_rand():
    numbers = set()
    with open('digits.txt') as file: 
        line_num = 0
        lines = islice(file, line_num, None)
        for l in lines:
            numbers.update(set(l.split(" ")[1:-1]))
            line_num += 1
            if len(numbers) >= 3* COUNT + 1:
                break
        numbers.remove("") 
        numbers = list(numbers)[:3*COUNT]
    one_digit = [int(i)%10 for i in numbers[:COUNT]]
    two_digits = [int(i)%90 + 10 for i in numbers[COUNT:COUNT*2]]
    three_digits = [int(i)%900 + 100 for i in numbers[COUNT*2:3*COUNT]]
    return one_digit, two_digits, three_digits

def alg_rand():
    random = MyRandom()
    one_digit = [random.get_number(0, 10) for i in range(COUNT)]
    two_digits = [random.get_number(10, 100) for i in range(COUNT)]
    three_digits = [random.get_number(100, 1000) for i in range(COUNT)]
    return  one_digit, two_digits, three_digits

def calc_hi(arr, n, start, end): 
    tab = [0 for i in range(start + end)]
    for i in range(n):
        tab[arr[i]] += 1
    s = 0
    for i in tab:
        s += i*i
    return s * (end-start) / n - n 
    

def main():
    numbers = [i for i in range(10)]
    table_tbl = PrettyTable()
    one_tbl, two_tbl, three_tbl = table_rand()

    table_tbl.add_column("№", numbers)
    table_tbl.add_column('1 разряд', one_tbl[:10])
    table_tbl.add_column('2 разряд', two_tbl[:10])
    table_tbl.add_column('3 разряд', three_tbl[:10])
        
    one_alg, two_alg, three_alg = alg_rand()
    table_tbl.add_column('1 разряд', one_alg[:10])
    table_tbl.add_column('2 разряд', two_alg[:10])
    table_tbl.add_column('3 разряд', three_alg[:10])
    
    table_tbl.add_row(['коэф',
                       calc_hi(one_tbl, 10000, 0 , 10),
                       calc_hi(two_tbl, 10000,10, 100),
                       calc_hi(three_tbl, 10000, 100, 1000),
                       calc_hi(one_alg, 10000, 0 , 10),
                       calc_hi(two_alg, 10000, 10, 100),
                       calc_hi(three_alg, 10000, 100, 1000)])
    print("\t\t\t    --Табличный метод--\t\t\t\t\t     --Алгоритмический метод--")

    print(table_tbl)
    

if __name__ == '__main__':
    main() 


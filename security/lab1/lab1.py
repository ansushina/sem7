# coding=utf-8
from installer import check_checksum
import sys


# Перевод в трочно-симметричную систему из десятичной и обратно.

# Калькулятор с графическим интерфейсом, выполняющий перевод чисел из
# десятичной системы счисления в троично-симметричную и обратно.
# Так же окно имеет меню, выполняющее очистку полей, повторяющее математические
# действия и выводящее информацию об авторе и о программе.
# Сушина АД ИУ7-21б

# root - окно
# m, m1-m3 - меню и выпадающее меню
# c1 - канвас, определяющий форму окна
# l1-l3 - надписи в окне(пояснения для пользователя)
# rb1,rb2 - кнопки выбора способа перевода
# e1,e2 - онка ввода и вывода значений
# arr,m - кнопки экранной клавиатуры
# btn - кнопка "Решить"
# a - текст, введенный пользователем(в функциях)
# t1,t2 - информация для пользователя
# k,t,x,v,l,n- рабочие переменные

# Варианты тестовых данных:
# исходное число: -14 полученное число: -+++
# исходное число: 8 полученное число: +0-
# исходное число: -0+ полученное число: -8
# исходное число: +--- полученное число: 14

from tkinter import *
from tkinter import messagebox as mb


# Функция обработки нажатия кнопок экранной клавиатуры
def f(x):
    e1.insert(END, x)


def proverka1():
    # Проверка введенного числа(троично-сииметричная)
    v = e1.get()
    if len(v) == 0:
        return 0
    if v.count('+') + v.count('-') + v.count('0') == len(v):
        return 1
    else:
        return 0


def perevod1(a):
    # Перевод из трочно-симметричной в десятичную
    k = 0
    v = 0
    for i in range(len(a) - 1, -1, -1):
        if a[i] == '-':
            v += (-1) * 3 ** k
        elif a[i] == '+':
            v += 3 ** k
        k += 1
    e2.insert(0, str(v))


def proverka2():
    # Проверка введенного числа(целое десятичное)
    v = e1.get()
    if v[0] == '-':
        v = v.replace('-', '')
    if v.isdigit():
        return 1
    else:
        return 0


def perevod2(a):
    # Перевод из десятичой в троично-симметричную
    v = ''
    if a < 0:
        # Для отрицательных чисел
        t = abs(a)
        while t > 0:
            x = t % 3
            t = t // 3
            if x == 2 and t != 0:
                v += '-'
                t += 1
            elif x == 2 and t == 0:
                v += '-+'
            elif x == 1:
                v += '+'
            else:
                v += '0'
        k = ''
        for i in range(len(v) - 1, -1, -1):
            if v[i] == '-':
                k += '+'
            elif v[i] == '+':
                k += '-'
            else:
                k += '0'
    elif a == 0:
        # Для нуля
        k = '0'
    else:
        # Для положительных чисел
        while a > 0:
            x = a % 3
            a = a // 3
            if x == 2 and a != 0:
                v += '-'
                a += 1
            elif x == 2 and a == 0:
                v += '-+'
            elif x == 1:
                v += '+'
            else:
                v += '0'
        k = ''
        for i in range(len(v) - 1, -1, -1):
            k += v[i]
    e2.insert(0, k)


def btnclicked():
    # Нажатие кнопки "Решить"
    e2.delete(0, END)
    l1 = int(l.get())
    if l1 == 0:
        mb.showerror('Невозможно выполнить', 'Не выбран вид перевода.')
    elif l1 == 1:
        if proverka1():
            v = e1.get()
            perevod1(v)
        else:
            mb.showerror('Невозможно выполнить', 'Некорректный ввод исходного\
 числа.')
    elif l1 == 2:
        if proverka2():
            v = int(e1.get())
            perevod2(v)
        else:
            mb.showerror('Невозможно выполнить', 'Некорректный ввод исходного\
 числа.')


# Функции обработки первой вкладки меню (Очистить)
def o1():
    e1.delete(0, END)


def o2():
    e2.delete(0, END)


def o3():
    e1.delete(0, END)
    e2.delete(0, END)


# Функции обработки второй вкладки меню (Перевести)
def p1():
    e2.delete(0, END)
    if proverka1():
        v = e1.get()
        perevod1(v)
    else:
        mb.showerror('Невозможно выполнить', 'Некорректный ввод исходного\
 числа.')


def p2():
    e2.delete(0, END)
    if proverka2():
        v = int(e1.get())
        perevod2(v)
    else:
        mb.showerror('Невозможно выполнить', 'Некорректный ввод исходного\
 числа.')


# Функции обработки третей вкладки меню (Инфо)
def i1():
    t1 = '''Переводчик с графическим интерфейсом, выполняющий перевод
чисел из десятичной системы счисления в троично-симметричную
и обратно. Так же окно имеет меню, выполняющее очистку полей,
повторяющее математические действия и выводящее информацию
об авторе и о программе.
Переводчик работает только с целыми числами в обоих
системах счисления. Ввод любых других чисел или букв
калькулятор воспримет как ошибку и выдаст ссответсвующее
сообщение.'''
    mb.showinfo('Информация о программе', t1)


def i2():
    t2 = '''Сушина АД ИУ7-21б
Московский Государственный Технический Университет
имени Н.Э. Баумана.
2018'''
    mb.showinfo('Информация об авторе', t2)


if not check_checksum("license.key"):
    print("You don't have a license!")
    mb.showerror("error", "You don't have a license!")
    sys.exit()
else:

    # Создание окна
    root = Tk()
    root.title('Переводчик из 3-симметр сс в 10 сс')

    # Меню
    m = Menu(root)
    m1 = Menu(m)
    m.add_cascade(label='Очистить', menu=m1)
    m1.add_command(label='первое поле', command=o1)
    m1.add_command(label='второе поле', command=o2)
    m1.add_command(label='оба поля', command=o3)
    m2 = Menu(m)
    m.add_cascade(label='Перевести', menu=m2)
    m2.add_command(label='из троично-симметричной в десятичную', command=p1)
    m2.add_command(label='из десятичной в троично-симметричную', command=p2)
    m3 = Menu(m)
    m.add_cascade(label='Инфо', menu=m3)
    m3.add_command(label='о программе', command=i1)
    m3.add_command(label='об авторе', command=i2)

    # Основа
    root.config(menu=m)
    c1 = Canvas(width=350, height=230)
    c1.pack()

    # Кнопки выбора способа перевода
    l = IntVar()
    l1 = Label(root, text='Выберите вид перевода:')
    l1.place(x=30, y=70)
    rb1 = Radiobutton(root, text='из троично-симметричной\n в десятичную', \
                      variable=l, value=1)
    rb2 = Radiobutton(root, text='из десятичной\n в троично-симметричную', \
                      variable=l, value=2)
    rb1.place(x=10, y=90)
    rb2.place(x=10, y=130)

    # Окна ввода и вывода значений и их описание
    l2 = Label(root, text='Исходное число:')
    l3 = Label(root, text='Полученное число:')
    l2.place(x=100, y=10)
    l3.place(x=85, y=40)
    v = StringVar()
    e1 = Entry(root, textvariable=v, justify=RIGHT)
    e1.place(x=200, y=10)
    e2 = Entry(root, justify=RIGHT)
    e2.place(x=200, y=40)

    # Экранная клавиатура для ввода цифр нажатием кнопок
    m = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '0', '-']
    arr = []
    k = 40
    for i in range(12):
        arr.append(Button(root, text=m[i], command=lambda i=i: f(m[i])))
        n = i % 3
        if n == 0:
            k += 30
        arr[i].place(x=200 + 55 * n, y=k)

    # Кнопка "Решить"
    btn = Button(root, text='Решить', command=btnclicked)
    btn.place(x=240, y=190)

    ##btn1 = Button(root,text = 'Очистить все',command =

    root.mainloop()

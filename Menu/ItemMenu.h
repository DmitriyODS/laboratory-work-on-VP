#ifndef COSMODROME_ITEMMENU_H
#define COSMODROME_ITEMMENU_H

#include <iostream>
#include <string>
#include <functional>

using std::string;

// описываем тип функции
// которая будет передаваться пункту меню
// эта функция будет возвращать код возврата
// а принимать номер пункта, под которым она находится
// сделаем это через класс function
// это будет аналогично строке, только позволит работать
// с лямбда функциями
// using FuncExec = int (*)(int);
using FuncExec = std::function<int(int)>;

/*
 * Класс который описывает объект пункта меню
 */
class ItemMenu {
public:
    // удаляем конструктор по умолчанию
    ItemMenu() = delete;

    // реализуем оператор присваивания
    ItemMenu &operator=(const ItemMenu &itemMenu);

    // главный конструктор принимающий
    // название пункта и запускаемую функцию
    ItemMenu(string name, FuncExec func);

    // конструктор копирования
    ItemMenu(const ItemMenu &itemMenu);

    // метод запуска заложенной функции
    // возвращает значение, которое вернула функция
    // на вход подаётся номер выбранного пункта
    int exec(int selected) const;

    // перегруженный оператор вывода
    // делаем его дружественным
    friend std::ostream &operator<<(std::ostream &out, const ItemMenu &itemMenu);

    // перегружаем оператор исполнения
    // на вход подаётся номер выбранного пункта
    // тоже делаем константным
    int operator()(size_t selected) const;

    // константный метод
    // печати на экран
    // принимает поток вывода (может принимать)
    void print(std::ostream &out = std::cout) const;

private:
    string m_name{};
    FuncExec m_func_exec{};
};


#endif //COSMODROME_ITEMMENU_H

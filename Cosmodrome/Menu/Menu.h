#ifndef COSMODROME_MENU_H
#define COSMODROME_MENU_H

#include <string>
#include <vector>
#include <iostream>
#include <ItemMenu.h>
#include <consoleUtils.h>

using std::string;

// описываем тип вектора
// который будет хранить наши пункты меню
using ItemList = std::vector<ItemMenu>;

/*
 *  ласс меню - объекты данного класса
 * будут представл€ть из себ€ меню пользовател€
 * которое будет содержать запускаемые объекты
 * и позвол€ть оперировать ими (запуска€)
 * через единный интерфейс
 */
class Menu {
public:
    // удал€ем конструктор по умолчанию
    Menu() = delete;

    // удал€ем оператор присваивани€
    Menu &operator=(const Menu &) = delete;

    // создаЄм конструктор, который принимает заголовок меню
    // и вектор функций
    Menu(string title, ItemList itemList);

    // создаЄм метод печати пунктов на экране
    // который может принимать поток вывода
    void print(std::ostream &out = std::cout) const;

    // метод устанавливающий выбранный пункт меню
    void selectItem(int selected);

    // метод запуска пункта меню
    // возвращает код возврата вызванной функции
    int execSelected() const;

    // перегрузка оператора исполнени€
    // тоже делаем константным
    int operator()() const;

    // дружественна€ функци€ вывода
    friend std::ostream &operator<<(std::ostream &out, const Menu &menu);

    // дружественна€ функци€ ввода
    friend std::istream &operator>>(std::istream &in, Menu &menu);

    // получить выбранный пункт
    int getSelected() const;

    // метод добавл€ющий пункт меню в конец
    void addItem(ItemMenu itemMenu);

    // метод добавл€ющий пункт меню на заданную позицию
    void addItemByIndex(ItemMenu itemMenu, int index);

private:
    string m_title{};
    ItemList m_item_lst{};
    int m_selected{-1};
};

// функци€ возвращает нужный валидатор дл€ ввода
// принимает кол - во эелемнтов в меню
ValidateNum getValidate(int count_items);


#endif //COSMODROME_MENU_H

#include "Menu.h"

Menu::Menu(string title, ItemList itemList)
        : m_title(std::move(title)), m_item_lst(std::move(itemList)) {}

void Menu::print(std::ostream &out) const {
    out << m_title << std::endl;
    out << "============================\n";

    size_t index{1};

    // выводим пункты по одному
    for (const auto &item : m_item_lst) {
        out << index++ << " -> " << item << '\n';
    }

    out << std::endl;
}

void Menu::selectItem(int selected) {
    // делаем проверку на диапозон
    if (selected <= m_item_lst.size() && selected > 0) {
        m_selected = selected - 1;
    } else {
        m_selected = -1;
    }
}

int Menu::execSelected() const {
    // выполняем проверку
    if (m_selected == -1) {
        return -1;
    }

    // если всё хорошо запускаем
    return m_item_lst.at(m_selected)(m_selected);
}

int Menu::operator()() const {
    return execSelected();
}

std::ostream &operator<<(std::ostream &out, const Menu &menu) {
    menu.print(out);

    return out;
}

int Menu::getSelected() const {
    return m_selected;
}

std::istream &operator>>(std::istream &in, Menu &menu) {
    int selected = getEnteredNum(
            "Введите номер нужного пункта -> ",
            getValidate(menu.m_item_lst.size()),
            in
    );
    menu.selectItem(selected);

    return in;
}

void Menu::addItem(ItemMenu itemMenu) {
    m_item_lst.push_back(itemMenu);
}

void Menu::addItemByIndex(ItemMenu itemMenu, int index) {
    // проверяем, что указанный индекс входит в заданный диапазон
    if (index < m_item_lst.size()) {
        m_item_lst.insert(m_item_lst.begin() + index, itemMenu);
    }
}

// функция возвращает нужный валидатор для ввода
// принимает кол - во эелемнтов в меню
ValidateNum getValidate(int count_items) {
    // возвращаем лямбду функцию
    // с замыканием кол - ва эелемнтов в меню
    return [count_items](int value) -> bool {
        return (value <= count_items && value > 0);
    };
}

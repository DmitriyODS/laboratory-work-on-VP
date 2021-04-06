#include "ItemMenu.h"


// главный конструктор
ItemMenu::ItemMenu(string name, FuncExec func)
        : m_name(name), m_func_exec(func) {}

// вызываем дилегирующий конструктор
ItemMenu::ItemMenu(const ItemMenu &itemMenu)
        : ItemMenu(itemMenu.m_name, itemMenu.m_func_exec) {}

int ItemMenu::exec(int selected) const {
    return m_func_exec(selected);
}

std::ostream &operator<<(std::ostream &out, const ItemMenu &itemMenu) {
    itemMenu.print(out);

    return out;
}

void ItemMenu::print(std::ostream &out) const {
    out << m_name;
}

int ItemMenu::operator()(size_t selected) const {
    return exec(selected);
}

ItemMenu &ItemMenu::operator=(const ItemMenu &itemMenu) {
    // делаем проверку на самоприсваивание
    if (this == &itemMenu) {
        return *this;
    }

    m_name = itemMenu.m_name;
    m_func_exec = itemMenu.m_func_exec;

    return *this;
}

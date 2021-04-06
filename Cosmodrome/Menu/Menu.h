#ifndef COSMODROME_MENU_H
#define COSMODROME_MENU_H

#include <string>
#include <vector>
#include <iostream>
#include <ItemMenu.h>
#include <consoleUtils.h>

using std::string;

// ��������� ��� �������
// ������� ����� ������� ���� ������ ����
using ItemList = std::vector<ItemMenu>;

/*
 * ����� ���� - ������� ������� ������
 * ����� ������������ �� ���� ���� ������������
 * ������� ����� ��������� ����������� �������
 * � ��������� ����������� ��� (��������)
 * ����� ������� ���������
 */
class Menu {
public:
    // ������� ����������� �� ���������
    Menu() = delete;

    // ������� �������� ������������
    Menu &operator=(const Menu &) = delete;

    // ������ �����������, ������� ��������� ��������� ����
    // � ������ �������
    Menu(string title, ItemList itemList);

    // ������ ����� ������ ������� �� ������
    // ������� ����� ��������� ����� ������
    void print(std::ostream &out = std::cout) const;

    // ����� ��������������� ��������� ����� ����
    void selectItem(int selected);

    // ����� ������� ������ ����
    // ���������� ��� �������� ��������� �������
    int execSelected() const;

    // ���������� ��������� ����������
    // ���� ������ �����������
    int operator()() const;

    // ������������� ������� ������
    friend std::ostream &operator<<(std::ostream &out, const Menu &menu);

    // ������������� ������� �����
    friend std::istream &operator>>(std::istream &in, Menu &menu);

    // �������� ��������� �����
    int getSelected() const;

    // ����� ����������� ����� ���� � �����
    void addItem(ItemMenu itemMenu);

    // ����� ����������� ����� ���� �� �������� �������
    void addItemByIndex(ItemMenu itemMenu, int index);

private:
    string m_title{};
    ItemList m_item_lst{};
    int m_selected{-1};
};

// ������� ���������� ������ ��������� ��� �����
// ��������� ��� - �� ��������� � ����
ValidateNum getValidate(int count_items);


#endif //COSMODROME_MENU_H

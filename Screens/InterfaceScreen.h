#ifndef COSMODROME_INTERFACESCREEN_H
#define COSMODROME_INTERFACESCREEN_H

#include <iostream>
#include <string>
#include <config.h>
#include <consoleUtils.h>
#include <stack>
#include <map>
#include <Store.h>
#include <algorithm>

// вынисем все нужные объекты из пространств имён
// которые будут использоваться во всех скринах сюда
using std::cout;
using std::string;
using std::endl;

// Общий класс - интерфейс для обобщения объектов
// различных экранов
// сюда можно выносить виртуальные методы общие для всех скринов
class InterfaceScreen {
public:
    // метод запуска экрана - входная точка
    virtual int start() = 0;

    // метод выполняющий главную отрисовку экрана
    virtual void renderMain() const = 0;
};

// создаём тип словарь экранов
using MapScreens = std::map<IdScreens, InterfaceScreen *>;

// создаём тип стек экранов
using StackScreens = std::stack<InterfaceScreen *>;


#endif //COSMODROME_INTERFACESCREEN_H

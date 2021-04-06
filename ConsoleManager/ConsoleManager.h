#ifndef COSMODROME_CONSOLEMANAGER_H
#define COSMODROME_CONSOLEMANAGER_H

#include <string>
#include <iostream>


struct Size {
    int width{};
    int height{};
};

struct Coord {
    int x{};
    int y{};
};

struct Color {
    int background_color{};
    int foregraund_color{};
};

/*
 * Класс, который является сингтоном и отвечает за работу с консолью
 * В нём реалллизованы методы отрисовки в консоли
 */
// TODO: Можно реализовать, но в самую последнюю очередь!
class ConsoleManager {
private:
    Size m_global_size{};
    Coord m_cursore_pos{};
    Color m_global_color{};
};


#endif //COSMODROME_CONSOLEMANAGER_H

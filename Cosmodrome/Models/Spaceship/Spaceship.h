#ifndef COSMODROME_SPACESHIP_H
#define COSMODROME_SPACESHIP_H

#include <string>
#include <vector>


using std::string;
using std::vector;

/*
 * Структура данных - корабль
 */
struct Spaceship {
    // создаём статическое поле для учёта id
    static unsigned int current_id_spaceship;

    // создаём тип список кораблей
    using SpaceshipList = vector<Spaceship *>;

    unsigned int id{};
    string name{};
};

#endif //COSMODROME_SPACESHIP_H

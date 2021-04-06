#ifndef COSMODROME_USER_H
#define COSMODROME_USER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

/*
 * Структура данных - пользователь
 */
struct User {
    // храним возможные уровни доступа, как перечисление
    enum LevelAccess : int {
        EMPLOYEE,
        ASTRONAUT
    };

    // создаём тип список пользователей
    using UsersList = vector<User *>;

    // создаём статическое поле для учёта id
    static unsigned int current_id_user;

    unsigned int id{};
    string name{};
    string surname{};
    string login{};
    string password{};
    LevelAccess level_access{};
};

#endif //COSMODROME_USER_H

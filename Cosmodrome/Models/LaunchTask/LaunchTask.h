#ifndef COSMODROME_LAUNCHTASK_H
#define COSMODROME_LAUNCHTASK_H

#include <string>
#include <ctime>
#include <vector>
#include <ostream>
#include <iomanip>

using std::string;
using std::vector;

/*
 * Структура данных - задача на запуск
 */
struct LaunchTask {
    // создаём статическое поле для учёта id
    static unsigned int current_id_launch_task;

    // создаём тип список задач
    using LaunchTaskList = vector<LaunchTask *>;

    unsigned int id{};
    unsigned int spaceship_id{};
    unsigned int astronaut_id{};
    string name{};
    tm datetime_starting{};
    bool is_completed{};
};

std::ostream &operator<<(std::ostream &out, const tm &dateTime);

#endif //COSMODROME_LAUNCHTASK_H

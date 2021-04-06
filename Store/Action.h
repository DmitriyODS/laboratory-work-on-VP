#ifndef COSMODROME_ACTION_H
#define COSMODROME_ACTION_H

#include <string>
#include <ActionTypes.h>

using std::string;

/*
 * Структура, которая описывает какие данные и на что
 * нужно заменить
 * Является тем самым событием, которое обрабатывает reducer
 * первым параметром идёт тип события
 * вторым параметром неопределённый указатель
 * на данные
 */
struct Action {
    ActionTypes type{};
    void *data{};
};


#endif //COSMODROME_ACTION_H

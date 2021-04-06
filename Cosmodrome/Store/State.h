#ifndef COSMODROME_STORE_H
#define COSMODROME_STORE_H

#include <string>
#include <vector>
#include <map>
#include <LaunchTask/LaunchTask.h>
#include <Spaceship/Spaceship.h>
#include <User/User.h>

// глобально объявляем string
using std::string;

// глобально объявляем vector
using std::vector;

// глобально подключаем map
using std::map;

/*
 * Глобальное хранилище состояний и данных приложения
 * В этой структуре описываются все поля, которые необходимы
 * для приложения
 *
 * Объект этой структуры создаётся в момент запуска приложения
 * и по указателю передаётся классу Store
 */
struct State {
    // TODO: Сюда добавляем поля для данных нашего приложения
    string app_name{}; // название приложения
    User *current_user{}; // указатель на текущего пользователя
    User::UsersList users_list{}; // спиcок указателей на пользователей
    Spaceship::SpaceshipList spaceship_list{}; // список указателей на корабли
    LaunchTask::LaunchTaskList launch_task_list{}; // список указателей на задания
    void *intent_next_screen{}; // указатель, который может хранить следующий запускаемый экран
    void *intent_data{}; // указатель, который может хранить данные для другого экрана
    bool is_push_stack{}; // нужно ли класть текущий экран в стэк
    void *screens_map{}; // указатель на словарь экранов программы
};

#endif //COSMODROME_STORE_H

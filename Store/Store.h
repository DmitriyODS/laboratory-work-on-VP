#ifndef COSMODROME_STATE_H
#define COSMODROME_STATE_H

#include <iostream>
#include <State.h>
#include <Action.h>
#include <ActionTypes.h>
#include <LaunchTask/LaunchTask.h>
#include <Spaceship/Spaceship.h>
#include <User/User.h>
#include <Db.h>

/*
 * Класс - синглтон, который управляет состояниями и данными всего приложения
 *
 * Синглтон - класс, от которого можно создать лишь
 * один объект на всё приложение, достигается путём создание
 * статического объекта и закрытия конструкторов и опертора присваивания
 *
 * Состояние приложения - данные, которые описывают состояние эелемнтов
 * приложения (что выведено на экране, что выбрал пользователь и т д),
 * а также к ним относятся сами данные, с которыми работает приложение
 */
class Store {
public:
    // удаляем конструктор по умолчанию
    Store() = delete;

    // удаляем конструктор копирования
    Store(const Store &) = delete;

    // удаляем оператор присваивания
    Store &operator=(const Store &) = delete;

    // статический метод, который будет возвращать
    // статический объект класса Store
    // и принимать путь к корневой папке с данными
    static Store &createStore(string root_path);

    // перегруженная версия метода возврата объекта
    // принимает начальное состояние и путь к корневой папки с данными
    static Store &createStore(State state, string root_path);

    // метод возвращает указатель на текущий объект
    static Store *getStore();

    // деструктор стора
    ~Store();

    // метод, который будет обновлять состояние хранилища
    // на вход принимает объект структуры ActionTypes
    // возвращает новое состояние приложения
    State dispatch(Action action);

    // метод получения состояния нашего приложения
    State getState();


private:
    // закрываем конструктор
    explicit Store(string root_path);

    // закрываем главный конструктор
    Store(State state, string root_path);

    // объект хранилища
    State m_state{};

    // ссылка на объект базы данных
    Db &m_db;

    // храним указатель на текущий объект
    static Store *s_store;

    // метод начальной инициализации Store
    void _init();

    // метод обработки событий
    State _reducer(Action action);

    // метод загрузки state
    bool _loadState();

    // метод сохранения state
    bool _saveState();
};


#endif //COSMODROME_STATE_H

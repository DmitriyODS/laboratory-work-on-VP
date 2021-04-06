#ifndef COSMODROME_AUTH_H
#define COSMODROME_AUTH_H

#include <InterfaceScreen.h>
#include <User/User.h>

/*
 * Экран авторизации
 * Он обеспечивает следующую логику:
 * TODO: сделать описание класса
 */
class Auth : public InterfaceScreen {
public:
    // удаляем конструктор копирования
    Auth(const Auth &) = delete;

    // удаляем оператор присваивания
    Auth &operator=(const Auth &) = delete;

    // метод возвращает указатель на объект экрана
    static Auth *createScreen();

    // точка входа в экран
    int start() override;

    // метод выполняет главную отрисовку экрана
    void renderMain() const override;

    // метод авторизации
    // возвращает указатель на пользователя
    // который вошёл в систему
    User *auth();

protected:
    Store *m_store{}; // указатель на объект хранилища

    // метод выполняет начальную инициализацию экрана
    void _init();

    // закрываем конструктор по умолчанию
    Auth();
};


#endif //COSMODROME_AUTH_H

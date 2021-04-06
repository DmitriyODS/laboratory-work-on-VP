#ifndef COSMODROME_LAUNCH_H
#define COSMODROME_LAUNCH_H

#include <InterfaceScreen.h>
#include <Menu.h>
#include <Spaceship/Spaceship.h>

/*
 * Экран запуска космических кораблей
 * Он обеспечивает следующую логику:
 * TODO: сделать описание класса
 */
class Launch : public InterfaceScreen {
public:
    // удаляем конструктор копирования
    Launch(const Launch &) = delete;

    // удаляем оператор присваивания
    Launch &operator=(const Launch &) = delete;

    // метод возвращает указатель на объект экрана
    static Launch *createScreen();

    // точка входа в экран
    int start() override;

    // метод выполняет главную отрисовку экрана
    void renderMain() const override;

    // функция создания меню
    Menu *createMenu();

    // метод выполнения запуска
    void runLaunching();

protected:
    Store *m_store{}; // указатель на объект хранилища

    bool m_is_runnning{}; // нужно ли закрывать скрин

    Spaceship *m_spaceship{}; // указатель на корабль с которым мы будем работать

    // метод выполняет начальную инициализацию экрана
    void _init();

    // закрываем конструктор по умолчанию
    Launch();
};

#endif //COSMODROME_LAUNCH_H

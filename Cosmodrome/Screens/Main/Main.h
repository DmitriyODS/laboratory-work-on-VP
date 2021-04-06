#ifndef COSMODROME_MAIN_H
#define COSMODROME_MAIN_H


#include <InterfaceScreen.h>
#include <Menu.h>


/*
 * Главный экран программы
 * Он обеспечивает следующую логику:
 * TODO: сделать описание класса
 */
class Main : public InterfaceScreen {
public:
    // удаляем конструктор копирования
    Main(const Main &) = delete;

    // удаляем оператор присваивания
    Main &operator=(const Main &) = delete;

    // метод возвращает указатель на объект экрана
    static Main *createScreen();

    // точка входа в экран
    int start() override;

    // метод выполняет главную отрисовку экрана
    void renderMain() const override;

    // метод генерации меню
    // на основе уровня доступа текущего пользователя
    Menu *createMainMenu();

    // метод открытия списка кораблей
    void openSpaceshipsListScreen();

    // метод открытия списка пользователей
    void openUsersListScreen();

    // метод открытия списка задач
    void openTasksListScreen();

    // метод разлогинивания
    void logout();

protected:
    Store *m_store{}; // указатель на объект хранилища

    // метод выполняет начальную инициализацию экрана
    void _init();

    // закрываем конструктор по умолчанию
    Main();
};


#endif //COSMODROME_MAIN_H

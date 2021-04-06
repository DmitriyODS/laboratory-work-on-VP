#ifndef COSMODROME_SPACESHIPLIST_H
#define COSMODROME_SPACESHIPLIST_H


#include <InterfaceScreen.h>
#include <Menu.h>


/*
 * Экран отображения списка кораблей
 * Он обеспечивает следующую логику:
 * TODO: сделать описание класса
 */
class SpaceshipList : public InterfaceScreen {
public:

    // создаём тип функции сортировки
    // список космических кораблей
    // возвращает отсортированный новый список
    using SortFunc = std::function<Spaceship::SpaceshipList(Spaceship::SpaceshipList)>;

    // удаляем конструктор копирования
    SpaceshipList(const SpaceshipList &) = delete;

    // удаляем оператор присваивания
    SpaceshipList &operator=(const SpaceshipList &) = delete;

    // метод возвращает указатель на объект экрана
    static SpaceshipList *createScreen();

    // точка входа в экран
    int start() override;

    // метод выполняет главную отрисовку экрана
    void renderMain() const override;

    // вывести список космиеческих кораблей
    // может принимать функцию сортировки
    void printSpaceshipsList(SortFunc sortFunc = nullptr) const;

    // добавить корабль
    void addSpaceship();

    // редактировать корабль по id
    void editSpaceshipById();

    // удалить корабль по его id
    void deleteSpaceshipById();

    // отсортировать по названию
    void sortSpaceshipByName() const;

    // функция создания меню
    Menu *createMenu();

protected:
    Store *m_store{}; // указатель на объект хранилища

    bool m_is_runnning{}; // нужно ли закрывать скрин

    // метод выполняет начальную инициализацию экрана
    void _init();

    // закрываем конструктор по умолчанию
    SpaceshipList();
};


#endif //COSMODROME_SPACESHIPLIST_H

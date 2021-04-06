#ifndef COSMODROME_USERLIST_H
#define COSMODROME_USERLIST_H


#include <InterfaceScreen.h>
#include <Menu.h>
#include <User/User.h>
#include <functional>


/*
 * Экран отображения списка пользователей
 * Он обеспечивает следующую логику:
 * TODO: сделать описание класса
 */
class UserList : public InterfaceScreen {
public:

    // создаём тип функции фильтрации
    // которая принимает указатель на пользователя
    // а возвращает логическое выражение нужно ли его
    // включать в вывод
    using FilterFunc = std::function<bool(User *)>;

    // создаём тип функции сортировки
    // список пользователей
    // возвращает отсортированный новый список
    using SortFunc = std::function<User::UsersList(User::UsersList)>;

    // удаляем конструктор копирования
    UserList(const UserList &) = delete;

    // удаляем оператор присваивания
    UserList &operator=(const UserList &) = delete;

    // метод возвращает указатель на объект экрана
    static UserList *createScreen();

    // точка входа в экран
    int start() override;

    // метод выполняет главную отрисовку экрана
    void renderMain() const override;

    // функция создания меню
    Menu *createMenu();

    // добавить пользователя
    void addNewUser();

    // редактировать пользователя
    void editUserById();

    // удалить пользователя
    void deleteUserById();

    // сортировать пользователей по имени
    void sortUsersByName() const;

    // фильтровать пользователей по сотруднику
    void filterUsersByEmployee() const;

    // фильтровать пользователей по космонавту
    void filterUsersByAstronaut() const;

    // отобразить список всех пользователей
    void printAllUsersList() const;

    // вывод списка пользователей
    // может принимать функцию фильтрации и сортировки
    void printUsersList(SortFunc sortFunc = nullptr, FilterFunc filterFunc = nullptr) const;

protected:
    Store *m_store{}; // указатель на объект хранилища

    bool m_is_runnning{}; // нужно ли закрывать скрин

    // метод выполняет начальную инициализацию экрана
    void _init();

    // закрываем конструктор по умолчанию
    UserList();
};


#endif //COSMODROME_USERLIST_H

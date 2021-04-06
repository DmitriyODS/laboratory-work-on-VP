#ifndef COSMODROME_LAUNCHTASKLIST_H
#define COSMODROME_LAUNCHTASKLIST_H


#include <InterfaceScreen.h>
#include <Menu.h>
#include <Spaceship/Spaceship.h>
#include <LaunchTask/LaunchTask.h>
#include <User/User.h>


/*
 * Экран отображения списка запусков
 * Он обеспечивает следующую логику:
 * TODO: сделать описание класса
 */
class LaunchTaskList : public InterfaceScreen {
public:
    // создаём тип функции фильтрации
    // которая принимает указатель на задачу
    // а возвращает логическое выражение нужно ли её
    // включать в вывод
    using FilterFunc = std::function<bool(LaunchTask *)>;

    // создаём тип функции сортировки
    // список задач
    // возвращает отсортированный новый список
    using SortFunc = std::function<LaunchTask::LaunchTaskList(LaunchTask::LaunchTaskList)>;

    // удаляем конструктор копирования
    LaunchTaskList(const LaunchTaskList &) = delete;

    // удаляем оператор присваивания
    LaunchTaskList &operator=(const LaunchTaskList &) = delete;

    // метод возвращает указатель на объект экрана
    static LaunchTaskList *createScreen();

    // точка входа в экран
    int start() override;

    // метод выполняет главную отрисовку экрана
    void renderMain() const override;

    // функция создания меню
    Menu *createMenu();

    // доабвление новой задачи
    void addNewTask();

    // редактирование существующей задачи
    void editTask();

    // удаление задачи
    void deleteTask();

    // сортировка задач по дате запуска
    void sortTaskByDateStart() const;

    // фильтрация задач по ещё не выполненным
    void filterTaskByCompleted() const;

    // перейти к запуску
    void goToLaunching();

    // вывести все задачи, которые относятся к текущему пользователю
    // или вывести все, если это админ
    void printAllTasksList() const;

    // вывести задачи в отсортированном или отфильтрованном виде
    // (если предоставлена функия сортировки или фильтрации)
    void printTasksList(SortFunc sortFunc = nullptr, FilterFunc filterFunc = nullptr) const;

    void printSpaceships() const;

    void printAstronauts() const;

protected:
    Store *m_store{}; // указатель на объект хранилища

    bool m_is_runnning{}; // нужно ли закрывать скрин

    // метод выполняет начальную инициализацию экрана
    void _init();

    // закрываем конструктор по умолчанию
    LaunchTaskList();
};


#endif //COSMODROME_LAUNCHTASKLIST_H

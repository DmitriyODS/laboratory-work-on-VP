#include <LaunchTaskList/LaunchTaskList.h>
#include "Launch.h"


// выполняем начальную инициализацию экрана
void Launch::_init() {
    // TODO: инициализируем начальное состояние экрана
}

Launch::Launch() {
    // выполняем начальную настройку экрана
    _init();
}

// возвращаем указатель на созданный объект
// текущего класса экрана
Launch *Launch::createScreen() {
    static Launch *launch = new Launch();

    return launch;
}

// метод, главная точка входа в экран
int Launch::start() {
    // TODO: пишем логику экрана здесь

    // получаем указатель на объект хранилища
    m_store = Store::getStore();

    // получаем выбранную задачу запуска
    m_spaceship = static_cast<Spaceship *>(m_store->getState().intent_data);

    // отрисовываем шапку экрана
    renderMain();

    // создаём новое меню приложения
    Menu &menu = *createMenu();

    m_is_runnning = true;

    while (m_is_runnning) {
        // выводим меню
        cout << menu;

        // ожидаем ввод от пользователя
        cin >> menu;

        // запускаем заданную функцию
        menu();
    }

    // удаляем меню
    delete &menu;

    return 0;
}

void Launch::renderMain() const {
    // TODO: здесь рисуем начальное состояние экрана

    system("clear");
    system("cls");

    cout << "Запуск космического корабля - " << m_spaceship->name << '\n'
         << "============================\n\n";
}

Menu *Launch::createMenu() {
    // получаем указатель на текущий экран
    Launch *launch = Launch::createScreen();

    // создаём меню со стандартными пунктами
    Menu *menu = new Menu("Что вы хотите сделать?", ItemList{
            ItemMenu("Выполнить запуск", [launch](int index) -> int {
                launch->runLaunching();
                return index;
            }),
            ItemMenu("Вернуться назад", [launch](int index) -> int {
                launch->m_is_runnning = false;
                return index;
            })
    });

    return menu;
}

void Launch::runLaunching() {
    // TODO: реализовать прикольный обратный отсчёт до старта
    //  затем написать, что корабль запущен и выставить флаг - выполнен запуск
    //  через диспач в хранилище
}

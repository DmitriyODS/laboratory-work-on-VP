#include "Main.h"


// выполняем начальную инициализацию экрана
void Main::_init() {
    // TODO: инициализируем начальное состояние экрана
}

Main::Main() {
    // выполняем начальную настройку экрана
    _init();
}

// возвращаем указатель на созданный объект
// текущего класса экрана
Main *Main::createScreen() {
    static Main *main = new Main();

    return main;
}

// метод, главная точка входа в экран
int Main::start() {
    // TODO: пишем логику экрана здесь

    // получаем указатель на объект хранилища
    m_store = Store::getStore();

    // отрисовываем шапку экрана
    renderMain();

    // создаём новое меню приложения
    Menu &menu = *createMainMenu();

    // выводим меню
    cout << menu;

    // ожидаем ввод от пользователя
    cin >> menu;

    // запускаем заданную функцию
    menu();

    // удаляем меню
    delete &menu;

    return 0;
}

void Main::renderMain() const {
    // TODO: здесь рисуем начальное состояние экрана

    system("cls");
    system("clear");
    cout << "Добро пожаловать в главное меню, "
         << m_store->getState().current_user->name << "!\n"
         << "============================================\n\n"
         << endl;
}

Menu *Main::createMainMenu() {
    // получаем указатель на текущий экран
    Main *main = Main::createScreen();

    // создаём меню со стандартными пунктами
    Menu *menu = new Menu("Главное меню", ItemList{
            ItemMenu("Открыть список космических кораблей", [main](int index) -> int {
                main->openSpaceshipsListScreen();
                return index;
            }),
            ItemMenu("Открыть список предстоящих запусков", [main](int index) -> int {
                main->openTasksListScreen();
                return index;
            }),
            ItemMenu("Выйти из учётных данных", [main](int index) -> int {
                main->logout();
                return index;
            })
    });

    // если текущий пользователь является админом
    // добавляем туда дополнительные пункты
    if (m_store->getState().current_user->level_access == User::LevelAccess::EMPLOYEE) {
        menu->addItemByIndex(ItemMenu("Открыть список пользователей", [main](int index) -> int {
            main->openUsersListScreen();
            return index;
        }), 2);
    }

    return menu;
}

void Main::openSpaceshipsListScreen() {
    // задаём нужный экран для открытия
    m_store->dispatch(Action{
            ActionTypes::SET_INTENT_NEXT_SCREEN,
            static_cast<MapScreens *>(m_store->getState().screens_map)->at(IdScreens::SPACESHIPLIST)
    });

    // задаём триггер о том, что текущий экран следует поместить в стэк
    m_store->dispatch(Action{
            ActionTypes::PUSH_STACK_SCREEN
    });
}

void Main::openUsersListScreen() {
    // задаём нужный экран для открытия
    m_store->dispatch(Action{
            ActionTypes::SET_INTENT_NEXT_SCREEN,
            static_cast<MapScreens *>(m_store->getState().screens_map)->at(IdScreens::USERLIST)
    });

    // задаём триггер о том, что текущий экран следует поместить в стэк
    m_store->dispatch(Action{
            ActionTypes::PUSH_STACK_SCREEN
    });
}

void Main::openTasksListScreen() {
    // задаём нужный экран для открытия
    m_store->dispatch(Action{
            ActionTypes::SET_INTENT_NEXT_SCREEN,
            static_cast<MapScreens *>(m_store->getState().screens_map)->at(IdScreens::LAUNCHTASKLIST)
    });

    // задаём триггер о том, что текущий экран следует поместить в стэк
    m_store->dispatch(Action{
            ActionTypes::PUSH_STACK_SCREEN
    });
}

void Main::logout() {
    // задаём нужный экран для открытия
    m_store->dispatch(Action{
            ActionTypes::SET_INTENT_NEXT_SCREEN,
            static_cast<MapScreens *>(m_store->getState().screens_map)->at(IdScreens::AUTH)
    });

    // делаем разлогин
    m_store->dispatch(Action{
            ActionTypes::CLEAR_CURRENT_USER
    });
}

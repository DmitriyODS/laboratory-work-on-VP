#include "SpaceshipList.h"


// выполняем начальную инициализацию экрана
void SpaceshipList::_init() {
    // TODO: инициализируем начальное состояние экрана
}

SpaceshipList::SpaceshipList() {
    // выполняем начальную настройку экрана
    _init();
}

// возвращаем указатель на созданный объект
// текущего класса экрана
SpaceshipList *SpaceshipList::createScreen() {
    static SpaceshipList *spaceship_list = new SpaceshipList();

    return spaceship_list;
}

// метод, главная точка входа в экран
int SpaceshipList::start() {
    // TODO: пишем логику экрана здесь

    // получаем указатель на объект хранилища
    m_store = Store::getStore();

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

void SpaceshipList::renderMain() const {
    // TODO: здесь рисуем начальное состояние экрана

    system("clear");
    system("cls");

    cout << "Раздел космических кораблей\n"
         << "============================\n\n";

    // отрисуем сразу список всех кораблей
    printSpaceshipsList();
}

void SpaceshipList::printSpaceshipsList(SortFunc sortFunc) const {
    cout << "\n\n=========================\n"
         << "Список всех кораблей:\n"
         << "-----------------------------\n";

    cout << "Id\tНазвание\n";

    auto spaceshipList = (sortFunc) ? sortFunc(m_store->getState().spaceship_list)
                                    : m_store->getState().spaceship_list;

    for (auto *pItem : spaceshipList) {
        cout << pItem->id << "\t" << pItem->name << "\n";
    }

    cout << "=====================================\n\n";
}

Menu *SpaceshipList::createMenu() {
    // получаем указатель на текущий экран
    SpaceshipList *spaceshipList = SpaceshipList::createScreen();

    // создаём меню со стандартными пунктами
    Menu *menu = new Menu("Что вы хотите сделать?", ItemList{
            ItemMenu("Отобразить список кораблей", [spaceshipList](int index) -> int {
                spaceshipList->printSpaceshipsList();
                return index;
            }),
            ItemMenu("Сортировать по названию", [spaceshipList](int index) -> int {
                spaceshipList->sortSpaceshipByName();
                return index;
            }),
            ItemMenu("Вернуться назад", [spaceshipList](int index) -> int {
                spaceshipList->m_is_runnning = false;
                return index;
            })
    });

    // если текущий пользователь является админом
    // добавляем туда дополнительные пункты
    if (m_store->getState().current_user->level_access == User::LevelAccess::EMPLOYEE) {
        menu->addItemByIndex(ItemMenu("Добавить новый корабль", [spaceshipList](int index) -> int {
            spaceshipList->addSpaceship();
            return index;
        }), 2);
        menu->addItemByIndex(ItemMenu("Редактировать корабль по id", [spaceshipList](int index) -> int {
            spaceshipList->editSpaceshipById();
            return index;
        }), 3);
        menu->addItemByIndex(ItemMenu("Удалить корабль по id", [spaceshipList](int index) -> int {
            spaceshipList->deleteSpaceshipById();
            return index;
        }), 4);
    }

    return menu;
}

void SpaceshipList::addSpaceship() {
    cout << "\n\n=================================\n"
         << "Добавление нового космического корабля:\n\n";

    // создаём пустой объект пользователя
    Spaceship spaceship{};

    // устанавливаем новый id
    spaceship.id = Spaceship::current_id_spaceship++;

    // запрашиваем данные для пользователя
    spaceship.name = getEnteredString("Введите название космического корабля -> ");

    // после заполнения полей отправляем новый космический корабль в хранилище
    m_store->dispatch(Action{
            ActionTypes::ADD_NEW_SPACESHIP,
            &spaceship
    });

    // сообщаем пользователю об успешноом завершении операции
    cout << "Космический корабль успешно добавлен!\n"
         << "==========================================\n\n";
}

void SpaceshipList::editSpaceshipById() {
    cout << "\n\n======================================\n"
         << "Редактирвоание космического корабля\n"
         << "------------------------------------------------\n";

    // создаём пустой объект космического корабля
    Spaceship spaceship{};

    // вытаскиваем стэйт специально для валидатора
    State state = m_store->getState();

    // выводим список всех космических кораблей
    printSpaceshipsList();

    // запрашиваем id космического корабля, который будем редачить
    spaceship.id = getEnteredNum(
            "Введите id нужного космического корабля -> ",
            [state](int id) -> bool {
                for (auto *pItem : state.users_list) {
                    if (pItem->id == id) {
                        return true;
                    }
                }

                return false;
            }
    );

    // запрашиваем новые данные для космического корабля
    spaceship.name = getEnteredString("Введите новое название космического корабля -> ");

    // сохраняем новые данные
    m_store->dispatch(Action{
            ActionTypes::EDIT_SPACESHIP,
            &spaceship
    });

    // сообщаем пользователю об успешной операции
    cout << "Космический корабль успешно отредактирован!\n"
         << "======================================\n\n";

}

void SpaceshipList::deleteSpaceshipById() {
    cout << "\n\n=====================================\n"
         << "Удаление космического корабля\n"
         << "-----------------------------------------\n";

    // вытаскиваем стэйт специально для валидатора
    State state = m_store->getState();

    // выводим список всех космических кораблей
    printSpaceshipsList();

    // запрашиваем id космического корабля, который будем удалять
    unsigned int id = getEnteredNum(
            "Введите id нужного пользвоателя -> ",
            [state](int id) -> bool {
                for (auto *pItem : state.users_list) {
                    if (pItem->id == id) {
                        return true;
                    }
                }

                return false;
            }
    );

    // ищем индекс пользователя в массиве
    // TODO: Много раз в разных местах приходится проходиться по массиву
    //  нужно подумать, как оптимизировать этот процесс
    int index{};
    for (auto *pItem : m_store->getState().users_list) {
        if (pItem->id == id) {
            break;
        }
        ++index;
    }

    // обращаемся к стору за удалением
    m_store->dispatch(Action{
            ActionTypes::DELETE_SPACESHIP,
            &index
    });

    // сообщаем об успешном удалении
    cout << "Космический корабль успешно удалён!\n"
         << "==================================n\n\n";
}

void SpaceshipList::sortSpaceshipByName() const {
    cout << "\n\n=========================================\n";
    cout << "Сортировка по имени\n";

    // добавляем функцию сортировки
    printSpaceshipsList([](Spaceship::SpaceshipList spaceshipList) -> Spaceship::SpaceshipList {
        Spaceship::SpaceshipList sortSpaceshipList = spaceshipList;

        // запускаем функцию сортировки по возрастанию
        std::sort(sortSpaceshipList.begin(), sortSpaceshipList.end(),
                  [](const Spaceship *first, const Spaceship *second) -> bool {
                      return first->name < second->name;
                  });

        return sortSpaceshipList;
    });
}

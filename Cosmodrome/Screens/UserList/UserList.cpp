#include "UserList.h"


// выполняем начальную инициализацию экрана
void UserList::_init() {
    // TODO: инициализируем начальное состояние экрана
}

UserList::UserList() {
    // выполняем начальную настройку экрана
    _init();
}

// возвращаем указатель на созданный объект
// текущего класса экрана
UserList *UserList::createScreen() {
    static UserList *user_list = new UserList();

    return user_list;
}

// метод, главная точка входа в экран
int UserList::start() {
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

void UserList::renderMain() const {
    // TODO: здесь рисуем начальное состояние экрана

    system("clear");
    system("cls");

    cout << "Список пользователей\n"
         << "============================\n\n";

    // отрисовываем всех пользователей
    printAllUsersList();
}

Menu *UserList::createMenu() {
    // получаем указатель на текущий экран
    UserList *userList = UserList::createScreen();

    // создаём меню со стандартными пунктами
    Menu *menu = new Menu("Что вы хотите сделать?", ItemList{
            ItemMenu("Отобразить всех пользователей", [userList](int index) -> int {
                userList->printAllUsersList();
                return index;
            }),
            ItemMenu("Добавить пользователя", [userList](int index) -> int {
                userList->addNewUser();
                return index;
            }),
            ItemMenu("Редактировать пользователя", [userList](int index) -> int {
                userList->editUserById();
                return index;
            }),
            ItemMenu("Удалить пользователя", [userList](int index) -> int {
                userList->deleteUserById();
                return index;
            }),
            ItemMenu("Сортировать по имени", [userList](int index) -> int {
                userList->sortUsersByName();
                return index;
            }),
            ItemMenu("Показать сотрудников", [userList](int index) -> int {
                userList->filterUsersByEmployee();
                return index;
            }),
            ItemMenu("Показать космонавтов", [userList](int index) -> int {
                userList->filterUsersByAstronaut();
                return index;
            }),
            ItemMenu("Вернуться назад", [userList](int index) -> int {
                userList->m_is_runnning = false;
                return index;
            })
    });

    return menu;
}

// TODO: Для всех этих пунктов нужно добавить возможность отмены выбора/ввода
//  чтобы пользователь мог вернуться к экрану
//  скорее всего это действие нужно добавить в функции ввода в Utils

void UserList::addNewUser() {
    cout << "\n\n=================================\n"
         << "Добавление нового пользователя:\n\n";

    // создаём пустой объект пользователя
    User user{};

    // устанавливаем новый id
    user.id = User::current_id_user++;

    // запрашиваем данные для пользователя
    user.name = getEnteredString("Введите имя пользователя -> ");
    user.surname = getEnteredString("Введите фамилию пользователя -> ");

    // здесь нужна функция валидатор для проверки
    // на уникальность логина
    // вытаскиваем стэйт специально для валидатора
    State state = m_store->getState();
    user.login = getEnteredString(
            "Введите логин пользователя -> ",
            [state](string login) -> bool {
                for (auto *pItem : state.users_list) {
                    if (pItem->login == login) {
                        return false;
                    }
                }

                return true;
            });

    user.password = getEnteredString("Введите пароль пользователя -> ");

    // запрашиваем уровень доступа
    // добавляем валидатор
    user.level_access = static_cast<User::LevelAccess>(getEnteredNum(
            "Введите 0, если пользователь сотрудник и 1 в ином случае -> ",
            [](int num) -> bool {
                return num == 0 || num == 1;
            }));

    // после заполнения полей отправляем нового пользователя в хранилище
    m_store->dispatch(Action{
            ActionTypes::ADD_NEW_USER,
            &user
    });

    // сообщаем пользователю об успешноом завершении операции
    cout << "Пользователь успешно добавлен!\n"
         << "==========================================\n\n";
}

void UserList::editUserById() {
    cout << "\n\n======================================\n"
         << "Редактирвоание пользователя\n"
         << "------------------------------------------------\n";

    // создаём пустой объект пользователя
    User user{};

    // вытаскиваем стэйт специально для валидатора
    State state = m_store->getState();

    // выводим список всех пользователей
    printAllUsersList();

    // запрашиваем id пользователя, которого будем редачить
    user.id = getEnteredNum(
            "Введите id нужного пользователя -> ",
            [state](int id) -> bool {
                for (auto *pItem : state.users_list) {
                    if (pItem->id == id) {
                        return true;
                    }
                }

                return false;
            }
    );

    // запрашиваем новые данные для пользвователя
    // TODO: можно реализовать редактирование только определённых пунктов
    //  с сохранением прошлых значений в остальных
    user.name = getEnteredString("Введите новое имя пользователя -> ");
    user.surname = getEnteredString("Введите новую фамилию пользователя -> ");
    user.login = getEnteredString(
            "Введите новый логин пользователя -> ",
            [state](string login) -> bool {
                for (auto *pItem : state.users_list) {
                    if (pItem->login == login) {
                        return false;
                    }
                }

                return true;
            });

    user.password = getEnteredString("Введите новый пароль пользователя -> ");

    // запрашиваем уровень доступа
    // добавляем валидатор
    user.level_access = static_cast<User::LevelAccess>(getEnteredNum(
            "Введите 0, если пользователь сотрудник и 1 в ином случае -> ",
            [](int num) -> bool {
                return num == 0 || num == 1;
            }));

    // сохраняем новые данные
    m_store->dispatch(Action{
            ActionTypes::EDIT_USER,
            &user
    });

    // сообщаем пользователю об успешной операции
    cout << "Пользователь успешно отредактирован!\n"
         << "======================================\n\n";

}

void UserList::deleteUserById() {
    cout << "\n\n=====================================\n"
         << "Удаление пользователя\n"
         << "-----------------------------------------\n";

    // вытаскиваем стэйт специально для валидатора
    State state = m_store->getState();

    // выводим список всех пользователей
    printAllUsersList();

    // запрашиваем id пользователя, которого будем удалять
    unsigned int id = getEnteredNum(
            "Введите id нужного пользвоателя -> ",
            [state](int id) -> bool {
                // сперва чекаем что пользователь не является текущим
                if (state.current_user->id == id) {
                    return false;
                }
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
            ActionTypes::DELETE_USER,
            &index
    });

    // сообщаем об успешном удалении
    cout << "Пользователь успешно удалён!\n"
         << "==================================n\n\n";
}

void UserList::sortUsersByName() const {
    cout << "\n\n=========================================\n";
    cout << "Сортировка по имени\n";

    // добавляем функцию сортировки
    printUsersList([](User::UsersList usersList) -> User::UsersList {
        User::UsersList sortUserList = usersList;

        // запускаем функцию сортировки по возрастанию
        // лексикографически сравниваем имена пользователей
        std::sort(sortUserList.begin(), sortUserList.end(), [](const User *first, const User *second) -> bool {
            return first->name < second->name;
        });

        return sortUserList;
    });
}

void UserList::filterUsersByEmployee() const {
    cout << "\n\n=========================================\n";
    cout << "Все сотрудники\n";

    // добавляем функцию фильтрации
    printUsersList(nullptr, [](User *user) -> bool {
        return user->level_access == User::LevelAccess::EMPLOYEE;
    });
}

void UserList::filterUsersByAstronaut() const {
    cout << "\n\n=========================================\n";
    cout << "Все астронавты\n";

    // добавляем функцию фильтрации
    printUsersList(nullptr, [](User *user) -> bool {
        return user->level_access == User::LevelAccess::ASTRONAUT;
    });
}

void UserList::printAllUsersList() const {
    cout << "\n\n=========================================\n";
    cout << "Все пользователи:\n";
    printUsersList();
}

void UserList::printUsersList(UserList::SortFunc sortFunc, UserList::FilterFunc filterFunc) const {
    cout << "Id\tИмя\tФамилия\tЛогин\tТип\n"
         << "---------------------------------------------\n";

    // если функция сортировки существует, то прогоняем по ней наш список
    // если нет берём тот же список
    User::UsersList usersList = (sortFunc) ? sortFunc(m_store->getState().users_list)
                                           : m_store->getState().users_list;

    for (auto *pItem : usersList) {

        // фильтруем записи
        // если функция существует и запись
        // не подходит, то переходим к следующей
        // записи
        if (filterFunc && !filterFunc(pItem)) {
            continue;
        }

        cout << pItem->id << "\t"
             << pItem->name << "\t"
             << pItem->surname << "\t"
             << pItem->login << "\t";

        // вывод типа учётной записи
        switch (pItem->level_access) {
            case User::LevelAccess::EMPLOYEE:
                cout << "Сотрудник" << "\n";
                break;
            case User::LevelAccess::ASTRONAUT:
                cout << "Астронавт" << "\n";
                break;
        }
    }

    cout << "=========================================\n\n";
}

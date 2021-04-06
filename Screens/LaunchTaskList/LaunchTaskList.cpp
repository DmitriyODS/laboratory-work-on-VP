#include "LaunchTaskList.h"


// выполняем начальную инициализацию экрана
void LaunchTaskList::_init() {
    // TODO: инициализируем начальное состояние экрана
}

LaunchTaskList::LaunchTaskList() {
    // выполняем начальную настройку экрана
    _init();
}

// возвращаем указатель на созданный объект
// текущего класса экрана
LaunchTaskList *LaunchTaskList::createScreen() {
    static LaunchTaskList *launch_task_list = new LaunchTaskList();

    return launch_task_list;
}

// метод, главная точка входа в экран
int LaunchTaskList::start() {
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

void LaunchTaskList::renderMain() const {
    // TODO: здесь рисуем начальное состояние экрана

    system("clear");
    system("cls");

    cout << "Список запусков\n"
         << "============================\n\n";

    // отрисовываем все запуски
    printTasksList();
}

Menu *LaunchTaskList::createMenu() {
    // получаем указатель на текущий экран
    LaunchTaskList *launchTaskList = LaunchTaskList::createScreen();

    // создаём меню со стандартными пунктами
    Menu *menu = new Menu("Что вы хотите сделать?", ItemList{
            ItemMenu("Показать все запуски", [launchTaskList](int index) -> int {
                launchTaskList->printTasksList();
                return index;
            }),
            ItemMenu("Сортировать по дате запуска", [launchTaskList](int index) -> int {
                launchTaskList->sortTaskByDateStart();
                return index;
            }),
            ItemMenu("Отобразить предстоящие запуски", [launchTaskList](int index) -> int {
                launchTaskList->filterTaskByCompleted();
                return index;
            }),
            ItemMenu("Выполнить конкретный запуск", [launchTaskList](int index) -> int {
                launchTaskList->filterTaskByCompleted();
                return index;
            }),
            ItemMenu("Вернуться назад", [launchTaskList](int index) -> int {
                launchTaskList->m_is_runnning = false;
                return index;
            })
    });

    // если текущий пользователь является админом
    // добавляем туда дополнительные пункты
    if (m_store->getState().current_user->level_access == User::LevelAccess::EMPLOYEE) {
        menu->addItemByIndex(ItemMenu("Добавить новый запуск", [launchTaskList](int index) -> int {
            launchTaskList->addNewTask();
            return index;
        }), 4);
        menu->addItemByIndex(ItemMenu("Редактировать запуск по id", [launchTaskList](int index) -> int {
            launchTaskList->editTask();
            return index;
        }), 5);
        menu->addItemByIndex(ItemMenu("Удалить запуск по id", [launchTaskList](int index) -> int {
            launchTaskList->deleteTask();
            return index;
        }), 6);
    }

    return menu;
}

void LaunchTaskList::addNewTask() {
    cout << "\n\n=================================\n"
         << "Добавление новой задачи:\n\n";

    // создаём пустой объект задачи
    LaunchTask launchTask{};

    // устанавливаем новый id
    launchTask.id = LaunchTask::current_id_launch_task++;

    // запрашиваем название для задачи
    launchTask.name = getEnteredString("Введите название задачи -> ");

    // здесь нужна функция валидатор для проверки,
    // существует ли нужный космический корабль.
    // вытаскиваем стэйт специально для валидатора.
    State state = m_store->getState();

    printAstronauts();

    launchTask.astronaut_id = getEnteredNum(
            "Введите id астронавта, ответственного за полёт -> ",
            [state](int id) -> bool {
                for (auto *pItem : state.users_list) {
                    if (pItem->id == id) {
                        return true;
                    }
                }
                return false;
            }
    );

    // делаем задачу незавершённой
    launchTask.is_completed = false;

    printSpaceships();

    // спрашиваем у пользователя
    // на каком корабле будет совершён полёт
    // в валидаторе также проверяем,
    // существует ли корабль с таким id
    launchTask.spaceship_id = getEnteredNum(
            "Введите id корабля, на котором состоиться полёт -> ",
            [state](int id) -> bool {
                for (auto *pItem : state.spaceship_list) {
                    if (pItem->id == id) {
                        return true;
                    }
                }
                return false;
            }
    );

    launchTask.datetime_starting = getEnteredDateTime(
            "Введите время запуска(в формате day.month.year-hour:minute) -> "
    );

    // после заполнения полей отправляем новую задачу в хранилище
    m_store->dispatch(Action{
            ActionTypes::ADD_NEW_LAUNCH_TASK,
            &launchTask
    });

    // сообщаем пользователю об успешноом завершении операции
    cout << "Задача успешно добавлена!\n"
         << "==========================================\n\n";
}

void LaunchTaskList::editTask() {
    cout << "\n\n======================================\n"
         << "Редактирвоание задачи\n"
         << "------------------------------------------------\n";

    // создаём пустой объект задачи
    LaunchTask launchTask{};

    // вытаскиваем стэйт специально для валидатора
    State state = m_store->getState();

    // выводим список всех задач
    // принадлежащих пользователю
    // если пользователь администратор -
    //           выводятся все задачи
    printTasksList();

    // запрашиваем id задачи, которую будем редачить
    launchTask.id = getEnteredNum(
            "Введите id нужного пользователя -> ",
            [state](int id) -> bool {
                for (auto *pItem : state.launch_task_list) {
                    if (pItem->id == id) {
                        return true;
                    }
                }
                return false;
            }
    );

    // запрашиваем новые данные
    // TODO: можно реализовать редактирование только определённых пунктов
    //  с сохранением прошлых значений в остальных
    launchTask.name = getEnteredString("Введите новое название задачи -> ");

    printSpaceships();

    launchTask.spaceship_id = getEnteredNum(
            "Введите новый id корабля -> ",
            [state](int id) {
                for (auto *pItem : state.spaceship_list) {
                    if (pItem->id == id) {
                        return true;
                    }
                }
                return false;
            }
    );

    printAstronauts();

    launchTask.astronaut_id = getEnteredNum(
            "Введите новый id астронавта -> ",
            [state](int id) {
                for (auto *pItem : state.users_list) {
                    if (pItem->id == id && pItem->level_access == User::LevelAccess::ASTRONAUT) {
                        return true;
                    }
                }
                return false;
            }
    );

    launchTask.is_completed = 'Y' == getEnteredChar(
            "Является ли задача завершённой? [Y/n]",
            [](char ch) {
                return ch == 'Y' || ch == 'n';
            }
    );

    launchTask.datetime_starting = getEnteredDateTime(
        "Введите дату начала полёта(в формате day.month.year-hour:minute) -> "
    );

    // сохраняем новые данные
    m_store->dispatch(Action{
            ActionTypes::EDIT_LAUNCH_TASK,
            &launchTask
    });

    // сообщаем пользователю об успешной операции
    cout << "Задача успешно отредактирован!\n"
         << "======================================\n\n";
}

void LaunchTaskList::deleteTask() {
    cout << "\n\n=====================================\n"
         << "Удаление задачи\n"
         << "-----------------------------------------\n";

    // вытаскиваем стэйт специально для валидатора
    State state = m_store->getState();

    // выводим список всех задач
    printTasksList();

    // запрашиваем id задачи, которую будем удалять
    unsigned int id = getEnteredNum(
            "Введите id нужной задачи-> ",
            [state](int id) -> bool {
                for (auto *pItem : state.launch_task_list) {
                    if (pItem->id == id) {
                        return true;
                    }
                }
                return false;
            }
    );

    // ищем индекс задачи в массиве
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
            ActionTypes::DELETE_LAUNCH_TASK,
            &index
    });

    // сообщаем об успешном удалении
    cout << "Задача успешно удалена!\n"
         << "==================================n\n\n";
}

void LaunchTaskList::sortTaskByDateStart() const {
    cout << "\n\n=========================================\n";
    cout << "Сортировка по дате начала\n";

    printTasksList([](LaunchTask::LaunchTaskList launchTaskList) -> LaunchTask::LaunchTaskList {
        auto sortedTaskList{launchTaskList};
        /* FIXME: not working, operator& return const tm*, when mktime hold only tm*
        std::sort(sortedTaskList.begin(), sortedTaskList.end(), [](const LaunchTask *first, const LaunchTask *second) {
            return difftime(mktime(&first->datetime_starting), mktime(&second->datetime_starting));
        });
         */
        return sortedTaskList;
    });
}

void LaunchTaskList::filterTaskByCompleted() const {
    cout << "\n\n=========================================\n";
    cout << "Незавершённые задачи\n";
    printTasksList(nullptr, [](LaunchTask *launchTask) -> bool {
        return !launchTask->is_completed;
    });
}

void LaunchTaskList::goToLaunching() {
    // TODO: Перейти к экрану запуска (передав указатель на нужную задачу)
}

void LaunchTaskList::printAllTasksList() const {
    cout << "\n\n=========================\n"
         << "Список задач:\n"
         << "-----------------------------\n";
    printTasksList();
}

void LaunchTaskList::printTasksList(LaunchTaskList::SortFunc sortFunc, LaunchTaskList::FilterFunc filterFunc) const {
    cout << "Id\tНазвание\tId корабля\tId астронавта\tДата запуска\tЗавершена\n";

    cout << "=====================================\n\n";

    const auto &state = m_store->getState();

    const auto &launchTaskList = (sortFunc ? sortFunc(state.launch_task_list) : state.launch_task_list);

    for (const auto &pItem : launchTaskList) {
        if (state.current_user->level_access == User::LevelAccess::EMPLOYEE
            || pItem->astronaut_id == state.current_user->id) {

            // Не выводим задачу, если она не прошла фильтрацию
            if (filterFunc && !filterFunc(pItem)) {
                continue;
            }

            cout << pItem->id << "\t"
                 << pItem->name << "\t"
                 << pItem->spaceship_id << "\t"
                 << pItem->astronaut_id << "\t"
                 << pItem->datetime_starting << "\t"
                 << (pItem->is_completed ? "Completed" : "Not completed")
                 << endl;
        }
    }
    cout << "=====================================\n\n";
}

void LaunchTaskList::printSpaceships() const {
    cout << "\n\n=========================\n"
         << "Список всех кораблей:\n"
         << "-----------------------------\n";

    cout << "Id\tНазвание\n";

    for (auto *pItem : m_store->getState().spaceship_list) {
        cout << pItem->id << "\t" << pItem->name << "\n";
    }

    cout << "=====================================\n\n";
}

void LaunchTaskList::printAstronauts() const {
    cout << "Id\tИмя\tФамилия\n"
         << "---------------------------------------------\n";

    for (auto *pItem : m_store->getState().users_list) {

        // печатаем пользователя только, если
        // он является астронавтом
        if (pItem->level_access == User::LevelAccess::ASTRONAUT) {
            cout << pItem->id << "\t"
                 << pItem->name << "\t"
                 << pItem->surname << "\t"
                 << endl;
        }
    }

    cout << "=========================================\n\n";
}

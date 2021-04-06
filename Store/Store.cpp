#include "Store.h"

// инициализируем указатель на текущий объект
// в данном случае он равен нулевому указателю
Store *Store::s_store{};

// метод, который загружает данные в state
// из базы данных
// база данных представляем из себя класс - синглтон
// и имеет методы для выгрузки
// и загрузки данных
bool Store::_loadState() {
    // TODO: Реализовать загрузку пользователей, кораблей и задач.
    //  Если набор данных пользователя пуст, создать админа по умолчанию.

    // FIXME: Пока сразу создаём админа по умолчанию
    //  т к не реализована логика сохранения данных в базе
    //  можно её реализовать разными способами: через сохранение
    //  в файлики, через сохранение в БД и т д
    //  здесь, нужно будет обращаться к рбъекту базы
    // и выгружать от туда данные в state
    m_state.users_list.push_back(new User{
            .id = User::current_id_user++,
            .name = "admin",
            .login = "admin",
            .password = "admin",
            .level_access = User::LevelAccess::EMPLOYEE
    });


    // если всё успешно - возвращаем тру
    return true;
}

// в этом методе происходит сохранение State
// в объекте базы
bool Store::_saveState() {
    // TODO: Реализовать сохранение пользователей, кораблей и задач
    return false;
}

// метод инициализации хранилища
void Store::_init() {
    // TODO: Здесь описываем начаьную инициализацию Store

    // загружаем данные и проверяем на ошибку
    if (bool err = _loadState(); !err) {
        // не удалось загрузить данные
        // отображаем сообщение об этом в логе ошибок
        std::cerr
                << "Не удалось загрузить начальные данные хранилища! Store.cpp - _init() 23"
                << std::endl;
    }
}

Store::~Store() {
    // TODO: сохраняем данные и очищаем что нужно

    // пытаемся сохраниться
    if (bool err = _saveState(); !err) {
        // не удалось сохранить данные
        // отображаем сообщение об этом в логе ошибок
        std::cerr
                << "Не удалось сохранить данные хранилища! Store.cpp - ~Store() 36"
                << std::endl;
    }

    // удаляем всё из state

    // удаляем корабли
    for (auto *pItem : m_state.spaceship_list) {
        delete pItem;
    }

    // удаляем пользователей
    for (auto *pItem : m_state.users_list) {
        delete pItem;
    }

    // удаляем задачи запуска
    for (auto *pItem : m_state.launch_task_list) {
        delete pItem;
    }
}

// конструктор, принимающий путь до корневой
// директории с данными
// и объект state с начальной инициализацией
// через список инициализации настраиваем объекты
Store::Store(State state, string root_path)
        : m_state(state), m_db(Db::createDb(root_path)) {

    // запускаем метод начлаьной инициализации Store
    _init();
}

// вызываем дилегирующий конструктор
// с новым (пустым) объектом State
// и корневой дирректорией
Store::Store(string root_path) : Store(State{}, root_path) {}


Store &Store::createStore(string root_path) {
    // содаём статический объект
    static Store store(root_path);

    // сохраняем указатель на этот объект
    s_store = &store;

    // возвращаем его
    return store;
}

Store &Store::createStore(State state, string root_path) {
    // создаём статический объект с начальным состоянием
    static Store store(state, root_path);

    // сохраняем указатель на этот объект
    s_store = &store;

    // возвращаем его
    return store;
}

// метод, который принимает объект Action
// объект Action состоит из двух полей:
// типа события и данных
// затем, этот метод передаёт пришедший
// объект событий методу reducer
// который на основе типа события и данных
// будет менять состояние приложения
// а затем вернёт новое состояние
State Store::dispatch(Action action) {
    // вызываем метод обработки событий
    // присваеваем новый объект состояния
    m_state = _reducer(action);

    // возвращаем его
    return m_state;
}

// метод обработки событий приложения
// сюда мы помещаем все возможные события
// которые могут возникнуть в нашей программе
// данный метод по пришедшему к нему события
// создаёт новый объект State
// заполняет его новыми данными
// которые пришли в событии и отправляет его
// обратно, сам корневой State - он не меняет
State Store::_reducer(Action action) {
    // создаём копию состояния
    State state(m_state);

    // TODO: Здесь описываем логику событий нашего приложения в case-ах
    //  делаем проверку по типу события
    switch (action.type) {
        case ActionTypes::CHANGE_APP_NAME:
            state.app_name = *static_cast<string *>(action.data);
            break;
        case ActionTypes::SET_CURRENT_USER:
            state.current_user = static_cast<User *>(action.data);
            break;
        case ActionTypes::CLEAR_CURRENT_USER:
            state.current_user = nullptr;
            break;
        case ActionTypes::ADD_NEW_USER:
            state.users_list.push_back(new User(*static_cast<User *>(action.data)));
            break;
        case ActionTypes::EDIT_USER:
            for (auto *item : state.users_list) {
                if (item->id == static_cast<User *>(action.data)->id) {
                    *item = *static_cast<User *>(action.data);
                }
            }
            break;
        case ActionTypes::DELETE_USER:
            delete state.users_list.at(*static_cast<int *>(action.data));
            state.users_list.erase(state.users_list.begin() + *static_cast<int *>(action.data));
            break;
        case ActionTypes::ADD_NEW_SPACESHIP:
            state.spaceship_list.push_back(new Spaceship(*static_cast<Spaceship *>(action.data)));
            break;
        case ActionTypes::EDIT_SPACESHIP:
            for (auto *item : state.spaceship_list) {
                if (item->id == static_cast<Spaceship *>(action.data)->id) {
                    *item = *static_cast<Spaceship *>(action.data);
                }
            }
            break;
        case ActionTypes::DELETE_SPACESHIP:
            delete state.spaceship_list.at(*static_cast<int *>(action.data));
            state.spaceship_list.erase(state.spaceship_list.begin() + *static_cast<int *>(action.data));
            break;
        case ActionTypes::ADD_NEW_LAUNCH_TASK:
            state.launch_task_list.push_back(new LaunchTask(*static_cast<LaunchTask *>(action.data)));
            break;
        case ActionTypes::EDIT_LAUNCH_TASK:
            for (auto *item : state.launch_task_list) {
                if (item->id == static_cast<LaunchTask *>(action.data)->id) {
                    *item = *static_cast<LaunchTask *>(action.data);
                }
            }
            break;
        case ActionTypes::DELETE_LAUNCH_TASK:
            delete state.launch_task_list.at(*static_cast<int *>(action.data));
            state.launch_task_list.erase(state.launch_task_list.begin() + *static_cast<int *>(action.data));
            break;
        case ActionTypes::SET_INTENT_NEXT_SCREEN:
            state.intent_next_screen = action.data;
            break;
        case ActionTypes::SET_INTENT_DATA:
            state.intent_data = action.data;
            break;
        case ActionTypes::CLEAR_INTENT_NEXT_SCREEN:
            // объекты экранов не удаляются
            // они синглтоны и должны существовать до конца программы
            // здесь мы просто обнуляем указатель на следующий экран
            state.intent_next_screen = nullptr;
            break;
        case ActionTypes::CLEAR_INTENT_DATA:
            // т к данные будут храниться, как не определённый
            // указатель на объект, удалить мы его не сможем
            // по этому удаление самого объекта ложиться
            // на плечи принимающему экрану
            // а здесь мы просто обнуляем указатель
            state.intent_data = nullptr;
            break;
        case ActionTypes::PUSH_STACK_SCREEN:
            state.is_push_stack = true;
            break;
        case ActionTypes::CLEAR_PUSH_STACK_SCREEN:
            state.is_push_stack = false;
            break;

        default:
            // какая - то общая логика обработки
            // если не нашли ничего нужного
            break;
    }

    return state;
}

// возвращаем объект состояния приложения
State Store::getState() {
    return m_state;
}

// возвращаем указатель на статический объект хранилища
Store *Store::getStore() {

    // проверка ошибки
    if (s_store == nullptr) {
        std::cerr << "Вызов getStore раньше чем createStore! Получен нулевой указатель!" << std::endl;
    }

    return s_store;
}

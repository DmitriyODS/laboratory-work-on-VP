#ifndef COSMODROME_CONFIG_H
#define COSMODROME_CONFIG_H

#include <string>

using std::string;

/*
 * Сюда мы помещаем глобальные ресурсы
 * доступ к которым будет осуществляться
 * из любой части нашей программы
 */

// устанавливаем корневую директорию для файлов данных
const string ROOT_DIR = "./";

// набор идентификаторов экранов
enum IdScreens : int {
    // TODO: Сюда помещаем описание всех наших экранов
    //  которые есть в вашем приложении

    AUTH,
    MAIN,
    LAUNCH,
    LAUNCHTASKLIST,
    SPACESHIPLIST,
    USERLIST
};

#endif //COSMODROME_CONFIG_H

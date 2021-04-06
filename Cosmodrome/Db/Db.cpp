#include "Db.h"


void Db::_init() {
    // TODO: выполняем начальную настройку объекта базы
    //  сперва бы хорошо, выполнить обработку корневого пути
    //  т к если к нам приходит пустой путь, то вместо него
    //  нужно положить путь к текущей дирректории из которой была
    //  запущена программа
}

Db &Db::createDb(string root_path) {
    static Db db(root_path);

    return db;
}

Db::Db(string root_path) : m_root_path_data(root_path) {
    _init();
}

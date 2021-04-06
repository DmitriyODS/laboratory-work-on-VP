#ifndef COSMODROME_DB_H
#define COSMODROME_DB_H

#include <string>

using std::string;

/*
 * Класс синглтон в котором реализована логика
 * сохранения данных программы в долгосрочное
 * хранилище
 */
// TODO: Написать логику работы с данными!
class Db {
public:
    // удаляем конструктор по умолчанию
    Db() = delete;

    // удаляем конструктор копирования
    Db(const Db &) = delete;

    // удаляем оператор присваивания
    Db &operator=(const Db &) = delete;

    // метод возвращает объект базы
    // принимает путь к корневому каталогу с файлами
    // если ничего не пришло, то выбирается каталог
    // из которого запущена программа
    static Db &createDb(string root_path = string());

private:
    // поле хранит путь к корневому каталогу с данными
    string m_root_path_data{};

    // закрываем главный конструктор
    // принимает путь к корневому каталогу данных
    explicit Db(string root_path);

    // метод начальной инициализаии базы
    void _init();
};


#endif //COSMODROME_DB_H

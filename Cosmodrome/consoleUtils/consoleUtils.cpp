#include "consoleUtils.h"


string getEnteredString(string text, ValidateString validate, std::istream &in) {
    string console_enter{};

    while (true) {
        cout << text;
        in >> console_enter;

        if (in.fail() || (validate && !validate(console_enter))) {
            console_enter.clear();
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\n\nYou entered an incorrect value, please try again!\n\n";
            continue;
        }

        break;
    }

    return console_enter;
}

int getEnteredNum(string text, ValidateNum validate, std::istream &in) {
    int console_enter{};

    while (true) {
        cout << text;
        in >> console_enter;

        if (cin.fail() || (validate && !validate(console_enter))) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\n\nYou entered an incorrect value, please try again!\n\n";
            continue;
        }

        break;
    }

    return console_enter;
}

char getEnteredChar(string text, ValidateChar validate, std::istream &in) {
    char console_enter{};

    while (true) {
        cout << text;
        in >> console_enter;

        if (cin.fail() || (validate && !validate(console_enter))) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\n\nYou entered an incorrect value, please try again!\n\n";
            continue;
        }

        break;
    }

    return console_enter;
}

std::tm getEnteredDateTime(string text, ValidateDateTime validate, std::istream &in) {
    // устанавливаем формат считывания даты
    // TODO: это можно куда - то в другое место вынести, или вообще сделать
    //  универсальный считыватель на дату, время, или всё вместе с разными
    //  форматами ввода, но это если будет желание
    const char *FORMAT_DATETIME = "%d.%m.%Y-%H:%M";

    string console_enter{};

    // создаём объект даты и времени
    std::tm datetime{};

    while (true) {
        cout << text;
        in >> console_enter;

        if (cin.fail()) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\n\nYou entered an incorrect value, please try again!\n\n";
            continue;
        }

        // создаём строковый поток на считывание
        // инициализируем его считанной строкой
        // FIXME: Придумать как заставить поток выдавать всю строку, а не через пробел делитель
        istringstream i_string_stream{console_enter};

        // пытаемся выполнить преобразование строки в дату по формату
        i_string_stream >> std::get_time(&datetime, FORMAT_DATETIME);

        // если произошла ошибка парсинга, или неверный валидатор идём на второй круг
        if (i_string_stream.fail() || (validate && !validate(datetime))) {
            cout << "\n\nYou entered an incorrect value, please try again!\n\n";
            datetime = std::tm{};
            continue;
        }

        break;
    }

    return datetime;
}

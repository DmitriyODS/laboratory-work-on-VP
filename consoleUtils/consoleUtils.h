#ifndef COSMODROME_CONSOLEUTILS_H
#define COSMODROME_CONSOLEUTILS_H

#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <iomanip>

using std::string;
using std::cout;
using std::cin;
using std::istringstream;

/*
 * Функции в этом файле принимают валидаторы
 *
 * Валидатор - это функция, которая на основании
 * переданного ей значения возвращает логичеескую переменную
 * значение которой сообщает подходит ли нам пользовательский ввод,
 * или нет
 *
 * Функции валидаторы имеют общий интерфейс оисанный здесь
 *
 * Сами функции валидаторы - объявляются там, где используются
 */

// TODO: хорошо бы функции валидаторы переписать таким образом
//  чтобы они возвращали не только bool, но ещё и строку
//  с ошибкой, чтобы пользователь знал точнее, что не так

// интерфейс для валидирования ввода строки
// создаём указатель на функцию через класс function
// чтобы мы могли использовать лямбда - функции
// почти аналогично строке:
// using ValidateString = bool (*)(string);
using ValidateString = std::function<bool(string)>;

// интерфейс для валидирования ввода числа
// создаём указатель на функцию через класс function
// чтобы мы могли использовать лямбда - функции
// почти аналогично строке:
// using ValidateNum = bool (*)(int);
using ValidateNum = std::function<bool(int)>;

// интерфейс для валидирвоания ввода символа
// создаём указатель на функцию через класс function
// чтобы мы могли использовать лямбда - функции
// почти аналогично строке:
// using ValidateChar = bool (*)(char);
using ValidateChar = std::function<bool(char)>;

// интерфейс для валидирвоания ввода даты и времени
// создаём указатель на функцию через класс function
// чтобы мы могли использовать лямбда - функции
// почти аналогично строке:
// using ValidateChar = bool (*)(char);
using ValidateDateTime = std::function<bool(std::tm)>;

// функция считывания даты и времени
// в формате: 04.05.2018-12:10
// возвращает объект даты и времени tm
// принимает строку запроса, валидатор (опционально)
// а также, поток ввода (опционально)
std::tm getEnteredDateTime(string text, ValidateDateTime validate = nullptr, std::istream &in = cin);

// функция считывнаия строки с консоли
// возвращает считанную строку
// строку запроса, поток ввода (опционально) и
// принимает валидатор ввода (опционально)
string getEnteredString(string text, ValidateString validate = nullptr, std::istream &in = cin);

// функция считывнаия числа с консоли
// возвращает считанное число
// строку запроса, поток ввода (опционально) и
// принимает валидатор ввода
int getEnteredNum(string text, ValidateNum validate = nullptr, std::istream &in = cin);

// функция считывнаия символа с консоли
// возвращает считанный символ
// строку запроса, поток ввода (опционально) и
// принимает валидатор ввода
char getEnteredChar(string text, ValidateChar validate = nullptr, std::istream &in = cin);


#endif //COSMODROME_CONSOLEUTILS_H

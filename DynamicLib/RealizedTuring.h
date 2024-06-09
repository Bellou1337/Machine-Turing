/*
* ИКТИБ ЮФУ
* МОП ЭВМ
* Программная инженерия
* ПИОТА
* Итоговое задание
* Вариант 27.2
* дата: 18.05.2024
* Исполнитель: Иванов А.А, КТбо 1-7
*/
/**
* \file RealizedTuring.h
* \brief Заголовочный файл для определения всех функций  и структур в dll
* \author Иванов А.А, КТбо1-7
* \date Дата последней модификации - 18.05.2024
*/
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <deque>
#include <set>
#include <clocale>
using namespace std;

/**
* \struct data
* \brief В данной структуре содержатся все состояния, необходимые для работы машины
*/
struct data
{
    string name; ///< Поле структуры - имя состояния
    bool last; ///< Поле структуры - булевое значение для того,что знать заключающее ли это состояние
    char symbol; ///< Поле структуры - текущий символ для состояния
    char symbolAdd; ///< Поле структуры - символ который должен поставить в текущую ячейку в данном состоянии
    char action; ///< Поле структуры - Движение головки
    string next; ///< Поле структуры - Имя следующего состояния

};
/**
* \struct machine
* \brief В данной структуре находятся необходимые объекты для работы машины Тьюринга
* \details Для корректной работы необходимы следующие поля: вектор состояний,
* текущее состояние, лента,алфавит машины
*/
struct machine
{
    vector<struct data> UserVec; ///< Вектор для хранения всех состояний
    string head; ///< Текущее состояние машины
    deque<char> ribbon; ///< Лента машины Тьюринга
    set<char> alphabet; ///< Алфавит машины Тьюринга
    int position; ///< Текущий индекс головки
};
/**
* \fn void ReadTuring()
* \brief Считывание данных из файла
* \details Осуществляет считывание данных из файла и
* записывает их вектор, в котором хранится структура данных для каждого
* состояния
*/
extern "C" __declspec(dllexport) void ReadTuring();
/**
* \fn void StartFunc()
* \brief Выполняет полный цикл работы машины Тьюринга
* \details В функции происходит следующее :
* 1. Если мы пришли в заключающее состояние,то происходит остановка машины
* 2. Вызывается функция одного шага машины
* 3. Если произошла ошибка то работа машины также прекращается
* 4. Вызывается функция вывода текущей ленты на экран
*/
extern "C" __declspec(dllexport) void StartFunc();
/**
* \fn void ChangeRibbon()
* \brief Добавляет к исходной ленте пробелы слева и справа
* \param[out] MyTuring.ribbon - текущая лента машины
*/
extern "C" __declspec(dllexport) void ChangeRibbon();
/**
* \fn void InitTuring(string & userWord)
* \brief Инициализирует ленту машины Тьюринга и ставит головку на нужную позицию
* \param[in] userWord исходная строка пользователя
* \param[out] MyTuring.head - имя текущего состояния машины
* \param[out] MyTuring.position - индекс головки
*/
extern "C" __declspec(dllexport) void InitTuring(string&);
/**
* \fn void ClearRibbon()
* \brief Очищает ленту для записи следующего слова пользователя
* \param[out] MyTuring.ribbon - текущая лента машины
*/
extern "C" __declspec(dllexport) void ClearRibbon();
/**
* \fn void ClearMT()
* \brief Очищает вектор состояний для машины Тьюринга
* \param[out] - текущий вектор состояний
*/
extern "C" __declspec(dllexport) void ClearMT();
/**
* \fn bool CheckAlphabet()
* \brief Производит проверку ленты на соответствие алфавиту
*/
extern "C" __declspec(dllexport) bool CheckAlphabet();
/**
* \fn ClearAlphabet()
* \brief Очищает алфавит для текущей машины
* \param[out] - текущий алфавит машины
*/
extern "C" __declspec(dllexport) void ClearAlphabet();
/**
* \fn void RemoveHead()
* \brief Очищает данные о текущем положении головки машины
*/
extern "C" __declspec(dllexport) void RemoveHead();
/**
* \fn void PrintInitialConf()
* \brief Вывод начальной конфигурации на экран
*/
extern "C" __declspec(dllexport) void PrintInitialConf();
/**
* \fn void void RemovePosition()
* \brief Возвращение позиции головки в исходное состояние
* \param[out] MyTruing.position - текущий индекс головки машины
*/
extern "C" __declspec(dllexport) void RemovePosition();
/**
* \fn void PrintResult()
* \brief Осуществляет вывод результата работы машины
* \param[out] stringForPrint - лента машины для вывода на экран
*/
extern "C" __declspec(dllexport) void PrintResult();
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
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <clocale>
using namespace std;

/*
* Что принимает: изначальную строку пользователя
* Что делает: проверяет на валидность строку пользователя
* Что возращает: тип bool, валидная ли строка или нет
*/
bool IsValid(string);

int main()
{
    setlocale(LC_ALL, "Rus");
    cout << "Справка: если слева или справа в строке вы видите _, то это пробел"<<endl;
    HINSTANCE load;
    load = LoadLibrary(L"DynamicLib.dll");
    if (!load)
    {
        cout << "Ошибка подключения библиотеки!" << endl;
        return 0;
    }
    bool flag = 1;
    typedef void (*ChangeRibbon)();
    ChangeRibbon changeRibbon = (ChangeRibbon)GetProcAddress(load, "ChangeRibbon");
    if (!changeRibbon)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*GetFile)();
    GetFile getFile = (GetFile)GetProcAddress(load, "ReadTuring");
    if (!getFile)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*GoTur)();
    GoTur start = (GoTur)GetProcAddress(load, "StartFunc");
    if (!start)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*InitTuring)(string&);
    InitTuring init = (InitTuring)GetProcAddress(load, "InitTuring");
    if (!init)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*ClearRibbon)();
    ClearRibbon clearRibbon = (ClearRibbon)GetProcAddress(load, "ClearRibbon");
    if (!clearRibbon)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*ClearMT)();
    ClearMT clearMT = (ClearMT)GetProcAddress(load, "ClearMT");
    if (!clearMT)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*CheckAlphabet)();
    CheckAlphabet checkAlphabet = (CheckAlphabet)GetProcAddress(load, "CheckAlphabet");
    if (!checkAlphabet)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*ClearAlphabet)();
    ClearAlphabet clearAlphabet = (ClearAlphabet)GetProcAddress(load, "ClearAlphabet");
    if (!clearAlphabet)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*SetStartName)();
    SetStartName remName = (SetStartName)GetProcAddress(load, "RemoveHead");
    if (!remName)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*PrintInitConf)();
    PrintInitConf printInitConf = (PrintInitConf)GetProcAddress(load, "PrintInitialConf");
    if (!printInitConf)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*RemovePosition)();
    RemovePosition removePos = (RemovePosition)GetProcAddress(load, "RemovePosition");
    if (!removePos)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    typedef void(*PrintResult)();
    PrintResult printResult = (PrintResult)GetProcAddress(load, "PrintResult");
    if (!printResult)
    {
        cout << "Ошибка получения указателя на функцию!" << endl;
        return 0;
    }
    while (flag)
    {
        cout << "Введите входное слово: ";
        string userWord;
        cin >> userWord;
        
        //проверка строки на валидность
        bool result = IsValid(userWord);
        // проверка на принадлежность алфавиту
        if (!result)
        {
            cout << "Вы ввели недопустимые символы!" << endl;
            cout << "Хотите попробовать ещё раз? что угодно = да , 0 = нет" << endl;
            string reload;
            cin >> reload;
            if (reload == "0") flag = 0;
        }
        else
        {
            //инициализируем ленту
            init(userWord);
            // добавляем пробелы слева и справа
            changeRibbon();
            //вывод начальной конфигурации
            printInitConf();
            // проверка алфавита
            checkAlphabet();
            //считывание состояний
            getFile();   
            //старт работы машины
            start();
            //вывод результата работы машины
            cout << "Результат: ";
            printResult();
            //очистка ленты
            clearRibbon();
            //очистка вектора состояний
            clearMT();
            //очистка алфавита
            clearAlphabet();
            //очистка имени текущего состояния
            remName();
            //очистка текущей позиции головки
            removePos();
            cout << "Работа машины окончена!" << endl;
            cout << "Хотите ввести слово заново ? что угодно = да, 0 = нет" << endl;
            string reload;
            cin >> reload;
            if (reload == "0") flag = 0;
        }
    }

    FreeLibrary(load);
    return 0;
}
bool IsValid(string word)
{
    for (int i = 0; i < word.size(); ++i)
    {
        if (word[i] != '1') return false;
    }
    return true;
}

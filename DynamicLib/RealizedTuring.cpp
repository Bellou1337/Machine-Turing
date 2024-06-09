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
* \file RealizedTuring.cpp
* \brief Файл c реализацией машины Тьюринга
* \details В данном файле содержится весь программный код для универсальной
* машины Тьюринга, включая все необходимые функции для работы машины, структуру данных
* для хранения состояний, а также функцию для считывания пользовательской информации
* и функцию для вывода данных в консоль.
* \author Иванов А.А, КТбо1-7
* \date Дата последней модификации - 18.05.2024
*/ 
#pragma once
#include "RealizedTuring.h"

struct machine MyTuring; ///< Структура для хранения машины

/**
* \fn void InitTuring(string & userWord)
* \brief Инициализирует ленту машины Тьюринга и ставит головку на нужную позицию
* \param[in] userWord исходная строка пользователя
* \param[out] MyTuring.head - имя текущего состояния машины
* \param[out] MyTuring.position - индекс головки
*/
extern "C" __declspec(dllexport) void InitTuring(string & userWord)
{
	for (int i = 0; i < userWord.size(); ++i)
	{
		MyTuring.ribbon.push_back(userWord[i]);
	}
	MyTuring.head = "q1";
	MyTuring.position = 1;
}
/**
* \fn setAlphabet(string Stralphabet)
* \brief Производит запись алфавита для текущей машины
* \param[in] Stralphabet - текущий алфавит
*/
void setAlphabet(string Stralphabet)
{
	for (int i = 0; i < Stralphabet.size(); ++i)
	{
		if (Stralphabet[i] == 'x') MyTuring.alphabet.insert('_');
		else MyTuring.alphabet.insert(Stralphabet[i]);
	}
}
/**
* \fn void ReadTuring()
* \brief Считывание данных из файла
* \details Осуществляет считывание данных из файла и 
* записывает их вектор, в котором хранится структура данных для каждого
* состояния
*/
extern "C" __declspec(dllexport) void ReadTuring()
{
	setlocale(LC_ALL, "Rus");
    // запись с файла
	ifstream file("input.txt");
	if (!file.is_open())
	{
		cout << "Ошибка при открытии файла!" << endl;
		return;
	}
	// запись алфавита
	string Stralphabet;
	file >> Stralphabet;
	setAlphabet(Stralphabet);
	// запись состояний
	string name;
	bool last;
	char symbol;
	char symbolAdd;
	char action;
	string next;
	while(file >> name >> last >> symbol >> symbolAdd >> action >> next)
	{		
		if (symbol == 'x') symbol = '_';
		if (symbolAdd == 'x') symbolAdd = '_';
		MyTuring.UserVec.push_back({ name,last,symbol,symbolAdd,action,next });
	}
	file.close();

};

/**
* \fn bool CheckAlphabet()
* \brief Производит проверку ленты на соответствие алфавиту
*/
extern "C" __declspec(dllexport) bool CheckAlphabet()
{
	for (int i = 0; i < MyTuring.ribbon.size(); ++i)
	{
		if (!MyTuring.alphabet.count(MyTuring.ribbon[i])) return false;
	}
	return true;
}
/**
* \fn void ResizeString(struct machine& MyTuring)
* \brief Осуществляет расширение ленты по надобности
* \param[out] MyTuring.position - текущий индекс ячейки
* \param[in] machine&MyTuring - структура для машины Тьюринга
*/
void ResizeString(struct machine& MyTuring)
{
	if (MyTuring.position < 0)
	{
		MyTuring.position = 0;
		MyTuring.ribbon.push_front('_');
	}
	else if (MyTuring.position >= MyTuring.ribbon.size())
	{
		MyTuring.ribbon.push_back('_');
	}
}
/**
* \fn void PrintErrorComand()
* \brief Осуществляет вывод ошибки для несуществующей команды движения
* головки
*/
void PrintErrorComand()
{
	setlocale(LC_ALL, "Rus");
	cout << "Ошибка! такой команды не существует..." << endl;
}
/**
* \fn void PrintErrorAlpha()
* \brief Осуществляет вывод ошибки для несуществующего символа
*/
void PrintErrorAlpha()
{
	setlocale(LC_ALL, "Rus");
	cout << "Ошибка! такого символа нет в алфавите!" << endl;
}
/**
* \fn void PrintResult()
* \brief Осуществляет вывод результата работы машины
* \param[out] stringForPrint - лента машины для вывода на экран
*/
extern "C" __declspec(dllexport) void PrintResult()
{
	
	string searchRibbon = string(MyTuring.ribbon.begin(), MyTuring.ribbon.end());
	string stringForPrint = searchRibbon.substr(0, MyTuring.position) + "<" + MyTuring.head + ">" + searchRibbon.substr(MyTuring.position, searchRibbon.size());
	cout<< stringForPrint << endl;
}
/**
* \fn void PrintConfig(struct machine& MyTuring)
* \brief Выводит ленту на экран
* \details Собирает строку из deque, затем добавляет в неё состояние и
* выводит на экран
* \param[in] struct machine& MyTuring - структура для машины Тьюринга
*/
void PrintConfig(struct machine& MyTuring)
{
	string searchRibbon = string(MyTuring.ribbon.begin(), MyTuring.ribbon.end());
	string stringForPrint = searchRibbon.substr(0, MyTuring.position) + "<" + MyTuring.head + ">" + searchRibbon.substr(MyTuring.position, searchRibbon.size());
	cout << stringForPrint << endl;

}
/**
* \fn void OneAction(struct data temp,bool& error)
* \brief Осуществляет выбор одного действия машины
* \param[in] struct data temp - текущее состояние машины
* \param[in] bool error - флажок для ошибки
*/
void OneAction(struct data temp,bool& error)
{
	if (temp.action == 'L')
	{
		MyTuring.position--;
		ResizeString(MyTuring);
	}
	else if (temp.action == 'R')
	{
		MyTuring.position++;
		ResizeString(MyTuring);
	}
	else if (temp.action != 'S')
	{
		PrintErrorComand();
		error = 1;
	}
}
/**
* \fn void OneStepTur(bool& error)
* \brief Выполняет один шаг машины Тьюринга
* \details В функции происходит следующее :
* 1. Выводится на экран текущее слово вместе с текущим состоянием и позицией головки
* 2. Происходит обход всех состояних до тех пор, пока не найдёт, то которое нужно
* 3. При нахождении нужного состояния происходит запись символа в текущую ячейку, а также сдвиг головки, в соответствии с командой
* 4. В случае возникновения ошибки вызываются соответствующие функции
* \param[out] position текущий индекс ячейки
* \param[out] checker булевская переменная для определения конца работы машины
* \param[out] head имя текущего состояния, которое нужно найти
* \param[in] error флажок для обработки ошибки в случае её возникновения
*/
void OneStepTur(bool& error)
{
	bool flag = 1;
	for (int i = 0; i < MyTuring.UserVec.size() && flag; ++i)
	{
		struct data temp = MyTuring.UserVec[i];
		if (temp.name == MyTuring.head && temp.symbol == MyTuring.ribbon[MyTuring.position])
		{
			MyTuring.ribbon[MyTuring.position] = temp.symbolAdd;
			OneAction(temp,error);
			if (error) break;
			MyTuring.head = temp.next;
			flag = 0;
		}
		else if (!MyTuring.alphabet.count(temp.symbol))
		{
			PrintErrorAlpha();
			error = 1;
			break;
		}
	}
}
/**
* \fn void StartFunc()
* \brief Выполняет полный цикл работы машины Тьюринга
* \details В функции происходит следующее :
* 1. Если мы пришли в заключающее состояние,то происходит остановка машины
* 2. Вызывается функция одного шага машины
* 3. Если произошла ошибка то работа машины также прекращается
* 4. Вызывается функция вывода текущей ленты на экран
*/
extern "C" __declspec(dllexport) void StartFunc()
{
	setlocale(LC_ALL, "Rus");
	int counter = 10000;
	while (true && counter)
	{
		bool error = 0;
		if (MyTuring.head == "q0")
		{
			break;
		}
		OneStepTur(error);
		if (error) break;
		PrintConfig(MyTuring);
		counter--;
	}
	if(!counter)
	{
		cout << "Извините, но машина не может делать более 10000 шагов" << endl;
		cout << "Попробуйте уменьшить входное слово" << endl;
	}
}
/**
* \fn void ChangeRibbon()
* \brief Добавляет к исходной ленте пробелы слева и справа
* \param[out] MyTuring.ribbon - текущая лента машины
*/
extern "C" __declspec(dllexport) void ChangeRibbon()
{
	MyTuring.ribbon.push_back('_');
	MyTuring.ribbon.push_front('_');
}

/**
* \fn void ClearRibbon()
* \brief Очищает ленту для записи следующего слова пользователя
* \param[out] MyTuring.ribbon - текущая лента машины
*/
extern "C" __declspec(dllexport) void ClearRibbon()
{
	MyTuring.ribbon.clear();
}
/**
* \fn void ClearMT()
* \brief Очищает вектор состояний для машины Тьюринга
* \param[out] - текущий вектор состояний
*/
extern "C" __declspec(dllexport) void ClearMT()
{
	MyTuring.UserVec.clear();
}
/**
* \fn ClearAlphabet()
* \brief Очищает алфавит для текущей машины
* \param[out] - текущий алфавит машины
*/
extern "C" __declspec(dllexport) void ClearAlphabet()
{
	MyTuring.alphabet.clear();
}
/**
* \fn void RemoveHead()
* \brief Очищает данные о текущем положении головки машины
*/
extern "C" __declspec(dllexport) void RemoveHead()
{
	MyTuring.head.clear();
}
/**
* \fn void PrintInitialConf()
* \brief Вывод начальной конфигурации на экран
*/
extern "C" __declspec(dllexport) void PrintInitialConf()
{
	string strForPrint = string(MyTuring.ribbon.begin(),MyTuring.ribbon.end());
	string begin = strForPrint.substr(0, MyTuring.position) + "<q1>" + strForPrint.substr(MyTuring.position, strForPrint.size());
	cout<< begin << endl;
}
/**
* \fn void void RemovePosition()
* \brief Возвращение позиции головки в исходное состояние
* \param[out] MyTruing.position - текущий индекс головки машины
*/
extern "C" __declspec(dllexport) void RemovePosition()
{
	MyTuring.position = 1;
}
///\file
///\details Реализация класса реализующего вывод информации на консоль.

#include <iostream>

#include "Log2Console.h"



/**
 * \brief Конструктор класса для отображения строк лога из класса логера.
 * \param[in] loger указатель на логер.
 * \param[in] parent указатель на родителя.
 * \return Конструктор не возвращает ничего.
 *
 * \n
 */
Log2Console::Log2Console(Loger *loger, QObject *parent): QObject{parent}
      , loger_(loger)
      , logList_(0)
{

    if (loger_ == 0){
        loger_ = Loger_global::instance();
    }

    logList_ = loger->getLogList();

    for (int i = 0; i < logList_->size(); ++i){
        showLogLine(i);
    }

    connect(loger_, &Loger::newLineInserted, this, &Log2Console::insertNewLine);
    connect(loger_, &Loger::lastLineUpdated, this, &Log2Console::updateLastLine);

}


/**
 * \brief Деструктор класса для отображения строк лога из класса логера.
 * \return Деструктор не возвращает ничего.
 *
 * \n
 */
Log2Console::~Log2Console(){

}


/**
 * \brief Слот вставки новой строки в виджет.
 * \return Слот не возвращает ничего.
 *
 * \n
 */
void Log2Console::insertNewLine() {
    showLogLine(logList_->size() - 1);
}



/**
 * \brief Слот для обновления последней строки в виджете (расширения или указания ошибочного завершения).
 * \return Слот не возвращает ничего.
 *
 * \n
 */
void Log2Console::updateLastLine() {
    //TODO Удалить последнюю стку из консоли???
    showLogLine(logList_->size() - 1);
}


/**
 * \brief Метод вывода строки лога на консоль.
 * \param[in] lineNum выводимая строка лога.
 * \return Не возвращает ничего.
 *
 * \n
 */
void Log2Console::showLogLine (int lineNum){

    // Если номер строки указывает на валидные данные в списке строк лога.
    if(lineNum < logList_->size()){

        Loger::LogLine line = logList_->at(lineNum);

        if(line.getLogerLevel() <= Loger::LogerLevels::LL_WARNING){
            std::cerr << line.getLine().toStdString() << std::endl;
        }else{
            std::cout << line.getLine().toStdString() << std::endl;
        }
    }
}


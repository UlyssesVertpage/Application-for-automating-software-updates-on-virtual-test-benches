///\file
///\details Описание класса реализующего вывод информации на консоль.
#ifndef LOG2CONSOLE_H
#define LOG2CONSOLE_H

#include <QWidget>

#include "Loger.h"


/**
 * \brief Класс для отображения строк лога из класса логера на консоли.
 *
 */
class Log2Console: public QObject
{
    
    Q_OBJECT
    
public:
    
    // Конструтор, создающий виджет, получающий строки из локального логера loger.
    Log2Console(Loger *loger, QObject *parent = nullptr);

    // Деструктор
    ~Log2Console();
    
public slots:

    // Слот вывода последней строки лога на консоль.
    void insertNewLine();

    // Слот обновления последней строки лога на консоли.
    void updateLastLine();

private:
    
    // Метод вывода строки лога на консоль.
    void showLogLine (int lineNum);

    /// Указатель на считываемый логер.
    Loger *loger_;

    /// Указатель на данные лога.
    const QList<Loger::LogLine> * logList_;
    
};

#endif // LOG2CONSOLE_H



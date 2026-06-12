#ifndef LOGERCRASHDUMPER_H
#define LOGERCRASHDUMPER_H

#include <QObject>
#include <QString>
#include <QDateTime>

class QFile;
class QTextStream;
class Loger;

/**
 * \brief Класс дампа.
 *
 * \n
 * Класс обеспечивает запись логов в файл при внештатном падении приложения
 */

class LogerCrashDumper : public QObject {
    Q_OBJECT

public:
    explicit LogerCrashDumper(Loger *loger, QObject *parent = nullptr);

    /// Деструктор класса.
    ~LogerCrashDumper() override;

    /// Метод инициализации класса, в которой передаётся путь для файла, в который запишется дамп.
    bool initialize(const QString &filePath);

    /// Метод завершения работы при плановом завершении работы программы.
    void shutdownNormally();

    /// Геттер инстанса класса.
    static LogerCrashDumper *instance();

private:

    /// Метод для написания даты начала работы с логером в дамп.
    void writeDump(const QString &reason, int signalValue = 0);

    /// Метод отлова исключений.
    static void terminateHandler();

    /// Метод обработчик сигналов при падении.
    static void signalHandler(int signalValue);

private:

    /// Указатель на логер.
    Loger *loger_;

    /// Счётчик записаных строк в дамп.
    int flushedCount_;

    /// Флаг инициализации класса дампа.
    bool initialized_;

    /// Флаг планового завершения работы.
    bool normalShutdown_;

    /// Строка, в которой указан путь до файла с дампом.
    QString filePath_;

    /// Время начала работы с логером.
    QDateTime startTime_;

    /// Флаг записи дампа при падении.
    bool crashWritten_;

    /// Указатель на свой инстанс.
    static LogerCrashDumper *instance_;

};
#endif // LOGERCRASHDUMPER_H

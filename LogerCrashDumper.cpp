#include "LogerCrashDumper.h"
#include "Loger.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <cstdlib>
#include <exception>
#include <csignal>

LogerCrashDumper *LogerCrashDumper::instance_ = nullptr;

LogerCrashDumper::LogerCrashDumper(Loger *loger, QObject *parent)
    : QObject(parent),
      loger_(loger),
      flushedCount_(0),
      initialized_(false),
      normalShutdown_(false),
      crashWritten_(false)
{
  instance_ = this;

}

/**
 * \brief Сеттер цветового оформления конкретного уровня логирования, для указанной темы.
 * \return void.
 *
 * \n
 */
LogerCrashDumper::~LogerCrashDumper(){

    if(instance_ == this){
        instance_ = nullptr;
    }
}


/**
 * \brief Метод инициализации класса.
 * \param[in] filePath. Путь для файла с дампом.
 * \return void.
 *
 * \n
 */
bool LogerCrashDumper::initialize(const QString &filePath){

    filePath_ = filePath;
    startTime_ = QDateTime::currentDateTime();

    std::set_terminate(&LogerCrashDumper::terminateHandler);
    std::signal(SIGSEGV, &LogerCrashDumper::signalHandler);
    std::signal(SIGABRT, &LogerCrashDumper::signalHandler);
    std::signal(SIGFPE, &LogerCrashDumper::signalHandler);
    std::signal(SIGILL, &LogerCrashDumper::signalHandler);

    initialized_ = true;
    return true;
}

/**
 * \brief Метод завершения работы при плановом завершении работы программы.
 * \return void.
 *
 * \n
 */
void LogerCrashDumper::shutdownNormally(){
    normalShutdown_ = true;
}



LogerCrashDumper *LogerCrashDumper::instance(){
    return instance_;
}

/**
 * \brief Метод для записи информации в дамп.
 * \param[in] reason. Причина падения.
 * \param[in] signalValue. Значение сигнала при падении.
 * \return void.
 *
 * \n
 */
void LogerCrashDumper::writeDump(const QString &reason, int signalValue){
    if(crashWritten_){
        return;
    }

    QFile file(filePath_);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream stream(&file);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    stream->setEncoding(QStringConverter::Utf8);
#endif
    stream << "\n===== CRASH DUMP =====\n";
    stream << "Application started: " << startTime_.toString( "yyyy-MM-dd HH:mm:ss" ) << "\n";
    stream << "Crash time: " << QDateTime::currentDateTime().toString( "yyyy-MM-dd HH:mm:ss" ) << "\n";
    stream << "Reason: " << reason << "\n";

    if (signalValue != 0){
        stream << "Signal: ";

        switch(signalValue) {
        case SIGSEGV:
            stream << "SIGSEGV";
            break;
        case SIGABRT:
            stream << "SIGABRT";
            break;
        case SIGFPE:
            stream << "SIGFPE";
            break;
        case SIGILL:
            stream << "SIGILL";
            break;
        default:
            stream << "UNKNOWN";
            break;

        }
        stream << "\n";
    }

    if (reason == "std::terminate"){
        try {
            std::exception_ptr exptr = std::current_exception();
            if(exptr){
                std::rethrow_exception(exptr);
            }
            stream << "Exception unknown " << "\n";
        }
        catch (const std::exception &ex) {
            stream << "Exception: " << ex.what() <<"\n";
        }
        catch(...){
            stream << "Non-std exception";
        }

    }

    auto *list = loger_->getLogList();
    if (list != nullptr){
        flushedCount_ = list->size();
        for (int i = 0; i < list->size(); ++i){
            const auto &line = list->at(i);
            stream << "[" << line.getLogerLevel() << "] " << line.getLine() << "\n";

        }
    }

    stream.flush();
    file.flush();
    file.close();
    crashWritten_ = true;
}

/**
 * \brief  Метод сохранения дампа при падении.
 * \param[in] signalValue. Сигнал падения.
 * \return void.
 *
 * \n
 */
void LogerCrashDumper::signalHandler(int signalValue){
    if (instance_ != nullptr){
        instance_->writeDump("signal crash", signalValue);
    }
    std::_Exit(128 + signalValue);

}

/**
 * \brief  Метод сохранения дампа при исключениях.
 * \return void.
 *
 * \n
 */
void LogerCrashDumper::terminateHandler(){
    if (instance_ != nullptr){
        instance_->writeDump("std::terminate");
    }
    std::_Exit(1);

}

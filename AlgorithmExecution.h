#ifndef ALGORITHMEXECUTION_H
#define ALGORITHMEXECUTION_H

#include <QObject>
//#include <QThread>
#include <QtConcurrent/QtConcurrent>
//#include <QProcess>

//#include <libssh2.h>

//#include "MainWindow.h"
#include "GlobalData.h"
#include "LogViewer.h"

#include <atomic>


class AlgorithmExecution : public QObject
{
    
    Q_OBJECT
    
public:
    
    AlgorithmExecution(const QString& abnName, const QString& algName, QObject* parent = nullptr);      // P.S.: Launcher создаёт экземпляр этого класса в новом для него потоке --> родителя быть не может.
    //AlgorithmExecution(QObject* parent, MainWindow* mainWindow);              // Создаётся из под Launcher'а, родитель должен быть.
    
    ~AlgorithmExecution();
    
    
    
    //std::atomic<bool> eventLoopCheck_{false};
    
    
    
public slots:
    
    
    ///
    bool getStopFlag() { return stopFlag_; }
    
    ///
    void execute();
    
    
    //void checkEventLoop() { eventLoopCheck_ = true; }
    
    ///
    //Q_INVOKABLE void terminationRequired();
    void terminationRequired();
    
    
    
    
    //
    void processErrorOccurred(QProcess::ProcessError error);
    //
    void processStarted();
    ////
    //void processReadyReadStandardOutput();
    
    ////
    //void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    ///
//    void stopSignalReceived();
    
    
    
    
    
signals:
    
    ///
    void processReturnedResult(const QString& abnNameFinished, int exitCode, int exitStatus, bool stopFlag);
    ///
    void algorithmExecutionFinished(const QString& abnName, const QString& objName, int exitCode, int exitStatus, bool stopFlag_);
    ///
    void logUpdated(const QString msg);
    // TODO: ЭТО ДЛЯ ПРЕЗЫ, МОЖНО УБИРАТЬ ПОСЛЕ ПОКАЗА НА "НИР".    
    /////
    //void updateSuccessView(const QString& abnName);
    
    
    
private:
    
    
    bool stopFlag_{};
    
    //MainWindow* mainWindow_;
    
    /// Имя исполняемого абонента
    QString abnName_;
    /// Имя запускаемого алгоритма
    QString algName_;
    
    ///
    const AbonentInfo& abnInfo_;
    ///
    const AlgorithmInfo& algInfo_;
    
    /// Процесс выполнения подключения
    QProcess* process_;
    
};

#endif // ALGORITHMEXECUTION_H

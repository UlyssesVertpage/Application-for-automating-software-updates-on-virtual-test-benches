#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QtConcurrent/QtConcurrentMap>
#include <QElapsedTimer>

#include "Globals.h"
#include "GlobalData.h"
#include "LogViewer.h"
#include "AlgorithmExecution.h"

#include <exception>





class TerminationWrapper : public QObject
{
    
    Q_OBJECT
    
public:
    
    TerminationWrapper(AlgorithmExecution* algExec, QObject* parent = nullptr)
        : QObject{parent}
        , algExec_{algExec}
    {
        connect(this, &TerminationWrapper::terminationRequired, algExec_, &AlgorithmExecution::terminationRequired, Qt::QueuedConnection);
    }
    
    void terminateExecution() {
        emit terminationRequired();
    }
    
signals:
    void terminationRequired();
    
private:
    ///
    AlgorithmExecution* algExec_;
    
};








class Launcher : public QObject
{
    
    Q_OBJECT
    
public:
    
    ~Launcher();
    
    Launcher(QMap<QString, AbonentGroupsViewInfoMap>&& map, const QString& algName, QObject *parent = nullptr);

    ///
    QMap<QString, AbonentGroupsViewInfoMap>& getChosenAbonentsMap() { return chosenAbonentsViewInfoMap_; }
    ///
    int getChosenAbonentsMapSize() { return chosenAbonentsViewInfoMap_.size(); }
    
    ///
    void setUpFutures();
    
    
    
public slots:
    
    ///
    void terminateOneAbonentExecutionSlot(const QString& abnName);
    ///
    void terminateAllAbonentsExecutionsSlot();
    
    
    
signals:
    
    ///
    void allThreadsFinished();
    
    ///
    void algExecCreated(const QString& abnName, const QString& objName);
    ///
    void algExecDestroyed(const QString& abnName, const QString& objName);
    ///
    void processReturnedResult(const QString& abnNameFinished, int exitCode, int exitStatus, bool stopFlag);
    
    
    
private:

    QMap<QString, bool> finishMap_;
    
    QMap<QString, QThread*> algThreadsMap_;
    
    QMap<QString, AlgorithmExecution*> algExecMap_;
    
    QMap<QString, AbonentGroupsViewInfoMap> chosenAbonentsViewInfoMap_;
    
    QMap<QString, AbonentLogStruct>& abonentsLogsMap_;
    
    
    int startThreadCount_;
    
    QAtomicInt finishedThreadCount_ = 0;
    
    
    // ИНФОРМАЦИЯ ПО АЛГОРИТМУ
    QString algName_;
    
    
    
};

#endif // LAUNCHER_H

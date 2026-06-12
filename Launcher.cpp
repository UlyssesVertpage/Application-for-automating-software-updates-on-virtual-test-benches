

#include "Launcher.h"






Launcher::Launcher(QMap<QString, AbonentGroupsViewInfoMap>&& map, const QString& algName, QObject* parent)
    : QObject{parent}
    , chosenAbonentsViewInfoMap_{std::move(map)}
    , abonentsLogsMap_(GlobalData::instance().getAbonentsLogsMap())
    , algName_{algName}
{
    
    setObjectName("Launcher_inst");
    LOG_REG_OBJNAME(objectName());
    LOG_ADD_OBJNAME(objectName());
    
    
    for (const QString& abnName: chosenAbonentsViewInfoMap_.keys()) {
        finishMap_[abnName] = false;
    }    
    

}




Launcher::~Launcher() {
        
    qDebug().noquote() << "Launcher::~Launcher: Launcher deleted, there were abonents:";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "Launcher::~Launcher: Launcher deleted, there were abonents:");
    
}



void Launcher::setUpFutures() {
    
    // Задание числа задействованных потоков.
    startThreadCount_ = chosenAbonentsViewInfoMap_.size();

    
    // =========================== ЗАПУСК АЛГОРИТМОВ И СОХРАНЕНИЕ ЭКЗЕМПЛЯРОВ ПОТОКОВ ===========================
    
    for (QString& abnName : chosenAbonentsViewInfoMap_.keys()) {
        
        // TODO: собсно вот здесь нам и надо передавать некий LogViewAbonent как обёртку, а не Loger и LogViewer.
        Loger* loger = abonentsLogsMap_[abnName].loger;
        LogViewer* logViewer = abonentsLogsMap_[abnName].logViewer;
        
        QThread* thread = new QThread;
        AlgorithmExecution* algorithmExecution = new AlgorithmExecution(abnName, algName_);
        algThreadsMap_.insert(abnName, thread);
        algExecMap_.insert(abnName, algorithmExecution);
        
        connect(algorithmExecution, &AlgorithmExecution::algorithmExecutionFinished, this, [this](const QString& abnName, const QString& objName) {
            emit algExecDestroyed(abnName, objName);
        }, Qt::QueuedConnection);
        
        connect(algorithmExecution, &AlgorithmExecution::logUpdated, loger, &Loger::handleRawLog, Qt::QueuedConnection);
        
        connect(algorithmExecution, &AlgorithmExecution::algorithmExecutionFinished, this,
                [this, thread, algorithmExecution](const QString& abnName, const QString& objName, int exitCode, int exitStatus, bool stopFlag) mutable {
            
            finishMap_[abnName] = true;
            
            emit processReturnedResult(abnName, exitCode, exitStatus, stopFlag);            
            
            QString logstr = QString("Launcher::launchAlgorithmExecution: Handling algorithmExecutionFinished from algExec: \nResult from abonent: %1, Is current Thread global?: %2, Current Thread's ID: %3")
                                 .arg(abnName)
                                 .arg(QVariant(QThread::currentThread() == QCoreApplication::instance()->thread()).toString())
                                 .arg(QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()), 0, 16));
            qDebug().noquote() << logstr;
            LogerGlobal::instance().addMessageToGlobalLog(objName, Loger::LL_DEBUG, logstr);
            
            algorithmExecution->deleteLater();
            algorithmExecution = nullptr;
            QString logstr1 = QString("Launcher: algExec for %1 is NULLPTR NOW").arg(abnName);
            qDebug().noquote() << logstr1;
            LogerGlobal::instance().addMessageToGlobalLog(objName, Loger::LL_DEBUG, logstr1);
            
            // NOTE: ...а этот вызывается ниже "emit processReturnedResult", т.к. дальше в методе вызывается allThreadsFinished и --> launcherDone.
            //whenAlgorithmFinished(abnName, exitCode, stopFlag);
            int currentFinished = finishedThreadCount_.fetchAndAddOrdered(1) + 1;
            if (currentFinished == startThreadCount_) {
                // Все потоки завершены
                emit allThreadsFinished();
            }

            thread->quit();
            
        }, Qt::QueuedConnection);

        connect(thread, &QThread::started, algorithmExecution, &AlgorithmExecution::execute);
        
        connect(thread, &QThread::destroyed, [this, thread]() mutable {
            //algThreadsMap_[abnName] = nullptr;        // Главное не так, ибо Launcher может удаляться раньше, чем остальные потоки и AlgExec
            thread = nullptr;                           // БЕЗ mutable будет ошибка --- assignment of read-only variable ‘thread’
        });

        
        
        emit algExecCreated(abnName, algorithmExecution->objectName());

        
        
        
        
        QString logstr = QString("Launcher::setUpFutures: Creating Thread for abonent: %1, Is current Thread global?: %2, Current Thread's ID: %3")
                     .arg(abnName)
                     .arg(QVariant(QThread::currentThread() == QCoreApplication::instance()->thread()).toString())
                     .arg(QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()), 0, 16));
        qDebug().noquote() << logstr;
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, logstr);
        
        algorithmExecution->moveToThread(thread);
        thread->start();
        
    }    

        
}









void Launcher::terminateOneAbonentExecutionSlot(const QString& abnName) {
    
    qDebug().noquote() << "Launcher::terminateAlgorithmExecution: STOPPING execution on" << abnName;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_WARNING, "Launcher::terminateAlgorithmExecution: STOPPING execution on " + abnName);
    
    QString logstr = QString("Launcher::terminateAlgorithmExecution: Is current Thread global?: %1, Current Thread's ID: %2")
                 .arg(QVariant(QThread::currentThread() == QCoreApplication::instance()->thread()).toString())
                 .arg(QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()), 0, 16));
    
    qDebug().noquote() << logstr;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_WARNING, logstr);

    TerminationWrapper(algExecMap_[abnName]).terminateExecution();

}




void Launcher::terminateAllAbonentsExecutionsSlot() {
        
    qDebug().noquote() << "Launcher::terminateAllAbonentsExecutions: STOPPING executions on ALL ABONENTS (!)";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_WARNING, "Launcher::terminateAllAbonentsExecutions: STOPPING executions on ALL ABONENTS (!)");
    
    QString logstr = QString("Launcher::terminateAllAbonentsExecutions: Is current Thread global?: %1, Current Thread's ID: %2")
            .arg(QVariant(QThread::currentThread() == QCoreApplication::instance()->thread()).toString())
            .arg(QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()), 0, 16));
    
    qDebug().noquote() << logstr;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_WARNING, logstr);
    
    for (const QString& abnName: chosenAbonentsViewInfoMap_.keys()) {
        AlgorithmExecution* algExec = algExecMap_[abnName];
        if (algExec != nullptr && finishMap_[abnName] == false) {
            TerminationWrapper(algExec).terminateExecution();               //QMetaObject::invokeMethod(algExec, "terminationRequired", Qt::QueuedConnection);
        }
    }
}





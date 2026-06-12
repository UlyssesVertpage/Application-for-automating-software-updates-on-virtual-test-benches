
#include "AlgorithmExecution.h"




AlgorithmExecution::AlgorithmExecution(const QString& abnName, const QString& algName, QObject* parent)
    : QObject{parent}
    , abnName_{abnName}                                                                 // TODO: В WSL фигурные скобки интерпретируются 
    , algName_{algName}                                                                 // как список инициализации...
    //, algInfo_{GlobalData::instance().getAlgorithmsMap()[algName]}    // Не сможет взять так элемент..
    , abnInfo_(GlobalData::instance().getAbonentsMap().find(abnName).value())           // Надо заменять на круглые скобки 
    , algInfo_(GlobalData::instance().getAlgorithmsMap().find(algName).value())         // для WSL и его версий инструментов
{
    setObjectName(QString("AlgExec_%1_inst").arg(abnName));
    //LOG_REG_OBJNAME(objectName())
    //LOG_ADD_OBJNAME(objectName())
    
}



// CHECK:
void AlgorithmExecution::terminationRequired() {
    
    
    // NOTE:
    //       Можно использовать связку из QConnection::Connection, QEventLoop и QTimer::singleShot для
    //       неблокирования потока событий, пока этот метод будет пытаться закрыть QProcess выполнения алгоритма
    
    
    QString logstr = QString("AlgorithmExecution::terminationRequired: Abonent %1.\nIs current Thread global?: %2, Current Thread's ID: %3")
                 .arg(abnName_)
                 .arg(QVariant(QThread::currentThread() == QCoreApplication::instance()->thread()).toString())
                 .arg(QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()), 0, 16));
    
    qDebug().noquote() << logstr;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_WARNING, logstr);
    
    
    
    
    qDebug().noquote() << QString("%1: Terminanting algExec (SIGTERM)").arg(abnName_);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_WARNING, QString("%1: Terminanting algExec (SIGTERM)").arg(abnName_));
    
    if (process_ != nullptr) {
        stopFlag_ = true;
        process_->terminate();
        
        // TODO: Перепроверить, стоит ли делать килл за 100 мс.
        // CHECK: С этим кодом было падение через SIGPIPE (Broken pipe).
        if (!process_->waitForFinished(100)) {
            qDebug().noquote() << QString("%1: Killing algExec (SIGKILL)").arg(abnName_);
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_WARNING, QString("%1: Killing algExec (SIGKILL)").arg(abnName_));
            process_->kill();
        }
    }
}




AlgorithmExecution::~AlgorithmExecution() {
    
    // TODO: Сделать нужного вида лог-сообщение (соотв-й уровень лог-я) и указание кода и статуса завершения...
    //       а то вечно 'пустое' и зелёное "ALG FINISHED FOR..." уже не катит.
    emit logUpdated(QString("ALG FINISHED FOR %1").arg(abnName_));
    //emit algorithmExecutionFinished(abnName_, objectName());
    
    //qDebug().noquote() << QString("AlgorithmExecution::~AlgorithmExecution: %1").arg(LOG_BOOL(eventLoopCheck_));
    //LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::~AlgorithmExecution: %1").arg(LOG_BOOL(eventLoopCheck_)));
    
    qDebug().noquote() << "AlgorithmExecution::~AlgorithmExecution: finished for" << abnName_ << "at the thread " << QThread::currentThreadId();
    // LogerGlobal::instance().addGlobalMessageToLog(Loger::LL_TRACE, QString("AlgorithmExecution::~AlgorithmExecution: finished for %1 at the thread %2").arg(abnName_).arg(QVariant(QThread::currentThreadId())).toStdString());
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::~AlgorithmExecution: finished for %1 at the thread %2")
                                                                  .arg(abnName_).arg(QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()), 0, 16)));
    process_ = nullptr;
}


void AlgorithmExecution::processErrorOccurred(QProcess::ProcessError error) {
    qDebug().noquote() << "AlgorithmExecution::processErrorOccurred: error is" << error;
    // TODO: Работает ли тут в конце помещение error в QString, чтоб выводился как строка, а не как число?
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::processErrorOccurred: error is %1").arg(QString(error)));
}

void AlgorithmExecution::processStarted() {
    qDebug().noquote() << "AlgorithmExecution::processStarted.";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::processStarted."));
}

//void AlgorithmExecution::processReadyReadStandardOutput() {
//    qDebug().noquote() << "AlgorithmExecution::processReadyReadStandardOutput.";
//    LogerGlobal::instance().addGlobalMessageToLog(Loger::LL_TRACE, QString("AlgorithmExecution::processReadyReadStandardOutput."));
//    emit logUpdated();   
//}




//void AlgorithmExecution::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
//    qDebug().noquote() << "AlgorithmExecution::processFinished: THREAD" << QThread::currentThreadId() << "finished with exit code" << exitCode << "and exit status" << static_cast<int>(exitStatus);
//    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::processFinished: THREAD %1 finished with exit code %2 and exit status %3")
//                                                                  .arg(QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()), 0, 16))
//                                                                  .arg(exitCode)
//                                                                  .arg(static_cast<int>(exitStatus)));
//    if (process_ != nullptr) {
//        delete process_; 
//    }
//}





void AlgorithmExecution::execute() {
    
    // ОБЯЗАТЕЛЬНО через указатель, т.к. ссылка умирает под конец функции
    process_ = new QProcess(this);
    
    
    // NOTE: Хорошая опция, когда нужно сростить каналы (стандартный и ошибочный) в один единный (в standard)
    //process_->setProcessChannelMode(QProcess::MergedChannels);
    
    
    // 1.
    QTemporaryFile *tempFile = nullptr;
    
    // 2.
    // QFile file;
    
    
    
    // ===================================== КУЧА КОННЕКТОВ К ПРОЦЕССУ =====================================
    connect(process_, &QProcess::started, this, &AlgorithmExecution::processStarted);
    //connect(&process, &QProcess::readyReadStandardOutput, this, &AlgorithmExecution::processReadyReadStandardOutput);
    
    connect(process_, &QProcess::readyReadStandardError, [this]() {
        //connect(process_, &QProcess::readyReadStandardOutput, [this, process_]() {
        qDebug().noquote() << "AlgorithmExecution::execute: QProcess::readyReadStandardError emited";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::execute: QProcess::readyReadStandardError emited"));
        // NOTE: НА ОБРАБОТКУ ЛОГЕРУ УХОДИТ ТРИММИРОВАННАЯ СТРОЧКА (!)
        QString str = QString(process_->readAllStandardError()).trimmed();
        qDebug().noquote() << QString("AlgorithmExecution::execute: str is: \n%1").arg(str);
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: str is: \n%1").arg(str));
        emit logUpdated(str);
    });

    connect(process_, &QProcess::readyReadStandardOutput, [this]() {
    //connect(process_, &QProcess::readyReadStandardOutput, [this, process_]() {
        qDebug().noquote() << "AlgorithmExecution::execute: QProcess::readyReadStandardOutput emited";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::execute: QProcess::readyReadStandardOutput emited"));
        // NOTE: НА ОБРАБОТКУ ЛОГЕРУ УХОДИТ ТРИММИРОВАННАЯ СТРОЧКА (!)
        QString str = QString(process_->readAllStandardOutput()).trimmed();
        qDebug().noquote() << QString("AlgorithmExecution::execute: str is: \n%1").arg(str);
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("AlgorithmExecution::execute: str is: \n%1").arg(str));
        emit logUpdated(str);
    });
    connect(process_, &QProcess::destroyed, [this]() {
        qDebug().noquote() << QString("QProcess::destroyed: %1").arg(abnName_);
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("QProcess::destroyed: %1").arg(abnName_));
    });
    connect(process_, &QProcess::errorOccurred, this, &AlgorithmExecution::processErrorOccurred);
    connect(process_, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            [this, tempFile](int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug().noquote() << "AlgorithmExecution::processFinished: THREAD" << QThread::currentThreadId() << "finished with exit code" << exitCode << "and exit status" << static_cast<int>(exitStatus);
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), (exitCode == 0 ? Loger::LL_TRACE : Loger::LL_ERROR), QString("AlgorithmExecution::processFinished: THREAD %1 finished with exit code %2 and exit status %3")
                                                                      .arg(QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()), 0, 16))
                                                                      .arg(exitCode)
                                                                      .arg(static_cast<int>(exitStatus)));
        
        
        if (tempFile != nullptr && tempFile->exists()) {
            tempFile->remove();         // Удалим временный файл
        }        
        
        
        // NOTE: По сути временная мера для прогресс-бара пока нет сырого логирования, но в целом why not передачу кода и статуса? Полезно в теории.
        ////if (exitCode == 0) {
        //emit processReturnedResult(abnName_, exitCode, static_cast<int>(exitStatus), stopFlag_);
        ////}   // Хотел сюда добавить установку прогресс-баров на 100%. Лучше уж через algorithmExecutionFinished в лаунчере.
        
        emit algorithmExecutionFinished(abnName_, objectName(), exitCode, static_cast<int>(exitStatus), stopFlag_);
        
        
        // 1.
        //// TODO: Где-как-когда вообще удалять этот временный файл?
        ////       Более того: где его хранить? Может тогда лучше в Launcher?
        ////       А доступ для чтения файла тогда разбивать надо? Или не надо?
        
        
        //delete tempFile;            // Освободим от него память
        
        // Удалять явно не нужно, т.к. оба являются дочерними для AlgExec класса
        //tempFile->deleteLater();
        //process_->deleteLater();
        
        
        // 2.
        // QFile::remove(file); // Удаляем файл
        
        
        //emit algorithmExecutionFinished(abnName_, objectName());
        
    });
    // ===================================== КУЧА КОННЕКТОВ К ПРОЦЕССУ =====================================
    
    
    
    
    // ========================= НА СЛУЧАЙ КОГДА НУЖЕН БУДЕТ НЕ ПУТЬ К КЛЮЧУ, А САМ КЛЮЧ =========================    
    //QString sshKey;
    //if (!abnInfo_.ssh_path.isEmpty()) {
    //    QFile sshKeyFile(abnInfo_.ssh_path);
    //    if (!sshKeyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //        if (sshKeyFile.exists()) {
    //            qDebug().noquote() << "AlgorithmExecution::execute: sshKeyFile.open() failed, cannot read it.";
    //            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: sshKeyFile.open() failed, cannot read it."));
    //        } else {
    //            qDebug().noquote() << QString("AlgorithmExecution::execute: sshKeyFile doesn't exist at given directory (%1). Current path is %2").arg(sshKeyFile.fileName()).arg(QDir::currentPath());
    //            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: sshKeyFile doesn't exist at given directory (%1). Current path is %2").arg(sshKeyFile.fileName()).arg(QDir::currentPath()));
    //        }
    //    }
    //    else {
    //        sshKey = QTextStream(&sshKeyFile).readAll();
    //    }
    //}
    // ========================= НА СЛУЧАЙ КОГДА НУЖЕН БУДЕТ НЕ ПУТЬ К КЛЮЧУ, А САМ КЛЮЧ =========================
    
    
    QString destinatonUser = (abnInfo_.user.isEmpty() ? "" : abnInfo_.user + "@");
    QString destinationFlag = destinatonUser + abnInfo_.ip;
    
    QString portOption = "";
    QString portData = "";
    if (!abnInfo_.port.isEmpty()) {
        portOption = "-p";
        portData = abnInfo_.port;
    }
    
    // NOTE: Обязательно БЕЗ ПРОБЕЛА между "-i" и путём к файлу. Иначе вставляется лишний пробел к пути и 
    //       ssh не может обработать входные аргументы (какой-то код ошибки дропается, то ли 127 то ли 255)
    // NOTE: Проверить коды ошибок. Возможно, 255 - это код ошибки самого ssh, а код 127 - это уже ошибка внутренняя от bash..
    //QString sshkeyFlag = (abnInfo_.ssh_path.isEmpty()) ? "" : "-i" + abnInfo_.ssh_path;
    
    //QString sshkeyOption = (abnInfo_.ssh_path.isEmpty()) ? "" : "-i";
    //QString sshkeyData = (abnInfo_.ssh_path.isEmpty()) ? "" : "./MK3_1079_N0_sshkey.rsa";
    QString sshkeyOption = "";
    QString sshkeyPath = "";
    if (!abnInfo_.ssh_path.isEmpty()) {
        
        sshkeyPath = abnInfo_.ssh_path;
        
        if (!abnInfo_.ssh_path.startsWith(":")) {
            sshkeyOption = "-i";
            //sshkeyData = "./MK3_1079_N0_sshkey.rsa";
            //sshkeyData = abnInfo_.ssh_path;
            QFile sshkeyFile(abnInfo_.ssh_path);
            // NOTE: Важно для Linux/macOS:         // QFile::setPermissions(file, QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner));
            
            
            // TODO:
            if (!sshkeyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                if (sshkeyFile.exists()) {
                    qDebug().noquote() << "AlgorithmExecution::execute: sshkeyFile.open() failed, cannot read it.";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: sshkeyFile.open() failed, cannot read it."));
                } else {
                    qDebug().noquote() << QString("AlgorithmExecution::execute: sshkeyFile doesn't exist at given directory (%1). Current path is %2").arg(sshkeyFile.fileName()).arg(QDir::currentPath());
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: sshkeyFile doesn't exist at given directory (%1). Current path is %2").arg(sshkeyFile.fileName()).arg(QDir::currentPath()));
                }
                return;
            }
            
            
            tempFile = new QTemporaryFile(this);
            // TODO:
            if (!tempFile->open()) {
                if (tempFile->exists()) {
                    qDebug().noquote() << "AlgorithmExecution::execute: tempFileSSHKEY.open() failed, cannot read it.";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: tempFileSSHKEY.open() failed, cannot read it."));
                } else {
                    qDebug().noquote() << QString("AlgorithmExecution::execute: tempFileSSHKEY (%1) doesn't exist ... ").arg(tempFile->fileName());
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: tempFileSSHKEY (%1) doesn't exist ... ").arg(tempFile->fileName()));
                }
                return;
            }
            
            tempFile->write(sshkeyFile.readAll());
            // NOTE: Если где-то вызывается readAll(), то все данные из файла считаются.
            //       Если надо потом повторно всё считать, то используем seek(0).
            //       QString content1 = QTextStream(sshkeyFile.readAll()).readAll();        // В этой строке-примере есть два метода readAll. Тот что на QFile выдаёт QByteArray, а на QTextStream - QString.
            //                                                                              // Можно ещё писать  QString fileContent = QString::fromUtf8(rawData);
            //       sshkeyFile->seek(0);   // Возвращаемся в начало файла
            //LogerGlobal......
            
            sshkeyFile.close();
            tempFile->close();
            
            sshkeyPath = tempFile->fileName();
            // Важно для Linux/macOS
            QFile::setPermissions(sshkeyPath, QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner));
        }
    }
    


    
    QStringList list;
    list << destinationFlag;
    if (!portOption.isEmpty()) {
        list << portOption << portData;
    }
    if (!sshkeyOption.isEmpty()) {
        list << sshkeyOption << sshkeyPath;
    }
    
    // QStringList list = QStringList() << destinationFlag << portFlag << sshkeyFlag << "powershell -ExecutionPolicy Bypass -File" << QDir().absoluteFilePath(algInfo_.alg_path);
    
    // TODO: В общем если надо будет запускать на винде когда-то, то здесь нужно передавать "powershell"
    // QStringList list = QStringList() << destinationFlag << portFlag << sshkeyFlag << "powershell";
    // QStringList list = QStringList() << "-tt" << destinationFlag << portFlag << sshkeyFlag;
    // QStringList list = QStringList() << "-T" << destinationFlag << portFlag << sshkeyFlag;
    // QStringList list = QStringList() << "-T" << destinationFlag << portFlag << sshkeyFlag << "powershell";  // ещё есть флаг "-c"

    
    qDebug().noquote() << "AlgorithmExecution::execute: arguments list: " + list.join("");
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_DEBUG, "AlgorithmExecution::execute: arguments list: " + list.join(""));
    
    process_->start("ssh", list);       // process_->start("pwd");
    
    
    
    
    
    if (!process_->waitForStarted(5000)) {
        qDebug().noquote() << "AlgorithmExecution::execute: waitForStarted(5000) is not enough...";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: waitForStarted(5000) is not enough..."));
        return;
    }
    else {
        qDebug().noquote() << "AlgorithmExecution::execute: waitForStarted(5000) got it, sending script data...";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::execute: waitForStarted(5000) got it, sending script data..."));
        
        QFile file(algInfo_.alg_path);
        //QFile file(QString("%1/%2").arg(ALGS_LOCAL_PATH).arg(algName_));
        //QFile::setPermissions(file, QFile::Permissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner));
        qDebug().noquote() << QString("AlgorithmExecution::execute: algorithm file path is %1").arg(file.fileName());
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::execute: algorithm file path is %1").arg(file.fileName()));
        
        //qDebug().noquote() << QString("AlgorithmExecution::execute: does algorithms dir exists?: %1").arg(LOG_BOOL(QDir(ALGS_LOCAL_PATH).exists()));
        //LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("AlgorithmExecution::execute: does algorithms dir exists?: %1").arg(LOG_BOOL(QDir(ALGS_LOCAL_PATH).exists())));
        ////LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("AlgorithmExecution::execute: is algorithms dir exists?: %1").arg(QVariant(QDir(ALGS_LOCAL_PATH).exists()).toString()));
        
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            if (file.exists()) {
                qDebug().noquote() << "AlgorithmExecution::execute: file.open() failed, cannot read it.";
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: file.open() failed, cannot read it."));
            } else {
                qDebug().noquote() << QString("AlgorithmExecution::execute: file doesn't exist at given directory (%1). Current path is %2").arg(file.fileName()).arg(QDir::currentPath());
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: file doesn't exist at given directory (%1). Current path is %2").arg(file.fileName()).arg(QDir::currentPath()));
            }
            return;
        } else {
            QByteArray algData = file.readAll();
            qDebug().noquote() << QString("AlgorithmExecution::execute: algorithm data is \n%1").arg(QString(algData));
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::execute: algorithm data is \n%1").arg(QString(algData)));
            //qDebug().noquote() << QString("AlgorithmExecution::execute: algorithm data is \n%1").arg(algData.toStdString().c_str());
            //LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::execute: algorithm data is \n%1").arg(algData.toStdString().c_str()));
            if (-1 == process_->write(algData)) {
            // if (-1 == process_->write(algInfo_.alg_path)) {      // NO
            // if (-1 == process_->write(QString("powershell -ExecutionPolicy Bypass -File").arg(algContent))) {
              qDebug().noquote() << "AlgorithmExecution::execute: error occured while sending data to abonent.";
              LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("AlgorithmExecution::execute: error occured while sending data to abonent."));
              return;
            }
            qDebug().noquote() << "AlgorithmExecution::execute: sent script data, closing channel and executing the script...";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("AlgorithmExecution::execute: sent script data, closing channel and executing the script..."));
            
            // TODO: Убираем? Не нужно закрывать канал?
            // UPD: Оставляем. Канал закрывать надо, чтобы после записи алгоритма и его выполнения на удалёнке процесс больше не ждал входных данных.
            process_->closeWriteChannel();
            file.close();
        }
    }
    
    
    
    // Чтобы процесс дождался выполнения ssh (когда "-1" --- Неограниченное выполнение).
    // NOTE: Плохая функция (по сути вместе с waitForReadyRead)... поток перестаёт ловить ВООБЩЕ все сигналы... точнее ловит, но ставит
    //       уже в очередь, которая обрабатывается только когда заканчивается QProcess.
    // process_->waitForFinished(-1);
    
}




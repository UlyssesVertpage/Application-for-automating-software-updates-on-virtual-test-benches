
#include "Loger.h"


// ========================================================================================================================================
// Создание шаблонов и строчек
// ========================================================================================================================================
//
// 1. Для добавления новой категории внесите имя в конец списка tagsMessagesList_.
// 2. Также добавьте его в LogerLevels внутри заголовка Loger.h.
// 3. Далее внутри определения LogViewer::formats_ создайте соответствующий новый QTextCharFormat, задайте его параметры
//    и добавьте (даже если он дефолтный) в список list по тому же индексу, что и у тега из tagsMessagesList_.
//
// ========================================================================================================================================





// Список названий категорий сообщений.
// const QStringList Loger::tagsMessagesList_ {"cerror", "error", "warning", "info", "debug", "trace"};
const QStringList Loger::tagsMessagesList_ = QStringList() << "cerror" << "error" << "warning" << "info" << "debug" << "trace";



//Общий закрывающий тег.
const QString Loger::tagClose_ = "<!/#>";








// Вариант под Qt5.15
// Наибольшая длина среди открывающих тегов для применения в дальнейшей обработке сырого лога.
//const int Loger::maxOpeningTagLength_ = []() {
//    int len = 0;
//    for (auto &str : tagsMessagesList_) {
//        if (str.length() > len) { len = str.length(); }
//    }
//    return len + 4;
//}();

// Переделка под Qt5.7.1.
int Loger::initMaxOpeningTagLength() {
    int len = 0;
    for (auto &str : tagsMessagesList_) {
        if (str.length() > len) { len = str.length(); }
    }
    return len + 4;
}

const int Loger::maxOpeningTagLength_ = Loger::initMaxOpeningTagLength();







// Регекс последнего символа в строке.
const QRegularExpression Loger::lastChar_RE_(QString(".$"));







// Вариант под Qt5.15
// Список названий категорий сообщений с некоторыми спецсимволами тегов.
//const QStringList Loger::tagsNoBracketsList_ = []() {
//    QStringList list = {"!/#"};
//    for (auto &str : tagsMessagesList_) {
//        list.append("!" + str + "#");
//    }
//    return list;
//}();

// Переделка под Qt5.7.1.
QStringList Loger::initTagsNoBracketsList() {
    QStringList list = QStringList() << "!/#";
    for (auto &str : tagsMessagesList_) {
        list.append("!" + str + "#");
    }
    return list;
}

const QStringList Loger::tagsNoBracketsList_ = Loger::initTagsNoBracketsList();





    
// Вариант под Qt5.15
// Всевозможные комбинации правых частей открывающий тегов.
// const QString Loger::tagsPartsInEnd_ = []() {
//     QString parts = "";
//     for (auto &str : tagsMessagesList_) {
//         for (int i = 0; i < str.length(); ++i) {
//             parts.append(str.at(i)).append("(");
//         }
//         parts.remove(lastChar_RE_);
//         parts.append(QString(")?").repeated(str.length() - 1) + "|");
//     }
//     parts.remove(lastChar_RE_);
//     return parts;
// }();


// Переделка под Qt5.7.1.
QString Loger::initTagsPartsInEnd() {
    QString parts = "";
    for (auto &str : tagsMessagesList_) {
        for (int i = 0; i < str.length(); ++i) {
            parts.append(str.at(i)).append("(");
        }
        parts.remove(lastChar_RE_);
        parts.append(QString(")?").repeated(str.length() - 1) + "|");
    }
    parts.remove(lastChar_RE_);
    return parts;
}

const QString Loger::tagsPartsInEnd_ = Loger::initTagsPartsInEnd();







// Вариант под Qt5.15
// Всевозможные комбинации левых частей открывающий тегов.
// const QString Loger::tagsPartsInBegin_ = []() {
//     QString parts = "";
//     for (auto &str : tagsMessagesList_) {
//         parts.append(QString("(").repeated(str.length() - 1) + str.at(0));
//         for (int i = 1; i < str.length(); ++i) {
//             parts.append(")?").append(str.at(i));
//         }
//         parts.append("|");
//     }
//     parts.remove(lastChar_RE_);    
//     return parts;
// }();


// Переделка под Qt5.7.1.
QString Loger::initTagsPartsInBegin() {
    QString parts = "";
    for (auto &str : tagsMessagesList_) {
        parts.append(QString("(").repeated(str.length() - 1) + str.at(0));
        for (int i = 1; i < str.length(); ++i) {
            parts.append(")?").append(str.at(i));
        }
        parts.append("|");
    }
    parts.remove(lastChar_RE_);    
    return parts;
}

const QString Loger::tagsPartsInBegin_ = Loger::initTagsPartsInBegin();












// Объединённые в одну строчку через "|" названия категорий логирования.
const QString Loger::tagsMessagesJoined_ = tagsMessagesList_.join("|");

// Опции для регексирования
const QRegularExpression::PatternOptions Loger::options_ = QRegularExpression::CaseInsensitiveOption;

// Регекс открытого тега.
const QRegularExpression Loger::tagOpen_RE_               (QString("<!(%1)#>").arg(tagsMessagesJoined_), options_);

// Регекс правой части открытого тега в начале строки.
const QRegularExpression Loger::tagOpenPartInBegin_RE_    (QString("^(((!)?(%1))?#)?>").arg(tagsPartsInBegin_), options_);

// Регекс левой части открытого тега в конце строки.
const QRegularExpression Loger::tagOpenPartInEnd_RE_      (QString("<(!((%1)(#)?)?)?$").arg(tagsPartsInEnd_), options_);

// Регекс закрытого тега.
const QRegularExpression Loger::tagClose_RE_              (tagClose_, options_);

// Регекс правой части закрытого тега в начале строки.
const QRegularExpression Loger::tagClosePartInBegin_RE_   ("^(((!)?/)?#)?>", options_);

// Регекс левой части закрытого тега в конце строки.
const QRegularExpression Loger::tagClosePartInEnd_RE_     ("(<(!(/(#)?)?)?)$", options_);







/**
 * \brief Конструктор класса
 * логирования.
 * \param[in] parseLevel
 * допустимый в экземпляре
 * уровень логирования.
 * \param[in] parent
 * указатель на родителя.
 * \return Конструктор 
 * не возвращает ничего.
 *
 * \n
 */
Loger::Loger(QObject *parent, LogerLevels parseLevel)
    : QObject{parent}
    , rawBuff_{""}
    , tagBuff_{""}
    , curLogerLevel_{parseLevel}
    , curMsgLogerLevel_{Loger::LL_TRACE}

{
    timer_ = new QTimer(this);
    
    for (int i = 0; i < LogerLevels::LL_ENUM_SIZE; ++i) {
        levelsMsgsCountList_.append(0);
    }
    
    logList_ = new QList<LogLine>;
    //logList_->append(LogLine(totalNumberOfLogMessages_, "", Loger::LL_TRACE));
    addProcessedRawMessageToLog();
    
    connect(this, &Loger::newLineInserted, this, &Loger::checkLogListSize);
    
}




/**
 * \brief Метод ....
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void Loger::abonentLogUpdated(const QString& msg) {
    //addMessageToLog(LogerLevels::LL_INFO, msg);
    QString logstr = QString("Loger::abonentLogUpdated: got msg: %1").arg(msg);
    qDebug().noquote() << logstr;
    LOG_MSG(objectName(), LogerLevels::LL_INFO, logstr);
    handleRawLog(msg);
}





/**
 * \brief Деструктор класса логирования.
 * \return Деструктор не возвращает ничего.
 *
 * \n
 */
Loger::~Loger() {
    qDebug().noquote() << "Loger::~Loger";
    
    // NOTE: Бессмысленно, будет падать при закрытии.
    //LogerGlobal::instance().addGlobalMessageToLog(Loger::LL_TRACE, QString("Loger::~Loger"));
    
    if (logList_ != nullptr) {
        delete logList_;
    }
    if (timer_ != nullptr) {
        // TODO: Проверку и остановку таки делать или можно всё же сразу удалять?
        if (timer_->isActive()) {
            timer_->stop();
        }
        delete timer_;
    }
}



/**
 * \brief Метод сброса текущих значений переменных, работающих с сырым логом.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void Loger::resetCountersValues() {
    wasTagOpened_ = false;
    curMsgLen_ = 0;
    curMsgLogerLevel_ = Loger::LL_TRACE;
    //errorMsgIncorrectClosing_ = false;
    //endedWithNewLine_ = false;
    rawBuff_ = "";      // Не rawBuff_.clear(). Пусть она будет обыкновенно пустая, а не null
    // Очищать здесь наш tagBuff_ не будем, т.к. он нужен для последующих считываний. Сброс его производится где-то ещё вроде resetLoger, либо где-то ещё вроде finishLogMessage...
}




/**
 * \brief Метод сброса текущих значений переменных, работающих с сырым логом.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void Loger::resetLoger() {
    resetCountersValues();
    tagBuff_ = "";
    msgErrorEnding_Trace_ = false;
    totalNumberOfLogMessages_ = 0;
    //levelsMsgsCountList_.clear();
    for (int i = 0; i < LogerLevels::LL_ENUM_SIZE; ++i) {
        levelsMsgsCountList_[i] = 0;
    }
    logList_->clear();
    timer_->start(TIMER_INTERVAL);      // Макрос лежит в хэдере, по умолчанию 100 ms.
}







//void Loger::setDefaultLogerParseLevel(LogerLevels level){
//    defaultParseLevel = level;
//}




///**
// * \brief Метод добавления сырого лога в виде стандартного строкового потока.
// * \return Метод не возвращает ничего.
// *
// * \n
// */
//void Loger::addStringStreamLog(const std::stringstream &stream) {
//    // TODO: 
//    // 1. Для UTF-8
//    // QString str = QString::fromStdString(stream.str()); addString(str);
//    // 2. Для ANSI/локальной кодировки
//    // QString str = QString::fromLocal8Bit(stream.str().c_str());
//    // 3. И т.д. и прочие реализации для кодировок
//    // Возможно, что предварительно потребуется перекодировка с помощью QStringDecoder.
    
//    addRowLog(QString::fromStdString(stream.str()));
//}






///**
// * \brief Метод закрытия текущего открытого сообщения.
// * \return Метод не возвращает ничего.
// *
// * \n
// */
//void Loger::finishLogMessage() {
//    if (wasTagOpened_) {
//        logList_->last().setMsgErrorFlag(true);
//        emit lastLineUpdated();
//        wasTagOpened_ = false;
//    }
//}







/**
 * \brief Слот для проверки допустимого размера списка строк лога.
 * \return Слот не возвращает ничего.
 *
 * \n
 */
void Loger::checkLogListSize() {
    if (logList_->size() > maxLogListSize_) {
        logList_->removeAt(0);
    }
}



/**
 * \brief Метод добавления сообщения определённого уровня.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void Loger::addMessageToLog(Loger::LogerLevels level, const QString &msg) {
    
    // Проверка на уровень парсинга. Если больше текущего, то сообщение не выводим.
    if (level > curLogerLevel_) {
        return;
    }
    
    logList_->append(LogLine(totalNumberOfLogMessages_, msg, level));

    ++totalNumberOfLogMessages_;
    ++levelsMsgsCountList_[static_cast<int>(level)];
    
    emit newLineInserted();
}





// TODO: Избавиться

///**
// * \brief Метод обновления информации о количестве и номерах сообщений.
// * \return Метод не возвращает ничего.
// *
// * \n
// * Метод увеличения общего числа сообщений на единицу, если сообщение пришло новое,
// * а также подсчёта сообщений по каждой категории.
// */
//void Loger::updateMsgsNumInfo(LogerLevels level) {
//    ++totalNumberOfLogMessages_;
//    ++levelsMsgsCountList_[static_cast<int>(level)];
//}
 


/**
 * \brief Метод передачи информации о текущем логе.
 * param[in/out] logerinfo структура для передачи информации о логе.
 * \return Метод не возвращает ничего.
 *
 * \n
 * Метод передаёт в структуру logerInfo общее кол-во сообщений 
 * в логе и список количеств по каждой категории).
 */
void Loger::getInfo(LogerInfo &logerInfo) {
    logerInfo.totalNumberOfLogMessages_ = totalNumberOfLogMessages_;
    logerInfo.levelsMsgsCountList_ = levelsMsgsCountList_;
}    
    
    

/*
 *
 * #include <qapplication.h>
  #include <stdio.h>
  #include <stdlib.h>

  void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
  {
      QByteArray localMsg = msg.toLocal8Bit();
      switch (type) {
      case QtDebugMsg:
          fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
          break;
      case QtInfoMsg:
          fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
          break;
      case QtWarningMsg:
          fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
          break;
      case QtCriticalMsg:
          fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
          break;
      case QtFatalMsg:
          fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
          abort();
      }
  }

  int main(int argc, char **argv)
  {
      qInstallMessageHandler(myMessageOutput);
      QApplication app(argc, argv);
      ...
      return app.exec();
  }

  */










/**
 * \brief Метод закрытия текущего открытого сообщения.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void Loger::finishLogMessage() {
//    if (wasTagOpened_) {
//        logList_->last().setMsgErrorFlag(true);
//        emit lastLineUpdated();
//        wasTagOpened_ = false;
//    }
    
//    qDebug() << rawBuff_;
    
    QString charsLeft = "";
    
    for (int i = 0; i < tagBuff_.length(); ++i) {
        if (curMsgLen_ + 1 <= maxLogMsgLength_) {
            rawBuff_.append(tagBuff_.at(i));
            ++curMsgLen_;
        }
        else {
            charsLeft.append(tagBuff_.at(i));
        }
    }
    
    if (!rawBuff_.isEmpty()) {
        
        if (wasTagOpened_) {
            addProcessedRawMessageToLog(true, true);
        }
        else {
            addProcessedRawMessageToLog(!charsLeft.isEmpty());
        }
        
        
        if (!charsLeft.isEmpty()) {
            addProcessedRawMessageToLog();
        }
        
    }
    
    resetCountersValues();
    tagBuff_ = "";
    msgErrorEnding_Trace_ = false;
}













/**
 * \brief Метод добавления строчки сообщения, по умолчанию обработанной сырой.
 * param[in/out] ...
 * \return Метод не возвращает ничего.
 *
 * \n
 * 
 */
//void Loger::addProcessedRawMessageToLog(bool errorFlag, LogerLevels level, const QString& str) {
void Loger::addProcessedRawMessageToLog(bool errorFlag, bool isTagMsgContinuing) {
    if (curMsgLogerLevel_ > curLogerLevel_) {
        return;
    }
    
    logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_, errorFlag));

    if (!isTagMsgContinuing) {
        ++totalNumberOfLogMessages_;
        ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)];
    }
    
    emit newLineInserted();
}




















/**
 * \brief Метод...
 * param[in/out] ...
 * \return Метод не возвращает ничего.
 *
 * \n
 *
 */
void Loger::handleRawLog(const QString logstr) {

    // Размер всей строчки лога...
    // TODO: Нужно ли и вправду считать размер отдельно? Перевызывает ли метод и пересчитывает ли цикл размер строки в шапке повторно?
    int strSize = logstr.size();


    // Посимвольная прогонка строчки лога...
    for (int i = 0; i < strSize; ++i) {
    //for (int i = 0; i < logstr.size(); ++i) {



        // 1. Проверка на совпадение тега / совпадение куска тега / не совпадение тега
        // 2. Проверка символа на '\n'
        // 3. ...






        // ================== ВЫВОД ПОЛЕЙ ==================

        //// for (int i = 0; i < 4; ++i) { qDebug() << ""; }
        ////// qDebug() << "    ";
        //// qDebug() << QString("================== ВЫВОД ПОЛЕЙ ==================");
        //// qDebug() << QString("i: %1").arg(i);
        //// qDebug() << QString("logstr.at(i): %1").arg(logstr.at(i));
        //// qDebug() << QString("rawBuff_: %1").arg(rawBuff_);
        //// qDebug() << QString("tagBuff_: %1").arg(tagBuff_);
        //// qDebug() << QString("wasTagOpened_: %1").arg(wasTagOpened_);
        //// qDebug() << QString("curMsgLogerLevel_: %1").arg(LogerLevelsStringsMap.value(curMsgLogerLevel_));
        //// qDebug() << QString("curMsgLen_: %1").arg(curMsgLen_);
        //// qDebug() << QString("msgErrorEnding_Trace_: %1").arg(msgErrorEnding_Trace_);
        ////// qDebug() << QString("msgErrorEnding_Tagged_: %1").arg(msgErrorEnding_Tagged_);
        ////// qDebug() << QString(": %1").arg();
        ////// qDebug() << QString("================== ВЫВОД ПОЛЕЙ ==================");

        // ================== ВЫВОД ПОЛЕЙ ==================









        // ============================================== 0 ==============================================
        // ПРОВЕРКИ ФЛАГОВ НЕКОРРЕКТНОГО ЗАВЕРШЕНИЯ СООБЩЕНИЙ

        /*
        if (msgErrorEnding_Trace_) {

            continue;
        }
        */

        /*
        if (msgErrorEnding_Tagged_ || msgErrorEnding_Trace_) {
            if (msgErrorEnding_Tagged_) {

                continue;
            }
            if (msgErrorEnding_Trace_) {

                continue;
            }
        }
        */

        // ============================================== 0 ==============================================











        // ============================================== 1 ==============================================
        // ИЩЕМ СОВПАДЕНИЯ КУСКОВ ТЕГОВ И ПОЛНЫЕ СОВПАДЕНИЯ ТЕГОВ



        bool foundOpenTag = false, foundCloseTag = false, tagBreak = false;
        QString newTagBuff = "";

        //const QRegularExpression& curTagPart_RE = (wasTagOpened_ ? Loger::tagClosePartInEnd_RE_ : Loger::tagOpenPartInEnd_RE_);
        //const QRegularExpression& curTag_RE = (wasTagOpened_ ? Loger::tagClose_RE_ : Loger::tagOpen_RE_);
        QRegularExpressionMatch partOpenMatch;
        QRegularExpressionMatch openMatch;
        QRegularExpressionMatch partCloseMatch;
        QRegularExpressionMatch closeMatch;


        if ((tagBuff_.isEmpty() && (Loger::tagOpenPartInEnd_RE_.match(logstr.at(i)).hasMatch() || Loger::tagClosePartInEnd_RE_.match(logstr.at(i)).hasMatch())) ||
                (Loger::tagOpenPartInEnd_RE_.match(tagBuff_).hasMatch() || Loger::tagClosePartInEnd_RE_.match(tagBuff_).hasMatch())) {
            //// qDebug() << "======================= 1 =======================";
        }



        if (tagBuff_.isEmpty() && (Loger::tagOpenPartInEnd_RE_.match(logstr.at(i)).hasMatch() || Loger::tagClosePartInEnd_RE_.match(logstr.at(i)).hasMatch())) {
            //// qDebug() << "Нашёлся первый символ тега.";
            tagBuff_ = logstr.at(i);
            continue;
        }

        // Проверяем буффер начала тега на наличие символов
        else if (Loger::tagOpenPartInEnd_RE_.match(tagBuff_).hasMatch() || Loger::tagClosePartInEnd_RE_.match(tagBuff_).hasMatch()) {
            //// qDebug() << "У нас уже был ранее найден кусок тега.";

            //QRegularExpressionMatch partMatch = curTagPart_RE.match(tagBuff_ + logstr.at(i));
            //QRegularExpressionMatch match =     curTag_RE.match(tagBuff_ + logstr.at(i));

            partOpenMatch   = Loger::tagOpenPartInEnd_RE_.match(tagBuff_ + logstr.at(i));
            openMatch       = Loger::tagOpen_RE_.match(tagBuff_ + logstr.at(i));
            partCloseMatch  = Loger::tagClosePartInEnd_RE_.match(tagBuff_ + logstr.at(i));
            closeMatch      = Loger::tagClose_RE_.match(tagBuff_ + logstr.at(i));

            // Проверяем связку "буффер начала тега + текущий символ" на соответствие началу тега
            if (partOpenMatch.hasMatch() || partCloseMatch.hasMatch()) {
                //// qDebug() << "    Нашли очередной символ для тега.";
                tagBuff_.append(logstr.at(i));
                continue;
            }

            // Связка найдена!
            else if (openMatch.hasMatch()) {
                //// qDebug() << "    Нашли связку (открытый тег)!";
                //tagBuff_ = "";
                foundOpenTag = true;
                /*
                int tagBuffLen = tagBuff_.length() + 1;
                resetCountersValues();
                wasTagOpened_ = true;
                rawBuff_.remove(rawBuff_.length() - tagBuffLen, tagBuffLen);
                tagBuff_ = "";
                curMsgLogerLevel_ = static_cast<Loger::LogerLevels>(tagsMessagesList_.indexOf(match.captured(1)));       // Взятие индекса названия самой категории из списка. (<!info#> --> info --> 3)
                */
            }
            else if (closeMatch.hasMatch()) {
                //// qDebug() << "    Нашли связку (закрытый тег)!";
                //tagBuff_ = "";
                foundCloseTag = true;
            }

            // Связка поломалась/ложная, переопределяем буфер тега:
            // если текущей символ подходит - записываем его, если нет - записываем пустоту
            else {
                tagBreak = true;
                //// qDebug() << "    Тег сломался.";
                if (Loger::tagClosePartInEnd_RE_.match(logstr.at(i)).hasMatch() || Loger::tagOpenPartInEnd_RE_.match(logstr.at(i)).hasMatch()) {
                    //// qDebug() << "        ...Но новый символ оказался началом нового тега.";
                    newTagBuff = logstr.at(i);
                }
            }

        }

        // ============================================== 1 ==============================================




        bool isNewLineSymbol = logstr.at(i) == '\n';
        bool wasMsgErrorEnding_Trace = msgErrorEnding_Trace_;


        // ============================================== 0 ==============================================
        // ПРОВЕРКИ ФЛАГА НЕКОРРЕКТНОГО ЗАВЕРШЕНИЯ ТРАССИРОВОЧНЫХ СООБЩЕНИЙ


        if (msgErrorEnding_Trace_) {
            //// qDebug() << "======================= 0 =======================";
            //// qDebug() << "Ранее был флаг переполнения трассировочного сообщения";
            if (!foundOpenTag && !isNewLineSymbol) {
                //// qDebug() << "    До сих пор не нашли '\\n' или открытого тега, делаем continue";
                if (tagBreak) {
                    //// qDebug() << "        Но т.к. был tagBreak, то перед continue чистим tagBuff_ от лишнего, никуда не сбрасываемого куска тега.";
                    tagBuff_ = "";
                }
                continue;
            }
            else {
                //// if (foundOpenTag)    { qDebug() << "    Встретили таки открытый тег, снимаем msgErrorEnding_Trace_"; }
                //// if (isNewLineSymbol) { qDebug() << "    Встретили таки '\\n', снимаем msgErrorEnding_Trace_"; }
                msgErrorEnding_Trace_ = false;
            }
        }
        //else {
        //}

        // ============================================== 0 ==============================================







        // ============================================== 2 ==============================================
        // ЕСЛИ БЫЛ КУСОК ТЕГА И ОН СЛОМАЛСЯ, ТО ЗАПИСЫВАЕМ ЭТОТ КУСОК К СЫРОЙ СТРОКЕ И ЗАДАЁМ НОВОЕ
        // ЗНАЧЕНИЕ ДЛЯ БУФЕРА ТЕГА



        QString charsLeft = "";

        if (tagBreak) {
            //// qDebug() << "======================= 2 =======================";
            //// qDebug() << "Ранее был сломан тег, добавляем символы из tagBuff_ в rawBuff_ и charsLeft...";
            for (int j = 0; j < tagBuff_.length(); ++j) {
                //(curMsgLen_ + 1 <= maxLogMsgLength_ ? rawBuff_ : charsLeft) += tagBuff_.at(j);
                ///*
                if (curMsgLen_ + 1 <= maxLogMsgLength_) {
                    rawBuff_ += tagBuff_.at(j);
                    ++curMsgLen_;
                }
                else {
                    charsLeft += tagBuff_.at(j);
                }
                //*/
            }


            //// if (charsLeft.isEmpty()) { qDebug() << "    Все символы поместились, charsLeft остаётся пустым"; }
            //// { qDebug() << "    Пришлось затолкать часть символов в charsLeft, не все влезли из tagBuff_"; }


//            // Нужно, чтобы 3 и 4 блоки отработали
//            if (curMsgLen_ == maxLogMsgLength_) {
//                --curMsgLen_;
//            }

//            if (!charsLeft.isEmpty() && newTagBuff.isEmpty()) {
//
//            }

            tagBuff_ = newTagBuff;          // if (!newTagBuff.isEmpty()) {}
        }

        // ============================================== 2 ==============================================




        // ============================================== 3 ==============================================
        // ОБРАБОТКА ТЕКУЩЕГО СИМВОЛА, ЕСЛИ ЭТО СИМВОЛ НОВОЙ СТРОКИ





        if (isNewLineSymbol) {

            //// qDebug() << "======================= 3 =======================";
            //// qDebug() << "Текущий символ - '\\n', обрабатываем.";

            bool isTagMsgLenExceeded = wasTagOpened_ && curMsgLen_ == maxLogMsgLength_;

            addProcessedRawMessageToLog(isTagMsgLenExceeded, wasTagOpened_ && curMsgLen_ < maxLogMsgLength_);
            // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_, isTagMsgLenExceeded)); // ++totalNumberOfLogMessages_; // ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)]; // emit newLineInserted();
            if (!wasTagOpened_ || isTagMsgLenExceeded) {
                resetCountersValues();
                //// if (!wasTagOpened_) { qDebug() << "    Тег не был открыт, поэтому просто делаем сброс"; }
                //// else { qDebug() << "    Тег был открыт, однако длина сообщения уже и так равна макс-ой! Никаких +1 переносов!"; }
            }
            else {
                ++curMsgLen_;
                rawBuff_ = "";
                //// qDebug() << "    Тег открыт, длина в порядке, просто вставляется переносик. +1 к curMsgLen_";
            }


            // Ниже     //rawBuff_ += charsLeft;
        }

        //else { //// qDebug() << "Текущий символ НЕ является переносом."; }

        // ============================================== 3 ==============================================






        // ============================================== 4 ==============================================
        // ОБРАБОТКА ТЕКУЩЕГО СИМВОЛА (НЕ СИМВОЛ НОВОЙ СТРОКИ)




        if (!isNewLineSymbol) {

            //// qDebug() << "======================= 4 =======================";
            //// qDebug() << "Обрабатываем текущий символ (не явл-ся переносом)";



            bool isCurMsgTRACE = curMsgLogerLevel_ == LogerLevels::LL_TRACE;



            if (foundCloseTag) {
                if (wasTagOpened_) {
                    //// qDebug() << "    ЗАКРЫТЫЙ: Корректно, нашли закрытый тег после открытого";
                    // Закрытый тег, сбрасываем
                    addProcessedRawMessageToLog();
                    // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_)); // ++totalNumberOfLogMessages_; // ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)]; // emit newLineInserted();
                    resetCountersValues();
                }
                else {
                    //// qDebug() << "    ЗАКРЫТЫЙ: Нашли закрытый тег без открытого, но это не проблема. Пробуем сбросить tagBuff_ в rawBuff_...";
                    // Закрытый без открытого
                    tagBuff_.append(logstr.at(i));      // Текущий символ не обрабатывался без этой строки... То есть '>' из "<!/#>" не добавлялся в rawBuff_/charsLeft  :)
                    //tagBuff_.append('\n');              // NOTE: !! Для того чтобы после ничейного закртытого ("<!/#>") тега ставился перенос и последующее трасс-е сооб-е шло отдельно от потерянного куска тегованного сооб-я. !!
                    for (int j = 0; j < tagBuff_.length(); ++j) {
                        //(curMsgLen_ + 1 <= maxLogMsgLength_ ? rawBuff_ : charsLeft) += tagBuff_.at(j);
                        if (curMsgLen_ + 1 <= maxLogMsgLength_) {
                            rawBuff_ += tagBuff_.at(j);
                            ++curMsgLen_;
                        }
                        else {
                            charsLeft += tagBuff_.at(j);
                        }
                    }



                    bool check = !charsLeft.isEmpty();

                    addProcessedRawMessageToLog(check);
                    resetCountersValues();

                    // NOTE: Код, чтобы сбросить кусок тега из tagBuff_ (!), когда длина превысилась..
                    ///*
                    if (check) {
                        rawBuff_ += charsLeft;
                        addProcessedRawMessageToLog();
                        rawBuff_ = "";
                        charsLeft = "";
                    }
                    //*/

                    // Работает, но сам код некрасивый
                    /*
                    if (!charsLeft.isEmpty()) {
                        addProcessedRawMessageToLog(true);
                        resetCountersValues();
                        rawBuff_ += charsLeft;
                        addProcessedRawMessageToLog();
                        rawBuff_ = "";
                        charsLeft = "";

                    } else {
                        addProcessedRawMessageToLog();
                        resetCountersValues();
                    }
                    */

                    // Не работает как надо
                    /*if (!charsLeft.isEmpty()) {
                        addProcessedRawMessageToLog(true);
                        // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_, true));// ++totalNumberOfLogMessages_;// ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)];// emit newLineInserted();
                        resetCountersValues();
                        //// qDebug() << "        Не все влезли, пришлось класть в charsLeft.";
                    }
                    //// else { qDebug() << "        Все поместились вовнутрь rawBuff_."; }

                    curMsgLen_ = 0;

                    if (!charsLeft.isEmpty()) {
                        rawBuff_ += charsLeft;
                        charsLeft = "";
                        addProcessedRawMessageToLog(true);

                    }
                    */

                }
                tagBuff_ = "";
            }


            else if (foundOpenTag) {
                if (!wasTagOpened_) {
                    //// qDebug() << "    ОТКРЫТЫЙ: Корректно, нашли новый открытый тег.";
                    // Открытый тег, сбрасываем
                    // NOTE: если до этого было НЕ трасс-е сообщение и у нас пуста сырая строка, то её не надо добавлять в лог.
                    // TODO: где ещё добавить такую проверку?
                    // NOTE: если длина списка ещё 0, выдаст ошибку.
                    if ( ! (rawBuff_.isEmpty() && (logList_->last().getLogerLevel() != LogerLevels::LL_TRACE || wasMsgErrorEnding_Trace)) ) {        // TODO: ещё протестить, когда текущее пустое и пред-е было трасс-е...
                        //// qDebug() << "        Выводим текущий буфер на экран, так как он (rawBuff_) не был пуст ИЛИ последнее сообщение было трассировочное";
                        addProcessedRawMessageToLog();
                        // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_));// ++totalNumberOfLogMessages_;// ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)];// emit newLineInserted();
                    }
                    resetCountersValues();
                    wasTagOpened_ = true;
                    curMsgLogerLevel_ = static_cast<Loger::LogerLevels>(tagsMessagesList_.indexOf(openMatch.captured(1)));
                }
                else {
                    //// qDebug() << "    ОТКРЫТЫЙ: Плохо, нашли открытый тег, когда был открыт предыдущий.";
                    // Повторно открытый тег: сброс и новый подсчёт
                    addProcessedRawMessageToLog(true);
                    // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_, true));// ++totalNumberOfLogMessages_;// ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)];// emit newLineInserted();
                    resetCountersValues();
                    wasTagOpened_ = true;
                    curMsgLogerLevel_ = static_cast<Loger::LogerLevels>(tagsMessagesList_.indexOf(openMatch.captured(1)));
                }
                tagBuff_ = "";
            }







            // Тегов не было, просто символ
            else {

                //// qDebug() << "    НЕТ_ТЕГОВ: обрабатываемым символ как есть, тегов не нашлось.";

                // Перебрасывали из буфера тега в сырую строку...
                if (tagBreak) {                                                                     // (!newTagBuff.isEmpty()) не обязательно true в такой ситуации
                    // ** Наш текущий символ не является началом нового тега **
                    if (newTagBuff.isEmpty()) {
                        // ...и добавим текущий символ тоже к сырой строке
                        if (curMsgLen_ < maxLogMsgLength_) {
                            //// qDebug() << "        Был tagBreak, newTagBuff пуст, а curMsgLen ещё пока меньше макс-й. Добавляем символ к rawBuff_!";
                            rawBuff_.append(logstr.at(i));
                            ++curMsgLen_;
                        }
                        // ...и упёрлись в предел, добавим текущий символ к оставшимся символам
                        else if (curMsgLen_ == maxLogMsgLength_) {

                            // Трасс-е не продолжаем выводить, а тегованное - да.
                            if (isCurMsgTRACE) {
                                // TODO: qDebug()...
                                //// qDebug() << "        Был tagBreak, newTagBuff пуст, но curMsgLen уже равна макс-й... Сброс ошиб-го сообщения, ждём открытый тег ИЛИ '\\n' для продолжения занесения в лог текста";
                                addProcessedRawMessageToLog(true);
                                resetCountersValues();
                                msgErrorEnding_Trace_ = true;
                            }
                            else {
                                // TODO: qDebug()...
                                //// qDebug() << "        Был tagBreak, newTagBuff пуст, но curMsgLen уже равна макс-й... Сброс ошиб-го сообщения, текущий символ идёт в charsLeft.";
                                charsLeft.append(logstr.at(i));
                                addProcessedRawMessageToLog(true);
                                // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_, true));// ++totalNumberOfLogMessages_;// ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)];// emit newLineInserted();
                                resetCountersValues();
                            }

                            /*
                            // Сбрасываем по трейсу всё что есть в лог и ждём
                            //// qDebug() << "        Был tagBreak, newTagBuff пуст, но curMsgLen уже равна макс-й... Сброс ошиб-го сообщения, ждём открытый тег ИЛИ '\\n' для продолжения занесения в лог текста";
                            addProcessedRawMessageToLog(true);
                            resetCountersValues();
                            msgErrorEnding_Trace_ = true;

                            // Было сохранение всего трассировочного.

                            //// qDebug() << "        Был tagBreak, newTagBuff пуст, но curMsgLen уже равна макс-й... Сброс ошиб-го сообщения, текущий символ идёт в charsLeft.";
                            charsLeft.append(logstr.at(i));
                            addProcessedRawMessageToLog(true);
                            // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_, true));// ++totalNumberOfLogMessages_;// ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)];// emit newLineInserted();
                            resetCountersValues();
                            */


                        }
                    }
                    //else if ()
                }
                //if (charsLeft.length() > 0) {
                //}



                // Встретили просто обычный символ, не находили никаких тегов.

                // TODO: коммент переделать
                // Если трейс превышен, сообщение обрывается и ожидаем открытый тег ИЛИ '\\n' для продолжения занесения в лог текста
                else {
                    bool curMsgLenExceeded = curMsgLen_ + 1 > maxLogMsgLength_;
                    if (curMsgLenExceeded) {
                        //// qDebug() << "        НЕтипичная ситуация: не закинем наш текущий символ в rawBuff_, т.к. уже достигнута макс-я curMsgLen_";
                        addProcessedRawMessageToLog(true);
                        // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_, true));// ++totalNumberOfLogMessages_;// ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)];// emit newLineInserted();
                        resetCountersValues();
                        if (isCurMsgTRACE) {
                            //// qDebug() << "            Ещё и сообщение трасс-е, придётся ждать '\\n' ИЛИ открытый тег...";
                            msgErrorEnding_Trace_ = true;
                        }
                    }
                    if (!(isCurMsgTRACE && curMsgLenExceeded)) {
                        //// qDebug() << "        Типичная ситуация: закинем наш текущий символ в rawBuff_!";
                        ++curMsgLen_;
                        rawBuff_.append(logstr.at(i));
                    }
                }

                // Ещё пока попадает всё, даже если трейс превышен
                /*
                else {
                    ++curMsgLen_;
                    if (curMsgLen_ > maxLogMsgLength_) {
                        //// qDebug() << "        НЕтипичная ситуация: не закинем наш текущий символ в rawBuff_, т.к. с ним превысится макс-я curMsgLen_, он пойдёт в следующее сообщение";
                        addProcessedRawMessageToLog(true);
                        // logList_->append(LogLine(totalNumberOfLogMessages_, rawBuff_, curMsgLogerLevel_, true));// ++totalNumberOfLogMessages_;// ++levelsMsgsCountList_[static_cast<int>(curMsgLogerLevel_)];// emit newLineInserted();
                        resetCountersValues();
                        ++curMsgLen_;
                    }
                    //// else { qDebug() << "        Типичная ситуация: закинем наш текущий символ в rawBuff_!"; }
                    rawBuff_.append(logstr.at(i));
                }
                */



            }

        }

        // ============================================== 4 ==============================================





        // ============================================== 5 ==============================================
        // ОБРАБОТКА ОСТАВШИХСЯ СИМВОЛОВ, ЕСЛИ ОНИ ЕСТЬ


        if (!charsLeft.isEmpty()) {
            //// qDebug() << "======================= 5 =======================";
            //// qDebug() << "charsLeft оказался не пуст, поэтому что-то да добавляем в rawBuff_.";
        }
        rawBuff_ += charsLeft;
        curMsgLen_ += charsLeft.length();

        // ============================================== 5 ==============================================










        //// ============================================== 6 ==============================================
        //
        //// ПРОСТО ПРИНТ ВСЕХ ТЕКУЩИХ СТРОК ЛОГОВ ДЛЯ ДЕБАГА.
        //
        ////// qDebug() << "";
        ////for (const LogLine& line : logList_) {
        //int newSize = logList_->size();
        //for (int j = 0; j < newSize; ++j) {
        //    const LogLine& line = logList_->at(j);
        //    //// qDebug() << line.getMsgNum() << "--" << line.getLine();
        //}
        //// ============================================== 6 ==============================================


    }

}






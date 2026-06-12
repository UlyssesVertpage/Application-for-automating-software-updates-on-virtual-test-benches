#ifndef LOGER_H
#define LOGER_H

#include <QDebug>
#include <QStyle>
#include <QTimer>

#include <QWidget>
#include <QSet>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QTextCharFormat>


#include <sstream>

#include "Globals.h"



// TODO: (NEW)
// 1. А надо ли хранить logList_ как указатель, а не просто список?

// +++ 2.    По новым сырым логам: вынести операции [добавления строки в список + увел-я кол-ва сооб-й + emit сигнала]
//           в отдельный метод Loger, куда будут передаваться допом необходимые флаги и т.д.
//     2.1.  Сделать перегрузку? todo внёс к объявлению метода addProcessedRawMessageToLog.

// 3. Прописывать одинаковые номера для LogLine'ов, относящихся к одному и тому же сообщению:
//    В нужных местах вовнутрь addProcessedRawMessageToLog передавать флажок, сообщающий,
//    что не нужно увеличивать totalNumberOfLogMessages_.

// 4. 




// TODO:
// 1. Doxygen-описания полей и методов..
// 2. Оставить памятки по использованию класса и его переменных.


// TODO: убрать, т.к. перешли на передачу длины при инициализации.
// Макрос для определения максимальной длины одного сообщения в кратком логе.
//#define MAX_LOG_TAG_MESSAGE_SIZE 20

/// Макрос определения макс-го кол-ва строк в логе.






/// Макрос добавления имени объекта в множество имён допустимых для логирования объектов.
#define LOG_REG_OBJNAME(objName) LogerGlobal::instance().addObjectNameToAllSet(objName)

///
#define LOG_ADD_OBJNAME(objName) LogerGlobal::instance().addObjectNameToAcceptableSet(objName)

///
//#define LOG_REG_OBJNAME("MainWindow_inst");  ""

///
#define LOG_MSG(objName, level, msg) LogerGlobal::instance().addMessageToGlobalLog(objName, level, msg)

///
#define TIMER_INTERVAL 100













/// Макрос вывода сообщения в лог.
#define LOG(loger, level, logText, ...) do { \
        if(level <= loger->getCurLogerLevel()){ \
            loger->addMessageToLog(level, QString(logText)__VA_ARGS__); \
        } \
    }while(0)

/// Макрос вывода сообщения о критической ошибке в локальный лог.
#define LLOG_C(loger, logText, ...) LOG(loger, Loger::LL_CERROR, logText, __VA_ARGS__)

/// Макрос вывода сообщения о критической ошибке в глобальный лог.
#define LOG_C(logText, ...) LLOG_C(LogerGlobal::instance(), logText, __VA_ARGS__)


/// Макрос вывода сообщения о ошибке в локальный лог.
#define LLOG_E(loger, logText, ...) LOG(loger, Loger::LL_ERROR, logText, __VA_ARGS__)

/// Макрос вывода сообщения о ошибке в глобальный лог.
#define LOG_E(logText, ...) LLOG_E(LogerGlobal::instance(), logText, __VA_ARGS__)


/// Макрос вывода сообщения с предупреждением в локальный лог.
#define LLOG_W(loger, logText, ...) LOG(loger, Loger::LL_WARNING, logText, __VA_ARGS__)

/// Макрос вывода сообщения с предупреждением в глобальный лог.
#define LOG_W(logText, ...) LLOG_W(LogerGlobal::instance(), logText, __VA_ARGS__)


/// Макрос вывода сообщения с информацией в локальный лог.
#define LLOG_I(loger, logText, ...) LOG(loger, Loger::LL_INFO, logText, __VA_ARGS__)

/// Макрос вывода сообщения с информацией в глобальный лог.
#define LOG_I(logText, ...) LLOG_I(LogerGlobal::instance(), logText, __VA_ARGS__)


/// Макрос вывода сообщения с отладочной информацией в локальный лог.
#define LLOG_D(loger, logText, ...) LOG(loger, Loger::LL_DEBUG, logText, __VA_ARGS__)

/// Макрос вывода сообщения с отладочной информацией в глобальный лог.
#define LOG_D(logText, ...) LLOG_D(LogerGlobal::instance(), logText, __VA_ARGS__)


/// Макрос вывода сообщения с трассировкой в локальный лог.
#define LLOG_T(loger, logText, ...) LOG(loger, Loger::LL_TRACE, logText, __VA_ARGS__)

/// Макрос вывода сообщения с трассировкой в глобальный лог.
#define LOG_T(logText, ...) LLOG_T(LogerGlobal::instance(), logText, __VA_ARGS__)

// Использование макросов в виде:
// LOG_C("some text");
// LOG_C(QString(std_string_var.c_str()));
// LOG_C("some parametrs text %1 %2", .arg(P1).arg(P2));
// LLOG_C аналогично LOG_C но указывая вначале в какой логер записывать данные.
// LOG аналогично LLOG но указывая вторым параметром уровень лога.


/// Макрос проверяет принимается ли сообщение указанного уровня логером.
#define IS_LOG(loger, level) (level <= loger->getCurLogerLevel())


/// Макрос проверяет принимается ли сообщение о критической ошибке в локальный лог.
#define IS_LLOG_C(loger) IS_LOG(loger, Loger::LL_CERROR)

/// Макрос проверяет принимается ли сообщение о критической ошибке в глобальный лог.
#define IS_LOG_C() IS_LOG(LogerGlobal::instance(), Loger::LL_CERROR)


/// Макрос проверяет принимается ли сообщение о ошибке в локальный лог.
#define IS_LLOG_E(loger) IS_LOG(loger, Loger::LL_ERROR)

/// Макрос проверяет принимается ли сообщение о ошибке в глобальный лог.
#define IS_LOG_E() IS_LOG(LogerGlobal::instance(), Loger::LL_ERROR)


/// Макрос проверяет принимается ли сообщение с предупреждением в локальный лог.
#define IS_LLOG_W(loger) IS_LOG(loger, Loger::LL_WARNING)

/// Макрос проверяет принимается ли сообщение с предупреждением в глобальный лог.
#define IS_LOG_W() IS_LOG(LogerGlobal::instance(), Loger::LL_WARNING)


/// Макрос проверяет принимается ли сообщение с информацией в локальный лог.
#define IS_LLOG_I(loger) IS_LOG(loger, Loger::LL_INFO)

/// Макрос проверяет принимается ли сообщение с информацией в глобальный лог.
#define IS_LOG_I() IS_LOG(LogerGlobal::instance(), Loger::LL_INFO)


/// Макрос проверяет принимается ли сообщение с отладочной информацией в локальный лог.
#define IS_LLOG_D(loger) IS_LOG(loger, Loger::LL_DEBUG)

/// Макрос проверяет принимается ли сообщение с отладочной информацией в глобальный лог.
#define IS_LOG_D() IS_LOG(LogerGlobal::instance(), Loger::LL_DEBUG)


/// Макрос проверяет принимается ли сообщение с трассировкой в локальный лог.
#define IS_LLOG_T(loger) IS_LOG(loger, Loger::LL_TRACE)

/// Макрос проверяет принимается ли сообщение с трассировкой в глобальный лог.
#define IS_LOG_T() IS_LOG(LogerGlobal::instance(), Loger::LL_TRACE)


/**
 * \brief Класс логирования.
 *
 * \n
 * Класс обеспечивает приём 
 * поступающих сообщений
 * определённых категорий либо
 * обработку сырого лога
 */
class Loger : public QObject
{
    
    Q_OBJECT

public:
    
    
    // TODO: заменить на enum class?
    /**
     * \brief Перечисление для уровней логирования.
     *
     * \n
     */
    enum LogerLevels {
        LL_CERROR = 0,
        LL_ERROR,
        LL_WARNING,
        LL_INFO,
        LL_DEBUG,
        LL_TRACE,
        LL_ENUM_SIZE
    };
    
    Q_ENUM(LogerLevels)     // Чтобы зарегистрировать enum в системе QT-объектов и т.д....
    
    QMap<int, QString> LogerLevelsStringsMap = []() {
        QMap<int, QString> llm;
        llm.insert(0, "LL_CERROR");
        llm.insert(1, "LL_ERROR");
        llm.insert(2, "LL_WARNING");
        llm.insert(3, "LL_INFO");
        llm.insert(4, "LL_DEBUG");
        llm.insert(5, "LL_TRACE");
        llm.insert(6, "LL_ENUM_SIZE");
        return llm;
    }();
    
    
    //static LogerLevels defaultParseLevel = LL_WARNING;

    // Конструктор
    Loger(QObject *parent = nullptr, LogerLevels parseLevel = LL_TRACE);

    // Деструктор
    ~Loger();
    
    
    
    
    //// Метод добавления сырого лога в виде стандартного строкового потока.
    //void addStringStreamLog(const std::stringstream &stream);
    
    // Метод добавления сообщения определённого уровня.
    void addMessageToLog(LogerLevels level, const QString &msg);
    
    // Метод закрытия текущего открытого сообщения.
    void finishLogMessage();
    
//    // Метод получения и обработки сырого лога.
//    void handleRawLog(const QString& logstr);
    
    // Метод добавления обработанной сырой строчки сообщения.
    // TODO: Т.к. нельзя передавать переменные класса как параметры по умолчанию для методов этого класса, то
    // можно сделать перегрузку этого метода и добавить такой же, но с сигнатурой как у этой строчки:
    //void addProcessedRawMessageToLog(bool errorFlag = false, LogerLevels level, const QString& str);
    void addProcessedRawMessageToLog(bool errorFlag = false, bool isTagMsgContinuing = false);
    
    
    
    /// Геттер для текущего уровня логирования экземпляра логера.
    LogerLevels getCurLogerLevel() const { return curLogerLevel_; }
    /// Сеттер для текущего уровня логирования экземпляра логера.
    void setCurLogerLevel(LogerLevels parseLevel) { curLogerLevel_ = parseLevel; emit logerLevelChanged();}
    //// Сеттер для уровня логирования, который будет установлен по умолчанию.
    //void setDefaultLogerParseLevel(LogerLevels level);

    /// Геттер для максимального количества хранимых сообщений в списке логов.
    int getMaxLogListSize() const { return maxLogListSize_; }
    /// Сеттер для максимального количества хранимых сообщений в списке логов.
    void setMaxLogListSize(int maxLogListSize) { maxLogListSize_ = maxLogListSize; }
    
    // TODO: Найти применение...
    /// Геттер для максимальной длины хранимого сообщения.
    int getMaxLogMsgLength() const { return maxLogMsgLength_; }
    /// Сеттер для максимальной длины хранимого сообщения.
    void setMaxLogMsgLength(int maxLogMsgLength) { maxLogMsgLength_ = maxLogMsgLength; }
    
    // Метод сброса текущих значений переменных, работающих с сырым логом.
    void resetCountersValues();
    
    // Метод сброса ВСЕХ переменных, кроме уровня лога и....
    void resetLoger();
    
    
    
    
    /**
     * \brief Структура для получения информации о логе.
     *
     * \n
     * Структура хранит общее кол-во сообщений за всё время (с учётом удалённых) и
     * список количеств сообщений по каждой категории логирования.
     */
    struct LogerInfo {
        /// Общее число сообщений (с учётом удалённых из лога).
        int totalNumberOfLogMessages_;
        /// Список количеств сообщений по каждой категории.
        QList<int> levelsMsgsCountList_;
    };
    
    
    
    
    /**
     * \brief Класс для хранения строки лога.
     *
     */
    class LogLine {
    public:
        /// Конструктор создания строки лога (1). Задаёт строчку, уровень логирования сообщения и флаг ошибки.
        LogLine(int msgNum, QString line, LogerLevels level, bool msgErrorFlag) : msgNum_(msgNum), line_(line), level_(level), msgErrorFlag_(msgErrorFlag) {}
        /// Конструктор создания строки лога (2). Задаёт строчку и флаг ошибки. 
        LogLine(int msgNum, QString line, bool msgErrorFlag) : msgNum_(msgNum), line_(line), msgErrorFlag_(msgErrorFlag) {}
        /// Конструктор создания строки лога (3). Задаёт строчку и уровень логирования сообщения.
        LogLine(int msgNum, QString line, LogerLevels level) : msgNum_(msgNum), line_(line), level_(level) {}
        /// Конструктор создания строки лога (4). Задаёт строчку.
        LogLine(int msgNum, QString line) : msgNum_(msgNum), line_(line) {}
        
        /// Геттер самой строчки.
        const QString &getLine() const { return line_; }
        /// Геттер уровня логирования сообщения.
        const LogerLevels &getLogerLevel() const { return level_; }
        /// Геттер флага ошибки.
        bool getMsgErrorFlag() const { return msgErrorFlag_; }
        /// Геттер номера сообщения.
        int getMsgNum() const { return msgNum_; }
        
        /// Сеттер флага ошибки.
        void setMsgErrorFlag(bool msgErrorFlag) { msgErrorFlag_ = msgErrorFlag; }
        
        /// Метод расширения хранимой строки.
        void appendLine(const QString& str) { line_.append(str); }
        
    private:
        /// Номер сообщения среди всех сообщений лога (включая удалённые).
        int msgNum_;
        /// Сама хранимая строчка.
        QString line_ = "";
        /// Уровень логирования сообщения.
        LogerLevels level_;
        /// Флаг ошибки.
        bool msgErrorFlag_ = false;
    };
    
    
    // static void initializeStatics();
    
    
    /// Геттер для указателя на список строк лога.
    const QList<LogLine>* getLogList() const { return logList_; }
    
    /// Геттер для общего числа сообщений (с учётом удалённых из лога)
    int getNumOfMsgs() { return totalNumberOfLogMessages_; }
    /// Геттер для списка количеств сообщений по каждой категории.
    QList<int> getLevelsMsgsCountList_() { return levelsMsgsCountList_; }
    // Метод передачи внутренней информации о текущем логе в получаемую структуру
    // (общем кол-ве сообщений и кол-вах по каждой категории).
    void getInfo(LogerInfo &logerInfo);
    
    
    
    // TODO: Избавиться
    
    //// Метод обновления информации о количестве и номерах сообщений.
    //void updateMsgsNumInfo(LogerLevels level);
    
    
    
    
    
    
signals:
    
    /// Сигнал о вставке новой строчки в лог.
    void newLineInserted();
    
    /// Сигнал об обновлении последней строчки в логе.
    void lastLineUpdated();
    
    /// Сигнал изменения уровня логирования.
    void logerLevelChanged();
    
    
    //void messageLengthExceeded();
    
    //void longLogExtended();
    
    

    /// UV: Сигнал получения тега прогресса.
    ///     Сейчас работает так, что просто передаёт сколько на данный момент процентов мы уже прошли.
    void progressTagGotten(int completedPercentage);
    
    
public slots:
    
    // Слот для проверки допустимого размера списка строк лога.
    void checkLogListSize();
    
    // UV: 
    void abonentLogUpdated(const QString& msg);
    
    // Слот получения и обработки сырого лога.
    void handleRawLog(const QString logstr);
    
    
    
private:
    
    
    
    
    // ============= СТАТИЧЕСКИЕ =============
    
    // Сеттеры статиков
    static int initMaxOpeningTagLength();
    static QStringList initTagsNoBracketsList();
    static QString initTagsPartsInEnd();
    static QString initTagsPartsInBegin();
    
    
    // Статик-поля    
    
    /// Наибольшая длина среди открывающих тегов для применения в дальнейшей обработке сырого лога.
    static const int maxOpeningTagLength_;
    
    static const QRegularExpression::PatternOptions options_;   ///< Опции для регексирования
    
    static const QString tagClose_;                             ///< Общий закрывающий тег.
    static const QString tagsPartsInEnd_;                       ///< Всевозможные комбинации правых частей открывающий тегов.
    static const QString tagsPartsInBegin_;                     ///< Всевозможные комбинации левых частей открывающий тегов.
    static const QString tagsMessagesJoined_;                   ///< Объединённые в одну строчку через "|" названия категорий логирования.
    
    static const QRegularExpression lastChar_RE_;               ///< Регекс последнего символа в строке.
    static const QRegularExpression tagOpen_RE_;                ///< Регекс открытого тега.
    static const QRegularExpression tagOpenPartInBegin_RE_;     ///< Регекс правой части открытого тега в начале строки.
    static const QRegularExpression tagOpenPartInEnd_RE_;       ///< Регекс левой части открытого тега в конце строки.
    
    static const QRegularExpression tagClose_RE_;               ///< Регекс закрытого тега.
    static const QRegularExpression tagClosePartInBegin_RE_;    ///< Регекс правой части закрытого тега в начале строки.
    static const QRegularExpression tagClosePartInEnd_RE_;      ///< Регекс левой части закрытого тега в конце строки.
    
    static const QStringList tagsMessagesList_;                 ///< Список названий категорий сообщений.
    static const QStringList tagsNoBracketsList_;               ///< Список названий категорий сообщений с некоторыми спецсимволами тегов.
    
    
    
    
    
    
    
    
    /// Список строк лога.
    QList<LogLine> *logList_;
    
    
    
    
    
    
    
    
    // ============= СЫРОЙ ЛОГ =============
    ///
    QTimer* timer_;
    // TODO: Производительно ли добавлять куски полученного лога к строчной переменной?
    //       Использовать другой способ?
    ///
    QString rawBuff_;
    
    
    /// Буфер для хранения частей поступающих открытых и закрытых тегов сообщений сырого лога.
    QString tagBuff_;
    
    /// Общее число сообщений (с учётом удалённых из лога).
    /// Первое сообщение в логе будет иметь номер "0", второе - "1" и т.д.
    int totalNumberOfLogMessages_{};
    
    /// Список количеств сообщений по каждой категории.
    QList<int> levelsMsgsCountList_;
    
    
    
    // Активные переменные считывания и регексирования строки
    
    /// Текущий принимаемый уровень логирования экземпляра логера.
    LogerLevels curLogerLevel_;
    /// Флаг, указывающий, открыт ли в данный момент тег.
    bool wasTagOpened_{};
    /// Текущая длина сообщения.
    int curMsgLen_{};
    /// Доп. переменная при обработке сырого лога.
    //bool doubleEmptyCheck_{};
    
    /// Максимальная длина сообщения, хранимого в списке логов.
    int maxLogMsgLength_ = 256;
    /// Максимальное количество сообщений, хранимых в списке логов.
    int maxLogListSize_ = 1024;      // = MAX_LOG_TAG_MESSAGE_SIZE;
    
    
    // TODO: RECOMMENT:
    // -- Проверять во всех блоках IS_LLOG_T (их вроде всего 7) был ли предыдущий LogLine в списке уровня TRACE,
    //    т.к. если оно TRACE, то делать logListShort->last().appendLine(),
    //    а если же оно другого уровня, то делаем logListShort->append().
    // !! Помнить, что там может быть перенос между ними, т.е. иногда надо вставлять и новую строчку в список.
    //    Расширять строчку надо тогда, когда текущий iList == 0. Когда iList != 0, значит пред. и тек. оба TRACE --> добавляем новую строчку.
    // -- Для этого добавляем endedWithNewLine, который будет true, когда logstr (?) будет зак-ся с '\n' (или как?)
    /// Флаг, указывающий, была ли последняя строка завершена переносом.
    //bool endedWithNewLine_{};
    
    // Флаги ошибок обработки лога:  (2/3 флагов так и не нашли применение)
    /// Флаг некорректного завершения сообщения.
    //bool errorMsgIncorrectClosing_{};
    ////bool errorDoubleOpenTag_{};
    ////bool errorNoOpenTag_{};
    
    // TODO: Был нужен при считывании rawLog. Сейчас уже вопросик.
    // Уровень логирования текущего считываемого сообщения.
    LogerLevels curMsgLogerLevel_;
    
    
    ///
    //bool msgErrorEnding_Tagged_{}, msgErrorEnding_Trace_{};
    bool msgErrorEnding_Trace_{};
    
    
};



//Q_DECLARE_METATYPE(Loger::LogerLevels)













/**
 * \brief Класс глобального логирования.
 *
 * \n
 * Класс является синглтоном для глобальной работы с логами приложения.
 */
class LogerGlobal : public Loger
{
    
    Q_OBJECT    
    
public:

    /// Запрет конструктора копирования.
    LogerGlobal(const LogerGlobal&) = delete;
    /// Запрет конструктора присваивания.
    LogerGlobal& operator=(const LogerGlobal&) = delete;

    ///// Деструтор синглтона.
    //~LogerGlobal() { instance_ = nullptr; }
    ~LogerGlobal() {
        qDebug() << "LogerGlobal::~LogerGlobal";
        //LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("LogerGlobal::~LogerGlobal"));
        addMessageToLog(Loger::LL_TRACE, QString("LogerGlobal::~LogerGlobal"));
    }

    /// Статический метод получения экземпляра синглтона.
    static LogerGlobal& instance() {
        static LogerGlobal instance_;
        return instance_;
    }
    
    
    //void addMessageToGlobalLog(Loger::LogerLevels level, const QString& msg) {
    // TODO: А надо ли "const QString objName" передавать по ссылке? Всё-таки из разных потоков передаётся..
    //       (тот же вопрос про "msg", уже не помню даже как оформлял сигнатуру когда создавал метод)
    void addMessageToGlobalLog(const QString objName, Loger::LogerLevels level, const QString msg) {
        emit addGlobalMessageSignal(objName, level, msg);
    }
    
    ///
    void addObjectNameToAcceptableSet(const QString& objName) {
        objectsNamesAcceptableMessagesSet_.insert(objName);
    }
    ///
    void addObjectNameToAllSet(const QString& objName) {
        objectsNamesAllSet_.insert(objName);
    }
    
    
    
public slots:
    

    
    
signals:
    
    // TODO: Тот же вопрос как к addMessageToGlobalLog: что по "&msg" или "msg"?
    ///
    void addGlobalMessageSignal(const QString objName, Loger::LogerLevels level, const QString &msg);
    
    
    
private:

    ///
    QSet<QString> objectsNamesAcceptableMessagesSet_;
    ///
    QSet<QString> objectsNamesAllSet_;
    
    /// Приватный конструтор для запрета создания экземпляра извне.
    LogerGlobal() {
        
        setObjectName("LogerGlobal_inst");
        
        // Коннект для передачи сообщений с учётом многопоточности.
        connect(this, &LogerGlobal::addGlobalMessageSignal,
                this, [this](const QString objName, Loger::LogerLevels level, const QString &msg) {
                    if (objectsNamesAcceptableMessagesSet_.contains(objName)) {
                        addMessageToLog(level, msg);
                    }
                },
                Qt::QueuedConnection);
        
        
    }

};






#endif // LOGER_H

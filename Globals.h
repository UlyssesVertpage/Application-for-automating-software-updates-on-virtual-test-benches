#ifndef GLOBALS_H
#define GLOBALS_H


#include <QObject>
#include <QMap>
#include <QCheckBox>
#include <QPushButton>
#include <QProgressBar>

//#include "Loger.h"
//#include "LogViewer.h"
class Loger;
class LogViewer;


//#define COLUMNS_NUMS 5
//#define COLUMNS_NAMES {"Выбор", "Название абонента", "Прогресс-бар", "Логи", "Стоп"}














//#define CONFIG_DATA_FILE_PATH "config-data-5"
#define CONFIG_DATA_FILE_PATH "./config-data.txt"
//#define CONFIG_DATA_FILE_PATH "./config-data-big.txt"
//#define ALGS_LOCAL_PATH "./algorithms"


#define LOG_QRECT(logRect) (QString("QRect(%1,%2 %3x%4)").arg(logRect.x()).arg(logRect.y()).arg(logRect.width()).arg(logRect.height()))
#define LOG_QSIZE(logSize) (QString("QSize(%1, %2)").arg(logSize.width()).arg(logSize.height()))
#define LOG_QPOINT(logPoint) (QString("QPoint(%1,%2)").arg(logPoint.x()).arg(logPoint.y()))
#define LOG_BOOL(logBool) (QString(logBool ? "true" : "false"))




namespace Globals {
    
    /// Глобальный шрифт
    extern QString widgetsFontGlobal;
    /// Глобальный шрифт для полей отображения логов
    extern QString logPlainTextEditStyleSheet_;
    /// Глобальный шрифт для логвьюера
    extern QString logViewerStyleSheet_;
    
    
    ///// Глобальный styleSheet для кнопок групповых таблиц главного окна
    //extern QString groupTablePushButtonStyleSheet_;
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- каркас.
    extern QString groupTableLogPushButtonStyleSheet_Base_;
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- цвета покоя.
    extern QString groupTableLogPushButtonStyleSheet_Usual_;
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- цвета успешного завершения.
    extern QString groupTableLogPushButtonStyleSheet_Success_;
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- цвета при остановке.
    extern QString groupTableLogPushButtonStyleSheet_Stop_;
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- цвета при ошибке.
    extern QString groupTableLogPushButtonStyleSheet_Error_;
    
    
    /// Глобальный styleSheet для прогресс-баров групповых таблиц главного окна
    extern QString groupTableProgressBarStyleSheet_;
    //extern QStr
    
    
    // Для currentAlgorithmName_ в MainWindow
    extern QString emptyStr_;
    
}






/**
 * \brief Структура для хранения информации о логировании абонента.
 *
 * \n
 * .
 */
struct AbonentLogStruct {
    Loger* loger{nullptr};
    LogViewer* logViewer{nullptr};
};








/**
 * \brief Структура для хранения информации об абоненте.
 *
 * \n
 * .
 */
struct AbonentInfo {
    QString ip, user, ssh_path, port;
};

/**
 * \brief Структура для хранения информации об алгоритме.
 *
 * \n
 * .
 */
struct AlgorithmInfo {
    QString alg_path, descr;
    QStringList execAbonents;
};



/// Псевдоним для словаря абонентов.
typedef QMap<QString, AbonentInfo> AbonentsMap;
/// Псевдоним для словаря групп абонентов.
typedef QMap<QString, QStringList> AbonentsGroupsMap;
/// Псевдоним для словаря алгоритмов.
typedef QMap<QString, AlgorithmInfo> AlgorithmsMap;






/**
 * \brief Структура для хранения указателей на виджеты в
 * строке с абонентом в определённой группе.
 * \n
 * .
 */
struct AbonentGroupViewInfo {
    int tableRowIndex;
    QCheckBox* groupChBox;
    QCheckBox* chooseChBox;
    QPushButton *logBtn, *stopBtn;
    QProgressBar* successPrgBr;
    //QLabel* successLbl;
    //GroupTable* groupTable;
};


/// Псевдоним для словаря информации о конкретной таблице (группе) конретного абонента.
typedef QMap<QString, AbonentGroupViewInfo> AbonentGroupsViewInfoMap;





/*

class Globals : public QObject
{
    Q_OBJECT
    
public:

    //static Globals* instance() { if (instance_ == nullptr) { instance_ = new Globals(); } return (instance_); }
    static Globals& instance() {
        static Globals instance;
        return instance;
    }
    
    // Qt 5.7.1
    QMap<int, QString> tablesColumns = []() {
        QMap<int, QString> tc;
        tc.insert(0, "Выбор");
        tc.insert(1, "Название абонента");
        tc.insert(2, "Прогресс-бар");
        tc.insert(3, "Логи");
        tc.insert(4, "Стоп");
        return tc;
    }();

    // Qt 5.15
    // QMap<int, QString> tablesColumns = {{0, "Выбор"},
    //                                     {1, "Название абонента"},
    //                                     {2, "Прогресс-бар"},
    //                                     {3, "Логи"},
    //                                     {4, "Стоп"}};

private:
    
    //static Globals* instance_;
    
    //Globals(QObject* parent = nullptr) : QObject(parent) {}
    Globals() {}
    //~Globals() { instance_ = nullptr; }
    ~Globals() {}
    Globals(const Globals&) = delete;
    Globals& operator=(const Globals&) = delete;
    
    
};

*/




#endif // GLOBALS_H

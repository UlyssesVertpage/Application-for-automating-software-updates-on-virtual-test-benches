#ifndef CONFIGDATA_H
#define CONFIGDATA_H


#include <QObject>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QDir>
#include <QList>
#include <QMap>

// #include <QMutex>

#include <lua.hpp> 

#include "Globals.h"
//#include "MainWindow.h"




// TODO:

// 1. Для всех блоков с continue в ".cpp" файле добавить окна-предпреждения,
// чтобы была ясна некорретность файла конфигурации.

// 2. Так и будем считывать конфиг-й Lua-файл из какой-то конкретной папки через
// QFile в конструкторе или как-то иначе?

// 3. Заменить insert на insert(std::move) (?), чтобы не копировать списки абонентов






/**
 * \brief Класс чтения, обработки и хранения конфигурационных данных.
 *
 * \n
 * .
*/
class ConfigData : public QObject
{
    Q_OBJECT
    
public:
    
    
    static ConfigData& instance() {
        static ConfigData instance;
        return instance;
    }
    
    ~ConfigData() {}
    
    
    
    //ConfigData(MainWindow *mainWindow);
    // Конструтор.
    // ConfigData(QObject *parent);
    
    // Деструктор.
    // ~ConfigData();
    
    
    
    //
    bool loadConfigData();
    
    
    // TODO: Нужен ли?
    /// Сеттер для указателя на главное окно приложения.
    //void setMainWindow(MainWindow* mainWindow) { mainWindow_ = mainWindow; }
    
    ///// Метод проверки успешного считывания конфиг-го файла.
    //bool wasConfigReadSucceeded() { return wasConfigReadSucceeded_; }
    
    // Метод формат-го вывода в консоль текущего стека для переданного Lua-состояния.
    void printLuaStack(lua_State* L);
    // Метод формат-го вывода в консоль словаря всех абонентов.
    void printAbonentsMap();
    // Метод формат-го вывода в консоль словаря всех групп абонентов.
    void printAbonentsGroupsMap();
    // Метод формат-го вывода в консоль словаря всех алгоритмов.
    void printAlgorithmsMap();
    

    
    
    // СТРУКТУРЫ ДЛЯ АЛГОРИТМОВ, АБОНЕНТОВ И ИХ ГРУПП.

    // Новое
    
    ///// Псевдонимы для списков абонентов в группе.
    //typedef QList<QString> AbonentGroup;
    ///// Псевдонимы для списков допустимых абонентов для запуска алгоритмов.
    //typedef QList<QString> ExecAbonents;
    
    ///**
    // * \brief Структура для хранения информации об абоненте.
    // *
    // * \n
    // * .
    // */
    //struct AbonentInfo {
    //    //QString name, ip, user, ssh_path;
    //    QString ip, user, ssh_path;
    //};
    //
    ///**
    // * \brief Структура для хранения информации об алгоритме.
    // *
    // * \n
    // * .
    // */
    //struct AlgorithmInfo {
    //    QString alg_path, descr;
    //    QStringList execAbonents;
    //};
    //
    //
    //
    ///// Псевдоним для словаря абонентов.
    //typedef QMap<QString, AbonentInfo> AbonentsMap;
    ///// Псевдоним для словаря групп абонентов.
    //typedef QMap<QString, QStringList> AbonentsGroupsMap;
    ///// Псевдоним для словаря алгоритмов.
    //typedef QMap<QString, AlgorithmInfo> AlgorithmsMap;
    
    
    
    // Старое
    
    ///// Псевдонимы для списков абонентов в группе.
    //typedef QList<QString> AbonentsGroup;
    ///// Псевдонимы для списков допустимых абонентов для запуска алгоритмов.
    //typedef QList<QString> ExecAbonents;
    //
    ///**
    // * \brief Структура для хранения информации об абоненте.
    // *
    // * \n
    // * .
    // */
    //struct AbonentInfo {
    //    //QString name, ip, user, ssh_path;
    //    QString ip, user, ssh_path;
    //};
    //
    ///**
    // * \brief Структура для хранения информации об алгоритме.
    // *
    // * \n
    // * .
    // */
    //struct AlgorithmInfo {
    //    QString alg_path, descr;
    //    ExecAbonents execAbonents;
    //};
    //
    //
    //
    ///// Псевдоним для словаря абонентов.
    //typedef QMap<QString, AbonentInfo> AbonentsMap;
    ///// Псевдоним для словаря групп абонентов.
    //typedef QMap<QString, AbonentsGroup> AbonentsGroupsMap;
    ///// Псевдоним для словаря алгоритмов.
    //typedef QMap<QString, AlgorithmInfo> AlgorithmsMap;
    
    
    
    ///// Геттер словаря всех абонентов.
    //AbonentsMap* getAbonentsMap() { return abonentsMap_; }
    ///// Геттер словаря всех групп абонентов.
    //AbonentsGroupsMap* getAbonentsGroupsMap() { return abonentsGroupsMap_; }
    ///// Геттер словаря всех алгоритмов.
    //AlgorithmsMap* getAlgorithmsMap() { return algorithmsMap_; }
    
    /// Геттер словаря всех абонентов.
    const AbonentsMap& getAbonentsMap() const { return abonentsMap_; }
    /// Геттер словаря всех групп абонентов.
    const AbonentsGroupsMap& getAbonentsGroupsMap() const { return abonentsGroupsMap_; }
    /// Геттер словаря всех алгоритмов.
    const AlgorithmsMap& getAlgorithmsMap() const { return algorithmsMap_; }
    
    /// Геттер для словаря информации по каждому абоненту об указателях на кнопки по его строчкам в таблицах
    QMap<QString, AbonentGroupsViewInfoMap>& getAbonentsViewInfoMap() { return abonentsViewInfoMap_; }
    
    
signals:
    
    
    
private:
    
    
    // Приватные конструктор, деструктор, оператор присваивания и копирования
    explicit ConfigData(QObject *parent = nullptr) : QObject(parent) {}
    ConfigData(const ConfigData&) = delete;
    ConfigData& operator=(const ConfigData&) = delete;
    // static ConfigData *m_instance;
    
    
    
    
    
    
    
    // TODO: Нужен ли?
    /// Указатель на главное окно приложения.
    // MainWindow* mainWindow_;
    
    // TODO: Придумать систему сообщений/флагов на случаи, когда файл неккоретно был обработан?
    //       Отображать отдельным окном сообщения об ошибках чтения (те что в qDebug в .cpp файле)? При помощи класса логирования?
    /// Флаг успешного считывания конфиг-го файла.
    //bool wasConfigReadSucceeded_{};
    

    
    // КОНФИГ-Е ДАННЫЕ
    
    /// Словарь для данных об абонентах.
    AbonentsMap abonentsMap_;
    //QList<AbonentInfo>* abonentsList_;
    
    /// Словарь для данных о группах абонентов.
    AbonentsGroupsMap abonentsGroupsMap_;
    //QList<AbonentsGroup>* abonentsGroupsList_;
    
    /// Словарь для данных об алгоритмах.
    AlgorithmsMap algorithmsMap_;
    //QList<Algorithm>* algorithmsList_;
    
    
    /// Словарь для информации по каждому абоненту об указателях на кнопки по его строчкам в таблицах.
    QMap<QString, AbonentGroupsViewInfoMap> abonentsViewInfoMap_;
    
    
    
};

#endif // CONFIGDATA_H

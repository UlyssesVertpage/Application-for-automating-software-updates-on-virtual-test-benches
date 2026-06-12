#ifndef GLOBALDATA_H
#define GLOBALDATA_H


#include <QObject>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QDir>
#include <QList>
#include <QMap>
#include <QDirIterator>

#include <QMetaType>


#include <lua.hpp> 

#include "Globals.h"
#include "Loger.h"









/**
 * \brief Класс чтения, обработки и хранения конфигурационных данных.
 *
 * \n
 * .
*/
class GlobalData : public QObject
{
    Q_OBJECT
    
public:
    
    
    static GlobalData& instance() {
        static GlobalData instance;
        return instance;
    }
    
    ~GlobalData() {}
    
    //
    bool loadConfigData();
    //
    void setClassesNames();
    
    
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
    
    
    /// Геттер словаря всех абонентов.
    const AbonentsMap& getAbonentsMap() const { return abonentsMap_; }
    /// Геттер словаря всех групп абонентов.
    const AbonentsGroupsMap& getAbonentsGroupsMap() const { return abonentsGroupsMap_; }
    /// Геттер словаря всех алгоритмов.
    const AlgorithmsMap& getAlgorithmsMap() const { return algorithmsMap_; }
    
    ///
    //const AlgorithmInfo* getAlgorithmInfo(const QString& algName) const { return &algorithmsMap_[algName]; }
    //const AlgorithmInfo* getAlgorithmInfo(const QString& algName) const { return &algorithmsMap_.find(algName).value(); }
    
    
    /// Геттер для словаря информации по каждому абоненту об указателях на кнопки по его строчкам в таблицах.
    QMap<QString, AbonentGroupsViewInfoMap>& getAbonentsViewInfoMap() { return abonentsViewInfoMap_; }
    
    /// Геттер для словаря информации о логировании каждого абонента.
    QMap<QString, AbonentLogStruct>& getAbonentsLogsMap() { return abonentsLogsMap_; }
    
    
signals:
    
    
    
private:
    
    
    // Приватные конструктор, деструктор, оператор присваивания и копирования
    explicit GlobalData(QObject* parent = nullptr);
    GlobalData(const GlobalData&) = delete;
    GlobalData& operator=(const GlobalData&) = delete;
    // static GlobalData *m_instance;
    

    ///
    QStringList classesNames_;
    

    
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
    
    
    /// Словарь для информации о логировании каждого абонента.
    QMap<QString, AbonentLogStruct> abonentsLogsMap_;
    
    
    
};

#endif // GLOBALDATA_H

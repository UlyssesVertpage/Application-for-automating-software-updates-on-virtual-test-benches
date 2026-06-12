#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGuiApplication>
#include <QScreen>
#include <QWindow>
#include <QDebug>
#include <QObject>
#include <QStringBuilder>
#include <QTextStream>

#include <QStyle>
#include <QFontDatabase>
#include <QFile>
#include <QIODevice>
#include <QDir>

#include <QList>
#include <QMap>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QToolBar>
#include <QGroupBox>
#include <QScrollArea>
#include <QComboBox>
#include <QScrollBar>

#include <QPushButton>
#include <QToolButton>


#include <lua.hpp> 

#include "Globals.h"
#include "GlobalData.h"
#include "GroupTable.h"
#include "Launcher.h"
//class GlobalData;
#include "LogViewer.h"



//#define COLUMNS_NUMS 5


//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE






// TODO:

// +++ 1. Сделать прогресс-бары на 50% при стопах... (временно)

// 2. Cделать отображение окон логов по принципу isActive (или ещё чего-то?), а не по isVisible

// +++ 3. Перенос взаимодействия с графикой в MainWindow:
//        Перенести весь код из коннекта из Launcher::whenAlgorithmFinished (вызывается в
//        коннекте AlgorithmExecution::algorithmExecutionFinished в методе Launcher::setUpFutures)
//        в слот MainWindow::handleAlgExecResult.

// +++ 4. Сделать считывание файлов ssh-ключей из локальных и из ресурсов в зависимости от
//    наличия двоеточия ":" в начале пути.

// 5. Создавать единые temp-файлы для одинаковых ключей: получится ли использовать в классе Launcher список созданных файлов для текущих ключей?

// 6. Там, где в AlgExec стоят return (например, при невозможности прочитать файл), нужно
//    вызывать algExecFinished или хоть что-то, чтобы завершать работу объекта и его потока.

// +++ 7. При выполнении алгоритма с некоторыми закрытыми группами, когда их абоненты используется в алгоритме прямо сейчас,
//    находясь в другой группе, в промежутке до запуска следующего алгоритма прогресс-бары и кнопки логирования закрытых групп
//    при последующем открытии остаются незатронутыми:
//    НЕОБХОДИМО подавать сигнальчики изменения и на неактивные во время выполнения алгоритма группы тоже...

// 7.1. Пересмотреть и изменить структуру задания всех параметров всех кнопок (чекбоксов, пушбаттонов, 
//      прогресс-баров и т.д.) в зависимости от отображения/активности/скрытия и т.д.




// TODO (Globals): 

// 1. Вынести всё глобально нужное из класса в сам файл. Объявления в ".h", определения в ".cpp".
//    Пока касается QMap на названия стобцов.





// TODO (GlobalData): 

// 1. Для всех блоков с continue в ".cpp" файле добавить окна-предпреждения,
// чтобы была ясна некорретность файла конфигурации.

// 2. Так и будем считывать конфиг-й Lua-файл из какой-то конкретной папки через
// QFile в конструкторе или как-то иначе?

// 3. Заменить insert на insert(std::move) (?), чтобы не копировать списки абонентов

// 4. Добавить пути к файлам куда-то. Можно в ресурсы. Туда тот же "config-1.txt".
//    В дальнейшем можно придумать функцию перерисовки всего centralWidget для 
//    возможности без перезапуска приложения загружать обновлённый конфиг.

// 5. Сделать диалоговые окна-подтверждения для запуска и стопа алгоритмов.

// 6. Задавать путь для всех алгоритмов (а также ключей и т.д.) через отдельную переменную в Lua-файле,
//    чтобы каждый раз не менять пути у всех алгоритмов сразу, а только в одном месте.



// TODO (Loger):        всё в его хэдере

// TODO (LogViewer):    рассмотреть шрифт Consolas заместо Ariel. у него все символы одного размера в пикселях.















class MenuItemContainer : public QWidget {
    Q_OBJECT
public:
    // По ссылке текст??
    MenuItemContainer(const QString &text, QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout(this);
        checkbox = new QCheckBox(text);
        checkbox->setAttribute(Qt::WA_TransparentForMouseEvents);       // Отключение чекбокса        
        layout->addWidget(checkbox);
        //layout->setContentsMargins(10, 5, 10, 5);
        setLayout(layout);
    }
protected:
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            checkbox->setChecked(!checkbox->isChecked());
            event->accept();
        }
    }
private:
    QCheckBox* checkbox;
};













class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    
    // Конструктор.
    MainWindow(QWidget *parent = nullptr);
    
    // Деструктор.
    ~MainWindow();
    
    //
    bool loadConfigData();
    
    ///
    QList<GroupTable*>& getGroupTablesList() { return groupTablesList_; }
    
    
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
    
    

    void closeEvent(QCloseEvent *event) override;
    
    
    
    
public slots:
        
    ///
    void currentAlgorithmChanged(int index);
    ///
    void launchBtnClicked();
    ///
    void hideGroupsChBoxClicked();
    ///
    void chooseAllAbonentsChBoxClicked();
    ///
    void updateChooseAllAbonentsChBox();
    ///
    void updateHideGroupsChBox();
    ///
    void launcherDone();
    ///
    void toggleAbnLogViewer(const QString& abnName);
    ///
    void algExecCreated(const QString& abnName, const QString& objName);
    ///
    void algExecDestroyed(const QString& abnName, const QString& objName);
    ///
    void handleAlgExecResult(const QString& abnNameFinished, int exitCode, int exitStatus, bool stopFlag);
    ///
    void timerSlot();
    
    
    
signals:
    
    ///
    void stopOneAbonentExecutionClicked(const QString& abnName);
    ///
    void stopAllAbonentsExecutionsClicked();
    ///
    void logViewerGlobalNeedToggle();
    
    
private:
    
    
    // ЛОГИРОВАНИЕ
    
    /// Таймер...
    QTimer* timerGlobal_;
    /// Счётчик таймера...
    static int timerCounter_;
    
    ///
    LogViewer* logViewerGlobal_;
    ///
    // TODO: Сделать локальной стековой
    QPoint* logViewerGlobalPoint_{nullptr};
    QRect logViewerGlobalRect_;

    
    
    
    // ТЕКУЩИЙ АЛГОРИТМ
    
    static QString emptyStr_;
    QString& currentAlgorithmName_{Globals::emptyStr_};
    
    Launcher* currentLauncher_;
    
    
    
    
    
    // КОНФИГ-Е ДАННЫЕ
    
    ///
    GlobalData& globalDataSingleton_;
    // Ещё можно здесь задать GlobalData* configDataSingleton_ = nullptr;.
    // А в ".cpp" написать configDataSingleton_ = &GlobalData::instance();
    
    
    /// Словарь для данных об абонентах.
    const AbonentsMap& abonentsMap_;
    
    /// Словарь для данных о группах абонентов.
    const AbonentsGroupsMap& abonentsGroupsMap_;
    
    /// Словарь для данных об алгоритмах.
    const AlgorithmsMap& algorithmsMap_;
    
    
    
    /// Словарь для информации по каждому абоненту об указателях на кнопки по его строчкам в таблицах.
    QMap<QString, AbonentGroupsViewInfoMap>& abonentsViewInfoMap_;
    
    ///
    QMap<QString, AbonentLogStruct>& abonentsLogsMap_;
    
    
    
    
    // ГРАФИКА И КНОПКИ.
    
    // Поле формы главного окна.
    //Ui::MainWindow *ui;

    // ПЛАВАЮЩИЕ ПАНЕЛИ И ВИДЖЕТЫ
    
    /// Панель инструментов главного окна.
    QToolBar* toolBar_;
    
    
    
    // ЦЕНТРАЛЬНЫЙ ВИДЖЕТ
    
    /// Центральный виджет главного окна.
    QWidget* centralWidget_;   
    /// Макет центрального виджета.
    QVBoxLayout* centralLayout_;
    
    
    /// Макет для панели кнопок сверху.
    QHBoxLayout* topButtons_;
    /// Комбобокс для выбора текущего алгоритма.
    QComboBox* currentAlgorigthmComboBox_;
    /// 
    QPushButton* launchButton_;
    /// 
    QPushButton* stopAllButton_;
    
    /// Макет для кнопок выбора всех абонентов и скрытия всех групп.
    QVBoxLayout* chooseAndHideLayout_;
    // QGridLayout* chooseAndHideLayout_;
    ///
    QCheckBox* hideGroupsChBox_;
    ///
    QCheckBox* chooseAllAbonentsChBox_;
    
    
    /// 
    QScrollArea* scrollArea_;   
    /// 
    QVBoxLayout* scrollAreaLayout_;   
    ///
    QWidget* scrollAreaWidget_;
    /// 
    QVBoxLayout* scrollAreaWidgetLayout_;
    
    
    ///
    QList<GroupTable*> groupTablesList_;       // Де-факто содержит children от scrollAreaWidget_
    
    
};



#endif // MAINWINDOW_H




#include "MainWindow.h"
//#include "ui_mainwindow.h"

//#include "GroupTable.h"



int MainWindow::timerCounter_ = 0;


// Для currentAlgorithmName_

//QString MainWindow::emptyStr_ = "";

//QString MainWindow::emptyStr_ = []() {
//    return "";
//}();

//void MainWindow::initEmptyStr() {
//    emptyStr_ = "";
//}











/**
 * \brief Конструктор главного окна
 * \return Конструктор ничего не возвращает
 * 
 * \n
 * Внутри задаются параметры отображения, геометрии. Устанавливаются панель инструментов,
 * центральный виджет и его макет, главная таблица для работы с абонентами
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , globalDataSingleton_(GlobalData::instance())              // В хэдере есть пояснение рядом с переменной.
    , abonentsMap_(globalDataSingleton_.getAbonentsMap())
    , abonentsGroupsMap_(globalDataSingleton_.getAbonentsGroupsMap())
    , algorithmsMap_(globalDataSingleton_.getAlgorithmsMap())
    , abonentsViewInfoMap_(globalDataSingleton_.getAbonentsViewInfoMap())
    , abonentsLogsMap_(globalDataSingleton_.getAbonentsLogsMap())
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    
    
    
    globalDataSingleton_.setClassesNames();
    
    
    setObjectName("MainWindow_inst");
    //LogerGlobal::instance().addObjectNameToAcceptableSet(objectName());
    LOG_REG_OBJNAME(objectName());
    
    
    
    
    
    
    qDebug().noquote() << "\n========== FIRST DEBUG MESSAGE ==========\n";
    //LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_DEBUG, "\n========== FIRST DEBUG MESSAGE ==========\n");
    LogerGlobal::instance().addMessageToLog(Loger::LL_DEBUG, "\n========== FIRST DEBUG MESSAGE ==========\n");
    


    // ============= ГЛОБАЛЬНЫЙ ТАЙМЕР =============
    QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(processOneThing()));
    //connect(timer, SIGNAL([]() {
    //    qt_noop();
    //}()), this, SLOT([]() {
    //    qt_noop();
    //}()));
    //connect(timer, SIGNAL(timeout()), this, SLOT([this](){
    //    ++timerCounter_;
    //    QString logstr = QString("timerCounter_ is %1").arg(timerCounter_);
    //    qDebug().noquote() << logstr;
    //    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_DEBUG, logstr);
    //}()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timerSlot();
    timer->start(1000);    


    
    
    // ============= ГЛОБАЛЬНЫЙ ШРИФТ =============
    // NOTE: Помнить, что ЛВГ не имеет родителя в лице MainWindow --> шрифт нужно задавать самостоятельно
    setStyleSheet(Globals::widgetsFontGlobal);
    //setStyleSheet(Globals::widgetsFontGlobal);
    //setStyleSheet("QWidget { font-family: 'Arial'; font-size: 14px; font-weight: bold; }");
    
    
    
    
    // ============= НАСТРОЙКА ОКНА =============
    setWindowTitle("SysWizard");
    setWindowIcon(style()->standardIcon(QStyle::SP_TitleBarMenuButton));
    

    
    // ============= НАСТРОЙКА ПАНЕЛИ ИНСТРУМЕНТОВ =============
    int alignOffset = 50;
    
    toolBar_ = new QToolBar(this);
    addToolBar(toolBar_);
    toolBar_->setMovable(false);
    toolBar_->setFloatable(false);
    toolBar_->setContextMenuPolicy(Qt::PreventContextMenu);
    toolBar_->setStyleSheet(
        "QToolButton {"
        "    font: bold 13px 'Arimo';"
        //"    font-size: 16px;"                    // Есть: Arial, Courier, Roboto, Serif, Tahoma, Terminus
        //"    font-family: 'Consolas';"            // Нет: Consolas, Times New Roman, Verdana
        "    border: 1px solid grey;"
        "}"
        "QToolBar {"
        "    spacing: 20px;"    // 5
        "    margin: 40px;"     // 5
        "}"
    );
    
    QToolButton* fileBtn = new QToolButton(toolBar_);
    fileBtn->setText("Файл");
    fileBtn->setFixedWidth(70);
    QToolButton* glbLogBtn = new QToolButton(toolBar_);
    glbLogBtn->setText("Логи");
    glbLogBtn->setFixedWidth(70);
    QToolButton* aboutBtn = new QToolButton(toolBar_);
    aboutBtn->setText("Справка");
    aboutBtn->setFixedWidth(70);
    
    
    // TODO: Наладить отображение менюшек.
    //QToolButton* logSettingsBtn = new QToolButton(toolBar_);
    //logSettingsBtn->setText("Настройки логов");
    //logSettingsBtn->setFixedWidth(150);
    //logSettingsBtn->setPopupMode(QToolButton::MenuButtonPopup);
    
    
    QToolButton* accesibleObjectsBtn = new QToolButton(toolBar_);
    //QAction* accesibleObjectsAct = new QAction(toolBar_);
    QMenu* accesibleObjectsMenu = new QMenu(toolBar_);
    accesibleObjectsBtn->setMenu(accesibleObjectsMenu);
    //accesibleObjectsBtn->setPopupMode(QToolButton::MenuButtonPopup);
    accesibleObjectsBtn->setPopupMode(QToolButton::InstantPopup);
    accesibleObjectsBtn->setText("Выбор объектов глоб. лога");
    accesibleObjectsBtn->setFixedWidth(215);
    
    
    //QMenu* logSettingsMenu = new QMenu(toolBar_);
    //QMenu* accesibleObjectsMenu = new QMenu("Список допустимых объектов", logSettingsMenu);
    
    //QAction* showAccesibleObjectsAct = new QAction("Список допустимых объектов");
    //logSettingsMenu->addAction(showAccesibleObjectsAct);
    ////connect(showAccesibleObjectsAct, &QAction::triggered, this, &MainWindow::showAccesibleObjects);
    //connect(&LogerGlobal::instance(), &LogerGlobal::objectAddedToSetOfAll, [accesibleObjectsMenu](const QString objName) {
    //    //accesibleObjectsMenu->actions().contains()
    //    QAction* act = new QAction(objName, accesibleObjectsMenu);
    //    accesibleObjectsMenu->addAction(act);
    //});
    QMenu* groupTablesLogSettingsMenu = new QMenu("GroupTables", accesibleObjectsMenu);
    QMenu* logersLogSettingsMenu = new QMenu("Logers", accesibleObjectsMenu);
    QMenu* logViewersLogSettingsMenu = new QMenu("LogViewers", accesibleObjectsMenu);
    QMenu* algExecsLogSettingsMenu = new QMenu("AlgExecs", accesibleObjectsMenu);
    
    
    
    QList<QCheckBox*>* groupTablesLogSettingsCHBList = new QList<QCheckBox*>;
    QList<QCheckBox*>* logersLogSettingsCHBList = new QList<QCheckBox*>;
    QList<QCheckBox*>* logViewersLogSettingsCHBList = new QList<QCheckBox*>;
    QList<QCheckBox*>* algExecsLogSettingsCHBList = new QList<QCheckBox*>;
    
    QList<QCheckBox*>* allLogSettingsCHBList = new QList<QCheckBox*>;
    
    
    
    QWidgetAction* chooseAllGroupTablesWA = new QWidgetAction(accesibleObjectsMenu);
    QCheckBox* chooseAllGroupTablesCHB = new QCheckBox(QString("ВЫБРАТЬ ВСЕХ").leftJustified(alignOffset, ' '), accesibleObjectsMenu);
    // groupTablesLogSettingsCHBList.append(chooseAllGroupTablesCHB);
    chooseAllGroupTablesCHB->setObjectName(chooseAllGroupTablesCHB->objectName() + "__LOG_CHB");
    chooseAllGroupTablesWA->setDefaultWidget(chooseAllGroupTablesCHB);
    groupTablesLogSettingsMenu->addAction(chooseAllGroupTablesWA);
    chooseAllGroupTablesCHB->setChecked(false);
    
    QWidgetAction* chooseAllLogersWA = new QWidgetAction(accesibleObjectsMenu);
    QCheckBox* chooseAllLogersCHB = new QCheckBox(QString("ВЫБРАТЬ ВСЕХ").leftJustified(alignOffset, ' '), accesibleObjectsMenu);
    // logersLogSettingsCHBList.append(chooseAllLogersCHB);
    chooseAllLogersCHB->setObjectName(chooseAllLogersCHB->objectName() + "__LOG_CHB");
    chooseAllLogersWA->setDefaultWidget(chooseAllLogersCHB);
    logersLogSettingsMenu->addAction(chooseAllLogersWA);
    chooseAllLogersCHB->setChecked(false);
    
    QWidgetAction* chooseAllLogViewersWA = new QWidgetAction(accesibleObjectsMenu);
    QCheckBox* chooseAllLogViewersCHB = new QCheckBox(QString("ВЫБРАТЬ ВСЕХ").leftJustified(alignOffset, ' '), accesibleObjectsMenu);
    // logViewersLogSettingsCHBList.append(chooseAllLogViewersCHB);
    chooseAllLogViewersCHB->setObjectName(chooseAllLogViewersCHB->objectName() + "__LOG_CHB");
    chooseAllLogViewersWA->setDefaultWidget(chooseAllLogViewersCHB);
    logViewersLogSettingsMenu->addAction(chooseAllLogViewersWA);
    chooseAllLogViewersCHB->setChecked(false);
    
    QWidgetAction* chooseAllAlgExecsWA = new QWidgetAction(accesibleObjectsMenu);
    QCheckBox* chooseAllAlgExecsCHB = new QCheckBox(QString("ВЫБРАТЬ ВСЕХ").leftJustified(alignOffset, ' '), accesibleObjectsMenu);
    // algExecsLogSettingsCHBList.append(chooseAllAlgExecsCHB);
    chooseAllAlgExecsCHB->setObjectName(chooseAllAlgExecsCHB->objectName() + "__LOG_CHB");
    chooseAllAlgExecsWA->setDefaultWidget(chooseAllAlgExecsCHB);
    algExecsLogSettingsMenu->addAction(chooseAllAlgExecsWA);
    chooseAllAlgExecsCHB->setChecked(false);
    
    
    
    
    
    
    
    
    
    // TODO: ЗДЕСЬ В КОННЕКТАХ НАДО ПРИЛЕПИТЬ LOG_TURN_OBJ ЧТОБЫ ЛОВИТЬ/НЕ ЛОВИТЬ ОТ КОНКРЕТНЫХ ОБЪЕКТОВ ЛОГИ
    
    
    
    connect(chooseAllGroupTablesCHB, &QCheckBox::toggled, this, [groupTablesLogSettingsCHBList](bool check) {
        int size = groupTablesLogSettingsCHBList->size();
        for (int i = 0; i < size; ++i) { groupTablesLogSettingsCHBList->at(i)->setChecked(check); }
    });
    connect(chooseAllLogersCHB, &QCheckBox::toggled, this, [logersLogSettingsCHBList](bool check) {
        int size = logersLogSettingsCHBList->size();
        for (int i = 0; i < size; ++i) { logersLogSettingsCHBList->at(i)->setChecked(check); }
    });
    connect(chooseAllLogViewersCHB, &QCheckBox::toggled, this, [logViewersLogSettingsCHBList](bool check) {
        int size = logViewersLogSettingsCHBList->size();
        for (int i = 0; i < size; ++i) { logViewersLogSettingsCHBList->at(i)->setChecked(check); }
    });
    connect(chooseAllAlgExecsCHB, &QCheckBox::toggled, this, [algExecsLogSettingsCHBList](bool check) {
        int size = algExecsLogSettingsCHBList->size();
        for (int i = 0; i < size; ++i) { algExecsLogSettingsCHBList->at(i)->setChecked(check); }
    });
    
    
    
    
    // ============= ПЕРВАЯ РЕГИСТРАЦИЯ ОБЪЕКТОВ ДЛЯ ГЛОБАЛЬНОГО ЛОГЕРА =============
    LOG_REG_OBJNAME(objectName());
    LOG_ADD_OBJNAME(objectName());
    LOG_REG_OBJNAME(GlobalData::instance().objectName());
    LOG_ADD_OBJNAME(GlobalData::instance().objectName());
    LOG_REG_OBJNAME(LogerGlobal::instance().objectName());
    LOG_ADD_OBJNAME(LogerGlobal::instance().objectName());
    
    
    // TODO: Переделку через такие чекбоксы:
    QWidgetAction* chooseAllWA = new QWidgetAction(accesibleObjectsMenu);
    QCheckBox* chooseAllCHB = new QCheckBox(QString("ВЫБРАТЬ ВСЕХ").leftJustified(alignOffset, ' '), accesibleObjectsMenu);
    chooseAllCHB->setObjectName("chooseAllCHB__LOG_CHB");
    //chooseAllCHB->setObjectName(chooseAllCHB->text() + "__LOG_CHB");
    chooseAllWA->setDefaultWidget(chooseAllCHB);
    accesibleObjectsMenu->addAction(chooseAllWA);
    chooseAllCHB->setChecked(false);
    
    QWidgetAction* mainWindowWA = new QWidgetAction(accesibleObjectsMenu);
//    MenuItemContainer* mainWindowMIC = new MenuItemContainer(QString(objectName()).leftJustified(alignOffset, ' '), this);
//    mainWindowMIC->setObjectName("__LOG_CHB");
    QCheckBox* mainWindowCHB = new QCheckBox(QString(objectName()).leftJustified(alignOffset, ' '), accesibleObjectsMenu);
    mainWindowCHB->setObjectName(mainWindowCHB->text() + "__LOG_CHB");
    mainWindowWA->setDefaultWidget(mainWindowCHB);
    accesibleObjectsMenu->addAction(mainWindowWA);
    mainWindowCHB->setChecked(true);
    
    QWidgetAction* globalDataWA = new QWidgetAction(accesibleObjectsMenu);
    QCheckBox* globalDataCHB = new QCheckBox(QString(GlobalData::instance().objectName()).leftJustified(alignOffset, ' '), accesibleObjectsMenu);
    globalDataCHB->setObjectName(globalDataCHB->text() + "__LOG_CHB");
    globalDataWA->setDefaultWidget(globalDataCHB);
    accesibleObjectsMenu->addAction(globalDataWA);
    globalDataCHB->setChecked(false);
    
    QWidgetAction* logerGlobalWA = new QWidgetAction(accesibleObjectsMenu);
    QCheckBox* logerGlobalCHB = new QCheckBox(QString(LogerGlobal::instance().objectName()).leftJustified(alignOffset, ' '), accesibleObjectsMenu);
    logerGlobalCHB->setObjectName(logerGlobalCHB->text() + "__LOG_CHB");
    logerGlobalWA->setDefaultWidget(logerGlobalCHB);
    accesibleObjectsMenu->addAction(logerGlobalWA);
    logerGlobalCHB->setChecked(false);

    
    // connect(chooseAllAlgExecsCHB, &QCheckBox::toggled, this, [algExecsLogSettingsCHBList](bool check) {
        
    // }



    //QAction* mainWindowAct = new QAction(objectName(), accesibleObjectsMenu);
    //accesibleObjectsMenu->addAction(mainWindowAct);
    //QAction* globalDataAct = new QAction(GlobalData::instance().objectName(), accesibleObjectsMenu);
    //accesibleObjectsMenu->addAction(globalDataAct);
    //QAction* logerGlobalAct = new QAction(LogerGlobal::instance().objectName(), accesibleObjectsMenu);
    //accesibleObjectsMenu->addAction(logerGlobalAct);
    
    
    allLogSettingsCHBList->append(chooseAllGroupTablesCHB);
    allLogSettingsCHBList->append(chooseAllLogersCHB);
    allLogSettingsCHBList->append(chooseAllLogViewersCHB);
    allLogSettingsCHBList->append(chooseAllAlgExecsCHB);
    allLogSettingsCHBList->append(mainWindowCHB);
    allLogSettingsCHBList->append(globalDataCHB);
    allLogSettingsCHBList->append(logerGlobalCHB);    
    
    connect(chooseAllCHB, &QCheckBox::toggled, this, [allLogSettingsCHBList](bool check) {
        int size = allLogSettingsCHBList->size();
        for (int i = 0; i < size; ++i) {
            allLogSettingsCHBList->at(i)->setChecked(check);
        }
    });
    
    
    
    accesibleObjectsMenu->addMenu(groupTablesLogSettingsMenu);
    accesibleObjectsMenu->addMenu(logersLogSettingsMenu);
    accesibleObjectsMenu->addMenu(logViewersLogSettingsMenu);
    accesibleObjectsMenu->addMenu(algExecsLogSettingsMenu);
    //logSettingsMenu->addMenu(accesibleObjectsMenu);
    //logSettingsBtn->setMenu(logSettingsMenu);
    
    
    
    toolBar_->addWidget(fileBtn);
    toolBar_->addWidget(glbLogBtn);
    toolBar_->addWidget(aboutBtn);
    toolBar_->addWidget(accesibleObjectsBtn);
    //toolBar_->addWidget(logSettingsBtn);
    
    
    
    
    
    
    
    
            
            
    
    
    
    // ============= НАСТРОЙКА ЦЕНТРАЛЬНОГО ВИДЖЕНТА =============
    centralWidget_ = new QWidget(this);
    setCentralWidget(centralWidget_);
    
    centralLayout_ = new QVBoxLayout(centralWidget_);
    //centralLayout_->setContentsMargins(80, 60, 80, 60);
    centralLayout_->setContentsMargins(40, 30, 40, 30);
    
    
    
    scrollArea_ = new QScrollArea(centralWidget_);
    scrollAreaLayout_ = new QVBoxLayout(scrollArea_);
    // К слову, из-за заполненности прокручиваемой области маржа не работает.
    //scrollAreaLayout_->setContentsMargins(30, 30, 30, 30);                           // Это margins, отступы --- на заметку!!!
    
    scrollAreaWidget_ = new QWidget(scrollArea_);
    scrollAreaWidgetLayout_ = new QVBoxLayout(scrollAreaWidget_);
    scrollAreaWidgetLayout_->setContentsMargins(30, 30, 30, 30);                       // Это margins, отступы --- на заметку!!!
    
    // scrollAreaWidget_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);    
    
    scrollAreaLayout_->addWidget(scrollAreaWidget_);
    scrollArea_->setWidget(scrollAreaWidget_);
    scrollArea_->setWidgetResizable(true);   // Позволяет внутреннему виджету подстраиваться под ширину scrollArea
    // scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    
    
    
    
    
    // ============= ЗАГРУЗКА ДАННЫХ ИЗ КОНФ-ГО ФАЙЛА =============
    // Нельзя задавать здесь ссылки на мапы из ConfigData, т.к. ссылки должны быть инициализированы, а не определены
    // после объявления. Поэтому задаю в списке иниц-и конструктора. В хэдере есть пояснялка рядом с переменной.
    
    
    globalDataSingleton_.loadConfigData();
    //globalDataSingleton_.initLogMap();
    
    
    for (const QString& abnName : abonentsMap_.keys()) {
        AbonentLogStruct als;
        
        Loger* loger = new Loger(this);
        QString logerObjName = QString("Loger_%1_inst").arg(abnName);
        loger->setObjectName(logerObjName);
        LOG_REG_OBJNAME(logerObjName);
        LOG_ADD_OBJNAME(logerObjName);
        
        //QAction* logerAct = new QAction(logerObjName, logersLogSettingsMenu);
        //logersLogSettingsMenu->addAction(logerAct);
        QWidgetAction* logerWA = new QWidgetAction(accesibleObjectsMenu);
        QCheckBox* logerCHB = new QCheckBox(QString(logerObjName).leftJustified(alignOffset, ' '), accesibleObjectsMenu);
        logerCHB->setObjectName(logerObjName + "__LOG_CHB");
        logerWA->setDefaultWidget(logerCHB);
        logerCHB->setChecked(false);
        logersLogSettingsMenu->addAction(logerWA);
        logersLogSettingsCHBList->append(logerCHB);
        
        
        
        
        LogViewer* logViewer = new LogViewer(loger, this);
        logViewer->setWindowFlags(Qt::Window);
        logViewer->setVisible(false);
        logViewer->setWindowTitle("Logging :: " + abnName);
        QString logViewerObjName = QString("LogViewer_%1_inst").arg(abnName);
        logViewer->setObjectName(logViewerObjName);
        LOG_REG_OBJNAME(logViewerObjName);
        LOG_ADD_OBJNAME(logViewerObjName);
        
        //QAction* logViewerAct = new QAction(logViewerObjName, logViewersLogSettingsMenu);
        //logViewersLogSettingsMenu->addAction(logViewerAct);
        QWidgetAction* logViewerWA = new QWidgetAction(accesibleObjectsMenu);
        QCheckBox* logViewerCHB = new QCheckBox(QString(logViewerObjName).leftJustified(alignOffset, ' '), accesibleObjectsMenu);
        logViewerCHB->setObjectName(logViewerObjName + "__LOG_CHB");
        logViewerWA->setDefaultWidget(logViewerCHB);
        logViewerCHB->setChecked(false);
        logViewersLogSettingsMenu->addAction(logViewerWA);
        logViewersLogSettingsCHBList->append(logViewerCHB);
                    
        
        als.loger = loger;
        als.logViewer = logViewer;
        abonentsLogsMap_[abnName] = als;
        
        QString algExecObjName = QString("AlgExec_%1_inst").arg(abnName);
        LOG_REG_OBJNAME(algExecObjName);
        LOG_ADD_OBJNAME(algExecObjName);
        
        //QAction* algExecAct = new QAction(algExecObjName, algExecsLogSettingsMenu);
        //algExecsLogSettingsMenu->addAction(algExecAct);
        QWidgetAction* algExecWA = new QWidgetAction(accesibleObjectsMenu);
        QCheckBox* algExecCHB = new QCheckBox(QString(algExecObjName).leftJustified(alignOffset, ' '), accesibleObjectsMenu);
        algExecCHB->setObjectName(algExecObjName + "__LOG_CHB");
        algExecWA->setDefaultWidget(algExecCHB);
        algExecCHB->setChecked(false);
        algExecsLogSettingsMenu->addAction(algExecWA);
        algExecsLogSettingsCHBList->append(algExecCHB);
        
    }
    
    globalDataSingleton_.printAbonentsMap();
    globalDataSingleton_.printAbonentsGroupsMap();
    globalDataSingleton_.printAlgorithmsMap();
    qDebug().noquote() << "";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "");

    
    

    
    
    // ============= НАСТРОЙКА ТАБЛИЦЫ =============
    
    
    LOG_MSG(objectName(), Loger::LL_TRACE, "\n====================== CREATING GROUPTABLES ======================\n");
    
    //groupTablesList_ = new QList<GroupTable*>;
    for (const QString& groupName : abonentsGroupsMap_.keys()) {
        const QStringList& abonentsGroup = abonentsGroupsMap_.value(groupName);
        GroupTable* gt = new GroupTable(groupName, abonentsGroup, centralWidget_);      // LOG_REG_OBJNAME(objectName()) вызывается внутри конструктора GroupTable
        
        QString groupTableObjName = gt->objectName();
        //QAction* groupTableAct = new QAction(gt->objectName(), groupTablesLogSettingsMenu);
        //groupTablesLogSettingsMenu->addAction(groupTableAct);
        QWidgetAction* groupTableWA = new QWidgetAction(accesibleObjectsMenu);
        QCheckBox* groupTableCHB = new QCheckBox(QString(groupTableObjName).leftJustified(alignOffset, ' '), accesibleObjectsMenu);
        groupTableCHB->setObjectName(groupTableObjName + "__LOG_CHB");
        groupTableWA->setDefaultWidget(groupTableCHB);
        groupTableCHB->setChecked(true);
        groupTablesLogSettingsMenu->addAction(groupTableWA);
        groupTablesLogSettingsCHBList->append(groupTableCHB);
        
        scrollAreaWidgetLayout_->addWidget(gt);
        
        connect(gt, &GroupTable::anyChooseAbonentChBoxToggled, [this](const QString& abnName, bool mode) {
            
            
            AbonentGroupsViewInfoMap& agvim = abonentsViewInfoMap_[abnName];
            for (const QString& groupName: agvim.keys()) {
                agvim[groupName].chooseChBox->setChecked(mode);     // Все связные коннекты к QCheckBox::toggle внутри GroupTable...
            }
            
            
            if (!mode) {
                chooseAllAbonentsChBox_->setChecked(false);
            }
            else {
                updateChooseAllAbonentsChBox();
            }
        });
        

        
        connect(gt->getGroupChooseChBox(), &QCheckBox::toggled, [this]() {
            updateChooseAllAbonentsChBox();
            updateHideGroupsChBox();
        });
        
        groupTablesList_.append(gt);
    }
    scrollAreaWidgetLayout_->addStretch(1);
    
    
    LOG_MSG(objectName(), Loger::LL_TRACE, "\n==================================================================\n");
    
            
            
    
    
    // ============= НАПОЛНЕНИЕ СТРУКТУР ИНФОРМАЦИИ О КНОПКАХ В ТАБЛИЦАХ И ГРУППАХ АБОНЕНТОВ =============
    
    
    
    
    
    
    
    
    
    // ============= КНОПКИ И ВЫБОР =============
    
    // Макет для панели кнопок сверху.
    topButtons_ = new QHBoxLayout();
    
    
    
    // 1. Выбор текущего алгоритма
    // 1.1. Подвязать комбобокс ко всем табличкам и менять у них столбец
    //      с возможностью выбора абонентов (через сигнал, издаваемый при выборе комбобокса)
    
    
    
    // Комбобокс для выбора текущего алгоритма.
    currentAlgorigthmComboBox_ = new QComboBox(centralWidget_);
    for (const QString& algorithmName : algorithmsMap_.keys()) {
        currentAlgorigthmComboBox_->addItem(algorithmName);
    }
    // TODO: увеличить высоту опций в открытом комбобоксе (слишком низенькие, неудобно тыкать)
    currentAlgorigthmComboBox_->setMinimumSize(400, 40);
    // Посмотреть, мб добавить
    // currentAlgorigthmComboBox_->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    currentAlgorigthmComboBox_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //currentAlgorigthmComboBox_->setToolTip();
    
    currentAlgorithmName_ = algorithmsMap_.keys().at(0);
    qDebug().noquote() << QString("MainWindow: currentAlgorithmName_ is %1").arg(currentAlgorithmName_);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow: currentAlgorithmName_ is %1").arg(currentAlgorithmName_));
    
    
            
            
    // Кнопка запуска
    launchButton_ = new QPushButton("ЗАПУСК", centralWidget_);
    launchButton_->setMinimumSize(100, 40);
    
    
    
    // Кнопка стопа
    stopAllButton_ = new QPushButton("СТОП", centralWidget_);
    stopAllButton_->setMinimumSize(100, 40);
    stopAllButton_->setEnabled(false);
    
    
    
    
    
    // Макет для выбора всех абонентов и скрытия всех групп.
    
    chooseAndHideLayout_ = new QVBoxLayout();
    hideGroupsChBox_ = new QCheckBox("Скрыть все группы");
    chooseAllAbonentsChBox_ = new QCheckBox("Выбрать всех абонентов");
    chooseAndHideLayout_->addWidget(hideGroupsChBox_);
    chooseAndHideLayout_->addWidget(chooseAllAbonentsChBox_);
    
    
    
    
    topButtons_->addWidget(currentAlgorigthmComboBox_);
    topButtons_->addWidget(launchButton_);
    topButtons_->addWidget(stopAllButton_);
    topButtons_->addLayout(chooseAndHideLayout_);
    
    
    
    
    // ============= ВСТАВКА ЭЛЕМЕНТОВ В ЦЕНТР =============
    centralLayout_->addLayout(topButtons_);
    centralLayout_->addWidget(scrollArea_);

    
    
    
    
    
    
    
    
    // ============= ГЛОБАЛЬНОЕ ЛОГИРОВАНИЕ =============
    logViewerGlobal_ = new LogViewer(&LogerGlobal::instance());    
    
    
    // NOTE: Когда ЛВГ не имеет родителя, то теряются шрифты, а когда имеет - окно всегда поверх главного 
    //       (на Винде - да, на Астре же - нет, на ней всё почему-то нормально. либо же это связано с версией Qt (5.7.1 / 5.15))
    //logViewerGlobal_->setParent(nullptr);
    
    
    logViewerGlobal_->setWindowTitle("Global Logging");    
    logViewerGlobal_->setWindowFlags(Qt::Window);
    // logViewerGlobal_->setWindowModality(Qt::WindowModal);                                                                // Блокирует остальные окна.
    logViewerGlobal_->setVisible(false);
    logViewerGlobal_->resize(1600, 800);
    
    
    
    
    
    
    // ============= ПОДКЛЮЧЕНИЕ СИГНАЛОВ И СЛОТОВ =============
    
    
    connect(glbLogBtn, &QToolButton::clicked, [this](){
        emit logViewerGlobalNeedToggle();
    });

    
    
    // TODO: Тестировать на НОРМАЛЬНОМ линуксе, а не этом фуфеле.
    //       Прыгание logViewerGlobal_ по экранам не пропадает.
    // TODO: Когда ширина или высота окна логера больше главного окна лог открывается где-то не там, не по середине.
    //       Надо высчитывать центр главного окна относительно координат на экране и относительно этого уже ставить окно лога.
    connect(this, &MainWindow::logViewerGlobalNeedToggle, [this](){
        bool check = !logViewerGlobal_->isVisible();
        
        qDebug().noquote() << "MainWindow: logViewerGlobal_ visibility is turned" << (check ? "ON" : "OFF");
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow: logViewerGlobal_ visibility is turned ") + (check ? "ON" : "OFF"));
        
        // logViewerGlobal_->show();
        logViewerGlobal_->setVisible(check);
        if (logViewerGlobal_->frameGeometry().topLeft() == *logViewerGlobalPoint_) { return; }
        if (check) {
            logViewerGlobal_->move(*logViewerGlobalPoint_);
            // Не помогает перемещение на нужный экран
            //if (logViewerGlobalPoint_ != nullptr) { logViewerGlobal_->windowHandle()->setScreen(QGuiApplication::screenAt(*logViewerGlobalPoint_)); }
            //if (logViewerGlobalPoint_ != nullptr) {
                qDebug().noquote() << "if: " << logViewerGlobal_->frameGeometry() << *logViewerGlobalPoint_ << frameGeometry().center();
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("if: ")
                                                                              + LOG_QRECT(logViewerGlobal_->frameGeometry()) + " "
                                                                              + LOG_QPOINT((*logViewerGlobalPoint_)) + " "
                                                                              + LOG_QPOINT(frameGeometry().center()));
        }
        else {
            if (logViewerGlobalPoint_ != nullptr) { delete logViewerGlobalPoint_; }
            logViewerGlobalPoint_ = new QPoint(logViewerGlobal_->frameGeometry().topLeft());
            
            qDebug().noquote() << "else: " << logViewerGlobal_->frameGeometry() << *logViewerGlobalPoint_;
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "else: "
                                                                          + LOG_QRECT(logViewerGlobal_->frameGeometry()) + " "
                                                                          + LOG_QPOINT((*logViewerGlobalPoint_)));
            
        }
    });
    
    
    
    connect(currentAlgorigthmComboBox_, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::currentAlgorithmChanged);    
    connect(launchButton_, &QPushButton::clicked, this, &MainWindow::launchBtnClicked);
    connect(hideGroupsChBox_, &QCheckBox::clicked, this, &MainWindow::hideGroupsChBoxClicked);
    connect(chooseAllAbonentsChBox_, &QCheckBox::clicked, this, &MainWindow::chooseAllAbonentsChBoxClicked);
    connect(stopAllButton_, &QPushButton::clicked, [this]() {
        emit stopAllAbonentsExecutionsClicked(); 
    });

    
    
    for (const QString& abnName : abonentsViewInfoMap_.keys()) {
        const AbonentGroupsViewInfoMap& agvim = abonentsViewInfoMap_[abnName];
        for (const QString& groupName : agvim.keys()) {
            
            const AbonentGroupViewInfo& agvi = agvim[groupName];
            
            
            // 1. Привязка кнопок "Логи" для отображения логов по клику для каждого абонента.
            connect(agvi.logBtn, &QPushButton::clicked, [this, abnName]() {
                toggleAbnLogViewer(abnName);
            });
            //connect(agvi.logBtn, &QPushButton::clicked, this, &MainWindow::toggleAbnLogViewer);
            
            
            // 2. Привязка кнопок "Стоп" для досрочного завершения алгоритма по клику для каждого абонента.
            connect(agvi.stopBtn, &QPushButton::clicked, [this, abnName]() {
                emit stopOneAbonentExecutionClicked(abnName);
            });
            
            
            // 3. Привязка прогресс-баров к логерам для изменения прогресса.
            Loger* loger = abonentsLogsMap_[abnName].loger;
            QProgressBar* prgBr = agvi.successPrgBr;
            prgBr->setValue(0);
            // CHECK: Процентное выполнение: сигнал из логера...
            connect(loger, &Loger::progressTagGotten, [prgBr](int completedPercentage) {
                prgBr->setValue(completedPercentage);
            });
            
        }
    }
    

    
    
    // ============= ОБНОВЛЕНИЕ НАЧАЛЬНЫХ ДАННЫХ =============
    currentAlgorithmChanged(currentAlgorigthmComboBox_->currentIndex());
    // TODO:
    // Этот вызов тут стоит, т.к. почему-то внутри updateChooseAbonentsChBxs вызов updateChooseAllAbonentsChBox
    // не ставит чекбокс на false сам. У него видимо не видно чекбоксы, т.к. ещё не вызван mainWindow->show() в main.cpp.
    chooseAllAbonentsChBox_->setChecked(false);
    



    
    
    qDebug().noquote() << geometry();
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, LOG_QRECT(geometry()));

    
    show();
    
    
    qDebug().noquote() << geometry();
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("QRect(%1,%2 %3x%4)").arg(geometry().x()).arg(geometry().y()).arg(geometry().width()).arg(geometry().height()));

    
    
    // ============================= РАБОТА С МОНИТОРАМИ. НЕ УДАЛЯТЬ --> НА БУДУЩЕЕ. =============================
    
    QScreen* primScr = QGuiApplication::primaryScreen();
    // QScreen* curScr = screen();                  // Не работает на Qt5.7.1.
    QScreen* curScr = windowHandle()->screen();
    
    
    
    QList<QScreen*> screens = QGuiApplication::screens();
    for (int i = 0; i < screens.size(); ++i) {
        QScreen* scr = screens.at(i);
        
        qDebug().noquote() << scr->name() << "--- is it primary? :" << QVariant(scr == primScr).toString();
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, scr->name() + " --- is it primary? : " + QVariant(scr == primScr).toString());
        
        qDebug().noquote() << scr->geometry() << "geometry and size" << scr->size();
        QRect g = scr->geometry();
        QSize s = scr->size();
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("QRect(%1,%2 %3x%4)").arg(g.x()).arg(g.y()).arg(g.width()).arg(g.height())
                                                                                   + " geometry and size " 
                                                                                   + QString("QSize(%1, %2)").arg(s.width()).arg(s.height()));
        
        qDebug().noquote() << scr->availableGeometry() << "available geometry and available size" << scr->availableSize();
        QRect ag = scr->availableGeometry();
        QSize as = scr->availableSize();
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("QRect(%1,%2 %3x%4)").arg(ag.x()).arg(ag.y()).arg(ag.width()).arg(ag.height()) 
                                                                                   + " available geometry and available size " 
                                                                                   + QString("QSize(%1, %2)").arg(as.width()).arg(as.height()));
        
        
        // ========================= ВЫВОД ПРИЛОЖЕНИЯ НА ВТОРОСТЕПЕННОМ ЭКРАНЕ =========================
        //if (scr != primScr) {
        //    qDebug().noquote() << "MainWindow::MainWindow: changing current screen on " + scr->name();
        //    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "MainWindow::MainWindow: changing current screen on " + scr->name());
        //    // move(scr->geometry().topLeft());
        //    curScr = scr;
        //}
        
        // logStrBuf_.clear();
    }
    
    
    
    // Размер рамочки окна (зависимый от ОС)
    int frameWidth = frameGeometry().width() - geometry().width();
    int frameHeight = frameGeometry().height() - geometry().height();
    
    //resize(720, screen()->availableSize().height());
    resize(1000 - frameWidth, curScr->availableSize().height() - frameHeight);        // Этот вариант, а не предыдущий, т.к. Qt5.7.1.

    QRect scrGeo = curScr->availableGeometry();
    int x = (scrGeo.width() - width() - frameWidth) / 2 + scrGeo.left(), y = (scrGeo.height() - height() - frameHeight) / 2 + scrGeo.top();
    
    qDebug().noquote() << scrGeo.left() << scrGeo.top();
    qDebug().noquote() << x << y;
    qDebug().noquote() << pos();
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("%1 %2").arg(scrGeo.left()).arg(scrGeo.top()));
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("%1 %2").arg(x).arg(y));
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("QPoint(%1,%2)").arg(pos().x()).arg(pos().y()));

    
    
    
    move(x, y);
    
    
    
    qDebug().noquote() << geometry() << frameGeometry() << normalGeometry() << scrGeo;
    QRect g1 = geometry(), g2 = frameGeometry(), g3 = normalGeometry(), g4 = scrGeo;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, LOG_QRECT(g1) + " " + LOG_QRECT(g2) + " " + LOG_QRECT(g3) + " " + LOG_QRECT(g4));
    
    qDebug().noquote() << curScr->availableGeometry() << curScr->availableSize();
    QRect g5 = curScr->availableGeometry();
    QSize s5 = curScr->availableSize();
    // NOTE: Не использовать QVariant().toString() с Loger-ом, т.к. он не обрабатывает такой формат данных в строковый в отличие от qDebug (касается и QRect, и QPoint, и QSize и т.д.)
    //LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QVariant(curScr->availableSize()).toString() + " " + QVariant(curScr->availableGeometry()).toString());
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("QRect(%1,%2 %3x%4)").arg(g5.x()).arg(g5.y()).arg(g5.width()).arg(g5.height())
                                                                               + " "
                                                                               + QString("QSize(%1, %2)").arg(s5.width()).arg(s5.height()));
    
    
    
    QPoint cntr = frameGeometry().center();
    
    // TODO: NOTE: Временная мера чтобы ЛВГ появлялся на втором монике (если он есть)
    logViewerGlobalPoint_ = new QPoint(cntr.x() - logViewerGlobal_->width() / 2 + (screens.size() == 1 ? 0 : scrGeo.right()), cntr.y() - logViewerGlobal_->height() / 2);
    
    qDebug().noquote() << *logViewerGlobalPoint_;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, LOG_QPOINT((*logViewerGlobalPoint_)));
    
    
    
    emit logViewerGlobalNeedToggle();
    
    
    // ============================= РАБОТА С МОНИТОРАМИ. НЕ УДАЛЯТЬ --> НА БУДУЩЕЕ. =============================
    
    
    
    
    // ============================= ОТКЛЮЧЕНИЕ НЕНУЖНЫХ ОБЪЕКТОВ ОТ ГЛОБ. ЛОГА =============================
    //chooseAllGroupTablesCHB->setChecked(false);
    //chooseAllLogersCHB->setChecked(false);
    //chooseAllLogViewersCHB->setChecked(false);
    //chooseAllAlgExecsCHB->setChecked(false);
    // chooseAllCHB->setChecked(false);
    // mainWindowCHB->setChecked(true);
    
}







/**
 * \brief 
 * \return 
 * 
 * \n
 * 
*/
void MainWindow::timerSlot() {
    //QString logstr = QString("timerCounter_ is %1").arg(MainWindow::timerCounter_);
    QString logstr = QString("MainWindow::timerSlot(): MainWindow::timerCounter_ is   __ ") + QString::number(MainWindow::timerCounter_) + QString(" __");
    if (MainWindow::timerCounter_ % 10 == 0) {
        qDebug().noquote() << logstr;
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_DEBUG, logstr);
    }
    //LogerGlobal::instance().addMessageToLog(Loger::LL_DEBUG, logstr);
    ++(MainWindow::timerCounter_);
}









/**
 * \brief Деструктор главного окна
 * \return Деструктор ничего не возвращает
 * 
 * \n
 * Закрытие главного окна подразумевает закрытие всего приложения и завершение его работы.
 * Динамически выделенные объекты можно не удалять вручную.
*/
MainWindow::~MainWindow() {
    // NOTE: На самом деле это не отображается вовсе, всё заканчивается на closeEvent.
    qDebug().noquote() << "MainWindow::~MainWindow";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::~MainWindow"));
}



void MainWindow::closeEvent(QCloseEvent *) {
    qDebug().noquote() << "MainWindow::closeEvent";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::closeEvent"));
    for (const QString& abnName : abonentsLogsMap_.keys()) {
        AbonentLogStruct& als = abonentsLogsMap_[abnName];
        als.logViewer->turnOnClosePossibility();
        if (als.logViewer != nullptr) {
            qDebug().noquote() << "MainWindow::closeEvent: closing and deleting LogViewer of" << abnName;
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::closeEvent: closing and deleting LogViewer of %1").arg(abnName));
            als.logViewer->close();
            delete als.logViewer;
        }
        if (als.loger != nullptr) {
            qDebug().noquote() << "MainWindow::closeEvent: closing and deleting Loger of" << abnName;
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::closeEvent: closing and deleting Loger of %1").arg(abnName));
            delete als.loger;
        }
    }
    if (logViewerGlobal_ != nullptr) {
        logViewerGlobal_->turnOnClosePossibility();
        logViewerGlobal_->close();
        delete logViewerGlobal_;
    }
}







void MainWindow::toggleAbnLogViewer(const QString& abnName) {
    LogViewer* logViewer = abonentsLogsMap_[abnName].logViewer;
    bool check = logViewer->isVisible();
    logViewer->setVisible(!check);
    qDebug().noquote() << "MainWindow::toggleAbnLogViewer: view turned" << LOG_BOOL(!check) << "on" << abnName;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::toggleAbnLogViewer: view turned %1 on %2").arg(!check).arg(abnName));
}





/**
 * \brief Слот обработки завершения обработки алгоритма.
 * \return Слот ничего не возвращает
 *
 * \n
 *
*/
void MainWindow::launcherDone() {
    qDebug().noquote() << "MainWindow::launcherDone";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::launcherDone"));
    
    // TODO
    currentAlgorigthmComboBox_->setEnabled(true);
    launchButton_->setEnabled(true);
    stopAllButton_->setEnabled(false);
    chooseAllAbonentsChBox_->setEnabled(true);
    hideGroupsChBox_->setEnabled(true);
    
    for (GroupTable* gt : groupTablesList_) {
        gt->getGroupChooseChBox()->setEnabled(true);
        if (gt->getTable()->isVisible()) {
            gt->getTable()->horizontalHeader()->setEnabled(true);
            const QList<QCheckBox*>& chblist = gt->getChooseCheckBoxesList();
            for (QCheckBox* chbox : chblist) {
                chbox->setEnabled(true);
            }
        }
    }
    
    if (currentLauncher_ != nullptr) {
        delete currentLauncher_;
    }
}





// Методы для работы с глобальным логированием объектов...
void MainWindow::algExecDestroyed(const QString& abnName, const QString& objName) {
    // TODO: ??????
}
void MainWindow::algExecCreated(const QString& abnName, const QString& objName) {
    // TODO: ??????
}







/**
 * \brief Слот обработки клика кнопки "ЗАПУСК".
 * \return Слот ничего не возвращает
 * 
 * \n
 *
*/
void MainWindow::launchBtnClicked() {
    
    
    // =========================== ПОЛУЧЕНИЕ ДАННЫХ ОБ ИСПОЛНЯЕМЫХ АБОНЕНТАХ ===========================
    
    QMap<QString, AbonentGroupsViewInfoMap>& abonentsViewInfoMap = GlobalData::instance().getAbonentsViewInfoMap();    
    QMap<QString, AbonentGroupsViewInfoMap> chosenAbonentsViewInfoMap_;    
    // const AbonentsGroupsMap& agm = GlobalData::instance().getAbonentsGroupsMap();
    const QStringList& algExecAbns = algorithmsMap_[currentAlgorithmName_].execAbonents;
    
    for (const QString& abnName : abonentsViewInfoMap.keys()) {
        if (algExecAbns.contains(abnName)) {
            bool check = false;
            const AbonentGroupsViewInfoMap& abvim = abonentsViewInfoMap[abnName];
            for (const QString& groupName : abvim.keys()) {
                const AbonentGroupViewInfo& agvi = abvim[groupName];
                if (agvi.groupChBox->isChecked()) { check = true; break;}
            }
            if (check) {
                for (const QString& groupName : abvim.keys()) {
                    const AbonentGroupViewInfo& agvi = abvim[groupName];
                    const QCheckBox* chbox = agvi.chooseChBox;
                    if (chbox->isChecked()) {       //if (chbox->isVisible() && chbox->isChecked()) {
                        chosenAbonentsViewInfoMap_[abnName][groupName] = agvi;
                    }
                }
            }
        }
    }


    
    if (chosenAbonentsViewInfoMap_.size() == 0) {
        qDebug().noquote() << "MainWindow::launchBtnClicked: no abonents specified for launch.";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::launchBtnClicked: no abonents specified for launch."));
        return;
    }
    
    
    
    for (const QString& abnName : abonentsViewInfoMap.keys()) {
        AbonentGroupsViewInfoMap& agvim = abonentsViewInfoMap[abnName];
        bool found = false;
        for (const QString& groupName : agvim.keys()) {
            bool check = false;
            if (chosenAbonentsViewInfoMap_.contains(abnName)) {
                if (chosenAbonentsViewInfoMap_[abnName].contains(groupName)) {
                    check = true;
                    //if (agvim[groupName].groupChBox->isChecked()) {
                        found = true;
                    //}
                    // connect( chosenAbonentsViewInfoMap_[abnName][groupName].successPrgBr, &QProgressBar::valueChanged);
                }
            }
            AbonentGroupViewInfo& agvi = agvim[groupName];
            agvi.logBtn->setEnabled((!check && !agvi.groupChBox->isChecked() && algExecAbns.contains(abnName) && agvi.chooseChBox->isChecked()) ? true : check);     //agvi.logBtn->setEnabled(check);         //agvi.logBtn->setEnabled(found);
            agvi.logBtn->setStyleSheet(Globals::groupTableLogPushButtonStyleSheet_Usual_);
            agvi.stopBtn->setEnabled(check);
            agvi.successPrgBr->setValue(0);
        }
        AbonentLogStruct& als = abonentsLogsMap_[abnName];
        als.logViewer->setActive(found);        // Этот метод при передаче false следует вызывать вместе с resetLogViewer, т.к. это означает сброс вьюера.
        als.loger->resetLoger();                // А здесь помимо сброса всех данных логера ещё и запускается местный таймер
        als.logViewer->resetLogViewer();
        if (!found) {
            als.logViewer->hide();        // TODO: close точно не нужен? хватит hide?
        }
    }
    
    
    
    //QElapsedTimer eTimer;
    //eTimer.start();
    //currentLauncher_ = new Launcher(chosenAbonentsViewInfoMap_, this);                  // lvalue
    currentLauncher_ = new Launcher(std::move(chosenAbonentsViewInfoMap_), currentAlgorigthmComboBox_->currentText(), this);       // rvalue
    //qint64 time = eTimer.elapsed();
    //qint64 time = eTimer.nsecsElapsed();
    //qDebug().noquote() << QString("MainWindow::launchBtnClicked: launcher creation time passed: %1 ns").arg(time);
    
    
    
    currentAlgorigthmComboBox_->setEnabled(false);
    launchButton_->setEnabled(false);
    stopAllButton_->setEnabled(true);
    chooseAllAbonentsChBox_->setEnabled(false);
    hideGroupsChBox_->setEnabled(false);
    
    for (GroupTable* gt : groupTablesList_) {
        gt->getGroupChooseChBox()->setEnabled(false);
        if (gt->getTable()->isVisible()) {
            gt->getTable()->horizontalHeader()->setEnabled(false);
            const QList<QCheckBox*>& chblist = gt->getChooseCheckBoxesList();
            for (QCheckBox* chbox : chblist) {
                chbox->setEnabled(false);
            }
        }
    }
    
    
    
    
    
    
    // TODO: добавить вовнутрь лаунчера deleteLater, который будет удалять 
    // объект по завершению выполнения алгоритма на всех абонентах.
    
    connect(currentLauncher_, &Launcher::allThreadsFinished, this, &MainWindow::launcherDone);
    connect(this, &MainWindow::stopOneAbonentExecutionClicked, currentLauncher_, &Launcher::terminateOneAbonentExecutionSlot);
    connect(this, &MainWindow::stopAllAbonentsExecutionsClicked, currentLauncher_, &Launcher::terminateAllAbonentsExecutionsSlot);
    connect(currentLauncher_, &Launcher::algExecCreated, this, &MainWindow::algExecCreated);
    connect(currentLauncher_, &Launcher::algExecDestroyed, this, &MainWindow::algExecDestroyed);
    connect(currentLauncher_, &Launcher::processReturnedResult, this, &MainWindow::handleAlgExecResult);
    
    
    qDebug().noquote() << "MainWindow::launchBtnClicked: Launcher created";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::launchBtnClicked: Launcher created"));
    
    currentLauncher_->setUpFutures();
    
    qDebug().noquote() << "MainWindow::launchBtnClicked: futures and watchers set up";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::launchBtnClicked: futures and watchers set up"));
    
}







void MainWindow::handleAlgExecResult(const QString& abnName, int exitCode, int exitStatus, bool stopFlag) {
    
    AbonentGroupsViewInfoMap& agvim = abonentsViewInfoMap_[abnName];
    for (const QString& groupName : agvim.keys()) {
        AbonentGroupViewInfo& agvi = agvim[groupName];
        //agvi.logBtn->setEnabled(false);
        agvi.stopBtn->setEnabled(false);
        // TODO: Позже переделку под success из сырых логов...
        // NOTE: Для agvi.successPrgBr в первую очередь проверять стоп-флаг, т.к. даже при нём код завершения может быть 0.
        agvi.successPrgBr->setValue(stopFlag ? 50 : (exitCode == 0 ? 100 : 0));
        //agvi.successPrgBr->setValue(exitCode == 0 ? 100 : (stopFlag ? 50 : 0));
        if (stopFlag) {
            agvi.logBtn->setStyleSheet(Globals::groupTableLogPushButtonStyleSheet_Stop_);
        }
        else if (exitCode == 0) {
            agvi.logBtn->setStyleSheet(Globals::groupTableLogPushButtonStyleSheet_Success_);
        }
        else {
            agvi.logBtn->setStyleSheet(Globals::groupTableLogPushButtonStyleSheet_Error_);
        }
    }
    
    QString logstr = QString("MainWindow::handleAlgExecResult: abonent %1 finished with exitCode %2 and exitStatus %3").arg(abnName).arg(exitCode).arg(exitStatus);
    qDebug().noquote() << logstr;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_DEBUG, logstr);
    
    // TODO:
}





    
    
    
/**
 * \brief Слот ...
 * \return Слот ничего не возвращает
 * 
 * \n
 *
*/
void MainWindow::updateHideGroupsChBox() {
    for (GroupTable* gt : groupTablesList_) {
        if (gt->getGroupChooseChBox()->isChecked()) {
            hideGroupsChBox_->setChecked(false);
            return;
        }
    }    
    hideGroupsChBox_->setChecked(true);
}




/**
 * \brief Слот ...
 * \return Слот ничего не возвращает
 * 
 * \n
 *
*/
void MainWindow::hideGroupsChBoxClicked() {
    bool check = hideGroupsChBox_->isChecked();
    qDebug().noquote() << "MainWindow::hideGroupsChBoxClicked:" << check;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::hideGroupsChBoxClicked: %1").arg(QVariant(check).toString()));
    for (GroupTable* gt : groupTablesList_) {
        QCheckBox* chBox = gt->getGroupChooseChBox();
        chBox->setChecked(!check);
    }
}





/**
 * \brief Слот ...
 * \return Слот ничего не возвращает
 * 
 * \n
 *
*/
void MainWindow::updateChooseAllAbonentsChBox() {
    for (GroupTable* gt : groupTablesList_) {
        if (gt->getGroupChooseChBox()->isChecked()) {
            for (QCheckBox* chBox : gt->getChooseCheckBoxesList()) {
                if (chBox->isVisible() && !chBox->isChecked()) {
                    chooseAllAbonentsChBox_->setChecked(false);
                    return;
                }
            }
        }
    }    
    chooseAllAbonentsChBox_->setChecked(true);
}






/**
 * \brief Слот ...
 * \return Слот ничего не возвращает
 * 
 * \n
 *
*/
void MainWindow::chooseAllAbonentsChBoxClicked() {
    bool check = chooseAllAbonentsChBox_->isChecked();
    qDebug().noquote() << "MainWindow::chooseAllAbonentsChBoxToggled:" << check;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::chooseAllAbonentsChBoxToggled: %1").arg(QVariant(check).toString()));
    
    const QStringList& algExecAbns = algorithmsMap_[currentAlgorithmName_].execAbonents;
    
    for (const QString& abnName : algExecAbns) {
        const AbonentGroupsViewInfoMap& agvim = abonentsViewInfoMap_[abnName];
        bool needOn = false;
        for (const QString& groupName : agvim.keys()) {
            if (agvim[groupName].groupChBox->isChecked()) {
                needOn = true; break;
            }
        }
        if (needOn) {
            for (const QString& groupName : agvim.keys()) {
                agvim[groupName].chooseChBox->setChecked(check);
            }
        }
    }
    

}



/**
 * \brief Слот обновления чекбоксов выбора абонентов в таблицах.
 * \return Слот ничего не возвращает
 * 
 * \n
 * Слот обновляет чекбоксы выбора в таблицах для абонентов при при переключении алгоритма.
*/
void MainWindow::currentAlgorithmChanged(int index) {
    qDebug().noquote() << "MainWindow::updateAbonentsChooseCheckboxes:" << index << currentAlgorigthmComboBox_->itemText(index);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow::updateAbonentsChooseCheckboxes: %1 %2").arg(index).arg(currentAlgorigthmComboBox_->itemText(index)));
    
    currentAlgorithmName_ = currentAlgorigthmComboBox_->itemText(index);    // QString algorithmName = currentAlgorigthmComboBox_->itemText(index);
    qDebug().noquote() << QString("MainWindow: currentAlgorithmName_ is %1").arg(currentAlgorithmName_);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("MainWindow: currentAlgorithmName_ is %1").arg(currentAlgorithmName_));
    
    // Задаётся всплывающая подсказка с описанием алгоритма.
    currentAlgorigthmComboBox_->setToolTip(algorithmsMap_.value(currentAlgorithmName_).descr);
    
    const QStringList execAbons = algorithmsMap_.value(currentAlgorithmName_).execAbonents;
    qDebug().noquote() << QString("abonentsViewInfoMap_.size(): %1").arg(abonentsViewInfoMap_.size());
    // LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString(abonentsViewInfoMap_.size()));
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("abonentsViewInfoMap_.size(): %1").arg(abonentsViewInfoMap_.size()));
    
    for (const QString& abnName : abonentsViewInfoMap_.keys()) {                         // Кол-во всех абонентов
        bool check = execAbons.contains(abnName);
        qDebug().noquote() << abnName << check;
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("%1 %2").arg(abnName).arg(check));
        bool checkActiveLast = abonentsLogsMap_[abnName].logViewer->isActive();
        for (const QString& groupName : abonentsViewInfoMap_[abnName].keys()) {
            bool isChBoxChecked = abonentsViewInfoMap_[abnName][groupName].chooseChBox->isChecked();
            // Эти две строчки связаны, логи показываются в зависимости от видимости чекбоксов абонентов.
            abonentsViewInfoMap_[abnName][groupName].chooseChBox->setVisible(check);
            abonentsViewInfoMap_[abnName][groupName].logBtn->setEnabled(checkActiveLast || (check && isChBoxChecked));
            qDebug().noquote() << "    " << groupName;
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("    %1").arg(groupName));
        }
    }
    
    updateChooseAllAbonentsChBox();
    updateHideGroupsChBox();
}




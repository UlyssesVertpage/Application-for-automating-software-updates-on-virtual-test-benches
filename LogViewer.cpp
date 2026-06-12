

#include "LogViewer.h"



// Символ некорректного завершения сообщения.
const QString LogViewer::incorrectSignString_   = ".....";


// Формат некорректного завершения сообщения.
const QTextCharFormat LogViewer::incorrectSignFormat_ = []() {
    QTextCharFormat format;
    format.setBackground(QColor("#7a7aff"));            // Qt::blue
    format.setForeground(QColor("#000000"));
    return format;
}();


/**
 * \brief  Функция инициализации цветовой палитры логера по умолчанию.
 * \param[in] void.
 * \return void.
 *
 * \n
 */
void LogViewer::initDefaultColors(){
    themeColors_.resize(2);

    for (int theme = 0; theme < 2; ++theme){
        themeColors_[theme].resize(6);
    }

    themeColors_[1][0].background = QColor("#dd5858");      //
    themeColors_[1][0].foreground = QColor("#000000");      //

    themeColors_[1][1].background = QColor("#ff8833");      //
    themeColors_[1][1].foreground = QColor("#000000");      //

    themeColors_[1][2].background = QColor("#ffff7a");      //
    themeColors_[1][2].foreground = QColor("#000000");      //

    themeColors_[1][3].background = QColor("#7aff7a");      //
    themeColors_[1][3].foreground = QColor("#000000");      //

    themeColors_[1][4].background = QColor("#ffffff");      //
    themeColors_[1][4].foreground = QColor("#333333");      //

    themeColors_[1][5].background = QColor("#333333");      //
    themeColors_[1][5].foreground = QColor("#ffffff");      //

    

    themeColors_[0][0].background = QColor("#dd5858");      // cccccc
    themeColors_[0][0].foreground = QColor("#000000");      // 333333

    themeColors_[0][1].background = QColor("#ff8833");      // 88ff88
    themeColors_[0][1].foreground = QColor("#000000");      // 224422

    themeColors_[0][2].background = QColor("#ffff7a");      // ffffff
    themeColors_[0][2].foreground = QColor("#000000");      // 2a2a2a

    themeColors_[0][3].background = QColor("#7aff7a");      // aa5500
    themeColors_[0][3].foreground = QColor("#000000");      // 554422

    themeColors_[0][4].background = QColor("#000000");      // ffdd88
    themeColors_[0][4].foreground = QColor("#ffffff");      // 552222

    themeColors_[0][5].background = QColor("#ffffff");      // ffaaaa
    themeColors_[0][5].foreground = QColor("#000000");      // 666666

    
    
    
    
    
    
    
    //themeColors_[0][0].background = QColor("#ffcccc");
    //themeColors_[0][0].foreground = QColor("#880000");

    //themeColors_[0][1].background = QColor("#ffe0e0");
    //themeColors_[0][1].foreground = QColor("#aa0000");

    //themeColors_[0][2].background = QColor("#fff0cc");
    //themeColors_[0][2].foreground = QColor("#aa5500");

    //themeColors_[0][3].background = QColor("#f0f0f0");
    //themeColors_[0][3].foreground = QColor("#000000");

    //themeColors_[0][4].background = QColor("#e0ffe0");
    //themeColors_[0][4].foreground = QColor("#008800");

    //themeColors_[0][5].background = QColor("#ffffff");
    //themeColors_[0][5].foreground = QColor("#2a2a2a");
    
    
    
    
    //themeColors_[1][0].background = QColor("#dd5858");    // cccccc
    //themeColors_[1][0].foreground = QColor("#000000");    // 333333

    //themeColors_[1][1].background = QColor("#ff8833");    // 88ff88
    //themeColors_[1][1].foreground = QColor("#000000");    // 224422

    //themeColors_[1][2].background = QColor("#ffff7a");    // ffffff
    //themeColors_[1][2].foreground = QColor("#000000");    // 2a2a2a

    //themeColors_[1][3].background = QColor("#7aff7a");    // aa5500
    //themeColors_[1][3].foreground = QColor("#000000");    // 554422

    //themeColors_[1][4].background = QColor("#000000");    // ffdd88
    //themeColors_[1][4].foreground = QColor("#ffffff");    // 552222

    //themeColors_[1][5].background = QColor("#ffffff");    // ffaaaa
    //themeColors_[1][5].foreground = QColor("#000000");    // 666666
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //infoFormat.setBackground(QColor("#7aff7a"));        // Qt::green        7aff7a
    //infoFormat.setForeground(QColor("#000000"));
    //warningFormat.setBackground(QColor("#ffff7a"));     // Qt::yellow       ffff7a
    //warningFormat.setForeground(QColor("#000000"));
    //errorFormat.setBackground(QColor("#ff8833"));       // Qt::orange       ff8833
    //errorFormat.setForeground(QColor("#000000"));
    //cerrorFormat.setBackground(QColor("#ff7a7a"));      // Qt::red          ff7a7a
    //cerrorFormat.setForeground(QColor("#000000"));
    //debugFormat.setBackground(QColor("#9a9a9a"));       // Qt::grey         9a9a9a
    //debugFormat.setForeground(QColor("#000000"));
    
    
}




//void LogViewer::abonentLogUpdated(const QString& msg) {
//    
//}





// ======================== UV ========================
void LogViewer::resetLogViewer() {
    curLogLineIndex_ = 0;
    curLogLine_ = 0;
    plainTextEdit_->clear();
    if (cursor_ != nullptr) {
        delete cursor_;
    }
    cursor_ = new QTextCursor(plainTextEdit_->textCursor());
}
// ======================== UV ========================





// ======================== UV ========================
// TODO: Переопределяю для сворачивания при клике по крестику и Alt+F4, но вообще-то это надо выносить в класс-обёртку.
void LogViewer::closeEvent(QCloseEvent* event) {
    
    // NOTE: event->spontaneous() как в итоге работает?
    
    if (!canClose) {
        qDebug().noquote() << "LogViewer::closeEvent: hiding" << windowTitle();
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("LogViewer::closeEvent: hiding \"%1\"").arg(windowTitle()));
        this->hide();
        event->ignore();
    }
    else {
        qDebug().noquote() << "LogViewer::closeEvent: closing" << windowTitle();
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("LogViewer::closeEvent: closing \"%1\"").arg(windowTitle()));
        event->accept();
    }    
}
// ======================== UV ========================



// ======================== UV ========================
/**
 * \brief Деструктор класса для отображения строк лога из класса логера.
 * \return Деструктор не возвращает ничего.
 *
 * \n
 */
LogViewer::~LogViewer() {
    qDebug().noquote() << "LogViewer::~LogViewer:" << windowTitle();
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("LogViewer::~LogViewer: %1").arg(windowTitle()));
}
// ======================== UV ========================


// ======================== UV ========================
/// UV: Сеттер палетки
void LogViewer::setSomeParams() {
    // UV: ЦВЕТА
    QPalette pal = palette();
    pal.setColor(QPalette::Window, "#333333");
    setAutoFillBackground(true);
    setPalette(pal);
    
    //plainTextEdit_->setStyleSheet(Globals::logPlainTextEditStyleSheet_);
    this->setStyleSheet(Globals::logViewerStyleSheet_);
    //plainTextEdit_->setStyleSheet(GlobalData::instance().getLogPlainTextEditStyleSheet_());
                
    //plainTextEdit_->setStyleSheet(
    //    "QPlainTextEdit { background-color: #333333; }"
    //    "QPlainTextEdit { font-family: 'Arial'; font-size: 18px; font-weight: bold; }"
    //);
}
// ======================== UV ========================































/**
 * \brief Конструктор класса для отображения строк лога из класса логера.
 * \param[in] loger указатель на логер.
 * \param[in] parent указатель на родителя.
 * \return Конструктор не возвращает ничего.
 *
 * \n
 */
LogViewer::LogViewer(Loger *loger, QWidget *parent)
    : QWidget{parent},
      loger_{loger}
{

    //this->resize(800, 600);
    this->resize(400, 300);
    this->setAttribute(Qt::WA_DeleteOnClose);

    //if (loger_ == 0){
    //    loger_ = LogerGlobal::instance();
    //}


    /// Поле для отображеня логов.
    plainTextEdit_ = new QPlainTextEdit(this);
    plainTextEdit_->setReadOnly(true);
    //plainTextEdit_->setMaximumBlockCount(1024);
    // UV: Закомментировал для глобальных шрифтов.
    //plainTextEdit_->setFont(QFont("Arial", 12));

    initDefaultColors();
    currentTheme_ = LVT_DARK;

    autoScrollEnabled_ = true;

    // Кнопка управления уровнем логирования.
    levelButton_ = new QToolButton(this);
    levelButton_->setPopupMode(QToolButton::InstantPopup);
    levelButton_->setCursor(Qt::ArrowCursor);

    Loger::LogerLevels currentLevel = loger_->getCurLogerLevel();
    updateLevelButtonStyle();

    levelMenu_ = new QMenu(this);
    levelActionGroup_ = new QActionGroup(this);

    QList<Loger::LogerLevels> levels = {Loger::LL_CERROR,
                                        Loger::LL_ERROR,
                                        Loger::LL_WARNING,
                                        Loger::LL_INFO,
                                        Loger::LL_DEBUG,
                                        Loger::LL_TRACE};



    for(Loger::LogerLevels level: levels){
        QString levelName = levelToString(level);
        QAction *action = levelMenu_->addAction(levelName);
        action->setCheckable(true);
        action->setActionGroup(levelActionGroup_);

        action->setData(QVariant::fromValue(static_cast<int>(level)));


        if (level == currentLevel){
            action->setChecked(true);
        }


        connect(action, &QAction::triggered, this, [this, level](){
            loger_->setCurLogerLevel(level);

            //updateLevelButtonStyle(level);

        });
    }

    levelButton_->setMenu(levelMenu_);

    // Кнопка меню фильтрации логов по их уровню логирования.
    filterButton_ = new QToolButton(this);
    filterButton_->setPopupMode(QToolButton::InstantPopup);
    filterButton_->setCursor(Qt::ArrowCursor);

    filterMenu_ = new QMenu(this);
    QWidget *levelsWidget = new QWidget(filterMenu_);
    QVBoxLayout *levelsLayout = new QVBoxLayout(levelsWidget);
    levelsLayout->setContentsMargins(5, 5, 5, 5);

    tempFilterLevels_ = enabledFilterLevels_;

    QVector<QCheckBox*> checkBoxes;


    for(Loger::LogerLevels level: levels){
        QString name = levelToString(level);
        QCheckBox *checkBox = new QCheckBox(name, levelsWidget);
        checkBox->setChecked(tempFilterLevels_.contains(level));
        levelsLayout->addWidget(checkBox);
        checkBoxes.append(checkBox);

        connect(checkBox, &QCheckBox::toggled, this, [this, level](bool checked){
            if(checked){
                tempFilterLevels_.insert(level);
            } else{
                tempFilterLevels_.remove(level);
            }

                });
    }

    filterMenu_->addSeparator();
    QPushButton *applyButton = new QPushButton("Применить", levelsWidget);
    levelsLayout->addWidget(applyButton);

    QWidgetAction *widgetAction = new QWidgetAction(filterMenu_);
    widgetAction->setDefaultWidget(levelsWidget);
    filterMenu_->addAction(widgetAction);


    connect(applyButton, &QPushButton::clicked, this, [this](){
        enabledFilterLevels_ = tempFilterLevels_;
        updateFilterDisplay();
        rebuildLogDispaly();
        filterMenu_->close();
    });

    connect(filterMenu_, &QMenu::aboutToHide, this, [this, widgetAction](){
    if(filterMenu_->activeAction() != widgetAction){
        tempFilterLevels_ = enabledFilterLevels_;
    }
    });

    filterButton_->setMenu(filterMenu_);
    updateFilterDisplay();

    // Текстовое поле для фильтрации логов по их содержимому.
    textFilterCheckBox_ = new QCheckBox("", this);
    textFilterCheckBox_->setChecked(false);

    textFilterLineEdit_ = new QLineEdit(this);
    textFilterLineEdit_->setPlaceholderText("Фильтр...");

    QAction *clearAct = textFilterLineEdit_->addAction(
                QIcon(":/images/icons/Clear"), QLineEdit::TrailingPosition
                );
    connect(clearAct, &QAction::triggered, textFilterLineEdit_, &QLineEdit::clear);

    connect(textFilterCheckBox_, &QCheckBox::toggled, this, [this](bool on){
        textFilterEnable_ = on;
        rebuildLogDispaly();
    });

    connect(textFilterLineEdit_, &QLineEdit::textChanged, this, [this](const QString  &texFil){
        textFilterValue_ = texFil;

        if(textFilterEnable_) {
            rebuildLogDispaly();
        }
    });

    connect(clearAct, &QAction::triggered, textFilterLineEdit_, &QLineEdit::clear);

    QHBoxLayout *levelLayout = new QHBoxLayout();
    levelLayout->addWidget(levelButton_);
    levelLayout->addWidget(filterButton_);
    levelLayout->addStretch();

    QHBoxLayout *textLayout = new QHBoxLayout();
    textLayout->addWidget(textFilterCheckBox_);
    textLayout->addWidget(textFilterLineEdit_, 1);

    cursor_ = new QTextCursor(plainTextEdit_->textCursor());
    
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(plainTextEdit_);
    layout->addLayout(levelLayout);
    layout->addLayout(textLayout);

    connect(plainTextEdit_->verticalScrollBar(), &QScrollBar::valueChanged, this, &LogViewer::onScrollBarMoved);

    this->setLayout(layout);
    logListShort_ = loger_->getLogList();
    addCurrentLogLines();

    connect(loger_, &Loger::newLineInserted, this, &LogViewer::insertNewLine, Qt::QueuedConnection);
    connect(loger_, &Loger::lastLineUpdated, this, &LogViewer::updateLastLine, Qt::QueuedConnection);
    connect(loger_, &Loger::logerLevelChanged, this, &LogViewer::updateLevelButtonStyle, Qt::QueuedConnection);
    
    
    
    flushTimer_ = new QTimer(this);
    flushTimer_->setInterval(30);
    flushTimer_->setSingleShot(false);
    
    pendingLinesCount_ = 0;
    
    connect(flushTimer_, &QTimer::timeout, this, &LogViewer::flushPendingLines);
    flushTimer_->start();
    
    //connect(flushTimer_, SIGNAL(timeout()), this, SLOT(flushPendingLines));
    //flushTimer_->start(100);
    
    
    

    
    
    
    
    
    //// UV: ЦВЕТА
    //
    //QPalette pal = palette();
    //pal.setColor(QPalette::Window, "#333333");
    //setAutoFillBackground(true);
    //setPalette(pal);
    //
    //plainTextEdit_->setStyleSheet("QPlainTextEdit { background-color: #333333; }");
    setSomeParams();

}












/**
 * \brief Сеттер цветовой темы логера.
 * \param[in] LogViewerTheme theme. Передаётся название темы, которую мы хотим выставить.
 * \return Возвращает текущую тему окна логирования.
 *
 * \n
 */

void LogViewer::setTheme(LogViewerTheme theme){
    if (currentTheme_ != theme){
        currentTheme_ = theme;
        updateLevelButtonStyle();
        rebuildLogDispaly();
    }
}


/**
 * \brief Геттер цветовой темы отображения логов, которая сейчас установлена.
 * \param[in] Имя параметра. Описание входного параметра функции.
 * \return Описание возвращаемого значения.
 *
 * \n
 */
LogViewer::LogViewerTheme LogViewer::getTheme() const {
    return currentTheme_;
}


/**
 * \brief Сеттер стиля и размера шрифта для сообщений лога.
 * \param[in] font. Шрифт текста для сообщений лога.
 * \return void.
 *
 * \n
 */
void LogViewer::setLogFont(const QFont &font){
    plainTextEdit_->setFont(font);
    rebuildLogDispaly();
}


/**
 * \brief Геттер шрифта текста сообщений лога.
 * \return font. Возвращает шрифт текста сообщений лога.
 *
 * \n
 */
QFont LogViewer::getLogFont() const {
    QFont font = plainTextEdit_->font();
    return font;
}

/**
 * \brief Сеттер максимального количества сообщений в окне лога.
 * \param[in] size. Передаётся число максимального количества сообщений в окне лога.
 * \return void.
 *
 * \n
 */
void LogViewer::setMaxMessage(int size){
//    loger_->setMaxLogListSize(size);
    plainTextEdit_->setMaximumBlockCount(size);
    rebuildLogDispaly();
}

/**
 * \brief Геттер максимального количества сообщений в окне лога.
 * \return size. Возвращает число максимального количества сообщений в окне лога.
 *
 * \n
 */
int LogViewer::getMaxMessage() const {
    int size = loger_->getMaxLogListSize();
    return size;
}

/**
 * \brief Сеттер уровня логирования, который будет установлен для логреа по умолчанию.
 * \param[in] levelIndex. Индекс по которому определяется уровень логирования по умолчанию.
 * \return void.
 *
 * \n
 */
void LogViewer::setDefaultLevel(int levelIndex){
    QList<Loger::LogerLevels> levels = {Loger::LL_CERROR,
                                        Loger::LL_ERROR,
                                        Loger::LL_WARNING,
                                        Loger::LL_INFO,
                                        Loger::LL_DEBUG,
                                        Loger::LL_TRACE};

    loger_->setCurLogerLevel(levels[levelIndex]);
}

/**
 * \brief Сеттер цветового оформления конкретного уровня логирования, для указанной темы.
 * \param[in] theme. Тема, для которой надо установить значение цвета.
 * \param[in] level. Уровень логирования, для которого надо установить значение цвета.
 * \param[in] background. Цвет заливки текста лога.
 * \param[in] foreground. Цвет текста лога.
 * \return void.
 *
 * \n
 */
void LogViewer::setLevelColor(LogViewerTheme theme, Loger::LogerLevels level,
                              const QColor background, const QColor foreground){

    int themeIndex = (theme == LVT_LIGHT) ? 0:1;
    int levelIndex = static_cast<int>(level);

    if (themeIndex >= 0 && themeIndex < 2 && levelIndex >= 0 && levelIndex < 6){
        themeColors_[themeIndex][levelIndex].background = background;
        themeColors_[themeIndex][levelIndex].foreground = foreground;
        if (theme == currentTheme_){
            rebuildLogDispaly();
        }
    }
}

/**
 * \brief Геттер цвета заливки текста для указанного уровня логирования.
 * \param[in] level. Уровень логирования.
 * \return Цвет заливки текста для указанного уровня логирования.
 *
 * \n
 */
QColor LogViewer::getLevelBgColor(Loger::LogerLevels level) const {
    int levelIndex = static_cast<int>(level);
    if(levelIndex >= 0 && levelIndex < 6) {
        return themeColors_[currentTheme_][levelIndex].background;
    }
    return QColor();
}


/**
 * \brief Геттер цвета заливки текста для указанного уровня логирования.
 * \param[in] level. Уровень логирования.
 * \return Цвет текста для указанного уровня логирования.
 *
 * \n
 */
QColor LogViewer::getLevelTextColor(Loger::LogerLevels level) const {
    int levelIndex = static_cast<int>(level);
    if(levelIndex >= 0 && levelIndex < 6){
        return themeColors_[currentTheme_][levelIndex].foreground;
    }
    return QColor();
}

/**
 * \brief Функции для перевода уровня логирования в строку и обратно.
 * \param[in] level. Уровень логирования в виде оного из значений из enum класса Loger.
 * \return Уровень логирования в виде строки.
 *
 * \n
 */
QString LogViewer::levelToString(Loger::LogerLevels level) const {
    switch(level){
        case Loger::LL_CERROR:  return "CERROR";
        case Loger::LL_ERROR:   return "ERROR";
        case Loger::LL_WARNING: return "WARNING";
        case Loger::LL_INFO:    return "INFO";
        case Loger::LL_TRACE:   return "TRACE";
        case Loger::LL_DEBUG:   return "DEBUG";
        default:         return "UNKNOWN";
    }
}

/**
 * \brief Краткое описание функции.
 * \param[in] levelStr. Уровень логирования в виде строки.
 * \return Уровень логирования в виде оного из значений из enum класса Loger.
 *
 * \n
 */
Loger::LogerLevels LogViewer::stringToLevel(const QString &levelStr) const {

        if (levelStr == "CERROR")    return Loger::LL_CERROR;
        if (levelStr ==  "ERROR")    return Loger::LL_ERROR;
        if (levelStr ==  "WARNING")  return Loger::LL_WARNING;
        if (levelStr ==  "INFO")     return Loger::LL_INFO;
        if (levelStr ==  "TRACE")    return Loger::LL_TRACE;
        if (levelStr ==  "DEBUG")     return Loger::LL_DEBUG;
        return Loger::LL_WARNING;

}


/**
 * \brief Функция фильтр, которая пропускает логи с указаным уровнем логирования и текстовым содержимым на отрисовку в окне логирования.
 * \param[in] logLevel. Уровень логирования который мы хотим показать.
 * \param[in] lineText. Текст, который должен содержаться в логе, для того, чтобы быть показаным в списке логов.
 * \return Возвращает bool, который показывает потходит ли лог под заданные параметры.
 *
 * \n
 */
bool LogViewer::showLog(Loger::LogerLevels logLevel, const QString &lineText) const{

    if (!enabledFilterLevels_.contains(logLevel)){
        return false;
    }

    if (textFilterEnable_ && !textFilterValue_.isEmpty()){

        if (!lineText.contains(textFilterValue_, Qt::CaseInsensitive)) {
            return false;
        }
    }
    return true;
}

/**
 * \brief Геттер для того чтобы получить формат отображения текста лога в зависимости от его уровня.
 * \param[in] level. Уровень логирования, для которого хотим получить формат отображеня текста.
 * \return Формат отображения текста для лога.
 *
 * \n
 */
QTextCharFormat LogViewer::getFormatForLevel(Loger::LogerLevels level) const {
    QTextCharFormat format;

    int levelIndex = static_cast<int>(level);
    const LogLevelColors& colors = themeColors_[currentTheme_][levelIndex];
    format.setBackground(colors.background);
    format.setForeground(colors.foreground);

    return format;
}

/**
 * \brief Функция которая сбрасывает цвета оформления к цветам по умолчанию.
 * \param[in] void.
 * \return void.
 *
 * \n
 */
void LogViewer::resetToDefaultColors() {
    initDefaultColors();
    rebuildLogDispaly();
}

/**
 * \brief Функция которая обновляет оформление кнопки выбора уровня логирования в зависимости от выбранного уровня.
 * \param[in] level. Уровень логирования, в зависимости от которого будут выбраны цвета оформления для кнопки.
 * \return void.
 *
 * \n
 */
void LogViewer::updateLevelButtonStyle() {
    Loger::LogerLevels level = loger_->getCurLogerLevel();
    QString colorBg = getLevelBgColor(level).name();
    QString colorText = getLevelTextColor(level).name();
    QString levelText = levelToString(level);

    levelButton_->setText(levelText);

    //qDebug().noquote() << levelButton_->styleSheet();
    // LogerGlobal::instance().addGlobalMessageToLog(Loger::LL_TRACE, QString(levelButton_->styleSheet()));
    //levelButton_->setStyleSheet(QString("background-color:" + colorBg + ";"));
    //levelButton_->setStyleSheet(QString("color:" + colorText + ";"));
    levelButton_->setStyleSheet(QString("QToolButton { background-color:" + colorBg + ";" + "color:" + colorText + "; }"));
    //qDebug().noquote() << levelButton_->styleSheet();
    // LogerGlobal::instance().addGlobalMessageToLog(Loger::LL_TRACE, QString(levelButton_->styleSheet()));

}

/**
 * \brief Функция которая обновляет текст кнопки для вызова меню фильтрации логов по их уровню логироания.
 * \param[in] void.
 * \return void.
 *
 * \n
 */

// TODO: Переделать это.
//       Другие тоже пересмотреть.
void LogViewer::updateFilterDisplay(){
     if (enabledFilterLevels_.isEmpty()){
         filterButton_->setText("Фильтр:....");
         filterButton_->setToolTip("Ничего не выбрано");
         return;
     }

     QList<Loger::LogerLevels> order = {Loger::LL_CERROR,
                                         Loger::LL_ERROR,
                                         Loger::LL_WARNING,
                                         Loger::LL_INFO,
                                         Loger::LL_DEBUG,
                                         Loger::LL_TRACE};
     QString parts;
     for(auto lvl : order) {
         if(enabledFilterLevels_.contains(lvl)){
             parts.append(levelToString(lvl).at(0));
             parts.append(',');
         }
     }

     QString text = parts;
     filterButton_->setText("Фильтр:" + text);
     filterButton_->setToolTip("Показываются:" + text);

}

/**
 * \brief Функция для перестраивания всего списка логов.
 * \param[in] void.
 * \return void.
 *
 * \n
 * Подробное описание функции.
 */
void LogViewer::rebuildLogDispaly(){
    plainTextEdit_->clear();
//    *cursor_ = plainTextEdit_->textCursor();

    curLogLineIndex_ = 0;
    curLogLine_ = 0;

    addCurrentLogLines();
}






/**
 * \brief Метод добавления всех текущих строк из логера в виджет.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void LogViewer::addCurrentLogLines() {   
    for (int i = 0; i < logListShort_->length(); ++i) {

        auto elem = logListShort_->at(i);

        if(!showLog(elem.getLogerLevel(), elem.getLine())) continue;

        cursor_->insertBlock();
        cursor_->insertText(elem.getLine(), getFormatForLevel(elem.getLogerLevel()));
        
        if (elem.getMsgErrorFlag()) {
            cursor_->insertText(incorrectSignString_, incorrectSignFormat_);
        }
        ensureScrollToBottomIfNeeded();
    }
    
}



/**
 * \brief Слот обновления счётчика строк, добавленных в логер.
 * \return Слот не возвращает ничего.
 *
 * \n
 */
void LogViewer::insertNewLine() {
    if(logListShort_ == nullptr || logListShort_->isEmpty()){
        return;
    }

    const auto &last = logListShort_->last();
    if(!showLog(last.getLogerLevel(), last.getLine())){
        return;
    }
//    ++bufferCount_;
//    if (bufferCount_ == 50) {
//        int b = 50; //loger_->getLogMaxMessage() > logListShort_->size() ? 200 : loger_->getLogMaxMessage();
//        bufferCount_ = 0;
//        int size = logListShort_->size();
//        for (int i = 0; i < b; ++i) {
//            cursor_->insertBlock();
//            //QString str = new QString;
//            cursor_->insertText(logListShort_->at(size-b+i).getLine(), getFormatForLevel(logListShort_->at(size-b+i).getLogerLevel()));
//        }
//    }
//    cursor_->insertBlock();
//    cursor_->insertText(logListShort_->last().getLine(), getFormatForLevel(logListShort_->last().getLogerLevel()));
//    curLogLineIndex_ = logListShort_->last().getLine().length();


//    cursor_->insertBlock();
//    
//    //qDebug() << logListShort_->size();
//    //QString str = logListShort_->last().getLine();
//    //QTextCharFormat tcf = getFormatForLevel(logListShort_->last().getLogerLevel());
//    //cursor_->insertText(str, tcf);
//    cursor_->insertText(logListShort_->last().getLine(), getFormatForLevel(logListShort_->last().getLogerLevel()));
    


//    ensureScrollToBottomIfNeeded();
    ++pendingLinesCount_;
}



/**
 * \brief Слот вставки новых строк в виджет.
 * \return Слот не возвращает ничего.
 *
 * \n
 */

void LogViewer::flushPendingLines(){
    if (pendingLinesCount_ <= 0){
        return;
    }

    if(logListShort_ == nullptr || logListShort_->isEmpty()){
        pendingLinesCount_ = 0;
        return;
    }
    const int maxBatch = 200;
    const int toAppend = qMin(pendingLinesCount_, maxBatch);
    const int size = logListShort_->size();

    if (size <= 0){
        pendingLinesCount_ = 0;
        return;
    }
    int inserted = 0;
    int startIndex = qMax(0, size - pendingLinesCount_);
    plainTextEdit_->setUpdatesEnabled(false);
    cursor_->beginEditBlock();

    for(int i = startIndex; i < size && inserted < toAppend; ++i) {
        const auto &line = logListShort_->at(i);
        if(!showLog(line.getLogerLevel(), line.getLine())){
            continue;
        }
        cursor_->insertBlock();
        cursor_->insertText(line.getLine(), getFormatForLevel(line.getLogerLevel()));
        // TODO: UV --- Только здесь и в addCurrentLogLines проверять errorFlag и добавлять знак некорректности сообщения?
        if (line.getMsgErrorFlag()) {
            cursor_->insertText(incorrectSignString_, incorrectSignFormat_);
        }
        ++inserted;
    }
    cursor_->endEditBlock();
    plainTextEdit_->setUpdatesEnabled(true);
    curLogLineIndex_ = logListShort_->last().getLine().length();
    pendingLinesCount_ -= inserted;

    ensureScrollToBottomIfNeeded();
}



/**
 * \brief Слот для обновления последней строки в виджете (расширения или указания ошибочного завершения).
 * \return Слот не возвращает ничего.
 *
 * \n
 */
void LogViewer::updateLastLine() {

    const auto &last = logListShort_->last();

    if (!showLog(last.getLogerLevel(), last.getLine())) return;

    if (logListShort_->last().getMsgErrorFlag()) {
        cursor_->insertText(incorrectSignString_, incorrectSignFormat_);
    } else {
       cursor_->insertText(logListShort_->last().getLine().mid(curLogLineIndex_), getFormatForLevel(logListShort_->last().getLogerLevel()));
       curLogLineIndex_ = logListShort_->last().getLine().length();
    }
     ensureScrollToBottomIfNeeded();

}


/**
 * \brief Слот для проверки положения скролбара после его движения, в зависимости от положения выставляется флаг автоскролла.
 * \return Слот не возвращает ничего.
 *
 * \n
 */

void LogViewer::onScrollBarMoved(int value){
    QScrollBar *scrollBar = plainTextEdit_->verticalScrollBar();
    if (value >= scrollBar -> maximum() - 5){
        autoScrollEnabled_ = true;
    } else {
        autoScrollEnabled_ = false;
    }
}


/**
 * \brief Слот для проверки флага автоскролла, в зависимости от его значение автоскролл происходит либо не происходит.
 * \return Слот не возвращает ничего.
 *
 * \n
 */

void LogViewer::ensureScrollToBottomIfNeeded(){
    if (autoScrollEnabled_){
        QTextCursor cursor = plainTextEdit_-> textCursor();
        cursor.movePosition(QTextCursor::End);
        plainTextEdit_->setTextCursor(cursor);
        plainTextEdit_->ensureCursorVisible();
    }
}








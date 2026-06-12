#ifndef LOGVIEWER_H
#define LOGVIEWER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QStackedWidget>
#include <QTabBar>
#include <QScrollBar>
#include <QLabel>
#include <QToolButton>
#include <QMenu>
#include <QActionGroup>
#include <QCheckBox>
#include <QLineEdit>
#include <QWidgetAction>
#include <QTimer>

#include "Loger.h"
//#include "GlobalData.h"
#include "Globals.h"




/**
 * \brief Класс для отображения строк лога из класса логера.
 *
 */
class LogViewer : public QWidget
{   
    Q_OBJECT
    
public:

    
    
    // Попытка сделать нормальный показ глобального вьюера.
    
    //void showEvent(QShowEvent* event) {
    //    QWidget::showEvent(event);
    //    if (!lastPoint_.isNull()) {
    //        move(lastPoint_);
    //    }
    //}
    //void moveEvent(QMoveEvent* event) {
    //    if (isVisible() && !(windowState() && Qt::WindowMinimized)) {
    //        lastPoint_ = pos();
    //    }
    //    QWidget::moveEvent(event);
    //}
    //
    //QPoint lastPoint_;
    
    
    
    
    
    
    
    
    /**
     * \brief Перечисление для тем оформления окна логирования.
     *
     * \n
     */
    enum LogViewerTheme {
        LVT_LIGHT,
        LVT_DARK
    };
    
    //// Конструтор, создающий виджет, получающий строки из глобального логера.
    //LogViewer(QWidget *parent):LogViewer(LogerGlobal::instance(), parent){}
    // Конструтор, создающий виджет, получающий строки из локального логера loger.
    LogViewer(Loger *loger, QWidget *parent = nullptr);
    
    /// Сеттер текущей темы окна логирования.
    void setTheme(LogViewerTheme theme);
    /// Геттер текущей темы окна логирования.
    LogViewerTheme getTheme() const;
    /// Сеттер текущего шрифта лога.
    void setLogFont(const QFont &font);
    /// Геттер текущего шрифта лога.
    QFont getLogFont() const;
    /// Сеттер максимального количества сообщений в окне лога.
    void setMaxMessage(int size);
    /// Геттер максимального количества сообщений в окне лога.
    int getMaxMessage() const;
    /// Сеттер уровня логирования, который будет установлен для логреа по умолчанию.
    void setDefaultLevel(int levelIndex);
    /// Сеттер цветового оформления лога для указанного уровня логирования.
    void setLevelColor(LogViewerTheme theme, Loger::LogerLevels level, const QColor background, const QColor foreground);
    /// Сеттер цвета заливки лога для указанного уровня логирования.
    QColor getLevelBgColor(Loger::LogerLevels level) const;
    /// Сеттер цвета текста лога для указанного уровня логирования.
    QColor getLevelTextColor(Loger::LogerLevels level) const;
    /// Метод для сброса цветов оформления логера к цветам по умолчанию.
    void resetToDefaultColors();
    
    
    
    /// UV: Сеттер цвета QPlainTextEdit
    void setTextEditColors(const QString& str) { plainTextEdit_->setStyleSheet(str); }
    /// UV: Сеттер палетки
    void setSomeParams();
    
    
    /// Функция для перевода уровня логирования в строку.
    QString levelToString(Loger::LogerLevels level) const;
    /// Функция для перевода строки в уровень логирования логера.
    Loger::LogerLevels stringToLevel(const QString &levelStr) const;

    QTextCharFormat  getLogFormat(Loger::LogerLevels level) const;

    /// Метод обновления стиля кнопки для смены текущего урованя логирования.
    void updateLevelButtonStyle();
    /// Функция фильтрации сообщений из логера по их уровню логирования и текстовому содержимому.
    bool showLog(Loger::LogerLevels logLevel, const QString &lineText) const;

    /// Метод для перестройки окна логирования.
    void rebuildLogDispaly();
    
    // Деструктор
    ~LogViewer();
    
    // Метод добавления всех текущих строк из логера в виджет.
    void addCurrentLogLines();
    
    
    
    // UV: 
    void resetLogViewer();
    
    /// UV: 
    void turnOnClosePossibility() { canClose = true; }
    
    /// UV:
    void setActive(bool mode) { activeMode = mode; }
    /// UV:
    bool isActive() { return activeMode; }
    
    
    
protected:
    
    // UV: 
    void closeEvent(QCloseEvent* event) override;
    
    
    
    
public slots:

    // Слот обновления счётчика строк.
    void insertNewLine();
    // Слот для добавления новых строк в виджет..
    void flushPendingLines();
    // Слот обновления последней строки в виджете.
    void updateLastLine();
    // Слот для проверки положения скролбара.
    void onScrollBarMoved(int value);
    // Слот для автоскролла вниз.
    void ensureScrollToBottomIfNeeded();

    // Слот обновления текста кнопки фильтра.
    void updateFilterDisplay();

    //void setIncorrectSign();
    
    //// UV: Слот обновления лога в экземпляре выполнения алгоритма.
    //void abonentLogUpdated(const QString& msg);
         
    
private:
    
    /// UV: 
    //QString abnName;
    /// UV:
    bool canClose{};
    ///// UV: Глобальный шрифт поля отображения логов
    //QString logPlainTextEditFont_;
    
    ///
    bool activeMode{};
    
    
    
    
    /// Указатель таймер.
    QTimer *flushTimer_;
    /// Счётчик строк на добавление.
    int pendingLinesCount_;
    
    /// Указатель на считываемый логер.
    Loger *loger_;
    
    /// Индексы последней считанной строчки и индекса, на котором на ней остановились при последнем считывании.
    int curLogLineIndex_{}, curLogLine_{};
    
    /// Константный указатель на список строк из логера.
    const QList<Loger::LogLine> *logListShort_;
    /// Контейнер для хранения цветов оформления текста логов.
    struct LogLevelColors {
        QColor background;
        QColor foreground;
    };

    /// Метод для инициализации цветов оформления логера по умолчанию.
    void initDefaultColors();
    /// Гетттер цветового оформления текста для указанного уровня логирования.
    QTextCharFormat getFormatForLevel(Loger::LogerLevels level) const;
    /// Матрица в которой хранятся цвета оформления логов для разных тем.
    QVector<QVector<LogLevelColors>> themeColors_;
    /// Текущая тема окна логирования.
    LogViewerTheme currentTheme_;
    /// Уровень логирования сообщений по умолчанию.
    Loger::LogerLevels logerDefaultLevel_;
     
    // Кнопки и графика

    /// Простой ТекстЭдит для отображения в виджете текста.
    QPlainTextEdit *plainTextEdit_;
    
    /// Курсор для внесения в ТекстЭдит текста вместе с цветовым фоном.
    QTextCursor *cursor_;

    /// Кнопка которая вызывает меню для выбора текущего уровня логирования логера.
    QToolButton *levelButton_;
    /// Меню выбора текущего уровня логирования.
    QMenu *levelMenu_;
    QActionGroup *levelActionGroup_;

    /// Кнопка которая вызывает меню для выбора уровней логирования сообщений, которые будут отображаться в списке логов.
    QToolButton *filterButton_;
    /// Меню для выбора уровней логирования сообщений, которые будут отображаться в списке логов.
    QMenu *filterMenu_;
    //QSet<Loger::LogerLevels> enabledFilterLevels_ = {Loger::LL_CERROR,
    //                                                 Loger::LL_ERROR,
    //                                                 Loger::LL_WARNING,
    //                                                 Loger::LL_INFO,
    //                                                 Loger::LL_DEBUG,
    //                                                 Loger::LL_TRACE};
    QSet<Loger::LogerLevels> enabledFilterLevels_ = []() {
        QSet<Loger::LogerLevels> set;
        set.insert(Loger::LL_CERROR);
        set.insert(Loger::LL_ERROR);
        set.insert(Loger::LL_WARNING);
        set.insert(Loger::LL_INFO);
        set.insert(Loger::LL_DEBUG);
        set.insert(Loger::LL_TRACE);
        return set;
    }();
    
    QSet<Loger::LogerLevels> tempFilterLevels_;

    /// Чекбокс отвечающий за работу текстового фильтра.
    QCheckBox *textFilterCheckBox_;
    /// Поле для ввода текста, по которому будут фильтроваться логи.
    QLineEdit *textFilterLineEdit_;
    /// Текст, по которому будут фильтроваться логи.
    QString textFilterValue_;
    /// Флаг работы тектового фильтра.
    bool textFilterEnable_;

    bool lastLineDisplayed_;


    QTextCursor *cursorShort_;

    /// Флаг необходимости автомотического скролла вниз.
    bool autoScrollEnabled_;

    // Статические

    /// Форматы вывода сообщений всех категорий в ТекстЭдит.
    static const QList<QTextCharFormat> formats_;
    
    /// Символ некорректного завершения сообщения.
    static const QString incorrectSignString_;
    
    /// Формат некорректного завершения сообщения.
    static const QTextCharFormat incorrectSignFormat_;
    
    
};

#endif // LOGVIEWER_H



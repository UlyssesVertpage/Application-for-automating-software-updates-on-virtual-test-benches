
#include "Globals.h"



namespace Globals {
    // Глобальный шрифт.
    QString widgetsFontGlobal = "QWidget { font-family: 'Arial'; font-size: 14px; font-weight: bold; }";
    // Глобальный шрифт для полей отображения логов.
    QString logPlainTextEditStyleSheet_ = "QPlainTextEdit { background-color: #333333; }"
                                          "QPlainTextEdit { font-family: 'Arial'; font-size: 18px; font-weight: bold; }";
    // Глобальный шрифт для логвьюера.
    QString logViewerStyleSheet_ = widgetsFontGlobal + logPlainTextEditStyleSheet_;
    
    
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- каркас.
    QString groupTableLogPushButtonStyleSheet_Base_ = "QPushButton {"
                                                      //"    border-style: ridge;"
                                                      "    border-radius: 5px;"
                                                      "    border-width: 1px;"
                                                      "    border-style: solid;"
                                                      "}"
                                                      ;
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- цвета покоя.
    QString groupTableLogPushButtonStyleSheet_Usual_ = "QPushButton:enabled {"
                                                       "    border-color: black;"
                                                       "    background-color: #eeeeee;"
                                                       "}"
                                                       "QPushButton:disabled {"
                                                       "    border-color: grey;"
                                                       "    background-color: #aaaaaa;"
                                                       "}"
                                                       "QPushButton:hover {"
                                                       "    background-color: #ffffff;"
                                                       "}"
                                                       "QPushButton:pressed {"
                                                       "    background-color: #dddddd;"
                                                       "}"
                                                       ;
    
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- цвета успешного завершения.
    QString groupTableLogPushButtonStyleSheet_Success_ = "QPushButton:enabled {"
                                                         "    border-color: black;"
                                                         "    background-color: #33cc33;"
                                                         "}"
                                                         "QPushButton:hover {"
                                                         "    background-color: #55ee55;"
                                                         "}"
                                                         "QPushButton:pressed {"
                                                         "    background-color: #00aa00;"
                                                         "}"
                                                         ;
    
    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- цвета при остановке.
    QString groupTableLogPushButtonStyleSheet_Stop_ = "QPushButton:enabled {"
                                                      "    border-color: black;"
                                                      "    background-color: #eeee33;"
                                                      "}"
                                                      "QPushButton:hover {"
                                                      "    background-color: #ffff77;"
                                                      "}"
                                                      "QPushButton:pressed {"
                                                      "    background-color: #dddd33;"
                                                      "}"
                                                      ;

    // Глобальный styleSheet для кнопок ЛОГОВ групповых таблиц главного окна --- цвета при ошибке.
    QString groupTableLogPushButtonStyleSheet_Error_ = "QPushButton:enabled {"
                                                       "    border-color: black;"
                                                       "    background-color: #dd4444;"
                                                       "}"
                                                       "QPushButton:hover {"
                                                       "    background-color: #ff6666;"
                                                       "}"
                                                       "QPushButton:pressed {"
                                                       "    background-color: #bb2222;"
                                                       "}"
                                                       ;    
    
    
    /// Глобальный styleSheet для прогресс-баров групповых таблиц главного окна
    QString groupTableProgressBarStyleSheet_ = "QProgressBar {"
                                               "    text-align: center;"
                                               "    border: 1px solid grey;"
                                               "    border-radius: 1px;"
                                               "    height: 20px;"
                                               //"    margin: 0.5px;"
                                               "}"
                                               "QProgressBar::chunk {"
                                               //"    background-color: #66cc66;"   // Светло-зелёный
                                               "    background-color: #77bbff;"     // Светло-голубой
                                               "}";
    
    // Для currentAlgorithmName_ в MainWindow
    QString emptyStr_ = "";
}




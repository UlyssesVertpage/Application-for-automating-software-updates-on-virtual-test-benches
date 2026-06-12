#ifndef GROUPTABLE_H
#define GROUPTABLE_H



#include <QWidget>
#include <QCheckBox>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QHeaderView>
#include <QPushButton>
#include <QProgressBar>
#include <QDebug>
#include <QMouseEvent>


#include "Globals.h"
#include "GlobalData.h"
#include "LogViewer.h"







///**
// * @brief ...
// * 
// * \n
// * 
// */
//class GroupTableChooseAbonentCheckBox : public QWidget {
//    Q_OBJECT
//public:
//    GroupTableChooseAbonentCheckBox(QWidget* parent = nullptr)
//        : QWidget{parent}
//    {}
//signals:
    
//protected:
//    void showEvent(QShowEvent *event) override {
//        qDebug().noquote() << "" << groupTableObjectName_;
//        LOG_MSG(groupTableObjectName_, Loger::LL_TRACE, QString("%1").arg(groupTableObjectName_));
//        event->accept();
//    }
//    void hideEvent(QHideEvent *event) override {
//        qDebug().noquote() << "" << groupTableObjectName_;
//        LOG_MSG(groupTableObjectName_, Loger::LL_TRACE, QString("%1").arg(groupTableObjectName_));
//        event->accept();
//    }
//private:
    
//};







/**
 * @brief ...
 * 
 * \n
 * 
 */
class GroupTableChooseAbonentBoxWidget : public QWidget {
    Q_OBJECT
public:
    GroupTableChooseAbonentBoxWidget(QCheckBox* chb, const QString groupTableObjectName, QWidget* parent = nullptr)
        : QWidget{parent}
        , chb_{chb}
        , groupTableObjectName_{groupTableObjectName}
    {} //chb_->setAttribute(Qt::WA_TransparentForMouseEvents);
signals:
    //void gtcabwClicked(bool isChecked);
    void gtcabwClicked();
protected:
    void mouseReleaseEvent(QMouseEvent *event) override {
        qDebug().noquote() << "GroupTableChooseAbonentBoxWidget::mouseReleaseEvent:" << groupTableObjectName_;
        LOG_MSG(groupTableObjectName_, Loger::LL_TRACE, QString("GroupTableChooseAbonentBoxWidget::mouseReleaseEvent: %1").arg(groupTableObjectName_));
        if (chb_->isVisible() && chb_->isEnabled()) {
            emit gtcabwClicked();
        }
        event->accept();
    }
private:
    QCheckBox* chb_;
    const QString groupTableObjectName_;
};


/**
 * @brief Класс метки для групповой таблицы
 * 
 */
class GroupTableLabelWidget : public QWidget {
    Q_OBJECT
public:
    GroupTableLabelWidget(const QString &text, QCheckBox* gtCheckBox, QWidget* parent = nullptr)
        : QWidget(parent)              // Это не делегирование конструктору нашего же класса,
        , text_{text}                  // это вызов конструктора базового (родительского) класса.
        , gtCheckBox_{gtCheckBox} {
        label_ = new QLabel(text, this);
        layout_ = new QHBoxLayout(this);
        layout_->addWidget(label_);
        layout_->addStretch();
    }
    const QString& getText() { return text_; }
signals:
    void clicked();
protected:
    void mouseReleaseEvent(QMouseEvent*) override {
    // void mouseReleaseEvent(QMouseEvent* event) override {
    // void mousePressEvent(QMouseEvent* event) override {
        if (gtCheckBox_->isEnabled()) {
            emit clicked();
        }
    }
private:
    const QString text_;
    QHBoxLayout* layout_;
    QCheckBox* gtCheckBox_;
    QLabel* label_;
};






class GroupTable : public QWidget
{
    
    Q_OBJECT
    
    
public:
    
    ~GroupTable();
    
    GroupTable(QString groupName, const QStringList& abonentsGroup, QWidget* parent = nullptr);
    
    // void fillTable(int columns, const GlobalData::AbonentsGroup abonentsGroup);
    
    QCheckBox* getGroupChooseChBox() { return checkBox_; }
    
    const QTableWidget* getTable() const { return tableWidget_; }
    
    const QList<QCheckBox*>& getChooseCheckBoxesList() const { return chooseCheckBoxesList_; }
    
    const QString getGroupName() const { return labelWidget_->getText(); }
    
    
    
public slots:
    
    // void setTableVisible(bool checked);
    void chooseAllAbonents(int index);
    
    
signals:
    
    ///
    void anyChooseAbonentChBoxToggled(const QString& abnName, bool mode);
    // void anyChooseAbonentChBoxToggled(const QString& abnName);
    ///
    void anyStopAlgExecBtnClicked(const QString& abnName);
    ///
    // void someAbonentChooseChBoxTurnedOff();
    ///
    // void someAbonentChooseChBoxTurnedOn();
    ///
    // void groupCheckBoxChanged(bool mode);
    
    
private:
    
    // ОБЩЕЕ
    
    //QHBoxLayout* layout_;
    QGridLayout* layout_;
    
    QCheckBox* checkBox_;
    
    QTableWidget* tableWidget_;

    GroupTableLabelWidget* labelWidget_;
    
    
    
    // СПИСКИ ВИДЖЕТОВ ВНУТРИ ТАБЛИЦЫ
    
    /// Список чекбоксов для выбора абонентов для запуска.
    QList<QCheckBox*> chooseCheckBoxesList_;
    /// Список имён абонентов.
    QStringList abnNamesList_;
    
    
    ///
    QMap<QString, AbonentLogStruct>& abonentsLogsMap_;
    
    
};

#endif // GROUPTABLE_H



#include "GroupTable.h"





GroupTable::~GroupTable() {
    //if (chooseCheckBoxesList_ != nullptr) {
    //    delete chooseCheckBoxesList_;
    //}
}


GroupTable::GroupTable(QString groupName, const QStringList& abonentsGroup, QWidget* parent)
    : QWidget{parent}
    , abnNamesList_{abonentsGroup}
    , abonentsLogsMap_(GlobalData::instance().getAbonentsLogsMap())
{

    setObjectName(QString("GroupTable_%1_inst").arg(groupName));
    LOG_REG_OBJNAME(objectName());
    LOG_ADD_OBJNAME(objectName());
    
    
    int rows = abonentsGroup.size();
    
    // Qt 5.7.1
    QMap<int, QString> tablesHorizontalHeaders = []() {
        QMap<int, QString> tc;
        tc.insert(0, "Выбор");
        tc.insert(1, "Название абонента");
        tc.insert(2, "Прогресс-бар");
        tc.insert(3, "Логи");
        tc.insert(4, "Стоп");
        return tc;
    }();
    
    QStringList headers = tablesHorizontalHeaders.values();
    
    int columns = headers.size();
    
    
    
    
    // ================= СОЗДАНИЕ КНОПОК И МЕТОК =================
    layout_ = new QGridLayout(this);
    
    // Чекбокс для сворачивания группы
    checkBox_ = new QCheckBox(this);
    checkBox_->setChecked(true);
    checkBox_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    // Метка с названием группы
    labelWidget_ = new GroupTableLabelWidget(groupName, checkBox_, this);
    //label_->setStyleSheet("QLabel { background-color : #00ff00; color : white; }");
    labelWidget_->setStyleSheet("QLabel { border : 1px solid black; }");
    
    
    // ================= СОЗДАНИЕ ТАБЛИЦЫ С ИНФОРМАЦИЕЙ ПО АБОНЕНТАМ =================
    // chooseCheckBoxesList_ = new QList<QCheckBox*>;
    
    tableWidget_ = new QTableWidget(rows, columns, this);      // Будем передавать размеры здесь или отдельным методом?
    tableWidget_->setHorizontalHeaderLabels(headers);
    tableWidget_->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidget_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget_->setObjectName(QString("GroupTable_%1_TableWidget_inst").arg(groupName));
    
    // TODO: Настройка редактирования конкретной ячейки.
    //QTableWidgetItem* item = tableWidget_->item(0, 1);
    ////item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    //item->setFlags(item->flags() | Qt::ItemIsEditable);
    
    
    QMap<QString, AbonentGroupsViewInfoMap>& abonentsViewInfoMap = GlobalData::instance().getAbonentsViewInfoMap();
    
    for (int i = 0; i < rows; ++i) {
        
        // 2 колонка - Названия абонентов
        QString abnName = abonentsGroup.at(i);
        QTableWidgetItem* twi = new QTableWidgetItem(abnName);
        tableWidget_->setItem(i, 1, twi);       // Индекс 1 - "Название абонента"
        
        
        // 1 колонка - Выбор
        //QWidget* w1 = new QWidget(tableWidget_);
        // TODO: Полностью перенести эти чекбоксы вовнутрь GroupTableChooseAbonentBoxWidget
        QCheckBox* chbx1 = new QCheckBox(tableWidget_);
        chbx1->setAttribute(Qt::WA_TransparentForMouseEvents);
        chooseCheckBoxesList_.append(chbx1);
        GroupTableChooseAbonentBoxWidget* w1 = new GroupTableChooseAbonentBoxWidget(chbx1, objectName(), tableWidget_);
        QHBoxLayout* hbl1 = new QHBoxLayout(w1);
        hbl1->setContentsMargins(0, 0, 0, 0);
        hbl1->setAlignment(Qt::AlignCenter);
        hbl1->addWidget(chbx1);
        tableWidget_->setCellWidget(i, 0, w1);
        connect(w1, &GroupTableChooseAbonentBoxWidget::gtcabwClicked, [this, abnName, chbx1]() {
        //connect(w1, &GroupTableChooseAbonentBoxWidget::gtcabwClicked, [this, abnName, chbx1](bool isChecked) {
            // NOTE: isVisible для проверки доступен абонент для применения текущего алгоритма.
            //       isEnabled для проверки не выполняется ли алгоритм прямо сейчас.
            //if (chbx1->isVisible() && chbx1->isEnabled()) {     
            emit anyChooseAbonentChBoxToggled(abnName, !chbx1->isChecked());
            //}
        });
        
        
        
        // TODO - добавить (функцию-)обнуление для прогресс-бара после каждого запуска алгоритма.
        
        // 3 колонка - Прогресс бар
        QWidget* w3 = new QWidget(tableWidget_);
        QHBoxLayout* hbl3 = new QHBoxLayout(w3);
        QProgressBar* pb3 = new QProgressBar(tableWidget_);
        pb3->setStyleSheet(Globals::groupTableProgressBarStyleSheet_);
        pb3->setFixedHeight(15);
        pb3->setOrientation(Qt::Horizontal);
        hbl3->addWidget(pb3);
        tableWidget_->setCellWidget(i, 2, w3);
        
        
        // 4 колонка - Логи
        QWidget* w4 = new QWidget(tableWidget_);
        QHBoxLayout* hbl4 = new QHBoxLayout(w4);
        //w4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        //QPushButton* phbtn4 = new QPushButton(QString::number(i), tableWidget_);
        QPushButton* phbtn4 = new QPushButton(tableWidget_);
        phbtn4->setStyleSheet(Globals::groupTableLogPushButtonStyleSheet_Base_);
        phbtn4->setStyleSheet(Globals::groupTableLogPushButtonStyleSheet_Usual_);
        phbtn4->setFixedWidth(25);
        phbtn4->setFixedHeight(25);
        //phbtn4->setMaximumWidth(30);
        //phbtn4->setMaximumHeight(30);
        hbl4->setContentsMargins(0, 0, 0, 0);
        //hbl4->setContentsMargins(0, 5, 0, 5);
        hbl4->setAlignment(Qt::AlignCenter);
        hbl4->addWidget(phbtn4);
        phbtn4->setEnabled(false);      //phbtn4->setDisabled(true);                                  // Отключаем "Логи" по умолчанию
        tableWidget_->setCellWidget(i, 3, w4);
        
        
        // 5 колонка - Стоп
        QWidget* w5 = new QWidget(tableWidget_);
        QHBoxLayout* hbl5 = new QHBoxLayout(w5);
        QPushButton* phbtn5 = new QPushButton("X", tableWidget_);
        phbtn5->setFixedWidth(25);
        phbtn5->setFixedHeight(25);
        //phbtn5->setMaximumWidth(30);
        hbl5->setContentsMargins(0, 0, 0, 0);
        hbl5->setAlignment(Qt::AlignCenter);
        hbl5->addWidget(phbtn5);
        phbtn5->setDisabled(true);                                  // Отключаем "Стоп" по умолчанию
        tableWidget_->setCellWidget(i, 4, w5);
        
        
        // Чтобы кнопки логов автоматически вкл/выкл, когда галочки выбора абонентов вкл/выкл.
        connect(chbx1, &QCheckBox::toggled, [this, abnName, chbx1, phbtn4](bool checked) {
            //emit anyChooseAbonentChBoxToggled(abnName, chbx1->isChecked());
            phbtn4->setEnabled(checked || abonentsLogsMap_[abnName].logViewer->isActive());
        });
        
        
        // Для AbonentGroupsViewInfoMap:
        AbonentGroupViewInfo agvi;
        agvi.tableRowIndex = i;
        agvi.chooseChBox = chbx1;
        agvi.successPrgBr = pb3;
        //agvi.successLbl = lbl3;
        agvi.logBtn = phbtn4;
        agvi.stopBtn = phbtn5;
        agvi.groupChBox = checkBox_;
        abonentsViewInfoMap[abnName][groupName] = agvi;
    }
    
    
    
    
    
    // =============== РАСТЯЖЕНИЯ ===============
    
    // tableWidget_->resizeColumnsToContents();
    // tableWidget_->resizeColumnToContents(1);
    for (int i = 0; i < tableWidget_->columnCount(); ++i) {
        if (i != 1) {                                                                                       // Не трогаем столбец с именами абонентов
            tableWidget_->resizeColumnToContents(i);
            tableWidget_->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeMode::Fixed);      // Отсутствие возможности растягивать столбцы
        }
    }
    tableWidget_->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    
    for (int i = 0; i < tableWidget_->rowCount(); ++i) {
        tableWidget_->verticalHeader()->setSectionResizeMode(i, QHeaderView::ResizeMode::Fixed);            // Отсутствие возможности растягивать строки
    }
    
    
    
    
    // =============== УСТАНОВКА ФИКСИРОВАННЫХ РАЗМЕРОВ ===============
    
    // ВЫСОТА
    
    //tableWidget_->resizeRowsToContents();
    
    int totalHeight = 0;
    for (int i = 0; i < tableWidget_->rowCount(); ++i) {
       totalHeight += tableWidget_->rowHeight(i);
    }
    totalHeight += tableWidget_->horizontalHeader()->height();
    tableWidget_->setFixedHeight(totalHeight + 4);              // На Windows хватает "+ 2"
    
    // ШИРИНА
    //int totalWidth = 0;
    //for (int i = 0; i < tableWidget_->columnCount(); ++i) {
    //    totalWidth += tableWidget_->columnWidth(i);
    //}
    //totalWidth += tableWidget_->verticalHeader()->width();
    //tableWidget_->setFixedWidth(totalWidth + 4);                // На Windows хватает "+ 2"
    
    
    
    
    tableWidget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    
    
    
    
    
    qDebug().noquote() << "GroupTable::GroupTable:" << groupName;
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GroupTable::GroupTable: %1").arg(groupName));
    
    // NOTE: Для тех, кто был вставлен через setCellWidget().
    //QWidget* widget = tableWidget_->cellWidget(0, 0);
    //widget->setEnabled(false);
    
    // NOTE: Для тех, кто был вставлен через setItem().
    //QTableWidgetItem* item = tableWidget_->item(0, 0);                // Ещё есть "itemAt", но он нужен для работы с ПИКСЕЛЯМИ (координатами относительно top-left-угла таблицы)
    //item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    
    
    
    
    // ================= ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ НА МАКЕТ + НАСТРОЙКА ПРУЖИН =================
    
    layout_->addWidget(checkBox_, 0, 0, Qt::AlignLeft);
    layout_->addWidget(labelWidget_, 0, 1); //, Qt::AlignLeft);
    // layout_->addWidget(tableWidget_, 1, 1, Qt::AlignLeft);
    layout_->addWidget(tableWidget_, 1, 1);
        
    // QSpacerItem* spacer = new QSpacerItem(10, 10);
    // layout_->addItem(spacer, 0, 1);
    
    
    
    
    // Настраиваем растяжение строк и столбцов
    // layout_->setRowStretch(0, 0);
    // layout_->setRowStretch(1, 0);
    // layout_->setColumnStretch(0, 0);
    
    layout_->setColumnStretch(1, 1);
    
    
    
    // Отступы --- на заметку!!!
    // layout_->setContentsMargins(0, 0, 0, 0);
    
    
    // connect(checkBox_, &QCheckBox::toggled, tableWidget_, &GroupTable::setVisible);
    connect(checkBox_, &QCheckBox::toggled, [this](bool checked) {
        tableWidget_->setVisible(checked);
        // emit groupCheckBoxChanged(checkBox_->isChecked());
    });
    
    //QTableWidgetItem headerItem = tableWidget_->horizontalHeaderItem(0);
    //headerItem.
    connect(tableWidget_->horizontalHeader(), &QHeaderView::sectionClicked, this, &GroupTable::chooseAllAbonents);
    
    connect(labelWidget_, &GroupTableLabelWidget::clicked, checkBox_, &QCheckBox::toggle);
    //connect(layout, &QGridLayout::)
}



void GroupTable::chooseAllAbonents(int index) {
    if (index == 0) {
        bool areAllOn{1};
        for (QCheckBox* chb: chooseCheckBoxesList_) {
            if (chb->isVisible() && chb->isEnabled()) {
                if (!chb->isChecked()) {
                    areAllOn = false;
                    break;
                }
            }
        }
        
        int size = abnNamesList_.size();
        for (int i = 0; i < size; ++i) {
            const QCheckBox* chb = chooseCheckBoxesList_.at(i);
            if (chb->isVisible() && chb->isEnabled()) {
                emit anyChooseAbonentChBoxToggled(abnNamesList_.at(i), !areAllOn);
            }
        }
    }
}




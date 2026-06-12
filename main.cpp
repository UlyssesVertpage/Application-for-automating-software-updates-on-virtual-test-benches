#include <QApplication>
#include <QDebug>

//extern "C" {
//    #include <lua.h>
//    #include <lualib.h>
//    #include <lauxlib.h>
//}
#include <lua.hpp> 

#include <QFile>
#include <QIODevice>
#include <QDir>

#include "MainWindow.h"


// TODO:

// 1. Для уровней логирования добавить новый - прогресс выполнения?

// 2. Везде где надо делать insert для данных, заменить на insert(std::move) (?), чтобы не копировать списки абонентов

// 3. Переименовать abonentsMap_ в abonentsConfigMap_ или типо того и другие мапы внутри GlobalData и MainWindow.




int main(int argc, char *argv[])
{
    
    QApplication a(argc, argv);
    
    MainWindow *w = new MainWindow;
        
    
    //w->show();
    //qDebug() << (w->geometry());
    
    return a.exec();
    
    //return 0;
}

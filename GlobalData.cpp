#include "GlobalData.h"







// TODO: Пробивал информацию по получению данных о классах в проекте (имена, типы и т.д.)
//       Сделать так, чтобы эта функция записывала имена в синглтон GlobalData.

void GlobalData::setClassesNames() {
    
    
    QDir dir;
    qDebug().noquote() << QString("GlobalData::setClassesNames: %1 --- %2").arg(dir.path()).arg(dir.absolutePath());
    LOG_MSG(objectName(), Loger::LL_DEBUG, QString("GlobalData::setClassesNames: %1 --- %2").arg(dir.path()).arg(dir.absolutePath()));
    
    //for () {
    //    classesNames_.append();
    //}
    
    
//    int typeCount = QMetaType::cou
            
    
}






GlobalData::GlobalData(QObject* parent)
    : QObject(parent)
{
    setObjectName("GlobalData_inst");
    //LOG_REG_OBJNAME(objectName())
    
}




/**
 * \brief Метод формат-го вывода в консоль текущего стека для переданного Lua-состояния.
 * \param[in] L текущее состояние Lua.
 * \return Метод не возвращает ничего.
 *
 * \n
 * В случаях, когда в стеке что-то есть (после считывания содержимого файла в буффер), оно
 * будет выведено в формате "Индекс, обратный индекс (отриц-й), тип данных, сами данные.
 */
void GlobalData::printLuaStack(lua_State* L) {
    int size = lua_gettop(L);
    qDebug().noquote() << "";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString(""));
    qDebug().noquote() << QString("=").repeated(10);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("=").repeated(10));
    for (int i = 1; i <= size; ++i) {
        //qDebug().noquote() << lua_type(L, i);
        lua_pushvalue(L, i);
        QString str = lua_tostring(L, -1);
        int type = lua_type(L, -1);
        lua_pop(L, 1);
        qDebug().noquote() << QString("%1 (%2), type: [%3], value: %4").arg(i).arg(-size-1+i).arg(type).arg(str);
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("%1 (%2), type: [%3], value: %4").arg(i).arg(-size-1+i).arg(type).arg(str));
        //qDebug().noquote() << i << "(" << -size-1+i << "): " << lua_tostring(L, i);
    }
    qDebug().noquote() << QString("=").repeated(10) << '\n';
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("=").repeated(10));
}




/**
 * \brief Метод формат-го вывода в консоль словаря всех абонентов.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void GlobalData::printAbonentsMap() {
    qDebug().noquote() << "";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString(""));
    qDebug().noquote() << QString("=").repeated(20) << "ABONENTS MAP" << QString("=").repeated(20);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("=").repeated(20) + " ABONENTS MAP " + QString("=").repeated(20));
    for (const QString& name : abonentsMap_.keys()) {
        AbonentInfo info = abonentsMap_.value(name);
        qDebug().noquote() << name << info.ip << info.port << info.user << info.ssh_path;
        // LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("%1 %2 %3 %4").arg(name).arg(info.ip).arg(info.user).arg(info.ssh_path));
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, name + " " + info.ip + " " + info.port + " " + info.user + " " + info.ssh_path);
    }
    qDebug().noquote() << QString("=").repeated(56);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("=").repeated(56));
}



/**
 * \brief Метод формат-го вывода в консоль словаря всех групп абонентов.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void GlobalData::printAbonentsGroupsMap() {
    qDebug().noquote() << "";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString(""));
    qDebug().noquote() << QString("=").repeated(20) << "ABONENTS GROUPS MAP" << QString("=").repeated(20);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("=").repeated(20) + " ABONENTS GROUPS MAP " + QString("=").repeated(20));
    for (const QString& name : abonentsGroupsMap_.keys()) {
        QStringList group = abonentsGroupsMap_.value(name);
        qDebug().noquote() << name;
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, name);
        for (QString& abn : group) {
            qDebug().noquote() << "    " << abn;
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("    %1").arg(abn));
        }
    }
    qDebug().noquote() << QString("=").repeated(63);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("=").repeated(63));
}



/**
 * \brief Метод формат-го вывода в консоль словаря всех алгоритмов.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void GlobalData::printAlgorithmsMap() {
    qDebug().noquote() << "";
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString(""));
    qDebug().noquote() << QString("=").repeated(20) << "ALGORITHMS MAP" << QString("=").repeated(20);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("=").repeated(20) + " ALGORITHMS MAP " + QString("=").repeated(20));
    for (const QString& name : algorithmsMap_.keys()) {
        AlgorithmInfo info = algorithmsMap_.value(name);
        qDebug().noquote() << name;
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, name);
        qDebug().noquote() << "    " << info.alg_path;
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "    " + info.alg_path);
        qDebug().noquote() << "    " << info.descr;
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "    " + info.descr);
        //for (QString& abn : info.execAbonents) {
        //    qDebug().noquote() << "    " << abn;
        //}
        qDebug().noquote() << "    " << info.execAbonents.join(", ");
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "    " + info.execAbonents.join(", "));
    }
    qDebug().noquote() << QString("=").repeated(58);
    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("=").repeated(58));
}






/**
 * \brief Метод чтения, обработки и хранения конфигурационных данных.
 * \return Метод возвращает bool как результат успешности чтения.
 *
 * \n
 */
bool GlobalData::loadConfigData() { 
    
    // ОТКРЫТИЕ ФАЙЛА И ПОЛУЧЕНИЕ ЕГО СОДЕРЖИМОГО ЧЕРЕЗ luaL_loadbuffer.
    
    lua_State* L = luaL_newstate();
    bool funcExecCheck = false;
    if (L == nullptr) {
        qDebug().noquote() << "GlobalData::loadConfigData: luaL_newstate() failed.";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData::loadConfigData: luaL_newstate() failed."));
    }
    else {
        qDebug().noquote() << "GlobalData::loadConfigData: luaL_newstate() succeeded.";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: luaL_newstate() succeeded."));
        luaL_openlibs(L);
        qDebug().noquote() << "GlobalData::loadConfigData: luaL_openlibs() succeeded.";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: luaL_openlibs() succeeded."));
        //printLuaStack(L);
        
        // TODO: путь указаывается относительно ".exe" файла (!!!)
        // QFile file("config-1.txt");
        //QFile file("../SysWizard/config-1.txt");
        // QFile file(":/resources/configs/config-data-2.txt");
        
        
        
        // NOTE: ОПЦИОНАЛЬНЫЙ ВЫВОД ВСЕХ РЕСУРСОВ И ДРУГИХ САБДИРОВ В КОНСОЛЬ.
        //QDirIterator it(":", QDirIterator::Subdirectories);
        //while (it.hasNext()) {
        //    qDebug().noquote() << it.next();
        //}
        
        
        
        // 1. Вариация считывания конфиг-файла из ресурсов.
        //QFile file(QString(":/configs/%1.txt").arg(CONFIG_DATA_FILE_PATH));
        // 1. Вариация считывания конфиг-файла из ресурсов.
        QFile file(CONFIG_DATA_FILE_PATH);
        
        
        //QFile file(QString(":/resources/configs/%1.txt").arg(CONFIG_DATA_FILE_PATH));
        //QFile file(QString(":/%1").arg(CONFIG_DATA_FILE_PATH));
        //QFile file(QString(":/resources/configs/resources/configs/%1.txt").arg(CONFIG_DATA_FILE_PATH));
        //QFile file(QString(":/resources/configs/resources/configs/config-data-3.txt"));
        //QFile file(QString("%1.txt").arg(CONFIG_DATA_FILE_PATH));
        
        //QFile file("../SysWizard/config-1.lua");
        //QFile file("../SysWizard/text2.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            if (file.exists()) {
                qDebug().noquote() << "GlobalData::loadConfigData: file.open() failed, cannot read it.";
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData::loadConfigData: file.open() failed, cannot read it."));
            } else {
                qDebug().noquote() << QString("GlobalData::loadConfigData: file doesn't exist at given directory (%1). Current path is %2").arg(file.fileName()).arg(QDir::currentPath());
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData::loadConfigData: file doesn't exist at given directory (%1). Current path is %2").arg(file.fileName()).arg(QDir::currentPath()));
            }
        }
        else {
            QByteArray data = file.readAll();
            int result = luaL_loadbuffer(L, data.data(), data.size(), "chunk");
            //QString text = QTextStream(&file).readAll();
            //lua_pushstring(L, text.toStdString().c_str());
            //printLuaStack(L);
            //// 1 - read file function
            //int result = luaL_loadbuffer(L, lua_tostring(L, (lua_gettop(L))), text.size(), "chunk");
            //printLuaStack(L);
            //qDebug().noquote() << text << text.size();
            //LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, text + "\n" + QString::number(text.size()));
            if (result != LUA_OK) {
                qDebug().noquote() << QString("GlobalData: %1 LUA_ERROR").arg(result);
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: %1 LUA_ERROR").arg(result));
            }
            else {
                if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
                    qDebug().noquote() << "GlobalData::loadConfigData: lua_pcall() failed.";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData::loadConfigData: lua_pcall() failed."));
                    qDebug().noquote() << QString("GlobalData: fail code: %1").arg(lua_tointeger(L, -1));
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: fail code: %1").arg(lua_tointeger(L, -1)));
                    qDebug().noquote() << QString("GlobalData: fail msg: %1").arg(lua_tostring(L, -1));
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: fail msg: %1").arg(lua_tostring(L, -1)));
                }
                else {
                    qDebug().noquote() << "GlobalData::loadConfigData: lua_pcall() succeeded.";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("GlobalData::loadConfigData: lua_pcall() succeeded."));
                    funcExecCheck = true;
                    printLuaStack(L);           // 1 - read file function
                    //lua_pop(L, 1);    // <-- было нужно при считывании конфиг-файла как текста, а не как ByteArray
                }
                //printLuaStack(L);
                //lua_pop(L, 1);
                //printLuaStack(L);
            }
        }
        
        file.close();        
    }
    
    
    
    
    
    
    // ОБРАБОТКА СОДЕРЖИМОГО ФАЙЛА ЧЕРЕЗ СТЕК LUA.
    
    
    // =======================================================================================
    if (funcExecCheck) {
        
        
        
        // ===========================
        // Try to get "Abonents" table
        // ===========================
        
        
        lua_getglobal(L, "Abonents");
        // 1 - table "Abonents"
        //printLuaStack(L);
        if (lua_isnoneornil(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: no \"Abonents\" table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData::loadConfigData: no \"Abonents\" table"));
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: \"Abonents\" is not a table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData::loadConfigData: \"Abonents\" is not a table"));
            return false;
        } else {
            // 1 - table
            // 2 - nil
            lua_pushnil(L);
            //printLuaStack(L);
            while (lua_next(L, -2) != 0) {
                // 1 - table
                // 2 - key (index)
                // 3 - value (abonent info table)
                //printLuaStack(L);
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: no inner abonent info table";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: no inner abonent info table");
                    lua_pop(L, 1);
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: element is not an inner abonent info table";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: element is not an inner abonent info table");
                    lua_pop(L, 1);
                    continue;
                } else {                    

                    AbonentInfo abonentInfo;    // = new AbonentInfo;                           
                    
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    
                    
                    
                    
                    // TODO: Добавить вспл. окно ошибки обработки имени абонента.
                    
                    
                    // Считываем имя абонента.
                    
                    lua_getfield(L, -1, "name");
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    // 4 - field (name string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << "GlobalData::loadConfigData: some abonent name among the keys is none or nil";
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData::loadConfigData: some abonent name among the keys is none or nil"));
                        lua_pop(L, 2);
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << "GlobalData::loadConfigData: some abonent name among the keys is not a string";
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData::loadConfigData: some abonent name among the keys is not a string"));
                        lua_pop(L, 2);
                        continue;
                    }
                    
                    
                    // Проверка на существование имени текущего абонента.
                    QString abonentName = lua_tostring(L, -1);
                    if (abonentsMap_.contains(abonentName)) {
                        qDebug().noquote() << QString("GlobalData: abonent with name '%1' already exists in 'Abonents' table").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: abonent with name '%1' already exists in 'Abonents' table").arg(abonentName));
                        lua_pop(L, 2);
                        continue;
                    }
                    
                    
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    
                    
                    
                    
                    
                    
                    
                    // Считываем IP абонента.
                    lua_getfield(L, -1, "ip");
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    // 4 - field (ip string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: ip field in '%1' abonent info table is none or nil").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: ip field in '%1' abonent info table is none or nil").arg(abonentName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (index)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: ip field in '%1' abonent info table is not a string").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: ip field in '%1' abonent info table is not a string").arg(abonentName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (index)
                        continue;
                    }
                    abonentInfo.ip = lua_tostring(L, -1);
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    
                    
                    
                    
                    
                    
                    // Считываем логин для подключения к абоненту.
                    lua_getfield(L, -1, "user");
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    // 4 - field (user string)
                    
                    bool check_user_field = true;
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: user field in '%1' abonent info table is none or nil").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("GlobalData: user field in '%1' abonent info table is none or nil").arg(abonentName));
//                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (index)
//                        continue;
                        check_user_field = false;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: user field in '%1' abonent info table is not a string").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("GlobalData: user field in '%1' abonent info table is not a string").arg(abonentName));
//                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (index)
//                        continue;
                        check_user_field = false;
                    }
                    
                    if (check_user_field) {
                        abonentInfo.user = lua_tostring(L, -1);
                    }
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    
                    
                    
                    // Считываем локальный путь к ssh-ключу для подключения к абоненту.
                    lua_getfield(L, -1, "ssh_path");
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    // 4 - field (ssh_path string)
                    
                    bool check_sshpath_field = true;                    
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: ssh_path field in '%1' abonent info table is none or nil").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("GlobalData: ssh_path field in '%1' abonent info table is none or nil").arg(abonentName));
//                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (index)
//                        continue;
                        check_sshpath_field = false;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: ssh_path field in '%1' abonent info table is not a string").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("GlobalData: ssh_path field in '%1' abonent info table is not a string").arg(abonentName));
//                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (index)
//                        continue;
                        check_sshpath_field = false;
                    }
                    
                    if (check_sshpath_field) {
                        abonentInfo.ssh_path = lua_tostring(L, -1);
                    }
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    
                    
                    
                    
                    // Считываем порт для подключения к абоненту.
                    lua_getfield(L, -1, "port");
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    // 4 - field (port string)
                    
                    bool check_port_field = true;                    
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: port field in '%1' abonent info table is none or nil").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("GlobalData: port field in '%1' abonent info table is none or nil").arg(abonentName));
//                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (index)
//                        continue;
                        check_port_field = false;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: port field in '%1' abonent info table is not a string").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_INFO, QString("GlobalData: port field in '%1' abonent info table is not a string").arg(abonentName));
//                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (index)
//                        continue;
                        check_port_field = false;
                    }
                    
                    if (check_port_field) {
                        abonentInfo.port = lua_tostring(L, -1);
                    }
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (index)
                    // 3 - value (abonent info table)
                    
                    
                    
                    
                    abonentsMap_.insert(abonentName, abonentInfo);
                    
                }
                // 1 - table
                // 2 - key (index)
                // 3 - value (abonent info table)
                //printLuaStack(L);
                lua_pop(L, 1);
                // 1 - table
                // 2 - key (index)
                //printLuaStack(L);
                
            }
            // 1 - table
            //printLuaStack(L);
            lua_pop(L, 1);
            // 0
            //printLuaStack(L);
            
        }
        
        
        
        
        
        
        
        
        
        
        
        
        // =========================
        // Try to get "Groups" table
        // =========================
        
        lua_getglobal(L, "Groups");
        
        // 1 - table "Groups"
        //printLuaStack(L);
        if (lua_isnoneornil(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: no \"Groups\" table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: no \"Groups\" table");
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: \"Groups\" is not a table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: \"Groups\" is not a table");
            return false;
        } else {
            // 1 - table
            // 2 - nil
            lua_pushnil(L);
            //printLuaStack(L);
            while (lua_next(L, -2) != 0) {
                // 1 - table
                // 2 - key (group name)
                // 3 - value (group abonents table)
                //printLuaStack(L);
                
                
                // TODO: Добавить вспл. окно ошибки обработки названия группы.
                
                // Считываем название группы.                    
                if (lua_isnoneornil(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some group name among the keys is none or nil";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: some group name among the keys is none or nil");
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                } else if (!lua_isstring(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some group name among the keys is not a string";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: some group name among the keys is not a string");
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                }
                
                
                // Проверка на существование названия текущей группы.
                QString groupName = lua_tostring(L, -2);
                if (abonentsGroupsMap_.contains(groupName)) {
                    qDebug().noquote() << QString("GlobalData: group with name '%1' already exists in 'Groups' table").arg(groupName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: group with name '%1' already exists in 'Groups' table").arg(groupName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                }
                
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug().noquote() << QString("GlobalData: no inner abonents group table for '%1' group").arg(groupName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: no inner abonents group table for '%1' group").arg(groupName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug().noquote() << QString("GlobalData: element is not an inner abonents group table for '%1' group").arg(groupName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: element is not an inner abonents group table for '%1' group").arg(groupName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                } else {                    

                    // 1 - table
                    // 2 - key (group name)
                    // 3 - value (group abonents table)
                    
                    QStringList abonentsGroup;    // = new AbonentsGroup;                           
                    
                    // 1 - table
                    // 2 - key (group name)
                    // 3 - value (group abonents table)
                    // 4 - nil
                    lua_pushnil(L);
                    while (lua_next(L, -2)) {
                        // 1 - table
                        // 2 - key (group name)
                        // 3 - value (group abonents table)
                        // 4 - key (index)
                        // 5 - value (abonent name string)
                        
                        if (lua_isnoneornil(L, -1)) {
                            qDebug().noquote() << QString("GlobalData: abonent name in group '%1' is none or nil.").arg(groupName);
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: abonent name in group '%1' is none or nil.").arg(groupName));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (!lua_isstring(L, -1)) {
                            qDebug().noquote() << QString("GlobalData: abonent name in group '%1' is not a string.").arg(groupName);
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: abonent name in group '%1' is not a string.").arg(groupName));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (abonentsGroup.contains(lua_tostring(L, -1))) {
                            qDebug().noquote() << QString("GlobalData: abonent name '%2' in group '%1' is already appended (duplicated name). "
                                                          "Will not append it to the group again.").arg(groupName).arg(lua_tostring(L, -1));
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: abonent name '%2' in group '%1' is already appended (duplicated name). "
                                                                                                    "Will not append it to the group again.").arg(groupName).arg(lua_tostring(L, -1)));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (!abonentsMap_.contains(lua_tostring(L, -1))) {
                            qDebug().noquote() << QString("GlobalData: abonent name '%2' from group '%1' doesn't exist in current AbonentMap. "
                                                          "Cannot append it to the group.").arg(groupName).arg(lua_tostring(L, -1));
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: abonent name '%2' from group '%1' doesn't exist in current AbonentMap. "
                                                                                                    "Cannot append it to the group.").arg(groupName).arg(lua_tostring(L, -1)));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        }
                        
                        abonentsGroup.append(lua_tostring(L, -1));
                        
                        lua_pop(L, 1);
                        // 1 - table
                        // 2 - key (group name)
                        // 3 - value (group abonents table)
                        // 4 - key (index)                    
                    }
                    
                    // 1 - table
                    // 2 - key (group name)
                    // 3 - value (group abonents table)
                    abonentsGroupsMap_.insert(groupName, abonentsGroup);
                    
                }
                // 1 - table
                // 2 - key (group name)
                // 3 - value (group abonents table)
                //printLuaStack(L);
                lua_pop(L, 1);
                // 1 - table
                // 2 - key (group name)
                //printLuaStack(L);
                
            }
            // 1 - table
            //printLuaStack(L);
            lua_pop(L, 1);
            // 0
            //printLuaStack(L);
            
        }        
        
        
        
        
        
        
        
        
        
        
        
        
        
        // =============================
        // Try to get "Algorithms" table
        // =============================
        
        lua_getglobal(L, "Algorithms");
        // 1 - table "Algorithms"
        //printLuaStack(L);
        if (lua_isnoneornil(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: no \"Algorithms\" table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: no \"Algorithms\" table");
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: \"Algorithms\" is not a table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: \"Algorithms\" is not a table");
            return false;
        } else {
            // 1 - table
            // 2 - nil
            lua_pushnil(L);
            //printLuaStack(L);
            while (lua_next(L, -2) != 0) {
                // 1 - table
                // 2 - key (name)
                // 3 - value (algorithm info table)
                //printLuaStack(L);
                
                
                // TODO: Добавить вспл. окно ошибки обработки названия алгоритма.
                
                // Считываем название алгоритма.                    
                if (lua_isnoneornil(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some algorithm name among the keys is none or nil";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: some algorithm name among the keys is none or nil");
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                } else if (!lua_isstring(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some algorithm name among the keys is not a string";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, "GlobalData::loadConfigData: some algorithm name among the keys is not a string");
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                }
                
                
                // Проверка на наличие в словаре названия текущего алгоритма.
                QString algorithmName = lua_tostring(L, -2);
                if (algorithmsMap_.contains(algorithmName)) {
                    qDebug().noquote() << QString("GlobalData: algorithm with name '%1' already exists in 'Algorithms' table").arg(algorithmName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: algorithm with name '%1' already exists in 'Algorithms' table").arg(algorithmName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                }
                
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug().noquote() << QString("GlobalData: no inner algorithm info table for '%1' algorithm").arg(algorithmName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: no inner algorithm info table for '%1' algorithm").arg(algorithmName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug().noquote() << QString("GlobalData: element is not an inner algorithm info table for '%1' algorithm").arg(algorithmName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: element is not an inner algorithm info table for '%1' algorithm").arg(algorithmName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                } else {                    

                    AlgorithmInfo algorithmInfo;    // = new AlgorithmInfo;
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    
                    // Считываем локальный путь к алгоритму.
                    lua_getfield(L, -1, "alg_path");
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (alg_path string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: alg_path field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: alg_path field in '%1' algorithm info table is none or nil").arg(algorithmName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: alg_path field in '%1' algorithm info table is not a string").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: alg_path field in '%1' algorithm info table is not a string").arg(algorithmName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    }
                    algorithmInfo.alg_path = lua_tostring(L, -1);
                    lua_pop(L, 1);
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    
                    // Считываем описание алгоритма.
                    lua_getfield(L, -1, "descr");
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (descr string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: descr field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: descr field in '%1' algorithm info table is none or nil").arg(algorithmName));
                        lua_pop(L, 2);
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: descr field in '%1' algorithm info table is not a string").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: descr field in '%1' algorithm info table is not a string").arg(algorithmName));
                        lua_pop(L, 2);
                        continue;
                    }
                    algorithmInfo.descr = lua_tostring(L, -1);
                    lua_pop(L, 1);
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    
                    
                    // Считываем описание алгоритма.
                    lua_getfield(L, -1, "exec_abns");
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (exec_abns table)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: exec_abns field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: exec_abns field in '%1' algorithm info table is none or nil").arg(algorithmName));
                        lua_pop(L, 2);
                        continue;
                    } else if (!lua_istable(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: exec_abns field in '%1' algorithm info table is not a table").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: exec_abns field in '%1' algorithm info table is not a table").arg(algorithmName));
                        lua_pop(L, 2);
                        continue;
                    }
                    
                    lua_pushnil(L);
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (exec_abns table)
                    // 5 - nil
                    while (lua_next(L, -2)) {
                        // 1 - table
                        // 2 - key (name)
                        // 3 - value (algorithm info table)
                        // 4 - field (exec_abns table)
                        // 5 - key (index)
                        // 6 - value (abonent name)
                        
                        if (lua_isnoneornil(L, -1)) {
                            qDebug().noquote() << QString("GlobalData: abonent name in executable abonents list of '%1' algorithm is none or nil").arg(algorithmName);
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: abonent name in executable abonents list of '%1' algorithm is none or nil").arg(algorithmName));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (!lua_isstring(L, -1)) {
                            qDebug().noquote() << QString("GlobalData: abonent name in executable abonents list of '%1' algorithm is not a string").arg(algorithmName);
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: abonent name in executable abonents list of '%1' algorithm is not a string").arg(algorithmName));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (algorithmInfo.execAbonents.contains(lua_tostring(L, -1))) {
                            qDebug().noquote() << QString("GlobalData: executable abonents list of '%1' algorithm already contains "
                                                          "abonent name '%2'").arg(algorithmName).arg(lua_tostring(L, -1));
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: executable abonents list of '%1' algorithm already contains "
                                                                                                    "abonent name '%2'").arg(algorithmName).arg(lua_tostring(L, -1)));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (!abonentsMap_.contains(lua_tostring(L, -1))) {
                            qDebug().noquote() << QString("GlobalData: abonent name '%2' from executable abonents list of '%1' algorithm doesn't exist in current AbonentMap. "
                                                          "Cannot append it to the executable abonents list.").arg(algorithmName).arg(lua_tostring(L, -1));
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_ERROR, QString("GlobalData: abonent name '%2' from executable abonents list of '%1' algorithm doesn't exist in current AbonentMap. "
                                                                                                    "Cannot append it to the executable abonents list.").arg(algorithmName).arg(lua_tostring(L, -1)));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        }
                        
                        algorithmInfo.execAbonents.append(lua_tostring(L, -1));
                        
                        lua_pop(L, 1);
                        // 1 - table
                        // 2 - key (name)
                        // 3 - value (algorithm info table)
                        // 4 - field (exec_abns table)
                        // 5 - key (index)                    
                    }
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (exec_abns table)
                    algorithmsMap_.insert(algorithmName, algorithmInfo);
                    
                }
                // 1 - table
                // 2 - key (name)
                // 3 - value (algorithm info table)
                // 4 - field (exec_abns table)
                //printLuaStack(L);
                lua_pop(L, 2);
                // 1 - table
                // 2 - key (name)
                //printLuaStack(L);
                
            }
            // 1 - table
            //printLuaStack(L);
            lua_pop(L, 1);
            // 0
            //printLuaStack(L);
            
        }
        
    }
    // =======================================================================================
    
    
    if (L != nullptr) {
        lua_close(L); 
        qDebug().noquote() << "GlobalData::loadConfigData: luaL_close().";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: luaL_close().");
    }
    
    // Если код достиг этой точки, значит конфиг-й файл был считан корректно.
    return true;
    
}





















// ВЕРСИЯ ДО ТОГО КАК ПЕРЕНЕСЛИ ИМЕНА ВОВНУТРЬ (СЛОВАРЬ-->СПИСОК)   (2026.04.27, 16:40)

/*
bool GlobalData::loadConfigData() {
    
    // СОЗДАНИЕ СЛОВАРЕЙ ДЛЯ ХРАНЕНИЯ ДАННЫХ.
    
    ////abonentsMap_ = new QMap<QString, AbonentInfo>;
    //abonentsMap_ = new AbonentsMap;
    ////abonentsGroupsMap_ = new QMap<QString, AbonentsGroup>;
    //abonentsGroupsMap_ = new AbonentsGroupsMap;
    ////algorithmsMap_ = new QMap<QString, AlgorithmInfo>;
    //algorithmsMap_ = new AlgorithmsMap;
    
    
    // ОТКРЫТИЕ ФАЙЛА И ПОЛУЧЕНИЕ ЕГО СОДЕРЖИМОГО ЧЕРЕЗ luaL_loadbuffer.
    
    lua_State* L = luaL_newstate();
    bool funcExecCheck = false;
    if (L == nullptr) {
        qDebug().noquote() << "GlobalData::loadConfigData: luaL_newstate() failed.";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: luaL_newstate() failed."));
    }
    else {
        qDebug().noquote() << "GlobalData::loadConfigData: luaL_newstate() succeeded.";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: luaL_newstate() succeeded."));
        luaL_openlibs(L);
        qDebug().noquote() << "GlobalData::loadConfigData: luaL_openlibs() succeeded.";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: luaL_openlibs() succeeded."));
        //printLuaStack(L);
        
        // TODO: путь указаывается относительно ".exe" файла (!!!)
        // QFile file("config-1.txt");
        //QFile file("../SysWizard/config-1.txt");
        // QFile file(":/resources/configs/config-data-2.txt");
        
        
        
        // NOTE: ОПЦИОНАЛЬНЫЙ ВЫВОД ВСЕХ РЕСУРСОВ И ДРУГИХ САБДИРОВ В КОНСОЛЬ.
        //QDirIterator it(":", QDirIterator::Subdirectories);
        //while (it.hasNext()) {
        //    qDebug().noquote() << it.next();
        //}
        
        
        
        // 1. Вариация считывания конфиг-файла из ресурсов.
        //QFile file(QString(":/configs/%1.txt").arg(CONFIG_DATA_FILE_PATH));
        // 1. Вариация считывания конфиг-файла из ресурсов.
        QFile file(CONFIG_DATA_FILE_PATH);
        
        
        //QFile file(QString(":/resources/configs/%1.txt").arg(CONFIG_DATA_FILE_PATH));
        //QFile file(QString(":/%1").arg(CONFIG_DATA_FILE_PATH));
        //QFile file(QString(":/resources/configs/resources/configs/%1.txt").arg(CONFIG_DATA_FILE_PATH));
        //QFile file(QString(":/resources/configs/resources/configs/config-data-3.txt"));
        //QFile file(QString("%1.txt").arg(CONFIG_DATA_FILE_PATH));
        
        //QFile file("../SysWizard/config-1.lua");
        //QFile file("../SysWizard/text2.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            if (file.exists()) {
                qDebug().noquote() << "GlobalData::loadConfigData: file.open() failed, cannot read it.";
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: file.open() failed, cannot read it."));
            } else {
                qDebug().noquote() << QString("GlobalData::loadConfigData: file doesn't exist at given directory (%1). Current path is %2").arg(file.fileName()).arg(QDir::currentPath());
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: file doesn't exist at given directory (%1). Current path is %2").arg(file.fileName()).arg(QDir::currentPath()));
            }
        }
        else {
            QString text = QTextStream(&file).readAll();
            lua_pushstring(L, text.toStdString().c_str());
            //printLuaStack(L);
            // 1 - read file function
            int result = luaL_loadbuffer(L, lua_tostring(L, (lua_gettop(L))), text.size(), "chunk");
            //printLuaStack(L);
            if (result != LUA_OK) {
                qDebug().noquote() << QString("GlobalData: %1 LUA_ERROR").arg(result);
                LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: %1 LUA_ERROR").arg(result));
            }
            else {
                if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
                    qDebug().noquote() << "GlobalData::loadConfigData: lua_pcall() failed.";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: lua_pcall() failed."));
                    qDebug().noquote() << QString("GlobalData: fail code: %1").arg(lua_tointeger(L, -1));
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: fail code: %1").arg(lua_tointeger(L, -1)));
                    qDebug().noquote() << QString("GlobalData: fail msg: %1").arg(lua_tostring(L, -1));
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: fail msg: %1").arg(lua_tostring(L, -1)));
                }
                else {
                    qDebug().noquote() << "GlobalData::loadConfigData: lua_pcall() succeeded.";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: lua_pcall() succeeded."));
                    funcExecCheck = true;
                    printLuaStack(L);           // 1 - read file function
                    lua_pop(L, 1);
                }
                //printLuaStack(L);
                //lua_pop(L, 1);
                //printLuaStack(L);
            }
        }
        
        file.close();        
    }
    
    
    
    
    
    
    // ОБРАБОТКА СОДЕРЖИМОГО ФАЙЛА ЧЕРЕЗ СТЕК LUA.
    
    
    // =======================================================================================
    if (funcExecCheck) {
        
        
        
        // ===========================
        // Try to get "Abonents" table
        // ===========================
        
        
        lua_getglobal(L, "Abonents");
        // 1 - table "Abonents"
        //printLuaStack(L);
        if (lua_isnoneornil(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: no \"Abonents\" table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: no \"Abonents\" table"));
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: \"Abonents\" is not a table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: \"Abonents\" is not a table"));
            return false;
        } else {
            // 1 - table
            // 2 - nil
            lua_pushnil(L);
            //printLuaStack(L);
            while (lua_next(L, -2) != 0) {
                // 1 - table
                // 2 - key (name)
                // 3 - value (abonent info table)
                //printLuaStack(L);
                
                // TODO: Добавить вспл. окно ошибки обработки имени абонента.
                
                // Считываем имя абонента.
                if (lua_isnoneornil(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some abonent name among the keys is none or nil";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: some abonent name among the keys is none or nil"));
                    lua_pop(L, 1);
                    continue;
                } else if (!lua_isstring(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some abonent name among the keys is not a string";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData::loadConfigData: some abonent name among the keys is not a string"));
                    lua_pop(L, 1);
                    continue;
                }
                
                
                // Проверка на существование имени текущего абонента.
                QString abonentName = lua_tostring(L, -2);
                if (abonentsMap_.contains(abonentName)) {
                    qDebug().noquote() << QString("GlobalData: abonent with name '%1' already exists in 'Abonents' table").arg(abonentName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: abonent with name '%1' already exists in 'Abonents' table").arg(abonentName));
                    lua_pop(L, 1);
                    continue;
                }
                
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: no inner abonent info table";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: no inner abonent info table");
                    lua_pop(L, 1);
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: element is not an inner abonent info table";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: element is not an inner abonent info table");
                    lua_pop(L, 1);
                    continue;
                } else {                    

                    AbonentInfo abonentInfo;    // = new AbonentInfo;                           
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (abonent info table)
                    
                    
                    // Считываем IP абонента.
                    lua_getfield(L, -1, "ip");
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (abonent info table)
                    // 4 - field (ip string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: ip field in '%1' abonent info table is none or nil").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: ip field in '%1' abonent info table is none or nil").arg(abonentName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: ip field in '%1' abonent info table is not a string").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: ip field in '%1' abonent info table is not a string").arg(abonentName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    }
                    abonentInfo.ip = lua_tostring(L, -1);
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (abonent info table)
                    
                    
                    
                    // Считываем логин для подключения к абоненту.
                    lua_getfield(L, -1, "user");
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (abonent info table)
                    // 4 - field (user string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: user field in '%1' abonent info table is none or nil").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: user field in '%1' abonent info table is none or nil").arg(abonentName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: user field in '%1' abonent info table is not a string").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: user field in '%1' abonent info table is not a string").arg(abonentName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    }
                    abonentInfo.user = lua_tostring(L, -1);
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (abonent info table)
                    
                    
                    
                    // Считываем локальный путь к ssh-ключу для подключения к абоненту.
                    lua_getfield(L, -1, "ssh_path");
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (abonent info table)
                    // 4 - field (ssh_path string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: ssh_path field in '%1' abonent info table is none or nil").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: ssh_path field in '%1' abonent info table is none or nil").arg(abonentName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: ssh_path field in '%1' abonent info table is not a string").arg(abonentName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: ssh_path field in '%1' abonent info table is not a string").arg(abonentName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    }
                    abonentInfo.ssh_path = lua_tostring(L, -1);
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (abonent info table)
                    
                    abonentsMap_.insert(abonentName, abonentInfo);
                    
                }
                // 1 - table
                // 2 - key (name)
                // 3 - value (abonent info table)
                //printLuaStack(L);
                lua_pop(L, 1);
                // 1 - table
                // 2 - key (name)
                //printLuaStack(L);
                
            }
            // 1 - table
            //printLuaStack(L);
            lua_pop(L, 1);
            // 0
            //printLuaStack(L);
            
        }
        
        
        
        // =========================
        // Try to get "Groups" table
        // =========================
        
        lua_getglobal(L, "Groups");
        
        // 1 - table "Groups"
        //printLuaStack(L);
        if (lua_isnoneornil(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: no \"Groups\" table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: no \"Groups\" table");
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: \"Groups\" is not a table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: \"Groups\" is not a table");
            return false;
        } else {
            // 1 - table
            // 2 - nil
            lua_pushnil(L);
            //printLuaStack(L);
            while (lua_next(L, -2) != 0) {
                // 1 - table
                // 2 - key (group name)
                // 3 - value (group abonents table)
                //printLuaStack(L);
                
                
                // TODO: Добавить вспл. окно ошибки обработки названия группы.
                
                // Считываем название группы.                    
                if (lua_isnoneornil(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some group name among the keys is none or nil";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: some group name among the keys is none or nil");
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                } else if (!lua_isstring(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some group name among the keys is not a string";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: some group name among the keys is not a string");
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                }
                
                
                // Проверка на существование названия текущей группы.
                QString groupName = lua_tostring(L, -2);
                if (abonentsGroupsMap_.contains(groupName)) {
                    qDebug().noquote() << QString("GlobalData: group with name '%1' already exists in 'Groups' table").arg(groupName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: group with name '%1' already exists in 'Groups' table").arg(groupName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                }
                
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug().noquote() << QString("GlobalData: no inner abonents group table for '%1' group").arg(groupName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: no inner abonents group table for '%1' group").arg(groupName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug().noquote() << QString("GlobalData: element is not an inner abonents group table for '%1' group").arg(groupName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: element is not an inner abonents group table for '%1' group").arg(groupName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                } else {                    

                    // 1 - table
                    // 2 - key (group name)
                    // 3 - value (group abonents table)
                    
                    QStringList abonentsGroup;    // = new AbonentsGroup;                           
                    
                    // 1 - table
                    // 2 - key (group name)
                    // 3 - value (group abonents table)
                    // 4 - nil
                    lua_pushnil(L);
                    while (lua_next(L, -2)) {
                        // 1 - table
                        // 2 - key (group name)
                        // 3 - value (group abonents table)
                        // 4 - key (index)
                        // 5 - value (abonent name string)
                        
                        if (lua_isnoneornil(L, -1)) {
                            qDebug().noquote() << QString("GlobalData: abonent name in group '%1' is none or nil.").arg(groupName);
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: abonent name in group '%1' is none or nil.").arg(groupName));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (!lua_isstring(L, -1)) {
                            qDebug().noquote() << QString("GlobalData: abonent name in group '%1' is not a string.").arg(groupName);
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: abonent name in group '%1' is not a string.").arg(groupName));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (abonentsGroup.contains(lua_tostring(L, -1))) {
                            qDebug().noquote() << QString("GlobalData: abonent name '%2' in group '%1' is already appended (duplicated name). "
                                                          "Will not append it to the group again.").arg(groupName).arg(lua_tostring(L, -1));
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: abonent name '%2' in group '%1' is already appended (duplicated name). "
                                                                                                    "Will not append it to the group again.").arg(groupName).arg(lua_tostring(L, -1)));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (!abonentsMap_.contains(lua_tostring(L, -1))) {
                            qDebug().noquote() << QString("GlobalData: abonent name '%2' from group '%1' doesn't exist in current AbonentMap. "
                                                          "Cannot append it to the group.").arg(groupName).arg(lua_tostring(L, -1));
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: abonent name '%2' from group '%1' doesn't exist in current AbonentMap. "
                                                                                                    "Cannot append it to the group.").arg(groupName).arg(lua_tostring(L, -1)));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        }
                        
                        abonentsGroup.append(lua_tostring(L, -1));
                        
                        lua_pop(L, 1);
                        // 1 - table
                        // 2 - key (group name)
                        // 3 - value (group abonents table)
                        // 4 - key (index)                    
                    }
                    
                    // 1 - table
                    // 2 - key (group name)
                    // 3 - value (group abonents table)
                    abonentsGroupsMap_.insert(groupName, abonentsGroup);
                    
                }
                // 1 - table
                // 2 - key (group name)
                // 3 - value (group abonents table)
                //printLuaStack(L);
                lua_pop(L, 1);
                // 1 - table
                // 2 - key (group name)
                //printLuaStack(L);
                
            }
            // 1 - table
            //printLuaStack(L);
            lua_pop(L, 1);
            // 0
            //printLuaStack(L);
            
        }        
        
        
        
        // =============================
        // Try to get "Algorithms" table
        // =============================
        
        lua_getglobal(L, "Algorithms");
        // 1 - table "Algorithms"
        //printLuaStack(L);
        if (lua_isnoneornil(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: no \"Algorithms\" table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: no \"Algorithms\" table");
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug().noquote() << "GlobalData::loadConfigData: \"Algorithms\" is not a table";
            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: \"Algorithms\" is not a table");
            return false;
        } else {
            // 1 - table
            // 2 - nil
            lua_pushnil(L);
            //printLuaStack(L);
            while (lua_next(L, -2) != 0) {
                // 1 - table
                // 2 - key (name)
                // 3 - value (algorithm info table)
                //printLuaStack(L);
                
                
                // TODO: Добавить вспл. окно ошибки обработки названия алгоритма.
                
                // Считываем название алгоритма.                    
                if (lua_isnoneornil(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some algorithm name among the keys is none or nil";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: some algorithm name among the keys is none or nil");
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                } else if (!lua_isstring(L, -2)) {
                    qDebug().noquote() << "GlobalData::loadConfigData: some algorithm name among the keys is not a string";
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: some algorithm name among the keys is not a string");
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                }
                
                
                // Проверка на наличие в словаре названия текущего алгоритма.
                QString algorithmName = lua_tostring(L, -2);
                if (algorithmsMap_.contains(algorithmName)) {
                    qDebug().noquote() << QString("GlobalData: algorithm with name '%1' already exists in 'Algorithms' table").arg(algorithmName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: algorithm with name '%1' already exists in 'Algorithms' table").arg(algorithmName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                }
                
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug().noquote() << QString("GlobalData: no inner algorithm info table for '%1' algorithm").arg(algorithmName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: no inner algorithm info table for '%1' algorithm").arg(algorithmName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug().noquote() << QString("GlobalData: element is not an inner algorithm info table for '%1' algorithm").arg(algorithmName);
                    LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: element is not an inner algorithm info table for '%1' algorithm").arg(algorithmName));
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                } else {                    

                    AlgorithmInfo algorithmInfo;    // = new AlgorithmInfo;
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    
                    // Считываем локальный путь к алгоритму.
                    lua_getfield(L, -1, "alg_path");
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (alg_path string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: alg_path field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: alg_path field in '%1' algorithm info table is none or nil").arg(algorithmName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: alg_path field in '%1' algorithm info table is not a string").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: alg_path field in '%1' algorithm info table is not a string").arg(algorithmName));
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    }
                    algorithmInfo.alg_path = lua_tostring(L, -1);
                    lua_pop(L, 1);
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    
                    // Считываем описание алгоритма.
                    lua_getfield(L, -1, "descr");
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (descr string)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: descr field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: descr field in '%1' algorithm info table is none or nil").arg(algorithmName));
                        lua_pop(L, 2);
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: descr field in '%1' algorithm info table is not a string").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: descr field in '%1' algorithm info table is not a string").arg(algorithmName));
                        lua_pop(L, 2);
                        continue;
                    }
                    algorithmInfo.descr = lua_tostring(L, -1);
                    lua_pop(L, 1);
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    
                    
                    // Считываем описание алгоритма.
                    lua_getfield(L, -1, "exec_abns");
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (exec_abns table)
                    
                    if (lua_isnoneornil(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: exec_abns field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: exec_abns field in '%1' algorithm info table is none or nil").arg(algorithmName));
                        lua_pop(L, 2);
                        continue;
                    } else if (!lua_istable(L, -1)) {
                        qDebug().noquote() << QString("GlobalData: exec_abns field in '%1' algorithm info table is not a table").arg(algorithmName);
                        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: exec_abns field in '%1' algorithm info table is not a table").arg(algorithmName));
                        lua_pop(L, 2);
                        continue;
                    }
                    
                    lua_pushnil(L);
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (exec_abns table)
                    // 5 - nil
                    while (lua_next(L, -2)) {
                        // 1 - table
                        // 2 - key (name)
                        // 3 - value (algorithm info table)
                        // 4 - field (exec_abns table)
                        // 5 - key (index)
                        // 6 - value (abonent name)
                        
                        if (lua_isnoneornil(L, -1)) {
                            qDebug().noquote() << QString("GlobalData: abonent name in executable abonents list of '%1' algorithm is none or nil").arg(algorithmName);
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: abonent name in executable abonents list of '%1' algorithm is none or nil").arg(algorithmName));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (!lua_isstring(L, -1)) {
                            qDebug().noquote() << QString("GlobalData: abonent name in executable abonents list of '%1' algorithm is not a string").arg(algorithmName);
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: abonent name in executable abonents list of '%1' algorithm is not a string").arg(algorithmName));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (algorithmInfo.execAbonents.contains(lua_tostring(L, -1))) {
                            qDebug().noquote() << QString("GlobalData: executable abonents list of '%1' algorithm already contains "
                                                          "abonent name '%2'").arg(algorithmName).arg(lua_tostring(L, -1));
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: executable abonents list of '%1' algorithm already contains "
                                                                                                    "abonent name '%2'").arg(algorithmName).arg(lua_tostring(L, -1)));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (!abonentsMap_.contains(lua_tostring(L, -1))) {
                            qDebug().noquote() << QString("GlobalData: abonent name '%2' from executable abonents list of '%1' algorithm doesn't exist in current AbonentMap. "
                                                          "Cannot append it to the executable abonents list.").arg(algorithmName).arg(lua_tostring(L, -1));
                            LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, QString("GlobalData: abonent name '%2' from executable abonents list of '%1' algorithm doesn't exist in current AbonentMap. "
                                                                                                    "Cannot append it to the executable abonents list.").arg(algorithmName).arg(lua_tostring(L, -1)));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        }
                        
                        algorithmInfo.execAbonents.append(lua_tostring(L, -1));
                        
                        lua_pop(L, 1);
                        // 1 - table
                        // 2 - key (name)
                        // 3 - value (algorithm info table)
                        // 4 - field (exec_abns table)
                        // 5 - key (index)                    
                    }
                    
                    // 1 - table
                    // 2 - key (name)
                    // 3 - value (algorithm info table)
                    // 4 - field (exec_abns table)
                    algorithmsMap_.insert(algorithmName, algorithmInfo);
                    
                }
                // 1 - table
                // 2 - key (name)
                // 3 - value (algorithm info table)
                // 4 - field (exec_abns table)
                //printLuaStack(L);
                lua_pop(L, 2);
                // 1 - table
                // 2 - key (name)
                //printLuaStack(L);
                
            }
            // 1 - table
            //printLuaStack(L);
            lua_pop(L, 1);
            // 0
            //printLuaStack(L);
            
        }
        
    }
    // =======================================================================================
    
    
    if (L != nullptr) {
        lua_close(L); 
        qDebug().noquote() << "GlobalData::loadConfigData: luaL_close().";
        LogerGlobal::instance().addMessageToGlobalLog(objectName(), Loger::LL_TRACE, "GlobalData::loadConfigData: luaL_close().");
    }
    
    // Если код достиг этой точки, значит конфиг-й файл был считан корректно.
    return true;
    
}
*/


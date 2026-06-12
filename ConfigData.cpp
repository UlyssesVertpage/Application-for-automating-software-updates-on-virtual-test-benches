#include "ConfigData.h"




/**
 * \brief Метод формат-го вывода в консоль текущего стека для переданного Lua-состояния.
 * \param[in] L текущее состояние Lua.
 * \return Метод не возвращает ничего.
 *
 * \n
 * В случаях, когда в стеке что-то есть (после считывания содержимого файла в буффер), оно
 * будет выведено в формате "Индекс, обратный индекс (отриц-й), тип данных, сами данные.
 */
void ConfigData::printLuaStack(lua_State* L) {
    int size = lua_gettop(L);
    qDebug() << "";
    qDebug() << QString("=").repeated(10);
    for (int i = 1; i <= size; ++i) {
        //qDebug() << lua_type(L, i);
        lua_pushvalue(L, i);
        QString str = lua_tostring(L, -1);
        int type = lua_type(L, -1);
        lua_pop(L, 1);
        qDebug() << QString("%1 (%2), type: [%3], value: %4").arg(i).arg(-size-1+i).arg(type).arg(str);
        //qDebug() << i << "(" << -size-1+i << "): " << lua_tostring(L, i);
    }
    qDebug() << QString("=").repeated(10) << '\n';
}




/**
 * \brief Метод формат-го вывода в консоль словаря всех абонентов.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void ConfigData::printAbonentsMap() {
    qDebug() << "";
    qDebug() << QString("=").repeated(20) << "ABONENTS MAP" << QString("=").repeated(20);
    for (const QString& name : abonentsMap_.keys()) {
        AbonentInfo info = abonentsMap_.value(name);
        qDebug() << name << info.ip << info.user << info.ssh_path;
    }
    qDebug() << QString("=").repeated(56);
}



/**
 * \brief Метод формат-го вывода в консоль словаря всех групп абонентов.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void ConfigData::printAbonentsGroupsMap() {
    qDebug() << "";
    qDebug() << QString("=").repeated(20) << "ABONENTS GROUPS MAP" << QString("=").repeated(20);
    for (const QString& name : abonentsGroupsMap_.keys()) {
        QStringList group = abonentsGroupsMap_.value(name);
        qDebug() << name;
        for (QString& abn : group) {
            qDebug() << "    " << abn;
        }
    }
    qDebug() << QString("=").repeated(63);
}



/**
 * \brief Метод формат-го вывода в консоль словаря всех алгоритмов.
 * \return Метод не возвращает ничего.
 *
 * \n
 */
void ConfigData::printAlgorithmsMap() {
    qDebug() << "";
    qDebug() << QString("=").repeated(20) << "ALGORITHMS MAP" << QString("=").repeated(20);
    for (const QString& name : algorithmsMap_.keys()) {
        AlgorithmInfo info = algorithmsMap_.value(name);
        qDebug() << name;
        qDebug() << "    " << info.alg_path;
        qDebug() << "    " << info.descr;
        for (QString& abn : info.execAbonents) {
            qDebug() << "    " << abn;
        }
    }
    qDebug() << QString("=").repeated(58);
}




/**
 * \brief Конструтор класса чтения, обработки и хранения конфигурационных данных.
 * \return Конструтор не возвращает ничего.
 *
 * \n
 */
bool ConfigData::loadConfigData() {
    
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
    if (L == nullptr) { qDebug() << "ConfigData: luaL_newstate() failed."; }
    else {
        qDebug() << "ConfigData: luaL_newstate() succeeded.";
        luaL_openlibs(L);  qDebug() << "ConfigData: luaL_openlibs() succeeded.";
        //printLuaStack(L);
        
        // TODO: путь указаывается относительно ".exe" файла (!!!)
        // QFile file("config-1.txt");
        QFile file("../SysWizard/config-1.txt");
        
        //QFile file("../SysWizard/config-1.lua");
        //QFile file("../SysWizard/text2.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            if (file.exists()) {
                qDebug() << "ConfigData: file.open() failed, cannot read it.";
            } else {
                qDebug() << "ConfigData: file doesn't exist at given directory: " << QDir::currentPath();
            }
        }
        else {
            QString text = QTextStream(&file).readAll();
            lua_pushstring(L, text.toStdString().c_str());
            //printLuaStack(L);
            // 1 - read file function
            int result = luaL_loadbuffer(L, lua_tostring(L, (lua_gettop(L))), text.size(), "chunk");
            //printLuaStack(L);
            if (result != LUA_OK) { qDebug() << QString("ConfigData: %1 LUA_ERROR").arg(result); }
            else {
                if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
                    qDebug() << "ConfigData: lua_pcall() failed.";
                    qDebug() << QString("ConfigData: fail code: %1").arg(lua_tointeger(L, -1));
                    qDebug() << QString("ConfigData: fail msg: %1").arg(lua_tostring(L, -1));
                }
                else {
                    qDebug() << "ConfigData: lua_pcall() succeeded.";
                    funcExecCheck = true;
                    printLuaStack(L);           // 1 - read file function
                    lua_pop(L, 1);
                }
                //printLuaStack(L);
                //lua_pop(L, 1);
                //printLuaStack(L);
            }
        }
    }
    
    
    
    // ОБРАБОТКА СОДЕРЖИМОГО ФАЙЛА ЧЕРЕЗ СТЕК LUA.
    
    
    // ============================= Для config-1.txt =============================            
    if (funcExecCheck) {
        
        
        
        // ===========================
        // Try to get "Abonents" table
        // ===========================
        
        
        lua_getglobal(L, "Abonents");
        // 1 - table "Abonents"
        //printLuaStack(L);
        if (lua_isnoneornil(L, -1)) {
            qDebug() << "ConfigData: no \"Abonents\" table";
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug() << "ConfigData: \"Abonents\" is not a table";
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
                    qDebug() << "ConfigData: some abonent name among the keys is none or nil";
                    lua_pop(L, 1);
                    continue;
                } else if (!lua_isstring(L, -2)) {
                    qDebug() << "ConfigData: some abonent name among the keys is not a string";
                    lua_pop(L, 1);
                    continue;
                }
                
                
                // Проверка на существование имени текущего абонента.
                QString abonentName = lua_tostring(L, -2);
                if (abonentsMap_.contains(abonentName)) {
                    qDebug() << QString("ConfigData: abonent with name '%1' already exists in 'Abonents' table").arg(abonentName);
                    lua_pop(L, 1);
                    continue;
                }
                
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug() << "ConfigData: no inner abonent info table";
                    lua_pop(L, 1);
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug() << "ConfigData: element is not an inner abonent info table";
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
                        qDebug() << QString("ConfigData: ip field in '%1' abonent info table is none or nil").arg(abonentName);
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug() << QString("ConfigData: ip field in '%1' abonent info table is not a string").arg(abonentName);
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
                        qDebug() << QString("ConfigData: user field in '%1' abonent info table is none or nil").arg(abonentName);
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug() << QString("ConfigData: user field in '%1' abonent info table is not a string").arg(abonentName);
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
                        qDebug() << QString("ConfigData: ssh_path field in '%1' abonent info table is none or nil").arg(abonentName);
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug() << QString("ConfigData: ssh_path field in '%1' abonent info table is not a string").arg(abonentName);
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
            qDebug() << "ConfigData: no \"Groups\" table";
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug() << "ConfigData: \"Groups\" is not a table";
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
                    qDebug() << "ConfigData: some group name among the keys is none or nil";
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                } else if (!lua_isstring(L, -2)) {
                    qDebug() << "ConfigData: some group name among the keys is not a string";
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                }
                
                
                // Проверка на существование названия текущей группы.
                QString groupName = lua_tostring(L, -2);
                if (abonentsGroupsMap_.contains(groupName)) {
                    qDebug() << QString("ConfigData: group with name '%1' already exists in 'Groups' table").arg(groupName);
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                }
                
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug() << QString("ConfigData: no inner abonents group table for '%1' group").arg(groupName);
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (group name)
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug() << QString("ConfigData: element is not an inner abonents group table for '%1' group").arg(groupName);
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
                            qDebug() << QString("ConfigData: abonent name in group '%1' is none or nil.").arg(groupName);
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (!lua_isstring(L, -1)) {
                            qDebug() << QString("ConfigData: abonent name in group '%1' is not a string.").arg(groupName);
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (abonentsGroup.contains(lua_tostring(L, -1))) {
                            qDebug() << QString("ConfigData: abonent name '%2' in group '%1' is already appended (duplicated name). "
                                                "Will not append it to the group again.").arg(groupName).arg(lua_tostring(L, -1));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (group name)
                            // 3 - value (group abonents table)
                            // 4 - key (index)
                            continue;
                        } else if (!abonentsMap_.contains(lua_tostring(L, -1))) {
                            qDebug() << QString("ConfigData: abonent name '%2' from group '%1' doesn't exist in current AbonentMap. "
                                                "Cannot append it to the group.").arg(groupName).arg(lua_tostring(L, -1));
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
            qDebug() << "ConfigData: no \"Algorithms\" table";
            return false;
        } else if (!lua_istable(L, -1)) {
            qDebug() << "ConfigData: \"Algorithms\" is not a table";
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
                    qDebug() << "ConfigData: some algorithm name among the keys is none or nil";
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                } else if (!lua_isstring(L, -2)) {
                    qDebug() << "ConfigData: some algorithm name among the keys is not a string";
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                }
                
                
                // Проверка на наличие в словаре названия текущего алгоритма.
                QString algorithmName = lua_tostring(L, -2);
                if (algorithmsMap_.contains(algorithmName)) {
                    qDebug() << QString("ConfigData: algorithm with name '%1' already exists in 'Algorithms' table").arg(algorithmName);
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                }
                
                
                if (lua_isnoneornil(L, -1)) {
                    qDebug() << QString("ConfigData: no inner algorithm info table for '%1' algorithm").arg(algorithmName);
                    lua_pop(L, 1);
                    // 1 - table
                    // 2 - key (name)
                    continue;
                } else if (!lua_istable(L, -1)) {
                    qDebug() << QString("ConfigData: element is not an inner algorithm info table for '%1' algorithm").arg(algorithmName);
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
                        qDebug() << QString("ConfigData: alg_path field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        lua_pop(L, 2);
                        // 1 - table
                        // 2 - key (name)
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug() << QString("ConfigData: alg_path field in '%1' algorithm info table is not a string").arg(algorithmName);
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
                        qDebug() << QString("ConfigData: descr field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        lua_pop(L, 2);
                        continue;
                    } else if (!lua_isstring(L, -1)) {
                        qDebug() << QString("ConfigData: descr field in '%1' algorithm info table is not a string").arg(algorithmName);
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
                        qDebug() << QString("ConfigData: exec_abns field in '%1' algorithm info table is none or nil").arg(algorithmName);
                        lua_pop(L, 2);
                        continue;
                    } else if (!lua_istable(L, -1)) {
                        qDebug() << QString("ConfigData: exec_abns field in '%1' algorithm info table is not a table").arg(algorithmName);
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
                            qDebug() << QString("ConfigData: abonent name in executable abonents list of '%1' algorithm is none or nil").arg(algorithmName);
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (!lua_isstring(L, -1)) {
                            qDebug() << QString("ConfigData: abonent name in executable abonents list of '%1' algorithm is not a string").arg(algorithmName);
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (algorithmInfo.execAbonents.contains(lua_tostring(L, -1))) {
                            qDebug() << QString("ConfigData: executable abonents list of '%1' algorithm already contains "
                                                "abonent name '%2'").arg(algorithmName).arg(lua_tostring(L, -1));
                            lua_pop(L, 1);
                            // 1 - table
                            // 2 - key (name)
                            // 3 - value (algorithm info table)
                            // 4 - field (exec_abns table)
                            // 5 - key (index)
                            continue;
                        } else if (!abonentsMap_.contains(lua_tostring(L, -1))) {
                            qDebug() << QString("ConfigData: abonent name '%2' from executable abonents list of '%1' algorithm doesn't exist in current AbonentMap. "
                                                "Cannot append it to the executable abonents list.").arg(algorithmName).arg(lua_tostring(L, -1));
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
    // ============================= Для config-1.txt =============================        
    
    
    if (L != nullptr) {
        lua_close(L); 
        qDebug() << "ConfigData: luaL_close().";
    }
    
    // Если код достиг этой точки, значит конфиг-й файл был считан корректно.
    return true;
    
}






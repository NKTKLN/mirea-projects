#include <string>

#include "models.h"

using namespace std;

// Interface language templates
Language English() {
    Language lang;

    lang.exit = "Exit";

    lang.mainMenuTitle = "Factory emulator";
    lang.mainMenuEntries = {
        "Start",
        "Settings",
        "About",
        lang.exit
    };

    lang.systemMenuTitle = "System";
    lang.systemMenuStopButton = "Stop system";
    lang.systemMenuStartButton = "Start system";
    lang.systemMenuConveyorStopButton = "Stop conveyor";
    lang.systemMenuConveyorStartButton = "Start conveyor";
    lang.systemErrors = {
        "",
        "The container ran out of details",
        "The maximum level of details in the container has been exceeded",
    };
    lang.systemMenuTabs = {
        "First conveyor",
        "Second conveyor",
        "Third conveyor"
    };

    lang.settingsMenuTitle = "Settings";
    lang.settingsMenuLanguage = "Language";
    lang.settingsMenuConatinerValue = "Container start value";
    lang.settingsMenuFirstConatiner = "First container";
    lang.settingsMenuSecondConatiner = "Second container";
    lang.settingsMenuThirdConatiner = "Third container";
    lang.settingsMenuLanguageEntries = {
        "English",
        "Russian",
        "Chinese"
    };

    lang.aboutMenuTitle = "About";
    lang.aboutMenuCodename = "Codename";
    lang.aboutMenuCreator = "Creator";

    return lang;
}

Language Russian() {
    Language lang;

    lang.exit = "Выход";

    lang.mainMenuTitle = "Эмулятор фабрики";
    lang.mainMenuEntries = {
        "Запуск",
        "Настройки",
        "О программе",
        lang.exit
    };

    lang.systemMenuTitle = "Система";
    lang.systemMenuStopButton = "Остановить систему";
    lang.systemMenuStartButton = "Запустить систему";
    lang.systemMenuConveyorStopButton = "Остановить конвейер";
    lang.systemMenuConveyorStartButton = "Запустить конвейер";
    lang.systemErrors = {
        "",
        "В корнейтене закончились детали",
        "Достигнут максимальный уровень деталей в контейнере",
    };
    lang.systemMenuTabs = {
        "Первый конвейер",
        "Второй конвейер",
        "Третий конвейер"
    };

    lang.settingsMenuTitle = "Настройки";
    lang.settingsMenuLanguage = "Язык";
    lang.settingsMenuConatinerValue = "Начальное значение контейнера";
    lang.settingsMenuFirstConatiner = "Первый контейнер";
    lang.settingsMenuSecondConatiner = "Второй контейнер";
    lang.settingsMenuThirdConatiner = "Третий контейнер";
    lang.settingsMenuLanguageEntries = {
        "Английский",
        "Русский",
        "Китайский"
    };

    lang.aboutMenuTitle = "О программе";
    lang.aboutMenuCodename = "Кодовое имя";
    lang.aboutMenuCreator = "Создатель";

    return lang;
}

Language Chinese() {
    Language lang;

    lang.exit = "退出";

    lang.mainMenuTitle = "工厂模拟器";
    lang.systemMenuStopButton = "停止系统";
    lang.systemMenuStartButton = "启动系统";
    lang.systemMenuConveyorStopButton = "停止传送带";
    lang.systemMenuConveyorStartButton = "启动传送带";
    lang.mainMenuEntries = {
        "启动",
        "设置",
        "关于",
        lang.exit
    };

    lang.systemMenuTitle = "系统";
    lang.systemMenuTabs = {
        "第一传送带",
        "第二传送带",
        "第三传送带"
    };

    lang.settingsMenuTitle = "设置";
    lang.settingsMenuLanguage = "语言";
    lang.settingsMenuConatinerValue = "容器初始值";
    lang.settingsMenuFirstConatiner = "第一容器";
    lang.settingsMenuSecondConatiner = "第二容器";
    lang.settingsMenuThirdConatiner = "第三容器";
    lang.systemErrors = {
        "",
        "没有关于集装箱的更多细节",
        "已超出容器中详细信息的最大级别",
    };
    lang.settingsMenuLanguageEntries = {
        "英语",
        "俄语",
        "汉语"
    };

    lang.aboutMenuTitle = "关于";
    lang.aboutMenuCodename = "代号";
    lang.aboutMenuCreator = "创建者";

    return lang;
}

extern const vector<Language> languages = {English(), Russian(), Chinese()};

// Conveyor screen templates

/*
0 - top box close
1 - top box open
2 - top box number
3 - second box close
4 - second box open
5 - second box number
6 - belt top
7 - belt bottom
8 - first detector
9 - second detector
*/
extern const string conveyorTemplate[13] = {
    "+--------+                                                            ",
    "|==[{2:02}]==|           +---+      +----+            +---+               ",
    "|========|           |{8} {8}|      |][][|            |{9} {9}|               ",
    "0{0}+           | - |      |][][|            | - |               ",
    " {1}                   +---+      +----+            +---+               ",
    "  {1}                    :                            :                 ",
    "   {1}                   :                            :             {4}   ",
    "                       :                            :              {4}  ",
    " .{6}.          {4} ",
    "( 0                                                     0 ) +{3}0",
    " '{7}'  |==[{5:02}]==|",
    "                                                            |========|",
    "                                                            +--------+"
};

extern const string containerStates[2][2] = {
    {"--------", "        "}, 
    {" ", "\\"}
};

extern const string detectorStates[2] = {"-", "0"};

extern const string printerStates[2] = {
    "  ||  ",
    "/====\\"
};

extern const string boxTypes[4][2] = {
    {
        "",
        "----"
    },
    {
        "*i^o",
        "----"
    },
    {
        " __ ",
        "[##]"
    },
    {
        " __ ",
        "[{}]"
    },
};

extern const string beltStates[3] = {
    "-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-",
    "==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-=",
    "=-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-=="
};

#ifndef models
#define models

#include <vector>
#include <string>

using namespace std;

struct ConveyorStatuses {
    int printer;
    int detailType;
    string detailData;
    int detailXCords;
    bool firstDetector;
    bool secondDetector;
    bool topContainer;
    bool bottomContainer;
    int topContainerValue;
    int bottomContainerValue;
    int errorIndex;
};

struct Language {
    string exit;

    string mainMenuTitle;
    vector<string> mainMenuEntries;

    string systemMenuTitle;
    string systemMenuStopButton;
    string systemMenuStartButton;
    string systemMenuConveyorStopButton;
    string systemMenuConveyorStartButton;
    vector<string> systemErrors;
    vector<string> systemMenuTabs;

    string settingsMenuTitle;
    string settingsMenuLanguage;
    string settingsMenuConatinerValue;
    string settingsMenuFirstConatiner;
    string settingsMenuSecondConatiner;
    string settingsMenuThirdConatiner;
    vector<string> settingsMenuLanguageEntries;

    string aboutMenuTitle;
    string aboutMenuCodename;
    string aboutMenuCreator;
};

struct Settings {
    int containerMaxValue;
    int firstContainerValue;
    int secondContainerValue;
    int thirdContainerValue;
    Language language;
};

extern const vector<Language> languages;

extern const string conveyorTemplate[13];
extern const string containerStates[2][2];
extern const string detectorStates[2];
extern const string printerStates[2];
extern const string boxTypes[4][2];
extern const string beltStates[3];

#endif

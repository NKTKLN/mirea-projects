#ifndef interface
#define interface

#include "models.h"

class UserInterface {
private:
    Settings settings;
    int selectedLanguageIndex;

public:
    UserInterface();

    void mainScreen();
    void systemScreen();
    void settingsScreen();
    void aboutScreen();
};

#endif

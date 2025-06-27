#include <string>
#include <vector>

#include <fmt/core.h>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/screen/terminal.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include "models.h"
#include "system.h"
#include "interface.h"
#include "environment.h"

using namespace std;
using namespace fmt;
using namespace ftxui;

UserInterface::UserInterface() : selectedLanguageIndex(0) {
    settings.containerMaxValue = 20;
    settings.firstContainerValue = 20;
    settings.secondContainerValue = 0;
    settings.thirdContainerValue = 0;
    settings.language = languages[selectedLanguageIndex];
}

void UserInterface::mainScreen() {
    if (Terminal::Size().dimy < 23 || Terminal::Size().dimx < 80) {
        Element document = color(Color::Red, hbox({
            text("Terminal window size is less than "),
            text("80x23") | underlined,
            text(" characters!"),
        })) | bold;
        Screen screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
        Render(screen, document);
        screen.Print();
        return;
    }

    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    int selected = 0;
    MenuOption option = MenuOption();
    option.on_enter = [&] {
        switch (selected) {
        case 0: systemScreen(); break;
        case 1: settingsScreen(); break;
        case 2: aboutScreen(); break;
        case 3: screen.Exit(); break;
        }
    };
    Component menu = Menu(&settings.language.mainMenuEntries, &selected, option);
    Component renderer = Renderer(menu, [&] {
        return vbox({
            text(settings.language.mainMenuTitle) | center | bold,
            separator(),
            menu->Render() | size(WIDTH, EQUAL, 20),
        }) | border | center;
    });
    
    screen.Loop(renderer);
}

void UserInterface::systemScreen() {
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    atomic<bool> refresh_ui_continue = true;
    thread refresh_ui([&] {
        while (refresh_ui_continue) {
            this_thread::sleep_for(0.05s);
            screen.Post(Event::Custom);
        }
    });

    System *mainSystem = new System(settings);
    Conveyor *conveyor = mainSystem->firstConveyor;

    Component exitButton = Button(&settings.language.exit, [&] { screen.Exit(); }, 
        ButtonOption::Ascii());

    bool isSystemStarted = false;
    string systemButtonLable = settings.language.systemMenuStartButton;
    Component systemButton = Button(&systemButtonLable, 
        [&] { 
            if (!isSystemStarted) {
                mainSystem->start();
                systemButtonLable = settings.language.systemMenuStopButton;
            }
            else mainSystem->stop();
            isSystemStarted = !isSystemStarted;
        }, ButtonOption::Ascii());

    string conveyorButtonLable = settings.language.systemMenuConveyorStartButton;
    Component conveyorButton = Button(&conveyorButtonLable, 
        [&] { 
            if (conveyor->status) conveyor->stop();
            else conveyor->start();
        }, ButtonOption::Ascii());

    int tabSelected = 0;
    Component tabToggle = Toggle(&settings.language.systemMenuTabs, &tabSelected);

    Component buttons = Container::Horizontal({
        systemButton | flex,
        Renderer([&] { return separator(); }),
        conveyorButton | flex,
        Renderer([&] { return separator(); }),
        exitButton | flex
    });

    Component container = Container::Vertical({
        tabToggle,
        buttons
    });
    Component renderer = Renderer(container, [&] {
        switch (tabSelected) {
        case 0: conveyor = mainSystem->firstConveyor; break;
        case 1: conveyor = mainSystem->secondConveyor; break;
        case 2: conveyor = mainSystem->thirdConveyor; break;
        }

        if (!mainSystem->firstConveyor->status ||
            !mainSystem->secondConveyor->status ||
            !mainSystem->thirdConveyor->status) {
            isSystemStarted = false;
            systemButtonLable = settings.language.systemMenuStartButton;
        }
        else {
            isSystemStarted = true;
            systemButtonLable = settings.language.systemMenuStopButton;
        }

        conveyorButtonLable = conveyor->status ? settings.language.systemMenuConveyorStopButton : 
            settings.language.systemMenuConveyorStartButton;

        // Сonveyor animation builder
        Component conveyorContainer = Container::Vertical({});
        ConveyorStatuses statuses = conveyor->getStatuses();
        int beltIndex = statuses.detailXCords >= 0 ? statuses.detailXCords % 3 : 0;
        for (int index = 0; index < 13; index++) {
            string line = vformat(conveyorTemplate[index], 
                make_format_args(
                    containerStates[0][statuses.topContainer],
                    containerStates[1][statuses.topContainer],
                    statuses.topContainerValue,
                    containerStates[0][statuses.bottomContainer],
                    containerStates[1][statuses.bottomContainer],
                    statuses.bottomContainerValue,
                    beltStates[2 - beltIndex],
                    beltStates[beltIndex],
                    detectorStates[statuses.firstDetector], 
                    detectorStates[statuses.secondDetector]
                ));

            if (index >= 6 && index <= 7 && statuses.detailType >= 0) {
                string detail = vformat(boxTypes[statuses.detailType][index - 6], 
                    make_format_args(statuses.detailData));
                for (int pixelCord = 0; pixelCord < detail.size(); pixelCord++)
                    line[7 + pixelCord + statuses.detailXCords] = detail[pixelCord];
            }

            if (index >= 5 && index <= 7) {
                string printer = (index - 5) == statuses.printer ? printerStates[1] : printerStates[0];
                if (statuses.printer == 0 && index != 5 || (index - 5) > statuses.printer) printer = "";
                for (int pixelCord = 0; pixelCord < printer.length(); pixelCord++)
                    line[32 + pixelCord] = printer[pixelCord];
            }
            
            conveyorContainer->Add(Renderer([line] { return text(line); }));
        } 

        return vbox({
            text(settings.language.systemMenuTitle) | bold | center,
            separator(),
            tabToggle->Render(),
            separator(),
            conveyorContainer->Render() | center,
            separator(),
            text(settings.language.systemErrors[statuses.errorIndex]) | color(Color::Red),
            separator(),
            buttons->Render(),
        }) | size(WIDTH, EQUAL, 78) | border | center;
    });
    screen.Loop(renderer);
    refresh_ui_continue = false;
    refresh_ui.join();
    delete mainSystem;
}

void UserInterface::settingsScreen() {
    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    RadioboxOption option = RadioboxOption();
    option.focused_entry = selectedLanguageIndex;
    option.on_change = [&] { settings.language = languages[selectedLanguageIndex]; };
    Component languageRadiobox = Radiobox(&settings.language.settingsMenuLanguageEntries, 
        &selectedLanguageIndex, option);
    Component exitButton = Button(&settings.language.exit, [&] { screen.Exit(); }, 
        ButtonOption::Ascii());
    Component firstContainerValueSlider = Slider("", &settings.firstContainerValue, 
        0, settings.containerMaxValue, 1);
    Component secondContainerValueSlider = Slider("", &settings.secondContainerValue, 
        0, settings.containerMaxValue, 1);
    Component thirdContainerValueSlider = Slider("", &settings.thirdContainerValue, 
        0, settings.containerMaxValue, 1);

    Component container = ftxui::Container::Vertical({
        languageRadiobox,
        firstContainerValueSlider,
        secondContainerValueSlider,
        thirdContainerValueSlider,
        exitButton,
    });
    Component renderer = Renderer(container, [&] {
        return vbox({
            text(settings.language.settingsMenuTitle) | bold | center,
            separator(),
            text(settings.language.settingsMenuLanguage),
            separator(),
            languageRadiobox->Render(),
            separator(),
            text(settings.language.settingsMenuConatinerValue),
            separator(),
            hbox(text(settings.language.settingsMenuFirstConatiner),
                 text(": " + to_string(settings.firstContainerValue))),
            firstContainerValueSlider->Render(),
            hbox(text(settings.language.settingsMenuSecondConatiner),
                 text(": " + to_string(settings.secondContainerValue))),
            secondContainerValueSlider->Render(),
            hbox(text(settings.language.settingsMenuThirdConatiner),
                 text(": " + to_string(settings.thirdContainerValue))),
            thirdContainerValueSlider->Render(),
            separator(),
            exitButton->Render(),
        }) | size(WIDTH, EQUAL, 50) | border | center;
    });
    screen.Loop(renderer);
}

void UserInterface::aboutScreen() {
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    Component exitButton = Button(settings.language.exit, [&] { screen.Exit(); },
        ButtonOption::Ascii());
    auto renderer = Renderer(exitButton, [&] {
        return vbox({
            text(settings.language.aboutMenuTitle) | bold | center,
            separator(),
            hbox(text(settings.language.aboutMenuCodename + ": "),
                color(Color::Green, text(projectCodename))),
            hbox(text(settings.language.aboutMenuCreator + ": "),
                color(Color::Cyan, text(projectCreator))),
            separator(),
            exitButton->Render(),
        }) | size(WIDTH, EQUAL, 20) | border | center;
    });
    screen.Loop(renderer);
}

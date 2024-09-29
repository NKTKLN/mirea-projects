#include <ctime>
#include <thread>
#include <vector>
#include <string>

#include "models.h"
#include "system.h"

#define DETAIL_SIZE 4
#define PRINTER_CORDS 25
#define MAX_DETAIL_CORDS 47
#define FIRST_DETECTOR_CORDS 13
#define SECOND_DETECTOR_CORDS 42
#define STOREHOUSE_MAX_VALUE 999

using namespace std;

// TickGenerator class functions
void TickGenerator::run() {
    while (status) {
        this_thread::sleep_for(0.3s);
        currentTick++;
    }
}

TickGenerator::TickGenerator() : currentTick(0), status(true) { 
    mainThread = thread(&TickGenerator::run, this);
}

TickGenerator::~TickGenerator() { 
    if (!status) return;

    status = false;
    mainThread.join();
}

void TickGenerator::delay(int ticks) {
    int endTick = currentTick + ticks;
    while (endTick > currentTick) {}
}

// Detail class functions
Detail::Detail(int _typeIndex) : typeIndex(_typeIndex) {}

// Container class functions
DetailContainer::DetailContainer(int _maxNumberOfDetails) : 
    maxNumberOfDetails(_maxNumberOfDetails), topDriverStatus(false), 
    bottomDriverStatus(false) {}

DetailContainer::DetailContainer(int _maxNumberOfDetails, int numberOfDetails, int detailTypeIndex) : 
    maxNumberOfDetails(_maxNumberOfDetails), topDriverStatus(true), bottomDriverStatus(false) { 
    fillWithDetails(numberOfDetails, detailTypeIndex);
    topDriverStatus = false;
}

DetailContainer::~DetailContainer() {
    for (int index = 0; index < details.size(); index++)
        delete details[index];
    details.clear();
}

Detail *DetailContainer::getDatail() {
    if (details.empty())
        throw underflow_error("The container ran out of details.");

    if (!bottomDriverStatus)
        throw logic_error("The container lid is closed.");

    Detail *tmp = details.back();
    details.pop_back();

    return tmp;
}

void DetailContainer::addDetail(Detail *detail) {
    if (details.size() + 1 > maxNumberOfDetails)
        throw out_of_range("The maximum level of details in the container has been exceeded.");

    if (!topDriverStatus)
        throw logic_error("The container lid is closed.");

    details.push_back(detail);
}

void DetailContainer::fillWithDetails(int numberOfDetails, int detailTypeIndex) {
    if (numberOfDetails + details.size() > maxNumberOfDetails)
        throw out_of_range("The maximum level of details in the container has been exceeded.");

    for (int index = 0; index < numberOfDetails; index++)
        addDetail(new Detail(detailTypeIndex));
}

int DetailContainer::getNumberOfDetails() { return details.size(); }

int DetailContainer::getMaxNumberOfDetails() { return maxNumberOfDetails; }

// Belt class functions
void Belt::run() {
    if (!detail) {
        status = false;
        throw logic_error("There are no details on the conveyor belt.");
    }

    while (status && detailXCords < MAX_DETAIL_CORDS) {
        tickGenerator->delay(1);
        detailXCords++;
    }
}

Belt::Belt(TickGenerator *_tickGenerator) : 
    status(false), detailXCords(0), detail(nullptr), tickGenerator(_tickGenerator) {}

Belt::~Belt() { stop(); }

void Belt::stop() {
    if (!status) return;

    status = false;
    mainThread.join();
}

void Belt::start() {
    if (status) return;

    status = true;
    mainThread = thread(&Belt::run, this);
}

int Belt::getDetailCords() {
    if (!detail)
        throw underflow_error("There is no detail on the belt.");

    return detailXCords;
}

Detail *Belt::getDetail() {
    if (!detail)
        throw underflow_error("There is no detail on the belt.");

    return detail;
}

Detail *Belt::pickUpDetail() {
    if (!detail)
        throw underflow_error("There is no detail on the belt.");

    if (detailXCords < MAX_DETAIL_CORDS)
        throw logic_error("The detal didn't go all the way through.");

    Detail *tmpDetail = detail;
    detail = nullptr;
    stop();

    return tmpDetail;
}

void Belt::putDetail(Detail *newDetail) {
    if (!newDetail)
        throw overflow_error("There's already a detail on the belt.");

    detail = newDetail;
    detailXCords = 0;
}

// Printer class functions
Printer::Printer(Belt *_belt, TickGenerator *_tickGenerator, void (*_printFunction)(Detail *)) : 
    printerStatus(0), status(true), belt(_belt), tickGenerator(_tickGenerator), 
    printFunction(_printFunction) {};

void Printer::print() {
    for (; (printerStatus < 2) && status; printerStatus++)
        tickGenerator->delay(1);

    if (!status) return;
    printFunction(belt->getDetail());

    for (; (printerStatus > 0) && status; printerStatus--)
        tickGenerator->delay(1);
}

void Printer::stop() { status = false; }

void Printer::start() { 
    status = true;
    for (; (printerStatus > 0) && status; printerStatus--)
        tickGenerator->delay(1);
}

int Printer::getPrinterStatus() { return printerStatus; }

// Detector class functions
Detector::Detector(Belt *_belt, int _detectableCords) : 
    belt(_belt), detectableCords(_detectableCords) {};

bool Detector::getStatus() {
    try {
        return belt->getDetailCords() >= detectableCords && 
            belt->getDetailCords() < detectableCords + DETAIL_SIZE;
    }
    catch (const underflow_error& error) { return false; }
}

// Conveyor class functions
void Conveyor::run() {
    /*
      \    /\
       )  ( ')
      (  /  )
       \(__)|
    
    I'm a little kitten who's tired of writing code. 
    Please do not pick on the crutches written below, meow :3
    */

    try {
        int detailCords = belt->getDetailCords();
        if ((detailCords > 0 && detailCords < 25) || 
            (detailCords > 26 && detailCords < MAX_DETAIL_CORDS)) belt->start();
    }
    catch (const underflow_error& error) {}

    while (status) {
        int detailCords;
        try { detailCords = belt->getDetailCords(); }
        catch (const underflow_error& error) { detailCords = -1; }
        
        if (detailCords == -1 && !topContainer->bottomDriverStatus) {
            if (topContainer->getNumberOfDetails() <= 0) {
                errorIndex = 1; // The container ran out of details.
                break;
            }

            topContainer->bottomDriverStatus = true;
        }
        else if (detailCords == -1 && topContainer->bottomDriverStatus)
            belt->putDetail(topContainer->getDatail());
        else if (detailCords == 0 && topContainer->bottomDriverStatus)
            topContainer->bottomDriverStatus = false;
        else if (detailCords == 0 && !topContainer->bottomDriverStatus)
            belt->start();
        else if (detailCords == PRINTER_CORDS) {
            belt->stop();
            tickGenerator->delay(1);
            if (!status) break;
            printer->print();
            tickGenerator->delay(1);
            if (!status) break;
            belt->start();
        }
        else if (secondDetector->getStatus())
            bottomContainer->topDriverStatus = true;
        else if (detailCords == MAX_DETAIL_CORDS) {
            if (bottomContainer->getMaxNumberOfDetails() < bottomContainer->getNumberOfDetails() + 1) {
                errorIndex = 2; // The maximum level of details in the container has been exceeded.
                break;
            }

            bottomContainer->addDetail(belt->pickUpDetail());
            tickGenerator->delay(1);
            if (!status) break;
            bottomContainer->topDriverStatus = false;

            if (bottomContainer->getMaxNumberOfDetails() <= bottomContainer->getNumberOfDetails()) {
                errorIndex = 2; // The maximum level of details in the container has been exceeded.
                break;
            }
        }
        tickGenerator->delay(1);
    }

    status = false;
    belt->stop();
    printer->stop();
}

Conveyor::Conveyor(DetailContainer *_topContainer, DetailContainer *_bottomContainer, 
    TickGenerator *_tickGenerator, void (*printFunction)(Detail *)) : topContainer(_topContainer), 
    bottomContainer(_bottomContainer), tickGenerator(_tickGenerator), status(false), errorIndex(0) {
    belt = new Belt(tickGenerator);
    printer = new Printer(belt, tickGenerator, printFunction);
    firstDetector = new Detector(belt, FIRST_DETECTOR_CORDS);
    secondDetector = new Detector(belt, SECOND_DETECTOR_CORDS);
}

Conveyor::~Conveyor() {
    belt->stop();
    printer->stop();
    try { mainThread.join(); }
    catch (const exception& e){}

    delete belt;
    delete printer;
    delete firstDetector;
    delete secondDetector;
}

void Conveyor::stop() {
    if (!status) return;

    status = false;
    belt->stop();
    printer->stop();
    mainThread.join();
}

void Conveyor::start() {
    if (status) return;

    try { mainThread.join(); }
    catch (const exception& e){}

    status = true;
    errorIndex = 0;
    printer->start();
    mainThread = thread(&Conveyor::run, this);
}

ConveyorStatuses Conveyor::getStatuses() {
    ConveyorStatuses statuses;
    
    try {
        Detail *tmpDetail = belt->getDetail();
        statuses.detailXCords = belt->getDetailCords();
        statuses.detailType = tmpDetail->typeIndex;
        statuses.detailData = tmpDetail->data;
    }
    catch (const underflow_error& error) {
        statuses.detailXCords = -1;
        statuses.detailType = -1;
        statuses.detailData = "";
    }

    statuses.errorIndex = errorIndex;
    statuses.printer = printer->getPrinterStatus();
    statuses.firstDetector = firstDetector->getStatus();
    statuses.secondDetector = secondDetector->getStatus();
    statuses.topContainer = topContainer->bottomDriverStatus;
    statuses.bottomContainer = bottomContainer->topDriverStatus;
    statuses.topContainerValue = topContainer->getNumberOfDetails();
    statuses.bottomContainerValue = bottomContainer->getNumberOfDetails();
    
    return statuses;
}

// System class functions
void System::stop() {
    firstConveyor->stop();
    secondConveyor->stop();
    thirdConveyor->stop();
}

void System::start() {
    firstConveyor->start();
    secondConveyor->start();
    thirdConveyor->start();
}

System::System(const Settings settings) {
    tickGenerator = new TickGenerator();

    firstContainer = new DetailContainer(settings.containerMaxValue, settings.firstContainerValue, 0);
    secondContainer = new DetailContainer(settings.containerMaxValue, settings.secondContainerValue, 1);
    thirdContainer = new DetailContainer(settings.containerMaxValue, settings.thirdContainerValue, 2);
    storehouseContainer = new DetailContainer(STOREHOUSE_MAX_VALUE);

    firstConveyor = new Conveyor(firstContainer, secondContainer, tickGenerator, 
        [](Detail* detail){ detail->typeIndex = 1; });
    secondConveyor = new Conveyor(secondContainer, thirdContainer, tickGenerator, 
        [](Detail* detail){ detail->typeIndex = 2; });
    thirdConveyor = new Conveyor(thirdContainer, storehouseContainer, tickGenerator, 
        [](Detail* detail){ 
            srand(time(0));
            detail->typeIndex = 3;
            detail->data = char(65 + rand() % 26) + to_string(rand() % 10);
        });
}

System::~System() {
    stop();

    delete tickGenerator;
    
    delete firstContainer;
    delete secondContainer;
    delete thirdContainer;
    delete storehouseContainer;
    
    delete firstConveyor;
    delete secondConveyor;
    delete thirdConveyor;
}

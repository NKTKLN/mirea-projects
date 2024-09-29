#ifndef system
#define system

#include <thread>
#include <vector>
#include <string>

#include "models.h"

class TickGenerator {
private:
    bool status;
    int currentTick;
    thread mainThread;

    void run();

public:
    TickGenerator();
    ~TickGenerator();

    void delay(int ticks);
};

class Detail {
public:
    string data;
    int typeIndex;

    Detail(int _typeIndex);
};

class DetailContainer {
private:
    int maxNumberOfDetails;
    vector<Detail *> details;

public:
    bool topDriverStatus;
    bool bottomDriverStatus;

    DetailContainer(int _maxNumberOfDetails);
    DetailContainer(int _maxNumberOfDetails, int numberOfDetails, int detailTypeIndex);
    ~DetailContainer();

    int getNumberOfDetails();
    int getMaxNumberOfDetails();
    Detail *getDatail();

    void addDetail(Detail *detail);
    void fillWithDetails(int numberOfDetails, int detailTypeIndex);
};

class Belt {
private:
    bool status;
    int detailXCords;
    thread mainThread;

    Detail *detail;
    TickGenerator *tickGenerator;

    void run();

public:
    Belt(TickGenerator *_tickGenerator);
    ~Belt();

    void stop();
    void start();
    
    int getDetailCords();
    Detail *getDetail();
    Detail *pickUpDetail();

    void putDetail(Detail *detail);
};

class Printer {
private:
    int status;
    int printerStatus;

    Belt *belt;
    TickGenerator *tickGenerator;
    void (*printFunction)(Detail *);

public:
    Printer(Belt *_belt, TickGenerator *_tickGenerator, void (*_printFunction)(Detail *));

    void stop();
    void start();

    void print();

    int getPrinterStatus();
};

class Detector {
private:
    int detectableCords;

    Belt *belt;

public:
    Detector(Belt *_belt, int _detectableCords);

    bool getStatus();
};

class Conveyor {
private:
    thread mainThread;
    int errorIndex;

    Belt *belt;
    Printer *printer;
    Detector *firstDetector;
    Detector *secondDetector;
    DetailContainer *topContainer;
    DetailContainer *bottomContainer;
    TickGenerator *tickGenerator;

    void run();

public:
    bool status;

    Conveyor(DetailContainer *_topContainer, DetailContainer *_bottomContainer, 
        TickGenerator *_tickGenerator, void (*printFunction)(Detail *));
    ~Conveyor();

    void stop();
    void start();

    ConveyorStatuses getStatuses();
};

class System {
private:
    TickGenerator *tickGenerator;

    DetailContainer *firstContainer;
    DetailContainer *secondContainer;
    DetailContainer *thirdContainer;
    DetailContainer *storehouseContainer;

public:
    Conveyor *firstConveyor;
    Conveyor *secondConveyor;
    Conveyor *thirdConveyor;

    System(const Settings settings);
    ~System();

    void stop();
    void start();
};

#endif

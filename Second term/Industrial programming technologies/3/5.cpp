#include <iostream>

using namespace std;

class Person {
public:
    string sex;
    string name;
    string date;
    int signIndex;
    string surname;

    Person(string sex, string date, string name, string surname);
    virtual void find() = 0;
    void goAway();
protected:
    int getSign();
};

Person *peoples[10];

class MilkHunter : public Person {
public:
    MilkHunter(string sex, string date, string name, string surname) : Person(sex, date, name, surname) {};
    void find();
};

class Skuf : public Person {
public:
    Skuf(string sex, string date, string name, string surname) : Person(sex, date, name, surname) {};
    void find();
};

class Altushka : public Person {
public:
    Altushka(string sex, string date, string name, string surname) : Person(sex, date, name, surname) {};
    void find();
};

class Extended : public Person {
public:
    Extended(string sex, string date, string name, string surname) : Person(sex, date, name, surname) {};
    void find();
};

Person::Person(string _sex, string _date, string _name, string _surname) : 
    sex(_sex), date(_date), name(_name), surname(_surname) {
    this->signIndex = getSign();
}

void Person::goAway() {
	int personIndex = 0;
    while (personIndex < 10 && peoples[personIndex] != this)
        personIndex++;

	for (int index = personIndex; index < 9; index++)
		peoples[index] = peoples[index + 1];

	peoples[9] = nullptr;
}

int Person::getSign() {
    int day, month, year;
    sscanf(this->date.c_str(), "%d.%d.%d", &day, &month, &year);

    if ((day >= 21 && month == 1)  || (day <= 19 && month == 2))  return 1;
    if ((day >= 20 && month == 2)  || (day <= 20 && month == 3))  return 2;
    if ((day >= 21 && month == 3)  || (day <= 20 && month == 4))  return 3;
    if ((day >= 21 && month == 4)  || (day <= 21 && month == 5))  return 4;
    if ((day >= 22 && month == 5)  || (day <= 21 && month == 6))  return 5;
    if ((day >= 22 && month == 6)  || (day <= 22 && month == 7))  return 6;
    if ((day >= 23 && month == 7)  || (day <= 22 && month == 8))  return 7;
    if ((day >= 22 && month == 8)  || (day <= 23 && month == 9))  return 8;
    if ((day >= 24 && month == 9)  || (day <= 23 && month == 10)) return 9;
    if ((day >= 24 && month == 10) || (day <= 22 && month == 11)) return 10;
    if ((day >= 23 && month == 11) || (day <= 21 && month == 12)) return 11;
    if ((day >= 23 && month == 12) || (day <= 20 && month == 1))  return 12;
    return 0;
}

void MilkHunter::find() {
    Person* person = nullptr;

    for (int index = 0; index < 10; index++) {
        Extended *personPtr = dynamic_cast<Extended *>(peoples[index]);
        if (personPtr == nullptr) continue;
        if (person == nullptr || person->date < personPtr->date)
            person = personPtr;
    }

    if (person == nullptr) {
        cout << "oops" << endl;
        return;
    }
        
    cout << person->name << endl
         << person->surname << endl
         << person->date << endl;
}

void Skuf::find() {
    Person* person = nullptr;

    for (int index = 0; index < 10; index++) {
        Altushka *personPtr = dynamic_cast<Altushka *>(peoples[index]);
        if (personPtr == nullptr) continue;
        if (person == nullptr  || person->date > personPtr->date)
            person = personPtr;
    }

    if (person == nullptr) {
        cout << "oops" << endl;
        return;
    }
        
    cout << person->name << endl
         << person->surname << endl
         << person->date << endl;
}

void Altushka::find() {
    Person* person = nullptr;

    for (int index = 0; index < 10; index++) {
        Skuf *personPtr = dynamic_cast<Skuf *>(peoples[index]);
        if (personPtr == nullptr) continue;
        if (person == nullptr || (personPtr->signIndex == this->signIndex && person->date < personPtr->date))
            person = personPtr;
    }

    if (person == nullptr) {
        cout << "oops" << endl;
        return;
    }
    
    cout << person->name << endl
         << person->surname << endl
         << person->date << endl;
}

void Extended::find() {
    Person* person = nullptr;

    for (int index = 0; index < 10; index++) {        
        MilkHunter *personPtr = dynamic_cast<MilkHunter *>(peoples[index]);
        if (personPtr == nullptr) continue;
        if (person == nullptr || (personPtr->signIndex == (this->signIndex + 6) % 12 && person->date > personPtr->date))
            person = personPtr;
    }

    if (person == nullptr) {
        cout << "oops" << endl;
        return;
    }

    cout << person->name << endl
         << person->surname << endl
         << person->date << endl;
}

Person *goIn() {
    string sex;
    string name;
    string surname;
    string date;
    int day, month, year;

    cin >> surname >> name >> sex >> date;
    sscanf(date.c_str(), "%d.%d.%d", &day, &month, &year);

    int age = 2024 - year;    
    if ((month > 1) || (month == 1 && day > 1)) age--;

    if (sex == "m" && age >= 25)
        return new Skuf(sex, date, name, surname);
    else if (sex == "m" && age < 25)
        return new MilkHunter(sex, date, name, surname);
    else if (sex == "f" && age >= 25)
        return new Extended(sex, date, name, surname);
    else if (sex == "f" && age < 25)
        return new Altushka(sex, date, name, surname);
    return nullptr;
}

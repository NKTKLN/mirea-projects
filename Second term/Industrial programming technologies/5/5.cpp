#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class Verdict {
public: 
    virtual string Article() const { return "You're free for now, but be careful from now on"; }
    virtual ~Verdict() { }
};

class Voprosik: public Verdict { 
    string Article() const override { return "Vam chelovechek na cifri naberet"; } 
};

class Temka: public Verdict { 
    string Article() const override { return "Poidem poshurshim, otskochim potreskochem"; } 
};

class Business: public Verdict { 
    string Article() const override { return "Molodoi chelovek, proidemte"; } 
};

using CriminalCase = vector<unique_ptr<Verdict>>;

CriminalCase createCriminalCase() {
    CriminalCase cc;
    string word;
    while (cin >> word) {
        if (word == "Voprosik") cc.push_back(make_unique<Voprosik>());
        else if (word == "Temka") cc.push_back(make_unique<Temka>());
        else if (word == "Business") cc.push_back(make_unique<Business>());
        else break;
    }
    return cc;
}

void RedHanded(const CriminalCase& criminalCase) {
    for (const auto& verdict: criminalCase) {
        if (&verdict != &criminalCase.back()) cout << verdict->Article() << endl;
        else cout << verdict->Article();
    }
}

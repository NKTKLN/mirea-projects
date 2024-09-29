#include <cmath>
#include <iostream>

using namespace std;

class NotifierBase {
public:
	virtual void notify(const string& message) = 0;
};

class BKNotifier : public NotifierBase {
private:
	string id;
public:
	BKNotifier(string id);
	void notify(const string& message);
};

class TelegraphNotifier: public NotifierBase {
private:
	string login;
public:
	TelegraphNotifier(string id);
	void notify(const string& message);
};

void SendBK(const string& id, const string& message) {
	cout << "Send '" << message << "' to BK user " << id << endl;
}

void SendTelegraph(const string& login, const string& message) {
	cout << "Send '" << message << "' to Telegraph user " << login << endl;
}

void BKNotifier::notify(const string& message) { SendBK(this->id, message); }

void TelegraphNotifier::notify(const string& message) { SendTelegraph(this->login, message); }

BKNotifier::BKNotifier(string id) { this->id = id; }

TelegraphNotifier::TelegraphNotifier(string login) { this->login = login; }

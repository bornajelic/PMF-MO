#include <list>
#include <string>
using namespace std;

class Vehicle {
private:
	int max_speed, cc;
	string registration;
	static list<Vehicle *> vehicles;
protected:
	int gas;
public:
	Vehicle(int max_speed, int cc, string registration);
	int get_max_speed();
	int get_cc();
	string get_registration();
	int get_gas();
	virtual void drive_10km();
	list<Vehicle *> same_speed();
	static Vehicle& fastest();
	~Vehicle();
};

class Motorcycle : public Vehicle {
private:
	string type;
public:
	Motorcycle(int max_speed, int cc, string registration, char type_);
	void drive_10km();
	string get_type();
};

class Car : public Vehicle {
private:
	int volume;
public:
	Car(int max_speed, int cc, string registration, int volume_);
	void drive_10km();
	int get_volume();
};

#include "vehicle.h"

list<Vehicle *> Vehicle::vehicles;

Vehicle::Vehicle(int max_speed_, int cc_, string registration_) {
	max_speed = max_speed_;
	cc = cc_;
	registration = registration_;
	gas = 100;
	if (!vehicles.empty()) {
		list<Vehicle *>::iterator li = vehicles.begin();
		for (; li != vehicles.end(); li++) {
			if ((*li)->get_max_speed() > max_speed || ((*li)->get_max_speed() == max_speed && (*li)->get_cc() >= cc)) {
					break;
			}
		}
		vehicles.insert(li, this);
	} else {
		vehicles.push_back(this);
	}
};
int Vehicle::get_max_speed() {
	return max_speed;
};
int Vehicle::get_cc() {
	return cc;
};
string Vehicle::get_registration() {
	return registration;
};
int Vehicle::get_gas() {
	return gas;
};
void Vehicle::drive_10km() {
	gas -= 10;
};
list<Vehicle *> Vehicle::same_speed() {
	list<Vehicle *>::iterator li = vehicles.begin();
	for (; li != vehicles.end(); li++) {
		if ((*li)->get_max_speed() >= max_speed) {
			break;
		}
	}
	list<Vehicle *> same_speed;
	for (; li != vehicles.end(); li++) {
		if ((*li)->get_max_speed() != max_speed) {
			break;
		}
		same_speed.push_back(*li);
	}
	return same_speed;
};
Vehicle& Vehicle::fastest() {
	list<Vehicle *>::iterator li = vehicles.begin(), it = li;
	for (; li != vehicles.end(); li++) {
		it = li;
	}
	return **it;
};
Vehicle::~Vehicle() {
	list<Vehicle *>::iterator li;
	for (li = vehicles.begin(); li != vehicles.end(); ++li) {
		if (*li == this) {
			vehicles.erase(li);
			break;
		}
	}
};

Motorcycle::Motorcycle(int max_speed, int cc, string registration, char type_)
	:Vehicle(max_speed, cc, registration) {
	if  (type_ == 'R') {
		type = "race";
	} else if (type_ == 'S') {
		type = "skuter";
	}
};
void Motorcycle::drive_10km() {
	gas -= 5;
};
string Motorcycle::get_type() {
	return type;
};

Car::Car(int max_speed, int cc, string registration, int volume_)
	:Vehicle(max_speed, cc, registration) {
	volume = volume;
};
void Car::drive_10km(){
	gas -= 15;
};
int Car::get_volume() {
	return volume;
};

#include <iostream>
#include <list>
#include "vehicle.h"
int main(void) {
	Vehicle A(200, 500, "AAAA"), B(200, 600, "BBBB"), C(240, 1100, "CCCC");
	Motorcycle M(300, 600, "MMMM", 'R');
	Car T(150, 500, "TTTT", 100);
	Vehicle *niz_vozila[5];
	niz_vozila[0] = new Car(200, 900, "R0000", 70);
	niz_vozila[1] = new Motorcycle(300, 650, "R1111", 'R');
	niz_vozila[2] = new Vehicle(250, 800, "R2222");
	niz_vozila[3] = new Car(150, 400, "R3333", 90);
	niz_vozila[4] = new Motorcycle(200, 300, "R4444", 'S');
	
	cout << "Motor M:" << endl;
	cout << M.get_max_speed() << " "
		<< M.get_cc() << " "
		<< M.get_registration() << " "
		<< M.get_type() << endl;
	
	// Motor M:
	// 300 600 MMMM race
	
	for(int i = 0; i < 5; i++)
	{
		niz_vozila[i]->drive_10km();
		niz_vozila[i]->drive_10km();
		niz_vozila[i]->drive_10km();
	}
	
	cout << "Nakon voznje:" << endl;
	for(int i = 0; i < 5; i++)
		cout << niz_vozila[i]->get_max_speed() << " "
			<< niz_vozila[i]->get_cc() << " "
			<< niz_vozila[i]->get_registration() << " "
			<< niz_vozila[i]->get_gas() << endl;
	// Nakon voznje:
	// 200 900 R0000 55
	// 300 650 R1111 85
	// 250 800 R2222 70
	// 150 400 R3333 55
	// 200 300 R4444 85
	
	cout << "Najbrzi:" << endl;
	Vehicle &najbrzi = Vehicle::fastest();
	cout << najbrzi.get_max_speed() << " "
		<< najbrzi.get_cc() << " "
		<< najbrzi.get_registration() << endl;
	//Najbrzi:
	//300 650 R1111
	
	cout << "Jednaka brzina:" << endl;
	list<Vehicle *> lista_vozila = A.same_speed();
	list<Vehicle *>:: iterator it;
	for(it = lista_vozila.begin(); it != lista_vozila.end(); ++it)
		cout << (*it)->get_cc() << " " << (*it)->get_registration() << endl;
	// Jednaka brzina:
	// 300 R4444
	// 500 AAAA
	// 600 BBBB
	// 900 R0000
	
	for(int i = 0; i < 5; i++)
		delete niz_vozila[i];
	
	return 0;
}

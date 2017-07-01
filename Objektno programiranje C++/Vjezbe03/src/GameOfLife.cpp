#include "GameOL.h"
#include <iostream>
#include <string>

static const std::string TERMINATE = "exit";
bool user_continue() {
	std::cout << std::endl << "If you want to quit and save your work type: \"" << TERMINATE
			<< "\"." << std::endl << "Otherwise, press ENTER to continue:" << std::endl
			<< "> ";
	std::string input;
	std::getline(std::cin, input);
	return input != TERMINATE;
}

int main(int argc, char * argv[]) {
	// uèitaj ulazno stanje iz datoteke. Datoteka je pocetno_stanje.txt
	// ili je zadana argumentom komandne linije
	std::string input_file("pocetno_stanje.txt");
	if (argc > 1)
		input_file = argv[1];

	GameOL gol;  // defaultni konstruktor

	// Inicijaliziraj Game Of Live objekt s poèetnim stanjem
	// koje je zadano u datoteci input_file
	gol.init(input_file);

	// iscrtaj poèetno stanje
	gol.print();

	while (user_continue()) {
		gol.update();  // prijelaz automata u novo stanje
		gol.print();
		std::cout << "Next step ? ";
	}
	// ispiši završno stanje u datoteku
	gol.print("zavrsno_stanje.txt");

	return 0;
}

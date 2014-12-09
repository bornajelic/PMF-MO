#include "pracenjeStudenataProtokol.h"

#include "h_core.h"
#include "h_clientCommands.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main(int args, char **argv) {
	
	//provjerava broj unesenih argumenata:
	
	if (args != 3) {
		fprintf(stderr, "Koristenje: ./klijent IP_adresa port");
		exit(0);
	}
	
	//puni strukturu sockaddr_in:
	
	unsigned short		port;
	sscanf (argv[2], "%hu", &port);
	
	struct sockaddr_in	adresa;
	
	adresa.sin_family	= AF_INET;
	adresa.sin_port		= htons(port);
	
	if (inet_aton(argv[1], &(adresa.sin_addr)) == 0) {
		perror("Adresa je losa.");
		exit(0);
	}
	memset(adresa.sin_zero, '\0', 8);
	memset(adresa.sin_zero, '\0', 8);
	
	//otvara socket:
	
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("Socket\n");
		exit(0);
	}
	
	//spaja se:
	
	if (
		connect(
			sock,
			(struct sockaddr*) &adresa,
			sizeof(adresa)
		)
		== -1
	) {
		perror("Connect\n");
		exit(0);
	}
	
	//pozdravljanje korisnika i pokretanje enginea:
	
	cout << "Uspjesno ste spojeni na " << argv[2] << "." << endl;
	cout << "Za pomoc utipkajte '?' ili 'help' (bez navodnika)!" << endl;
	core c(new clientCommands());
	c.run(sock);
	
	close(sock);
	
	return 0;
}
